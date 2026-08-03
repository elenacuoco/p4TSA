
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

    namespace {
        // Candidate wavelet bases for per-window basis selection in
        // WDF2Classify/WDF2Reconstruct: the full orthonormal GSL family
        // (Haar + every order of Daubechies/Daubechies-centered it
        // supports, up to order 20 -- GSL's own maximum). The biorthogonal
        // B-spline family (Bspline*/BsplineC*) is deliberately excluded:
        // it does not preserve L2 energy (Parseval's theorem), so
        // WaveletThreshold's pooled-median sigma estimate -- which assumes
        // homoscedastic, orthonormal coefficients -- systematically
        // misestimates its per-level noise floor and let it win basis
        // selection spuriously, even on pure Gaussian noise.
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

    WDF2Classify::WDF2Classify(unsigned int window, unsigned int overlap, double thresh, double sigma, unsigned int ncoeff, enum WaveletThreshold::WaveletThresholding WTh)
            :
            mWindow(window),
            mNCoeff(ncoeff),
            mOverlap(overlap),
            mStep(mWindow - mOverlap),
            mThresh(thresh),
            mFirstCall(true),
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

    WDF2Classify::WDF2Classify(const WDF2Classify& from)
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
            mFirstCall(from.mFirstCall),
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

    WDF2Classify& WDF2Classify::operator=(const WDF2Classify& from) {
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
        mFirstCall = from.mFirstCall;
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

    unsigned int WDF2Classify::GetDataVector(double& abov, double& sigmaWin, Dvector& Cmax, int& levelR, std::string& Wave) {
        double varmax = -1.0;
        Dvector cmax(mNCoeff);
        int level = 0;
        double bestSigma = 0.0;
        Cmax.resize(mNCoeff);

        if ((mWindow) > mBuffer.Size()) {
            LogWarning("Not enough data points");
            return 0;
        }

        // Try every candidate orthonormal basis on the same window, keep
        // whichever produces the largest post-threshold RMS relative to its
        // own noise floor (both computed from that basis's own
        // coefficients, so the comparison is basis-fair -- see
        // kCandidateBases above for why biorthogonal bases are excluded).
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
            varB = (sigmaB > 0) ? (sqrt(varB / mWindow) / sigmaB) : 0.0;

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

