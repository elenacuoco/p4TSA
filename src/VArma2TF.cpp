//
//
// C++ Implementation: VArma2TF.cpp
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

#if 0

#include <VArma2TF.hpp>

namespace tsa {

    VArma2TF::VArma2TF()
    :
    mLUsolver(0) {

    }

    void VArma2TF::execute(VDmatrix& AR, VDmatrix& MA, Cmatrix& TF) {

        if (MA.size() == 0) {
            LogSevere( "VArma2TF::execute - no MA part");
        }

        unsigned int channels = MA[0].size1();

        if (channels * (channels + 1) / 2 != TF.size1()) {
            LogSevere("bad_matrix_size: VArma2TF::execute");
        }

        double p = 2.0 * M_PI / (2.0 * (TF.size2() - 1));
        Cdouble z(1.0, 0.0);
        Cdouble dz(cos(p), sin(p));

        for (unsigned int j = 0; j < TF.size2(); j++) {
            Cmatrix num(channels, channels);
            Cmatrix den(channels, channels);
            if (MA.size() < AR.size()) {
                Cdouble zk(1.0, 0.0);
                unsigned int k;
                for (k = 0; k < MA.size(); k++) {
                    num += MA[k] * zk;
                    den += AR[k] * zk;
                    zk = zk*z;
                }
                for (; k < AR.size(); k++) {
                    den += AR[k] * zk;
                    zk = zk*z;
                }
            } else {
                Cdouble zk(1.0, 0.0);
                unsigned int k;
                for (k = 0; k < AR.size(); k++) {
                    num += MA[k] * zk;
                    den += AR[k] * zk;
                    zk = zk*z;
                }
                for (; k < MA.size(); k++) {
                    num += MA[k] * zk;
                    zk = zk*z;
                }
            }


            mLUsolver.execute(den, num);

            unsigned int p = 0;
            for (unsigned int row = 0; row < channels; row++) {
                for (unsigned int col = row; col < channels; col++) {

                    TF(p, j) = num(row, col);
                    p++;

                }
            }
            z = z*dz;
        }
    }

    ///
    /// Copy constructor
    ///
    /// @param from The instance that must be copied

    VArma2TF::VArma2TF(const VArma2TF& from)
    :
    mLUsolver(from.mLUsolver) {

    }

    ///
    /// Destructor
    ///

    VArma2TF::~VArma2TF() {

    }

    ///
    /// Assignement operator
    ///
    /// @param from The instance to be assigned from
    ///
    /// @return a reference to a new object

    VArma2TF& VArma2TF::operator=(const VArma2TF& from) {
        return *this;
    }

}

#endif
