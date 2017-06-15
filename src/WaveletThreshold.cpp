//
//
// C++ Implementation: WaveletThreshold.cpp
//
// Description:
//
//
// Author: Elena Cuoco <elena.cuoco@ego-gw.it>, (C) 2005
//
// Copyright: See COPYING file that comes with this distribution
//
//
//

#include <WaveletThreshold.hpp>

namespace tsa {

    inline unsigned int Min(unsigned int d1, unsigned int d2) {
        return d1 < d2 ? d1 : d2;
    }

    inline unsigned int Max(unsigned int d1, unsigned int d2) {
        return d1 > d2 ? d1 : d2;
    }

    WaveletThreshold::WaveletThreshold(unsigned int N, unsigned int ncoeff, double sigma)
            :
            mN(N),
            mMin(0),
            mMax(0),
            mMedian(0.0),
            mThresh(0.0),
            mNcoeff(ncoeff),
            mSigma(sigma) {
        mAbsCoeff = new double[mN];
        mP = new size_t[mN];
        mPAC = new size_t[1];
        mOrd = new double[mN];
    }
    ///
    /// Destructor
    ///

    WaveletThreshold::~WaveletThreshold() {
        delete[] mAbsCoeff;
        delete[] mP;
        delete[] mPAC;
        delete[] mOrd;
    }

    void WaveletThreshold::operator()(SeqViewDouble &WT, enum WaveletThresholding t, enum ThresholdingMode m) {
        for (unsigned int i = 0; i < mN; i++) {
            mAbsCoeff[i] = fabs(WT(0, i));
        }
        gsl_sort_index(mP, mAbsCoeff, 1, mN);
        gsl_sort_largest_index(mPAC, 1, mAbsCoeff, 1, mN);

        mlevel = mPAC[0];
        unsigned int a;
        unsigned int b;
        unsigned int nc=32;
        a = (mlevel + nc);
        b = (mlevel - nc);
        mMin = Min(a, mN);
        mMax = Max(b, 0);
        mC = fabs(WT(0, mlevel));

        switch (t) {
            case dohonojohnston: {
                for (unsigned int i = 0; i < mN; i++)
                    mOrd[i] = fabs(WT(0, mP[i]));
                mMedian = gsl_stats_median_from_sorted_data(mOrd, 1, mN);
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
                    case local: {
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
                        for (unsigned int i = mMin; i < mN; i++) {
                            WT(0, i) = 0.0;
                        }
                        for (unsigned int i = mMax; i < mlevel; i++) {
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
                    case local: {
                        for (unsigned int i = 0; i < mN; i++) {
                            if (fabs(WT(0, i)) <= mThresh)
                                WT(0, i) = 0.0;
                        }

                        for (unsigned int i = mlevel; i < mMin; i++) {
                            WT(0, i) = 0.0;
                        }
                        for (unsigned int i = mMax; i < mlevel; i++) {
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
        gsl_sort_index(mP, mAbsCoeff, 1, mN);
        gsl_sort_largest_index(mPAC, 1, mAbsCoeff, 1, mN);

        mlevel = mPAC[0];
        unsigned int a;
        unsigned int b;
        unsigned int nc=32;
        a = (mlevel + nc);
        b = (mlevel - nc);
        mMin = Min(a, mN);
        mMax = Max(b, 0);
        mC = fabs(WT(0, mlevel));


        switch (t) {
            case dohonojohnston: {
                for (unsigned int i = 0; i < mN; i++)
                    mOrd[i] = fabs(WT(0, mP[i]));
                mMedian = gsl_stats_median_from_sorted_data(mOrd, 1, mN);
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
                    case local: {
                        for (unsigned int i = 0; i < mN; i++) {
                            if (fabs(WT(0, i)) <= mThresh)
                                WT(0, i) = 0.0;
                        }
                        for (unsigned int i = mMin; i < mN; i++) {
                            WT(0, i) = 0.0;
                        }
                        for (unsigned int i = mMax; i < mlevel; i++) {
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
                    case local: {
                        for (unsigned int i = 0; i < mN; i++) {
                            if (fabs(WT(0, i)) <= mThresh)
                                WT(0, i) = 0.0;
                        }

                        for (unsigned int i = mlevel; i < mMin; i++) {
                            WT(0, i) = 0.0;
                        }
                        for (unsigned int i = mMax; i < mlevel; i++) {
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

                default:

                    for (unsigned int i = 0; i < mNcoeff; i++) {
                        WT(0, mP[i]) = 0.0;
                    }

                break;
            }

        }


    }
}
