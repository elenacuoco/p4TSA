//
//
// C++ Implementation: SelectionOrderCriteria.cpp
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

#include <SelectionOrderCriteria.hpp>

namespace tsa {

    SelectionOrderCriteria::SelectionOrderCriteria(unsigned int N, unsigned int Order)
    :
    mMaxOrder(Order + 1),
    mN(N),
    mEps(mMaxOrder),
    mFpe(mMaxOrder),
    mMdl(mMaxOrder),
    mAic(mMaxOrder),
    mAicC(mMaxOrder),
    mCat(mMaxOrder),
    mHQ(mMaxOrder),
    mFsic(mMaxOrder),
    mCic(mMaxOrder) {
    }


    ///
    /// Destructor
    ///

    SelectionOrderCriteria::~SelectionOrderCriteria() {
    }

    void SelectionOrderCriteria::execute(Dvector& Parcor) {

        mEps(0) = Parcor(0);
        /// criteria for order selection
        double parsum = 0.0;


        for (unsigned int k = 1; k < mMaxOrder; k++) {
            mEps(k) = (1 - Parcor(k) * Parcor(k)) * mEps(k - 1);

            parsum = 0.0;
            for (unsigned int j = 1; j < k; j++)
                parsum += (mN - j) / (mN * mEps(j));

            mFpe(k) = mEps(k)*(mN + k + 1.0) / (mN - k - 1.0);
            mMdl(k) = log(mEps(k)) + k * log(mN) / mN;
            mAic(k) = log(mEps(k)) + 2.0 * k / mN;
            mCat(k) = (1.0 / mN) * parsum - (mN - k) / (mN * mEps(k));

            mHQ(k) = log(mEps(k)) + 2 * k * log(log(mN)) / mN;
            mAicC(k) = log(mEps(k)) + 2 * (k + 1) / (mN - k - 2);

            double parprod = 1.0;
            for (unsigned int j = 1; j < k; j++)
                parprod *= (1 + 1 / (mN + 1 - j)) / (1 - 1 / (mN + 1 - j));

            mFsic(k) = log(mEps(k)) + parprod - 1;
            mCic(k) = mFsic(k) + k;
        }
        mFpe(0) = mFpe(1);
        mMdl(0) = mMdl(1);
        mAic(0) = mAic(1);
        mCat(0) = mCat(1);

        mHQ(0) = mHQ(1);
        mAicC(0) = mAicC(1);
        mFsic(0) = mFsic(1);
        mCic(0) = mCic(1);

    }

}

