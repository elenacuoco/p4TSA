
///
///   Copyright (C) 2004 by Giancarlo Cella                                 
///   giancarlo.cella@pi.infn.it                                            
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
/// @file   AlgoExceptions.hpp
/// @author Giancarlo Cella <giancarlo.cella@pi.infn.it>
/// @date   Sat Nov 13 17:21:06 2004
/// 
/// @brief  Base class for tsa Exceptions
/// 
#ifndef __ALGOEXCEPTIONS_HPP
#define __ALGOEXCEPTIONS_HPP

///
/// @name System includes
///
//@{
#include <stdexcept>
#include <string>
//@}

///
/// @name Project includes
///
//@{


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
/// tsa namespace
///
namespace tsa {

    /// 
    ///   This exception should be used when a matrix argument of an algorithm
    ///   has an incorrect size. It contains information about the correct expected size.
    /// 

    class bad_matrix_size : public std::invalid_argument {
    public:
        /// Constructor
        ///
        /// @param msg error message
        ///
        ///

        bad_matrix_size(const std::string& msg)
        :
        std::invalid_argument(msg) {

        };


    private:

    };



    /// 
    ///   This exception should be used when a vector argument of an algorithm
    ///   has an incorrect size. It contains information about the correct expected size.
    /// 

    class bad_vector_size : public std::invalid_argument {
    public:
        /// Constructor
        ///
        /// @param msg error message
        ///
        ///

        bad_vector_size(const std::string& msg)
        :
        std::invalid_argument(msg) {

        };


    private:

    };


    /// 
    ///   This exception should be used when some processed data cannot be returned
    /// 

    class no_data_available : public std::runtime_error {
    public:
        /// Constructor
        ///
        /// @param msg error message
        ///
        ///

        no_data_available(const std::string& msg)
        :
        std::runtime_error(msg) {

        };

    private:

    };


    /// 
    ///   This exception should be used when some processed data cannot be returned
    /// 

    class bad_value : public std::runtime_error {
    public:
        /// Constructor
        ///
        /// @param msg error message
        ///
        ///

        bad_value()
        :
        std::runtime_error("") {

        };

    private:

    };


    /// 
    ///   This exception should be used when some frames are missing
    /// 

    class missing_data : public std::runtime_error {
    public:
        /// Constructor
        ///
        /// @param msg error message
        ///
        ///

        missing_data(const std::string& msg, double miss_start, double miss_end, unsigned int channel)
        :
        std::runtime_error(msg),
        mStartPeriod(miss_start),
        mEndPeriod(miss_end),
        mChannel(channel) {

        };

        double Start() {
            return mStartPeriod;
        }

        double End() {
            return mEndPeriod;
        }

        double Channel() {
            return mChannel;
        }
    private:
        double mStartPeriod;
        double mEndPeriod;
        unsigned int mChannel;
    };


    /// 
    ///   This exception should be used when data quality change
    /// 

    class quality_change : public std::runtime_error {
    public:
        /// Constructor
        ///
        /// @param msg error message
        ///
        ///

        quality_change(const std::string& msg, double change_time, unsigned int old_flag, unsigned int new_flag)
        :
        std::runtime_error(msg),
        mEventTime(change_time),
        mOldFlag(old_flag),
        mNewFlag(new_flag) {

        };

        double EventTime() {
            return mEventTime;
        }

        unsigned int OldFlag() {
            return mOldFlag;
        }

        unsigned int NewFlag() {
            return mNewFlag;
        }
    private:
        double mEventTime;
        unsigned int mOldFlag;
        unsigned int mNewFlag;
    };





} // end namespace tsa

#endif // __ALGOEXCEPTIONS_HPP
