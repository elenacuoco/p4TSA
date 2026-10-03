///
///   Copyright (C) 2004 by Elena Cuoco
///   elena.cuoco@unibo.it
///
///   This program is free software; you can redistribute it and/or modify
///   it under the terms of the GNU General Public License as published by
///   the Free Software Foundation; either version 2 of the License, or
///   (at your option) any later version.
///
///   This program is distributed in the hope that it will be useful,
///   but WITHOUT ANY WARRANTY; without even the implied warranty of
///   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
///   GNU General Public License for more details.
///
///   You should have received a copy of the GNU General Public License
///   along with this program; if not, write to the
///   Free Software Foundation, Inc.,
///   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
///
/// @file   WaveletThreshold.hpp
/// @author Elena Cuoco <elena.cuoco@unibo.it>
/// @date   2005
///
/// @brief  Perform the hard and soft Wavelet Threshold
///
#ifndef __WAVELETTHRESHOLD_HPP
#define __WAVELETTHRESHOLD_HPP


///
/// @name System includes
///
//@{


//@}

///
/// @name Project includes
///
//@{

#include <AlgoBase.hpp>
#include <SeqView.hpp>
//@}

///
/// @name Local includes
///
//@{
#include <gsl/gsl_sort.h>
#include <gsl/gsl_statistics.h>

//@}

///
/// @name Forward references
///
//@{


//@}

///
/// namespace
///
#include <algorithm>
#include <cmath>
#include <stdexcept>
#include <vector>

namespace tsa {

    ///
    ///
    ///
    ///
    /// Perform threshold on wavelet coefficients
    ///
    ///

    class WaveletThreshold {
    public:

        ///
        /// How the coefficients of one window are selected.
        ///
        /// @c dohonojohnston keeps each coefficient on its own against the
        /// universal threshold sqrt(2 ln N) sigma, with sigma read from the
        /// median of the window's own coefficients; @c cuoco applies the same
        /// threshold with the sigma given from outside; @c highest keeps the
        /// largest coefficients by count.
        ///
        /// @c block judges contiguous coefficients of one level together
        /// (Cai 1999): a block of L coefficients is kept whole when its
        /// energy exceeds lambda L sigma^2, and zeroed whole otherwise. A
        /// signal spread over neighbouring coefficients, each below the
        /// universal threshold, survives as a block where no single
        /// coefficient would; a lone noise excursion does not carry its
        /// block over the line. sigma is read as for @c dohonojohnston.
        ///
        enum WaveletThresholding {
            highest,
            dohonojohnston,
            cuoco,
            block
        };

        ///
        /// How a coefficient above the threshold is treated.
        ///
        /// @c hard leaves it unchanged, so its amplitude is unbiased and the
        /// energy of the surviving set is the energy of the signal. @c soft
        /// shrinks every survivor by the threshold: that minimises the mean
        /// square error of a denoised reconstruction, but biases amplitudes
        /// low by an amount that grows with the number of coefficients the
        /// signal is spread over.
        ///
        /// A detection statistic and a parameter estimate are both read off
        /// the amplitude, so @c hard is the default.
        ///
        enum ThresholdingMode {
            hard,
            soft
        };
        ///
        /// Constructor
        ///
        WaveletThreshold(unsigned int N, unsigned int ncoeff = 0, double sigma = 1.0);
        ///
        /// Destructor
        ///
        ~WaveletThreshold();

        ///
        /// Copy constructor and assignment: the work buffers are owned by
        /// value, so a copy has its own and shares nothing with the original.
        ///
        WaveletThreshold(const WaveletThreshold&) = default;
        WaveletThreshold& operator=(const WaveletThreshold&) = default;

        ///
        /// @name Operations
        ///
        ///@{

        ///
        /// @brief Brief documentation for the execute method.
        ///
        /// Start of the long documentation for execute method.
        ///
        /// @pre A precondition
        /// @post A postcondition
        /// @exception An exception
        ///
        /// @param a parameter
        ///
        /// @return a returned value
        ///
        /// Declaration of execute operation
        void operator()(SeqViewDouble& WT, enum WaveletThresholding t, enum ThresholdingMode m = hard);
        void operator()(Dmatrix& WT, enum WaveletThresholding t, enum ThresholdingMode m = hard);
        //@}

        ///
        /// @name Getters
        ///
        //@{

        double GetSigma() {
            return mSigma;
        }

        double GetLevel() {
            return mlevel;
        }

        double GetCm() {
            return mC;
        }

        //@}

        ///
        /// @name Setters
        ///
        //@{

        void SetSigma(double sigma) {
            mSigma = sigma;
        }

        ///
        /// The block rule's parameters: the block length in coefficients,
        /// 0 for the natural logarithm of N, Cai's choice, and the energy
        /// threshold in units of L sigma^2, whose calibrated value for that
        /// length is 4.505.
        ///
        void SetBlock(unsigned int length, double lambda) {
            mBlockLength = length;
            mBlockLambda = lambda;
        }

        unsigned int GetBlockLength() {
            return mBlockLength > 0 ? mBlockLength : BlockLengthOf(mN);
        }

        double GetBlockLambda() {
            return mBlockLambda;
        }

        ///
        /// The coefficient layout the block rule cuts into blocks: 0 for the
        /// pyramid, whose levels are index 0, index 1 and [2^k, 2^(k+1)), or
        /// the depth D of a uniform wavelet-packet level, whose 2^D bands are
        /// [f N / 2^D, (f+1) N / 2^D) (see WaveletTransform's packet
        /// constructor). Either way each run is cut into blocks of L from its
        /// first index, so a block never crosses a level or band edge. The
        /// other rules judge coefficients one by one and ignore the layout.
        ///
        /// @exception std::invalid_argument when 2^D exceeds N
        ///
        void SetLayout(unsigned int packetDepth) {
            if (packetDepth >= 8 * sizeof(unsigned int) || (1u << packetDepth) > mN) {
                throw std::invalid_argument("WaveletThreshold: the packet level exceeds log2 of the window length");
            }
            mDepth = packetDepth;
        }

        unsigned int GetLayout() const {
            return mDepth;
        }

        ///
        /// Leave out the coefficients whose tile lies at or below fHz.
        ///
        /// A coefficient is dropped when the upper frequency edge of its run
        /// in the layout (see SetLayout) is <= fHz. That edge is
        /// (fs / 2) e / N, with e the index just past the run: for the
        /// pyramid index 0 reaches fs / 2N, index 1 fs / N and the level
        /// [2^k, 2^(k+1)) reaches 2^k fs / N; for packet depth D (and the
        /// local cosine of segment M = 2^D, whose rows have the same
        /// layout) band f reaches (f + 1) fs / 2^(D+1). At N 1024, fs 2048
        /// and fHz 16 this drops pyramid indices 0-15, packet depth 6 band 0
        /// (16 Hz wide) and LocalCos128 rows 0-1 (8 Hz wide).
        ///
        /// A dropped coefficient is zeroed before thresholding, so it is out
        /// of sigma (the median of |coefficient| is taken over the kept
        /// ones), out of the block rule, out of the largest coefficient
        /// (GetLevel, GetCm) and out of any energy read afterwards (WDF's
        /// EnWDF). The universal threshold of dohonojohnston and cuoco
        /// counts the kept coefficients, sqrt(2 ln n_kept).
        ///
        /// fHz <= 0 switches the cut off (the default): the coefficients go
        /// through the original code path, bit for bit.
        ///
        /// @exception std::invalid_argument when fs <= 0 with fHz > 0, or
        ///            when fHz is at or above fs / 2 (nothing would be kept)
        ///
        void SetMinFrequency(double fHz, double fs) {
            if (fHz > 0.0) {
                if (!(fs > 0.0)) {
                    throw std::invalid_argument("WaveletThreshold: the sampling rate must be positive");
                }
                if (fHz >= 0.5 * fs) {
                    throw std::invalid_argument("WaveletThreshold: the minimum frequency must be below fs / 2");
                }
                mMinFrequency = fHz;
                mFs = fs;
            } else {
                mMinFrequency = 0.0;
                mFs = 0.0;
            }
        }

        double GetMinFrequency() const {
            return mMinFrequency;
        }

        ///
        /// Whether coefficient i is kept under the current layout and
        /// minimum frequency (always true with the cut off).
        ///
        bool IsKept(unsigned int i) const {
            if (mMinFrequency <= 0.0) {
                return true;
            }
            return 0.5 * mFs * static_cast<double>(RunEnd(i)) / static_cast<double>(mN) > mMinFrequency + 1e-9;
        }
        //@}


    protected:

    private:
        static unsigned int BlockLengthOf(unsigned int N) {
            unsigned int L = static_cast<unsigned int>(std::floor(std::log(static_cast<double>(N)) + 0.5));
            return L > 0 ? L : 1;
        }

        ///
        /// The block rule over one coefficient vector, whichever container
        /// holds it: sigma from the median of |coefficient|, then every run
        /// of the layout (see SetLayout) -- for the pyramid index 0, index 1,
        /// then [2^k, 2^(k+1)); for packet depth D the 2^D bands of N / 2^D
        /// -- cut into blocks of L, each kept or zeroed on its energy.
        ///
        template <class Coefficients>
        void BlockThreshold(Coefficients& WT) {
            for (unsigned int i = 0; i < mN; i++)
                mOrd[i] = fabs(WT(0, mP[i]));
            mMedian = gsl_stats_median_from_sorted_data(mOrd.data(), 1, mN);
            mSigma = mMedian / 0.6745;
            BlockRuns(WT);
        }

        ///
        /// The block loop of the block rule, on the sigma already set: every
        /// run of the layout cut into blocks of L, each kept or zeroed on its
        /// energy against lambda L sigma^2.
        ///
        template <class Coefficients>
        void BlockRuns(Coefficients& WT) {
            const unsigned int L = GetBlockLength();
            const double energyPerCoefficient = mBlockLambda * mSigma * mSigma;
            mThresh = energyPerCoefficient;
            unsigned int levelStart = 0, levelSize = (mDepth > 0) ? (mN >> mDepth) : 1;
            while (levelStart < mN) {
                unsigned int levelEnd = std::min(levelStart + levelSize, mN);
                for (unsigned int b = levelStart; b < levelEnd; b += L) {
                    unsigned int e = std::min(b + L, levelEnd);
                    double energy = 0.0;
                    for (unsigned int i = b; i < e; i++)
                        energy += WT(0, i) * WT(0, i);
                    if (energy <= energyPerCoefficient * (e - b)) {
                        for (unsigned int i = b; i < e; i++)
                            WT(0, i) = 0.0;
                    }
                }
                levelStart = levelEnd;
                if (mDepth == 0) {
                    levelSize = (levelStart < 2) ? 1 : levelStart;
                }
            }
        }

        ///
        /// The index just past the run (pyramid level or packet band) that
        /// holds coefficient i.
        ///
        unsigned int RunEnd(unsigned int i) const {
            if (mDepth > 0) {
                const unsigned int band = mN >> mDepth;
                return (i / band + 1) * band;
            }
            if (i < 2) {
                return i + 1;
            }
            unsigned int e = 2;
            while (e <= i) {
                e <<= 1;
            }
            return e;
        }

        ///
        /// Every rule with the minimum frequency on (see SetMinFrequency):
        /// the dropped coefficients are zeroed first, then sigma, the
        /// largest coefficient and the thresholds are read on the kept ones.
        ///
        template <class Coefficients>
        void CutThreshold(Coefficients& WT, enum WaveletThresholding t, enum ThresholdingMode m) {
            unsigned int nk = 0;
            for (unsigned int i = 0; i < mN; i++) {
                if (IsKept(i)) {
                    mOrd[nk++] = fabs(WT(0, i));
                } else {
                    WT(0, i) = 0.0;
                }
            }
            mlevel = 0;
            mC = 0.0;
            for (unsigned int i = 0; i < mN; i++) {
                if (fabs(WT(0, i)) > mC) {
                    mC = fabs(WT(0, i));
                    mlevel = static_cast<int>(i);
                }
            }
            if (nk == 0) {
                mSigma = 0.0;
                return;
            }
            if (t == dohonojohnston || t == block) {
                std::sort(mOrd.begin(), mOrd.begin() + nk);
                mMedian = gsl_stats_median_from_sorted_data(mOrd.data(), 1, nk);
                mSigma = mMedian / 0.6745;
            }
            switch (t) {
                case dohonojohnston:
                case cuoco: {
                    mThresh = sqrt(2 * log(static_cast<double>(nk))) * mSigma;
                    for (unsigned int i = 0; i < mN; i++) {
                        const double a = fabs(WT(0, i));
                        if (m == hard) {
                            if (a <= mThresh)
                                WT(0, i) = 0.0;
                        } else if (a < mThresh) {
                            WT(0, i) = 0.0;
                        } else {
                            WT(0, i) += (WT(0, i) > 0) ? -mThresh : mThresh;
                        }
                    }
                    break;
                }
                case block:
                    BlockRuns(WT);
                    break;
                default: {
                    // highest: zero the mNcoeff smallest kept coefficients
                    for (unsigned int i = 0; i < mN; i++)
                        mAbsCoeff[i] = IsKept(i) ? fabs(WT(0, i)) : -1.0;
                    gsl_sort_index(mP.data(), mAbsCoeff.data(), 1, mN);
                    const unsigned int skip = mN - nk;
                    for (unsigned int i = 0; i < mNcoeff && skip + i < mN; i++)
                        WT(0, mP[skip + i]) = 0.0;
                    break;
                }
            }
        }

        std::vector<double> mAbsCoeff;
        std::vector<size_t> mP;
        std::vector<size_t> mPAC;
        std::vector<double> mOrd;
        unsigned int mN;
        double mMedian;
        double mThresh;
        unsigned int mNcoeff;
        double mSigma;
        int mlevel;
        double mC;
        unsigned int mBlockLength;
        double mBlockLambda;
        unsigned int mDepth; ///< layout of the block rule, 0 for the pyramid
        double mMinFrequency; ///< coefficients at or below it are dropped, 0 for none
        double mFs;           ///< sampling rate the minimum frequency is read with


    };

    ///
    /// @name Inline methods
    ///
    //@{

    //@}


    ///
    /// @name External references
    ///
    //@{

    //@}

} //end namespace

#endif // ___WAVELETTHRESHOLD_HPP
