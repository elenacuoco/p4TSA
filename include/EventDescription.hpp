///
///   Copyright (C) 2004 by Elena Cuoco
///   elena.cuoco@ego-gw.it
///
///   This program is free software; you can redistribute it and/or modify
///   it under the terms of the GNU General Public License as published by
///   the Free Software Foundation; either version 2 of the License, or
///   (at your option) any later version.
///
///   This program is distributed in the hope that it will be useful,
///   but WITHOUT ANY WARRANTY; without even the implied warranty of
///   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
///   GNU General Public License for more details.
///
///   You should have received a copy of the GNU General Public License
///   along with this program; if not, write to the
///   Free Software Foundation, Inc.,
///   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
///
/// @file   EventDescription.hpp
/// @author Elena Cuoco <elena.cuoco@ego-gw.it>
/// @date   2005
///
/// @brief  EventDescription is a class container for a transient event
///
#ifndef __EVENTDESCRIPTION_hpp
#define __EVENTDESCRIPTION_hpp


///
/// @name System includes
///
//@{

#include <string>

//@}

///
/// @name Project includes
///
//@{

#include <AlgoBase.hpp>
#include <BaseView.hpp>

//@}

///
/// @name Local includes
///
//@{


//@}

///
/// @name Forward references
///
//@{


//@}

///
/// namespace
///
using namespace boost::numeric::ublas;
namespace tsa {


    ///
    ///
    /// 
    ///
    ///@brief  EventDescription is a class container for a transient event

    ///
    ///

    class EventFull {
    public:

        EventFull()
        :
        mTime(0.0),
        mSNR(0.0),
        mCmax(0.0),
        mlevel(0.0) {
        }
        ;

        /**
         * Destructor
         */
        virtual ~EventFull() {
        }
        ;
        double mTime;
        double mSNR;
        double mCmax;
        double mlevel;
        std::string mWave;

        EventFull& operator=(const EventFull& from) {

            mTime = from.mTime;
            mSNR = from.mSNR;
            mCmax = from.mCmax;
            mlevel = from.mlevel;
            mWave = from.mWave;
        }

    };

    class Event {
    public:

        Event()
        :
        mTime(0.0),
        mSNR(0.0) {
        }
        ;

        /**
         * Destructor
         */
        virtual ~Event() {
        }
        ;
        double mTime;
        double mSNR;
        std::string mWave;

        /**
         * 
         * @param from 
         * @return 
         */
        Event& operator=(const Event& from) {

            mTime = from.mTime;
            mSNR = from.mSNR;
            mWave = from.mWave;

        }

    };

    class ClusterizedEvent {
    public:

        ClusterizedEvent()
        :
        mTime(0.0),
        mLenght(0.0),
        mSNR(0.0) {
        }
        ;

        virtual ~ClusterizedEvent() {
        }
        ;
        double mTime;
        double mLenght;
        double mSNR;
        std::string mWave;

        ClusterizedEvent& operator=(const ClusterizedEvent& from) {

            mTime = from.mTime;
            mSNR = from.mSNR;
            mLenght = from.mLenght;
            mWave = from.mWave;
        }
    };

    class ClusterizedEventFull {
    public:

        ClusterizedEventFull()
        :
        mTime(0.0),
        mTimeMax(0.0),
        mLenght(0.0),
        mSNR(0.0),
        mCmax(0.0),
        mlevel(0.0) {
        }
        ;

        virtual ~ClusterizedEventFull() {
        }
        ;
        double mTime;
        double mTimeMax;
        double mLenght;
        double mSNR;
        double mCmax;
        double mlevel;
        std::string mWave;

        ClusterizedEventFull& operator=(const ClusterizedEventFull& from) {

            mTime = from.mTime;
            mSNR = from.mSNR;
            mCmax = from.mCmax;
            mlevel = from.mlevel;
            mWave = from.mWave;
        }
    };







} //end namespace

#endif // __EVENTDESCRIPTION_hpp
