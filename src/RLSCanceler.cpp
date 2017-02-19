//
//
// C++ Implementation: RLSCanceler.cpp
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

#include <RLSCanceler.hpp>

namespace tsa {

    RLSCanceler::RLSCanceler(unsigned int Order, double delta, double lambda, unsigned int Channels)
    :
    mP(Order + 1),
    mdelta(delta),
    mlambda(lambda),
    mWeights(Channels, Order + 1),
    mC(Order + 1, Order + 1),
    mX(Order + 1),
    mM(Order + 1),
    mG(Order + 1),
    mlstart(0.0),
    msigma(0.0) {

        for (unsigned int j = 0; j < mP; j++) {
            mX(j) = 0.0;
            for (unsigned int k = 0; k < mP; k++)
                mC(j, k) = 0.0;
            for (unsigned int k = 0; k < Channels; k++)
                mWeights(k, j) = 0.0;
        }
        for (unsigned int j = 0; j < mP; j++)
            mC(j, j) = mdelta;

    }

    ///
    /// Destructor
    ///

    RLSCanceler::~RLSCanceler() {
    }

    ///
    /// Copy constructor
    ///
    /// @param from The instance that must be copied

    RLSCanceler::RLSCanceler(const RLSCanceler& from) {
    }

    void RLSCanceler::operator()(SeqViewDouble& InputData, SeqViewDouble& CleanedData) {
        Dmatrix* arg1 = InputData.GetData();
        Dmatrix* arg2 = CleanedData.GetData();

        if ((arg1->size1() != arg2->size1()) || (arg1->size2() != arg2->size2())) {
            arg2->resize(arg1->size1(), arg1->size2());
            arg2->clear();
            LogWarning("NotchWidrow: resizing output array");
        }
        CleanedData.SetStart(InputData.GetStart());
        CleanedData.SetSampling(InputData.GetSampling());
        execute(*arg1, *arg2);

    }

    void RLSCanceler::operator()(SeqViewDouble& InputData, SeqViewDouble& CleanedData, SeqViewDouble& ReferenceSignal) {
        Dmatrix* arg1 = InputData.GetData();
        Dmatrix* arg2 = CleanedData.GetData();
        Dmatrix* arg3 = ReferenceSignal.GetData();

        if ((arg1->size1() != arg2->size1()) || (arg1->size2() != arg2->size2())) {
            arg2->resize(arg1->size1(), arg1->size2());
            arg2->clear();
            LogWarning("RLSCanceler: resizing output array");
        }
        if ((arg1->size1() != arg3->size1()) || (arg1->size2() != arg3->size2())) {
            arg3->resize(arg1->size1(), arg1->size2());
            arg3->clear();
            LogWarning("RLSCanceler: resizing reference array");
        }
        CleanedData.SetStart(InputData.GetStart());
        CleanedData.SetSampling(InputData.GetSampling());
        execute(*arg1, *arg2, *arg3);

        ReferenceSignal.SetStart(InputData.GetStart());
        ReferenceSignal.SetSampling(InputData.GetSampling());
    }

    void RLSCanceler::execute(Dmatrix& Input, Dmatrix& Output, Dmatrix& ReferenceSignal) {
        if (Input.size1() != mWeights.size1()) {
            mWeights.resize(Input.size1(), mP, true);
            mWeights.clear();
            LogWarning("RLSCanceler: number of channels changed, weights reset");
        }

        /*operation*/
        double out, dat, erf, mu; ///temporary data

        for (unsigned int Channel = 0; Channel < Input.size1(); Channel++) {
            for (unsigned int i = 0; i < Input.size2(); i++) {

                dat = Input(Channel, i);

                out = 0.0;
                for (unsigned int k = 1; k < mP; k++)
                    out += mWeights(Channel, k) * mX(k);

                /*form prediction error*/

                erf = dat - out;

                /* Calculate new gain vector*/
                mM = prod(mC, mX);

                mu = inner_prod(mM, mX);

                mG = mM / (mlambda + mu);

                for (unsigned int k = 1; k < mP; k++)
                    mWeights(Channel, k) += mG(k) * erf;

                /* Update matrix inverse for the next time iteration */

                mC = (1.0 / mlambda)*(mC - outer_prod(mG, mM));

                msigma += erf*erf;

                for (unsigned int k = mP - 1; k > 1; k--)
                    mX(k) = mX(k - 1);
                mX(1) = ReferenceSignal(Channel, i);

                Output(Channel, i) = erf;
            }
            mlstart += (double) Input.size2();

            mWeights(Channel, 0) = sqrt(msigma / mlstart);
        }
    }

    void RLSCanceler::execute(Dmatrix& Input, Dmatrix& Output) {
        if (Input.size1() != mWeights.size1()) {
            mWeights.resize(Input.size1(), mP, true);
            mWeights.clear();
            LogWarning("RLSCanceler: number of channels changed, weights reset");
        }

        /*operation*/
        double out, dat, erf, mu; ///temporary data

        for (unsigned int Channel = 0; Channel < Input.size1(); Channel++) {
            for (unsigned int i = 0; i < Input.size2(); i++) {

                dat = Input(Channel, i);

                out = 0.0;
                for (unsigned int k = 1; k < mP; k++)
                    out += mWeights(Channel, k) * mX(k);

                /*form prediction error*/

                erf = dat - out;

                /* Calculate new gain vector*/
                mM = prod(mC, mX);

                mu = inner_prod(mM, mX);

                mG = mM / (mlambda + mu);

                for (unsigned int k = 1; k < mP; k++)
                    mWeights(Channel, k) += mG(k) * erf;

                /* Update matrix inverse for the next time iteration */

                mC = (1.0 / mlambda)*(mC - outer_prod(mG, mM));

                msigma += erf*erf;

                for (unsigned int k = mP - 1; k > 1; k--)
                    mX(k) = mX(k - 1);
                mX(1) = Input(Channel, i);

                Output(Channel, i) = erf;
            }
            mlstart += (double) Input.size2();

            mWeights(Channel, 0) = sqrt(msigma / mlstart);
        }
    }

    ///
    /// Assignement operator
    ///
    /// @param from The instance to be assigned from
    ///
    /// @return a reference to a new object

    RLSCanceler& RLSCanceler::operator=(const RLSCanceler& from) {
        return *this;
    }

}

