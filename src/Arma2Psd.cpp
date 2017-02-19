//
//
// C++ Implementation: Arma2Psd.cpp
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

#include <Arma2Psd.hpp>

namespace tsa {

    Arma2Psd::Arma2Psd() {
    }

    /// Copy constructor
    ///
    /// @param from The instance that must be copied

    Arma2Psd::Arma2Psd(const Arma2Psd& from) {
    }


    ///
    /// Destructor
    ///

    Arma2Psd::~Arma2Psd() {
    }


    ///
    /// Assignement operator
    ///
    /// @param from The instance to be assigned from
    ///
    /// @return a reference to a new object

    Arma2Psd& Arma2Psd::operator=(const Arma2Psd& from) {
        return *this;
    }

    void Arma2Psd::operator()(ARMAView& arma, SeqViewDouble& Psd) {

        Dvector ar(arma.GetArOrder() + 1);
        Dvector ma(arma.GetMaOrder() + 1);
        Dvector psd(Psd.GetSize());


        for (unsigned int i = 0; i < ar.size(); i++) {
            ar(i) = arma.GetAR(i);
        }
        for (unsigned int i = 0; i < ma.size(); i++) {
            ma(i) = arma.GetMA(i);
        }
        execute(
                ar,
                ma,
                psd
                );
        for (unsigned int i = 0; i < Psd.GetSize(); i++) {
            Psd(0, i) = sqrt(1.0 / (4.0 * (Psd.GetSize() - 1)*(Psd.GetSize() - 1))) * psd(i);
        }


    }



    ///It has been implemented a fast recurrence algorithm fot the estimation of sin and cos, by A. Vicere'

    void Arma2Psd::execute(Dvector& AR, Dvector& MA, Dvector& psd) {

        double re, im, spec;
        double cosarg, sinarg;
        double cosCurrent, sinCurrent;
        double cosNext;

        /* initialize fixed values */

        double arg = 0.0;
        double darg = M_PI / (psd.size() - 1);
        for (unsigned int j = 0; j < psd.size(); j++) {

            cosarg = cos(arg);
            sinarg = sin(arg);

            /* denominator (AR part) */
            re = 1.0;
            im = 0.0;
            cosCurrent = 1.0;
            sinCurrent = 0.0;
            for (unsigned int r = 1; r < AR.size(); r++) {
                /* recurrence form (much faster) */
                cosNext = cosCurrent * cosarg - sinCurrent * sinarg;
                sinCurrent = cosCurrent * sinarg + sinCurrent * cosarg;
                cosCurrent = cosNext;
                re += AR(r) * cosCurrent;
                im += AR(r) * sinCurrent;
            }

            /* one-sided spectral density */
            spec = 2.0 * AR(0) * AR(0) / (re * re + im * im);

            /* numerator (MA part) */
            re = MA(0);
            im = 0.0;
            cosCurrent = 1.0;
            sinCurrent = 0.0;
            for (unsigned int r = 1; r < MA.size(); r++) {
                /* recurrence form (much faster) */
                cosNext = cosCurrent * cosarg - sinCurrent * sinarg;
                sinCurrent = cosCurrent * sinarg + sinCurrent * cosarg;
                cosCurrent = cosNext;
                re += MA(r) * cosCurrent;
                im += MA(r) * sinCurrent;
            }
            psd(j) = spec * (re * re + im * im);

            arg += darg;
        }

    }
}

