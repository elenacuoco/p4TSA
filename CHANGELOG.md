# Changelog

## Unreleased

### Changed (behaviour)

- **The default basis competition of `WDF2Classify` changes.** The ten
  candidates a `WDF2Classify` is built with are now, ordered by filter length,
  shortest first (at equal length in the order shown): `Haar`, `DaubC4`,
  `DaubC8`, `Sym4`, `DaubC16`, `Sym8`, `Coif3`, `DaubC24`, `Sym12`, `Coif5`
  (PyWavelets' haar, db2, db4, sym4, db8, sym8, coif3, db12, sym12, coif5).
  Kept from 3.0.0-3.4.0: `Haar`, `DaubC4`, `DaubC8`, `Sym4`, `DaubC16`,
  `Sym8`; added: `Coif3`, `DaubC24`, `Sym12`, `Coif5`; removed from the
  default: `DaubC12`, `DaubC20`, `Coif1`, `Coif2`, which stay available through
  `SetBases`, as do all the long mothers. The order is part of the
  definition: a tie of the window statistic still goes to the later
  candidate, now the longer filter. With the default, trigger values
  (`mWave`, `mSNR`, the coefficients) change: the old competition is
  `SetBases("Haar,DaubC4,DaubC8,DaubC12,DaubC16,DaubC20,Sym4,Sym8,Coif1,Coif2")`.
  The list is defined in one place, `kCandidateBases` in
  `src/WDF2Classify.cpp`. `WDF2Reconstruct` keeps the 3.0.0 list.

### Added

- **Long mothers.** `WaveletType` gains `Sym10`, `Sym12`, `Sym16`, `Sym20`,
  `Coif3`, `Coif4`, `Coif5` and `DaubC24`, `DaubC32`, `DaubC40` (PyWavelets'
  db12, db16, db20; GSL's own centred Daubechies stop at 20 taps), 18 to 40
  taps, centred as `DaubC*`, `Sym*` and `Coif*` are (GSL's offset nc / 2).
  The values are appended after `Sym8`, so the existing ones keep their
  numbers. Every one is a `SetBases` name, as a pyramid or with `P<depth>` as
  a packet level. The taps are PyWavelets' (MIT licence), written at full
  precision by `tools/generate_long_wavelet_tables.py` into
  `src/ExtraWaveletLongTables.inc`; the transform agrees with PyWavelets'
  periodized `dwt` applied after a one-sample circular shift at every split
  to 4e-15, pyramid and packets. PyWavelets' Symlet taps are orthonormal
  only to 2.2e-14 (sym10), 4.4e-14 (sym12), 1.8e-12 (sym16) and 1.4e-11
  (sym20) and are kept as they are; reconstruction is exact to that accuracy
  (worst over N 512-2048 and packet depths up to 7: 6.7e-13, 1.4e-12,
  5.5e-11, 4.3e-10), the Daubechies and Coiflets to 4e-15.

### Added

- **Wavelet-packet bases.** `WaveletTransform(N, wt, packetDepth)` transforms
  a window at the uniform level D of the mother's wavelet-packet tree: 2^D
  bands of width fs / 2^(D+1), N / 2^D coefficients each, written in frequency
  order, band f at indices [f N / 2^D, (f+1) N / 2^D). Every split is GSL's own
  periodized step, so depth 1 is the pyramid's finest step coefficient for
  coefficient, and the level is orthonormal: the inverse reconstructs the
  window and the coefficient energy is its energy. Depth 0 is the pyramid.
  `GetPacketDepth()` and `GetLength()` report the level and the window.
- **`WDF2Classify::SetBases(names)` and `GetBases()`.** The candidates of the
  basis competition are a comma-separated list, in the order they compete (a
  tie goes to the later one): a mother (`Haar`, `DaubC4` to `DaubC20`, `Sym4`,
  `Sym8`, `Coif1`, `Coif2`) for its pyramid, or a mother followed by `P` and a
  depth, as `Coif1P6`, for that packet level. An unknown or repeated name, an
  empty list or a depth above log2 of the window raises `ValueError`. The
  default is the ten pyramid bases of 3.0.0. The winner's name is the trigger's
  `mWave`.
- **The block rule follows the packet layout.**
  `WaveletThreshold::SetLayout(packetDepth)` tells the rule where the runs of
  coefficients lie: at depth 0 the pyramid's levels, index 0, index 1 and
  [2^k, 2^(k+1)), exactly as before; at depth D the 2^D bands. Each run is cut
  into blocks of L from its first index, so no block crosses a band edge.
  `WDF2Classify` sets the layout of each candidate before thresholding it.
  Under the block rule `SetBases` refuses a packet depth whose bands are
  shorter than one block, N / 2^D < L, where the 4.505 calibration of lambda
  does not hold: for a window of 512, L = 6 and depths 1 to 6 are accepted,
  7 to 9 refused. The other rules accept every depth.

### Fixed

- **A copy of `WaveletThreshold` owns its work buffers.** They were raw arrays
  with the compiler's shallow copy, so copying a `WDF2Classify` (its copy
  constructor or `assign`) left two objects freeing the same memory, and the
  process aborted with a double free. They are now `std::vector`s.
- **`WaveletTransform` copies.** The copy constructor and assignment did
  nothing, leaving the GSL handles uninitialized; a copy is now a transform of
  the same length, mother and packet level with handles of its own.
- **`WaveletTransform::WaveletWaveform` inverts at the transform's packet
  level**, rather than always through the pyramid, and frees its buffer with
  `delete[]`. It is now bound in Python and returns the waveform.

### Notes for downstream users

Trigger values do not move: with the default bases every candidate is a
pyramid, whose block ladder is unchanged bit for bit. Once `SetBases` admits
packet bases, `mWave` can carry names such as `Coif1P6`, which a reader must
invert with `WaveletTransform(N, mother, depth)`; a reader that looks the name
up as a `WaveletType` fails on them. `WDF2Reconstruct` keeps its fixed pyramid
candidates.

## 3.3.0

### Added

- Wheels for CPython 3.14.

## 3.2.0

### Added

- **`pip install py4tsa`.** Wheels for CPython 3.10 to 3.13,
  `manylinux_2_28_x86_64`, with GSL, FFTW3 and FrameL inside them, so nothing
  has to be installed first. The build takes FrameL from the system when it is
  there, and otherwise compiles it from its own source
  (git.ligo.org/virgo/virgoapp/Fr, 8.50.2).
- `test_04_frame_io.py`, which reads a frame through `FrameIChannel` and
  checks the samples against an 8 kB fixture.

### Changed

- CMake 3.28 is now the minimum, for `FetchContent`'s `EXCLUDE_FROM_ALL`.
- Wheels are built and tested by a separate workflow, on tags and releases and
  by hand, rather than on every push. Publishing waits for a person.
- Metadata for the index: classifiers, `Source`, `Issues` and `Changelog`
  links, and `requires-python >= 3.10`, the range the wheels are built for.

## 3.1.0

### Changed

- **BREAKING: the Python module is now `py4tsa`, not `pytsa`.** Every
  `import pytsa` / `from pytsa.tsa import ...` becomes `import py4tsa` /
  `from py4tsa.tsa import ...`. The old name on PyPI belongs to an unrelated
  project, which would shadow this extension for anyone holding both. The C++
  library keeps the name p4TSA; the Python module and the distribution name
  change.
- **The block rule is the default of `WDF2Classify`.** A classifier built
  without a thresholding rule used `cuoco`, the universal threshold with the
  sigma given from outside; it now uses `block`. Callers that pass the rule
  explicitly are unaffected.

### Added

- **A block rule for the wavelet coefficients of a window.**
  `WaveletThreshold::block` judges contiguous coefficients of one level
  together (Cai 1999): a block of L is kept whole when its energy exceeds
  lambda L sigma^2, and zeroed whole otherwise, with sigma read from the
  window's median as for the universal threshold. A signal spread over
  neighbouring coefficients, each below sqrt(2 ln N) sigma, survives as a
  block where no single coefficient would; a lone noise excursion does not
  carry its block over the line. `SetBlock(length, lambda)` sets the two
  parameters, defaulting to ln N and 4.505. On the merger window of GW150914
  in H1 the rule keeps 18 coefficients where the universal threshold keeps
  five, twelve of them in 32-128 Hz, and fires on fewer windows of noise at
  the same EnWDF threshold.

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
