//
//
// C++ Implementation: WaveletThreshold.cpp
//
// Description:
//
//
// Author: Elena Cuoco <elena.cuoco@unibo.it>, (C) 2005
//
// Copyright: See COPYING file that comes with this distribution
//
//
//

#include <WaveletThreshold.hpp>

namespace tsa {


    WaveletThreshold::WaveletThreshold(unsigned int N, unsigned int ncoeff, double sigma)
            :
            mAbsCoeff(N),
            mP(N),
            mPAC(1),
            mOrd(N),
            mN(N),
            mMedian(0.0),
            mThresh(0.0),
            mNcoeff(ncoeff),
            mSigma(sigma),
            mlevel(0),
            mC(0.0),
            mBlockLength(0),
            mBlockLambda(4.505),
            mDepth(0) {
    }
    ///
    /// Destructor
    ///

    WaveletThreshold::~WaveletThreshold() {
    }

    void WaveletThreshold::operator()(SeqViewDouble &WT, enum WaveletThresholding t, enum ThresholdingMode m) {
        for (unsigned int i = 0; i < mN; i++) {
            mAbsCoeff[i] = fabs(WT(0, i));
        }
        gsl_sort_index(mP.data(), mAbsCoeff.data(), 1, mN);
        gsl_sort_largest_index(mPAC.data(), 1, mAbsCoeff.data(), 1, mN);
        mlevel = mPAC[0];
        mC = fabs(WT(0, mlevel));
        switch (t) {
            case dohonojohnston: {
                for (unsigned int i = 0; i < mN; i++)
                    mOrd[i] = fabs(WT(0, mP[i]));
                mMedian = gsl_stats_median_from_sorted_data(mOrd.data(), 1, mN);
                mSigma = mMedian / 0.6745;
                mThresh = sqrt(2 * log(mN)) * mSigma;
                switch (m) {
                    case hard: {
                        for (unsigned int i = 0; i < mN; i++) {
                            if (fabs(WT(0, i)) <= mThresh)
                                WT(0, i) = 0.0;
                        }
                    }
                        break;
                    default: {
                        for (unsigned int i = 0; i < mN; i++) {
                            if (fabs(WT(0, i)) < mThresh)
                                WT(0, i) = 0.0;
                            else {
                                if (WT(0, i) >= mThresh)
                                    WT(0, i) = WT(0, i) - mThresh;
                                if (WT(0, i) <= -mThresh)
                                    WT(0, i) = WT(0, i) + mThresh;
                            }
                        }
                    }
                }
                break;
                case cuoco:
                    mThresh = sqrt(2 * log(mN)) * mSigma;
                switch (m) {
                    case hard: {
                        //hard threshold
                        for (unsigned int i = 0; i < mN; i++) {
                            if (fabs(WT(0, i)) <= mThresh)
                                WT(0, i) = 0.0;
                        }

                    }
                        break;
                    default: {
                        //soft threshold
                        for (unsigned int i = 0; i < mN; i++) {
                            if (fabs(WT(0, i)) < mThresh)
                                WT(0, i) = 0.0;
                            else {
                                if (WT(0, i) >= mThresh)
                                    WT(0, i) = WT(0, i) - mThresh;
                                if (WT(0, i) <= -mThresh)
                                    WT(0, i) = WT(0, i) + mThresh;
                            }
                        }

                    }
                }
                break;

                case block:
                    BlockThreshold(WT);
                break;

                default:

                    for (unsigned int i = 0; i < mNcoeff; i++) {
                        WT(0, mP[i]) = 0.0;
                    }

                break;
            }
        }
    }

    void WaveletThreshold::operator()(Dmatrix &WT, enum WaveletThresholding t, enum ThresholdingMode m) {
        for (unsigned int i = 0; i < mN; i++) {
            mAbsCoeff[i] = fabs(WT(0, i));
        }
        gsl_sort_index(mP.data(), mAbsCoeff.data(), 1, mN);
        gsl_sort_largest_index(mPAC.data(), 1, mAbsCoeff.data(), 1, mN);

        mlevel = mPAC[0];

        mC = fabs(WT(0, mlevel));


        switch (t) {
            case dohonojohnston: {
                for (unsigned int i = 0; i < mN; i++)
                    mOrd[i] = fabs(WT(0, mP[i]));
                mMedian = gsl_stats_median_from_sorted_data(mOrd.data(), 1, mN);
                mSigma = mMedian / 0.6745;
                mThresh = sqrt(2 * log(mN)) * mSigma;
                switch (m) {
                    case hard: {
                        for (unsigned int i = 0; i < mN; i++) {
                            if (fabs(WT(0, i)) <= mThresh)
                                WT(0, i) = 0.0;
                        }
                    }
                        break;


                    default: {

                        for (unsigned int i = 0; i < mN; i++) {
                            if (fabs(WT(0, i)) < mThresh)
                                WT(0, i) = 0.0;
                            else {
                                if (WT(0, i) >= mThresh)
                                    WT(0, i) = WT(0, i) - mThresh;
                                if (WT(0, i) <= -mThresh)
                                    WT(0, i) = WT(0, i) + mThresh;
                            }
                        }
                    }
                }
                break;
                case cuoco:
                    mThresh = sqrt(2 * log(mN)) * mSigma;
                switch (m) {
                    case hard: {
                        //hard threshold
                        for (unsigned int i = 0; i < mN; i++) {
                            if (fabs(WT(0, i)) <= mThresh)
                                WT(0, i) = 0.0;
                        }


                    }

                        break;
                    default: {
                        //soft threshold
                        for (unsigned int i = 0; i < mN; i++) {
                            if (fabs(WT(0, i)) < mThresh)
                                WT(0, i) = 0.0;
                            else {
                                if (WT(0, i) >= mThresh)
                                    WT(0, i) = WT(0, i) - mThresh;
                                if (WT(0, i) <= -mThresh)
                                    WT(0, i) = WT(0, i) + mThresh;
                            }
                        }

                    }
                }
                break;

                case block:
                    BlockThreshold(WT);
                break;

                default:

                    for (unsigned int i = 0; i < mNcoeff; i++) {
                        WT(0, mP[i]) = 0.0;
                    }

                break;
            }

        }


    }
}
