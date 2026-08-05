# Changelog

## 2.2.0

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

### Notes for downstream users

Trigger values change. `mSNR` from a run before this release is not comparable
with one after it: it is larger, having lost the window-length division, and no
longer biased low by shrinkage. Thresholds tuned against the old scale must be
re-tuned against a measured background.
