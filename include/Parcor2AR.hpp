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
 * @file   Parcor2AR.hpp 
 * @author Elena Cuoco <elena.cuoco@ego-gw.it>
 * @date   2005
 *
 * @brief  Estimate the AR parameters by the Parcor
 */
#ifndef __PARCOR2AR_HPP
#define __PARCOR2AR_HPP


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
#include <CreateDvector.hpp>
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
     * @brief  Estimate the AR parameters by the Parcor
     */
    class Parcor2AR : public AlgoBase {
    public:

        /**
         * Constructor
         */
        Parcor2AR();

        /**
         * Destructor
         */
        virtual ~Parcor2AR();

        Dvector operator()(Dvector Parcor);


        /**
         * @name Operations
         */
        //@{

        /**
         * The execute method transform the parcor in AR
         *
         * @param Parcor reflection coefficients vector
         * @param AR autoregressive parameters
         */
        void execute(Dvector& Parcor, Dvector& AR);

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

#endif // ___PARCOR2AR_HPP



