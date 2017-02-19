#ifndef CLUSTERIZEDEVENTFULLFEATURED_CPP
#define CLUSTERIZEDEVENTFULLFEATURED_CPP


#include "ClusterizedEventFullFeatured.hpp"

using namespace boost::numeric::ublas;
namespace tsa {

    ClusterizedEventFullFeatured::ClusterizedEventFullFeatured(unsigned int NumCoeff)
    :
    mTime(0.0),
    mTimeMax(0.0),
    mLenght(0.0),
    mSNR(0.0),
    mlevel(0.0),
    mNumCoeff(NumCoeff),
    mCoeff(NumCoeff)

 {
    }

    ClusterizedEventFullFeatured::~ClusterizedEventFullFeatured() {
        mCoeff.clear();
    }
    ;

    void ClusterizedEventFullFeatured::operator=(const ClusterizedEventFullFeatured& from) {

        mTime = from.mTime;
        mTimeMax = from.mTimeMax;
        mSNR = from.mSNR;
        mCoeff.resize(from.mCoeff.size());
        for (unsigned int i = 0; i < from.mCoeff.size(); i++) {
            mCoeff(i) = from.mCoeff(i);
        }

        mlevel = from.mlevel;
        mWave = from.mWave;
    }

    void ClusterizedEventFullFeatured::CEVcopy(const ClusterizedEventFullFeatured& from) {

        mTime = from.mTime;
        mTimeMax = from.mTimeMax;
        mSNR = from.mSNR;
        mCoeff.resize(from.mCoeff.size());
        for (unsigned int i = 0; i < from.mCoeff.size(); i++) {
            mCoeff[i] = from.mCoeff[i];
        }
        mlevel = from.mlevel;
        mWave = from.mWave;
    }





} //end namespace


#endif // CLUSTERIZEDEVENTFULLFEATURED_CPP 
