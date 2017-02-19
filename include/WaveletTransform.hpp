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
/// @file   WaveletTransform.hpp
/// @author Elena Cuoco <elena.cuoco@ego-gw.it>
/// @date   2005
///
/// @brief  compute the Wavelet Transform usign GSL
///
#ifndef __WAVELETTRANSFORM_HPP
#define __WAVELETTRANSFORM_HPP


///
/// @name System includes
///
//@{
#include <gsl/gsl_wavelet.h>
#include <gsl/gsl_errno.h>
//@}

///
/// @name Project includes
///
//@{

#include <AlgoBase.hpp>
#include <SeqView.hpp>
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
    ///
    ///Compute the wavelet transform
    ///
    ///

    class WaveletTransform : AlgoBase {
    public:

        enum WaveletType {
            Daub4,
            Daub6,
            Daub8,
            Daub10,
            Daub12,
            Daub14,
            Daub16,
            Daub18,
            Daub20,
            DaubC4,
            DaubC6,
            DaubC8,
            DaubC10,
            DaubC12,
            DaubC14,
            DaubC16,
            DaubC18,
            DaubC20,
            Haar,
            HaarC,
            Bspline103,
            Bspline105,
            Bspline202,
            Bspline204,
            Bspline206,
            Bspline208,
            Bspline301,
            Bspline303,
            Bspline305,
            Bspline307,
            Bspline309,
            BsplineC103,
            BsplineC105,
            BsplineC202,
            BsplineC204,
            BsplineC206,
            BsplineC208,
            BsplineC301,
            BsplineC303,
            BsplineC305,
            BsplineC307,
            BsplineC309
        };

        ///
        /// Constructor
        ///
        WaveletTransform(unsigned int N, enum WaveletType wt);

        ///
        /// Copy constructor
        ///
        /// @param from The instance that must be copied
        WaveletTransform(const WaveletTransform& from);

        ///
        /// Destructor
        ///
        ~WaveletTransform();

        ///
        /// Assignement operator
        ///
        /// @param from The instance to be assigned from
        ///
        /// @return a reference to a new object
        WaveletTransform& operator=(const WaveletTransform& from);

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
        void Forward(SeqViewDouble& In);
        void Inverse(SeqViewDouble& In);
        void Forward(Dmatrix& In);
        void Inverse(Dmatrix& In);

        //@}

        ///
        /// @name Getters
        ///
        //@{
        void WaveletPrint();
        void WaveletWaveform(Dvector& V);

        //@}

        ///
        /// @name Setters
        ///
        //@{

        //@}


    protected:

    private:
        gsl_wavelet *mW;
        gsl_wavelet_workspace *mWork;
        unsigned int mN; ///< Lenght of input data. It must be a power of 2
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

#endif // ___WAVELETTRANSFORM_HPP


