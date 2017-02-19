//
//
// C++ Implementation: Parcor2AR.cpp
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

#include <AR2Parcor.hpp>

namespace tsa {

    AR2Parcor::AR2Parcor() {
    }

    AR2Parcor::~AR2Parcor() {
    }

    void AR2Parcor::execute(Dvector& AR, Dvector& Parcor) {

        Dvector tmpP(AR.size());
        Parcor.resize(AR.size());
        unsigned int P = AR.size() - 1;
        Dvector sigma(AR.size());
        sigma(P) = AR(0) * AR(0);

        for (unsigned int k = P; k >= 1; k--) {
            Parcor(k) = AR(k);
            for (unsigned int j = 1; j < k; j++)
                AR(j) = (tmpP(j) - Parcor(k) * tmpP(k - j)) / (1.0 - Parcor(k) * Parcor(k));

            for (unsigned int j = 1; j <= k; j++)
                tmpP(j) = AR(j);
        }

        for (unsigned int j = P; j > 0; j--)
            sigma(j - 1) = sigma(j) / (1.0 - Parcor(j) * Parcor(j));

        Parcor(0) = sigma(0);

        for (unsigned int j = 1; j < AR.size(); j++)
            Parcor(j) *= -1.0;
        ;
    }
}

