# Changelog

## 3.4.0

### Changed

- **The default basis competition of `WDF2Classify`.** A classifier is built
  with ten pyramidal candidates ordered by filter length, shortest first:
  `Haar`, `DaubC4`, `DaubC8`, `Sym4`, `DaubC16`, `Sym8`, `Coif3`, `DaubC24`,
  `Sym12`, `Coif5` (PyWavelets' haar, db2, db4, sym4, db8, sym8, coif3, db12,
  sym12, coif5). `DaubC12`, `DaubC20`, `Coif1` and `Coif2` leave the default
  and remain available through `SetBases`. A tie of the window statistic goes
  to the later candidate, so the order is part of the definition. Trigger
  values (`mWave`, `mSNR`, the coefficients) change with the default; the
  previous competition is `SetBases(LegacyWaveletBases())`, that is
  `SetBases("Haar,DaubC4,DaubC8,DaubC12,DaubC16,DaubC20,Sym4,Sym8,Coif1,Coif2")`.
  The list is defined once, `DefaultWaveletBases()` in
  `src/WaveletBases.cpp`.
- **`WDF2Reconstruct` follows the classifier's competition.** It is built
  with the same default list and takes the same names through `SetBases`
  (pyramids, `<mother>P<depth>` packet levels, `LocalCos<M>`), parsed and
  checked by the same code. With the same list, threshold rule and
  parameters, its winner and coefficients equal `WDF2Classify`'s in every
  window (its statistic is half the classifier's, as before). Its trigger
  values change with the default.
- **`WDF2Reconstruct`'s default threshold rule follows the classifier's:**
  `block`, defined once as `DefaultWaveletThresholding()`, instead of
  `cuoco`. `cuoco` and the universal rule `dohonojohnston` stay selectable
  through the constructor. With every default, the reconstructor's winner
  and coefficients equal the classifier's in every window. The output of
  3.3.0 is `WDF2Reconstruct(window, overlap, thresh, sigma, ncoeff,
  WaveletThreshold.cuoco)` followed by `SetBases(LegacyWaveletBases())`.

### Added

- **Wavelet-packet levels.** `WaveletTransform(N, wt, packetDepth)` transforms
  a window at the uniform level D of the mother's wavelet-packet tree: 2^D
  bands of width fs / 2^(D+1), N / 2^D coefficients each, written in
  frequency order, band f at indices [f N / 2^D, (f+1) N / 2^D). Each split
  is GSL's periodized filter step, so depth 1 equals the pyramid's finest
  step and the level is orthonormal. Depth 0 is the pyramid.
  `GetPacketDepth()` and `GetLength()` report the level and the window.
- **Long mothers.** `WaveletType` gains `Sym10`, `Sym12`, `Sym16`, `Sym20`,
  `Coif3`, `Coif4`, `Coif5`, `DaubC24`, `DaubC32` and `DaubC40` (PyWavelets'
  db12, db16, db20), centred as the existing `DaubC*`, `Sym*` and `Coif*`.
  The values are appended after `Sym8`, so existing values keep their
  numbers. The taps are PyWavelets' (MIT licence), written at full precision
  into `src/ExtraWaveletLongTables.inc` by
  `tools/generate_long_wavelet_tables.py`.
- **Local cosine bases and cosine packets** (`include/LocalCosine.hpp`).
  - `LocalCosineTransform(N, M, overlap=M/2, edge=periodic, bell=coifmanMeyer)`:
    the orthonormal local cosine basis of segment length M. The samples about
    every segment edge are folded with a Coifman-Meyer or sine bell, then
    each segment gets an orthonormal DCT-IV. `periodic` window edges fold at
    0 = N, `free` edges do not. `Forward`/`Inverse` are frequency-major (the
    layout of packet depth log2 M); `ForwardSegments`/`InverseSegments` are
    segment-major.
  - `CosinePackets(N, minSegment, maxSegment=N, overlap=minSegment/2, ...)`:
    the dyadic segmentation tree with one bell half-width at every edge, so
    every segmentation made of tree nodes is orthonormal. `BestBasis(x, cost,
    sigma)` is the Coifman-Wickerhauser search for the costs `l1`, `entropy`,
    `wdfUniversal` and `wdfBlock`; `GetSegmentation()` and
    `GetCoefficients()` return the result; `Analyse` and `Inverse` work on
    any segmentation; `SetBlock(length, lambda)` sets the block cost's
    parameters.
  - `WaveletType::LocalCos`: `WaveletTransform(N, LocalCos, D)` is the local
    cosine basis of segment 2^D (Coifman-Meyer, half-width 2^(D-1),
    periodic), with the layout of packet depth D.
- **`WDF2Classify::SetBases(names)` and `GetBases()`.** The candidates of the
  competition as a comma-separated list, in the order they compete: a
  mother for its pyramid, a mother followed by `P<depth>` (as `Sym8P6`) for a
  packet level, or `LocalCos<M>` (as `LocalCos128`) for a local cosine basis.
  An unknown or repeated name, an empty list or a depth above log2 of the
  window raises `ValueError`; under the block rule so does a band shorter
  than one block (N / 2^D < L).
- **The block rule follows the layout.** `WaveletThreshold::SetLayout(depth)`
  makes the block rule cut each packet band (or local cosine row) into blocks
  separately, as it cuts each pyramid level; `WDF2Classify` sets the layout
  of each candidate.
- **`SetMinFrequency(fHz, fs)`** on `WaveletThreshold` and `WDF2Classify`,
  with `GetMinFrequency`, and `WaveletThreshold::IsKept(i)`: a coefficient
  whose run (pyramid level, packet band, local cosine row) has its upper
  frequency edge at or below fHz is zeroed and left out of sigma, of the
  threshold, of the largest coefficient and of EnWDF; the universal threshold
  counts the kept coefficients. Off by default.
- **`SetBlockRemainder(mode)`** on `WaveletThreshold` and `WDF2Classify`,
  with `GetBlockRemainder`, `WaveletThreshold::GetBlockEnergyThreshold(n)`
  and the enum `WaveletThreshold::BlockRemainder`: how the block rule judges a
  block of n < L coefficients. `legacy` (default) judges it against
  lambda n sigma^2 as a full block; `merge` joins a run's remainder to the
  block before it; `scaled` keeps it when its energy exceeds
  Qinv_chi2_n(Q_chi2_L(lambda L)) sigma^2, the false-alarm probability of a
  full block.
- **`WaveletBases.hpp`**: `DefaultWaveletBases()`, `LegacyWaveletBases()`,
  `DefaultWaveletThresholding()`,
  the candidate-name parser `ParseWaveletBasis`/`ParseWaveletBases` and
  `MakeWaveletTransform`, shared by both classes and bound in py4tsa
  (`tsa.DefaultWaveletBases()`, `tsa.LegacyWaveletBases()`,
  `tsa.DefaultWaveletThresholding()`).
- **`WDF2Reconstruct::SetBases(names)`, `GetBases()` and
  `Reconstruct(Ev)`**: the time-domain window of a trigger, its coefficients
  inverted with the transform its `mWave` names; exact for every candidate,
  all of which are orthonormal.
- **`WDF2Classify::SetBlock(length, lambda)`**, with `GetBlockLength` and
  `GetBlockLambda`: the block rule's length (0 for round(ln window)) and
  lambda in every candidate.
- Python bindings for all of the above, `WaveletTransform.WaveletWaveform`
  among them.

### Fixed

- **Copying a `WaveletThreshold`** no longer shares its work buffers; copying
  a `WDF2Classify` (copy constructor or `assign`) ended in a double free.
- **Copying a `WaveletTransform`** gives a transform of the same length,
  mother and level with its own GSL handles; the copy was left uninitialized.
- **`WaveletTransform` resizing** frees the previous GSL workspace.
- **`WaveletTransform::WaveletWaveform`** inverts at the transform's own level
  and frees its buffer with `delete[]`.

### Compatibility

- Existing `WaveletType` values keep their numbers; all new API is additive.
- With every new option at its default, the only changes in trigger values
  are the default basis competition of both classes and the default rule of
  `WDF2Reconstruct`, above. `SetBases(LegacyWaveletBases())` restores the
  previous output of `WDF2Classify`; for `WDF2Reconstruct` pass
  `WaveletThreshold.cuoco` to the constructor as well.
- A reader of `mWave` must handle packet names (`<mother>P<depth>`) and
  `LocalCos<M>` when `SetBases` admits them.

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
