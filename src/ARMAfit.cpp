//
//
// C++ Implementation: ARMAfit.cpp
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

#include <ARMAfit.hpp>

namespace tsa {

    ARMAfit::ARMAfit(unsigned int P, unsigned int Q)
    :
    mP(P),
    mQ(Q),
    mAR(mP + 1),
    mMA(mQ + 1),
    mMethod(mP, mQ) {
    }




    ///
    /// Destructor
    ///

    ARMAfit::~ARMAfit() {
    }
    ;

    ///
    /// Assignement operator
    ///
    /// @param from The instance to be assigned from
    ///
    /// @return a reference to a new object

    ARMAfit& ARMAfit::operator=(const ARMAfit& from) {
        return *this;
    };

    void ARMAfit::execute(Dvector& PSD) {

    }
    ;
}


