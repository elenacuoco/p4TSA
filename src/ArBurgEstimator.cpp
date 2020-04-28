//
//
// C++ Implementation: ArBurgEstimator.cpp
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

#include <ArBurgEstimator.hpp>
#include <Parcor2AR.hpp>

namespace tsa {

    ArBurgEstimator::ArBurgEstimator(unsigned int ArOrder)
    :
    mArOrder(ArOrder + 1),
    mParcor(mArOrder),
    mAR(mArOrder),
    mErrorForward(mArOrder),
    mErrorBackward(mArOrder) {
    }

    ArBurgEstimator::~ArBurgEstimator() {
    }

    void ArBurgEstimator::operator()(SeqViewDouble& InputData, SeqViewDouble& WhitenedData) {
        Dmatrix* in = InputData.GetData();
        Dmatrix* out = WhitenedData.GetData();

        if ((in->size1() != out->size1()) || (in->size2() != out->size2())) {
            out->resize(in->size1(), in->size2());
            LogWarning("ArBurgEstimator: resizing output view");
        }
        for (unsigned int r = 0; r < in->size1(); r++) {
            LogInfo("ArBurgEstimator: execute starts");
            execute(row(*in, r));
            LogInfo("ArBurgEstimator: execute ends");
        }

        WhitenedData.SetStart(InputData.GetStart());
        WhitenedData.SetSampling(InputData.GetSampling());

        for (unsigned int r = 0; r < in->size1(); r++) {
            row(*out, r) = mWhitenedData;
        }
    }

    void ArBurgEstimator::Color(SeqViewDouble& WhitenedData, SeqViewDouble& ColoredData) {
        Dmatrix* in = WhitenedData.GetData();
        Dmatrix* out = ColoredData.GetData();

        if ((in->size1() != out->size1()) || (in->size2() != out->size2())) {
            out->resize(in->size1(), in->size2());
            LogWarning("ArBurgEstimator: resizing output view");
        }
        for (unsigned int r = 0; r < in->size1(); r++) {
            color(row(*in, r), row(*out, r));
        }

        ColoredData.SetStart(WhitenedData.GetStart());
        ColoredData.SetSampling(WhitenedData.GetSampling());
    }

    void ArBurgEstimator::operator()(SeqViewDouble& InputData) {
        Dmatrix* in = InputData.GetData();
        for (unsigned int r = 0; r < in->size1(); r++) {
            LogInfo("ArBurgEstimator: execute starts");
            execute(row(*in, r));
            LogInfo("ArBurgEstimator: execute ends");
        }
    }

    void ArBurgEstimator::execute(matrix_row<Dmatrix> InputData) {

        Dvector ErrorBackward(InputData.size() + 1);
        Dvector ErrorForward(InputData.size() + 1);
        Dvector tmpP(mArOrder);

        mWhitenedData.resize(InputData.size());

        double Norm; /// contain the norm of the input data
        double num;
        double den;
        Norm = 0.0;
        for (unsigned int j = 0; j < InputData.size(); j++)
            Norm += InputData(j) * InputData(j);


        mParcor(0) = Norm / (double) (InputData.size());
        mAR(0) = mParcor(0);
        ErrorForward(0) = InputData(0);
        ErrorBackward(InputData.size() - 1) = InputData(InputData.size() - 1);

        for (unsigned int j = 1; j < InputData.size(); j++) {
            ErrorForward(j) = InputData(j);
            ErrorBackward(j - 1) = InputData(j);
        }


        for (unsigned int k = 1; k < mArOrder; k++) {
            num = 0.0;
            den = 0.0;

            for (unsigned int j = 0; j < (InputData.size() - k); j++) {
                num += ErrorForward(j) * ErrorBackward(j);
                den += (ErrorForward(j) * ErrorForward(j) + ErrorBackward(j) * ErrorBackward(j));
            }

            mAR(k) = 2.0 * num / den;
            mParcor(k) = mAR(k);
            mAR(0) *= (1.0 - mAR(k) * mAR(k));

            for (unsigned int i = 1; i <= (k - 1); i++) {
                mAR(i) = tmpP(i) - mAR(k) * tmpP(k - i);
            }
            for (unsigned int i = 1; i <= k; i++)
                tmpP(i) = mAR(i);

            for (unsigned int j = 0; j < (InputData.size() - k); j++) {
                ErrorForward(j) -= tmpP(k) * ErrorBackward(j);
                ErrorBackward(j) = ErrorBackward(j + 1) - tmpP(k) * ErrorForward(j + 1);
            }

        }
        mAR(0) = sqrt(mAR(0));
        for (unsigned int j = 0; j < mArOrder; j++) {
            mErrorForward(j) = ErrorForward(j);
            mErrorBackward(j) = ErrorBackward(j);
        }

        for (unsigned int j = 0; j < InputData.size(); j++)
            mWhitenedData(j) = ErrorForward(j);

    }

    void ArBurgEstimator::color(matrix_row<Dmatrix> WhitenedData, matrix_row<Dmatrix> ColoredData) {


        mColoredData.resize(WhitenedData.size(), false);
        mColoredData(0) = WhitenedData(0);

        for (unsigned int j = 1; j < mArOrder; j++) {
            double sum = 0.0;
            for (unsigned int k = 1; k <= j; k++)
                sum += mAR(k) * mColoredData(j - k);

            mColoredData(j) = sum + WhitenedData(j);

        }
        for (unsigned int j = mArOrder; j < WhitenedData.size(); j++) {
            double sum = 0.0;
            for (unsigned int k = 1; k < mArOrder; k++)
                sum += mAR(k) * mColoredData(j - k);

            mColoredData(j) = sum + WhitenedData(j);

        }
        for (unsigned int j = 0; j < WhitenedData.size(); j++)
            ColoredData(j) = mColoredData(j);
    }

    void ArBurgEstimator::GetLatticeView(LatticeView& LV) {
        if (LV.GetOrder() != GetArOrder()) {
            LV.SetOrder(GetArOrder());
            LV.GetParcorF()->resize(GetArOrder() + 1);
            LV.GetParcorB()->resize(GetArOrder() + 1);
            LV.GetErrorForward()->resize(2, GetArOrder() + 1);
            LV.GetErrorBackward()->resize(2, GetArOrder() + 1);
            LogWarning("ArBurgEstimator: resizing Lattice view order");
        }
        for (unsigned int i = 0; i <= LV.GetOrder(); i++) {
            LV.SetParcorF(i, GetParcor(i));
            LV.SetParcorB(i, GetParcor(i));
            LV.SetErrorForward(i, GetErrorForward(i));
            LV.SetErrorBackward(i, GetErrorBackward(i));
        }
    }

    unsigned int ArBurgEstimator::GetArOrder() {
        return (mArOrder - 1);
    }

    double ArBurgEstimator::GetParcor(unsigned int j) {
        return mParcor(j);
    }

    double ArBurgEstimator::GetAR(unsigned int j) {
        return mAR(j);
    }

    double ArBurgEstimator::GetErrorForward(unsigned int j) {
        return mErrorForward(j);
    }

    double ArBurgEstimator::GetErrorBackward(unsigned int j) {
        return mErrorBackward(j);
    }

    /// setters

    void ArBurgEstimator::SetArOrder(unsigned int P) {
        mArOrder = P + 1;
    }

    void ArBurgEstimator::SetAR(unsigned int j, double value) {
        mAR(j) = value;
    }
}

