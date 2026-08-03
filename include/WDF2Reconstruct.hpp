///
///   Copyright (C) 2005 by Elena Cuoco
///   elena.cuoco@unibo.it
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
/// @author Elena Cuoco <elena.cuoco@unibo.it>
/// @date   2005
///
/// @brief  Wavelet based method for transient detection (Wavelet Detection Filter)
///
#ifndef __WDF2RECONSTRUCT_HPP
#define __WDF2RECONSTRUCT_HPP


///
/// @name System includes
///
//@{
#include <string>
#include <vector>
#include <utility>
#include <memory>

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

    class WDF2Reconstruct : public AlgoBase {
    public:

        ///
        /// Constructor
        ///
        WDF2Reconstruct(unsigned int window, unsigned int overlap, double thresh, double sigma,
                     unsigned int ncoeff, enum WaveletThreshold::WaveletThresholding WTh = WaveletThreshold::cuoco);

        ///
        /// Copy constructor. Explicit (not compiler-generated): mBases holds
        /// unique_ptr<WaveletTransform>, so a deep copy has to rebuild each
        /// basis's WaveletTransform rather than copy the pointer.
        ///
        WDF2Reconstruct(const WDF2Reconstruct& from);

        ///
        /// Destructor
        ///
        ~WDF2Reconstruct();

        ///
        /// Assignement operator
        ///
        /// @param from The instance to be assigned from
        ///
        WDF2Reconstruct& operator=(const WDF2Reconstruct& from);
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
            //mStartTime -= mSampling * static_cast<double> (WDF2Reconstruct::GetDataNeeded());
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





        int operator()(EventFullFeatured& Ev) {
            double abov;
            double sigmaWin;
            Dvector Cmax;
            int level;
            std::string Wave;
            unsigned int res = GetDataVector(abov, sigmaWin, Cmax, level, Wave);

            if (res == 1) {

                mEvFF.mlevel = static_cast<double> (level);

                for (unsigned int i = 0; i < mNCoeff; i++) {
                    mEvFF.mCoeff[i] = Cmax[i];
                }
                mEvFF.mTime = mStartTime;
                mEvFF.mSNR = abov;
                mEvFF.mWave = Wave;
                mEvFF.mSigma = sigmaWin;
                Ev = mEvFF;
            }

            mStartTime += mSampling * static_cast<double> (mStep);
            return res;
        }


        ///
        /// @name Getters
        ///
        //@{


        unsigned int GetDataVector(double& abov, double& sigmaWin, Dvector& Cmax, int& levelR, std::string& Wave);

        void GetEvent(EventFullFeatured &Ev) {

            Ev.mTime = mEvFF.mTime;
            Ev.mSNR = mEvFF.mSNR;
            Ev.mWave = mEvFF.mWave;
            Ev.mCoeff = mEvFF.mCoeff;
            Ev.mSigma = mEvFF.mSigma;
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
        FifoBuffer mBuffer;

        double mStartTime;
        double mSampling;
        Dmatrix mBuff;
        EventFullFeatured mEvFF;

        // Same candidate wavelet basis set as WDF2Classify -- see that
        // class's GetDataVector for why the biorthogonal B-spline family is
        // excluded. unique_ptr, not WaveletTransform by value: see the same
        // member in WDF2Classify.hpp for why.
        std::vector<std::unique_ptr<WaveletTransform>> mBases;
        std::vector<std::string> mBaseNames;
        enum WaveletThreshold::WaveletThresholding mT;
        WaveletThreshold mWavThres;
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
