.. p4TSA documentation master file, created by
   sphinx-quickstart on Mon Feb 20 10:04:45 2017.
   You can adapt this file completely to your liking, but it should at least
   contain the root `toctree` directive.

Welcome to p4TSA and pyTSA documentation
==========================================

This library is a 'spin-off' of the C++ Noise Analysis Package (NAP). It is specific to data
analysis for gravitational-wave signals, and in particular it is designed to work on the frame
format the gravitational-wave detectors write.

The core library is written in C++ and should be compiled before using the python interface.

The Python interface to the library is pyTSA (you can call it pi'za)

Features
--------
p4TSA is a minimal package containing ad hoc function to work with time
series. It contains

- Modern Spectral Analysis Estimators
- Whitening in Time domain
- Double Whitening in Time domain
- Wavelet Decomposition
- Wavelet Detection Filter (WDF)

The pipeline
------------

p4TSA provides the C++ core; the search pipeline that drives it lives in
`wdflow <https://github.com/elenacuoco/wdflow>`_, which imports this library
through its Python interface. ``wdflow`` supersedes the earlier ``wdf``
package: it carries forward the modules the real trigger-search pipeline uses,
adds the downstream trigger analysis, and is the one to install. The two share the top-level module name ``wdf``, so they cannot
be installed side by side.

.. toctree::
   :maxdepth: 2
   :caption: Contents:

   structure/installation
   structure/contact
   structure/source_code
   wdflow (the pipeline) <https://github.com/elenacuoco/wdflow>
