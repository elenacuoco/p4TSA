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
/// @file   DoubleWhitening.hpp
/// @author Elena Cuoco <elena.cuoco@ego-gw.it>
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
            mSampling = Data.GetSampling();

            if (mFirstCall) {
                mStartTime = Data.GetStart();
                mFirstCall=false;
               
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
        mSampling = Data.GetSampling();

        if (mFirstCall){
        mStartTime = Data.GetStart();
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
            mSampling = InputData.GetSampling(); 
            OutData.SetSampling(InputData.GetSampling());  

            if (mFirstCall){
            mStartTime = InputData.GetStart();
            mFirstCall=false;
            }
            out->resize(1, mOutputSize);
            GetData(*out);
               
            OutData.SetStart(mStartTime);
            OutData.SetSampling(InputData.GetSampling());  
            mSampling = InputData.GetSampling(); 
            OutData.SetScale(1.0);
            mStartTime += InputData.GetSampling()* mOutputSize;
                         
               
            
        }

       


        void Load(const char *filename, const char *fmt = "txt") {
            eternity::xml_archive fa;
            fa.open(filename, eternity::archive::load);
            xml_serialize(fa, "");
            fa.close();
        }

        void Save(const char *filename, const char *fmt = "txt") {
            eternity::xml_archive fa;
            fa.open(filename, eternity::archive::store);
            xml_serialize(fa, "");
            fa.close();
        }

        void xml_serialize(eternity::xml_archive &xml, const char *p) {
            char buffer[1024];

            if (xml.is_loading()) {

                snprintf(buffer, 1024, "%s.mBuffer", p);
                mBuffer.xml_serialize(xml, buffer);
                snprintf(buffer, 1024, "%s.mFirstCall", p);
                BOOL_XML_SERIALIZE(mFirstCall, xml, buffer);
                snprintf(buffer, 1024, "%s.mOutputSize", p);
                xml.read(buffer, mOutputSize, 0);
                snprintf(buffer, 1024, "%s.mTotSize", p);
                xml.read(buffer, mTotSize, 0);
                snprintf(buffer, 1024, "%s.mOrder", p);
                xml.read(buffer, mOrder, 0);
                snprintf(buffer, 1024, "%s.mStartTime", p);
                xml.read(buffer, mStartTime, 0);
                snprintf(buffer, 1024, "%s.mSampling", p);
                xml.read(buffer, mSampling, 0);
                snprintf(buffer, 1024, "%s.mParcorF", p);
                DVECTOR_XML_SERIALIZE(mParcorF, xml, buffer);
                snprintf(buffer, 1024, "%s.mParcorB", p);
                DVECTOR_XML_SERIALIZE(mParcorB, xml, buffer);
                snprintf(buffer, 1024, "%s.mErrF", p);
                DMATRIX_XML_SERIALIZE(mErrF, xml, buffer);
                snprintf(buffer, 1024, "%s.mErrB", p);
                DMATRIX_XML_SERIALIZE(mErrB, xml, buffer);
                snprintf(buffer, 1024, "%s.mStatus", p);
                xml.read(buffer, mStatus, 0);
                snprintf(buffer, 1024, "%s.mEf", p);
                DMATRIX_XML_SERIALIZE(mEf, xml, buffer);
                snprintf(buffer, 1024, "%s.mEb", p);
                DMATRIX_XML_SERIALIZE(mEb, xml, buffer);
                snprintf(buffer, 1024, "%s.mWhitened", p);
                DMATRIX_XML_SERIALIZE(mWhitened, xml, buffer);


            } else {

                snprintf(buffer, 1024, "%s.mBuffer", p);
                mBuffer.xml_serialize(xml, buffer);
                snprintf(buffer, 1024, "%s.mFirstCall", p);
                BOOL_XML_SERIALIZE(mFirstCall, xml, buffer);
                snprintf(buffer, 1024, "%s.mOutputSize", p);
                xml.write(buffer, mOutputSize);
                snprintf(buffer, 1024, "%s.mTotSize", p);
                xml.write(buffer, mTotSize);
                snprintf(buffer, 1024, "%s.mOrder", p);
                xml.write(buffer, mOrder);
                snprintf(buffer, 1024, "%s.mStartTime", p);
                xml.write(buffer, mStartTime);
                snprintf(buffer, 1024, "%s.mSampling", p);
                xml.write(buffer, mSampling);
                snprintf(buffer, 1024, "%s.mParcorF", p);
                DVECTOR_XML_SERIALIZE(mParcorF, xml, buffer);
                snprintf(buffer, 1024, "%s.mParcorB", p);
                DVECTOR_XML_SERIALIZE(mParcorB, xml, buffer);
                snprintf(buffer, 1024, "%s.mErrF", p);
                DMATRIX_XML_SERIALIZE(mErrF, xml, buffer);
                snprintf(buffer, 1024, "%s.mErrB", p);
                DMATRIX_XML_SERIALIZE(mErrB, xml, buffer);
                snprintf(buffer, 1024, "%s.mStatus", p);
                xml.write(buffer, mStatus);
                snprintf(buffer, 1024, "%s.mEf", p);
                DMATRIX_XML_SERIALIZE(mEf, xml, buffer);
                snprintf(buffer, 1024, "%s.mEb", p);
                DMATRIX_XML_SERIALIZE(mEb, xml, buffer);
                snprintf(buffer, 1024, "%s.mWhitened", p);
                DMATRIX_XML_SERIALIZE(mWhitened, xml, buffer);


            }
        }



        //@}

        ///
        /// @name Getters
        ///
        //@{
        void GetData(Dmatrix &DWOutput);

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
        void SetOutputSize(unsigned int OutputSize,unsigned int ExtraSize){
            mOutputSize=OutputSize;
            mTotSize=OutputSize+ExtraSize;
            mWhitened(1, mTotSize);
            mBuffer(1);
        }
      
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


