LocalCosine
========================================

Orthonormal local cosine bases (``LocalCosineTransform``), the cosine-packet
tree with the Coifman-Wickerhauser best-basis search (``CosinePackets``) and
the orthonormal DCT-IV they use (``DCT4``), declared in ``LocalCosine.hpp``.

Conventions shared by the three classes:

- Segment edges sit between samples: edge ``a`` separates sample ``a - 1``
  from sample ``a``. A bell of half-width ``eps`` acts on the ``2 eps``
  samples ``a - eps .. a + eps - 1``; ``2 eps`` must not exceed the shortest
  segment, and ``eps = 0`` is the block DCT-IV.
- The rising cut-off is ``r(t) = sin(pi/4 (1 + beta(t)))`` at the sample
  centres ``t = (j + 1/2) / eps``. The Coifman-Meyer bell takes ``beta`` as
  ``sin(pi t / 2)`` iterated three times; the sine bell takes ``beta(t) = t``.
- Each segment of ``M`` samples gets the orthonormal DCT-IV
  ``c_k = sqrt(2/M) sum_n y_n cos(pi/M (n + 1/2)(k + 1/2))``, FFTW's REDFT11
  scaled by ``1/sqrt(2M)``; it is its own inverse.
- ``periodic`` window edges fold at ``0 = N`` too, wrapping round, as the
  periodized wavelet transform does; ``free`` edges do not fold there. Both
  give orthonormal bases.

.. doxygenclass:: tsa::LocalCosineTransform
  :members:

.. doxygenclass:: tsa::CosinePackets
  :members:

.. doxygenclass:: tsa::DCT4
  :members:
