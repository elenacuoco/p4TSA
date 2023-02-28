.. p4TSA documentation master file, created by
   sphinx-quickstart on Mon Feb 20 10:04:45 2017.
   You can adapt this file completely to your liking, but it should at least
   contain the root `toctree` directive.

Welcome to p4TSA and pyTSA documentation
==========================================

This library is a 'spin-off' of C++ Noise Analysis Package (NAP). 

The core library is written in C++ and should be compiled before using the python interface.

The Python interface to the library is pyTSA (you can call it pi'za)

Features
--------
p4TSA is a minimal package containing ad hoc function to work with time
series. It contains

- Modern Spectral Analysis Estimators
- Whitening in Time domain
- Double Whitening (equivalent to divide by the inverse of power spectral density) in time domain
- Wavelet Decomposition
- Wavelet Detection Filter (WDF)



.. toctree::
   :maxdepth: 2
   :caption: Contents:

   structure/installation
   structure/contact
   structure/source_code
   WDFpipe <https://wdfpipe.gitlab.io>
