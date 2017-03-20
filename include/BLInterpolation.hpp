
/**
 *
 *   Copyright (C) 2004 by Giancarlo Cella                                 
 *   giancarlo.cella@pi.infn.it                                            
 *                                                                         
 *   This program is free software; you can redistribute it and/or modify  
 *   it under the terms of the GNU General Public License as published by  
 *   the Free Software Foundation; either version 2 of the License, or     
 *   (at your option) any later version.                                   
 *                                                                         
 *   This program is distributed in the hope that it will be useful,       
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         
 *   GNU General Public License for more details.                          
 *                                                                         
 *   You should have received a copy of the GNU General Public License     
 *   along with this program; if not, write to the                         
 *   Free Software Foundation, Inc.,                                       
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             
 *
 * @file   BLInterpolation.hpp
 * @author Giancarlo Cella <giancarlo.cella@pi.infn.it>
 * @date   Sat Nov 13 17:21:06 2004
 * 
 * @brief  Band limited interpolation
 */
#ifndef __BLINTERPOLATION_HPP
#define __BLINTERPOLATION_HPP

/**
 * @name System includes
 */
//@{
#include <queue>
#include <deque>
#include <gsl/gsl_sf.h>
//@}

/**
 * @name Project includes
 */
//@{
#include <AlgoBase.hpp>
#include <SeqView.hpp>
//@}

/**
 * @name Local includes
 */
//@{


//@}

/**
 * @name Forward references
 */
//@{


//@}

/** 
 * tsa namespace
 */
namespace tsa {

    /**  
     * @brief Band limited interpolation.
     *
     * 
     */
    class BLInterpolation : public AlgoBase {
    public:

        enum NormalizationType {
            NONormalization,
            DCNormalization
        };

        /** 
         * Constructor.
         * 
         * @param channels number of channels
         * @param outdata number of resampled data returned at each call
         * @param irate input rate
         * @param orate output rate
         * @param order order of filter
         * @param alpha window parameter
         */
        BLInterpolation(unsigned int channels,
                unsigned int outdata,
                unsigned int irate,
                unsigned int orate,
                unsigned int order,
                double alpha = 1.0,
                enum NormalizationType nt = NONormalization
                );

        /**
         * Copy constructor
         *
         * @param from The instance that must be copied
         */
        BLInterpolation(const BLInterpolation& from);

        /**
         * Destructor
         */
        ~BLInterpolation();

        /**
         * Assignement operator
         * 
         * @param from The instance to be assigned from
         *
         * @return a reference to a new object
         */
        BLInterpolation& operator=(const BLInterpolation& from);


        /** 
         * @name User interface
         */
        //@{

        /** 
         * Add data to be resampled. This method can be called repeatedly,
         * each time with a different chunk of data. The chunks are considered
         * as consecutive pieces of a continuous stream.
         * 
         * @param indata view containing input data
         * 
         * @return a reference to an instance of this class
         *
         * @pre the number of rows in indata must be equal to the number of channels 
         * 
         */

        BLInterpolation& Input(SeqViewDouble& indata);
        /** 
         * Get resampled data. If there are enough resampled data available
         * these are returned, otherwise an exception is raised.
         * 
         * @param outdata view which will be filled with resampled data
         * 
         *
         * @return a reference to an instance of this class
         *
         * @exception no_data_available there are not enough resampled data available
         * 
         * @post if no exception is raised outdata has a number of rows equal to the number
         * of channels and a number of columns equal to the number of returned data
         *
         */

        BLInterpolation& Output(SeqViewDouble& outdata);


        //@}


        /**
         * @name Operations
         */
        //@{



        //@}

        /**
         * @name Getters
         */
        //@{

        long int GetDataAvailable() {
            return resampled_available();
        }

        /** 
         * Get resampled data
         * 
         * @param outdata a matrix which will be filled with resampled data
         * 
         * @return the number of resampled data returned
         */
        unsigned int GetData(Dmatrix& outdata);

        /** 
         * Start time of the next sequence of resampled data.
         * 
         * 
         * @return the start time of the next sequence of resampled data
         */
        double GetStartTime();


        //@}

        /**
         * @name Setters
         */
        //@{

        /** 
         * Add data to be resampled
         * 
         * @param indata a matrix which contains input data
         * @param scale a scale parameter for input data
         */
        void SetData(Dmatrix& indata, double scale);



        //@}


    protected:

    private:


        /** 
         * Initialize internal structures
         * 
         */
        void Init();

        void NORenormalization();

        void DCRenormalization();

        /** 
         * Kaiser window.
         * 
         * @param x position in the window (between -1 and 1)
         * 
         * @return the value of Kaiser window at index k
         */
        double Kaiser(double x);

        unsigned int mChannels; /**< Number of channels to resample */
        unsigned int mOutData; /**< Number of resampled data for channel that will be returned if possible at each call */
        unsigned int mInputRate; /**< Input rate of data */
        unsigned int mOutputRate; /**< Output rate of data */
        unsigned int mOrder; /**< Order of the filter */
        double mAlpha; /**< Parameter of the Kaiser window */

        std::queue<Dvector*> mRepository; /**< Repository for unused data points */
        std::deque<Dvector*> mBuffer; /**< Buffer for incoming data points */
        long int mBufferBase; /**< Start of the buffer, in ticks units */


        double mRho; /**< Normalization factor for upsampling/downsampling */
        Dvector *mFilter; /**< Template for the filter */
        long int mFilterCenter; /**< Center of the filter, in ticks units */

        Dvector mNormalization;
        NormalizationType mNormalizationType;

        bool mFirstData; /**< Flag: is the actual view the first submitted? */
        double mStartTime; /**< Start (physical) time for resampling */
        double mSampling; /**< Physical sampling rate */



        /** 
         * Add a new data point to the buffer. If possible this is taken from
         * the repository, allocated otherwise.
         * 
         */
        void add_back_point();

        /** 
         * Delete some points from the buffer (the oldest ones) and
         * increment the start of the buffer position mBuffer
         * 
         * @param n number of points to delete from the buffer
         */
        void del_front_point(unsigned int n);

        /** 
         * This function returns the number of resampled data 
         * which are available at the current time.
         * 
         * @return resampled data available
         */
        long int resampled_available();
    };

    /**
     * @name Inline methods
     */
    //@{

    //@}


    /** 
     * @name External references
     */
    //@{

    //@}


} // end namespace tsa

#endif // __BLINTERPOLATION_HPP
