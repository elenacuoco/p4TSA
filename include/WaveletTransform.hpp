///
///   Copyright (C) 2004 by Elena Cuoco
///   elena.cuoco@unibo.it
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
/// @author Elena Cuoco <elena.cuoco@unibo.it>
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
#include <cstddef>
#include <vector>
//@}

///
/// @name Local includes
///
//@{
#include <ExtraWaveletFamilies.hpp>
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
            BsplineC309,
            Coif1,
            Coif2,
            Sym4,
            Sym8
        };

        ///
        /// Constructor: the pyramidal (Mallat) transform, GSL's packed layout.
        ///
        WaveletTransform(unsigned int N, enum WaveletType wt);

        ///
        /// Constructor: one level of the wavelet-packet tree.
        ///
        /// With `packetDepth` zero the transform is the pyramidal one of the
        /// constructor above. With `packetDepth` equal to D > 0 every band is
        /// split, not only the lowpass one, D times with the same periodized
        /// filter step GSL applies in its pyramid, so the output is the uniform
        /// level D of the wavelet-packet tree: 2^D bands of equal width
        /// fs / 2^(D+1), each carrying N / 2^D coefficients that tile the
        /// window in steps of 2^D samples. The bands are written in frequency
        /// order, band f occupying indices [f N / 2^D, (f+1) N / 2^D), so the
        /// index of a coefficient places it in the plane without knowledge of
        /// the tree: the highpass branch of a split reverses the spectrum of
        /// what it decimates, the natural order of the tree is therefore the
        /// Gray code of the frequency order, and the permutation undoes it.
        ///
        /// Every step is an orthonormal periodized two-channel filter bank and
        /// a permutation is orthonormal, so the level is an orthonormal basis:
        /// Inverse(Forward(x)) is x and the coefficient energy is the energy of
        /// x. The cost is D N nc multiply-adds, linear in N, with a data
        /// independent sequence of operations and a fixed latency.
        ///
        /// @param N window length, a power of 2
        /// @param wt mother wavelet
        /// @param packetDepth 0 for the pyramid, else the packet level, at
        ///        most log2(N)
        /// @exception std::invalid_argument when N is not a power of 2 or
        ///            packetDepth exceeds log2(N)
        ///
        WaveletTransform(unsigned int N, enum WaveletType wt, unsigned int packetDepth);

        ///
        /// Copy constructor: a transform of the same length, mother and
        /// packet level, with GSL handles of its own.
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

        ///
        /// The waveform of coefficient 22: the inverse transform, pyramidal
        /// or packet as the transform is, of a unit coefficient at index 22.
        ///
        /// @param V filled with the mN samples of the waveform
        ///
        void WaveletWaveform(Dvector& V);

        ///
        /// The window length the transform works on.
        ///
        unsigned int GetLength() const {
            return mN;
        }

        ///
        /// The packet level of the transform, 0 for the pyramid.
        ///
        unsigned int GetPacketDepth() const {
            return mDepth;
        }

        //@}

        ///
        /// @name Setters
        ///
        //@{

        //@}


    protected:

    private:
        void PacketForward(double* data);
        void PacketInverse(double* data);
        void Step(double* a, std::size_t n, bool forward);

        gsl_wavelet *mW;
        gsl_wavelet_workspace *mWork;
        unsigned int mN; ///< Lenght of input data. It must be a power of 2
        unsigned int mDepth; ///< packet level, 0 for the pyramidal transform
        enum WaveletType mType; ///< mother, from which a copy is rebuilt
        std::vector<double> mScratch; ///< one band of the packet step
        std::vector<double> mOrder; ///< the tree in natural order
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


