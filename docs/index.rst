.. p4TSA documentation master file, created by
   sphinx-quickstart on Mon Feb 20 10:04:45 2017.
   You can adapt this file completely to your liking, but it should at least
   contain the root `toctree` directive.

Welcome to p4TSA and pyTSA documentation
==========================================

The documentation is still Under Construction
---------------------------------------------

p4TSA is a C++ and python package for Time Series Analysis

pyTSA is the python wrapper

pyWDFml is a python package to perform Machine Learning with WDF pipeline

.. include:: ../README.rst
Features
--------

- Contains Whitening in Time domain
- Contais Wavelet Detection Filter (WDF)

How do I get set up?
~~~~~~~~~~~~~~~~~~~~

Installation
------------

-  You need to have a python environment setup and some extra library
   (boost, FramLib,gsl,fftw3 installed)
-  You should run cmake CMakeList.txt
-  Dependencies: gsl, fftw3, gslcblas, Framelib
-  Python Binding: it depends on binder and pybind11 which should be
   installed


* Prepare the enviroment

    - Use install_full_dependencies.sh in the root package dir

* Install p4TSA, pyTSA and pyWDFml by running:

    - cmake CmakeList.txt
    - make
    - make install
    - cd python-wrapper
    - python setup.py install
    - cd pyWDF
    - python setup.py install


Contribute
----------

- Issue Tracker: github.com/elenacuoco/p4TSA/issues
- Source Code: github.com/elenacuoco/p4TSA

Support
-------

If you are having issues, please let us know.
We have a mailing list located at: elena.cuoco@ego-gw.it

Contribution guidelines
~~~~~~~~~~~~~~~~~~~~~~~

-  Writing tests
-  Code review
-  Other guidelines

Who do I talk to?
~~~~~~~~~~~~~~~~~

-  Repo owner or admin (info@elenacuoco.com)
-  Other community or team contact (elena.cuoco@ego-gw.it,
   giancarlo.cella@pi.infn.it)

License
~~~~~~~

EGO



Documentation for pyTSA
=======================

.. toctree::
        :maxdepth: 2
        :numbered:
        :titlesonly:
        :glob:
        :hidden:
         pyTSA.rst


Documentation for pyWDF
=======================

.. toctree::
        :maxdepth: 2
        :numbered:
        :titlesonly:
        :glob:
        :hidden:


        modules.rst




Indices and tables
------------------

* :ref:`genindex`
* :ref:`modindex`
* :ref:`search`

.. toctree::
   :maxdepth: 2
   :caption: Contents:


