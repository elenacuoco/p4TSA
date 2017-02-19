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

#include <Parcor2AR.hpp>

namespace tsa {

    Parcor2AR::Parcor2AR() {
    }

    Parcor2AR::~Parcor2AR() {
    }

    Dvector Parcor2AR::operator()(Dvector Parcor) {
        Dvector tmp;
        tmp.resize(Parcor.size());
        this->execute(Parcor, tmp);
        return tmp;
    }

    void Parcor2AR::execute(Dvector& Parcor, Dvector& AR) {
        Dvector tmpP(Parcor.size());
        Dvector sigma(Parcor.size());

        AR.resize(Parcor.size());

        sigma(0) = Parcor(0);
        for (unsigned int j = 1; j < Parcor.size(); j++)
            AR(j) = -Parcor(j);

        for (unsigned int k = 1; k < Parcor.size(); k++) {
            for (unsigned int j = 1; j < k; j++)
                AR(j) = tmpP(j) + AR(k) * tmpP(k - j);

            for (unsigned int j = 1; j <= k; j++)
                tmpP(j) = AR(j);
        }
        for (unsigned int j = 1; j < Parcor.size(); j++)
            sigma(j) = (1.0 - Parcor(j) * Parcor(j)) * sigma(j - 1);

        /*for(unsigned int j = 1; j < Parcor.size(); j++)
              AR(j)*=-1.0;
         */
        AR(0) = sqrt(sigma(Parcor.size() - 1));
    }


}
