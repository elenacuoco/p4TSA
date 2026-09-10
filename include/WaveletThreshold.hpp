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
        //@}


    protected:

    private:
        static unsigned int BlockLengthOf(unsigned int N) {
            unsigned int L = static_cast<unsigned int>(std::floor(std::log(static_cast<double>(N)) + 0.5));
            return L > 0 ? L : 1;
        }

        ///
        /// The block rule over one coefficient vector, whichever container
        /// holds it: sigma from the median of |coefficient|, then every
        /// level of the dyadic ladder -- index 0, index 1, then [2^k, 2^(k+1))
        /// -- cut into blocks of L, each kept or zeroed on its energy.
        ///
        template <class Coefficients>
        void BlockThreshold(Coefficients& WT) {
            for (unsigned int i = 0; i < mN; i++)
                mOrd[i] = fabs(WT(0, mP[i]));
            mMedian = gsl_stats_median_from_sorted_data(mOrd, 1, mN);
            mSigma = mMedian / 0.6745;
            const unsigned int L = GetBlockLength();
            const double energyPerCoefficient = mBlockLambda * mSigma * mSigma;
            mThresh = energyPerCoefficient;
            unsigned int levelStart = 0, levelSize = 1;
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
                levelSize = (levelStart < 2) ? 1 : levelStart;
            }
        }

        double * mAbsCoeff;
        size_t * mP;
        size_t * mPAC;
        double * mOrd;
        unsigned int mN;
        double mMedian;
        double mThresh;
        unsigned int mNcoeff;
        double mSigma;
        int mlevel;
        double mC;
        unsigned int mBlockLength;
        double mBlockLambda;


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
