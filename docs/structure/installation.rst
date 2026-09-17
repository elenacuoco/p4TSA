Installation
===============

.. note::

   The module used to be called ``pytsa``. That name on PyPI belongs to an
   unrelated project, so change any ``import pytsa`` to ``import py4tsa``.

Dependencies
------------

p4TSA is not a pure-Python package: building it compiles the C++ core into a
single Python extension module (``py4tsa``). It depends on:

- GSL (+ gslcblas) -- build **and** run
- FFTW3 (double, float, long-double) -- build **and** run
- FrameL / libframel (LIGO/Virgo frame I/O) -- build **and** run
- Boost headers only (Boost.uBLAS) -- **build only**
- Cereal headers only (binary serialization) -- **build only**
- CMake >= 3.28, a C++ compiler, pybind11 >= 2.12 -- **build only**

The wheels on PyPI carry GSL, FFTW3 and FrameL inside them, so the list above
matters only when building from source. All of it is on
`conda-forge <https://conda-forge.org>`_.

Installation with pip (Linux)
------------------------------

::

    pip install py4tsa

Wheels are ``manylinux_2_28_x86_64``, for CPython 3.10 to 3.13. Elsewhere pip
builds from the source distribution, which needs the libraries above.

Installation with conda
------------------------

The repository ships a conda recipe under ``conda-recipe/``. From an
activated environment with conda-forge enabled at strict channel priority::

    conda install -n base conda-build
    conda config --add channels conda-forge
    conda config --set channel_priority strict

    PYVER=$(python -c "import sys; print(f'{sys.version_info.major}.{sys.version_info.minor}')")
    conda build conda-recipe/ -c conda-forge --python=$PYVER
    conda install -c conda-forge --use-local py4tsa

Installation with pip (from source)
-------------------------------------

Provide the native dependencies via conda, then build in place::

    conda install -c conda-forge gsl fftw framel libboost-headers cereal cxx-compiler cmake pybind11
    pip install .

Verify the installation
-------------------------

::

    python -c "import py4tsa; print(py4tsa.__file__)"

A path ending in a compiled extension (``.so`` on Linux, ``.pyd`` on
Windows) confirms this is p4TSA's own module, not the unrelated PyPI
``py4tsa`` package (which would show a plain ``.py`` file).

Running the tests
-------------------

::

    pip install pytest
    pytest python-wrapper/tests/ -v

Also run automatically on every push/PR via GitHub Actions -- see
``.github/workflows/ci.yml`` in the repository.

See the repository `README <https://github.com/elenacuoco/p4TSA#readme>`_
for the full, up-to-date instructions (this page mirrors it).
