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
 * @file   Arma2Psd.hpp
 * @author Elena Cuoco <elena.cuoco@ego-gw.it>
 * @date   2005
 *
 * @brief  Estimate the PSD for a ARMA model
 */
#ifndef __ARMA2PSD_HPP
#define __ARMA2PSD_HPP


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
#include <ARMAView.hpp>
#include <SeqView.hpp>
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
namespace tsa {

    /**
     *@brief  Estimate the PSD for a ARMA model
     */
    class Arma2Psd : public AlgoBase {
    public:

        /**
         * Constructor
         */
        Arma2Psd();

        /**
         * Copy constructor
         *
         * @param from The instance that must be copied
         */
        Arma2Psd(const Arma2Psd& from);

        /**
         * Destructor
         */
        virtual ~Arma2Psd();

        /**
         * Assignement operator
         *
         * @param from The instance to be assigned from
         *
         * @return a reference to a new object
         */
        Arma2Psd& operator=(const Arma2Psd& from);

        /**
         * @name Operations
         */
        //@{

        /**
         * @pre The P or the Q order must be greater than 0
         *
         * @param arma the Arma View
         *
         * @return Psd the Power Spectral density
         */
        void operator()(ARMAView& arma, SeqViewDouble& Psd);


        /**
         * @brief  Estimate the PSD for a ARMA model
         *
         * 
         * @param AR the autoregressive part
         * @param MA the moving average aprt
         * @param psd the Power Spectral Density
         */
        void execute(Dvector& AR, Dvector& MA, Dvector& psd);

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

#endif // ___ARMA2PSD_HPP




