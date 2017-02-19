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
 * @file   ArBurgEstimator.hpp
 * @author Elena Cuoco <elena.cuoco@ego-gw.it>
 * @date   05 December 2004
 *
 * @brief  Estimate the Parcor and AR parameters on a sequence of data
 */
#ifndef __ARBURGESTIMATOR_HPP
#define __ARBURGESTIMATOR_HPP


/**
 * @name System includes
 */
//@{


//@}

/**
 * @name Project includes
 */
//@{
#include <eternity.hpp>
#include <AlgoBase.hpp>
#include <SeqView.hpp>
#include <LatticeView.hpp>
#include <Parcor2AR.hpp>
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
     *@brief  Estimate the Parcor and AR parameters on a sequence of data
     *
     *
     */
    class ArBurgEstimator : public AlgoBase {
    public:

        /**
         * Constructor
         * @param ArOrder order of the AR model
         */
        ArBurgEstimator(unsigned int ArOrder);

        /**
         * Destructor
         */
        virtual ~ArBurgEstimator();

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

        void xml_serialize(eternity::xml_archive& xml, const char* prefix) {
            char buffer[1024];

            if (xml.is_loading()) {

                snprintf(buffer, 1024, "%s.mArOrder", prefix);
                xml.read(buffer, mArOrder, 0);
                snprintf(buffer, 1024, "%s.mAR", prefix);
                DVECTOR_XML_SERIALIZE(mAR, xml, buffer);

            } else {

                snprintf(buffer, 1024, "%s.mArOrder", prefix);
                xml.write(buffer, mArOrder);
                snprintf(buffer, 1024, "%s.mAR", prefix);
                DVECTOR_XML_SERIALIZE(mAR, xml, buffer);

            }
        }


        /**
         * @name Operations
         */
        //@{


        /**
         * Implements the estimation of the AR paramenters using the Burg method.
         * 
         * @param InputData Input data time series
         * @param WhitenedData Whitened time series
         */
        void operator()(SeqViewDouble& InputData, SeqViewDouble& WhitenedData);


        /**
         * Implements the estimation of the AR paramenters using the Burg method.
         * 
         * @param InputData Input data time series
         * @param WhitenedData Whitened time series
         */
        void Color(SeqViewDouble& WhitenedData, SeqViewDouble& ColoredData);
        /**
         * Implements the estimation of the AR paramenters using the Burg method.
         * 
         * @param InputData Input data time series
         * @param Parcor Parcor coefficients
         */
        void operator()(SeqViewDouble& InputData);
        /**
         *
         * @brief  Estimate the Parcor and AR parameters on a sequence of data
         * @pre The lenght of the input sequence must be greater then the AR order
         * @todo Add execption
         *
         *
         *  
         * @param InputData is the input sequences of data
         */
        void execute(matrix_row<Dmatrix> InputData);

        void color(matrix_row<Dmatrix> WhitenedData, matrix_row<Dmatrix> ColoredData);


        //@}

        /**
         * @name Getters
         */
        //@{

        /** 
         * 
         * 
         * @param LV the target lattice view
         */
        void GetLatticeView(LatticeView& LV);



        /**
         * 
         * @return the Ar Order
         */
        unsigned int GetArOrder();

        /**
         *@return Get The Parcor values
         */
        double GetParcor(unsigned int j);
        /**
         *@return Get The AR values
         */
        double GetAR(unsigned int j);

        /**
         * @return Get the ErrorForward values
         */
        double GetErrorForward(unsigned int j);

        /**
         * @return Get the ErrorBackward values
         */
        double GetErrorBackward(unsigned int j);

        //@}

        /**
         * @name Setters
         */
        //@{

        /**
         * @param P the Ar order 
         */
        void SetArOrder(unsigned int P);

        void SetAR(unsigned int j, double value);
        //@}


    protected:

    private:

        unsigned int mArOrder; /**< the Order of the AR model   */
        Dvector mParcor; /**<the vector of reflection coefficients */
        Dvector mAR;
        Dvector mErrorForward; /**<the error forward */
        Dvector mErrorBackward; /**<the error backward */
        Dvector mWhitenedData;
        Dvector mColoredData;

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

#endif // ___ARBURGESTIMATOR_HPP


