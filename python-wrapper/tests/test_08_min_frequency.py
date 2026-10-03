"""The low-frequency cut of the threshold (WaveletThreshold / WDF2Classify
SetMinFrequency): coefficients whose tile's upper edge is <= fHz are out of
sigma, out of the block rule and out of EnWDF, read on each layout."""
import numpy as np
import pytest

from py4tsa import tsa

from test_07_cosine_packets import DEFAULT_BASES, FS, TOL, ref_coefficients, view_of

W = tsa.WaveletTransform
RULES = {"universal": tsa.WaveletThreshold.dohonojohnston, "block": tsa.WaveletThreshold.block}


def ref_keep(n, depth, fs, fmin):
    """Upper edge (fs / 2) e / N of each coefficient's run, e the index past the run."""
    if depth == 0:
        edges = [0, 1] + [2 ** k for k in range(1, int(np.log2(n)) + 1)]
    else:
        edges = list(range(0, n + 1, n >> depth))
    f_hi = np.empty(n)
    for start, end in zip(edges[:-1], edges[1:]):
        f_hi[start:end] = 0.5 * fs * end / n
    return f_hi > fmin + 1e-9


def ref_rule_cut(c, depth, rule, keep):
    """(EnWDF, kept, sigma) with the dropped coefficients out, as the catalogue's port
    (wdf-catalogue scripts/band_choice.py cut_noise_scale / cut_rule_stat)."""
    n = len(c)
    sigma = np.median(np.abs(c[keep])) / 0.6745
    a = np.where(keep, c, 0.0)
    if rule == "universal":
        kept = np.where(np.abs(a) > np.sqrt(2 * np.log(keep.sum())) * sigma, a, 0.0)
    else:
        L, lam = int(np.floor(np.log(n) + 0.5)), 4.505
        edges = ([0, 1] + [2 ** k for k in range(1, int(np.log2(n)) + 1)] if depth == 0
                 else list(range(0, n + 1, n >> depth)))
        kept = a.copy()
        for start, end in zip(edges[:-1], edges[1:]):
            for b in range(start, end, L):
                e = min(b + L, end)
                if np.sum(a[b:e] ** 2) <= lam * sigma ** 2 * (e - b):
                    kept[b:e] = 0.0
    return np.sqrt(np.sum(kept ** 2)) / sigma, kept, sigma


def classify(x, bases, rule, fmin=None, fs=FS):
    n = len(x)
    c = tsa.WDF2Classify(n, 0, -1.0, 1.0, n, RULES[rule])
    if bases is not None:
        c.SetBases(bases)
    if fmin is not None:
        c.SetMinFrequency(fmin, fs)
    c(view_of(x), 1.0)
    event = tsa.EventFullFeatured(n)
    assert c(event) == 1
    return event, np.array([event.GetCoeff(i) for i in range(n)])


@pytest.mark.parametrize("n, depth, dropped", [
    (1024, 0, 16),     # pyramid: indices 0-15 (upper edges 1, 2, 4, 8, 16 Hz)
    (1024, 7, 16),     # LocalCos128 / packet depth 7: rows 0-1 of 8 Hz, 8 coefficients each
    (1024, 6, 16),     # packet depth 6: band 0 of 16 Hz
    (1024, 5, 0),      # packet depth 5: band 0 reaches 32 Hz, kept
    (512, 0, 8),       # N 512 at 2048 Hz: indices 0-7 reach 2, 4, 8, 16 Hz; [8, 16) reaches 32
    (2048, 0, 32),     # N 2048: [16, 32) reaches 16 Hz
])
def test_kept_mask_reads_the_layout(n, depth, dropped):
    t = tsa.WaveletThreshold(n)
    t.SetLayout(depth)
    assert all(t.IsKept(i) for i in range(n))            # off by default
    t.SetMinFrequency(16.0, FS)
    kept = np.array([t.IsKept(i) for i in range(n)])
    assert np.array_equal(kept, ref_keep(n, depth, FS, 16.0))
    assert int((~kept).sum()) == dropped
    assert not kept[:dropped].any() and kept[dropped:].all()


def test_local_cosine_rows_cut():
    # LocalCos128 at N 1024: rows of 8 Hz (fs / 2M), 8 segments per row; 16 Hz drops rows 0 and 1.
    t = tsa.WaveletThreshold(1024)
    t.SetLayout(W(1024, W.LocalCos, 7).GetPacketDepth())
    t.SetMinFrequency(16.0, FS)
    rows = np.array([t.IsKept(i) for i in range(1024)]).reshape(128, 8)
    assert not rows[:2].any() and rows[2:].all()


@pytest.mark.parametrize("rule", RULES)
def test_threshold_matches_the_reference(rule):
    rng = np.random.default_rng(3)
    for name in ("DaubC8", "Coif5", "LocalCos128", "Sym8P6"):
        x = rng.normal(size=1024) + 3.0 * np.sin(2 * np.pi * 6.0 * np.arange(1024) / FS)   # 6 Hz, cut
        if name.endswith("P6"):
            v = view_of(x)
            W(1024, W.Sym8, 6).Forward(v)
            coef, depth = np.array([v.GetY(0, i) for i in range(1024)]), 6
        else:
            coef, depth = ref_coefficients(x, name)
        th = tsa.WaveletThreshold(1024)
        th.SetLayout(depth)
        th.SetMinFrequency(16.0, FS)
        v = view_of(coef)
        th(v, RULES[rule])
        out = np.array([v.GetY(0, i) for i in range(1024)])
        en, kept, sigma = ref_rule_cut(coef, depth, rule, ref_keep(1024, depth, FS, 16.0))
        assert th.GetSigma() == pytest.approx(sigma, rel=1e-12)
        assert np.max(np.abs(out - kept)) < TOL
        assert th.GetCm() == pytest.approx(np.max(np.abs(np.where(ref_keep(1024, depth, FS, 16.0), coef, 0))), rel=1e-12)


@pytest.mark.parametrize("rule", RULES)
def test_competition_with_the_cut(rule):
    n = 1024
    bases = (DEFAULT_BASES + ",LocalCos128,LocalCos64").split(",")
    t = np.arange(n) / FS
    rng = np.random.default_rng(81)
    signals = [
        5.0 * np.sin(2 * np.pi * 9.0 * t),                                     # loud below the cut
        1.2 * np.sin(2 * np.pi * (40 + 150 * t) * t) + 4.0 * np.sin(2 * np.pi * 5.0 * t),
        1.0 * np.sin(2 * np.pi * 300.0 * t),
        np.where(np.abs(t - 0.25) < 0.002, 12.0, 0.0),
    ]
    for s in signals:
        x = rng.normal(size=n) + s
        event, coefficients = classify(x, ",".join(bases), rule, 16.0)
        scores = {}
        for name in bases:
            coef, depth = ref_coefficients(x, name)
            scores[name] = ref_rule_cut(coef, depth, rule, ref_keep(n, depth, FS, 16.0))
        best = max(bases, key=lambda b: (scores[b][0], bases.index(b)))
        assert event.mWave == best
        assert event.mSNR == pytest.approx(scores[best][0], rel=1e-12)
        assert event.mSigma == pytest.approx(scores[best][2], rel=1e-12)
        assert np.max(np.abs(coefficients - scores[best][1])) < TOL
        depth = ref_coefficients(x, best)[1]
        assert not np.any(coefficients[~ref_keep(n, depth, FS, 16.0)])


@pytest.mark.parametrize("rule", RULES)
def test_off_is_bit_for_bit(rule):
    # SetMinFrequency(0) and never calling it give the same trigger to the last bit.
    rng = np.random.default_rng(7)
    for _ in range(5):
        x = rng.normal(size=1024) + 4.0 * np.sin(2 * np.pi * 7.0 * np.arange(1024) / FS)
        a, ca = classify(x, DEFAULT_BASES + ",LocalCos128", rule)
        b, cb = classify(x, DEFAULT_BASES + ",LocalCos128", rule, 0.0)
        c, cc = classify(x, DEFAULT_BASES + ",LocalCos128", rule, -1.0, 0.0)
        for e, co in ((b, cb), (c, cc)):
            assert e.mWave == a.mWave and e.mSNR == a.mSNR and e.mSigma == a.mSigma
            assert np.array_equal(co, ca)


def test_cut_changes_the_low_frequency_window():
    x = np.random.default_rng(1).normal(size=1024) + 6.0 * np.sin(2 * np.pi * 7.0 * np.arange(1024) / FS)
    full, _ = classify(x, None, "block")
    cut, coefficients = classify(x, None, "block", 16.0)
    assert cut.mSNR < full.mSNR
    assert not np.any(coefficients[:16])


def test_copy_keeps_the_cut():
    c = tsa.WDF2Classify(1024, 0, -1.0, 1.0, 1024)
    assert c.GetMinFrequency() == 0.0
    c.SetMinFrequency(16.0, FS)
    assert tsa.WDF2Classify(c).GetMinFrequency() == 16.0
    c.SetMinFrequency(0.0, FS)
    assert c.GetMinFrequency() == 0.0


@pytest.mark.parametrize("f, fs", [(16.0, 0.0), (16.0, -2048.0), (1024.0, 2048.0), (2000.0, 2048.0)])
def test_rejects(f, fs):
    with pytest.raises(ValueError):
        tsa.WDF2Classify(1024, 0, -1.0, 1.0, 1024).SetMinFrequency(f, fs)
    with pytest.raises(ValueError):
        tsa.WaveletThreshold(1024).SetMinFrequency(f, fs)
