//
//
// C++ Implementation: NotchWidrow.cpp
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

#include <NotchWidrow.hpp>

namespace tsa {

    NotchWidrow::NotchWidrow(unsigned int channels, Dmatrix& FrequencyList, double C)
    :
    mFrequencyList(FrequencyList),
    mWeight1(channels, FrequencyList.size1()),
    mWeight2(channels, FrequencyList.size1()),
    mX1(FrequencyList.size1()),
    mX2(FrequencyList.size1()),
    mCs(FrequencyList.size1()),
    mSn(FrequencyList.size1()),
    mlstart(0.0),
    mAmp(C) {
    }

    NotchWidrow::~NotchWidrow() {
    }

    void NotchWidrow::operator()(SeqViewDouble& InputData, SeqViewDouble& CleanedData) {
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

    void NotchWidrow::operator()(SeqViewDouble& InputData, SeqViewDouble& CleanedData, SeqViewDouble& ReferenceSignal) {
        Dmatrix* arg1 = InputData.GetData();
        Dmatrix* arg2 = CleanedData.GetData();
        Dmatrix* arg3 = ReferenceSignal.GetData();

        if ((arg1->size1() != arg2->size1()) || (arg1->size2() != arg2->size2())) {
            arg2->resize(arg1->size1(), arg1->size2());
            arg2->clear();
            LogWarning("NotchWidrow: resizing output array");
        }
        CleanedData.SetStart(InputData.GetStart());
        CleanedData.SetSampling(InputData.GetSampling());
        execute(*arg1, *arg2);

        arg3->resize(mFrequencyList.size1(), arg1->size2());
        ReferenceSignal.SetStart(InputData.GetStart());
        ReferenceSignal.SetSampling(InputData.GetSampling());
        for (unsigned int i = 0; i < mFrequencyList.size1(); i++) {
            for (unsigned int j = 0; j < arg1->size2(); j++)
                ReferenceSignal(i, j) = mRefSign(i, j);
        }
    }

    void NotchWidrow::execute(Dmatrix& Input, Dmatrix& Output) {
        mRefSign.resize(mFrequencyList.size1(), Input.size2());

        if (Input.size1() != mWeight1.size1()) {
            mWeight1.resize(Input.size1(), mFrequencyList.size1(), true);
            mWeight1.clear();
            mWeight2.resize(Input.size1(), mFrequencyList.size1(), true);
            mWeight2.clear();
            LogWarning("NotchWidrow: number of channels changed, weight reset");
        }

        for (unsigned int j = 0; j < mFrequencyList.size1(); j++) {
            mX1(j) = mAmp * cos(mlstart * 2.0 * M_PI * mFrequencyList(j, 0));
            mX2(j) = mAmp * sin(mlstart * 2.0 * M_PI * mFrequencyList(j, 0));
            mCs(j) = cos(2.0 * M_PI * mFrequencyList(j, 0));
            mSn(j) = sin(2.0 * M_PI * mFrequencyList(j, 0));
        }

        for (unsigned int l = 0; l < Input.size2(); l++) {
            for (unsigned int channel = 0; channel < Input.size1(); channel++) {

                Output(channel, l) = Input(channel, l);
                for (unsigned int j = 0; j < mFrequencyList.size1(); j++) {
                    mRefSign(j, l) = mWeight1(channel, j) * mX1(j) + mWeight2(channel, j) * mX2(j);
                    Output(channel, l) -= mRefSign(j, l);
                }

                for (unsigned int j = 0; j < mFrequencyList.size1(); j++) {
                    mWeight1(channel, j) = mWeight1(channel, j) + 2.0 * mFrequencyList(j, 1) * Output(channel, l) * mX1(j);
                    mWeight2(channel, j) = mWeight2(channel, j) + 2.0 * mFrequencyList(j, 1) * Output(channel, l) * mX2(j);
                }
            }
            for (unsigned int j = 0; j < mFrequencyList.size1(); j++) {
                double x1_tmp = mCs(j) * mX1(j) - mSn(j) * mX2(j);
                double x2_tmp = mSn(j) * mX1(j) + mCs(j) * mX2(j);
                mX1(j) = x1_tmp;
                mX2(j) = x2_tmp;
            }
        }
        mlstart += Input.size2();
    }
    ///
    /// Copy constructor
    ///
    /// @param from The instance that must be copied

    NotchWidrow::NotchWidrow(const NotchWidrow& from) {
    }


    ///
    /// Assignement operator
    ///
    /// @param from The instance to be assigned from
    ///
    /// @return a reference to a new object

    NotchWidrow& NotchWidrow::operator=(const NotchWidrow& from) {
        return * this;
    }

}
