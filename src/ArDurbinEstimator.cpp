//
//
// C++ Implementation: ArDurbinEstimator.cpp
//
// Description:
//
//
// Author: Elena Cuoco <elena.cuoco@ego-gw.it>, (C) 2004
//
// Copyright: See COPYING file that comes with this distribution
//
//
//

#include <ArDurbinEstimator.hpp>

namespace tsa {

    ArDurbinEstimator::ArDurbinEstimator(unsigned int ArOrder)
    :
    mArOrder(ArOrder + 1) {
    }

    ArDurbinEstimator::~ArDurbinEstimator() {
    }

    void ArDurbinEstimator::execute(Dvector& AutoCorr, Dvector& ArParcor) {
        unsigned int P = mArOrder;
        Dvector Aux(P); ///< auxiliary matrix to estimate the AR coeff. by the Parcor

        Aux(0) = AutoCorr(0);

        for (unsigned int k = 0; k < P; ++k) {
            /// Estimation of the AR coefficient via durbin's algorithm

            double sum = 0.0;
            for (unsigned int i = 0; i < k; i++)
                sum += ArParcor(i) * AutoCorr(k - i);

            ArParcor(k) = (1.0 / Aux(k - 1))*(AutoCorr(k) - sum);

            for (unsigned int j = 0; j < k; j++)
                ArParcor(j) = Aux(j) - ArParcor(k) * Aux(k - j);

            for (unsigned int j = 0; j < k; j++)
                Aux(j) = ArParcor(j);

            Aux(k) = (1 - ArParcor(k) * ArParcor(k)) * Aux(k - 1);

        }

        ArParcor(0) = sqrt(Aux(P));
    }
}
