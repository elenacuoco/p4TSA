"""The block rule's short blocks (WaveletThreshold / WDF2Classify SetBlockRemainder).

A run (pyramid level, packet band, LocalCos row) is cut into blocks of
L = round(ln N); the remainder of 1 ... L-1 coefficients, and a whole run
shorter than L, is a short block. legacy (the default) judges it against
lambda n sigma^2 like a full block, merge joins the remainder to the block
before it, scaled judges it at the full block's false-alarm probability,
Qinv_chi2_n(Q_chi2_L(lambda L)).
"""
import hashlib
import json
import os

import numpy as np
import pytest

from py4tsa import tsa

FS = 2048.0
LAMBDA = 4.505
D0 = "Haar,DaubC4,DaubC8,Sym4,DaubC16,Sym8,Coif3,DaubC24,Sym12,Coif5"
WT = tsa.WaveletThreshold
MODES = ("legacy", "merge", "scaled")
HERE = os.path.dirname(os.path.abspath(__file__))
# Trigger digests of the block rule before the remainder option existed.
FIXTURE = os.path.join(HERE, "data", "block_remainder_legacy_digests.json")
# Directory of whitened strain windows (npz, array "w") for the real-data
# digests; those cases are skipped when it is not set.
STREAMS = [d for d in (os.environ.get("P4TSA_WHITENED_STREAMS", ""),) if d and os.path.isdir(d)]


def view_of(x):
    v = tsa.SeqView_double_t(0.0, 1.0 / FS, len(x))
    fp = v.FillPoint
    for i, value in enumerate(np.asarray(x, dtype=float).tolist()):
        fp(0, i, value)
    return v


def values(v, n):
    return np.array([v.GetY(0, i) for i in range(n)])


def threshold(c, depth, mode=None, length=0, lam=LAMBDA):
    t = WT(len(c))
    t.SetLayout(depth)
    t.SetBlock(length, lam)
    if mode is not None:
        t.SetBlockRemainder(mode)
    v = view_of(c)
    t(v, WT.block)
    return values(v, len(c)), t.GetSigma()


# ------------------------------------------------------------ reference
def runs(n, depth):
    if depth == 0:
        edges = [0, 1] + [2 ** k for k in range(1, int(np.log2(n)) + 1)]
    else:
        edges = list(range(0, n + 1, n >> depth))
    return list(zip(edges[:-1], edges[1:]))


def ref_blocks(n, depth, L, mode):
    """The block partition: every run cut into blocks of L from its first index;
    under merge a last block shorter than L joins the one before it."""
    out = []
    for start, end in runs(n, depth):
        cut = [(b, min(b + L, end)) for b in range(start, end, L)]
        if mode == "merge" and len(cut) > 1 and cut[-1][1] - cut[-1][0] < L:
            cut[-2:] = [(cut[-2][0], end)]
        out += cut
    return out


def ref_block_rule(c, depth, mode, L=None, lam=LAMBDA):
    from scipy.stats import chi2
    n = len(c)
    L = L or int(np.floor(np.log(n) + 0.5))
    sigma = np.median(np.abs(c)) / 0.6745
    out = c.copy()
    for b, e in ref_blocks(n, depth, L, mode):
        m = e - b
        limit = (chi2.isf(chi2.sf(lam * L, L), m) if mode == "scaled" and m < L else lam * m) * sigma ** 2
        if np.sum(c[b:e] ** 2) <= limit:
            out[b:e] = 0.0
    return out


# ------------------------------------------------------------ the option
def test_default_and_names():
    t = WT(1024)
    assert t.GetBlockRemainder() == WT.legacy
    for name, value in zip(MODES, (WT.legacy, WT.merge, WT.scaled)):
        t.SetBlockRemainder(name)
        assert t.GetBlockRemainder() == value
        t.SetBlockRemainder(WT.legacy)
        t.SetBlockRemainder(value)
        assert t.GetBlockRemainder() == value
    with pytest.raises(ValueError):
        t.SetBlockRemainder("merged")


def test_classifier_forwards_and_copies():
    c = tsa.WDF2Classify(1024, 0, 5.0, 1.0, 1024)
    assert c.GetBlockRemainder() == WT.legacy
    c.SetBlockRemainder("merge")
    assert c.GetBlockRemainder() == WT.merge
    assert tsa.WDF2Classify(c).GetBlockRemainder() == WT.merge
    d = tsa.WDF2Classify(1024, 0, 5.0, 1.0, 1024)
    d.assign(c)
    assert d.GetBlockRemainder() == WT.merge
    c.SetBlockRemainder(WT.scaled)
    assert c.GetBlockRemainder() == WT.scaled
    with pytest.raises(ValueError):
        c.SetBlockRemainder("none")


def test_scaled_formula():
    from scipy.stats import chi2
    for n_win, L, lam in ((1024, 7, LAMBDA), (512, 6, LAMBDA), (2048, 8, LAMBDA), (1024, 5, 2.5), (1024, 9, 3.0)):
        t = WT(n_win)
        t.SetBlock(0 if L == round(np.log(n_win)) else L, lam)
        assert t.GetBlockLength() == L
        for mode in ("legacy", "merge"):
            t.SetBlockRemainder(mode)
            assert [t.GetBlockEnergyThreshold(n) for n in range(1, 2 * L)] == [lam * n for n in range(1, 2 * L)]
        t.SetBlockRemainder("scaled")
        p = chi2.sf(lam * L, L)
        for n in range(1, L):
            assert t.GetBlockEnergyThreshold(n) == pytest.approx(chi2.isf(p, n), rel=1e-9)
        for n in range(L, 2 * L):
            assert t.GetBlockEnergyThreshold(n) == lam * n
    # the production numbers: L 7, lambda 4.505, p = 4.95e-5; a single coefficient needs |c| > 4.06 sigma
    t = WT(1024)
    t.SetBlockRemainder("scaled")
    assert chi2.sf(LAMBDA * 7, 7) == pytest.approx(4.952e-5, rel=1e-3)
    assert np.sqrt(t.GetBlockEnergyThreshold(1)) == pytest.approx(4.058, abs=1e-3)


# ------------------------------------------------------------ partition
LAYOUTS = [  # (N, depth): pyramid, packet levels, LocalCos rows (LocalCos M is depth log2 M)
    (1024, 0), (1024, 5), (1024, 6), (1024, 7), (512, 0), (512, 6), (2048, 0), (2048, 8)]


@pytest.mark.parametrize("n, depth", LAYOUTS)
@pytest.mark.parametrize("mode", MODES)
def test_partition(n, depth, mode):
    """|c| = 1 everywhere (sigma = 1 / 0.6745, every plain block zeroed) with a spike
    in some blocks: exactly the blocks holding a spike survive, whole."""
    L = int(np.floor(np.log(n) + 0.5))
    blocks = ref_blocks(n, depth, L, mode)
    rng = np.random.default_rng(n + depth)
    signs = rng.choice([-1.0, 1.0], size=n)
    for parity, where in ((0, "first"), (1, "last"), (0, "random")):
        c = signs.copy()
        expect = np.zeros(n, bool)
        for k, (b, e) in enumerate(blocks):
            if k % 2 == parity:
                j = b if where == "first" else (e - 1 if where == "last" else rng.integers(b, e))
                c[j] = 50.0
                expect[b:e] = True
        out, sigma = threshold(c, depth, mode)
        assert sigma == pytest.approx(1 / 0.6745)
        assert np.array_equal(out != 0, expect)
        assert np.array_equal(out[expect], c[expect])


def test_partition_lengths():
    # the remainders the review named: rows of 8 = 7 + 1 (LocalCos128 at 1024), 16 = 7 + 7 + 2, 32 = 4 x 7 + 4
    def lengths(depth, mode, n=1024):
        return sorted({e - b for b, e in ref_blocks(n, depth, 7, mode)})
    assert lengths(7, "legacy") == [1, 7] and lengths(7, "merge") == [8]
    assert lengths(6, "legacy") == [2, 7] and lengths(6, "merge") == [7, 9]
    assert lengths(5, "legacy") == [4, 7] and lengths(5, "merge") == [7, 11]
    # pyramid: runs of 1, 1, 2, 4 stay short blocks under merge; 8 = 7 + 1 becomes 8
    assert [e - b for b, e in ref_blocks(1024, 0, 7, "merge")[:5]] == [1, 1, 2, 4, 8]
    assert lengths(0, "legacy") == [1, 2, 4, 7] and lengths(0, "merge") == [1, 2, 4, 7, 8, 9, 11]


@pytest.mark.parametrize("mode", MODES)
def test_noise_matches_reference(mode):
    pytest.importorskip("scipy")
    rng = np.random.default_rng(5)
    for n, depth in LAYOUTS:
        for _ in range(3):
            c = rng.normal(size=n) * np.where(rng.random(n) < 0.05, 4.0, 1.0)
            out, _ = threshold(c, depth, mode)
            assert np.array_equal(out, ref_block_rule(c, depth, mode))


# ------------------------------------------------------------ noise
def survival(depth, mode, windows, n=1024, length=0, lam=LAMBDA, seed=0):
    """Per block length, the fraction of blocks kept on white Gaussian coefficients
    (the transforms are orthonormal, so noise coefficients are iid N(0, sigma^2))."""
    L = length or int(np.floor(np.log(n) + 0.5))
    blocks = ref_blocks(n, depth, L, mode)
    kept, count = {}, {}
    rng = np.random.default_rng(seed)
    for _ in range(windows):
        out, _ = threshold(rng.normal(size=n), depth, mode, length, lam)
        for b, e in blocks:
            m = e - b
            count[m] = count.get(m, 0) + 1
            kept[m] = kept.get(m, 0) + int(out[b] != 0)
    return {m: kept[m] / count[m] for m in count}, count


def test_single_coefficient_survival():
    # LocalCos128 at N 1024: 128 rows of 7 + 1. legacy keeps the lone coefficient at
    # |c| > sqrt(4.505) sigma, P(chi2_1 > 4.505) = 3.4 %; merge has no lone coefficient
    # left, every row is one block of 8; scaled keeps it at the full block's 5e-5.
    from scipy.stats import chi2
    legacy, count = survival(7, "legacy", 200)
    assert count[1] == 128 * 200
    assert legacy[1] == pytest.approx(chi2.sf(LAMBDA, 1), rel=0.15)
    merged, count = survival(7, "merge", 200)
    assert set(count) == {8}
    assert merged[8] < 1e-3
    scaled, _ = survival(7, "scaled", 200)
    assert scaled[1] < 1e-3


def test_scaled_false_alarm_matches_full_block():
    """Each short block length's false-alarm probability in noise against the full
    block's, within 10 %. lambda is lowered so the rate is measurable on a few
    hundred windows. At lambda 4.505 (p 5e-5) the match is exact for a known sigma;
    with sigma from the window's MAD the full block's steeper tail is inflated more
    (7.1e-5 full against 5.4e-5 single on 3.84 M blocks each)."""
    from scipy.stats import chi2
    cases = [  # (depth, L, lambda): rows of 2^(10 - depth) cut into L leave the short lengths
        (7, 7, 2.5), (6, 7, 2.5), (5, 7, 2.5),   # rows 8, 16, 32: short 1, 2, 4
        (7, 5, 2.5),                              # rows 8 = 5 + 3
        (6, 9, 2.0), (5, 9, 2.0),                 # rows 16 = 9 + 7, 32 = 3 x 9 + 5
    ]
    for depth, L, lam in cases:
        rate, count = survival(depth, "scaled", 600, length=L, lam=lam, seed=depth * 10 + L)
        full = rate[L]
        for m, r in rate.items():
            if m < L:
                assert r == pytest.approx(full, rel=0.10), (depth, L, lam, m, r, full, count)
        # legacy: each length at its own P(chi2_m > lambda m), above the full block's
        legacy, _ = survival(depth, "legacy", 300, length=L, lam=lam, seed=depth * 10 + L)
        for m, r in legacy.items():
            assert r == pytest.approx(chi2.sf(lam * m, m), rel=0.15)
            if m < L:
                assert r > 1.3 * full


def firing_rate(bases, mode, windows, seed=11, n=1024, thresh=5.0):
    c = tsa.WDF2Classify(n, 0, thresh, 1.0, n)
    c.SetBases(bases)
    if mode is not None:
        c.SetBlockRemainder(mode)
    ev = tsa.EventFullFeatured(n)
    rng = np.random.default_rng(seed)
    fired = total = 0
    for _ in range(0, windows, 128):
        c << view_of(rng.normal(size=128 * n))
        while c.GetDataNeeded() >= 0:
            fired += c(ev)
            total += 1
    return fired / total


def test_noise_firing_rate():
    # Per-window firing rate at threshold 5, N 1024, white noise. With legacy the
    # 128 lone coefficients of each LocalCos128 window lift its rate ~10x over D0;
    # merge brings it back to D0's. On 50 176 windows: D0 0.061 / 0.054 / 0.056,
    # D0 + LocalCos128 0.557 / 0.057 / 0.065 (legacy / merge / scaled).
    w = 1024
    d0 = {m: firing_rate(D0, m, w) for m in MODES}
    lc = {m: firing_rate(D0 + ",LocalCos128", m, w) for m in MODES}
    assert lc["legacy"] > 0.35
    assert lc["merge"] < 0.12 and lc["scaled"] < 0.12
    assert d0["merge"] <= d0["legacy"] and d0["scaled"] <= d0["legacy"]
    assert lc["merge"] < 1.6 * d0["merge"] + 0.02


# ------------------------------------------------------------ legacy, bit for bit
SOURCES = {  # name: (file or None for white noise, first sample)
    "white": (None, 0),
    "GW150914_H1": ("GW150914_H1_full_fullrun.npz", 1_000_000),
    "GW170817_L1": ("GW170817_L1_full_fullrun.npz", 3_000_000),
    "GW240413_022019_V1": ("GW240413_022019_V1_full_fullrun.npz", 2_000_000),
}
CONFIGS = {  # name: (bases, rule, minimum frequency)
    "D0 block": (D0, WT.block, 0.0),
    "D0+LocalCos128 block": (D0 + ",LocalCos128", WT.block, 0.0),
    "D0+LocalCos128 block 16 Hz": (D0 + ",LocalCos128", WT.block, 16.0),
    "D0+Sym8P6 block": (D0 + ",Sym8P6", WT.block, 0.0),
    "D0 universal": (D0, WT.dohonojohnston, 0.0),
}
WINDOWS = 48


def source(name):
    path, first = SOURCES[name]
    if path is None:
        return np.random.default_rng(2026).normal(size=WINDOWS * 1024)
    for d in STREAMS:
        if os.path.exists(os.path.join(d, path)):
            return np.load(os.path.join(d, path))["w"][first:first + WINDOWS * 1024].astype(float)
    return None


def trigger_digest(x, config, mode=None, n=1024):
    """sha256 over every window's winner, EnWDF, sigma and coefficients."""
    bases, rule, fmin = CONFIGS[config]
    c = tsa.WDF2Classify(n, 0, -1.0, 1.0, n, rule)
    c.SetBases(bases)
    if fmin > 0:
        c.SetMinFrequency(fmin, FS)
    if mode is not None:
        c.SetBlockRemainder(mode)
    c << view_of(x)
    h = hashlib.sha256()
    ev = tsa.EventFullFeatured(n)
    while c.GetDataNeeded() >= 0:
        assert c(ev) == 1
        h.update(ev.mWave.encode())
        h.update(np.array([ev.mSNR, ev.mSigma]).tobytes())
        h.update(np.array([ev.GetCoeff(i) for i in range(n)]).tobytes())
    return h.hexdigest()


def write_fixture():
    """Record the reference digests; run once with the module before the remainder option."""
    out = {}
    for s in SOURCES:
        x = source(s)
        if x is not None:
            out[s] = {cfg: trigger_digest(x, cfg) for cfg in CONFIGS}
    with open(FIXTURE, "w") as f:
        json.dump(out, f, indent=1, sort_keys=True)


@pytest.mark.parametrize("name", SOURCES)
@pytest.mark.parametrize("config", CONFIGS)
def test_legacy_is_unchanged_bit_for_bit(name, config):
    with open(FIXTURE) as f:
        reference = json.load(f)
    if name not in reference:
        pytest.skip("no reference recorded for " + name)
    x = source(name)
    if x is None:
        pytest.skip("whitened streams not found")
    assert trigger_digest(x, config) == reference[name][config]
    assert trigger_digest(x, config, "legacy") == reference[name][config]
    if CONFIGS[config][1] != WT.block:  # other rules ignore the option
        for mode in ("merge", "scaled"):
            assert trigger_digest(x, config, mode) == reference[name][config]
