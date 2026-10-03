"""WDF2Classify.SetBlock: the block rule's length L and lambda from the search.

The classifier owns its WaveletThreshold, whose SetBlock(length, lambda) was
unreachable from a search; the forwarder sets them in every candidate.
"""
import numpy as np
import pytest

from py4tsa import tsa

N = 1024


def view_of(x, fs=2048.0):
    v = tsa.SeqView_double_t(0.0, 1.0 / fs, len(x))
    fp = v.FillPoint
    for i, value in enumerate(np.asarray(x, dtype=float).tolist()):
        fp(0, i, value)
    return v


def energies(configure, windows=64, seed=3):
    c = tsa.WDF2Classify(N, 0, -1.0, 1.0, N, tsa.WaveletThreshold.block)
    configure(c)
    ev = tsa.EventFullFeatured(N)
    rng = np.random.default_rng(seed)
    c << view_of(rng.normal(size=windows * N))
    out = []
    while c.GetDataNeeded() >= 0:
        c(ev)
        out.append(ev.mSNR)
    return np.array(out)


def test_defaults_are_the_core_ones():
    c = tsa.WDF2Classify(N, 0, 5.0, 1.0, N)
    assert c.GetBlockLength() == 7
    assert c.GetBlockLambda() == pytest.approx(4.505)


def test_setter_forwards_and_copies():
    c = tsa.WDF2Classify(N, 0, 5.0, 1.0, N)
    c.SetBlock(9, 6.0)
    assert (c.GetBlockLength(), c.GetBlockLambda()) == (9, 6.0)
    d = tsa.WDF2Classify(c)
    assert (d.GetBlockLength(), d.GetBlockLambda()) == (9, 6.0)
    c.SetBlock(0, 4.505)
    assert c.GetBlockLength() == 7


def test_default_values_are_bit_for_bit():
    base = energies(lambda c: None)
    same = energies(lambda c: c.SetBlock(0, 4.505))
    np.testing.assert_array_equal(base, same)


def test_lambda_changes_what_is_kept():
    low = energies(lambda c: c.SetBlock(0, 2.0))
    high = energies(lambda c: c.SetBlock(0, 50.0))
    assert np.all(high <= low + 1e-12)
    assert high.sum() < low.sum()


def test_refusals():
    c = tsa.WDF2Classify(N, 0, 5.0, 1.0, N, tsa.WaveletThreshold.block)
    with pytest.raises(ValueError):
        c.SetBlock(0, 0.0)
    c.SetBases("DaubC8,LocalCos128")
    with pytest.raises(ValueError):
        c.SetBlock(16, 4.505)
    assert c.GetBlockLength() == 7
