"""Local cosine bases (Coifman-Meyer), cosine packets (Coifman-Wickerhauser
best basis) and the fixed-segment local cosine as a competition candidate."""
import itertools
import os
import sys

import numpy as np
import pytest

from py4tsa import tsa

W = tsa.WaveletTransform
LCT = tsa.LocalCosineTransform
CP = tsa.CosinePackets
FS = 2048.0
TOL = 1e-12
EDGES = {"periodic": LCT.periodic, "free": LCT.free}
CATALOGUE = os.environ.get("WDF_CATALOGUE_SCRIPTS", "/home/elena/workspace/wdf-catalogue/scripts")


# ------------------------------------------------- numpy reference
# The catalogue's local cosine (wdf-catalogue scripts/bases_windows.py, bell and
# local_cosine), copied, with the `free` edge added: no fold at 0 and N.
def ref_bell(m, overlap, kind="cm"):
    t = (np.arange(-overlap, overlap) + 0.5) / overlap
    theta = t
    if kind != "sine":
        for _ in range(3):
            theta = np.sin(np.pi / 2 * theta)
    return np.sin(np.pi / 4 * (1 + theta))


def ref_dct4(y):
    """Orthonormal DCT-IV along the last axis, by its matrix."""
    m = y.shape[-1]
    k = np.arange(m)
    C = np.sqrt(2.0 / m) * np.cos(np.pi / m * np.outer(k + 0.5, k + 0.5))
    return y @ C.T


def ref_fold(X, a, overlap, r):
    n = X.shape[-1]
    rp, rm = r[overlap:], r[:overlap][::-1]
    right = (a + np.arange(overlap)) % n
    left = (a - 1 - np.arange(overlap)) % n
    xr, xl = X[..., right].copy(), X[..., left].copy()
    X[..., right] = rp * xr + rm * xl
    X[..., left] = rp * xl - rm * xr


def ref_local_cosine(x, m, overlap=None, kind="cm", edge="periodic", segments=False):
    """Frequency-major (bin k of segment j at k N/m + j), or segment-major."""
    x = np.asarray(x, float)
    n = x.size
    overlap = m // 2 if overlap is None else overlap
    y = x.copy()
    if overlap > 0:
        r = ref_bell(m, overlap, kind)
        for a in range(0, n, m):
            if a == 0 and edge == "free":
                continue
            ref_fold(y, a, overlap, r)
    c = ref_dct4(y.reshape(n // m, m))           # (segments, bins)
    return c.ravel() if segments else c.T.ravel()


def ref_segmentation(x, lengths, overlap, edge="periodic"):
    """Coefficients of a segmentation, segment by segment."""
    y = np.asarray(x, float).copy()
    n = y.size
    starts = np.r_[0, np.cumsum(lengths)[:-1]]
    if overlap > 0:
        r = ref_bell(0, overlap)
        for a in starts:
            if not (a == 0 and edge == "free"):
                ref_fold(y, a, overlap, r)
    return np.concatenate([ref_dct4(y[a:a + m]) for a, m in zip(starts, lengths)])


def view_of(x):
    v = tsa.SeqView_double_t(0.0, 1.0 / FS, len(x))
    for i, value in enumerate(np.asarray(x, dtype=float).tolist()):
        v.FillPoint(0, i, value)
    return v


def values(v, n):
    return np.array([v.GetY(0, i) for i in range(n)])


def wt_forward(x, mother, depth=0):
    v = view_of(x)
    (W(len(x), getattr(W, mother), depth) if depth else W(len(x), getattr(W, mother))).Forward(v)
    return values(v, len(x))


def wt_inverse(c, mother, depth):
    v = view_of(c)
    W(len(c), getattr(W, mother), depth).Inverse(v)
    return values(v, len(c))


# ------------------------------------------------- the local cosine transform
SIZES = [(n, m) for n in (512, 1024, 2048) for m in (32, 64, 128, 256, 512)]


@pytest.mark.parametrize("edge", EDGES)
@pytest.mark.parametrize("n, m", [(512, m) for m in (32, 64, 128, 256, 512)])
def test_matrix_is_orthonormal(n, m, edge):
    t = LCT(n, m, -1, EDGES[edge])
    A = np.array([t.Forward(e) for e in np.eye(n)]).T
    assert np.max(np.abs(A.T @ A - np.eye(n))) < TOL


@pytest.mark.parametrize("edge", EDGES)
@pytest.mark.parametrize("n, m", SIZES)
def test_perfect_reconstruction_and_inner_products(n, m, edge):
    rng = np.random.default_rng(n + m)
    x, y = rng.normal(size=(2, n))
    t = LCT(n, m, -1, EDGES[edge])
    cx, cy = t.Forward(x), t.Forward(y)
    assert np.max(np.abs(t.Inverse(cx) - x)) < TOL
    assert abs(cx @ cx / (x @ x) - 1.0) < TOL
    assert abs(cx @ cy - x @ y) / np.sqrt((x @ x) * (y @ y)) < TOL
    s = t.ForwardSegments(x)
    assert np.max(np.abs(t.InverseSegments(s) - x)) < TOL
    assert np.array_equal(s.reshape(n // m, m).T.ravel(), cx)


@pytest.mark.parametrize("edge", EDGES)
@pytest.mark.parametrize("n, m", SIZES)
def test_matches_the_numpy_reference(n, m, edge):
    x = np.random.default_rng(7 * n + m).normal(size=n)
    for overlap in (None, m // 4, 1, 0):
        c = LCT(n, m, -1 if overlap is None else overlap, EDGES[edge]).Forward(x)
        assert np.max(np.abs(c - ref_local_cosine(x, m, overlap, edge=edge))) < TOL
    c = LCT(n, m, -1, EDGES[edge], LCT.sine).Forward(x)
    assert np.max(np.abs(c - ref_local_cosine(x, m, kind="sine", edge=edge))) < TOL


def test_matches_the_catalogue_itself():
    # bases_windows.local_cosine of the catalogue, when it is on this machine.
    if not os.path.isfile(os.path.join(CATALOGUE, "bases_windows.py")):
        pytest.skip("wdf-catalogue scripts not found")
    sys.path.insert(0, CATALOGUE)
    try:
        bw = pytest.importorskip("bases_windows")
    finally:
        sys.path.remove(CATALOGUE)
    for n, m in SIZES:
        x = np.random.default_rng(n * m).normal(size=(3, n))
        mine = np.array([LCT(n, m).Forward(row) for row in x])
        assert np.max(np.abs(mine - bw.local_cosine(x, m))) < TOL
        for kind, bell in (("cm", LCT.coifmanMeyer), ("sine", LCT.sine)):
            assert np.max(np.abs(LCT.Ramp(m // 2, bell) - bw.bell(m, m // 2, kind))) < 1e-15


def test_bell_is_a_partition_of_energy():
    for bell in (LCT.coifmanMeyer, LCT.sine):
        r = LCT.Ramp(16, bell)
        assert np.max(np.abs(r ** 2 + r[::-1] ** 2 - 1.0)) < 1e-15
        assert np.all(np.diff(r) > 0)


def test_basis_functions_are_localised():
    # A coefficient of segment j lives on [jM - eps, (j+1)M + eps).
    n, m = 1024, 128
    t = LCT(n, m)
    for k, j in ((5, 3), (100, 0), (0, 7)):
        c = np.zeros(n)
        c[k * (n // m) + j] = 1.0
        w = t.Inverse(c)
        support = np.flatnonzero(np.abs(w) > 1e-14)
        inside = (np.arange(n) - (j * m - m // 2)) % n < m + m
        assert np.all(inside[support])


@pytest.mark.parametrize("args", [(1000, 128), (1024, 96), (1024, 2048), (1024, 128, 65), (64, 0)])
def test_invalid_arguments(args):
    with pytest.raises(ValueError):
        LCT(*args)


# ------------------------------------------------- inside WaveletTransform
@pytest.mark.parametrize("n, depth", [(512, 5), (1024, 7), (2048, 8), (1024, 10)])
def test_wavelet_transform_mode(n, depth):
    x = np.random.default_rng(depth).normal(size=n)
    w = W(n, W.LocalCos, depth)
    assert w.IsLocalCosine() and w.GetCosineSegment() == 2 ** depth
    assert w.GetPacketDepth() == depth and w.GetLength() == n
    c = wt_forward(x, "LocalCos", depth)
    assert np.max(np.abs(c - ref_local_cosine(x, 2 ** depth))) < TOL
    assert np.max(np.abs(wt_inverse(c, "LocalCos", depth) - x)) < TOL
    unit = np.zeros(n)
    unit[22] = 1.0
    assert np.array_equal(np.array(w.WaveletWaveform()), wt_inverse(unit, "LocalCos", depth))
    assert not W(n, W.Coif1, 3).IsLocalCosine() and W(n, W.Coif1, 3).GetCosineSegment() == 0


def test_wavelet_transform_mode_rejects():
    with pytest.raises(ValueError):
        W(1024, W.LocalCos)
    with pytest.raises(ValueError):
        W(1024, W.LocalCos, 0)
    with pytest.raises(ValueError):
        W(1024, W.LocalCos, 11)


def test_wavelet_transform_mode_copies_and_resizes():
    n = 1024
    x = np.random.default_rng(9).normal(size=n)
    original = W(n, W.LocalCos, 6)
    copy = W(original)
    assigned = W(64, W.Haar)
    assigned.assign(original)
    del original
    for t in (copy, assigned):
        assert t.IsLocalCosine() and t.GetPacketDepth() == 6
        v = view_of(x)
        t.Forward(v)
        assert np.array_equal(values(v, n), wt_forward(x, "LocalCos", 6))
    # A window of another length: the basis follows it.
    t = W(n, W.LocalCos, 6)
    y = x[:512]
    v = view_of(y)
    t.Forward(v)
    assert t.GetLength() == 512
    assert np.max(np.abs(values(v, 512) - ref_local_cosine(y, 64))) < TOL


# ------------------------------------------------- cosine packets
def all_segmentations(n, lo, hi):
    """Every segmentation of [0, n) built from dyadic nodes of length lo..hi."""
    def node(m):
        out = [[m]]
        if m > lo:
            out += [a + b for a in node(m // 2) for b in node(m // 2)]
        return out
    parts = [node(hi)] * (n // hi)
    return [sum(p, []) for p in itertools.product(*parts)]


COSTS = {"l1": CP.l1, "entropy": CP.entropy, "wdfUniversal": CP.wdfUniversal, "wdfBlock": CP.wdfBlock}


@pytest.mark.parametrize("edge", EDGES)
@pytest.mark.parametrize("cost", COSTS)
def test_best_basis_reconstructs(cost, edge):
    rng = np.random.default_rng(11)
    n = 1024
    t = np.arange(n) / FS
    for x in (rng.normal(size=n),
              rng.normal(size=n) + 3 * np.sin(2 * np.pi * 150 * t) * (np.abs(t - 0.25) < 0.1),
              rng.normal(size=n) + 2 * np.sin(2 * np.pi * (50 + 300 * t) * t)):
        cp = CP(n, 32, 0, -1, EDGES[edge])
        cp.BestBasis(x, COSTS[cost], 0.0)
        seg, c = cp.GetSegmentation(), cp.GetCoefficients()
        assert sum(seg) == n
        assert np.max(np.abs(cp.Inverse(c, seg) - x)) < TOL
        assert abs(c @ c / (x @ x) - 1.0) < TOL
        assert np.max(np.abs(cp.Analyse(x, seg) - c)) < TOL
        assert np.max(np.abs(c - ref_segmentation(x, seg, 16, edge))) < TOL


@pytest.mark.parametrize("edge", EDGES)
def test_every_segmentation_is_orthonormal(edge):
    n = 256
    cp = CP(n, 32, 0, 16, EDGES[edge])
    rng = np.random.default_rng(12)
    for seg in all_segmentations(n, 32, n)[::3]:
        A = np.array([cp.Analyse(e, seg) for e in np.eye(n)]).T
        assert np.max(np.abs(A.T @ A - np.eye(n))) < TOL
        x = rng.normal(size=n)
        assert np.max(np.abs(cp.Inverse(cp.Analyse(x, seg), seg) - x)) < TOL


def test_uniform_segmentation_is_the_local_cosine():
    n = 1024
    x = np.random.default_rng(13).normal(size=n)
    cp = CP(n, 64, 0, 32)
    for m in (64, 128, 1024):
        assert np.array_equal(cp.Analyse(x, [m] * (n // m)), LCT(n, m, 32).ForwardSegments(x))


@pytest.mark.parametrize("cost", COSTS)
def test_best_basis_is_the_minimum_and_monotone(cost):
    # The tree of N 256, segments 256..32, has 26 segmentations: the search
    # must return the cheapest, and each node's best is the smaller of its
    # own cost and its children's best, so it never exceeds either.
    n, lo = 256, 32
    rng = np.random.default_rng(14)
    t = np.arange(n) / FS
    for trial in range(5):
        x = rng.normal(size=n)
        x[40 * trial:40 * trial + 60] += 4 * np.sin(2 * np.pi * (100 + 150 * trial) * t[:60])
        cp = CP(n, lo)
        best = cp.BestBasis(x, COSTS[cost], 1.0 if cost.startswith("wdf") else 0.0)
        segs = all_segmentations(n, lo, n)
        assert len(segs) == 26
        costs = [cp.SegmentationCost(s) for s in segs]
        assert best == pytest.approx(min(costs), abs=1e-12)
        assert cp.SegmentationCost(cp.GetSegmentation()) == pytest.approx(best, abs=1e-12)
        for level in range(cp.GetLevels()):
            m = cp.GetSegmentLength(level)
            for i in range(n // m):
                b = cp.GetBestCost(level, i)
                assert b <= cp.GetNodeCost(level, i)
                if level + 1 < cp.GetLevels():
                    kids = cp.GetBestCost(level + 1, 2 * i) + cp.GetBestCost(level + 1, 2 * i + 1)
                    assert b <= kids
                    assert b == min(cp.GetNodeCost(level, i), kids)
        # direct check of a node cost against its definition
        c = ref_segmentation(x, [n // 2] * 2, lo // 2)[: n // 2]
        p = c ** 2 / (x @ x)
        own = {"l1": np.abs(c).sum(), "entropy": -np.sum(p[p > 0] * np.log(p[p > 0]))}
        if cost in own:
            assert cp.GetNodeCost(1, 0) == pytest.approx(own[cost], rel=1e-12)


@pytest.mark.parametrize("cost", ["l1", "entropy"])
def test_best_basis_follows_the_signal(cost):
    n = 1024
    t = np.arange(n) / FS
    rng = np.random.default_rng(15)
    # A DCT-IV basis function of the whole window, without bells at its
    # edges: one coefficient in the single segment, so no split.
    free = CP(n, 32, 0, -1, LCT.free)
    tone = np.cos(np.pi / n * (np.arange(n) + 0.5) * (200 + 0.5)) + 1e-3 * rng.normal(size=n)
    free.BestBasis(tone, COSTS[cost])
    assert free.GetSegmentation() == [n]
    cp = CP(n, 32)
    # An arbitrary long sinusoid: long segments only.
    tone = np.sin(2 * np.pi * 173.3 * t + 0.4) + 1e-3 * rng.normal(size=n)
    cp.BestBasis(tone, COSTS[cost])
    assert min(cp.GetSegmentation()) >= 256
    # A click: the shortest segments around it, long ones far from it
    # (where there is nothing, a tie keeps the longer segment).
    click = np.zeros(n)
    click[600] += 5.0
    click[601] -= 3.0
    cp.BestBasis(click, COSTS[cost])
    seg = cp.GetSegmentation()
    starts = np.r_[0, np.cumsum(seg)[:-1]]
    home = int(np.flatnonzero(starts <= 600)[-1])
    assert seg[home] == 32
    assert max(seg) >= 256


def test_wdf_cost_sigma():
    n = 1024
    x = np.random.default_rng(16).normal(size=n)
    cp = CP(n, 64, 1024, 32)
    cp.BestBasis(x, CP.wdfUniversal, 0.0)
    finest = LCT(n, 64, 32).ForwardSegments(x)
    assert cp.GetSigma() == pytest.approx(np.median(np.abs(finest)) / 0.6745, rel=1e-14)
    cp.BestBasis(x, CP.wdfBlock, 2.5)
    assert cp.GetSigma() == 2.5 and cp.GetBlockLength() == 7
    cp.BestBasis(x, CP.l1)
    assert cp.GetSigma() == 0.0


def ref_cospkt_best(x, n, rule, levels=(64, 128, 256, 512, 1024), eps=32):
    """The catalogue's cospkt_best (scripts/single_chirp_optimal.py), sigma
    'mad', kappa 1, one window: WDF's kept energy as the gain, sigma from the
    finest level, split when the children gain strictly more."""
    coef = {m: ref_local_cosine(x, m, eps, segments=True).reshape(n // m, m) for m in levels}
    sigma = np.median(np.abs(coef[levels[0]])) / 0.6745
    L, lam = int(np.floor(np.log(n) + 0.5)), 4.505

    def gain(A):
        if rule == "univ":
            return np.where(A > np.sqrt(2 * np.log(n)), A * A, 0.0).sum(-1)
        first = np.arange(0, A.shape[-1], L)
        s = np.add.reduceat(A * A, first, axis=-1)
        return np.where(s > lam * np.diff(np.r_[first, A.shape[-1]]), s, 0.0).sum(-1)

    cost = {m: gain(np.abs(coef[m]) / sigma) for m in levels}
    best, split = {levels[0]: cost[levels[0]]}, {}
    for lo, m in zip(levels[:-1], levels[1:]):
        children = best[lo][0::2] + best[lo][1::2]
        split[m] = children > cost[m]
        best[m] = np.where(split[m], children, cost[m])
    out = []

    def walk(m, i):
        if m == levels[0] or not split[m][i]:
            out.append(m)
        else:
            walk(m // 2, 2 * i)
            walk(m // 2, 2 * i + 1)
    for i in range(n // levels[-1]):
        walk(levels[-1], i)
    starts = np.r_[0, np.cumsum(out)[:-1]]
    return out, np.concatenate([coef[m][a // m] for a, m in zip(starts, out)]), sigma


@pytest.mark.parametrize("rule, cost", [("univ", CP.wdfUniversal), ("block", CP.wdfBlock)])
def test_wdf_best_basis_matches_the_catalogue(rule, cost):
    n = 1024
    t = np.arange(n) / FS
    rng = np.random.default_rng(17)
    for q in range(6):
        x = rng.normal(size=n)
        x[120 * q:120 * q + 300] += 3 * np.sin(2 * np.pi * (60 + 70 * q) * t[:300] * (1 + 2 * t[:300]))
        seg, c, sigma = ref_cospkt_best(x, n, rule)
        cp = CP(n, 64, 1024, 32)
        cp.BestBasis(x, cost, 0.0)
        assert cp.GetSegmentation() == seg
        assert np.max(np.abs(cp.GetCoefficients() - c)) < TOL
        assert cp.GetSigma() == pytest.approx(sigma, rel=1e-13)


@pytest.mark.parametrize("args", [(1000, 32), (1024, 48), (1024, 64, 32), (1024, 32, 2048),
                                  (1024, 32, 0, 17)])
def test_cosine_packets_reject(args):
    with pytest.raises(ValueError):
        CP(*args)


def test_cosine_packets_reject_bad_segmentations():
    cp = CP(256, 32)
    x = np.zeros(256)
    for seg in ([128, 64], [32, 128, 32, 64], [16] * 16, [64, 64, 64]):
        with pytest.raises(ValueError):
            cp.Analyse(x, seg)


# ------------------------------------------------- in the competition
DEFAULT_BASES = "Haar,DaubC4,DaubC8,Sym4,DaubC16,Sym8,Coif3,DaubC24,Sym12,Coif5"
PYWT = {"Haar": ("haar", 0), "DaubC4": ("db2", 1), "DaubC8": ("db4", 1), "Sym4": ("sym4", 1),
        "DaubC16": ("db8", 1), "Sym8": ("sym8", 1), "Coif3": ("coif3", 1), "DaubC24": ("db12", 1),
        "Sym12": ("sym12", 1), "Coif5": ("coif5", 1)}


def ref_coefficients(x, name):
    """The candidate's coefficients in numpy: PyWavelets' periodized pyramid
    after GSL's circular shift (none for Haar, one sample for the centred
    mothers), or the local cosine."""
    if name.startswith("LocalCos"):
        return ref_local_cosine(x, int(name[8:])), int(np.log2(int(name[8:])))
    pywt = pytest.importorskip("pywt")
    wavelet, shift = PYWT[name]
    a, details = np.asarray(x, float), []
    while a.size >= 2:
        a, d = pywt.dwt(np.roll(a, shift), wavelet, mode="periodization")
        details.insert(0, d)
    return np.concatenate([a] + details), 0


def ref_rule(c, depth, rule):
    """(EnWDF, kept, sigma) of WaveletThreshold in numpy."""
    n = len(c)
    sigma = np.median(np.abs(c)) / 0.6745
    if rule == "universal":
        kept = np.where(np.abs(c) > np.sqrt(2 * np.log(n)) * sigma, c, 0.0)
    else:
        L, lam = int(np.floor(np.log(n) + 0.5)), 4.505
        edges = ([0, 1] + [2 ** k for k in range(1, int(np.log2(n)) + 1)] if depth == 0
                 else list(range(0, n + 1, n >> depth)))
        kept = c.copy()
        for start, end in zip(edges[:-1], edges[1:]):
            for b in range(start, end, L):
                e = min(b + L, end)
                if np.sum(c[b:e] ** 2) <= lam * sigma ** 2 * (e - b):
                    kept[b:e] = 0.0
    return np.sqrt(np.sum(kept ** 2)) / sigma, kept, sigma


RULES = {"universal": tsa.WaveletThreshold.dohonojohnston, "block": tsa.WaveletThreshold.block}


@pytest.mark.parametrize("rule", RULES)
def test_competition_with_local_cosine(rule):
    n = 1024
    bases = (DEFAULT_BASES + ",LocalCos128").split(",")
    t = np.arange(n) / FS
    rng = np.random.default_rng(18)
    signals = [
        1.0 * np.sin(2 * np.pi * 300.0 * t),                                  # a long tone
        0.8 * np.sin(2 * np.pi * 120.0 * t + 1.0) + 0.6 * np.sin(2 * np.pi * 410.0 * t),
        1.2 * np.sin(2 * np.pi * (40 + 150 * t) * t),                          # a chirp
        np.where(np.abs(t - 0.25) < 0.002, 12.0, 0.0),                         # a click
    ]
    winners = []
    for s in signals:
        x = rng.normal(size=n) + s
        c = tsa.WDF2Classify(n, 0, -1.0, 1.0, n, RULES[rule])
        c.SetBases(",".join(bases))
        assert c.GetBases() == ",".join(bases)
        c(view_of(x), 1.0)
        event = tsa.EventFullFeatured(n)
        assert c(event) == 1
        scores = {}
        for name in bases:
            coef, depth = ref_coefficients(x, name)
            scores[name] = ref_rule(coef, depth, rule)
        best = max(bases, key=lambda b: (scores[b][0], bases.index(b)))   # a tie goes to the later
        assert event.mWave == best
        assert event.mSNR == pytest.approx(scores[best][0], rel=1e-12)
        assert event.mSigma == pytest.approx(scores[best][2], rel=1e-12)
        coefficients = np.array([event.GetCoeff(i) for i in range(n)])
        assert np.max(np.abs(coefficients - scores[best][1])) < TOL
        winners.append(best)
    assert "LocalCos128" in winners and any(w != "LocalCos128" for w in winners)


def test_local_cosine_is_not_a_default():
    assert tsa.WDF2Classify(1024, 0, -1.0, 1.0, 1024).GetBases() == DEFAULT_BASES


@pytest.mark.parametrize("n, names", [(1024, "Haar,LocalCos"), (1024, "LocalCos0"), (1024, "LocalCos100"),
                                      (1024, "LocalCos2048"), (1024, "LocalCos128P3"), (1024, "LocalCos064"),
                                      (1024, "LocalCos1"), (1024, "LocalCos128,LocalCos128"),
                                      (1024, "Localcos128")])
def test_set_bases_rejects_local_cosine(n, names):
    with pytest.raises(ValueError):
        tsa.WDF2Classify(n, 0, -1.0, 1.0, n, tsa.WaveletThreshold.dohonojohnston).SetBases(names)


@pytest.mark.parametrize("n, largest", [(512, 64), (1024, 128), (2048, 256)])
def test_block_rule_caps_the_segment(n, largest):
    # Each row of LocalCos M holds N / M coefficients, at least one block of
    # L = round(ln N): M <= N / L.
    c = tsa.WDF2Classify(n, 0, -1.0, 1.0, n, tsa.WaveletThreshold.block)
    c.SetBases(",".join("LocalCos%d" % m for m in (2, 32, largest)))
    with pytest.raises(ValueError):
        c.SetBases("Haar,LocalCos%d" % (2 * largest))
    u = tsa.WDF2Classify(n, 0, -1.0, 1.0, n, tsa.WaveletThreshold.dohonojohnston)
    u.SetBases("Haar,LocalCos%d" % (4 * largest))
    assert tsa.WDF2Classify(u).GetBases() == "Haar,LocalCos%d" % (4 * largest)
