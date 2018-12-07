#ifndef EVENTFULLFEATURED_CPP
#define EVENTFULLFEATURED_CPP


#include "EventFullFeatured.hpp"
//
/// namespace
///
using namespace boost::numeric::ublas;
namespace tsa {



    ///

    ///
    ///
    ///
    ///

    /* This class contain the event found by WDF plus the vector of  wavelet coefficients up to @NumCoeff coefficients. */








    EventFullFeatured::EventFullFeatured(unsigned int NumCoeff)
    :
    mTime(0.0),
    mSNR(0.0),
    mlevel(0.0),
    mWave("Haar"),
    mCoeff(NumCoeff) {


    }

    /**
     * Destructor
     */
    EventFullFeatured::~EventFullFeatured() {

        mCoeff.clear();
    };

    void EventFullFeatured::operator=(const EventFullFeatured& from) {

        mTime = from.mTime;
        mSNR = from.mSNR;
        mCoeff.resize(from.mCoeff.size());
        for (unsigned int i = 0; i < mCoeff.size(); i++) {
            mCoeff(i) = from.mCoeff(i);
        }
        mlevel = from.mlevel;
        mWave = from.mWave;
    }

    void EventFullFeatured::EVcopy(const EventFullFeatured& from) {

        mTime = from.mTime;
        mSNR = from.mSNR;
        mCoeff.resize(from.mCoeff.size());
        for (unsigned int i = 0; i < mCoeff.size(); i++) {
            mCoeff(i) = from.mCoeff(i);
        }
        mlevel = from.mlevel;
        mWave = from.mWave;
    }







} //end namespace




#endif // EVENTFULLFEATURED_CPP 
