//
//
// C++ Implementation: Arma2TF.cpp
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

#include <Arma2TF.hpp>

namespace tsa {

    Arma2TF::Arma2TF() {

    }

    void Arma2TF::operator()(ARMAView& arma, SeqViewComplex& TF) {
        if (arma.GetChannels() == 1) {

            Dvector ar(arma.GetArOrder() + 1);
            Dvector ma(arma.GetMaOrder() + 1);

            Cvector tf(TF.GetSize());

            for (unsigned int i = 0; i < ar.size(); i++) {
                ar(i) = arma.GetAR(i);
            }
            for (unsigned int i = 0; i < ma.size(); i++) {
                ma(i) = arma.GetMA(i);
            }
            execute(
                    ar,
                    ma,
                    tf
                    );
            row(*TF.GetData(), 0) = tf;
        } else {
            /// @todo implement Multivectorial Arma 

            LogSevere("Arma2TF: to be implemented");
            abort();
#if 0
            execute(
                    Attribute<VDmatrix>(arma, "AR"),
                    Attribute<VDmatrix>(arma, "MA"),
                    Attribute<Cmatrix>(TF, "Data")
                    );
#endif

        }
    }

    void Arma2TF::execute(Dvector& AR, Dvector& MA, Cvector& TF) {

        double p = M_PI / (TF.size() - 1);
        Cdouble z(1.0, 0.0);
        Cdouble dz(cos(p), sin(p));

        for (unsigned int j = 0; j < TF.size(); j++) {

            Cdouble num(0.0, 0.0);
            Cdouble den(0.0, 0.0);

            if (MA.size() < AR.size()) {
                Cdouble zk(1.0, 0.0);

                unsigned int k;

                for (k = 0; k < MA.size(); k++) {
                    num += MA(k) * zk;
                    den += AR(k) * zk;
                    zk = zk*z;
                }
                for (; k < AR.size(); k++) {
                    den += AR(k) * zk;
                    zk = zk*z;
                }
            }
            else {
                Cdouble zk(1.0, 0.0);
                unsigned int k;

                for (k = 0; k < AR.size(); k++) {
                    num += MA(k) * zk;
                    den += AR(k) * zk;
                    zk = zk*z;
                }
                for (; k < MA.size(); k++) {
                    num += MA(k) * zk;
                    zk = zk*z;
                }
            }
            TF(j) = num / den;
            z = z*dz;
        }
    }

    ///
    /// Copy constructor
    ///
    /// @param from The instance that must be copied

    Arma2TF::Arma2TF(const Arma2TF& from) {

    }

    ///
    /// Destructor
    ///

    Arma2TF::~Arma2TF() {
    }

    ///
    /// Assignement operator
    ///
    /// @param from The instance to be assigned from
    ///
    /// @return a reference to a new object

    Arma2TF& Arma2TF::operator=(const Arma2TF& from) {
        return *this;
    }

}
