"""Reading a frame: FrameIChannel over data/test_ramp.gwf.

The channel carries a ramp, so every sample read back has a known value.
See data/make_fixture.c for how the fixture was written.
"""
import os
import unittest

import py4tsa
from py4tsa.tsa import FrameIChannel

GWF = os.path.join(os.path.dirname(__file__), "data", "test_ramp.gwf")
CHANNEL = "RAMP"
FS = 16.0
NDATA = 64
GPS = 700000000.0


class TestFrameIO(unittest.TestCase):
    def test_reads_the_samples_it_was_given(self):
        stream = FrameIChannel(GWF, CHANNEL, 1.0, GPS)
        data = py4tsa.tsa.SeqView_double_t()
        stream.GetData(data)

        # GetSampling is the step between samples, not the rate.
        self.assertEqual(data.GetSampling(), 1.0 / FS)
        self.assertEqual(data.GetStart(), GPS)

        n = int(FS)  # one second was asked for
        self.assertEqual(data.GetSize(), n)
        for i in range(n):
            self.assertEqual(data.GetY(0, i), float(i))

    def test_a_second_read_continues_where_the_first_stopped(self):
        stream = FrameIChannel(GWF, CHANNEL, 1.0, GPS)
        data = py4tsa.tsa.SeqView_double_t()

        stream.GetData(data)
        stream.GetData(data)

        n = int(FS)
        self.assertEqual(data.GetStart(), GPS + 1.0)
        for i in range(n):
            self.assertEqual(data.GetY(0, i), float(n + i))


if __name__ == "__main__":
    unittest.main()
