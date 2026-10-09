"""The long mothers: Sym10-20, Coif3-5 and DaubC24/32/40 (db12/16/20)."""
import numpy as np
import pytest

from py4tsa import tsa

W = tsa.WaveletTransform
# p4TSA name -> PyWavelets name
LONG = {"DaubC24": "db12", "DaubC32": "db16", "DaubC40": "db20",
        "Sym10": "sym10", "Sym12": "sym12", "Sym16": "sym16", "Sym20": "sym20",
        "Coif3": "coif3", "Coif4": "coif4", "Coif5": "coif5"}
TAPS = {"DaubC24": 24, "DaubC32": 32, "DaubC40": 40, "Sym10": 20, "Sym12": 24,
        "Sym16": 32, "Sym20": 40, "Coif3": 18, "Coif4": 24, "Coif5": 30}
# PyWavelets' own Symlet taps are orthonormal only to 2.2e-14 (sym10),
# 4.4e-14 (sym12), 1.8e-12 (sym16) and 1.4e-11 (sym20): max |sum h[k] h[k+2m]
# - delta_m|, printed by tools/generate_long_wavelet_tables.py. The tables keep
# them bit for bit, so these mothers are orthonormal and reconstruct to that
# accuracy, which a packet level of depth 7 multiplies by about 30 (measured
# worst over N 512-2048, depths 0/6/7: 6.7e-13, 1.4e-12, 5.5e-11, 4.3e-10).
# The Daubechies and Coiflet ones reach 4e-15.
TOL = {m: 1e-12 for m in LONG}
TOL.update(Sym12=3e-12, Sym16=1e-10, Sym20=1e-9)
FS = 2048.0


def view_of(x):
    v = tsa.SeqView_double_t(0.0, 1.0 / FS, len(x))
    for i, value in enumerate(np.asarray(x, dtype=float).tolist()):
        v.FillPoint(0, i, value)
    return v


def values(v, n):
    return np.array([v.GetY(0, i) for i in range(n)])


def transform(mother, n, depth):
    return W(n, getattr(W, mother)) if depth == 0 else W(n, getattr(W, mother), depth)


def forward(x, mother, depth=0):
    v = view_of(x)
    transform(mother, len(x), depth).Forward(v)
    return values(v, len(x))


def inverse(c, mother, depth=0):
    v = view_of(c)
    transform(mother, len(c), depth).Inverse(v)
    return values(v, len(c))


@pytest.mark.parametrize("mother", LONG)
def test_matrix_is_orthonormal(mother):
    # The whole transform matrix of a 512 window, pyramid and packet level 6.
    n = 512
    for depth in (0, 6):
        t = np.array([forward(e, mother, depth) for e in np.eye(n)]).T
        assert np.max(np.abs(t.T @ t - np.eye(n))) < TOL[mother]


@pytest.mark.parametrize("mother", LONG)
@pytest.mark.parametrize("n", [512, 1024, 2048])
@pytest.mark.parametrize("depth", [0, 6, 7])
def test_perfect_reconstruction_and_inner_products(mother, n, depth):
    rng = np.random.default_rng(n + depth)
    x, y = rng.normal(size=(2, n))
    cx, cy = forward(x, mother, depth), forward(y, mother, depth)
    assert np.max(np.abs(inverse(cx, mother, depth) - x)) < TOL[mother]
    assert abs(cx @ cx / (x @ x) - 1.0) < TOL[mother]
    assert abs(cx @ cy - x @ y) / np.sqrt((x @ x) * (y @ y)) < TOL[mother]


@pytest.mark.parametrize("mother", LONG)
def test_packet_depth_zero_and_one_are_the_pyramid(mother):
    x = np.random.default_rng(4).normal(size=512)
    assert np.array_equal(forward(x, mother, 0), forward(x, mother))
    assert np.array_equal(forward(x, mother, 1)[256:], forward(x, mother)[256:])


@pytest.mark.parametrize("mother", LONG)
def test_taps_and_centring(mother):
    # A unit impulse at the window centre: the finest-level coefficients it
    # touches are the high-pass taps, centred as GSL centres DaubC*
    # (offset nc / 2): coefficient k of the finest level sees samples
    # 2k - nc/2 .. 2k + nc/2 - 1.
    n, nc = 512, TAPS[mother]
    x = np.zeros(n)
    x[n // 2] = 1.0
    fine = forward(x, mother)[n // 2:]
    support = np.flatnonzero(np.abs(fine) > 0)
    k = np.arange(n // 2)
    expected = np.flatnonzero((2 * k - nc // 2 <= n // 2) & (n // 2 <= 2 * k + nc // 2 - 1))
    assert np.array_equal(support, expected)


# ------------------------------------------------- agreement with PyWavelets
def pywt_pyramid(x, name):
    """GSL's packed pyramid with PyWavelets' filters: before each split a
    one-sample circular shift, the offset nc / 2 of GSL's centred families."""
    pywt = pytest.importorskip("pywt")
    a, details = np.asarray(x, float), []
    while a.size >= 2:
        a, d = pywt.dwt(np.roll(a, 1), name, mode="periodization")
        details.insert(0, d)
    return np.concatenate([a] + details)


def pywt_packets(x, name, depth):
    """The uniform packet level, bands in frequency order (Gray permutation)."""
    pywt = pytest.importorskip("pywt")
    parts = [np.asarray(x, float)]
    for _ in range(depth):
        parts = [y for p in parts for y in pywt.dwt(np.roll(p, 1), name, mode="periodization")]
    return np.concatenate([parts[f ^ (f >> 1)] for f in range(2 ** depth)])


@pytest.mark.parametrize("mother", LONG)
@pytest.mark.parametrize("n", [512, 1024, 2048])
def test_pyramid_matches_pywavelets(mother, n):
    x = np.random.default_rng(n).normal(size=n)
    assert np.max(np.abs(forward(x, mother) - pywt_pyramid(x, LONG[mother]))) < 1e-12


@pytest.mark.parametrize("mother", LONG)
@pytest.mark.parametrize("n", [1024, 2048])
@pytest.mark.parametrize("depth", [6, 7])
def test_packets_match_pywavelets(mother, n, depth):
    x = np.random.default_rng(n + depth).normal(size=n)
    assert np.max(np.abs(forward(x, mother, depth) - pywt_packets(x, LONG[mother], depth))) < 1e-12


# ------------------------------------------------- the basis competition
def statistic(c):
    a = np.abs(c)
    sigma = np.median(a) / 0.6745
    kept = np.where(a > np.sqrt(2 * np.log(len(c))) * sigma, c, 0.0)
    return np.sqrt(np.sum(kept ** 2)) / sigma


@pytest.mark.parametrize("names", [",".join(LONG), ",".join(m + "P6" for m in LONG)])
def test_set_bases_accepts_the_long_mothers(names):
    c = tsa.WDF2Classify(1024, 0, -1.0, 1.0, 1024, tsa.WaveletThreshold.dohonojohnston)
    c.SetBases(names)
    assert c.GetBases() == names


def test_competition_with_the_long_mothers():
    n = 1024
    bases = ["Haar", "DaubC8", "Sym4", "Coif1"] + list(LONG) + [m + "P6" for m in ("Sym20", "Coif5")]
    rng = np.random.default_rng(5)
    t = np.arange(n) / FS
    for window in range(4):
        x = rng.normal(size=n)
        x[300:600] += (2.0 + window) * np.sin(2 * np.pi * (60.0 + 40.0 * window) * t[300:600])
        c = tsa.WDF2Classify(n, 0, -1.0, 1.0, n, tsa.WaveletThreshold.dohonojohnston)
        c.SetBases(",".join(bases))
        c(view_of(x), 1.0)
        event = tsa.EventFullFeatured(n)
        assert c(event) == 1
        scores = {}
        for name in bases:
            mother, _, depth = name.partition("P")
            scores[name] = statistic(forward(x, mother, int(depth or 0)))
        best = max(bases, key=lambda b: (scores[b], bases.index(b)))   # a tie goes to the later
        assert event.mWave == best
        assert event.mSNR == pytest.approx(scores[best], rel=1e-12)


def test_default_competition_picks_the_best_basis():
    # Whatever the default list is (test_05 spells it out), its winner is the
    # candidate of the largest statistic, the later one on a tie.
    n = 1024
    rng = np.random.default_rng(6)
    t = np.arange(n) / FS
    for window in range(3):
        x = rng.normal(size=n)
        x[200:700] += 1.5 * np.sin(2 * np.pi * (40.0 + 80.0 * window) * t[200:700] * (1.0 + t[200:700]))
        c = tsa.WDF2Classify(n, 0, -1.0, 1.0, n, tsa.WaveletThreshold.dohonojohnston)
        bases = c.GetBases().split(",")
        c(view_of(x), 1.0)
        event = tsa.EventFullFeatured(n)
        assert c(event) == 1
        scores = {b: statistic(forward(x, b)) for b in bases}
        best = max(bases, key=lambda b: (scores[b], bases.index(b)))
        assert event.mWave == best
        assert event.mSNR == pytest.approx(scores[best], rel=1e-12)
