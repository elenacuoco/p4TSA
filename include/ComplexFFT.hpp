/**
 * @file   ComplexFFT.hpp
 * @author Giancarlo Cella <giancarlo.cella@pi.infn.it>
 * @date   Sat Nov 13 17:21:06 2004
 *
 * @brief  Interface for ComplexFFT
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
#ifndef __COMPLEXFFT_HPP
#define __COMPLEXFFT_HPP

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


/**
 * @namespace tsa
 *
 * @brief The main namespace of the library.
 */
namespace tsa {

    /**
     * @class ComplexFFT
     * @brief Multichannel complex FFT.
     *
     * This is the implementation of the FFT of a complex multichannel buffer. The transformation
     * is simply iterated over all the channels.
     */
    class ComplexFFT : public BaseFFT {
    public:

        /**
         * Transform sign.
         * See the fftw documentation.
         */
        enum TransformSign {
            FORWARD, //*< Transform sign = -1
            BACKWARD //*< Transform sign = +1
        };


        /**
         * Constructor
         *
         * @param size the size of the transform
         * @param s the sign of the transform
         * @param mode specify the way in which plans are calculated
         * @param PreserveInput true if the input buffer must be preserved during the transform, false otherwise
         */
        ComplexFFT(int size = 0, enum TransformSign s = FORWARD, enum FFTPlanningMode mode = ESTIMATE, bool PreserveInput = true);

        /**
         * Copy constructor
         *
         * @param from The instance that must be copied
         */
        ComplexFFT(const ComplexFFT& from);

        /**
         * Destructor
         */
        ~ComplexFFT();

        /**
         * Assignement operator
         *
         * @param from The instance to be assigned from
         *
         * @return a reference to a new object
         */
        ComplexFFT& operator=(const ComplexFFT& from);

        /**
         * @name Operations
         */
        //@{

        /**
         * Execution of the fft of a multichannel buffer of complex double precision numbers.
         * Input data are organized in a matrix. Each row is a different channel,
         * and the number of data to transform is equal to the number of columns.
         * Both the number of rows and the number of columns can change between
         * each call to this method. If the number of rows changes nothing special
         * will happen, if the number of cols changes the plan is reevaluated
         * with the current flags.
         * 
         * 
         * @pre The number of rows of input and output matrix must be the same.
         * @pre The number of columns of the output matrix must be equal to the number of columns of the input matrix.
         * @post the input buffer is unchanged, unless @ref SetPreserveInput was called with a false argument
         * @post the output buffer contain the fft of the input data
         *
         * @exception bad_matrix_size the dimension of the output array is wrong
         *
         * @param in reference to the input multichannel buffer
         * @param out reference to the output multichannel buffer
         */
        void execute(Cmatrix& in, Cmatrix& out) ;

        /**
         * Make a new plan, with the current parameters.
         */
        void MakePlan();

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

        /** 
         * set the sign of the transform
         * 
         * @param s the new sign of the transform
         */
        void SetSign(enum TransformSign s);

        //@}


    protected:

    private:

        int mSign; /**< The sign of the transform */


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

#endif // __COMPLEXFFT_HPP
