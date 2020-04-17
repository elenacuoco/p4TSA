
//
// C++ Implementation: WavTransientDetection.cpp
//
// Description: Module responsible for the reconstruction of waveforms
// Current version (feb. 2020) contains only one wavelet - BSpline309
//
// Author: Filip Morawski <fmorawski@camk.edu.pl>, (C) 2020
//
// Copyright: See COPYING file that comes with this distribution
//
//
//

#include <WDF2Reconstruct.hpp>



namespace tsa {

    WDF2Reconstruct::WDF2Reconstruct(unsigned int window, unsigned int overlap, double thresh, double sigma, unsigned int ncoeff, enum WaveletThreshold::WaveletThresholding WTh)
            :
            mWindow(window),
            mNCoeff(ncoeff),
            mOverlap(overlap),
            mStep(mWindow - mOverlap),
            mThresh(thresh),
            mSigma(sigma),
            mSigmaH(sigma),
            mSigmaBsC309(sigma),
            mBuffer(1),
            mBuff(1, mWindow),
            mWtH(WaveletTransform::Haar),
            mWTH(mWindow, mWtH),
            mWtBsC309(WaveletTransform::BsplineC309),
            mWTBsC309(mWindow, mWtBsC309),

            //mT( WaveletThreshold::dohonojohnston ),
            mT(WTh),
            mWavThres(mWindow, mWindow, sigma),

            mWindowing(mWindow),
            mEvFF(mNCoeff) {
    }




    ///
    /// Destructor
    ///

    WDF2Reconstruct::~WDF2Reconstruct() {

    }


    ///

    int WDF2Reconstruct::GetDataNeeded() {

        return mBuffer.Size() - mWindow;
    }

    ///

    /**
     *
     * @param Data
     * @param scale
     */
    void WDF2Reconstruct::SetData(Dmatrix& Data, double scale) {
        mBuffer.AddPoints(Data, scale);
    }


    ///Execute method

    unsigned int WDF2Reconstruct::GetDataVector(double& abov, Dvector& Cmax, int& levelR, std::string& Wave) {
        double varmax = 0.0;
        Dvector cmax(mNCoeff);
        int level;
        double varH;
        double varBsC309;
        int levelH;
        int levelBsC309;
        Dvector cH(mNCoeff);
        Dvector cBsC309(mNCoeff);
        Cmax.resize(mNCoeff);

        if ((mWindow) > mBuffer.Size()) {
            LogWarning("Not enough data points");
            return 0;
        }
        //
        for (unsigned int i = 0; i < mWindow; i++) {
            mBuff(0, i) = mBuffer(0, i);
        }

        mWTH.Forward(mBuff);
        mWavThres(mBuff, mT);

        mSigmaH = mWavThres.GetSigma();
        levelH = mWavThres.GetLevel();
        varH = 0.0;
        for (unsigned int i = 0; i < mWindow; i++) {
            varH += (mBuff(0, i) * mBuff(0, i));
        }

        for (unsigned int i = 0; i < mNCoeff; i++) {
            cH[i] = mBuff(0, i);

        }
        //

        //
        for (unsigned int i = 0; i < mWindow; i++) {
            mBuff(0, i) = mBuffer(0, i);
        }

        mWTBsC309.Forward(mBuff);
        mWavThres(mBuff, mT);

        mSigmaBsC309 = mWavThres.GetSigma();
        levelBsC309 = mWavThres.GetLevel();

        varBsC309 = 0.0;

        for (unsigned int i = 0; i < mWindow; i++) {

            varBsC309 += (mBuff(0, i) * mBuff(0, i));
        }

        for (unsigned int i = 0; i < mNCoeff; i++) {
            cBsC309[i] = mBuff(0, i);

        }
        //

        if (mSigmaH>0) {
            varH = sqrt(varH) / (2.0*mSigmaH);
        }
        else
        {
            varH=0;
        }


        if (mSigmaBsC309>0) {
            varBsC309 = sqrt(varBsC309) / (2.0*mSigmaBsC309);
        }
        else
        {
            varBsC309=0;
        }

        varmax = varH;
        for (unsigned int i = 0; i < mNCoeff; i++) {
            cmax[i] = cH[i];
        }
        level = levelH;
        Wave = "Haar";
        
         

       //  $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$


        // ###########33 BSPLINE ####################
        if (varBsC309 >= varmax) {
            varmax = varBsC309;
            for (unsigned int i = 0; i < mNCoeff; i++) {
                cmax[i] = cBsC309[i];
            }

            level = levelBsC309;
            Wave = "BsplineC309";
        }

        mBuffer.DelPoints(mStep);


        if (varmax >= mThresh) {
            abov = varmax;
            levelR = level;
            for (unsigned int i = 0; i < mNCoeff; i++) {
                Cmax[i] = cmax[i];

            }
            return 1;
        }
        else

            return 0;

    }

}

