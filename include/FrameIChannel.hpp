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
/// @file   FrameIStream.hpp
/// @author Giancarlo Cella <giancarlo.cella@pi.infn.it>
/// @date   Sat Nov 13 17:21:06 2004
///
/// @brief  Interface for FrameIStream
///
#ifndef __FRAMEICHANNEL_HPP
#define __FRAMEICHANNEL_HPP

////// @name System includes
///
//@{



#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>



#include <deque>
#include <FrameL.h>

//@}

///
/// @name Project includes
///
//@{
#include <AlgoBase.hpp>
#include <SeqView.hpp>

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

    /**
     * @brief A source of data taken from a Frame file
     *
     * This class can be used to read data from a frame file, in a single channel. 
     * 
     *
     *
     **/
    class FrameIChannel : public AlgoBase {
    public:


        /// Constructor
        ///
        /// @param fileName the name of the frame file (or a ffl file)
        /// @param channelName the channel's names
        /// @param dLength length of data that will be returned by GetData()
        /// @param tStart start time of the data returned by GetData()
        ///
        ///
        FrameIChannel(const std::string& fileName, const std::string& channelName,
                double dLength = 1.0, double tStart = 0.0);


        ///
        /// Destructor
        ///
        ~FrameIChannel();

        ///
        /// @name Operations
        ///
        //@{

        double NextSlice();


        //@}

        ///
        /// @name Getters
        ///
        //@{

        /// Get a specified slice of data. After this call, start time will be
        /// set to tStart+dLength and data length to dLength
        ///
        /// @param rSeqView the view to fill with data
        /// @param tStart start time of the data returned 
        /// @param dLength length of data returned by 
        ///
        ///
        bool GetData(SeqViewDouble& rSeqView, double tStart, double dLength);

        /// Get a slice of data the current data length, starting 
        /// from the current start time.
        ///
        /// @param rSeqView the view to fill with data
        ///
        ///
        bool GetData(SeqViewDouble& rSeqView);

        static std::string GetChannelList(const std::string& fileName, int gtime = 0);

        //@}

        ///
        /// @name Setters
        ///
        //@{

        void SetStartTime(double tStart);

        void SetDataLength(double dLength);

        void SetAutoIncrement(bool status);

        //@}

    protected:

    private:

        void PushFrVect(FrVect *frv, Dmatrix& data, unsigned int row, double offset, double slope);

        bool ReopenIfModified();

        std::string mFileName;
        FrFile *miFile;
        std::string mChannelName;
        double mStartTime;
        double mDataLength;
        FrVect *mFrameVect;
        bool mAutoIncrement;
        time_t mLastModification;
    };

    ///
    /// @name Inline methods
    ///
    //@{


    //@}

    ///
    /// @name External references
    ///
    //@{

    //@}



} // end namespace tsa

#endif // __FRAMEICHANNEL_HPP

