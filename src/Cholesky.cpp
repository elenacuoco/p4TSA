//
//
// C++ Implementation: Cholesky.cpp
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

#include <Cholesky.hpp>

namespace tsa {

    Cholesky::Cholesky(unsigned int N, double eps)
    :
    mN(N + 1),
    mD(mN),
    mY(mN),
    mXL(mN, mN),
    mIflag(0),
    mEps(eps) {
    }



    ///
    /// Copy constructor
    ///
    /// @param from The instance that must be copied

    Cholesky::Cholesky(const Cholesky& from) {
    }
    ;

    ///
    /// Destructor
    ///

    Cholesky::~Cholesky() {
    }
    ;

    ///
    /// Assignement operator
    ///
    /// @param from The instance to be assigned from
    ///
    /// @return a reference to a new object

    Cholesky& Cholesky::operator=(const Cholesky& from) {
        return *this;
    };

    void Cholesky::execute(Dvector& A, Dvector& B) {
        unsigned int l;
        l = 1;
        mD(1) = A(l);

        for (unsigned int i = 2; i < mN; i++) {
            for (unsigned int j = 1; j < i; j++) {
                l++;
                mXL(i, j) = A(l) / mD(j);
                if (j != 1) {
                    for (unsigned int k = 1; k < j; k++)
                        mXL(i, j) = mXL(i, j) - mXL(i, k) * mXL(j, k) * mD(k) / mD(j);
                }
            }
            l++;
            mD(i) = A(l);

            for (unsigned int k = 1; k < i; k++)
                mD(i) = mD(i) - mD(k)*(mXL(i, k))*(mXL(i, k));

            if (mD(i) <= mEps)
                mIflag = -1;
        }

        mY(1) = B(1);
        for (unsigned int k = 2; k < mN; k++) {
            mY(k) = B(k);

            for (unsigned int j = 1; j < k; j++)
                mY(k) = mY(k) - mXL(k, j) * mY(j);
        }

        B(mN - 1) = mY(mN - 1) / mD(mN - 1);

        for (unsigned int k = mN - 2; k >= 1; k = k - 1) {
            B(k) = mY(k) / mD(k);

            for (unsigned int j = k + 1; j < mN - 1; j++)
                B(k) = B(k) - mXL(j, k) * B(j);
        }

    };
}

