"""Frame I/O: the one part of the library that needs FrameL.

Everything else here runs on GSL and FFTW3, so a build whose FrameL is
missing, mislinked or built against different headers passes the rest of the
suite untouched -- and that is precisely the build a wheel would ship. The
fixture carries a ramp, so a read that returns the wrong offset, the wrong
channel or zeros fails on the values rather than merely on an exception.

See data/make_fixture.c for how test_ramp.gwf was written.
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
