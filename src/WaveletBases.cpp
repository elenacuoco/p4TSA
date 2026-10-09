//
// C++ Implementation: WaveletBases.cpp
//
// Description: the candidate bases of the WDF basis competition, see
// include/WaveletBases.hpp.
//
// Author: Elena Cuoco <elena.cuoco@unibo.it>, (C) 2026
//
// Copyright: See COPYING file that comes with this distribution
//

#include <WaveletBases.hpp>

#include <cstddef>
#include <stdexcept>
#include <utility>

namespace tsa {

    namespace {
        // The default list, the only place it is defined. All orthonormal
        // (each candidate's statistic is read on its own noise scale, which a
        // non-orthonormal basis does not preserve), all pyramids. Ordered by
        // filter length, shortest first (Haar 2 taps, DaubC4 4, DaubC8 and
        // Sym4 8, DaubC16 and Sym8 16, Coif3 18, DaubC24 and Sym12 24, Coif5
        // 30), Daubechies before Symlet at equal length: a tie of the window
        // statistic goes to the later candidate, the longer filter.
        //
        // - Daubechies, centered only: plain and centered Daubechies of the
        //   same order have the same filter taps, phase-shifted, and the
        //   centered ones have a symmetric time support. DaubC4/8/16/24 are
        //   db2/4/8/12.
        // - Symlets and Coiflets, centered (see ExtraWaveletFamilies.hpp).
        //   Coiflets have vanishing moments for the scaling function too.
        //   PyWavelets' sym12 taps, kept bit for bit, are orthonormal to
        //   4.4e-14.
        // - Haar.
        const char kDefaultBases[] =
            "Haar,DaubC4,DaubC8,Sym4,DaubC16,Sym8,Coif3,DaubC24,Sym12,Coif5";

        // The default list of releases 3.0.0 to 3.3.0.
        const char kLegacyBases[] =
            "Haar,DaubC4,DaubC8,DaubC12,DaubC16,DaubC20,Sym4,Sym8,Coif1,Coif2";

        // Every mother a candidate name may use.
        const std::pair<const char*, enum WaveletTransform::WaveletType> kMothers[] = {
            {"Haar", WaveletTransform::Haar},
            {"DaubC4", WaveletTransform::DaubC4},
            {"DaubC6", WaveletTransform::DaubC6},
            {"DaubC8", WaveletTransform::DaubC8},
            {"DaubC10", WaveletTransform::DaubC10},
            {"DaubC12", WaveletTransform::DaubC12},
            {"DaubC14", WaveletTransform::DaubC14},
            {"DaubC16", WaveletTransform::DaubC16},
            {"DaubC18", WaveletTransform::DaubC18},
            {"DaubC20", WaveletTransform::DaubC20},
            {"DaubC24", WaveletTransform::DaubC24},
            {"DaubC32", WaveletTransform::DaubC32},
            {"DaubC40", WaveletTransform::DaubC40},
            {"Sym4", WaveletTransform::Sym4},
            {"Sym8", WaveletTransform::Sym8},
            {"Sym10", WaveletTransform::Sym10},
            {"Sym12", WaveletTransform::Sym12},
            {"Sym16", WaveletTransform::Sym16},
            {"Sym20", WaveletTransform::Sym20},
            {"Coif1", WaveletTransform::Coif1},
            {"Coif2", WaveletTransform::Coif2},
            {"Coif3", WaveletTransform::Coif3},
            {"Coif4", WaveletTransform::Coif4},
            {"Coif5", WaveletTransform::Coif5},
        };

        // The local cosine prefix; the name never ends in P<digits>, so it
        // never reads as a packet level.
        const char kLocalCos[] = "LocalCos";
    }

    const char* DefaultWaveletBases() {
        return kDefaultBases;
    }

    const char* LegacyWaveletBases() {
        return kLegacyBases;
    }

    WaveletBasis ParseWaveletBasis(const std::string& name, unsigned int window) {
        const std::size_t prefix = sizeof(kLocalCos) - 1;
        if (name.compare(0, prefix, kLocalCos) == 0) {
            const std::string digits = name.substr(prefix);
            if (digits.empty() || digits.size() > 9 || digits[0] == '0' ||
                digits.find_first_not_of("0123456789") != std::string::npos) {
                throw std::invalid_argument("unknown basis " + name +
                                            " (LocalCos takes a segment length, as LocalCos128)");
            }
            const unsigned long M = std::stoul(digits);
            if (M < 2 || (M & (M - 1)) != 0 || M > window) {
                throw std::invalid_argument("the segment length of " + name +
                                            " must be a power of 2 from 2 to the window");
            }
            unsigned int depth = 0;
            while ((1ul << depth) < M) {
                ++depth;
            }
            return WaveletBasis{name, WaveletTransform::LocalCos, depth};
        }
        std::string mother = name;
        unsigned int depth = 0;
        const std::size_t p = name.rfind('P');
        if (p != std::string::npos && p + 1 < name.size() && p > 0 &&
            name.find_first_not_of("0123456789", p + 1) == std::string::npos) {
            mother = name.substr(0, p);
            if (name.size() - p - 1 > 9) {
                throw std::invalid_argument("packet depth of " + name + " exceeds log2 of the window");
            }
            depth = static_cast<unsigned int>(std::stoul(name.substr(p + 1)));
            if (depth == 0) {
                throw std::invalid_argument("packet depth 0 in basis " + name);
            }
        }
        for (const auto& m : kMothers) {
            if (mother == m.first) {
                if (depth >= 8 * sizeof(std::size_t) || (static_cast<std::size_t>(1) << depth) > window) {
                    throw std::invalid_argument("packet depth of " + name + " exceeds log2 of the window");
                }
                return WaveletBasis{name, m.second, depth};
            }
        }
        throw std::invalid_argument("unknown basis " + name + " (only orthonormal mothers are candidates)");
    }

    void CheckWaveletBlocks(const std::vector<WaveletBasis>& bases, unsigned int window,
                            unsigned int blockLength) {
        // Every band (a packet level's) or row (a local cosine's: one DCT-IV
        // bin over the window / M segments) must hold one full block of L,
        // the length lambda is calibrated for: window / 2^D >= L.
        for (const auto& b : bases) {
            if (b.depth > 0 && (window >> b.depth) < blockLength) {
                throw std::invalid_argument("the bands (rows) of basis " + b.name +
                                            " are shorter than one block of the block rule");
            }
        }
    }

    std::vector<WaveletBasis> ParseWaveletBases(const std::string& names, unsigned int window,
                                                unsigned int blockLength) {
        std::vector<WaveletBasis> bases;
        std::size_t start = 0;
        while (start <= names.size()) {
            std::size_t end = names.find(',', start);
            if (end == std::string::npos) {
                end = names.size();
            }
            std::string name = names.substr(start, end - start);
            const std::size_t first = name.find_first_not_of(" \t");
            const std::size_t last = name.find_last_not_of(" \t");
            name = (first == std::string::npos) ? std::string() : name.substr(first, last - first + 1);
            if (!name.empty()) {
                for (const auto& b : bases) {
                    if (b.name == name) {
                        throw std::invalid_argument("basis " + name + " named twice");
                    }
                }
                bases.push_back(ParseWaveletBasis(name, window));
            }
            start = end + 1;
        }
        if (bases.empty()) {
            throw std::invalid_argument("no candidate basis");
        }
        if (blockLength > 0) {
            CheckWaveletBlocks(bases, window, blockLength);
        }
        return bases;
    }

    std::string JoinWaveletBases(const std::vector<WaveletBasis>& bases) {
        std::string out;
        for (std::size_t i = 0; i < bases.size(); ++i) {
            if (i > 0) {
                out += ",";
            }
            out += bases[i].name;
        }
        return out;
    }

    std::unique_ptr<WaveletTransform> MakeWaveletTransform(const WaveletBasis& basis, unsigned int window) {
        return std::unique_ptr<WaveletTransform>(new WaveletTransform(window, basis.type, basis.depth));
    }

} // namespace tsa
