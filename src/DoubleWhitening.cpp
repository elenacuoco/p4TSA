//
//
// C++ Implementation: DoubleWhitening.cpp
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

#include <DoubleWhitening.hpp>

namespace tsa {

    DoubleWhitening::DoubleWhitening(Dvector &ParcorF, Dvector &ParcorB, Dmatrix &ErrF, Dmatrix &ErrB,
                                     unsigned int OutputSize, unsigned int ExtraSize)
            :
            mBuffer(1),
            mFirstCall(true),
            mOutputSize(OutputSize),
            mTotSize(ExtraSize + OutputSize),
            mOrder(ParcorF.size()),
            mParcorF(ParcorF),
            mParcorB(ParcorB),
            mErrF(ErrF),
            mErrB(ErrB),
            mStatus(0),
            mEf(2, mOrder),
            mEb(2, mOrder),
            mWhitened(1, mTotSize) {
    }

    DoubleWhitening::DoubleWhitening(LatticeView &LV, unsigned int OutputSize, unsigned int ExtraSize)
            :
            mBuffer(1),
            mFirstCall(true),
            mOutputSize(OutputSize),
            mTotSize(ExtraSize + OutputSize),
            mOrder(LV.GetParcorF()->size()),
            mParcorF(*LV.GetParcorF()),
            mParcorB(*LV.GetParcorB()),
            mErrF(*LV.GetErrorForward()),
            mErrB(*LV.GetErrorBackward()),
            mStatus(0),
            mEf(2, mOrder),
            mEb(2, mOrder),
            mWhitened(1, mTotSize) {
            }

    void DoubleWhitening::init(LatticeView &LV) {
        mOrder = LV.GetParcorF()->size();
        mParcorF = *LV.GetParcorF();
        mParcorB = *LV.GetParcorB();
        mErrF = *LV.GetErrorForward();
        mErrB = *LV.GetErrorBackward();
        mStatus = 0;
        mFirstCall=true;
    }

    DoubleWhitening::~DoubleWhitening() {

    }

    void DoubleWhitening::SetData(Dmatrix &Data, double scale) {
        mBuffer.AddPoints(Data, scale);
    }
  

    void DoubleWhitening::GetData(Dmatrix &DWOutput) {
        int F0 = mStatus;
        int F1 = 1 - mStatus;
        unsigned int t;
        unsigned int End = mOrder - 1;

        mEf.clear();
        mEb.clear();

        if (mTotSize > mBuffer.Size()) {
            LogWarning("Not enough data points");
            throw no_data_available("DoubleWhitening::GetData ->No data available");
        }


        for (unsigned int i = 0; i < mOutputSize; i++) {

            mErrF(F1, 0) = mBuffer(0, i);
            mErrB(F1, 0) = mBuffer(0, i);

            for (unsigned int k = 1; k < mOrder; k++) {
                t = k - 1;
                mErrF(F1, k) = mErrF(F1, t) - mParcorF(k) * mErrB(F0, t);
                mErrB(F1, k) = mErrB(F0, t) - mParcorB(k) * mErrF(F1, t);
            }

            mWhitened(0, i) = mErrF(F1, End);
            F0 = 1 - F0;
            F1 = 1 - F1;
        }
        mStatus = F0;

        for (unsigned int k = 0; k < mOrder; k++) {
            mEf(F0, k) = mErrF(mStatus, k);
            mEb(F0, k) = mErrB(mStatus, k);
        }

        /**********Lattice implementation on workspace***************/

        for (unsigned int i = mOutputSize; i < mTotSize; i++) {
            mEf(F1, 0) = mBuffer(0, i);
            mEb(F1, 0) = mBuffer(0, i);

            for (unsigned int k = 1; k < mOrder; k++) {
                t = k - 1;
                mEf(F1, k) = mEf(F1, t) - mParcorF(k) * mEb(F0, t);
                mEb(F1, k) = mEb(F0, t) - mParcorB(k) * mEf(F1, t);
            }


            F0 = 1 - F0;
            F1 = 1 - F1;

            mWhitened(0, i) = mEf(F0, End);
        }

        mEf(F0, 0) = mWhitened(0, mTotSize - 1);
        mEb(F0, 0) = mWhitened(0, mTotSize - 1);

        for (unsigned int k = 1; k < mOrder; k++) {
            mEf(F0, k) = mEf(F0, k - 1);
            mEb(F0, k) = 0.0;
        }


        for (unsigned int i = 0; i < (mTotSize - mOutputSize); i++) {
            mEf(F1, 0) = mWhitened(0, mTotSize - i - 1);
            mEb(F1, 0) = mWhitened(0, mTotSize - i - 1);

            for (unsigned int k = 1; k < mOrder; k++) {
                t = k - 1;
                mEf(F1, k) = mEf(F1, t) - mParcorF(k) * mEb(F0, t);
                mEb(F1, k) = mEb(F0, t) - mParcorB(k) * mEf(F1, t);
            }

            F0 = 1 - F0;
            F1 = 1 - F1;
        }

        for (unsigned int i = (mTotSize - mOutputSize); i < mTotSize; i++) {
            mEf(F1, 0) = mWhitened(0, mTotSize - i - 1);
            mEb(F1, 0) = mWhitened(0, mTotSize - i - 1);
            for (unsigned int k = 1; k < mOrder; k++) {
                t = k - 1;
                mEf(F1, k) = mEf(F1, t) - mParcorF(k) * mEb(F0, t);
                mEb(F1, k) = mEb(F0, t) - mParcorB(k) * mEf(F1, t);
            }

            F0 = 1 - F0;
            F1 = 1 - F1;

            DWOutput(0, mTotSize - i - 1) = mEf(F0, End);
        }

        mBuffer.DelPoints(mOutputSize);
    }
    
 void DoubleWhitening::SetOutputSize(unsigned int OutputSize,unsigned int ExtraSize)
        {
            mOutputSize=OutputSize;
            mTotSize=OutputSize+ExtraSize;
            mWhitened(1, mOutputSize);
        }
   


}
