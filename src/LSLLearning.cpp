//
//
// C++ Implementation: LSLLearning.cpp
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

#include <LSLLearning.hpp>

namespace tsa {

    LSLLearning::LSLLearning(unsigned int Order, double sigma, double lambda)
    :
    mOrder(Order + 1),
    mSigma(sigma),
    mLambda(lambda) {
        mEF.resize(2, mOrder);
        mEB.resize(2, mOrder);
        mEpf.resize(2, mOrder);
        mEpb.resize(2, mOrder);
        mKf.resize(mOrder);
        mKb.resize(mOrder);
        mG.resize(mOrder);
        mF0 = 0;
        for (unsigned int k = 0; k < mOrder; k++) {
            mEB(0, k) = 0.0;
            mKf(k) = 0.0;
            mKb(k) = 0.0;
            mG(k) = 1.0;
            mEpf(0, k) = sigma;
            mEpb(0, k) = sigma;
        }
        mKf(0) = -sigma;
        mKb(0) = -sigma;
    }

    LSLLearning::~LSLLearning() {
    }

    void LSLLearning::operator()(SeqViewDouble& InputData, SeqViewDouble& WhitenedData) {
        Dmatrix* in = InputData.GetData();
        Dmatrix* out = WhitenedData.GetData();

        if ((in->size1() != out->size1()) || (in->size2() != out->size2())) {
            out->resize(in->size1(), in->size2());
            LogWarning("LSLLearning: resizing output view");
        }

        for (unsigned int r = 0; r < in->size1(); r++) {
            execute(row(*in, r), row(*out, r));
        }
        WhitenedData.SetStart(InputData.GetStart());
        WhitenedData.SetSampling(InputData.GetSampling());
    }

    void LSLLearning::operator()(SeqViewDouble& InputData, LatticeView& LatView) {
        Dmatrix * in = InputData.GetData();
        LogWarning("LSLLearning: the input data have been overwritten");

        for (unsigned int r = 0; r < in->size1(); r++) {
            execute(row(*in, r), row(*in, r));
        }

        if (LatView.GetOrder() != GetOrder()) {
            LatView.SetOrder(GetOrder());
            LogWarning("LSLLearning: resizing Lattice view order");
        }

        for (unsigned int i = 0; i <= GetOrder(); i++) {
            LatView.SetParcorF(i, -GetParcorForward(i));
            LatView.SetParcorB(i, -GetParcorBackward(i));
            LatView.SetErrorForward(i, GetErrorForward(mF0, i));
            LatView.SetErrorBackward(i, GetErrorBackward(mF0, i));
        }
    }

    void LSLLearning::operator()(SeqViewDouble& InputData, Dvector& Parcor) {
        Dmatrix * in = InputData.GetData();
        LogWarning("LSLLearning: the input data have been overwritten");

        for (unsigned int r = 0; r < in->size1(); r++) {
            execute(row(*in, r), row(*in, r));
        }

        if (Parcor.size() != (GetOrder() + 1)) {
            Parcor.resize(GetOrder() + 1);
            LogWarning("LSLLearning: resizing order of vector Parcor");
        }
        for (unsigned int i = 0; i < Parcor.size(); i++) {
            Parcor(i) = GetParcorForward(i);
        }
    }

    void LSLLearning::execute(matrix_row<Dmatrix> InputData, matrix_row<Dmatrix> OutputData) {

        unsigned int f_0 = mF0;
        unsigned int f_1 = 1 - mF0;

        /*--Recursive relation-----------------------------------------------*/
        unsigned int End = mOrder - 1;
        for (unsigned int l = 0; l < InputData.size(); l++) {
            mEB(f_1, 0) = InputData(l);
            mEF(f_1, 0) = InputData(l);
            mEpf(f_1, 0) = mLambda * mEpf(f_0, 0) + InputData(l) * InputData(l);
            mEpb(f_1, 0) = mLambda * mEpf(f_0, 0) + InputData(l) * InputData(l);
            mG(0) = 1.0;

            /*--------*/
            for (unsigned int k = 1; k < mOrder; k++) {
                unsigned int t = k - 1;
                mEpf(f_1, t) = mLambda * mEpf(f_0, t) + mG(t) * mEF(f_1, t) * mEF(f_1, t);
                mEpb(f_1, t) = mLambda * mEpb(f_0, t) + mG(t) * mEB(f_0, t) * mEB(f_0, t);
                mEF(f_1, k) = mEF(f_1, t) + mKf(k) * mEB(f_0, t);
                mEB(f_1, k) = mEB(f_0, t) + mKb(k) * mEF(f_1, t);
                mKf(k) = mKf(k) - mG(t) * mEB(f_0, t) * mEF(f_1, k) / mEpb(f_1, t);
                mKb(k) = mKb(k) - mG(t) * mEF(f_1, t) * mEB(f_1, k) / mEpf(f_1, t);
                mG(k) = mG(t) - (mG(t) * mG(t)) * (mEB(f_0, t) * mEB(f_0, t)) / mEpb(f_1, t);
            }
            OutputData(l) = mEF(f_1, End);
            f_1 = 1 - f_1;
            f_0 = 1 - f_0;
        }
        mSigma = mEpf(f_0, End - 1) / (InputData.size());
        // mSigma = mEpf( f_0, End - 1 );
        // --- Save the state of the filter
        mF0 = f_0;
    }

    ///
    /// Copy constructor
    ///
    /// @param from The instance that must be copied

    LSLLearning::LSLLearning(const LSLLearning& from) {
    }


    ///
    /// Assignement operator
    ///
    /// @param from The instance to be assigned from
    ///
    /// @return a reference to a new object

    LSLLearning& LSLLearning::operator=(const LSLLearning& from) {
        return * this;
    }

}
