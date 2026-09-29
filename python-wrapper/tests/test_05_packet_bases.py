"""Uniform wavelet-packet levels and the configurable basis competition."""
import numpy as np
import pytest

from py4tsa import tsa

W = tsa.WaveletTransform
MOTHERS = ["Haar", "DaubC4", "DaubC8", "DaubC12", "DaubC16", "DaubC20",
           "Sym4", "Sym8", "Coif1", "Coif2"]
N = 512
FS = 2048.0


def view_of(x):
    v = tsa.SeqView_double_t(0.0, 1.0 / FS, len(x))
    for i, value in enumerate(np.asarray(x, dtype=float).tolist()):
        v.FillPoint(0, i, value)
    return v


def values(v, n):
    return np.array([v.GetY(0, i) for i in range(n)])


def forward(x, mother, depth=None):
    v = view_of(x)
    transform = W(len(x), getattr(W, mother)) if depth is None else W(len(x), getattr(W, mother), depth)
    transform.Forward(v)
    return values(v, len(x))


def inverse(c, mother, depth):
    v = view_of(c)
    W(len(c), getattr(W, mother), depth).Inverse(v)
    return values(v, len(c))


@pytest.fixture(scope="module")
def noise():
    return np.random.default_rng(0).normal(size=N)


@pytest.mark.parametrize("mother", MOTHERS)
def test_depth_zero_is_the_pyramid(noise, mother):
    assert np.array_equal(forward(noise, mother, 0), forward(noise, mother))


@pytest.mark.parametrize("mother", MOTHERS)
def test_first_split_is_the_pyramid_finest_step(noise, mother):
    # One packet step is GSL's own step: its highpass half is the pyramid's
    # finest level and, all the way down, the two lowest bands are the
    # pyramid's scaling and coarsest wavelet coefficient.
    assert np.array_equal(forward(noise, mother, 1)[N // 2:], forward(noise, mother)[N // 2:])
    assert np.array_equal(forward(noise, mother, 9)[:2], forward(noise, mother)[:2])


@pytest.mark.parametrize("mother", MOTHERS)
@pytest.mark.parametrize("depth", range(1, 10))
def test_perfect_reconstruction_and_energy(noise, mother, depth):
    c = forward(noise, mother, depth)
    # Sym4's tabulated taps are orthonormal to about 1e-12, which bounds the
    # pyramid's own reconstruction as well.
    assert np.max(np.abs(inverse(c, mother, depth) - noise)) < 1e-10
    assert abs(np.sum(c * c) / np.sum(noise * noise) - 1.0) < 1e-10


@pytest.mark.parametrize("mother", MOTHERS)
def test_bands_are_in_frequency_order(mother):
    depth, width = 6, FS / 2 ** 7
    t = np.arange(N) / FS
    for band in range(2 ** depth):
        c = forward(np.sin(2 * np.pi * (band + 0.5) * width * t), mother, depth)
        assert int(np.argmax((c.reshape(2 ** depth, -1) ** 2).sum(axis=1))) == band


def test_invalid_packet_level():
    with pytest.raises(ValueError):
        W(N, W.Haar, 10)
    with pytest.raises(ValueError):
        W(500, W.Haar, 2)


def classifier(rule=tsa.WaveletThreshold.dohonojohnston, threshold=-1.0):
    return tsa.WDF2Classify(N, 0, threshold, 1.0, N, rule)


def test_default_candidates_are_the_ten():
    assert classifier().GetBases() == ",".join(MOTHERS)


@pytest.mark.parametrize("names", ["Haar,Nope", "Haar,Haar", "", "HaarP10", "HaarP0",
                                   "Bspline103"])
def test_set_bases_rejects(names):
    with pytest.raises(ValueError):
        classifier().SetBases(names)


def test_block_rule_caps_the_packet_depth():
    # L = round(ln 512) = 6: a band of 512 / 2^D holds a full block up to D = 6.
    c = classifier(tsa.WaveletThreshold.block)
    c.SetBases(",".join("Coif1P%d" % d for d in range(1, 7)))
    for depth in (7, 8, 9):
        with pytest.raises(ValueError):
            c.SetBases("Haar,Coif1P%d" % depth)
    classifier().SetBases("Haar,Coif1P7,Coif1P9")


def block_rule(c, depth, length=6, lam=4.505):
    """The block rule on the runs of a layout: the pyramid's dyadic ladder
    for depth 0, the 2^depth equal bands otherwise."""
    n = len(c)
    if depth == 0:
        edges = [0, 1] + [2 ** k for k in range(1, int(np.log2(n)) + 1)]
    else:
        edges = list(range(0, n + 1, n >> depth))
    sigma = np.median(np.abs(c)) / 0.6745
    kept = c.copy()
    for start, end in zip(edges[:-1], edges[1:]):
        for b in range(start, end, length):
            e = min(b + length, end)
            if np.sum(c[b:e] ** 2) <= lam * sigma ** 2 * (e - b):
                kept[b:e] = 0.0
    return kept, sigma


@pytest.mark.parametrize("name, mother, depth", [("Coif1P6", "Coif1", 6),
                                                 ("DaubC8P3", "DaubC8", 3),
                                                 ("Coif1", "Coif1", 0)])
def test_block_rule_follows_the_packet_bands(name, mother, depth):
    rng = np.random.default_rng(2)
    x = rng.normal(size=N)
    t = np.arange(N) / FS
    x[200:330] += 1.5 * np.sin(2 * np.pi * 200.0 * t[200:330])
    c = classifier(tsa.WaveletThreshold.block)
    c.SetBases(name)
    c(view_of(x), 1.0)
    event = tsa.EventFullFeatured(N)
    assert c(event) == 1
    kept, sigma = block_rule(forward(x, mother, depth or None), depth)
    assert kept.any()
    coefficients = np.array([event.GetCoeff(i) for i in range(N)])
    assert np.array_equal(coefficients, kept)
    assert event.mSigma == pytest.approx(sigma, rel=1e-12)
    assert event.mSNR == pytest.approx(np.sqrt(np.sum(kept ** 2)) / sigma, rel=1e-12)


def test_threshold_layout():
    # At depth 2 a band edge falls at 384, inside the pyramid's block
    # [380, 386) of its level [256, 512): four coefficients at 3 sigma
    # straddling it fill one pyramid block, kept whole, but split over two
    # band blocks, judged apart.
    c = np.random.default_rng(3).normal(size=N)
    c[382:386] = 3.0
    results = {}
    for depth in (0, 2):
        rule = tsa.WaveletThreshold(N)
        rule.SetLayout(depth)
        assert rule.GetLayout() == depth
        v = view_of(c)
        rule(v, tsa.WaveletThreshold.block)
        results[depth] = values(v, N)
        assert np.array_equal(results[depth], block_rule(c, depth)[0])
    assert results[0][382:386].all() and not results[2][382:386].all()
    rule.SetLayout(9)
    with pytest.raises(ValueError):
        rule.SetLayout(10)


def statistic(c):
    a = np.abs(c)
    sigma = np.median(a) / 0.6745
    kept = np.where(a > np.sqrt(2 * np.log(len(c))) * sigma, c, 0.0)
    return np.sqrt(np.sum(kept ** 2)) / sigma, kept, sigma


def test_competition_over_packet_bases(noise):
    bases = MOTHERS[:7] + ["Coif1", "Coif2"] + [m + "P6" for m in MOTHERS]
    c = classifier()
    c.SetBases(",".join(bases))
    assert c.GetBases() == ",".join(bases)
    rng = np.random.default_rng(1)
    x = rng.normal(size=N)
    t = np.arange(N) / FS
    x[200:330] += 4.0 * np.sin(2 * np.pi * 200.0 * t[200:330])
    c(view_of(x), 1.0)
    event = tsa.EventFullFeatured(N)
    assert c(event) == 1
    scores = {}
    for name in bases:
        depth = int(name.split("P")[1]) if name.endswith("P6") else None
        mother = name[:-2] if depth else name
        scores[name] = statistic(forward(x, mother, depth))
    # The later candidate wins a tie, as the competition is defined.
    best = max(bases, key=lambda b: (scores[b][0], bases.index(b)))
    assert event.mWave == best
    assert event.mSNR == pytest.approx(scores[best][0], rel=1e-12)
    assert event.mSigma == pytest.approx(scores[best][2], rel=1e-12)
    coefficients = np.array([event.GetCoeff(i) for i in range(N)])
    assert np.allclose(coefficients, scores[best][1], rtol=0, atol=1e-12)


def test_copy_keeps_the_candidates():
    c = classifier()
    c.SetBases("Haar,Coif1P6")
    assert tsa.WDF2Classify(c).GetBases() == "Haar,Coif1P6"
