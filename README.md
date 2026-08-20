 # p4TSA — package for Time Series Analysis

[![docs](https://img.shields.io/badge/docs-latest-brightgreen.svg?style=flat)](http://p4tsa.readthedocs.io/en/latest/?badge=latest)
[![CI](https://github.com/elenacuoco/p4TSA/actions/workflows/ci.yml/badge.svg)](https://github.com/elenacuoco/p4TSA/actions/workflows/ci.yml)
[![DOI](https://img.shields.io/badge/DOI-10.5281%2Fzenodo.22030083-blue.svg)](https://doi.org/10.5281/zenodo.22030083)

Contact: info@elenacuoco.com — https://www.elenacuoco.com

`p4TSA` is a spin-off of the C++ *Noise Analysis Package* (NAP). The core is
written in C++ and is exposed to Python through a [pybind11](https://pybind11.readthedocs.io)
binding. The Python interface is called **pyTSA** (you can pronounce it *pi'za*)
and is imported as `pytsa`.

> **`pip install pytsa` is NOT this package.** There is an unrelated project
> also named `pytsa` on PyPI (a Python decorator library, nothing to do with
> time series or gravitational waves). This `pytsa` — p4TSA's own compiled
> extension module — is never published to PyPI; the only correct way to get
> it is building from **this repository's source**, via one of the methods
> below (conda recipe, `pip install .` from a checkout, or a wheel you built
> yourself with `python -m build`). If `import pytsa` behaves unexpectedly,
> check `pip show pytsa` / `python -c "import pytsa; print(pytsa.__file__)"`
> first — a `.py` file instead of a compiled `.so`/`.pyd` means the wrong
> package is installed.

## What is this for?

`p4TSA` is a minimal package of ad-hoc functions to work with time series. It
includes:

- Whitening in the time domain
- Double whitening (equivalent to dividing by the Power Spectral Density) in the
  time domain
- Wavelet decomposition
- Wavelet Detection Filter

## The pipeline that uses it

`p4TSA` is the C++ core. The search pipeline that drives it —
trigger generation and the downstream trigger analysis — is
[**wdflow**](https://github.com/elenacuoco/wdflow), which imports this library
through `pytsa`. `wdflow` supersedes the earlier `wdf` package.

> The two share the top-level module name `wdf`, so **they cannot be installed
> side by side**: whichever `wdf` sits directly in `site-packages` shadows the
> other, including an editable install of `wdflow`. If `import wdf` resolves
> somewhere unexpected, `pip uninstall wdf` removes the legacy package.

## How to cite

**Use of this code in published work requires citation of the following.** A
further paper covering the calibration of the statistic and the parameter
estimation is in preparation and will be added here.

*The Wavelet Detection Filter:*

- E. Cuoco, M. Razzano, A. Utina, *Wavelet-based classification of transient
  signals for gravitational wave detectors*, 26th European Signal Processing
  Conference (EUSIPCO), 2648–2652 (2018).
  [10.23919/EUSIPCO.2018.8553393](https://doi.org/10.23919/EUSIPCO.2018.8553393)

*Time-domain whitening, which this library implements:*

- E. Cuoco *et al.*, *On-line power spectra identification and whitening for the
  noise in interferometric gravitational wave detectors*, Class. Quantum Grav.
  **18**, 1727 (2001).
  [10.1088/0264-9381/18/9/309](https://doi.org/10.1088/0264-9381/18/9/309)
- E. Cuoco *et al.*, *Noise parametric identification and
  whitening for LIGO 40-m interferometer data*, Phys. Rev. D **64**, 122002
  (2001).
  [10.1103/PhysRevD.64.122002](https://doi.org/10.1103/PhysRevD.64.122002)

`CITATION.cff` in this repository carries the same list in machine-readable
form; GitHub's *Cite this repository* button reads it.

## Requirements

`p4TSA` is not a pure-Python package: building it compiles the C++ core into a
single Python extension module. It depends on a few native libraries:

| Library | Role | Needed at |
|---------|------|-----------|
| GSL (+ gslcblas) | linear algebra / numerics | build **and** run |
| FFTW3 (double, float, long-double) | FFTs | build **and** run |
| FrameL / libframel | LIGO/Virgo frame I/O | build **and** run |
| Boost (headers only — Boost.uBLAS) | matrix/vector templates | **build only** |
| Cereal (headers only) | binary serialization (AR/lattice-filter persistence) | **build only** |

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


## Build and install the `pytsa` Python module

The C++ sources are compiled with CMake into a Python extension module named
`pytsa`. Build and install it for the currently active Python environment with:

```bash
conda install -c conda-forge cmake make compilers pybind11 gsl fftw framel libboost-headers cereal

cmake -S . -B build \
  -DCMAKE_BUILD_TYPE=Release \
  -DCMAKE_INSTALL_PREFIX="$CONDA_PREFIX"

cmake --build build -j"$(nproc)"
cmake --install build
```

CMake may install the compiled extension in the environment prefix. Move it to
the active Python `site-packages` directory if necessary:

```bash
PYTHON_SITE=$(python -c "import sysconfig; print(sysconfig.get_paths()['platlib'])")
mv "$CONDA_PREFIX"/pytsa*.so "$PYTHON_SITE"/
```

Verify the installation with:

```bash
python -c "import pytsa; print(pytsa.__file__)"
```

### Reinstalling after changing the C++ sources

A rebuild does not by itself change what `import pytsa` loads. Repeat the build
and install, and check that the module Python resolves is the one just built:

```bash
cmake --build build -j"$(nproc)"
cmake --install build

PYTHON_SITE=$(python -c "import sysconfig; print(sysconfig.get_paths()['platlib'])")
mv "$CONDA_PREFIX"/pytsa*.so "$PYTHON_SITE"/

md5sum build/pytsa*.so "$PYTHON_SITE"/pytsa*.so
```

The two checksums must match. If they differ, the interpreter is still loading
the previous build and any change to the C++ will appear not to have taken
effect -- a failure that looks like a bug in the code rather than in the
install.

A `.so` placed in `site-packages` this way takes precedence over an editable
install (`pip install -e .`), which resolves the module through a `.pth` file
instead. Having both means the copied file wins and rebuilds stop taking effect
silently, so pick one: either move the file after each build, as above, or use
the editable install and delete the copy in `site-packages`.

## Installation with pip

`pip` builds the C++ extension from source, so the native libraries and the
Boost headers must already be present in the environment. The simplest way to
provide them is a conda environment:

```bash
conda install -c conda-forge gsl fftw framel libboost-headers cereal
pip install .
```

To build a wheel instead of installing in place:

```bash
pip install build
python -m build --wheel        # -> dist/p4tsa-2.2.0-*.whl
```

## Running the tests

```bash
pip install pytest
pytest python-wrapper/tests/ -v
```

Runs on every push/PR via [GitHub Actions](.github/workflows/ci.yml) (Python 3.10-3.12).

## Changelog

### 2.2.0 (2026-08-03)

- **Contact info updated**: `elena.cuoco@unibo.it` replacing the retired `ego-gw.it` address
  everywhere it appeared (source headers, README, docs); Giancarlo Cella dropped as a docs team
  contact.
- **Missing docs page added** for `ExtraWaveletFamilies.hpp` (Coiflet/Symlet bases below) —
  it had doxygen comments but no Sphinx page since it was introduced.
- **CI Node.js 20 deprecation cleared**: `actions/checkout` v4→v5, `mamba-org/setup-micromamba`
  v1→v3 (both now Node 24-native).
- **`test_02_persistence.py` no longer depends on `wdf`**: builds its `SeqView` fixture with
  pytsa's own `SeqView_double_t`/`FillPoint` instead of `wdf.structures.array2SeqView`, which
  isn't installed in this repo's CI.
- **WDF trigger SNR statistic fixed**: `EventFullFeatured::mSigma` now exposes the winning
  wavelet basis's own per-window sigma across the C++/Python boundary (was previously
  recomputed downstream from a separate, staler sigma convention). The candidate wavelet-basis
  list dropped the 3 biorthogonal B-spline bases (not L2-energy-preserving, let them win basis
  selection spuriously even on pure noise).
- **Candidate wavelet-basis list redesigned and trimmed** (`WDF2Classify`/`WDF2Reconstruct`,
  19 → 10 bases): dropped redundant plain/centered Daubechies duplicates (same filter taps, just
  phase-shifted), added Coiflet (order 1, 2) and Symlet (order 4, 8) — genuinely new basis
  shapes, plugged into GSL's own extensible `gsl_wavelet_type` mechanism (no new external
  wavelet library, no GSL patching). See `include/ExtraWaveletFamilies.hpp`.
- **`eternity` (1999-2003 vendored XML persistence) removed entirely**, replaced with
  [Cereal](https://uscilab.github.io/cereal/) (header-only, actively maintained; new
  `cereal` conda-forge dependency). See `include/CerealPersistence.hpp`.
- **Legacy pre-packaging-build files removed**: `bind.sh`, `install_dependencies.sh`,
  `install_full_dependencies.sh`, `python-wrapper/CMakeLists.txt` (an orphaned separate build
  script from before this repo's CMake packaging build, unused by it).
- **CI moved from Travis to GitHub Actions** (`.github/workflows/ci.yml`) — Travis's free tier
  for open source was retired years ago, and its old config predated the current build system.

## Contributing

Changes reach `master` through pull requests only, and a pull request merges
only once CI is green. See [`CONTRIBUTING.md`](CONTRIBUTING.md) for how to build
and test locally, what CI checks, and the invariants a change to the detection
filter must preserve.

## Who do I talk to?

- Repo owner / admin: info@elenacuoco.com
- Team contacts: elena.cuoco@unibo.it 


## License

GPL-3.0-or-later. See [`LICENSE`](LICENSE).
