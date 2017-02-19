///
///   Copyright (C) 2004 by Elena Cuoco
///   elena.cuoco@ego-gw.it
///
///   This program is free software; you can redistribute it and/or modify
///   it under the terms of the GNU General Public License as published by
///   the Free Software Foundation; either version 2 of the License, or
///   (at your option) any later version.
///
///   This program is distributed in the hope that it will be useful,
///   but WITHOUT ANY WARRANTY; without even the implied warranty of
///   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
///   GNU General Public License for more details.
///
///   You should have received a copy of the GNU General Public License
///   along with this program; if not, write to the
///   Free Software Foundation, Inc.,
///   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
///
/// @file   WavReconstruction.hpp
/// @author Elena Cuoco <elena.cuoco@ego-gw.it>
/// @date   2006
///
/// @brief  description of WavReconstruction
///
#ifndef __WAVRECONSTRUCTION_HPP
#define __WAVRECONSTRUCTION_HPP


///
/// @name System includes
///
//@{

//@}

///
/// @name Project includes
///
//@{

#include <AlgoBase.hpp>
#include <WaveletTransform.hpp>
#include <SeqView.hpp>
#include <AlgoExceptions.hpp>
#include <WaveletThreshold.hpp>
//@}

///
/// @name Local includes
///
//@{


//@}

///
/// @name Forward references
///
//@{


//@}

///
/// namespace
///
namespace tsa {

    ///
    ///
    /// A more detailed description of WavReconstruction
    ///
    ///@brief Reconstructed the wavelet transformed signal
    ///
    ///

    class WavReconstruction : public AlgoBase {
    public:

        ///
        /// Constructor
        ///
        WavReconstruction(unsigned int N, enum WaveletTransform::WaveletType F, double Th);


        ///
        /// Destructor
        ///
        ~WavReconstruction();


        void operator()(SeqViewDouble& InputData);
        ///
        /// @name Operations
        ///
        ///@{

        ///
        /// @brief Brief documentation for the execute method.
        ///
        /// Start of the long documentation for execute method.
        ///
        /// @pre A precondition
        /// @post A postcondition
        /// @exception An exception
        ///
        /// @param a parameter
        ///
        /// @return a returned value
        ///
        /// Declaration of execute operation
        void execute(Dmatrix& buffer);
        //@}

        ///
        /// @name Getters
        ///
        //@{

        //@}

        ///
        /// @name Setters
        ///
        //@{

        //@}


    protected:

    private:
        unsigned int mN;
        Dmatrix mBuff;
        enum WaveletTransform::WaveletType mWt;
        WaveletTransform mWT;
        enum WaveletThreshold::WaveletThresholding mT;
        WaveletThreshold mWavThres;

    };

    ///
    /// @name Inline methods
    ///
    //@{

    //@}


    ///
    /// @name External references
    ///
    //@{

    //@}

} //end namespace

#endif // ___WAVRECONSTRUCTION_HPP



