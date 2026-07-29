# p4TSA — package for Time Series Analysis

[![docs](https://img.shields.io/badge/docs-latest-brightgreen.svg?style=flat)](http://p4tsa.readthedocs.io/en/latest/?badge=latest)

Contact: info@elenacuoco.com — https://www.elenacuoco.com

`p4TSA` is a spin-off of the C++ *Noise Analysis Package* (NAP). The core is
written in C++ and is exposed to Python through a [pybind11](https://pybind11.readthedocs.io)
binding. The Python interface is called **pyTSA** (you can pronounce it *pi'za*)
and is imported as `pytsa`.

## What is this for?

`p4TSA` is a minimal package of ad-hoc functions to work with time series. It
includes:

- Whitening in the time domain
- Double whitening (equivalent to dividing by the Power Spectral Density) in the
  time domain
- Wavelet decomposition
- Wavelet Detection Filter

## Requirements

`p4TSA` is not a pure-Python package: building it compiles the C++ core into a
single Python extension module. It depends on a few native libraries:

| Library | Role | Needed at |
|---------|------|-----------|
| GSL (+ gslcblas) | linear algebra / numerics | build **and** run |
| FFTW3 (double, float, long-double) | FFTs | build **and** run |
| FrameL / libframel | LIGO/Virgo frame I/O | build **and** run |
| Boost (headers only — Boost.uBLAS) | matrix/vector templates | **build only** |

All of these are available on **conda-forge**, which is why conda is the
recommended way to install `p4TSA`. FrameL has no PyPI wheel, so a pure `pip`
install from PyPI is not available; `pip` works when the native libraries are
already provided by the environment (see below).

## Installation with conda (recommended)

### Option A — install a pre-built package

If a built package has been published to a conda channel, install it directly
(replace `<channel>` with the channel it was uploaded to):

```bash
conda install -c conda-forge -c <channel> p4tsa
```

The importable module is `pytsa`:

```bash
python -c "import pytsa; print('pyTSA ready')"
```

### Option B — build from source with conda-build

The repository ships a conda recipe under `conda-recipe/`. The native
dependencies live on **conda-forge**, which must be enabled with strict channel
priority, otherwise conda resolves against `defaults` (where `framel`,
`libframel` and `libboost-headers` do not exist).

The build follows the Python of the environment you activate, so `p4tsa` always
matches the interpreter you use — no fixed pin, no version mismatch at install
time.

```bash
# 1. install conda-build in the base environment
conda install -n base conda-build

# 2. enable conda-forge with strict priority (once)
conda config --add channels conda-forge
conda config --set channel_priority strict

# 3. activate the environment you want to use p4tsa in (or create it),
#    then build FOR that environment's Python:
conda activate <your-env>
PYVER=$(python -c "import sys; print(f'{sys.version_info.major}.{sys.version_info.minor}')")
conda build conda-recipe/ -c conda-forge --python=$PYVER

# 4. install into the same environment
conda install -c conda-forge --use-local p4tsa
```

> `--python=$PYVER` compiles the package exactly for the active environment's
> Python. If that environment uses a pre-release Python, conda-forge may not yet
> provide builds of the dependencies — in that case use an environment with a
> stable Python.

## Installation with pip

`pip` builds the C++ extension from source, so the native libraries and the
Boost headers must already be present in the environment. The simplest way to
provide them is a conda environment:

```bash
conda install -c conda-forge gsl fftw framel libboost-headers
pip install .
```

To build a wheel instead of installing in place:

```bash
pip install build
python -m build --wheel        # -> dist/p4tsa-2.1.0-*.whl
```

## Running the tests

```bash
cd test
python test.py
```

## Contributing

- Write tests
- Code review
- Follow the existing style of the C++ core and the pybind11 binding

## Who do I talk to?

- Repo owner / admin: info@elenacuoco.com
- Team contacts: elena.cuoco@ego-gw.it, giancarlo.cella@pi.infn.it,
  fmorawski@camk.edu.pl

## License

GPL-3.0-or-later. See [`LICENSE`](LICENSE).
