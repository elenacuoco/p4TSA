//
//
// C++ Implementation: LeastSquaresLattice.cpp
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

#include <LeastSquaresLattice.hpp>

namespace tsa {

    LeastSquaresLattice::LeastSquaresLattice(matrix_row<Dmatrix>& LearnData, matrix_row<Dmatrix>& WhitenData, unsigned int P, double lambda, unsigned int D)
    :
    mOrder(P),
    mLwsp(2 * mOrder + 1),
    mLambda(lambda),
    mLast(6, mOrder + 1),
    mDirection(D),
    mStep(0),
    mLSLlearn(mOrder, mLambda, mLwsp) {
        mLSLlearn.execute(LearnData, WhitenData);
    }




    ///
    /// Destructor
    ///

    LeastSquaresLattice::~LeastSquaresLattice() {
    }


    ///
    /// Assignement operator
    ///
    /// @param from The instance to be assigned from
    ///
    /// @return a reference to a new object

    LeastSquaresLattice& LeastSquaresLattice::operator=(const LeastSquaresLattice& from) {
        return *this;
    }



}
