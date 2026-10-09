//
//
// C++ Implementation: WaveletTransform.cpp
//
// Description:
//
//
// Author: Elena Cuoco <elena.cuoco@unibo.it>, (C) 2005
//
// Copyright: See COPYING file that comes with this distribution
//
//
//

#include <WaveletTransform.hpp>
#include <stdexcept>
#include <utility>

namespace tsa {

    WaveletTransform::WaveletTransform(unsigned int N, enum WaveletType wt)
    :
    WaveletTransform(N, wt, Unchecked()) {
        if (wt == LocalCos) {
            throw std::invalid_argument("WaveletTransform: LocalCos needs a segment length, WaveletTransform(N, LocalCos, log2 M)");
        }
    }

    WaveletTransform::WaveletTransform(unsigned int N, enum WaveletType wt, Unchecked)
    :
    mN(N),
    mDepth(0),
    mType(wt) {
        mWork = gsl_wavelet_workspace_alloc(mN);
        switch (wt) {
            case Daub4:
                mW = gsl_wavelet_alloc(gsl_wavelet_daubechies, 4);
                break;
            case Daub6:
                mW = gsl_wavelet_alloc(gsl_wavelet_daubechies, 6);
                break;
            case Daub8:
                mW = gsl_wavelet_alloc(gsl_wavelet_daubechies, 8);
                break;
            case Daub10:
                mW = gsl_wavelet_alloc(gsl_wavelet_daubechies, 10);
                break;
            case Daub12:
                mW = gsl_wavelet_alloc(gsl_wavelet_daubechies, 12);
                break;
            case Daub14:
                mW = gsl_wavelet_alloc(gsl_wavelet_daubechies, 14);
                break;
            case Daub16:
                mW = gsl_wavelet_alloc(gsl_wavelet_daubechies, 16);
                break;
            case Daub18:
                mW = gsl_wavelet_alloc(gsl_wavelet_daubechies, 18);
                break;
            case Daub20:
                mW = gsl_wavelet_alloc(gsl_wavelet_daubechies, 20);
                break;
            case DaubC4:
                mW = gsl_wavelet_alloc(gsl_wavelet_daubechies_centered, 4);
                break;
            case DaubC6:
                mW = gsl_wavelet_alloc(gsl_wavelet_daubechies_centered, 6);
                break;
            case DaubC8:
                mW = gsl_wavelet_alloc(gsl_wavelet_daubechies_centered, 8);
                break;
            case DaubC10:
                mW = gsl_wavelet_alloc(gsl_wavelet_daubechies_centered, 10);
                break;
            case DaubC12:
                mW = gsl_wavelet_alloc(gsl_wavelet_daubechies_centered, 12);
                break;
            case DaubC14:
                mW = gsl_wavelet_alloc(gsl_wavelet_daubechies_centered, 14);
                break;
            case DaubC16:
                mW = gsl_wavelet_alloc(gsl_wavelet_daubechies_centered, 16);
                break;
            case DaubC18:
                mW = gsl_wavelet_alloc(gsl_wavelet_daubechies_centered, 18);
                break;
            case DaubC20:
                mW = gsl_wavelet_alloc(gsl_wavelet_daubechies_centered, 20);
                break;

            case Bspline103:
                mW = gsl_wavelet_alloc(gsl_wavelet_bspline, 103);
                break;
            case Bspline105:
                mW = gsl_wavelet_alloc(gsl_wavelet_bspline, 105);
                break;
            case Bspline202:
                mW = gsl_wavelet_alloc(gsl_wavelet_bspline, 202);
                break;
            case Bspline204:
                mW = gsl_wavelet_alloc(gsl_wavelet_bspline, 204);
                break;
            case Bspline206:
                mW = gsl_wavelet_alloc(gsl_wavelet_bspline, 206);
                break;
            case Bspline208:
                mW = gsl_wavelet_alloc(gsl_wavelet_bspline, 208);
                break;
            case Bspline301:
                mW = gsl_wavelet_alloc(gsl_wavelet_bspline, 301);
                break;
            case Bspline303:
                mW = gsl_wavelet_alloc(gsl_wavelet_bspline, 303);
                break;
            case Bspline305:
                mW = gsl_wavelet_alloc(gsl_wavelet_bspline, 305);
                break;
            case Bspline307:
                mW = gsl_wavelet_alloc(gsl_wavelet_bspline, 307);
                break;
            case Bspline309:
                mW = gsl_wavelet_alloc(gsl_wavelet_bspline, 309);
                break;
            case BsplineC103:
                mW = gsl_wavelet_alloc(gsl_wavelet_bspline_centered, 103);
                break;
            case BsplineC105:
                mW = gsl_wavelet_alloc(gsl_wavelet_bspline_centered, 105);
                break;
            case BsplineC202:
                mW = gsl_wavelet_alloc(gsl_wavelet_bspline_centered, 202);
                break;
            case BsplineC204:
                mW = gsl_wavelet_alloc(gsl_wavelet_bspline_centered, 204);
                break;
            case BsplineC206:
                mW = gsl_wavelet_alloc(gsl_wavelet_bspline_centered, 206);
                break;
            case BsplineC208:
                mW = gsl_wavelet_alloc(gsl_wavelet_bspline_centered, 208);
                break;
            case BsplineC301:
                mW = gsl_wavelet_alloc(gsl_wavelet_bspline_centered, 301);
                break;
            case BsplineC303:
                mW = gsl_wavelet_alloc(gsl_wavelet_bspline_centered, 303);
                break;
            case BsplineC305:
                mW = gsl_wavelet_alloc(gsl_wavelet_bspline_centered, 305);
                break;
            case BsplineC307:
                mW = gsl_wavelet_alloc(gsl_wavelet_bspline_centered, 307);
                break;
            case BsplineC309:
                mW = gsl_wavelet_alloc(gsl_wavelet_bspline_centered, 309);
                break;
            case HaarC:
                mW = gsl_wavelet_alloc(gsl_wavelet_haar_centered, 2);
                break;
            case Coif1:
                mW = gsl_wavelet_alloc(tsa_wavelet_coiflet_centered, 1);
                break;
            case Coif2:
                mW = gsl_wavelet_alloc(tsa_wavelet_coiflet_centered, 2);
                break;
            case Sym4:
                mW = gsl_wavelet_alloc(tsa_wavelet_symlet_centered, 4);
                break;
            case Sym8:
                mW = gsl_wavelet_alloc(tsa_wavelet_symlet_centered, 8);
                break;
            case Sym10:
                mW = gsl_wavelet_alloc(tsa_wavelet_symlet_centered, 10);
                break;
            case Sym12:
                mW = gsl_wavelet_alloc(tsa_wavelet_symlet_centered, 12);
                break;
            case Sym16:
                mW = gsl_wavelet_alloc(tsa_wavelet_symlet_centered, 16);
                break;
            case Sym20:
                mW = gsl_wavelet_alloc(tsa_wavelet_symlet_centered, 20);
                break;
            case Coif3:
                mW = gsl_wavelet_alloc(tsa_wavelet_coiflet_centered, 3);
                break;
            case Coif4:
                mW = gsl_wavelet_alloc(tsa_wavelet_coiflet_centered, 4);
                break;
            case Coif5:
                mW = gsl_wavelet_alloc(tsa_wavelet_coiflet_centered, 5);
                break;
            case DaubC24:
                mW = gsl_wavelet_alloc(tsa_wavelet_daubechies_long_centered, 24);
                break;
            case DaubC32:
                mW = gsl_wavelet_alloc(tsa_wavelet_daubechies_long_centered, 32);
                break;
            case DaubC40:
                mW = gsl_wavelet_alloc(tsa_wavelet_daubechies_long_centered, 40);
                break;
            default:
                mW = gsl_wavelet_alloc(gsl_wavelet_haar, 2);
                break;
        }

    }

    namespace {
        // Checked before anything is allocated: GSL's handler aborts rather
        // than returning on a length it cannot transform.
        unsigned int PacketLength(unsigned int N, unsigned int packetDepth) {
            if (N < 2 || (N & (N - 1)) != 0) {
                throw std::invalid_argument("WaveletTransform: the window length must be a power of 2");
            }
            if (packetDepth >= 8 * sizeof(std::size_t) ||
                (static_cast<std::size_t>(1) << packetDepth) > N) {
                throw std::invalid_argument("WaveletTransform: the packet level exceeds log2 of the window length");
            }
            return N;
        }
    }

    // The packet level shares the mother's filters with the pyramid, so it is
    // built by the pyramid's constructor and only its depth and buffers added.
    WaveletTransform::WaveletTransform(unsigned int N, enum WaveletType wt, unsigned int packetDepth)
    :
    WaveletTransform(PacketLength(N, packetDepth), wt, Unchecked()) {
        mDepth = packetDepth;
        if (wt == LocalCos) {
            if (packetDepth == 0) {
                throw std::invalid_argument("WaveletTransform: LocalCos needs a segment length 2^packetDepth of at least 2");
            }
            mCos.reset(new LocalCosineTransform(mN, 1u << packetDepth));
        } else {
            mScratch.assign(mN, 0.0);
            mOrder.assign(mN, 0.0);
        }
    }

    // A window of another length: the GSL workspace, the packet buffers and
    // the local cosine basis follow it; the level must still fit.
    void WaveletTransform::Resize(unsigned int N) {
        LogWarning("WaveletTransform: the size of input data is different from the size of the working space. Resizing it");
        if ((static_cast<std::size_t>(1) << mDepth) > N) {
            throw std::invalid_argument("WaveletTransform: the packet level exceeds log2 of the window length");
        }
        std::unique_ptr<LocalCosineTransform> cosine;
        if (mCos) {
            cosine.reset(new LocalCosineTransform(N, mCos->GetSegment()));
        }
        gsl_wavelet_workspace* work = gsl_wavelet_workspace_alloc(N);
        gsl_wavelet_workspace_free(mWork);
        mWork = work;
        mN = N;
        if (mCos) {
            mCos = std::move(cosine);
        } else if (mDepth > 0) {
            mScratch.assign(mN, 0.0);
            mOrder.assign(mN, 0.0);
        }
    }
    ///
    /// Destructor
    ///

    WaveletTransform::~WaveletTransform() {
        gsl_wavelet_free(mW);
        gsl_wavelet_workspace_free(mWork);
    }

    void WaveletTransform::Forward(SeqViewDouble& In) {
        Dmatrix * in = In.GetData();
        WaveletTransform::Forward(*in);
    }

    void WaveletTransform::Inverse(SeqViewDouble& In) {
        Dmatrix * in = In.GetData();
        WaveletTransform::Inverse(*in);
    }

    void WaveletTransform::Forward(Dmatrix& In) {
        if (In.size1() != 1) {
            LogWarning("WaveletTransform: multichannel yet not implemented. Working on first channel");
        }
        if (In.size2() != mN) {
            Resize(static_cast<unsigned int>(In.size2()));
        }
        double *data = new double[ mN ];
        for (unsigned int i = 0; i < mN; i++) {
            data[ i ] = In(0, i);
        }

        if (mCos) {
            mCos->Forward(data);
        } else if (mDepth == 0) {
            gsl_wavelet_transform_forward(mW, data, 1, mN, mWork);
        } else {
            PacketForward(data);
        }
        for (unsigned int i = 0; i < mN; i++) {
            In(0, i) = data[ i ];
        }
        delete[] data;
    }

    void WaveletTransform::Inverse(Dmatrix& In) {

        if (In.size1() != 1) {
            LogWarning("WaveletTransform: multichannel yet not implemented. Working on first channel");
        }
        if (In.size2() != mN) {
            Resize(static_cast<unsigned int>(In.size2()));
        }
        double* data = new double[ mN ];
        for (unsigned int i = 0; i < mN; i++) {
            data[ i ] = In(0, i);
        }

        if (mCos) {
            mCos->Inverse(data);
        } else if (mDepth == 0) {
            gsl_wavelet_transform_inverse(mW, data, 1, mN, mWork);
        } else {
            PacketInverse(data);
        }
        for (unsigned int i = 0; i < mN; i++) {
            In(0, i) = data[ i ];
        }
        delete[] data;
    }

    // One periodized two-channel step on n samples, the operation GSL's
    // pyramid applies at each of its levels (gsl/wavelet/dwt.c, dwt_step),
    // written out because GSL keeps it static. The same filters, offset and
    // wrap are used, so a packet level of depth one is the finest step of the
    // pyramid, coefficient for coefficient. n is a power of 2, so masking with
    // n - 1 is the reduction modulo n that periodizes the filters, which keeps
    // the step orthonormal for any n, filters longer than the band included.
    void WaveletTransform::Step(double* a, std::size_t n, bool forward) {
        const std::size_t nc = mW->nc;
        const std::size_t n1 = n - 1;
        const std::size_t nh = n >> 1;
        const std::size_t nmod = nc * n - mW->offset;
        for (std::size_t i = 0; i < n; i++) {
            mScratch[i] = 0.0;
        }
        if (forward) {
            for (std::size_t ii = 0, i = 0; i < n; i += 2, ii++) {
                double h = 0.0, g = 0.0;
                const std::size_t ni = i + nmod;
                for (std::size_t k = 0; k < nc; k++) {
                    const std::size_t jf = n1 & (ni + k);
                    h += mW->h1[k] * a[jf];
                    g += mW->g1[k] * a[jf];
                }
                mScratch[ii] += h;
                mScratch[ii + nh] += g;
            }
        } else {
            for (std::size_t ii = 0, i = 0; i < n; i += 2, ii++) {
                const double ai = a[ii];
                const double ai1 = a[ii + nh];
                const std::size_t ni = i + nmod;
                for (std::size_t k = 0; k < nc; k++) {
                    const std::size_t jf = n1 & (ni + k);
                    mScratch[jf] += mW->h2[k] * ai + mW->g2[k] * ai1;
                }
            }
        }
        for (std::size_t i = 0; i < n; i++) {
            a[i] = mScratch[i];
        }
    }

    // Level l splits each of its 2^l bands of N / 2^l samples in two, lowpass
    // half first, which leaves the tree in natural (Paley) order. The band of
    // frequency rank f sits at natural position f ^ (f >> 1), its Gray code,
    // because each highpass branch reverses the order of what lies below it.
    void WaveletTransform::PacketForward(double* data) {
        const std::size_t N = mN;
        for (unsigned int l = 0; l < mDepth; l++) {
            const std::size_t n = N >> l;
            for (std::size_t start = 0; start < N; start += n) {
                Step(data + start, n, true);
            }
        }
        const std::size_t bands = static_cast<std::size_t>(1) << mDepth;
        const std::size_t len = N >> mDepth;
        for (std::size_t f = 0; f < bands; f++) {
            const std::size_t natural = f ^ (f >> 1);
            for (std::size_t k = 0; k < len; k++) {
                mOrder[f * len + k] = data[natural * len + k];
            }
        }
        for (std::size_t i = 0; i < N; i++) {
            data[i] = mOrder[i];
        }
    }

    void WaveletTransform::PacketInverse(double* data) {
        const std::size_t N = mN;
        const std::size_t bands = static_cast<std::size_t>(1) << mDepth;
        const std::size_t len = N >> mDepth;
        for (std::size_t f = 0; f < bands; f++) {
            const std::size_t natural = f ^ (f >> 1);
            for (std::size_t k = 0; k < len; k++) {
                mOrder[natural * len + k] = data[f * len + k];
            }
        }
        for (std::size_t i = 0; i < N; i++) {
            data[i] = mOrder[i];
        }
        for (unsigned int l = mDepth; l-- > 0;) {
            const std::size_t n = N >> l;
            for (std::size_t start = 0; start < N; start += n) {
                Step(data + start, n, false);
            }
        }
    }

    ///
    /// Copy constructor
    ///
    /// @param from The instance that must be copied

    // The GSL handles are owned, so a copy allocates its own for the same
    // mother, length and packet level rather than sharing the original's.
    WaveletTransform::WaveletTransform(const WaveletTransform& from)
    :
    WaveletTransform(from.mN, from.mType, Unchecked()) {
        mDepth = from.mDepth;
        mScratch = from.mScratch;
        mOrder = from.mOrder;
        if (from.mCos) {
            mCos.reset(new LocalCosineTransform(*from.mCos));
        }
    }



    ///
    /// Assignement operator
    ///
    /// @param from The instance to be assigned from
    ///
    /// @return a reference to a new object

    WaveletTransform& WaveletTransform::operator=(const WaveletTransform& from) {
        if (this != &from) {
            WaveletTransform copy(from);
            std::swap(mW, copy.mW);
            std::swap(mWork, copy.mWork);
            std::swap(mN, copy.mN);
            std::swap(mDepth, copy.mDepth);
            std::swap(mType, copy.mType);
            std::swap(mScratch, copy.mScratch);
            std::swap(mOrder, copy.mOrder);
            std::swap(mCos, copy.mCos);
        }
        return * this;
    }
    ///Getters
    ///

    void WaveletTransform::WaveletPrint() {
        if (mCos) {
            printf("Local cosine: segment %u, bell half-width %u, periodic edges, DCT-IV\n",
                   mCos->GetSegment(), mCos->GetOverlap());
            return;
        }
        size_t n = mW->nc;
        size_t i;

        printf("Wavelet type: %s\n", mW->type->name);

        printf
                (" h1(%d):%12.8f   g1(%d):%12.8f       h2(%d):%12.8f   g2(%d):%12.8f\n",
                0, mW->h1[ 0 ], 0, mW->g1[ 0 ], 0, mW->h2[ 0 ], 0, mW->g2[ 0 ]);

        for (i = 1; i < (n < 10 ? n : 10); i++) {
            printf
                    (" h1(%ld):%12.8f   g1(%ld):%12.8f       h2(%ld):%12.8f   g2(%ld):%12.8f\n",
                    i, mW->h1[ i ], i, mW->g1[ i ], i, mW->h2[ i ], i, mW->g2[ i ]);
        }

        for (; i < n; i++) {
            printf
                    ("h1(%ld):%12.8f  g1(%ld):%12.8f      h2(%ld):%12.8f  g2(%ld):%12.8f\n",
                    i, mW->h1[ i ], i, mW->g1[ i ], i, mW->h2[ i ], i, mW->g2[ i ]);
        }
    }

    void WaveletTransform::WaveletWaveform(Dvector& V) {
        double* data = new double[ mN ];
        for (unsigned int i = 0; i < mN; i++) {
            data[ i ] = 0.0;
        }

        data[ 22 ] = 1.0;
        if (mCos) {
            mCos->Inverse(data);
        } else if (mDepth == 0) {
            gsl_wavelet_transform_inverse(mW, data, 1, mN, mWork);
        } else {
            PacketInverse(data);
        }
        for (unsigned int i = 0; i < mN; i++) {
            V(i) = data[ i ];
        }
        delete[] data;
    }

}
