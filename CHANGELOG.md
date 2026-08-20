# Changelog

## 3.0.1

### Fixed

- **The package declares the version it is tagged with.** `pyproject.toml`, the
  conda recipe and the changelog heading still read 2.2.0 when 3.0.0 was tagged,
  so an installed package reported a version its archive was not built from and
  the changelog attributed the trigger-scale changes to a release that predates
  them.

- **`CITATION.cff` carries the author ORCID, the version and the release date.**
  Zenodo builds the record for an archived release from that file; without those
  fields the archived record names an author with no identifier behind it.

## 3.0.0

### Changed

- **`WaveletThreshold` defaults to hard thresholding.** Both `operator()`
  overloads took `ThresholdingMode m = soft`, so every caller that omitted the
  argument -- including `WDF2Classify` -- shrank each surviving coefficient by
  the threshold, biasing amplitudes low by an amount that grows with the number
  of coefficients a signal is spread over. Soft thresholding minimises the mean
  square error of a denoised reconstruction; a detection statistic and a
  parameter estimate are read off the amplitude instead, so the survivors are
  now left unchanged.

- **`WDF2Classify`'s statistic is the coefficient norm on the noise scale.** The
  division by the window length was removed, so `mSNR` is
  `sqrt(sum c_i^2) / sigma`. The candidate bases are orthonormal, so that is the
  matched-filter signal-to-noise ratio of the reconstructed transient, and a
  configured threshold carries the units it appears to have. Previously the
  statistic scaled as the inverse square root of the window length.

- **`WDF2Classify` exports the noise scale that produced the statistic.**
  `EventFullFeatured::mSigma` carries the winning basis's own per-window
  estimate, so a downstream consumer can recompute the signal-to-noise ratio
  under the convention that decided the trigger rather than a separately frozen
  one.

- **The candidate basis list goes from 19 bases to 10.** Plain and centered
  Daubechies of the same order are the same filter taps up to a phase shift, so
  keeping both spent roughly half the list's compute on no real diversity; the
  plain family and every other centered order were dropped. Coiflet (orders 1
  and 2) and Symlet (orders 4 and 8) were added in their place as genuinely
  different shapes -- Symlet only begins to differ from Daubechies at order 4,
  and Coiflet has vanishing moments for the scaling function as well as for the
  wavelet. The biorthogonal B-spline family stays excluded: it is not
  orthonormal, so Parseval does not hold for it and `mSNR` would not be the
  signal-to-noise ratio of the reconstruction.

- **New `ExtraWaveletFamilies.hpp`.** Coiflet and Symlet are plugged into GSL's
  own extensible `gsl_wavelet_type` mechanism rather than by patching GSL or
  taking on another wavelet library. Filter coefficients were cross-checked
  against PyWavelets for orthonormality and for tap order, which the two
  libraries store in opposite conventions.

### Removed

- **`eternity` is gone, replaced by Cereal.** The vendored 1999--2003 XML
  persistence layer was a real compiled dependency, not dead code. All eight
  persistable classes (`ArBurgEstimator`, `LatticeView`, `ARMAView`,
  `DoubleWhitening`, `FifoBuffer`, `LatticeFilter`, `LSLfilter`, `LSLLearning`)
  now use Cereal through the new `CerealPersistence.hpp`, whose
  `DvectorProxy`/`DmatrixProxy`/`VDmatrixProxy` types exist to sidestep a real
  ambiguity: `boost::numeric::ublas` vectors and matrices already carry an
  inherited Boost.Serialization `serialize()` member, which clashes with any
  free save/load pair added for the same type. Save/load round-trips are
  verified byte-exact against freshly estimated filter state. Cereal is a new
  header-only dependency (conda-forge). The legacy ENV_ROOT-era build files,
  unused by the CMake packaging build, were removed at the same time.

### Infrastructure

- **CI moved from Travis to GitHub Actions.** Travis's free tier for open
  source was retired years ago and its configuration predated the current build
  system entirely.

- **The Sphinx documentation build was broken and now works.** `conf.py` used
  an `intersphinx_mapping` shorthand that modern Sphinx rejects outright;
  `docs/requirements.txt` was missing Sphinx itself and the theme; the
  list-form `source_suffix` silently parsed `index.md` as reStructuredText with
  no Markdown parser registered; and `index.md` and `index.rst` both existed as
  master-document candidates, with Sphinx picking the stale one.
  `structure/installation.rst` still described the pre-packaging build.

- **The C++ API reference was rendering empty and now has content.** Doxygen ran
  only on Read the Docs, and `breathe_default_project` named a key that was
  never added to `breathe_projects` anywhere else, so all 66 class pages came
  out blank with one breathe warning each. Doxygen now runs on every build and
  the project key is defined once; `.readthedocs.yaml` installs `doxygen`
  through `apt_packages`, which it was never asked to do, so the published
  pages had no Doxygen XML to render from either. Twelve pages asked
  `doxygenclass` for a class their header does not declare (`tsaTypes`,
  `WindowFactory`, `fparser`, ...) and now use `doxygenfile`; nine pages were
  in no toctree; `armafit.rst` duplicated `ARMAfit.rst`. The build goes from 78
  warnings to 9.

- **Documentation points at `wdflow`, not the retired `wdf`.** `docs/index.rst`
  linked the old project's repository and site, both being retired.
  `README.rst`, an unreferenced duplicate of `README.md` predating the
  PyPI-collision warning and the contact change, was removed.

- **A `.gitignore` covering build artifacts, Python cache and generated docs**
  replaces the previous one-line file.

### Notes for downstream users

Trigger values change. `mSNR` from a run before this release is not comparable
with one after it: it is larger, having lost the window-length division, and no
longer biased low by shrinkage. Thresholds tuned against the old scale must be
re-tuned against a measured background. Triggers also no longer report a
biorthogonal winning basis, and the set of names that can appear in `mWave` is
the ten listed above.

`pytsa` on PyPI is an unrelated package (a Python decorator library). p4TSA's
own `pytsa` module is never published there and is only ever built from this
repository's source; install it with `pip install .` from a checkout, which
builds the extension through scikit-build-core and CMake.
