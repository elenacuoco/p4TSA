//
//
// C++ Implementation: MYWE.cpp
//
// Description:
//
//
// Author: Elena Cuoco <elena.cuoco@ego-gw.it>, (C) 2006
//
// Copyright: See COPYING file that comes with this distribution
//
//
//

#include <MYWE.hpp>

namespace tsa {

    MYWE::MYWE(unsigned int mIP, unsigned int mIQ)
    :
    mIP(mIP),
    mIQ(mIQ),
    mA(mIP + 1, mIP + 1),
    mB(mIP + 1, mIP + 1),
    mRho(mIP + mIQ + 1) {
    }




    ///


    ///
    /// Destructor
    ///

    MYWE::~MYWE() {
    }
    ;

    ///
    /// Assignement operator
    ///
    /// @param from The instance to be assigned from
    ///
    /// @return a reference to a new object

    MYWE& MYWE::operator=(const MYWE& from) {
        return *this;
    };

    void MYWE::execute(Dvector& Corr, Dvector& AR) { /*initialite*/

        mA(1, 1) = -Corr(mIQ + 1) / Corr(mIQ);
        mB(1, 1) = -Corr(mIQ - 1) / Corr(mIQ);

        mRho(1) = (1.0 - mA(1, 1) * mB(1, 1)) * Corr(mIQ);

        /*recursion*/
        for (unsigned k = 2; k <= mIP; k++) {
            double sumA = 0.0;

            for (unsigned int l = 1; l < k; l++)
                sumA += mA(k - 1, l) * Corr(mIQ + k - l);

            mA(k, k) = -(Corr(mIQ + k) + sumA) / mRho(k - 1);

            for (unsigned int i = 1; i < k; i++)
                mA(k, i) = mA(k - 1, i) + mA(k, k) * mB(k - 1, k - i);

            double sumB = 0.0;

            for (unsigned int l = 1; l < k; l++)
                sumB += mB(k - 1, l) * Corr(mIQ - k - l);

            mB(k, k) = -(Corr(mIQ - k) + sumB) / mRho(k - 1);

            for (unsigned int i = 1; i < k; i++)
                mB(k, i) = mB(k - 1, i) + mB(k, k) * mA(k - 1, k - i);

            mRho(k) = (1.0 - mA(k, k) * mB(k, k)) * mRho(k - 1);
        }

        for (unsigned int k = 1; k <= mIP; k++)
            AR(k) = mA(mIP, k);

        AR(0) = 1.0;
    };
}

