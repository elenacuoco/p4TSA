
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
#include <algorithm>
#include <stdexcept>



namespace tsa {

    namespace {
        // Prefix the shared parser's message with the class name.
        std::vector<WaveletBasis> Parse(const std::string& names, unsigned int window, unsigned int blockLength) {
            try {
                return ParseWaveletBases(names, window, blockLength);
            } catch (const std::invalid_argument& e) {
                throw std::invalid_argument(std::string("WDF2Reconstruct: ") + e.what());
            }
        }
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
        mSpecs = Parse(DefaultWaveletBases(), mWindow, 0);
        Build();
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
            mWindowing(from.mWindowing),
            mSpecs(from.mSpecs) {
        Build();
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
        mSpecs = from.mSpecs;
        Build();
        return *this;
    }

    // Each candidate owns its transform, built from its specification, so a
    // copy rebuilds its candidates rather than sharing them.
    void WDF2Reconstruct::Build() {
        mBases.clear();
        mBaseNames.clear();
        mBases.reserve(mSpecs.size());
        mBaseNames.reserve(mSpecs.size());
        for (const auto& spec : mSpecs) {
            mBases.push_back(MakeWaveletTransform(spec, mWindow));
            mBaseNames.push_back(spec.name);
        }
    }

    // Under the block rule every packet band or local cosine row must hold
    // one full block (see CheckWaveletBlocks).
    void WDF2Reconstruct::SetBases(const std::string& names) {
        mSpecs = Parse(names, mWindow, mT == WaveletThreshold::block ? mWavThres.GetBlockLength() : 0);
        Build();
    }

    std::string WDF2Reconstruct::GetBases() const {
        return JoinWaveletBases(mSpecs);
    }

    void WDF2Reconstruct::Reconstruct(const EventFullFeatured& Ev, Dvector& out) const {
        WaveletBasis basis;
        try {
            basis = ParseWaveletBasis(Ev.mWave, mWindow);
        } catch (const std::invalid_argument& e) {
            throw std::invalid_argument(std::string("WDF2Reconstruct: ") + e.what());
        }
        std::unique_ptr<WaveletTransform> transform = MakeWaveletTransform(basis, mWindow);
        Dmatrix c(1, mWindow);
        const std::size_t n = std::min<std::size_t>(Ev.mCoeff.size(), mWindow);
        for (unsigned int i = 0; i < mWindow; i++) {
            c(0, i) = (i < n) ? Ev.mCoeff[i] : 0.0;
        }
        transform->Inverse(c);
        out.resize(mWindow);
        for (unsigned int i = 0; i < mWindow; i++) {
            out(i) = c(0, i);
        }
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
            mWavThres.SetLayout(mBases[b]->GetPacketDepth());
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

