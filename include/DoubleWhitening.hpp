///
///   Copyright (C) 2004 by Elena Cuoco
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
/// @file   DoubleWhitening.hpp
/// @author Elena Cuoco <elena.cuoco@unibo.it>
/// @date   26 May 2005
///
/// @brief  Implement the DoubleWhitening in the time domain
///
#ifndef __DOUBLEWHITENING_HPP
#define __DOUBLEWHITENING_HPP

#include <boost/config.hpp>

///
/// @name System includes
///
//@{


//@}

///
/// @name Project includes
///
//@{

#include <SeqView.hpp>
#include <LatticeView.hpp>
#include <AlgoBase.hpp>
#include <FifoBuffer.hpp>
#include <CerealPersistence.hpp>
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
using namespace boost::numeric::ublas;
///
/// namespace
///
namespace tsa {

    ///
    ///
    /// A more detailed description of DoubleWhitening
    ///
    /**
     @brief Implement the double whitening filter in time domain
   
     */
    ///
    ///

    class DoubleWhitening : public AlgoBase {
    public:

        ///
        /// Constructor
        ///@param LV is the view containg the parameters for the Lattice Filter

        DoubleWhitening(LatticeView &LV, unsigned int OutputSize, unsigned int ExtraSize);

        DoubleWhitening(Dvector &ParcorF, Dvector &ParcorB, Dmatrix &ErrF, Dmatrix &ErrB, unsigned int OutputSize,
                        unsigned int ExtraSize);


        void init(LatticeView &LV);

        ///
        /// Destructor
        ///
        virtual ~DoubleWhitening();

        //@{

        /**
         * Declaration of execute operation
         *
         * @param InputData Matrix containing Time Series
         * @param WhitenedData Matrix containing the WhitenedData
         */
        void operator<<(SeqViewDouble &Data) {
            Dmatrix *in = Data.GetData();

            if (in->size1() != 1) {
                LogSevere("DoubleWhitening: multichannels not implemented resize");
                throw bad_matrix_size("Wrong Matrix size");
            }

            SetData(*in, Data.GetScale());
            

            if (mFirstCall) {
                mStartTime = Data.GetStart();
                mFirstCall=false;
                mSampling = Data.GetSampling();
               
            }
        }

        void operator>>(SeqViewDouble &outdata) {
            Dmatrix *out = outdata.GetData();
            out->resize(1, mOutputSize);
            GetData(*out);
            outdata.SetStart(mStartTime);
            outdata.SetSampling(mSampling);
            outdata.SetScale(1.0);
            mStartTime += mSampling * mOutputSize;
            
        }
         
        DoubleWhitening& Input(SeqViewDouble &Data) {
        Dmatrix *in = Data.GetData();

        if (in->size1() != 1) {
            LogSevere("DoubleWhitening: multichannels not implemented resize");
            throw bad_matrix_size("Wrong Matrix size");
        }

        SetData(*in, Data.GetScale());
       

        if (mFirstCall){
        mStartTime = Data.GetStart();
        mSampling = Data.GetSampling();
        mFirstCall=false;
       
        }
        
       
        return *this;

        }

        DoubleWhitening& Output(SeqViewDouble &outdata) {
        Dmatrix *out = outdata.GetData();
        out->resize(1, mOutputSize);
        GetData(*out);
        outdata.SetStart(mStartTime);
        outdata.SetSampling(mSampling);
        outdata.SetScale(1.0);
        mStartTime += mSampling * mOutputSize;
    

        return *this;
    }
           void operator()(SeqViewDouble& InputData, SeqViewDouble& OutData) {
            Dmatrix* in = InputData.GetData();
            Dmatrix* out = OutData.GetData();
            if (in->size1() != 1) {
            LogSevere("DoubleWhitening: multichannels not implemented resize");
            throw bad_matrix_size("Wrong Matrix size");
            }

            SetData(*in, InputData.GetScale());
        

            if (mFirstCall){
            mStartTime = InputData.GetStart();
            mFirstCall=false;
            mSampling = InputData.GetSampling(); 
            }
            OutData.SetSampling(mSampling);  
            out->resize(1, mOutputSize);
            GetData(*out);
               
            OutData.SetStart(mStartTime);
 
            OutData.SetScale(1.0);
            mStartTime += mSampling* mOutputSize;
                         
               
            
        }

       


        void Load(const char *filename, const char *fmt = nullptr) {
            tsa::LoadBinary(filename, *this);
        }

        void Save(const char *filename, const char *fmt = nullptr) {
            tsa::SaveBinary(filename, *this);
        }

        template<class Archive>
        void serialize(Archive& ar) {
            ar(mBuffer, mFirstCall, mOutputSize, mTotSize, mOrder, mStartTime, mSampling,
               DvectorProxy(mParcorF), DvectorProxy(mParcorB), DmatrixProxy(mErrF), DmatrixProxy(mErrB),
               mStatus, DmatrixProxy(mEf), DmatrixProxy(mEb), DmatrixProxy(mWhitened));
        }



        //@}

        ///
        /// @name Getters
        ///
        //@{
        void GetData(Dmatrix &DWOutput);
        int GetDataNeeded();

        ///
        ///@return the whitened buffer
        ///

        Dmatrix *GetWhitenedMatrix() {
            return &mWhitened;
        }
        //@}

        ///
        /// @name Setters
        ///
        //@{
        void SetData(Dmatrix &Data, double scale);
        void SetOutputSize(unsigned int OutputSize,unsigned int ExtraSize);
    
      
        //@}


    protected:

    private:
        FifoBuffer mBuffer;
        bool mFirstCall;
        unsigned int mOutputSize;
        unsigned int mTotSize;
        unsigned int mOrder;
        double mStartTime;
        double mSampling;
        Dvector mParcorF;
        Dvector mParcorB;
        Dmatrix mErrF;
        Dmatrix mErrB;
        int mStatus;
        Dmatrix mEf;
        Dmatrix mEb;
        Dmatrix mWhitened;

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

} //end namespace

#endif // ___DOUBLEWHITENING_HPP


