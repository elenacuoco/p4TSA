/**
 * @file   RealFFT.hpp
 * @author Giancarlo Cella <giancarlo.cella@pi.infn.it>
 * @date   Sat Nov 13 17:21:06 2004
 *
 * @brief  RealFFT
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
 *
 **/
#ifndef __REALFFT_HPP
#define __REALFFT_HPP

/**
 * @name System includes
 **/
//@{

//@}

/**
 * @name Project includes
 **/
//@{
#include <BaseFFT.hpp>
#include <SeqView.hpp>
//@}

/**
 * @name Local includes
 **/
//@{

//@}

/**
 * @name Forward references
 **/
//@{

//@}


/**
 * @namespace tsa
 *
 * @brief The main namespace of the library.
 **/
namespace tsa {

    /**
     * @class RealFFT
     * @brief Multichannel real to complex FFT.
     *
     * This is the implementation of the FFT of a real multichannel buffer
     **/
    class RealFFT : public BaseFFT {
    public:
        /**
         * Constructor
         *
         * @param size the size of the transform
         * @param mode specify the way in which plans are calculated
         * @param PreserveInput true if the input buffer must be preserved during the transform, false otherwise
         **/
        RealFFT(int size = 0, enum FFTPlanningMode mode = ESTIMATE, bool PreserveInput = true);

        /**
         * Copy constructor
         *
         * @param from The instance that must be copied
         **/
        RealFFT(const RealFFT& from);

        /**
         * Destructor
         **/
        virtual ~RealFFT();

        /**
         * @name Operations
         **/
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
        void operator()(SeqViewDouble& in, SeqViewComplex& out);


        /**
         * Execution of the fft of a multichannel buffer of double.
         * Input data are organized in a matrix. Each row is a different channel,
         * and the number of data to transform is equal to the number of columns.
         * Both the number of rows and the number of columns can change between 
         * each call to this method. If the number of rows changes nothing special
         * will happen, if the number of cols changes the plan is reevaluated
         * with the current flags.
         *
         * @pre The number of rows of input and output matrix must be the same.
         * @pre The columns of the output matrix must be int(n/2)+1, where n is the number of columns of the input matrix.
         *
         * @post the input buffer is unchanged, unless @ref SetPreserveInput(false) was called
         * @post the output buffer contain the fft of the input data
         * 
         * @exception bad_matrix_size the size of the output matrix is wrong
         * @param in reference to the input multichannel buffer
         * @param out reference to the output multichannel buffer
         **/
        void execute(Dmatrix& in, Cmatrix& out);

        void execute(Dmatrix& indata, Cmatrix& outdata, unsigned int size, unsigned int offset);


        /**
         * Execution of the fft of a single channel buffer of double.
         * If the number of the buffer changes the plan is reevaluated
         * with the current flags.
         *
         * @pre The sized of the output vector must be int(n/2)+1, where n is the size of the input vector.
         *
         * @post the input buffer is unchanged, unless @ref SetPreserveInput(false) was called
         * @post the output buffer contain the fft of the input data
         * 
         * @exception bad_matrix_size the size of the output matrix is wrong
         * @param in reference to the input buffer
         * @param out reference to the output buffer
         **/
        void execute(Dvector& in, Cvector& out) ;


        /**
         * Make a new plan, with the current parameters.
         * 
         * @exception std::runtime_error The new plan cannot be created
         **/
        void MakePlan();


        //@}

        /**
         * @name Getters
         **/
        //@{


        //@}

        /**
         * @name Setters
         **/
        //@{


        //@}


    protected:

    private:



    };

    /**
     * @name Inline methods
     **/
    //@{


    //@}

    /**
     * @name External references
     **/
    //@{

    //@}


} // end namespace tsa

#endif // __REALFFT_HPP
