/**
 * @file   InverseRealFFT.hpp
 * @author Giancarlo Cella <giancarlo.cella@pi.infn.it>
 * @date   Sat Nov 13 17:21:06 2004
 *
 * @brief  Interface for InverseRealFFT
 *
 *
 *   Copyright (C) 2004 by Giancarlo Cella
 *   giancarlo.cella@pi.infn.it
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
 */
#ifndef __INVERSEREALFFT_HPP
#define __INVERSEREALFFT_HPP

/**
 * @name System includes
 */
//@{

//@}

/**
 * @name Project includes
 */
//@{
#include <BaseFFT.hpp>
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

namespace tsa {

    /**
     * @class InverseRealFFT
     * @brief Multichannel inverse real to complex FFT.
     *
     * This is the implementation of the FFT of a real multichannel buffer
     */
    class InverseRealFFT : public BaseFFT {
    public:
        /**
         * Constructor
         *
         * @param size the size of the transform
         * @param mode specify the way in which plans are calculated
         * @param PreserveInput true if the input buffer must be preserved during the transform, false otherwise
         */
        InverseRealFFT(int size = 0, enum FFTPlanningMode mode = ESTIMATE, bool PreserveInput = false);

        /**
         * Copy constructor
         *
         * @param from The instance that must be copied
         */
        InverseRealFFT(const InverseRealFFT& from);

        /**
         * Destructor
         */
        ~InverseRealFFT();


        /**
         * @name Operations
         */
        //@{

        /**
         * Apply the transformation on the data
         *
         * @param in a reference to the buffer containing the input data
         * @param out a reference to the buffer containing the input data
         *
         *
         * @return a reference to this instance of the class
         **/
        void operator()(SeqViewComplex& in, SeqViewDouble& out);


        /**
         * Execution of the inverse real fft of a multichannel buffer of complex.
         * Input data are organized in a matrix. Each row is a different channel,
         * and the number of data to transform is equal to the number of columns.
         * Both the number of rows and the number of columns can change between
         * each call to this method. If the number of rows changes nothing special
         * will happen, if the number of cols changes the plan is reevaluated
         * with the current flags.
         *
         * @pre The number of rows of input and output matrix must be the same.
         * @pre The number of columns of the input matrix must be int(n/2)+1, 
         * where n is the number of columns of the output matrix.
         *
         * @post the input buffer is changed, unless @ref SetPreserveInput was called with true argument
         * @post the output buffer contain the inverse fft of the input data
         * @exception bad_matrix_size the size of the output matrix is wrong
         *
         * @param in reference to the input multichannel buffer
         * @param out reference to the output multichannel buffer
         */
        void execute(Cmatrix& in, Dmatrix& out);


        /**
         * Execution of the inverse real fft of a buffer of complex.
         * If the number of data changes the plan is reevaluated
         * with the current flags.
         *
         * @pre The number of columns of the input matrix must be int(n/2)+1, 
         * where n is the number of columns of the output matrix.
         *
         * @post the input buffer is changed, unless @ref SetPreserveInput was called with true argument
         * @post the output buffer contain the inverse fft of the input data
         * @exception bad_vector_size the size of the output vector
         *
         * @param in reference to the input vector
         * @param out reference to the output vector
         */
        void execute(Cvector& in, Dvector& out);

        void execute(CmatrixRow& in, DmatrixRow& out) ;

        void execute(CmatrixRow& in, DmatrixRow& out, unsigned int insize);


        /**
         * Make a new plan, with the current parameters.
         *
         * @exception std::runtime_error The new plan cannot be created
         */
        void MakePlan() ;

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


} // end namespace tsa

#endif // __INVERSEREALFFT_HPP
