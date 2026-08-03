
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

    namespace {
        // Same candidate basis set as WDF2Classify (see that file's
        // GetDataVector for the rationale on excluding biorthogonal
        // B-spline bases).
        const std::pair<enum WaveletTransform::WaveletType, const char*> kCandidateBases[] = {
            {WaveletTransform::Haar, "Haar"},
            {WaveletTransform::Daub4, "Daub4"},
            {WaveletTransform::Daub6, "Daub6"},
            {WaveletTransform::Daub8, "Daub8"},
            {WaveletTransform::Daub10, "Daub10"},
            {WaveletTransform::Daub12, "Daub12"},
            {WaveletTransform::Daub14, "Daub14"},
            {WaveletTransform::Daub16, "Daub16"},
            {WaveletTransform::Daub18, "Daub18"},
            {WaveletTransform::Daub20, "Daub20"},
            {WaveletTransform::DaubC4, "DaubC4"},
            {WaveletTransform::DaubC6, "DaubC6"},
            {WaveletTransform::DaubC8, "DaubC8"},
            {WaveletTransform::DaubC10, "DaubC10"},
            {WaveletTransform::DaubC12, "DaubC12"},
            {WaveletTransform::DaubC14, "DaubC14"},
            {WaveletTransform::DaubC16, "DaubC16"},
            {WaveletTransform::DaubC18, "DaubC18"},
            {WaveletTransform::DaubC20, "DaubC20"},
        };
        const std::size_t kNumCandidateBases = sizeof(kCandidateBases) / sizeof(kCandidateBases[0]);
    }

    WDF2Reconstruct::WDF2Reconstruct(unsigned int window, unsigned int overlap, double thresh, double sigma, unsigned int ncoeff, enum WaveletThreshold::WaveletThresholding WTh)
            :
            mWindow(window),
            mNCoeff(ncoeff),
            mOverlap(overlap),
            mStep(mWindow - mOverlap),
            mThresh(thresh),
            mSigma(sigma),
            mBuffer(1),
            mBuff(1, mWindow),
            mT(WTh),
            mWavThres(mWindow, mWindow, sigma),
            mWindowing(mWindow),
            mEvFF(mNCoeff) {
        mBases.reserve(kNumCandidateBases);
        mBaseNames.reserve(kNumCandidateBases);
        for (std::size_t i = 0; i < kNumCandidateBases; ++i) {
            mBases.push_back(std::unique_ptr<WaveletTransform>(
                new WaveletTransform(mWindow, kCandidateBases[i].first)));
            mBaseNames.push_back(kCandidateBases[i].second);
        }
    }

    WDF2Reconstruct::WDF2Reconstruct(const WDF2Reconstruct& from)
            :
            mWindow(from.mWindow),
            mOverlap(from.mOverlap),
            mStep(from.mStep),
            mNCoeff(from.mNCoeff),
            mThresh(from.mThresh),
            mSigma(from.mSigma),
            mBuffer(from.mBuffer),
            mStartTime(from.mStartTime),
            mSampling(from.mSampling),
            mBuff(from.mBuff),
            mEvFF(from.mEvFF),
            mT(from.mT),
            mWavThres(from.mWavThres),
            mWindowing(from.mWindowing) {
        mBases.reserve(kNumCandidateBases);
        mBaseNames = from.mBaseNames;
        for (std::size_t i = 0; i < kNumCandidateBases; ++i) {
            mBases.push_back(std::unique_ptr<WaveletTransform>(
                new WaveletTransform(mWindow, kCandidateBases[i].first)));
        }
    }

    WDF2Reconstruct& WDF2Reconstruct::operator=(const WDF2Reconstruct& from) {
        if (this == &from) {
            return *this;
        }
        mWindow = from.mWindow;
        mOverlap = from.mOverlap;
        mStep = from.mStep;
        mNCoeff = from.mNCoeff;
        mThresh = from.mThresh;
        mSigma = from.mSigma;
        mBuffer = from.mBuffer;
        mStartTime = from.mStartTime;
        mSampling = from.mSampling;
        mBuff = from.mBuff;
        mEvFF = from.mEvFF;
        mT = from.mT;
        mWavThres = from.mWavThres;
        mWindowing = from.mWindowing;

        mBaseNames = from.mBaseNames;
        mBases.clear();
        mBases.reserve(kNumCandidateBases);
        for (std::size_t i = 0; i < kNumCandidateBases; ++i) {
            mBases.push_back(std::unique_ptr<WaveletTransform>(
                new WaveletTransform(mWindow, kCandidateBases[i].first)));
        }
        return *this;
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

    unsigned int WDF2Reconstruct::GetDataVector(double& abov, double& sigmaWin, Dvector& Cmax, int& levelR, std::string& Wave) {
        double varmax = -1.0;
        Dvector cmax(mNCoeff);
        int level = 0;
        double bestSigma = 0.0;
        Cmax.resize(mNCoeff);

        if ((mWindow) > mBuffer.Size()) {
            LogWarning("Not enough data points");
            return 0;
        }

        // Try every candidate orthonormal basis; formula matches this
        // class's original convention (no /mWindow, extra factor of 2 in
        // the denominator -- kept as-is, differs from WDF2Classify's).
        for (std::size_t b = 0; b < mBases.size(); ++b) {
            for (unsigned int i = 0; i < mWindow; i++) {
                mBuff(0, i) = mBuffer(0, i);
            }

            mBases[b]->Forward(mBuff);
            mWavThres(mBuff, mT);

            double sigmaB = mWavThres.GetSigma();
            int levelB = mWavThres.GetLevel();

            double varB = 0.0;
            for (unsigned int i = 0; i < mWindow; i++) {
                varB += (mBuff(0, i) * mBuff(0, i));
            }
            varB = (sigmaB > 0) ? (sqrt(varB) / (2.0 * sigmaB)) : 0.0;

            if (varB >= varmax) {
                varmax = varB;
                for (unsigned int i = 0; i < mNCoeff; i++) {
                    cmax[i] = mBuff(0, i);
                }
                level = levelB;
                Wave = mBaseNames[b];
                bestSigma = sigmaB;
            }
        }

        mBuffer.DelPoints(mStep);

        if (varmax >= mThresh) {
            abov = varmax;
            sigmaWin = bestSigma;
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

