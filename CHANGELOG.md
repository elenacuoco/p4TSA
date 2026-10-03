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

- **A remainder option for the block rule: `WaveletThreshold::SetBlockRemainder(mode)`
  and `WDF2Classify::SetBlockRemainder(mode)`** (bound in py4tsa with
  `GetBlockRemainder`, `WaveletThreshold.GetBlockEnergyThreshold(n)` and the
  enum `WaveletThreshold.BlockRemainder`; the setter takes the enum or the
  name). Off by default.
  - The defect: each run (pyramid level, packet band, LocalCos row) is cut into
    blocks of L = round(ln N), and a remainder of n = 1 ... L-1 coefficients,
    like a whole run shorter than L (pyramid levels of 1, 1, 2, 4), was judged
    against the same lambda n sigma^2 as a full block. Its false-alarm
    probability P(chi2_n > lambda n) rises as n falls: 3.4 % for a single
    coefficient (|c| > 2.12 sigma) against 5e-5 for a full block of 7. LocalCos128
    at N 1024 has rows of 8 = 7 + 1, so 128 such single coefficients per window.
  - `legacy` (default): the rule as it was, bit for bit (triggers equal
    d335d33's on white noise and on whitened O1/O2/O4 windows).
  - `merge`: a remainder shorter than L joins the block before it in the same
    run (7 + 1 -> one block of 8, judged against lambda 8 sigma^2). A run
    shorter than L has no block before it and stays one short block.
  - `scaled`: the partition of legacy, but a block of n < L is kept when its
    energy exceeds Qinv_{chi2_n}(Q_{chi2_L}(lambda L)) sigma^2, the chi-square
    quantile at the full block's false-alarm probability (L 7, lambda 4.505:
    p = 4.95e-5, a single coefficient needs |c| > 4.06 sigma).
  - Per-window firing rate at threshold 5, N 1024, white noise, 50 176 windows:
    D0 (default ten bases) 0.061 legacy, 0.054 merge, 0.056 scaled;
    D0 + LocalCos128 0.557 legacy, 0.057 merge, 0.065 scaled.
  - With sigma read from the window's MAD, at lambda 4.505 the full block
    fires at 7.1e-5 and a scaled single coefficient at 5.4e-5 (3.84 M blocks
    each); the chi-square match is exact for a known sigma, and the MAD
    scatter inflates the full block's steeper tail more.

- **A low-frequency cut in the threshold: `WaveletThreshold::SetMinFrequency(fHz, fs)`
  and `WDF2Classify::SetMinFrequency(fHz, fs)`** (bound in py4tsa, with
  `GetMinFrequency` and `WaveletThreshold.IsKept(i)`).
  - A coefficient is dropped when the upper frequency edge of its run in the
    layout is <= fHz. The edge is (fs / 2) e / N, with e the index just past
    the run: pyramid levels {0}, {1}, [2^k, 2^(k+1)); packet bands of depth D;
    LocalCos M rows (depth log2 M, row width fs / 2M). At N 1024, fs 2048 and
    16 Hz it drops pyramid indices 0-15, packet depth 6 band 0 and LocalCos128
    rows 0-1.
  - Dropped coefficients are zeroed before thresholding: out of sigma (median
    of |c| over the kept ones / 0.6745), out of the block rule, out of the
    largest coefficient (`GetLevel`, `GetCm`) and out of WDF's window
    statistic (EnWDF); the trigger holds zeros there. The universal threshold
    (`dohonojohnston`, `cuoco`) counts the kept coefficients,
    sqrt(2 ln n_kept).
  - Why: on real O4/O2/O1 data the 0-16 Hz levels of a full-band whitened
    stream carry seismic residuals that fire windows by themselves. Cutting
    them halved the H1-L1 time-slide pair rate on three events at no loss on
    GW150914 (catalogue study of 3 Oct 2026, done with a numpy port; this is
    that port in C++).
  - Off by default (fHz <= 0): the code path is the original one, and the
    triggers equal those of acedc0d bit for bit (checked on 6400 real
    whitened windows of GW150914 and GW170817, H1 and L1, with the default
    list and with the default list plus LocalCos128). With 16 Hz on the same
    windows, winner and EnWDF equal the catalogue port to 3.6e-15.
  - Tests: `python-wrapper/tests/test_08_min_frequency.py` (the kept mask per
    layout, the threshold and the competition against a numpy reference for
    both rules, the off switch bit for bit, copies, invalid arguments).

- **Local cosine bases and cosine packets** (`include/LocalCosine.hpp`).
  - `LocalCosineTransform(N, M, overlap=M/2, edge=periodic, bell=coifmanMeyer)`
    is the orthonormal local cosine basis of segment length M, a power of 2
    that divides N. At every segment edge the 2 eps samples about the edge
    are folded with the cut-off r(t) = sin(pi/4 (1 + beta(t))), sampled at
    t = (j + 1/2)/eps. The Coifman-Meyer bell takes beta to be
    sin(pi t / 2) iterated three times; the `sine` bell takes beta(t) = t
    (the MDCT window). eps <= M/2.
  - Each segment then gets its DCT-IV: FFTW_REDFT11 scaled by 1/sqrt(2M),
    that is sqrt(2/M) sum y_n cos(pi/M (n + 1/2)(k + 1/2)). It is
    orthonormal and its own inverse.
  - Window edges. `periodic` also folds at 0 = N, wrapping round, as the
    periodized DWT treats the window as a circle. `free` puts no bell at 0
    and N (the classic basis of an interval). Both are orthonormal.
  - Layout. `Forward`/`Inverse` are frequency-major: index k N/M + j is
    bin k of segment j, the layout of a packet level of depth log2 M.
    `ForwardSegments`/`InverseSegments` are segment-major.
  - These are the conventions of the catalogue's `scripts/bases_windows.py`
    (`bell`, `local_cosine`): bell, fold signs, half-width M/2 and
    bin-major layout. The two agree to 1.8e-15 for M 32-512 at N 512-2048.
    `free`, and eps < M/2 for the `sine` bell, are additions.
  - `CosinePackets(N, minSegment, maxSegment=N, overlap=minSegment/2, ...)`
    holds the dyadic segmentation tree of the window, segments maxSegment
    down to minSegment. Every edge has the same bell half-width, so any
    segmentation made of tree nodes is an orthonormal basis.
  - `BestBasis(x, cost, sigma)` is Coifman-Wickerhauser's bottom-up search
    for the minimum of an additive cost; a node splits only when its
    children cost strictly less. The costs:
    - `l1`: sum |c|;
    - `entropy`: -sum p ln p, p = c^2/|x|^2;
    - `wdfUniversal`: WDF's statistic as a negative gain,
      -sum (c/sigma)^2 over |c| > sqrt(2 ln N) sigma;
    - `wdfBlock`: -kept energy/sigma^2 of the block rule run along each
      segment's bins, L = round(ln N), lambda 4.505.

    sigma <= 0 takes median |c|/0.6745 of the finest level. With segments
    1024 down to 64 and eps 32, the WDF costs reproduce the segmentation of
    the catalogue's `cospkt_best` (`scripts/single_chirp_optimal.py`,
    sigma "mad") for every window tested.
  - Results: `GetSegmentation()` (lengths in time order) and
    `GetCoefficients()` (segment by segment, bins in frequency order).
    `Analyse`/`Inverse` work for any segmentation, and the node and best
    costs can be read.
- **`LocalCos<M>` candidates in the basis competition.**
  - `WaveletType` gains `LocalCos`, appended so the other values keep their
    numbers. `WaveletTransform(N, LocalCos, D)` is the local cosine basis of
    segment 2^D: Coifman-Meyer, eps = M/2, periodic, frequency-major.
  - `GetPacketDepth()` = D gives the threshold the packet layout it needs,
    so every rule, sigma and EnWDF work unchanged.
  - `SetBases` accepts `LocalCos64`, `LocalCos128`, ...: a power of 2 from 2
    to the window. The name never ends in `P<digits>`. None is in the
    default list.
  - Under the block rule each row of N/M coefficients must hold one block of
    L = round(ln N), so M <= N/L: 64 at N 512, 128 at N 1024, 256 at N 2048.
- **Why the 2006 DCT failed as a candidate** (`DCT.hpp`, removed from
  `WDF2Classify` in adfaffa).
  - It was a global DCT-II (FFTW_REDFT10) over the whole window. It had no
    time localisation: every coefficient spans the window.
  - It was not orthonormal. The window was first tapered by
    `Cs2HammingWindow`. FFTW's unnormalised REDFT10 (2 sum ...) was then
    rescaled by sqrt(2/N), with an extra sqrt(1/2) on the DC bin: twice the
    orthonormal scale. `DCT::operator()` sets the scale to Sampling/Size.
  - So sigma and EnWDF were not on the wavelets' noise scale, and the
    competition was not fair.
  - It had no bells and no folding. The local cosine above is what that
    candidate should have been: windowed without losing orthonormality, and
    local in time.

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

### Caveat for wdflow (not changed here)

- wdflow reads a trigger's layout only from `mWave`, through
  `wdf/analysis/wavelets.py packet_depth` (wdflow-packets). Today it reads
  `LocalCos128` as a pyramid: every tile is placed silently on the pyramid's
  geometry.
- `reconstruction.py` does `getattr(WaveletTransform, "LocalCos128")`, which
  raises.
- Before a `LocalCos<M>` trigger reaches wdflow, two changes are needed:
  - `packet_depth` must return log2 M for `LocalCos<M>`; the tile layout is
    then the depth-D packet one, with the nominal supports ignoring the
    +-M/2 bell overlap;
  - reconstruction must use `WaveletTransform(n, LocalCos, log2 M)`.

### Not implemented: adaptive cosine packets in the competition

A best-basis segmentation chosen per window gives rows of different lengths
(segment m has m bins), which a single depth cannot describe. It would need
the following.

- **`WaveletThreshold`.** The layout becomes an explicit list of runs
  (start, length) rather than a depth, e.g. `SetLayout(std::vector<run>)`.
  - `BlockThreshold` already loops over runs from a generator, so only the
    generator changes.
  - A run is either one segment's bins (blocks along frequency, as the
    catalogue's `cospkt` and `CosinePackets::wdfBlock` do), or one bin
    across consecutive segments of equal length. That has to be decided.
  - sigma (median over all N) and the universal rule are unaffected.
- **`WDF2Classify`.**
  - A candidate kind holding a `CosinePackets` whose forward step chooses the
    segmentation (`BestBasis` with the cost of the rule in force) and returns
    its runs. `GetDataVector` calls `SetLayout(runs)` for it instead of
    `SetLayout(GetPacketDepth())`.
  - Since `Forward`/`Inverse` are not virtual, `mBases` would need a variant
    or a small interface over `WaveletTransform`.
  - The block-length check moves to minSegment: each run must hold a block.
  - The choice is a second search inside a candidate, so the EnWDF it
    competes with is a maximum over segmentations. Its noise distribution
    differs from that of a fixed basis, and the threshold would need
    recalibrating.
- **Trigger schema.**
  - `mWave` is today the whole layout contract; `mlevel` is the index of the
    largest coefficient and carries no layout.
  - The segmentation (lengths in time order) must travel with the event:
    either a new `EventFullFeatured` field (vector of lengths, bound in
    py4tsa and mirrored in wdflow's `eventPE` and its Arrow schema), or
    encoded in the name (`CosPkt64:256/64/64/128/512`).
- **wdflow geometry.**
  - `coeff_levels`, `coeff_freq_bands` and `coeff_time_bounds` (wavelets.py)
    assume rows of `n >> depth`. They need a segmentation branch: segment
    start a and length m, bin k gives [a, a+m)/fs x [k, k+1) fs/(2m).
  - The integer-depth group and cache keys in `detector_graph.py` and
    `scale.py` become the segmentation, or the `wave` string.
  - Reconstruction calls `CosinePackets.Inverse(c, segmentation)`.
  - Everything downstream of the tile edges (`ladder_rows`, ridge,
    pixel graph, wavegram match) is already layout-agnostic.

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
