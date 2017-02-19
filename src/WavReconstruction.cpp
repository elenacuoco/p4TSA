//
//
// C++ Implementation: WavReconstruction.cpp
//
// Description:
//
//
// Author: Elena Cuoco <elena.cuoco@ego-gw.it>, (C) 2006
//
// Copyright: See COPYING file that comes with this distribution
//
//
//

#include <WavReconstruction.hpp>

namespace tsa {

    WavReconstruction::WavReconstruction(unsigned int N, enum WaveletTransform::WaveletType F, double Th)
    :
    mN(N),
    mWt(F),
    mWT(mN, mWt),
    mT(WaveletThreshold::cuoco),
    mWavThres(mN, 1, Th) {
    }

    WavReconstruction::~WavReconstruction() {
    }

    void WavReconstruction::operator()(SeqViewDouble& InputData) {
        Dmatrix* in = InputData.GetData();
        execute(*in);
    }

    void WavReconstruction::execute(Dmatrix& buffer) {

        mWT.Forward(buffer);
        mWavThres(buffer, mT);
        mWT.Inverse(buffer);
    }
}




