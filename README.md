# P4TSA (package for Time Series Analysis) #
 

by Elena Cuoco (info@elenacuoco.com) https://www.elenacuoco.com

This library is a 'spin-off' of C++ Noise Analysis Package (NAP) written together 
with Giancarlo Cella (giancarlo.cella@pi.infn.it)

The core library is writte in C++ and should be compiled before using the python interface.

The Python interface to the library is pyTSA (you can call it pi'za)
 
### What is this repository for? ###
p4TSA is a minimal package containing ad hoc function to work with time series. 
It includes
 * Whitening in time domain
 * Wavelet decomposition
 * Wavelet Detection Filter

### How do I get set up? ###

* You need to have a python environment setup and some extralibrary (boost, FramLib,gsl,fftw3 installed)
* You should run cmake CMakeList.txt
* Dependencies: gsl, fftw3, gslcblas, Framelib
* Python Binding: it depends on binder and pybind11 which should be installed 
* Database configuration: none
* How to run tests: under dir test run 

    <code>python test.py</code>
* Deployment instructions: under python-wrapper directory run

    <code>python setup.py install</code>

### Contribution guidelines ###

* Writing tests
* Code review
* Other guidelines

### Who do I talk to? ###

* Repo owner or admin (info@elenacuoco.com)
* Other community or team contact (elena.cuoco@ego-gw.it, giancarlo.cella@pi.infn.it)

[![Foo](https://img.shields.io/badge/docs-latest-brightgreen.svg?style=flat)](http://p4tsa.readthedocs.io/en/latest/?badge=latest)
 
