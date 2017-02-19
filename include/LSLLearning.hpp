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
 * @file   LSLLearning.hpp
 * @author Elena Cuoco <elena.cuoco@ego-gw.it>
 * @date   2005
 *
 * @brief  Least Squares Lattice  filter
 */
#ifndef __LSLLEARNING_HPP
#define __LSLLEARNING_HPP


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
     * @brief   rithm for the learning phase of the Adaptive Least Squares Lattice
     */
    class LSLLearning : public AlgoBase {
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
        LSLLearning(unsigned int Order, double sigma, double lambda = 1.0);

        /**
         * Copy constructor
         *
         * @param from The instance that must be copied
         */
        LSLLearning(const LSLLearning& from);

        /**
         * Destructor
         */
        ~LSLLearning();

        /**
         * Assignement operator
         *
         * @param from The instance to be assigned from
         *
         * @return a reference to a new object
         */
        LSLLearning& operator=(const LSLLearning& from);

        /**
         * @name Operations
         */
        //@{

        /**
         * 
         * @param InputData Time series 
         * @param WhitenedData Whitened Time series 
         */
        void operator()(SeqViewDouble& InputData, SeqViewDouble& WhitenedData);

        /**
         * 
         * @param InputData
         * @param LatView
         */
        void operator()(SeqViewDouble& InputData, LatticeView& LatView);

        /**
         * 
         * @param InputData
         * @param Parcor
         */
        void operator()(SeqViewDouble& InputData, Dvector& Parcor);



        /**
         * 
         * @param InputData  Input data
         * @param OutputData Output data
         */
        void execute(matrix_row<Dmatrix> InputData, matrix_row<Dmatrix> OutputData);
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

        double GetErrorForward(unsigned int i, unsigned int j) {
            return mEF(i, j);
        }

        /**
         */
        double GetErrorBackward(unsigned int i, unsigned int j) {
            return mEB(i, j);
        }

        double GetEpf(unsigned int i, unsigned int j) {
            return mEpf(i, j);
        }

        /**
         */
        double GetEpb(unsigned int i, unsigned int j) {
            return mEpb(i, j);
        }

        double GetGamma(unsigned int j) {
            return mG(j);
        }

        unsigned int GetStatus() {
            return mF0;
        }

        /**
         */
        double GetSigma() {
            return mSigma;
        }

        //@}

        /**
         * @name Setters
         */
        //@{

        //@}

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

        void xml_serialize(eternity::xml_archive& xml, const char* p) {
            char buffer[1024];

            if (xml.is_loading()) {

                snprintf(buffer, 1024, "%s.mOrder", p);
                xml.read(buffer, mOrder, 0);
                snprintf(buffer, 1024, "%s.mKf", p);
                DVECTOR_XML_SERIALIZE(mKf, xml, buffer);
                snprintf(buffer, 1024, "%s.mKb", p);
                DVECTOR_XML_SERIALIZE(mKb, xml, buffer);
                snprintf(buffer, 1024, "%s.mEF", p);
                DMATRIX_XML_SERIALIZE(mEF, xml, buffer);
                snprintf(buffer, 1024, "%s.mEB", p);
                DMATRIX_XML_SERIALIZE(mEB, xml, buffer);
                snprintf(buffer, 1024, "%s.mF0", p);
                xml.read(buffer, mF0, 0);

            } else {

                snprintf(buffer, 1024, "%s.mOrder", p);
                xml.write(buffer, mOrder);
                snprintf(buffer, 1024, "%s.mKf", p);
                DVECTOR_XML_SERIALIZE(mKf, xml, buffer);
                snprintf(buffer, 1024, "%s.mKb", p);
                DVECTOR_XML_SERIALIZE(mKb, xml, buffer);
                snprintf(buffer, 1024, "%s.mEF", p);
                DMATRIX_XML_SERIALIZE(mEF, xml, buffer);
                snprintf(buffer, 1024, "%s.mEB", p);
                DMATRIX_XML_SERIALIZE(mEB, xml, buffer);
                snprintf(buffer, 1024, "%s.mF0", p);
                xml.write(buffer, mF0);



            }
        }


    protected:

    private:
        unsigned int mOrder; /**< Order of the filter */
        double mSigma; /**<The estimated rms */
        Dmatrix mEF; /**< ErrorForward */
        Dmatrix mEB; /**< ErrorBackward */
        Dmatrix mEpf; /**< Mean Square Error Forward */
        Dmatrix mEpb; /**< Mean Square Error Backward */
        Dvector mKf; /**< Forward Parcor */
        Dvector mKb; /**< Backward Parcor */
        Dvector mG; /**< Angle parameter */
        double mLambda; /**< Forgetting Factor */
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

#endif // ___LSLLEARNING_HPP
