"""WDF2Reconstruct follows WDF2Classify's basis competition.

Both classes take the default list DefaultWaveletBases(), the default rule
DefaultWaveletThresholding() and the same names through SetBases; with the
same list, rule and parameters they pick the same winner with the same
coefficients in every window. Reconstruct inverts a trigger exactly with the
transform its mWave names. SetBases(LegacyWaveletBases()) with the rule
passed explicitly (cuoco, the 3.3.0 default) reproduces the output of release
3.3.0, recorded in data/wdf2reconstruct_3.3.0.json by record_reference().
"""
import json
import os

import numpy as np
import pytest

from py4tsa import tsa

FS = 2048.0
HERE = os.path.dirname(os.path.abspath(__file__))
REFERENCE = os.path.join(HERE, "data", "wdf2reconstruct_3.3.0.json")
OLD = "Haar,DaubC4,DaubC8,DaubC12,DaubC16,DaubC20,Sym4,Sym8,Coif1,Coif2"
NEW = "Haar,DaubC4,DaubC8,Sym4,DaubC16,Sym8,Coif3,DaubC24,Sym12,Coif5"
RULES = {"cuoco": tsa.WaveletThreshold.cuoco, "block": tsa.WaveletThreshold.block,
         "dohonojohnston": tsa.WaveletThreshold.dohonojohnston}


def stream(n=256, windows=24):
    """White noise with a Gaussian-windowed tone in every third window."""
    rng = np.random.default_rng(340)
    x = rng.normal(size=windows * n)
    t = np.arange(n) / FS
    for w in range(0, windows, 3):
        x[w * n:(w + 1) * n] += (2 + w % 5) * np.sin(2 * np.pi * (40 + 25 * w) * t) * \
            np.exp(-((t - 0.06) / 0.02) ** 2)
    return x


def view_of(x):
    v = tsa.SeqView_double_t(0.0, 1.0 / FS, len(x))
    fp = v.FillPoint
    for i, value in enumerate(np.asarray(x, dtype=float).tolist()):
        fp(0, i, value)
    return v


def events(algo, x, ncoeff):
    algo << view_of(x)
    ev = tsa.EventFullFeatured(ncoeff)
    out = []
    while algo.GetDataNeeded() >= 0:
        assert algo(ev) == 1
        out.append({"wave": ev.mWave, "snr": ev.mSNR, "sigma": ev.mSigma, "level": ev.mlevel,
                    "coeff": np.array([ev.GetCoeff(i) for i in range(ncoeff)]), "event": ev})
        ev = tsa.EventFullFeatured(ncoeff)
    return out


def reconstructor(n, ncoeff, rule=None, bases=None):
    r = (tsa.WDF2Reconstruct(n, 0, -1.0, 1.0, ncoeff) if rule is None
         else tsa.WDF2Reconstruct(n, 0, -1.0, 1.0, ncoeff, RULES[rule]))
    if bases is not None:
        r.SetBases(bases)
    return r


def record_reference():
    """Write the reference; run once with the py4tsa 3.3.0 module on the path."""
    def plain(r):
        return [{k: (v.tolist() if k == "coeff" else v) for k, v in e.items() if k != "event"}
                for e in events(r, stream(), 32)]
    ref = {"cuoco": plain(reconstructor(256, 32, "cuoco")), "block": plain(reconstructor(256, 32, "block"))}
    with open(REFERENCE, "w") as f:
        json.dump(ref, f, indent=0)


def test_default_is_the_shared_list():
    assert tsa.DefaultWaveletBases() == NEW
    assert tsa.LegacyWaveletBases() == OLD
    assert tsa.DefaultWaveletThresholding() == tsa.WaveletThreshold.block
    c = tsa.WDF2Classify(1024, 0, 5.0, 1.0, 1024)
    r = tsa.WDF2Reconstruct(1024, 0, 5.0, 1.0, 1024)
    assert r.GetBases() == c.GetBases() == NEW


def test_default_settings_match_the_classifier():
    """Both built with every default: same winner, coefficients, sigma and
    level in every window, the reconstructor's statistic half the classifier's."""
    n = 256
    x = stream(n)
    ec = events(tsa.WDF2Classify(n, 0, -1.0, 1.0, n), x, n)
    er = events(tsa.WDF2Reconstruct(n, 0, -1.0, 1.0, n), x, n)
    explicit = events(tsa.WDF2Classify(n, 0, -1.0, 1.0, n, tsa.WaveletThreshold.block), x, n)
    assert len(ec) == len(er) == 24
    for a, b, e in zip(ec, er, explicit):
        assert a["wave"] == b["wave"] == e["wave"]
        assert a["sigma"] == b["sigma"] and a["level"] == b["level"]
        assert np.array_equal(a["coeff"], b["coeff"]) and np.array_equal(a["coeff"], e["coeff"])
        assert b["snr"] == pytest.approx(a["snr"] / 2, rel=1e-14)


@pytest.mark.parametrize("rule", ["block", "cuoco"])
@pytest.mark.parametrize("bases", [None, NEW + ",Sym8P4,LocalCos32", OLD])
def test_same_winner_and_coefficients_as_the_classifier(rule, bases):
    n = 256
    x = stream(n)
    c = tsa.WDF2Classify(n, 0, -1.0, 1.0, n, RULES[rule])
    r = reconstructor(n, n, rule, bases)
    if bases is not None:
        c.SetBases(bases)
    assert r.GetBases() == c.GetBases()
    ec, er = events(c, x, n), events(r, x, n)
    assert len(ec) == len(er) == 24
    for a, b in zip(ec, er):
        assert a["wave"] == b["wave"]
        assert a["sigma"] == b["sigma"] and a["level"] == b["level"]
        assert np.array_equal(a["coeff"], b["coeff"])
        assert b["snr"] == pytest.approx(a["snr"] / 2, rel=1e-14)


def test_packet_and_local_cosine_winners_occur():
    n = 256
    r = reconstructor(n, n, None, "Sym8P4,LocalCos32")
    waves = {e["wave"] for e in events(r, stream(n), n)}
    assert waves == {"Sym8P4", "LocalCos32"}


@pytest.mark.parametrize("bases", [None, NEW + ",Sym8P4,Coif5P3,LocalCos32,LocalCos16"])
def test_reconstruct_inverts_exactly(bases):
    n = 256
    x = stream(n)
    r = reconstructor(n, n, None, bases)
    seen = set()
    for e in events(r, x, n):
        seen.add(e["wave"])
        y = r.Reconstruct(e["event"])
        # Round trip: the reconstructed window, transformed again in the
        # winner's basis, gives the trigger's coefficients back.
        name = e["wave"]
        if name.startswith("LocalCos"):
            t = tsa.WaveletTransform(n, tsa.WaveletTransform.LocalCos, int(np.log2(int(name[8:]))))
        elif "P" in name[1:]:
            mother, depth = name.rsplit("P", 1)
            t = tsa.WaveletTransform(n, getattr(tsa.WaveletTransform, mother), int(depth))
        else:
            t = tsa.WaveletTransform(n, getattr(tsa.WaveletTransform, name))
        v = view_of(y)
        t.Forward(v)
        coeff = np.array([v.GetY(0, i) for i in range(n)])
        # Relative to the largest coefficient (a window can be zeroed
        # whole): the Symlet taps are orthonormal to about 1e-14 only.
        assert np.max(np.abs(coeff - e["coeff"])) <= 1e-11 * max(1.0, np.max(np.abs(e["coeff"])))
    assert seen


@pytest.mark.parametrize("bases", ["Haar", "Sym8P4", "LocalCos32"])
def test_reconstruct_of_unthresholded_coefficients_is_the_window(bases):
    n = 256
    x = np.random.default_rng(5).normal(size=n)
    r = reconstructor(n, n, None, bases)
    ev = tsa.EventFullFeatured(n)
    ev.mWave = bases
    name = bases
    if name.startswith("LocalCos"):
        t = tsa.WaveletTransform(n, tsa.WaveletTransform.LocalCos, 5)
    elif "P" in name[1:]:
        t = tsa.WaveletTransform(n, tsa.WaveletTransform.Sym8, 4)
    else:
        t = tsa.WaveletTransform(n, tsa.WaveletTransform.Haar)
    v = view_of(x)
    t.Forward(v)
    for i in range(n):
        ev.SetCoeff(i, v.GetY(0, i))
    assert np.max(np.abs(r.Reconstruct(ev) - x)) < 1e-11


def test_reconstruct_rejects_unknown_names():
    r = tsa.WDF2Reconstruct(256, 0, -1.0, 1.0, 256)
    ev = tsa.EventFullFeatured(256)
    for name in ("Bspline309", "Sym8P9", "LocalCos512", ""):
        ev.mWave = name
        with pytest.raises(ValueError):
            r.Reconstruct(ev)


@pytest.mark.parametrize("names", ["", "Haar,Haar", "Foo", "Sym8P0", "LocalCos3"])
def test_set_bases_rejects(names):
    with pytest.raises(ValueError):
        tsa.WDF2Reconstruct(256, 0, -1.0, 1.0, 256).SetBases(names)


def test_block_rule_refuses_bands_shorter_than_a_block():
    r = tsa.WDF2Reconstruct(256, 0, -1.0, 1.0, 256, tsa.WaveletThreshold.block)
    r.SetBases("Sym8P5")          # bands of 8 >= L = 6
    with pytest.raises(ValueError):
        r.SetBases("Sym8P6")      # bands of 4 < 6


def test_copies_keep_the_list():
    r = tsa.WDF2Reconstruct(256, 0, -1.0, 1.0, 256)
    r.SetBases("Sym8P4,LocalCos32")
    assert tsa.WDF2Reconstruct(r).GetBases() == "Sym8P4,LocalCos32"


@pytest.mark.parametrize("rule", ["cuoco", "block"])
def test_legacy_list_reproduces_release_3_3_0(rule):
    with open(REFERENCE) as f:
        reference = json.load(f)[rule]
    # The 3.3.0 configuration: the legacy list and the rule, both explicit.
    got = events(reconstructor(256, 32, rule, tsa.LegacyWaveletBases()), stream(), 32)
    assert len(got) == len(reference)
    for a, b in zip(got, reference):
        assert a["wave"] == b["wave"] and a["level"] == b["level"]
        assert a["snr"] == pytest.approx(b["snr"], rel=1e-12)
        assert a["sigma"] == pytest.approx(b["sigma"], rel=1e-12)
        assert np.allclose(a["coeff"], b["coeff"], rtol=1e-12, atol=1e-12)


def test_new_defaults_differ_from_release_3_3_0():
    with open(REFERENCE) as f:
        reference = json.load(f)["cuoco"]
    got = events(reconstructor(256, 32), stream(), 32)
    assert [e["wave"] for e in got] != [e["wave"] for e in reference]
