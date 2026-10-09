///
///   Copyright (C) 2026 by Elena Cuoco
///   elena.cuoco@unibo.it
///
///   This program is free software; you can redistribute it and/or modify
///   it under the terms of the GNU General Public License as published by
///   the Free Software Foundation; either version 2 of the License, or
///   (at your option) any later version.
///
/// @file   WaveletBases.hpp
/// @author Elena Cuoco <elena.cuoco@unibo.it>
/// @date   2026
///
/// @brief  The candidate bases of the WDF basis competition: their names,
///         the default list and the list parser shared by WDF2Classify and
///         WDF2Reconstruct.
///
/// A candidate name is one of:
///
/// - an orthonormal mother, for its pyramidal (Mallat) transform: Haar,
///   DaubC4 to DaubC20 (even lengths), DaubC24, DaubC32, DaubC40, Sym4, Sym8,
///   Sym10, Sym12, Sym16, Sym20, Coif1 to Coif5;
/// - a mother followed by "P" and a depth D >= 1, as "Sym8P6", for the uniform
///   level D of its wavelet-packet tree (see WaveletTransform's packet
///   constructor);
/// - "LocalCos" followed by a segment length M, a power of 2 from 2 to the
///   window, as "LocalCos128", for the orthonormal local cosine basis of
///   segment M (WaveletTransform's LocalCos: Coifman-Meyer bell of half-width
///   M / 2, periodic window edges), with the layout of packet depth log2 M.
///
/// Every candidate is orthonormal and exactly invertible with the
/// WaveletTransform that MakeWaveletTransform builds from it.
///
#ifndef __WAVELETBASES_HPP
#define __WAVELETBASES_HPP

#include <WaveletTransform.hpp>

#include <memory>
#include <string>
#include <vector>

namespace tsa {

    ///
    /// One candidate of the basis competition: its name, its mother (or
    /// LocalCos) and its packet depth, 0 for the pyramidal transform.
    ///
    struct WaveletBasis {
        std::string name;                       ///< the candidate name, as in SetBases
        enum WaveletTransform::WaveletType type; ///< the mother, or LocalCos
        unsigned int depth;                     ///< packet depth (log2 M for LocalCos), 0 for the pyramid
    };

    ///
    /// The default candidate list of WDF2Classify and WDF2Reconstruct,
    /// comma-separated in competition order: Haar, DaubC4, DaubC8, Sym4,
    /// DaubC16, Sym8, Coif3, DaubC24, Sym12, Coif5, ten pyramids ordered by
    /// filter length, shortest first, Daubechies before Symlet at equal
    /// length. A tie of the window statistic goes to the later candidate.
    ///
    const char* DefaultWaveletBases();

    ///
    /// The default candidate list of releases 3.0.0 to 3.3.0: Haar, DaubC4,
    /// DaubC8, DaubC12, DaubC16, DaubC20, Sym4, Sym8, Coif1, Coif2. Passing
    /// it to SetBases reproduces the competition of those releases.
    ///
    const char* LegacyWaveletBases();

    ///
    /// Parse one candidate name for a window of the given length.
    ///
    /// @exception std::invalid_argument on an unknown name, packet depth 0,
    ///            a depth above log2 of the window, or a LocalCos segment
    ///            that is not a power of 2 from 2 to the window
    ///
    WaveletBasis ParseWaveletBasis(const std::string& name, unsigned int window);

    ///
    /// Parse a comma-separated candidate list; blanks around names are
    /// ignored.
    ///
    /// @param names the list
    /// @param window the window length
    /// @param blockLength when non-zero, the block rule's length L: every
    ///        packet band or local cosine row (window / 2^depth
    ///        coefficients) must hold one full block of L
    /// @exception std::invalid_argument on an invalid name, a repeated
    ///            name, an empty list, or a band shorter than blockLength
    ///
    std::vector<WaveletBasis> ParseWaveletBases(const std::string& names, unsigned int window,
                                                unsigned int blockLength = 0);

    ///
    /// Throw std::invalid_argument when a band (row) of a candidate,
    /// window / 2^depth coefficients, is shorter than blockLength.
    ///
    void CheckWaveletBlocks(const std::vector<WaveletBasis>& bases, unsigned int window,
                            unsigned int blockLength);

    /// The names of a candidate list, comma-separated.
    std::string JoinWaveletBases(const std::vector<WaveletBasis>& bases);

    ///
    /// The transform of a candidate on a window: its Forward gives the
    /// coefficients the competition thresholds, its Inverse inverts them
    /// exactly.
    ///
    std::unique_ptr<WaveletTransform> MakeWaveletTransform(const WaveletBasis& basis, unsigned int window);

} // namespace tsa

#endif // __WAVELETBASES_HPP
