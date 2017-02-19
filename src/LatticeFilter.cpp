//
//
// C++ Implementation: LatticeFilter.cpp
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

#include <LatticeFilter.hpp>

namespace tsa {

    LatticeFilter::LatticeFilter(Dvector& ParcorF, Dvector& ParcorB, Dmatrix& ErrF, Dmatrix& ErrB)
    :
    mOrder(ParcorF.size()),
    mParcorF(ParcorF),
    mParcorB(ParcorB),
    mErrF(ErrF),
    mErrB(ErrB),
    mStatus(0) {
    }

    LatticeFilter::LatticeFilter(LatticeView& LV)
    :
    mOrder(LV.GetParcorF()->size()),
    mParcorF(*LV.GetParcorF()),
    mParcorB(*LV.GetParcorB()),
    mErrF(*LV.GetErrorForward()),
    mErrB(*LV.GetErrorBackward()),
    mStatus(0) {
    }

    LatticeFilter::~LatticeFilter() {
    }

    void LatticeFilter::init(LatticeView& LV) {
        mOrder = LV.GetParcorF()->size();
        mParcorF = *LV.GetParcorF();
        mParcorB = *LV.GetParcorB();
        mErrF = *LV.GetErrorForward();
        mErrB = *LV.GetErrorBackward();
        mStatus = 0;
    }

    void LatticeFilter::execute(matrix_row<Dmatrix> Input, matrix_row<Dmatrix> Output) {
        int F0 = mStatus;
        int F1 = 1 - mStatus;
        unsigned int t;
        unsigned int End = mOrder - 1;
        /**********Lattice implementation***************/

        for (unsigned int i = 0; i < Input.size(); i++) {
            mErrF(F1, 0) = Input(i);
            mErrB(F1, 0) = Input(i);
            for (unsigned int k = 1; k < mOrder; k++) {
                t = k - 1;
                mErrF(F1, k) = mErrF(F1, t) - mParcorF(k) * mErrB(F0, t);
                mErrB(F1, k) = mErrB(F0, t) - mParcorB(k) * mErrF(F1, t);
            }

            Output(i) = mErrF(F1, End);
            F0 = 1 - F0;
            F1 = 1 - F1;
        }
        mStatus = F0;
    }


}

