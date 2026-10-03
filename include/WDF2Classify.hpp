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
#ifndef __WDF2CLASSIFY_HPP
#define __WDF2CLASSIFY_HPP


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
//#include <DCT.hpp>
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

        /// One candidate of the basis competition: its name, its mother and
        /// its packet depth, 0 for the pyramidal transform.
        struct Basis {
            std::string name;
            enum WaveletTransform::WaveletType type;
            unsigned int depth;
        };

        ///
        /// Constructor
        ///
        WDF2Classify(unsigned int window, unsigned int overlap, double thresh, double sigma,
                     unsigned int ncoeff, enum WaveletThreshold::WaveletThresholding WTh = WaveletThreshold::block);

        ///
        /// Copy constructor. Explicit (not compiler-generated): mBases holds
        /// unique_ptr<WaveletTransform>, so a deep copy has to rebuild each
        /// basis's WaveletTransform rather than copy the pointer.
        ///
        WDF2Classify(const WDF2Classify& from);

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
        WDF2Classify& operator=(const WDF2Classify& from);

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
            if (mFirstCall) {
                mStartTime = Data.GetStart();
                mFirstCall=false;
               
            }
            mSampling = Data.GetSampling();
           
        }

        void operator()(SeqViewDouble& Data, double sigma) {
            Dmatrix* in = Data.GetData();     
            if (in->size1() != 1) {
                LogSevere("TransientDetection: multichannels not implemented resize");
                throw bad_matrix_size("Wrong Matrix size");
            }
            SetData(*in, Data.GetScale());
            if (mFirstCall) {
                mStartTime = Data.GetStart();
                mFirstCall=false;
            }
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
                // Noise scale of the winning basis's own per-window MAD
                // estimate (see WaveletThreshold::operator()), i.e. the same
                // sigma that produced mSNR above -- carried through so a
                // downstream SNR recomputation (wdf.processes.wavelet_energy)
                // can use the convention that actually decided this trigger,
                // instead of a separate, frozen, time-domain sigma.
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

        /// The candidate bases, comma-separated, in the order they compete.
        std::string GetBases() const;

        //@}

        ///
        /// @name Setters
        ///
        //@{


        void SetData(Dmatrix& Data, double scale);

        /// Replace the candidate bases of the competition.
        ///
        /// Every window is transformed in each candidate and the one whose
        /// thresholded coefficients have the largest norm on their own noise
        /// scale wins; on a tie the later candidate wins, so the order is part
        /// of the definition. A name is an orthonormal mother (Haar, DaubC4 to
        /// DaubC20, Sym4, Sym8, Coif1, Coif2, or a long one: DaubC24, DaubC32,
        /// DaubC40, Sym10, Sym12, Sym16, Sym20, Coif3, Coif4, Coif5) for its
        /// pyramidal transform, or
        /// a mother followed by "P" and a depth D, as "Coif1P6", for the
        /// uniform level D of its wavelet-packet tree, whose coefficient
        /// layout is described at WaveletTransform's packet constructor. The
        /// trigger records the winner's name, which is what a reader needs to
        /// place and invert its coefficients.
        ///
        /// "LocalCos" followed by a segment length M, a power of 2 (as
        /// "LocalCos128"), is the orthonormal local cosine basis of segment M
        /// (WaveletTransform's LocalCos: Coifman-Meyer bell of half-width
        /// M / 2, periodic window edges, DCT-IV per segment), written
        /// frequency-major so that it has the layout of the packet level of
        /// depth log2 M: row k is DCT-IV bin k, centre (k + 1/2) fs / (2M),
        /// over the N / M segments in time order. No LocalCos is in the
        /// default list.
        ///
        /// Under the block rule the blocks of a packet basis are cut band by
        /// band (see WaveletThreshold::SetLayout), so a packet depth D is
        /// accepted only while each band of window / 2^D coefficients holds
        /// one full block of L = round(ln window): for a window of 512, L = 6
        /// and D is at most 6. The same holds for the rows of LocalCos M,
        /// D = log2 M: M <= 64 at a window of 512, M <= 128 at 1024 (L = 7),
        /// M <= 256 at 2048 (L = 8).
        ///
        /// @param names comma-separated candidate names
        /// @exception std::invalid_argument on an unknown or repeated name,
        ///            a packet depth above log2 of the window, an empty list,
        ///            or, under the block rule, a packet band shorter than
        ///            one block.
        void SetBases(const std::string& names);

        /// Leave the coefficients at or below fHz out of the competition.
        ///
        /// Every candidate drops the coefficients whose tile's upper
        /// frequency edge is <= fHz, read on its own layout (pyramid levels,
        /// packet bands, LocalCos rows; see WaveletThreshold::SetMinFrequency):
        /// they are out of the window's sigma, out of the block rule and out
        /// of EnWDF, and the trigger's coefficients hold zero there. At
        /// window 1024 and fs 2048, fHz 16 drops pyramid indices 0-15 and
        /// LocalCos128 rows 0-1. fHz <= 0, the default, keeps every
        /// coefficient and leaves the classifier bit for bit as without it.
        ///
        /// @param fHz minimum frequency in Hz, <= 0 for none
        /// @param fs  sampling rate of the searched stream in Hz
        /// @exception std::invalid_argument when fs <= 0 with fHz > 0, or
        ///            fHz >= fs / 2
        void SetMinFrequency(double fHz, double fs) {
            mWavThres.SetMinFrequency(fHz, fs);
        }

        /// The minimum frequency in Hz, 0 when every coefficient is kept.
        double GetMinFrequency() const {
            return mWavThres.GetMinFrequency();
        }

        /// How the block rule judges a block shorter than L = round(ln
        /// window), in every candidate (see WaveletThreshold::BlockRemainder):
        /// "legacy" (the default, bit for bit as before) like a full block
        /// against lambda n sigma^2; "merge" joins the remainder of a run to
        /// the block before it (7 + 1 = one block of 8); "scaled" judges a
        /// block of n < L at a full block's false-alarm probability,
        /// Qinv_{chi2_n}(Q_{chi2_L}(lambda L)) sigma^2. Other rules ignore it.
        ///
        /// @exception std::invalid_argument on an unknown name
        void SetBlockRemainder(const std::string& mode) {
            mWavThres.SetBlockRemainder(mode);
        }

        void SetBlockRemainder(enum WaveletThreshold::BlockRemainder mode) {
            mWavThres.SetBlockRemainder(mode);
        }

        enum WaveletThreshold::BlockRemainder GetBlockRemainder() const {
            return mWavThres.GetBlockRemainder();
        }



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
        bool mFirstCall;
        Dmatrix mBuff;
        EventFullFeatured mEvFF;

        // Candidate wavelet bases of the competition, one transform per
        // entry of mSpecs (see SetBases).
        // unique_ptr, not WaveletTransform by value: a WaveletTransform owns
        // GSL handles and has no move, so a vector of values would reallocate
        // every one of them as it grows. A vector of pointers only ever moves
        // the pointer.
        std::vector<std::unique_ptr<WaveletTransform>> mBases;
        std::vector<std::string> mBaseNames;
        enum WaveletThreshold::WaveletThresholding mT;
        WaveletThreshold mWavThres;
       // DCT mDct;
        //Dmatrix mBuffDct;
        Cs2HammingWindow mWindowing;
        std::vector<Basis> mSpecs;

        void Build();

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
