//
//
// C++ Implementation: WaveletTransform.cpp
//
// Description:
//
//
// Author: Elena Cuoco <elena.cuoco@ego-gw.it>, (C) 2005
//
// Copyright: See COPYING file that comes with this distribution
//
//
//

#include <WaveletTransform.hpp>

namespace tsa {

    WaveletTransform::WaveletTransform(unsigned int N, enum WaveletType wt)
    :
    mN(N) {
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
            default:
                mW = gsl_wavelet_alloc(gsl_wavelet_haar, 2);
                break;
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
            mN = In.size2();
            LogWarning("WaveletTransform: the size of input data is different from the size of the working space. Resizing it");
            mWork = gsl_wavelet_workspace_alloc(In.size2());
        }
        double *data = new double[ mN ];
        for (unsigned int i = 0; i < mN; i++) {
            data[ i ] = In(0, i);
        }

        gsl_wavelet_transform_forward(mW, data, 1, mN, mWork);
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
            mN = In.size2();
            LogWarning("WaveletTransform: the size of input data is different from the size of the working space. Resizing it");
            mWork = gsl_wavelet_workspace_alloc(In.size2());
        }
        double* data = new double[ mN ];
        for (unsigned int i = 0; i < mN; i++) {
            data[ i ] = In(0, i);
        }

        gsl_wavelet_transform_inverse(mW, data, 1, mN, mWork);
        for (unsigned int i = 0; i < mN; i++) {
            In(0, i) = data[ i ];
        }
        delete[] data;
    }

    ///
    /// Copy constructor
    ///
    /// @param from The instance that must be copied

    WaveletTransform::WaveletTransform(const WaveletTransform& from) {
    }



    ///
    /// Assignement operator
    ///
    /// @param from The instance to be assigned from
    ///
    /// @return a reference to a new object

    WaveletTransform& WaveletTransform::operator=(const WaveletTransform& from) {
        return * this;
    }
    ///Getters
    ///

    void WaveletTransform::WaveletPrint() {
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
        gsl_wavelet_transform_inverse(mW, data, 1, mN, mWork);
        for (unsigned int i = 0; i < mN; i++) {
            V(i) = data[ i ];
        }
        delete data;
    }

}
