/**
 *
 *   Copyright (C) 2004 by Elena Cuoco
 *   elena.cuoco@ego-gw.it
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
 * @file   LSLfilter.hpp
 * @author Elena Cuoco <elena.cuoco@ego-gw.it>
 * @date   2005
 *
 * @brief  Least Squares Lattice  filter
 */
#ifndef __LSLFILTER_HPP
#define __LSLFILTER_HPP


/**
 * @name System includes
 */
//@{


//@}

/**
 * @name Project includes
 */
//@{
#include <AlgoBase.hpp>
#include <SeqView.hpp>
#include <LatticeView.hpp>
#include <FifoBuffer.hpp>
#include <LSLLearning.hpp>
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
 * namespace
 */
using namespace boost::numeric::ublas;

namespace tsa {

    /**
     * @brief   Algorithm for the filter phase of the Adaptive Least Squares Lattice
     */
    class LSLfilter : public AlgoBase {
    public:

        /**
         * Constructor
         * 
         * @param Order Order of the filter
         * @param sigma guessed value for the initial sigma
         * @param Lwsp Lenght of workspace
         * @param lambda forgetting factor
         *  
         */
        LSLfilter(LSLLearning& LSL, double lambda = 1.0, unsigned int size = 1, bool Norm = false);



        /**
         * Destructor
         */
        ~LSLfilter();

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

        void xml_serialize(eternity::xml_archive& xml, const char *p) {
            char buffer[1024];

            snprintf(buffer, 1024, "%s.mBuffer", p);
            mBuffer.xml_serialize(xml, buffer);

            if (xml.is_loading()) {

                snprintf(buffer, 1024, "%s.mWinSize", p);
                xml.read(buffer, mWinSize, 0);
                snprintf(buffer, 1024, "%s.mOrder", p);
                xml.read(buffer, mOrder, 0);
                snprintf(buffer, 1024, "%s.mLambda", p);
                xml.read(buffer, mLambda, 0);
                snprintf(buffer, 1024, "%s.mSigma", p);
                DVECTOR_XML_SERIALIZE(mSigma, xml, buffer);
                snprintf(buffer, 1024, "%s.mNorm", p);
                BOOL_XML_SERIALIZE(mNorm, xml, buffer);
                snprintf(buffer, 1024, "%s.mSigma0", p);
                xml.read(buffer, mSigma0, 0);
                snprintf(buffer, 1024, "%s.mStartTime", p);
                xml.read(buffer, mStartTime, 0);
                snprintf(buffer, 1024, "%s.mSampling", p);
                xml.read(buffer, mSampling, 0);
                snprintf(buffer, 1024, "%s.mFirstCall", p);
                BOOL_XML_SERIALIZE(mFirstCall, xml, buffer);
                snprintf(buffer, 1024, "%s.mEF", p);
                DMATRIX_XML_SERIALIZE(mEF, xml, buffer);
                snprintf(buffer, 1024, "%s.mEB", p);
                DMATRIX_XML_SERIALIZE(mEB, xml, buffer);
                snprintf(buffer, 1024, "%s.mEpf", p);
                DMATRIX_XML_SERIALIZE(mEpf, xml, buffer);
                snprintf(buffer, 1024, "%s.mEpb", p);
                DMATRIX_XML_SERIALIZE(mEpb, xml, buffer);
                snprintf(buffer, 1024, "%s.mKf", p);
                DVECTOR_XML_SERIALIZE(mKf, xml, buffer);
                snprintf(buffer, 1024, "%s.mKb", p);
                DVECTOR_XML_SERIALIZE(mKb, xml, buffer);
                snprintf(buffer, 1024, "%s.mNG", p);
                DVECTOR_XML_SERIALIZE(mG, xml, buffer);
                snprintf(buffer, 1024, "%s.mF0", p);
                xml.read(buffer, mF0, 0);

            } else {

                snprintf(buffer, 1024, "%s.mWinSize", p);
                xml.write(buffer, mWinSize);
                snprintf(buffer, 1024, "%s.mOrder", p);
                xml.write(buffer, mOrder);
                snprintf(buffer, 1024, "%s.mLambda", p);
                xml.write(buffer, mLambda);
                snprintf(buffer, 1024, "%s.mSigma", p);
                DVECTOR_XML_SERIALIZE(mSigma, xml, buffer);
                snprintf(buffer, 1024, "%s.mNorm", p);
                BOOL_XML_SERIALIZE(mNorm, xml, buffer);
                snprintf(buffer, 1024, "%s.mSigma0", p);
                xml.write(buffer, mSigma0);
                snprintf(buffer, 1024, "%s.mStartTime", p);
                xml.write(buffer, mStartTime);
                snprintf(buffer, 1024, "%s.mSampling", p);
                xml.write(buffer, mSampling);
                snprintf(buffer, 1024, "%s.mFirstCall", p);
                BOOL_XML_SERIALIZE(mFirstCall, xml, buffer);
                snprintf(buffer, 1024, "%s.mEF", p);
                DMATRIX_XML_SERIALIZE(mEF, xml, buffer);
                snprintf(buffer, 1024, "%s.mEB", p);
                DMATRIX_XML_SERIALIZE(mEB, xml, buffer);
                snprintf(buffer, 1024, "%s.mEpf", p);
                DMATRIX_XML_SERIALIZE(mEpf, xml, buffer);
                snprintf(buffer, 1024, "%s.mEpb", p);
                DMATRIX_XML_SERIALIZE(mEpb, xml, buffer);
                snprintf(buffer, 1024, "%s.mKf", p);
                DVECTOR_XML_SERIALIZE(mKf, xml, buffer);
                snprintf(buffer, 1024, "%s.mKb", p);
                DVECTOR_XML_SERIALIZE(mKb, xml, buffer);
                snprintf(buffer, 1024, "%s.mNG", p);
                DVECTOR_XML_SERIALIZE(mG, xml, buffer);
                snprintf(buffer, 1024, "%s.mF0", p);
                xml.write(buffer, mF0);


            }
        }



        /**
         * @name Operations
         */
        //@{

        /**
         * Declaration of execute operation
         *
         * @param InputData Matrix containing Time Series
         * @param WhitenedData Matrix containing the WhitenedData
         * @brief to be used only when data are contiguos (offline analysis)
         */

        void operator<<(SeqViewDouble& Data) {
            Dmatrix* in = Data.GetData();

            if (in->size1() != 1) {
                LogSevere("LSLfilter: multichannels not implemented resize");
               
            }

            SetData(*in, Data.GetScale());

            if (mFirstCall) {
                mFirstCall = false;
                mStartTime = Data.GetStart();
                mSampling = Data.GetSampling();
            }
        }

        void operator>>(SeqViewDouble& outdata) {
            Dmatrix *out = outdata.GetData();
            out->resize(1, mWinSize);
            GetData(*out);
            outdata.SetStart(mStartTime);
            outdata.SetSampling(mSampling);
            outdata.SetScale(1.0);
            mStartTime += mSampling*mWinSize;
        }

        //for the online process  

        /**
         * 
         * @param Data 
         * @param outdata 
         * @brief for online process
         */


        void operator()(SeqViewDouble& Data, SeqViewDouble& outdata) {
            Dmatrix* in = Data.GetData();

            if (in->size1() != 1) {
                LogSevere("LSLfilter: multichannels not implemented resize");
               
            }

            SetData(*in, Data.GetScale());

            mStartTime = Data.GetStart();
            mSampling = Data.GetSampling();


            Dmatrix *out = outdata.GetData();
            out->resize(1, mWinSize);
            GetData(*out);
            outdata.SetStart(Data.GetStart());
            outdata.SetSampling(Data.GetSampling());
            outdata.SetScale(1.0);

        }



        //@}

        ///
        /// @name Getters
        ///
        //@{
        void GetData(Dmatrix& DWOutput);

        ///
        ///@return the whitened buffer
        ///

        Dmatrix *GetWhitenedMatrix() {
            return &mEF;
        }
        //@}
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

        //@}

        /**
         * @name Getters
         */
        //@{

        unsigned int GetOrder() {
            return mOrder - 1;
        }

        double GetParcorForward(unsigned int j) {
            return mKf(j);
        }

        /**
         *
         */
        double GetParcorBackward(unsigned int j) {
            return mKb(j);
        }

        double GetEpf(unsigned int j) {
            return mEpf(mF0, j);
        }

        double GetErrorForward(unsigned int j) {
            return mEF(mF0, j);
        }

        /**
         */
        double GetErrorBackward(unsigned int j) {
            return mEB(mF0, j);
        }

        /**
         */
        double GetSigma(unsigned int j) {
            return mSigma(j);
        }

        //@}

        /**
         * @name Setters
         */
        //@{

        //@}


    protected:

    private:
        FifoBuffer mBuffer;
        unsigned int mWinSize;
        unsigned int mOrder; /**< Order of the filter */
        double mLambda; /**< Forgetting Factor */
        Dvector mSigma; /**<The estimated rms */
        bool mNorm;
        double mSigma0;
        double mStartTime;
        double mSampling;
        bool mFirstCall;
        Dmatrix mEF; /**< ErrorForward */
        Dmatrix mEB; /**< ErrorBackward */
        Dmatrix mEpf; /**< Mean Square Error Forward */
        Dmatrix mEpb; /**< Mean Square Error Backward */
        Dvector mKf; /**< Forward Parcor */
        Dvector mKb; /**< Backward Parcor */
        Dvector mG; /**< Angle parameter */
        unsigned int mF0; /**<index for the status of the Lattice filter */

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

} //end namespace

#endif // ___LSLFILTER_HPP
