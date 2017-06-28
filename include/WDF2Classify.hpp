///
///   Copyright (C) 2005 by Elena Cuoco
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
/// @file   WavTransientDetection.hpp
/// @author Elena Cuoco <elena.cuoco@ego-gw.it>
/// @date   2005
///
/// @brief  Wavelet based method for transient detection (Wavelet Detection Filter)
///
#ifndef __WDF2CLASSIFY_HPP
#define __WDF2CLASSIFY_HPP


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

//@}

///
/// @name Local includes
///
//@{
#include <AlgoBase.hpp>
#include <SeqView.hpp>
#include <FifoBuffer.hpp>
#include <AlgoExceptions.hpp>

#include <EventFullFeatured.hpp>
#include <WaveletTransform.hpp>
#include <WaveletThreshold.hpp>
#include <DCT.hpp>
#include <Cs2HammingWindow.hpp>
#include <BaseView.hpp>
#include <math.h>
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
    /// @brief Time domain detection of transients based on wavelet transform
    ///
    ///
    ///
    ///
    ///

    class WDF2Classify : public AlgoBase {
    public:

        ///
        /// Constructor
        ///
        WDF2Classify(unsigned int window, unsigned int overlap, double thresh, double sigma, unsigned int ncoeff, enum WaveletThreshold::WaveletThresholding WTh = WaveletThreshold::cuoco);

        ///
        /// Destructor
        ///
        ~WDF2Classify();

        ///
        /// Assignement operator
        ///
        /// @param from The instance to be assigned from
        ///
        /// @return a reference to a new object

        ///
        /// @name Operations
        ///
        ///@{

        void operator<<(SeqViewDouble& Data) {
            Dmatrix* in = Data.GetData();

            if (in->size1() != 1) {
                LogSevere("TransientDetection: multichannels not implemented resize");
                throw bad_matrix_size("Wrong Matrix size");
            }

            SetData(*in, Data.GetScale());
            mStartTime = Data.GetStart();
            mSampling = Data.GetSampling();
        }

        void operator()(SeqViewDouble& Data, double sigma) {
            Dmatrix* in = Data.GetData();

            if (in->size1() != 1) {
                LogSevere("TransientDetection: multichannels not implemented resize");
                throw bad_matrix_size("Wrong Matrix size");
            }

            SetData(*in, Data.GetScale());
            mStartTime = Data.GetStart();
            mSampling = Data.GetSampling();
            mWavThres.SetSigma(sigma);
        }





        void operator()(EventFullFeatured& Ev) {
            double abov;
            Dvector Cmax;
            int level;
            int k,j;
            std::string Wave;
            //                //old way to find time of the event
            //double factorT;
            unsigned int res = GetDataVector(abov, Cmax, level, Wave);


            if (res == 1) {

                mEvFF.mlevel = static_cast<double> (level);

                for (unsigned int i = 0; i < mNCoeff; i++) {
                    mEvFF.mCoeff[i] = Cmax[i];
                }
                //old way to find time of the event
                //j= log2(level+1.0);
                //k =  pow(2.0,j)-1.0;
                //printf("level:%d  j:%d  k:%d \n",level,j,k);
                mEvFF.mTime = mStartTime+mSampling*mEvFF.mlevel;//*(k+1.0/2.0)/pow(2.0,j);
                mEvFF.mSNR = abov;
                mEvFF.mWave = Wave;
                Ev = mEvFF;
            }
            mStartTime += mSampling * static_cast<double> (mStep);
        }


        ///
        /// @name Getters
        ///
        //@{


        unsigned int GetDataVector(double& abov, Dvector& Cmax, int& levelR, std::string& Wave);

        void GetEvent(EventFullFeatured &Ev) {

            Ev.mTime = mEvFF.mTime;
            Ev.mSNR = mEvFF.mSNR;
            Ev.mWave = mEvFF.mWave;
            Ev.mCoeff = mEvFF.mCoeff;
        }

        /**
         * Get the number of data needed in order to be able to 
         * call GetData successfully. If the returned value is less or 
         * equal than zero no data are needed.
         *
         * @return the needed data
         */
        int GetDataNeeded();

        //@}

        ///
        /// @name Setters
        ///
        //@{


        void SetData(Dmatrix& Data, double scale);



        //@}


    protected:

    private:
        unsigned int mWindow;
        unsigned int mOverlap;
        unsigned int mStep;
        unsigned int mNCoeff;
        double mThresh;
        double mSigma;
        double mSigmaH;
        double mSigma4;
        double mSigmaC8;
        double mSigma10;
        double mSigma12;
        double mSigmaC16;
        double mSigma20;
        double mSigmaC20;
        double mSigmaBsC307;
        double mSigmaBsC309;
        double mSigmaDCT;
        FifoBuffer mBuffer;

        double mStartTime;
        double mSampling;
        Dmatrix mBuff;
        EventFullFeatured mEvFF;

        enum WaveletTransform::WaveletType mWtH;
        WaveletTransform mWTH;
        enum WaveletTransform::WaveletType mWt4;
        WaveletTransform mWT4;
        enum WaveletTransform::WaveletType mWtC8;
        WaveletTransform mWTC8;
        enum WaveletTransform::WaveletType mWt10;
        WaveletTransform mWT10;
        enum WaveletTransform::WaveletType mWt12;
        WaveletTransform mWT12;
        enum WaveletTransform::WaveletType mWtC16;
        WaveletTransform mWTC16;
        enum WaveletTransform::WaveletType mWt20;
        WaveletTransform mWT20;
        enum WaveletTransform::WaveletType mWtC20;
        WaveletTransform mWTC20;
        enum WaveletTransform::WaveletType mWtBsC307;
        WaveletTransform mWTBsC307;
        enum WaveletTransform::WaveletType mWtBsC309;
        WaveletTransform mWTBsC309;
        enum WaveletThreshold::WaveletThresholding mT;
        WaveletThreshold mWavThres;
        DCT mDct;
        Dmatrix mBuffDct;
        Cs2HammingWindow mWindowing;

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

}
//end namespace

#endif //  __WAVTRANSIENTDETECTION_HPP
