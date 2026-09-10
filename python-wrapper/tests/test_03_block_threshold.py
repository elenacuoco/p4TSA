"""The block rule of WaveletThreshold: neighbouring coefficients judged
together, against the universal threshold that judges each alone."""
import math
import unittest

import numpy as np
import pytsa

N = 512
DJ = math.sqrt(2.0 * math.log(N))


def coefficients(values):
    view = pytsa.tsa.SeqView_double_t(0.0, 1.0, N)
    for i, v in enumerate(values):
        view.FillPoint(0, i, float(v))
    return view


def kept(view):
    return np.array([view.GetY(0, i) for i in range(N)]) != 0.0


class BlockThreshold(unittest.TestCase):

    def setUp(self):
        # Unit Gaussian noise, so the median-based sigma is close to one.
        self.noise = np.random.default_rng(7).standard_normal(N)
        # Six contiguous coefficients of the 32-64 Hz level at 2048 Hz
        # (indices 16-31), each at 2.5 sigma: below the universal threshold
        # one by one, well above lambda L sigma^2 as a block. The level is
        # cut into blocks of six from its first index, so 22-27 is one block.
        self.signal = self.noise.copy()
        self.signal[22:28] = 2.5

    def test_the_universal_threshold_drops_a_signal_spread_over_a_block(self):
        rule = pytsa.tsa.WaveletThreshold(N)
        view = coefficients(self.signal)
        rule(view, pytsa.tsa.WaveletThreshold.dohonojohnston)
        self.assertTrue(rule.GetSigma() < 1.3)
        self.assertFalse(kept(view)[22:28].any())

    def test_the_block_rule_keeps_it_whole(self):
        rule = pytsa.tsa.WaveletThreshold(N)
        self.assertEqual(rule.GetBlockLength(), 6)
        self.assertAlmostEqual(rule.GetBlockLambda(), 4.505)
        view = coefficients(self.signal)
        rule(view, pytsa.tsa.WaveletThreshold.block)
        survivors = kept(view)
        self.assertTrue(survivors[22:28].all())
        # a kept coefficient keeps its value, hard thresholding
        self.assertAlmostEqual(view.GetY(0, 24), 2.5)

    def test_the_block_rule_keeps_little_of_noise(self):
        rule = pytsa.tsa.WaveletThreshold(N)
        view = coefficients(self.noise)
        rule(view, pytsa.tsa.WaveletThreshold.block)
        # lambda L sigma^2 = 27 for six unit-variance coefficients:
        # chi-square with six degrees of freedom exceeds it once in 7000
        self.assertLessEqual(kept(view).sum(), 6)

    def test_the_block_parameters_are_settable(self):
        rule = pytsa.tsa.WaveletThreshold(N)
        rule.SetBlock(3, 3.0)
        self.assertEqual(rule.GetBlockLength(), 3)
        self.assertAlmostEqual(rule.GetBlockLambda(), 3.0)
        view = coefficients(self.signal)
        rule(view, pytsa.tsa.WaveletThreshold.block)
        # blocks of three from index 16: 22-24 and 25-27 are all signal
        self.assertTrue(kept(view)[22:28].all())

    def test_the_classifier_accepts_the_mode(self):
        pytsa.tsa.WDF2Classify(N, 32, 5.0, 1.0, N, pytsa.tsa.WaveletThreshold.block)


if __name__ == "__main__":
    unittest.main()
