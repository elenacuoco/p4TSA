Installation
===============

-  You need to have a python environment setup and some extra library
   (boost, FramLib,gsl,fftw3 installed)
-  You should run cmake CMakeList.txt
-  Dependencies: gsl, fftw3, gslcblas, Framelib
-  Python Binding: it depends on binder and pybind11 which should be
   installed


Prepare the enviroment
-----------------------

- Use install_full_dependencies.sh in the root package dir

Install p4TSA, pyTSA  by running:
------------------------------------

- cmake CmakeList.txt
- make
- make install
- cd python-wrapper
- python setup.py install
