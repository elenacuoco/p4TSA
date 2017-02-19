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
 * @file   VArma2TF.hpp
 * @author Elena Cuoco <elena.cuoco@ego-gw.it>
 * @date   2004
 *
 * @brief  Estimate the Transfer function using the ARMA parametrization
 */
#ifndef __VARMA2TF_HPP
#define __VARMA2TF_HPP


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
//@}

/**
 * @name Local includes
 */
//@{
#include <LUComplexSolve.hpp>
//@}

/**
 * @name Forward references
 */
//@{


//@}

/**
 * namespace
 */
namespace tsa {

    /**
     * @brief  Estimate the Transfer function using the ARMA parametrization
     *
     */
    class VArma2TF : public AlgoBase {
    public:

        /**
         * Constructor
         */
        VArma2TF();

        /**
         * Copy constructor
         *
         * @param from The instance that must be copied
         */
        VArma2TF(const VArma2TF& from);

        /**
         * Destructor
         */
        virtual ~VArma2TF();

        /**
         * Assignement operator
         *
         * @param from The instance to be assigned from
         *
         * @return a reference to a new object
         */
        VArma2TF& operator=(const VArma2TF& from);

        /**
         * @name Operations
         */
        //@{

        /**
         * 
         * @param AR autoregressive part
         * @param MA moving average part
         * @param TF transfer function
         */
        void execute(VDmatrix& AR, VDmatrix& MA, Cmatrix& TF);

        //@}

        /**
         * @name Getters
         */
        //@{

        //@}

        /**
         * @name Setters
         */
        //@{

        //@}


    protected:

    private:

        LUComplexSolve mLUsolver;

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

#endif // ___VARMA2TF_HPP






