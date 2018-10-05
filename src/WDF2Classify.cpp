
//
// C++ Implementation: WavTransientDetection.cpp
//
// Description:
//
//
// Author: Elena Cuoco <elena.cuoco@ego-gw.it>, (C) 2014
//
// Copyright: See COPYING file that comes with this distribution
//
//
//

#include <WDF2Classify.hpp>



namespace tsa {

    WDF2Classify::WDF2Classify(unsigned int window, unsigned int overlap, double thresh, double sigma, unsigned int ncoeff, enum WaveletThreshold::WaveletThresholding WTh)
            :
            mWindow(window),
            mNCoeff(ncoeff),
            mOverlap(overlap),
            mStep(mWindow - mOverlap),
            mThresh(thresh),
            mSigma(sigma),
            mSigmaH(sigma),
            mSigma4(sigma),
            mSigmaC8(sigma),
            mSigma10(sigma),
            mSigma12(sigma),
            mSigmaC16(sigma),
            mSigma20(sigma),
            mSigmaC20(sigma),
            mSigmaBsC206(sigma),
            mSigmaBsC103(sigma),
            mSigmaBsC309(sigma),
            mSigmaDCT(sigma),
            mDct(mWindow),
            mBuffDct(1, mWindow),
            mBuffer(1),
            mBuff(1, mWindow),
            mWtH(WaveletTransform::Haar),
            mWTH(mWindow, mWtH),
            mWt4(WaveletTransform::Daub4),
            mWT4(mWindow, mWt4),
            mWtC8(WaveletTransform::DaubC8),
            mWTC8(mWindow, mWtC8),
            mWt10(WaveletTransform::Daub10),
            mWT10(mWindow, mWt10),
            mWt12(WaveletTransform::Daub12),
            mWT12(mWindow, mWt12),
            mWtC16(WaveletTransform::DaubC16),
            mWTC16(mWindow, mWtC16),
            mWt20(WaveletTransform::Daub20),
            mWT20(mWindow, mWt20),
            mWtC20(WaveletTransform::DaubC20),
            mWTC20(mWindow, mWtC20),
            mWtBsC103(WaveletTransform::BsplineC103),
            mWTBsC103(mWindow, mWtBsC103),
            mWtBsC206(WaveletTransform::BsplineC206),
            mWTBsC206(mWindow, mWtBsC206),
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

    WDF2Classify::~WDF2Classify() {

    }


    ///

    int WDF2Classify::GetDataNeeded() {

        return mBuffer.Size() - mWindow;
    }

    ///

    /**
     *
     * @param Data
     * @param scale
     */
    void WDF2Classify::SetData(Dmatrix& Data, double scale) {
        mBuffer.AddPoints(Data, scale);
    }


    ///Execute method

    unsigned int WDF2Classify::GetDataVector(double& abov, Dvector& Cmax, int& levelR, std::string& Wave) {
        double varmax = 0.0;
        Dvector cmax(mNCoeff);
        int level;
        double varH;
        double var4;
        double varC8;
        double var10;
        double var12;
        double varC16;
        double var20;
        double varC20;
        double varBsC206;
        double varBsC103;
        double varBsC309;
        double varDCT;
        int levelH;
        int level4;
        int levelC8;
        int level10;
        int level12;
        int levelC16;
        int level20;
        int levelC20;
        int levelBsC206;
        int levelBsC103;
        int levelBsC309;
        int levelDCT;
        Dvector cH(mNCoeff);
        Dvector c4(mNCoeff);
        Dvector cC8(mNCoeff);
        Dvector c10(mNCoeff);
        Dvector c12(mNCoeff);
        Dvector cC16(mNCoeff);
        Dvector c20(mNCoeff);
        Dvector cC20(mNCoeff);
        Dvector cBsC206(mNCoeff);
        Dvector cBsC103(mNCoeff);
        Dvector cBsC309(mNCoeff);
        Dvector cDCT(mNCoeff);
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

        mWT4.Forward(mBuff);
        mWavThres(mBuff, mT);

        mSigma4 = mWavThres.GetSigma();
        level4 = mWavThres.GetLevel();

        var4 = 0.0;

        for (unsigned int i = 0; i < mWindow; i++) {

            var4 += (mBuff(0, i) * mBuff(0, i));
        }

        for (unsigned int i = 0; i < mNCoeff; i++) {
            c4[i] = mBuff(0, i);

        }
        //

        //



        for (unsigned int i = 0; i < mWindow; i++) {
            mBuff(0, i) = mBuffer(0, i);
        }

        mWTC8.Forward(mBuff);
        mWavThres(mBuff, mT);

        mSigmaC8 = mWavThres.GetSigma();
        levelC8 = mWavThres.GetLevel();

        varC8 = 0.0;

        for (unsigned int i = 0; i < mWindow; i++) {

            varC8 += (mBuff(0, i) * mBuff(0, i));
        }

        for (unsigned int i = 0; i < mNCoeff; i++) {
            cC8[i] = mBuff(0, i);

        }

        //
        //
        for (unsigned int i = 0; i < mWindow; i++) {
            mBuff(0, i) = mBuffer(0, i);
        }


        mWT10.Forward(mBuff);
        mWavThres(mBuff, mT);

        mSigma10 = mWavThres.GetSigma();
        level10 = mWavThres.GetLevel();

        var10 = 0.0;

        for (unsigned int i = 0; i < mWindow; i++) {

            var10 += (mBuff(0, i) * mBuff(0, i));
        }

        for (unsigned int i = 0; i < mNCoeff; i++) {
            c10[i] = mBuff(0, i);

        }
        //
        //
        for (unsigned int i = 0; i < mWindow; i++) {
            mBuff(0, i) = mBuffer(0, i);
        }

        mWT12.Forward(mBuff);
        mWavThres(mBuff, mT);

        mSigma12 = mWavThres.GetSigma();
        level12 = mWavThres.GetLevel();

        var12 = 0.0;

        for (unsigned int i = 0; i < mWindow; i++) {


            var12 += (mBuff(0, i) * mBuff(0, i));
        }

        for (unsigned int i = 0; i < mNCoeff; i++) {
            c12[i] = mBuff(0, i);

        }
        //
        //

        for (unsigned int i = 0; i < mWindow; i++) {
            mBuff(0, i) = mBuffer(0, i);
        }

        mWTC16.Forward( mBuff );
        mWavThres(mBuff, mT);

        mSigmaC16 = mWavThres.GetSigma();
        levelC16 = mWavThres.GetLevel();

        varC16 = 0.0;

        for (unsigned int i = 0; i < mWindow; i++) {

            varC16 += (mBuff(0, i) * mBuff(0, i));
        }

        for (unsigned int i = 0; i < mNCoeff; i++) {
            cC16[i] = mBuff(0, i);

        }
        //
        //

        for (unsigned int i = 0; i < mWindow; i++) {
            mBuff(0, i) = mBuffer(0, i);
        }

        mWT20.Forward(mBuff);
        mWavThres(mBuff, mT);

        mSigma20 = mWavThres.GetSigma();
        level20 = mWavThres.GetLevel();

        var20 = 0.0;

        for (unsigned int i = 0; i < mWindow; i++) {


            var20 += (mBuff(0, i) * mBuff(0, i));
        }

        for (unsigned int i = 0; i < mNCoeff; i++) {
            c20[i] = mBuff(0, i);

        }
        //
        //

        for (unsigned int i = 0; i < mWindow; i++) {
            mBuff(0, i) = mBuffer(0, i);
        }

        mWTC20.Forward(mBuff);
        mWavThres(mBuff, mT);

        mSigmaC20 = mWavThres.GetSigma();
        levelC20 = mWavThres.GetLevel();

        varC20 = 0.0;

        for (unsigned int i = 0; i < mWindow; i++) {

            varC20 += (mBuff(0, i) * mBuff(0, i));
        }

        for (unsigned int i = 0; i < mNCoeff; i++) {
            cC20[i] = mBuff(0, i);

        }
        //
        for (unsigned int i = 0; i < mWindow; i++) {
            mBuff(0, i) = mBuffer(0, i);
        }

        mWTBsC206.Forward(mBuff);
        mWavThres(mBuff, mT);

        mSigmaBsC206 = mWavThres.GetSigma();
        levelBsC206 = mWavThres.GetLevel();

        varBsC206 = 0.0;

        for (unsigned int i = 0; i < mWindow; i++) {

            varBsC206 += (mBuff(0, i) * mBuff(0, i));
        }

        for (unsigned int i = 0; i < mNCoeff; i++) {
            cBsC206[i] = mBuff(0, i);

        }
        //
        //
        for (unsigned int i = 0; i < mWindow; i++) {
            mBuff(0, i) = mBuffer(0, i);
        }

        mWTBsC103.Forward(mBuff);
        mWavThres(mBuff, mT);

        mSigmaBsC103 = mWavThres.GetSigma();
        levelBsC103 = mWavThres.GetLevel();

        varBsC103 = 0.0;

        for (unsigned int i = 0; i < mWindow; i++) {

            varBsC103 += (mBuff(0, i) * mBuff(0, i));
        }

        for (unsigned int i = 0; i < mNCoeff; i++) {
            cBsC103[i] = mBuff(0, i);

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
        //
        for (unsigned int i = 0; i < mWindow; i++) {
            mBuffDct(0, i) = mBuffer(0, i);
        }

        mWindowing.execute(mBuffDct);

        mDct.execute(mBuffDct, mBuff);
        mBuff(0, 0) *= sqrt(1.0 / 2.0);

        for (unsigned int i = 0; i < mWindow; i++) {
            mBuff(0, i) *= sqrt(2.0 / mWindow);
        }


        mWavThres(mBuff, mT);

        mSigmaDCT = mWavThres.GetSigma();

        levelDCT = mWavThres.GetLevel();

        varDCT = 0.0;

        for (unsigned int i = 0; i < mWindow; i++) {
            varDCT += (mBuff(0, i) * mBuff(0, i));
        }

        for (unsigned int i = 0; i < mNCoeff; i++) {
            cDCT[i] = mBuff(0, i);

        }

        //
        //

        if (mSigmaH>0) {
            varH = sqrt(varH) / (2.0*mSigmaH);
        }
        else
        {
            varH=0;
        }
        if (mSigma4>0) {
            var4 = sqrt(var4) / (2.0*mSigma4);
        }
        else
        {
            var4=0;
        }
        if (mSigmaC8>0) {
            varC8 = sqrt(varC8) / (2.0*mSigmaC8);
        }
        else
        {
            varC8=0;
        }

        if (mSigma10>0) {
            var10 = sqrt(var10) / (2.0*mSigma10);
        }
        else
        {
            var10=0;
        }

        if (mSigma12>0) {
            var12 = sqrt(var12) / (2.0*mSigma12);
        }
        else
        {
            var12=0;
        }

        if (mSigmaC16>0) {
            varC16 = sqrt(varC16) / (2.0*mSigmaC16);
        }
        else
        {
            varC16=0;
        }
        if (mSigma20>0) {
            var20 = sqrt(var20) / (2.0*mSigma20);
        }
        else
        {
            var20=0;
        }
        if (mSigmaC20>0) {
            varC20 = sqrt(varC20) / (2.0*mSigmaC20);
        }
        else
        {
            varC20=0;
        }
        if (mSigmaBsC206>0) {
            varBsC206 = sqrt(varBsC206) / (2.0*mSigmaBsC206);
        }
        else
        {
            varBsC206=0;
        }

        if (mSigmaBsC103>0) {
            varBsC103 = sqrt(varBsC103) / (2.0*mSigmaBsC103);
        }
        else
        {
            varBsC103=0;
        }
        if (mSigmaBsC309>0) {
            varBsC309 = sqrt(varBsC309) / (2.0*mSigmaBsC309);
        }
        else
        {
            varBsC309=0;
        }
        if (mSigmaDCT>0) {
            varDCT = sqrt(varDCT) / (2.0*mSigmaDCT);
        }
        else
        {
            varDCT=0;
        }

        varmax = varH;
        for (unsigned int i = 0; i < mNCoeff; i++) {
            cmax[i] = cH[i];
        }
        level = levelH;
        Wave = "Haar";

        if (var4 >= varmax) {
            varmax = var4;
            for (unsigned int i = 0; i < mNCoeff; i++) {
                cmax[i] = c4[i];
            }

            level = level4;
            Wave = "Daub4";
        }

        if (varC8 >= varmax) {
            varmax = varC8;
            for (unsigned int i = 0; i < mNCoeff; i++) {
                cmax[i] = cC8[i];
            }
            level = levelC8;
            Wave = "DaubC8";
        }
        if (var10 >= varmax) {
            varmax = var10;
            for (unsigned int i = 0; i < mNCoeff; i++) {
                cmax[i] = c10[i];
            }

            level = level10;
            Wave = "Daub10";
        }
        if (var12 >= varmax) {
            varmax = var12;
            for (unsigned int i = 0; i < mNCoeff; i++) {
                cmax[i] = c12[i];
            }

            level = level12;
            Wave = "Daub12";
        }

        if (varC16 >= varmax) {
            varmax = varC16;
            for (unsigned int i = 0; i < mNCoeff; i++) {
                cmax[i] = cC16[i];
            }

            level = levelC16;
            Wave = "DaubC16";
        }
        if (var20 >= varmax) {
            varmax = var20;
            for (unsigned int i = 0; i < mNCoeff; i++) {
                cmax[i] = c20[i];
            }

            level = level20;
            Wave = "Daub20";
        }
        if (varC20 >= varmax) {
            varmax = varC20;
            for (unsigned int i = 0; i < mNCoeff; i++) {
                cmax[i] = cC20[i];
            }

            level = levelC20;
            Wave = "DaubC20";
        }
        if (varBsC206 >= varmax) {
            varmax = varBsC206;
            for (unsigned int i = 0; i < mNCoeff; i++) {
                cmax[i] = cBsC206[i];
            }

            level = levelBsC206;
            Wave = "BsplineC206";
        }
        if (varBsC103 >= varmax) {
            varmax = varBsC103;
            for (unsigned int i = 0; i < mNCoeff; i++) {
                cmax[i] = cBsC103[i];
            }

            level = levelBsC103;
            Wave = "BsplineC103";
        }
        if (varBsC309 >= varmax) {
            varmax = varBsC309;
            for (unsigned int i = 0; i < mNCoeff; i++) {
                cmax[i] = cBsC309[i];
            }

            level = levelBsC309;
            Wave = "BsplineC309";
        }
        if (varDCT >= varmax) {
            varmax = varDCT;
            for (unsigned int i = 0; i < mNCoeff; i++) {
                cmax[i] = cDCT[i];
            }

            level = levelDCT;
            Wave = "DCT";
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

        return 0;

    }

}

