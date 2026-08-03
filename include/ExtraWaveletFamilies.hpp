///
///   Copyright (C) 2026 by Elena Cuoco
///   elena.cuoco@unibo.it
///
///   This program is free software; you can redistribute it and/or modify
///   it under the terms of the GNU General Public License as published by
///   the Free Software Foundation; either version 2 of the License, or
///   (at your option) any later version.
///
/// @file   ExtraWaveletFamilies.hpp
/// @author Elena Cuoco <elena.cuoco@unibo.it>
/// @date   2026
///
/// @brief  Coiflet and Symlet orthonormal wavelet families, plugged into
///         GSL's own wavelet-family mechanism (gsl_wavelet_type is a public,
///         pluggable {name, init-callback} struct -- see gsl_wavelet.h) so
///         WaveletTransform can select them exactly like GSL's own built-in
///         Daubechies/Haar/Bspline families, without patching GSL itself or
///         adding a new external wavelet library dependency.
///
///         Coefficients are the standard, published Coiflet/Symlet scaling
///         (low-pass analysis) filters, cross-checked (2026-08-03) against
///         PyWavelets (`pywt.Wavelet(name).filter_bank`, itself the
///         well-established reference implementation) for exact
///         orthonormality: sum(h^2) == 1 and sum(h) == sqrt(2) confirmed to
///         within float64 rounding for every array below. PyWavelets stores
///         filters in the OPPOSITE tap order from GSL's own daubechies.c
///         convention -- confirmed by reversing PyWavelets' db2 and matching
///         GSL's literal h_4/g_4 arrays element-for-element -- so every array
///         below is PyWavelets' filter_bank[0], reversed, not used directly.
///
///         For orthogonal (as opposed to Bspline's biorthogonal) wavelets,
///         analysis and synthesis filters coincide (h1==h2, g1==g2) and the
///         high-pass filter is the standard quadrature-mirror flip of the
///         low-pass one: g[i] = (-1)^i * h[nc-1-i] -- verified against GSL's
///         own h_4/g_4 daubechies tables before being applied here.
///
#ifndef __EXTRAWAVELETFAMILIES_HPP
#define __EXTRAWAVELETFAMILIES_HPP

#include <gsl/gsl_wavelet.h>

namespace tsa {

    extern const gsl_wavelet_type *tsa_wavelet_coiflet_centered;
    extern const gsl_wavelet_type *tsa_wavelet_symlet_centered;

} // namespace tsa

#endif // __EXTRAWAVELETFAMILIES_HPP
