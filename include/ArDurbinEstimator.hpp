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
 * @file   ArDurbinEstimator.hpp 
 * @author Elena Cuoco <elena.cuoco@ego-gw.it>
 * @date   2004
 *
 * @brief  AR estimator based on  Durbin procedure
 */
#ifndef __ARDURBINESTIMATOR_HPP
#define __ARDURBINESTIMATOR_HPP

/**
 * @name System includes
 */
//@{

#include <boost/numeric/ublas/matrix.hpp>



//@}

/**
 * @name Project includes
 */
//@{

#include <AlgoBase.hpp>
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

using namespace boost::numeric::ublas;


/**
 * namespace
 */

namespace tsa {

    /**
     * @brief  Estimate the AR coefficients and the PARCOR of a time series using its correlation function
     *
     */
    class ArDurbinEstimator : public AlgoBase {
    public:

        /**
         * Constructor
         * 
         * @param ArOrder order of the the AR model
         */
        ArDurbinEstimator(unsigned int ArOrder);


        /**
         * Destructor
         */
        virtual~ArDurbinEstimator();


        /**
         * @name Operations
         */
        //@{



        /**
         *  The excute method estimate the AR and PARCOR parameters with the Durbin rithm.
         * @pre The input of the algorithm must be the autocorrelation function in Toeplitz form
         *
         * @param AutoCorr autocorrelation in Toeplitz form
         * @param ArParcor vector  containing the Reflection coefficients 
         */
        void execute(Dvector& AutoCorr, Dvector& ArParcor);
        //@}

        /**
         * @name Getters
         */
        //@{

        unsigned int GetArOrder() {
            return mArOrder;
        }

        //@}

        /**
         * @name Setters
         */
        //@{

        void SetArOrder(unsigned int P) {
            mArOrder = P + 1;
        }

        //@}


    protected:

    private:
        unsigned int mArOrder;

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

#endif // __ARDURBINESTIMATOR_HPP


