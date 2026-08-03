"""Round-trip regression tests for Cereal-based persistence
(ArBurgEstimator.Save/Load, LatticeView.Save/Load), replacing the old
eternity XML framework as of 2026-08-03 -- see include/CerealPersistence.hpp.
"""
import os
import tempfile
import unittest

import numpy as np

import pytsa
from pytsa.tsa import ArBurgEstimator, LatticeView


def _seqview(n, seed, fs=256.0, t0=0.0):
    rng = np.random.default_rng(seed)
    x = rng.normal(0.0, 1.0, n)
    from wdf.structures.array2SeqView import array2SeqView
    return array2SeqView(t0, fs, n).Fill(t0, x)


class TestPersistence(unittest.TestCase):
    def test_ar_burg_estimator_round_trip(self):
        ade = ArBurgEstimator(20)
        ade(_seqview(4000, seed=1))
        order = ade.GetArOrder()

        with tempfile.TemporaryDirectory() as tmp:
            path = os.path.join(tmp, "ar.bin")
            ade.Save(path)
            self.assertTrue(os.path.exists(path))

            reloaded = ArBurgEstimator(20)
            reloaded.Load(path)
            self.assertEqual(reloaded.GetArOrder(), order)
            for i in range(order + 1):
                self.assertEqual(reloaded.GetAR(i), ade.GetAR(i))

    def test_lattice_view_round_trip(self):
        ade = ArBurgEstimator(20)
        ade(_seqview(4000, seed=2))
        lv = LatticeView(20)
        ade.GetLatticeView(lv)

        with tempfile.TemporaryDirectory() as tmp:
            path = os.path.join(tmp, "lv.bin")
            lv.Save(path)

            reloaded = LatticeView(20)
            reloaded.Load(path)
            self.assertEqual(reloaded.GetOrder(), lv.GetOrder())
            for j in range(lv.GetOrder() + 1):
                self.assertEqual(reloaded.GetParcorF(j), lv.GetParcorF(j))
                self.assertEqual(reloaded.GetParcorB(j), lv.GetParcorB(j))
                self.assertEqual(reloaded.GetErrorForward(0, j), lv.GetErrorForward(0, j))
                self.assertEqual(reloaded.GetErrorBackward(0, j), lv.GetErrorBackward(0, j))


if __name__ == "__main__":
    unittest.main()
