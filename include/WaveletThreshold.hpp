///
///   Copyright (C) 2004 by Elena Cuoco
///   elena.cuoco@ego-gw.it
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
/// @author Elena Cuoco <elena.cuoco@ego-gw.it>
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

        enum WaveletThresholding {
            highest,
            dohonojohnston,
            cuoco
        };

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
        //@}


    protected:

    private:
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
