from scipy import signal

from scipy.signal import cheby1, firwin, lfilter, resample


def downsampling(data, factor, numtaps):
    """

    :type numtaps: int number
    :type factor: int number
    :rtype: numpy array
    :type data: numpy array
    :param data: the orginal data
    :param factor: the downsamplig factor
    :param numtaps: the number of taps for the filter
    :return: downsampled data
    """
    data_ds = signal.decimate(data, factor, numtaps - 1, ftype='fir')
    return data_ds


def decimate(x, q, n=None, ftype='iir', axis=-1):
    """
    This wdf_code is copied from scipy.signal

    Downsample the signal by using a filter.
    By default, an order 8 Chebyshev type I filter is used.  A 30 point FIR
    filter with hamming window is used if `ftype` is 'fir'.

        Parameters
    ----------
    x : ndarray
        The signal to be downsampled, as an N-dimensional array.
    q : int
        The downsampling factor.
    n : int, optional
        The order of the filter (1 less than the length for 'fir').
    ftype : str {'iir', 'fir'}, optional
        The type of the lowpass filter.
    axis : int, optional
        The axis along which to decimate.
        Returns
    -------
    y : ndarray
        The down-sampled signal.
        See also
        --------
    scipy.resample
    """

    if not isinstance(q, int):
        raise TypeError("q must be an integer")

    if n is None:
        if ftype == 'fir':
            n = 30
        else:
            n = 8

    if ftype == 'fir':
        b = firwin(n + 1, 1. / q, window='hamming')
        a = 1.
    else:
        b, a = cheby1(n, 0.05, 0.8 / q)

    y = lfilter(b, a, x, axis=axis)
    sl = [slice(None)] * y.ndim
    sl[axis] = slice(None, None, q)
    return y[sl]


def downsampling_cheby1(s, r, n=8, fir=False):
    """
    Downsample the signal by using a filter.
    By default, an order 8 Chebyshev type I filter is used.

    :rtype y: numpy array
    :type s: numpy array
    :param s: the orginal data
    :param r: the downsamplig factor
    :param n: the order of the filter
    :return: downsampled data

    """

    b, a = signal.cheby1(n, 0.05, 1.0 / r)
    f = signal.filtfilt(b, a, s)

    y = f[::r]
    return y
