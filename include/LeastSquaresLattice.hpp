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
 * @file   LeastSquaresLattice.hpp
 * @author Elena Cuoco <elena.cuoco@ego-gw.it>
 * @date   17 January 2005
 *
 * @brief  The LeastSquaresLattice is the algorithm to estimate in adaptive way the parameters for the whitening filter
 */
#ifndef __LEASTSQUARESLATTICE_HPP
#define __LEASTSQUARESLATTICE_HPP


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

using namespace boost::numeric::ublas;

/**
 * namespace
 */
namespace tsa {

    /**
     *
     *
     *
     * @brief Estimate the parameters for the Least Squares Lattice filter and implement the adaptive whitening. 
     *
     *
     */
    class LeastSquaresLattice : public AlgoBase {
    public:

        /**
         * Constructor
         */
        LeastSquaresLattice(matrix_row<Dmatrix>& LearnData,
                matrix_row<Dmatrix>& WhitenData,
                unsigned int P, double lambda, unsigned int D);


        /**
         * Destructor
         */
        virtual ~LeastSquaresLattice();

        /**
         * Assignement operator
         *
         * @param from The instance to be assigned from
         *
         * @return a reference to a new object
         */
        LeastSquaresLattice& operator=(const LeastSquaresLattice& from);

        /**
         * @name Operations
         */
        //@{

        /**
         * 
         * @param Input Input data
         * @param Output Whitened Data
         */
        void execute(Dvector& Input, Dvector& Output);

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
        unsigned int mOrder;
        unsigned int mLwsp;
        double mLambda;
        Dmatrix mLast;
        unsigned mDirection;
        unsigned int mStep;
        LSLLearning mLSLlearn;

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

#endif // ___LEASTSQUARESLATTICE_HPP
