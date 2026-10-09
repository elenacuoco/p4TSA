 # p4TSA — package for Time Series Analysis

[![PyPI](https://img.shields.io/pypi/v/py4tsa.svg)](https://pypi.org/project/py4tsa/)
[![docs](https://img.shields.io/badge/docs-latest-brightgreen.svg?style=flat)](http://p4tsa.readthedocs.io/en/latest/?badge=latest)
[![CI](https://github.com/elenacuoco/p4TSA/actions/workflows/ci.yml/badge.svg)](https://github.com/elenacuoco/p4TSA/actions/workflows/ci.yml)
[![DOI](https://img.shields.io/badge/DOI-10.5281%2Fzenodo.22030083-blue.svg)](https://doi.org/10.5281/zenodo.22030083)

Contact: info@elenacuoco.com — https://www.elenacuoco.com

`p4TSA` is a spin-off of the C++ *Noise Analysis Package* (NAP). The core is
written in C++ and is exposed to Python through a [pybind11](https://pybind11.readthedocs.io)
binding. The Python interface is called **py4TSA** (you can still pronounce it
*pi'za*) and is imported as `py4tsa`.

> **The module used to be called `pytsa`.** That name on PyPI belongs to an
> unrelated project, so change any `import pytsa` to `import py4tsa`.

## What is this for?

`p4TSA` is a minimal package of ad-hoc functions to work with time series. It
includes:

- Whitening in the time domain
- Double whitening (equivalent to dividing by the Power Spectral Density) in the
  time domain
- Wavelet decomposition: pyramidal transforms, uniform wavelet-packet levels
  and orthonormal local cosine bases
- Cosine packets with the Coifman-Wickerhauser best-basis search
- Wavelet Detection Filter

## The WDF basis competition

`WDF2Classify` transforms every window in each candidate basis, thresholds
the coefficients on the window's own noise scale and keeps the candidate with
the largest thresholded energy; the winner's name is the trigger's `mWave`.

```python
from py4tsa import tsa

fs, n = 2048.0, 1024
wdf = tsa.WDF2Classify(n, 0, 5.0, 1.0, n, tsa.WaveletThreshold.block)
wdf.GetBases()      # 'Haar,DaubC4,DaubC8,Sym4,DaubC16,Sym8,Coif3,DaubC24,Sym12,Coif5'
wdf.SetBases(wdf.GetBases() + ",Sym8P6,LocalCos128")
wdf.SetMinFrequency(16.0, fs)      # coefficients at or below 16 Hz leave the statistic
wdf.SetBlockRemainder("merge")     # how blocks shorter than L are judged
wdf.SetBlock(0, 4.505)             # block length (0: round(ln n)) and lambda
```

- **Candidate names** (`SetBases`, comma-separated, in the order they
  compete; a tie goes to the later one):
  - a mother for its pyramidal transform: `Haar`, `DaubC4` to `DaubC20`,
    `DaubC24`, `DaubC32`, `DaubC40`, `Sym4`, `Sym8`, `Sym10`, `Sym12`,
    `Sym16`, `Sym20`, `Coif1` to `Coif5`;
  - a mother followed by `P` and a depth D, as `Sym8P6`, for the uniform level
    D of its wavelet-packet tree: 2^D bands of width fs / 2^(D+1), written in
    frequency order;
  - `LocalCos` followed by a segment length M, a power of 2, as `LocalCos128`,
    for the orthonormal local cosine basis of segment M (Coifman-Meyer bell of
    half-width M / 2, periodic window edges), written with the layout of the
    packet level of depth log2 M.

  Under the block rule a packet band, or a local cosine row, must hold one
  full block of L = round(ln n) coefficients: n / 2^D >= L.
- **`SetMinFrequency(fHz, fs)`** drops every coefficient whose band lies at or
  below fHz from sigma, from the threshold and from the statistic; 0 (the
  default) keeps every coefficient.
- **`SetBlockRemainder(mode)`** sets how the block rule judges a block of n < L
  coefficients at the end of a run: `"legacy"` (default) against lambda n
  sigma^2 as a full block, `"merge"` joined to the block before it, `"scaled"`
  at the false-alarm probability of a full block.
- **`SetBlock(length, lambda)`** sets the block length L (0 for round(ln n))
  and lambda (default 4.505) in every candidate.
- The default list is `tsa.DefaultWaveletBases()`.
  `SetBases(tsa.LegacyWaveletBases())` restores the competition of releases
  3.0.0 to 3.3.0.

`WDF2Reconstruct` runs the same competition: the same default list, the same
names through `SetBases`, and, with the same threshold rule, the same winner
and coefficients in every window. `Reconstruct(ev)` returns a trigger's
window in the time domain, its coefficients inverted with the transform its
`mWave` names:

```python
rec = tsa.WDF2Reconstruct(n, 0, 5.0, 1.0, n, tsa.WaveletThreshold.block)
rec.SetBases(wdf.GetBases())
# ... rec << data; while rec.GetDataNeeded() >= 0: if rec(ev): ...
waveform = rec.Reconstruct(ev)     # numpy array of n samples
```

The transforms are also available on their own:

```python
import numpy as np

x = np.random.default_rng(1).normal(size=n)

lc = tsa.LocalCosineTransform(n, 128)        # segment 128, bell half-width 64
c = lc.Forward(x)                            # frequency-major coefficients
x_back = lc.Inverse(c)

cp = tsa.CosinePackets(n, 64)                # segments n down to 64
cp.BestBasis(x, tsa.CosinePackets.wdfBlock)  # or l1, entropy, wdfUniversal
seg = cp.GetSegmentation()                   # segment lengths in time order
c = cp.GetCoefficients()
x_back = cp.Inverse(c, seg)                  # Analyse(x, seg) gives c back
```

## The pipeline that uses it

`p4TSA` is the C++ core. The search pipeline that drives it —
trigger generation and the downstream trigger analysis — is
[**wdflow**](https://github.com/elenacuoco/wdflow), which imports this library
through `py4tsa`. `wdflow` supersedes the earlier `wdf` package.

> The two share the top-level module name `wdf`, so **they cannot be installed
> side by side**: whichever `wdf` sits directly in `site-packages` shadows the
> other, including an editable install of `wdflow`. If `import wdf` resolves
> somewhere unexpected, `pip uninstall wdf` removes the legacy package.

## How to cite

**Use of this code in published work requires citation of the following.**

*The Wavelet Detection Filter:*

- E. Cuoco, *The Wavelet Detection Filter: A Real Time Unmodeled Pipeline for
  Gravitational Wave Transients, Ranking Coincidences with a Graph Neural
  Network*, arXiv:2609.12797 (2026).
  [arxiv.org/html/2609.12797v1](https://arxiv.org/html/2609.12797v1),
  [10.48550/arXiv.2609.12797](https://doi.org/10.48550/arXiv.2609.12797)
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

The wheels on PyPI carry GSL, FFTW3 and FrameL inside them, so this table
matters only when building from source. All of it is on **conda-forge**.

## Installation with pip (Linux)

```bash
pip install py4tsa
python -c "import py4tsa; print(py4tsa.__file__)"
```

The wheels are `manylinux_2_28_x86_64`, for CPython 3.10 to 3.14.

Elsewhere — macOS, Windows, another architecture — pip falls back to the
source distribution, which compiles the C++ core and needs the libraries
above; use conda there.

## Installation with conda

### Option A — install a pre-built package

If a built package has been published to a conda channel, install it directly
(replace `<channel>` with the channel it was uploaded to):

```bash
conda install -c conda-forge -c <channel> py4tsa
```

The importable module is `py4tsa`:

```bash
python -c "import py4tsa; print('py4TSA ready')"
```

### Option B — build from source with conda-build

The repository ships a conda recipe under `conda-recipe/`. The native
dependencies live on **conda-forge**, which must be enabled with strict channel
priority, otherwise conda resolves against `defaults` (where `framel`,
`libframel` and `libboost-headers` do not exist).

The build follows the Python of the environment you activate, so `py4tsa` always
matches the interpreter you use — no fixed pin, no version mismatch at install
time.

```bash
# 1. install conda-build in the base environment
conda install -n base conda-build

# 2. enable conda-forge with strict priority (once)
conda config --add channels conda-forge
conda config --set channel_priority strict

# 3. activate the environment you want to use py4tsa in (or create it),
#    then build FOR that environment's Python:
conda activate <your-env>
PYVER=$(python -c "import sys; print(f'{sys.version_info.major}.{sys.version_info.minor}')")
conda build conda-recipe/ -c conda-forge --python=$PYVER

# 4. install into the same environment
conda install -c conda-forge --use-local py4tsa
```

> `--python=$PYVER` compiles the package exactly for the active environment's
> Python. If that environment uses a pre-release Python, conda-forge may not yet
> provide builds of the dependencies — in that case use an environment with a
> stable Python.


## Build and install the `py4tsa` Python module

The C++ sources are compiled with CMake into a Python extension module named
`py4tsa`. Build and install it for the currently active Python environment with:

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
mv "$CONDA_PREFIX"/py4tsa*.so "$PYTHON_SITE"/
```

Verify the installation with:

```bash
python -c "import py4tsa; print(py4tsa.__file__)"
```

### Reinstalling after changing the C++ sources

A rebuild does not by itself change what `import py4tsa` loads. Repeat the build
and install, and check that the module Python resolves is the one just built:

```bash
cmake --build build -j"$(nproc)"
cmake --install build

PYTHON_SITE=$(python -c "import sysconfig; print(sysconfig.get_paths()['platlib'])")
mv "$CONDA_PREFIX"/py4tsa*.so "$PYTHON_SITE"/

md5sum build/py4tsa*.so "$PYTHON_SITE"/py4tsa*.so
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
python -m build --wheel        # -> dist/py4tsa-3.3.0-*.whl
```

## Running the tests

```bash
pip install pytest
pytest python-wrapper/tests/ -v
```

The cross-checks of the long mothers against PyWavelets run when `PyWavelets`
is installed. The real-data regression digests of the block rule run when
`P4TSA_WHITENED_STREAMS` names a directory of whitened strain windows, and are
skipped otherwise.

Runs on every push/PR via [GitHub Actions](https://github.com/elenacuoco/p4TSA/blob/master/.github/workflows/ci.yml) (Python 3.10-3.12).

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
  py4tsa's own `SeqView_double_t`/`FillPoint` instead of `wdf.structures.array2SeqView`, which
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
only once CI is green. See [`CONTRIBUTING.md`](https://github.com/elenacuoco/p4TSA/blob/master/CONTRIBUTING.md) for how to build
and test locally, what CI checks, and the invariants a change to the detection
filter must preserve.

## Who do I talk to?

- Repo owner / admin: info@elenacuoco.com
- Team contacts: elena.cuoco@unibo.it 


## License

GPL-3.0-or-later. See [`LICENSE`](https://github.com/elenacuoco/p4TSA/blob/master/LICENSE).
