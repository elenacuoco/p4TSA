
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
        // WDF2Classify/WDF2Reconstruct. All orthonormal (required -- see
        // below), 10 total (2026-08-03, down from 19):
        //
        // - Daub4/8/12/16/20, centered only. Plain and centered Daubechies
        //   of the same order are the same filter taps, just phase-shifted;
        //   empirically their post-threshold RMS/sigma ratio agrees to
        //   4-6% on real+injected data (verified 2026-08-03), so keeping
        //   both wastes ~half this list's compute for no real diversity.
        //   Centered kept over plain for its symmetric time support (more
        //   consistent gpsPeak estimates). Every-other order (not all 9)
        //   trims further while still spanning short- to long-support.
        // - Sym4/Sym8 (symlet, centered -- see ExtraWaveletFamilies.hpp).
        //   Sym2/Sym3 are excluded because they are numerically identical
        //   to Daub4/Daub6 (verified against PyWavelets 2026-08-03) --
        //   Symlets only start differing from Daubechies at order 4.
        // - Coif1/Coif2 (coiflet, centered -- see ExtraWaveletFamilies.hpp):
        //   unlike Daubechies/Symlet, has vanishing moments for the scaling
        //   function too, not just the wavelet -- genuinely different
        //   coefficient behavior on smooth/slowly-varying signal content,
        //   not just a further Daubechies-family variant.
        // - Haar.
        //
        // The biorthogonal B-spline family (Bspline*/BsplineC*) remains
        // excluded: it does not preserve L2 energy (Parseval's theorem), so
        // WaveletThreshold's pooled-median sigma estimate -- which assumes
        // homoscedastic, orthonormal coefficients -- systematically
        // misestimates its per-level noise floor and let it win basis
        // selection spuriously, even on pure Gaussian noise. A plain
        // (non-wavelet-packet) DCT was tried in this codebase's history and
        // removed: DCT is a single global, non-multiresolution transform,
        // structurally mismatched with the pyramidal-DWT-based downstream
        // machinery (coeff_freq_bands/coeff_time_bounds assume a Mallat
        // octave layout) and with WaveletThreshold's own per-level sigma
        // assumptions -- reintroducing it needs a real cosine wavelet
        // packet (tree-structured, like DWT), not a block DCT, plus its own
        // downstream time-frequency mapping; not attempted here.
        const std::pair<enum WaveletTransform::WaveletType, const char*> kCandidateBases[] = {
            {WaveletTransform::Haar, "Haar"},
            {WaveletTransform::DaubC4, "DaubC4"},
            {WaveletTransform::DaubC8, "DaubC8"},
            {WaveletTransform::DaubC12, "DaubC12"},
            {WaveletTransform::DaubC16, "DaubC16"},
            {WaveletTransform::DaubC20, "DaubC20"},
            {WaveletTransform::Sym4, "Sym4"},
            {WaveletTransform::Sym8, "Sym8"},
            {WaveletTransform::Coif1, "Coif1"},
            {WaveletTransform::Coif2, "Coif2"},
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

