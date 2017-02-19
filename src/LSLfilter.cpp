//
//
// C++ Implementation: LSLLearning.cpp
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

#include <LSLfilter.hpp>


namespace tsa {

    LSLfilter::LSLfilter(LSLLearning& LSL, double lambda, unsigned int size, bool Norm)
    :
    mBuffer(1),
    mWinSize(size),
    mOrder(LSL.GetOrder() + 1),
    mLambda(lambda),
    mSigma(size),
    mNorm(Norm),
    mSigma0(LSL.GetSigma()),
    mFirstCall(true) {
        mEF.resize(2, mOrder);
        mEB.resize(2, mOrder);
        mEpf.resize(2, mOrder);
        mEpb.resize(2, mOrder);
        mKf.resize(mOrder);
        mKb.resize(mOrder);
        mG.resize(mOrder);
        mF0 = LSL.GetStatus();

        for (unsigned int k = 0; k < mOrder; k++) {
            mEB(mF0, k) = LSL.GetErrorBackward(mF0, k);
            mKf(k) = LSL.GetParcorForward(k);
            mKb(k) = LSL.GetParcorBackward(k);
            mG(k) = LSL.GetGamma(k);
            mEpf(mF0, k) = LSL.GetEpf(mF0, k);
            mEpb(mF0, k) = LSL.GetEpb(mF0, k);
        }
    }

    LSLfilter::~LSLfilter() {
    }

    void LSLfilter::SetData(Dmatrix& Data, double scale) {
        mBuffer.AddPoints(Data, scale);
    }
    ///

    int LSLfilter::GetDataNeeded() {
        return mBuffer.Size() - mWinSize;
    }

    ///

    void LSLfilter::GetData(Dmatrix& OutputData) {

        unsigned int f_0 = mF0;
        unsigned int f_1 = 1 - mF0;

        /*--Recursive relation-----------------------------------------------*/

        unsigned int End = mOrder - 1;
        unsigned int End2 = End - 1;

        for (unsigned int l = 0; l < mWinSize; l++) {
            mEB(f_1, 0) = mBuffer(0, l);
            mEF(f_1, 0) = mBuffer(0, l);
            mEpf(f_1, 0) = mLambda * mEpf(f_0, 0) + mBuffer(0, l) * mBuffer(0, l);
            mEpb(f_1, 0) = mLambda * mEpf(f_0, 0) + mBuffer(0, l) * mBuffer(0, l);
            mG(0) = 1.0;

            /*--------*/
            for (unsigned int k = 1; k < mOrder; k++) {
                unsigned int t = k - 1;
                mEpf(f_1, t) = mLambda * mEpf(f_0, t) + mG(t) * mEF(f_1, t) * mEF(f_1, t);
                mEpb(f_1, t) = mLambda * mEpb(f_0, t) + mG(t) * mEB(f_0, t) * mEB(f_0, t);
                mEF(f_1, k) = mEF(f_1, t) + mKf(k) * mEB(f_0, t);
                mEB(f_1, k) = mEB(f_0, t) + mKb(k) * mEF(f_1, t);
                mKf(k) = mKf(k) - mG(t) * mEB(f_0, t) * mEF(f_1, k) / mEpb(f_1, t);
                mKb(k) = mKb(k) - mG(t) * mEF(f_1, t) * mEB(f_1, k) / mEpf(f_1, t);
                mG(k) = mG(t) - (mG(t) * mG(t)) * (mEB(f_0, t) * mEB(f_0, t)) / mEpb(f_1, t);

            }
            OutputData(0, l) = mEF(f_1, End);
            mSigma(l) = sqrt(mEpf(f_1, End2));
            f_1 = 1 - f_1;
            f_0 = 1 - f_0;
        }

        // --- Normalization
        /*  if(mNorm) {
               double mean=0.0;
               for(unsigned int l = 0; l < mWinSize; l++)
                   mean+=OutputData(0,l);

               mean=mean/mWinSize;
               for(unsigned int l = 0; l < mWinSize; l++) {
                   OutputData(0,l)= (OutputData(0,l)-mean)/mSigma(l);

                   }
               } */
        if (mNorm) {
            for (unsigned int l = 0; l < mWinSize; l++)
                OutputData(0, l) /= (mSigma(l) / (1.0 / (1.0 - mLambda)));
        }
        mF0 = f_0;
        mBuffer.DelPoints(mWinSize);
    }

}
