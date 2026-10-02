
//
// C++ Implementation: WavTransientDetection.cpp
//
// Description:
//
//
// Author: Elena Cuoco <elena.cuoco@unibo.it>, (C) 2014
//
// Copyright: See COPYING file that comes with this distribution
//
//
//

#include <WDF2Classify.hpp>
#include <stdexcept>



namespace tsa {

    namespace {
        // The default candidate set of the per-window basis competition, the
        // one a WDF2Classify is built with until SetBases replaces it, and the
        // only place it is defined. All orthonormal (required: each
        // candidate's statistic is read on its own noise scale, which a
        // non-orthonormal basis does not preserve), all pyramids, 10 total.
        //
        // Ordered by filter length, shortest first (Haar 2 taps, DaubC4 4,
        // Coif2 12, DaubC16 16, DaubC20 and Sym10 20 -- equal length, by
        // name --, DaubC24 24, Coif5 30, DaubC32 32, DaubC40 40). The order is
        // part of the definition: on a tie of the window statistic the later
        // candidate wins (GetDataVector keeps a basis whose statistic is >=
        // the best so far), so a tie goes to the longer filter.
        //
        // History: 3.0.0-3.4.0 used Haar, DaubC4/8/12/16/20, Sym4, Sym8,
        // Coif1, Coif2 (2026-08-03, down from 19; see WDF2Reconstruct, which
        // keeps that list). The long mothers replace DaubC8, DaubC12, Sym4,
        // Sym8 and Coif1, which stay available through SetBases.
        //
        // - Daubechies, centered only: plain and centered Daubechies of the
        //   same order are the same filter taps, just phase-shifted; their
        //   post-threshold RMS/sigma ratio agrees to 4-6% on real+injected
        //   data (verified 2026-08-03). DaubC24/32/40 are db12/16/20.
        // - Sym10 (symlet) and Coif2/Coif5 (coiflet), centered -- see
        //   ExtraWaveletFamilies.hpp. Coiflets have vanishing moments for the
        //   scaling function too, not just the wavelet.
        // - Haar.
        //
        const char* const kCandidateBases[] = {
            "Haar", "DaubC4", "Coif2", "DaubC16", "DaubC20", "Sym10",
            "DaubC24", "Coif5", "DaubC32", "DaubC40",
        };

        // Every mother a candidate name may use. A name is a mother alone,
        // the pyramidal transform, or a mother followed by "P" and a depth,
        // the uniform level of that depth of its wavelet-packet tree (see
        // WaveletTransform's packet constructor).
        const std::pair<const char*, enum WaveletTransform::WaveletType> kMothers[] = {
            {"Haar", WaveletTransform::Haar},
            {"DaubC4", WaveletTransform::DaubC4},
            {"DaubC6", WaveletTransform::DaubC6},
            {"DaubC8", WaveletTransform::DaubC8},
            {"DaubC10", WaveletTransform::DaubC10},
            {"DaubC12", WaveletTransform::DaubC12},
            {"DaubC14", WaveletTransform::DaubC14},
            {"DaubC16", WaveletTransform::DaubC16},
            {"DaubC18", WaveletTransform::DaubC18},
            {"DaubC20", WaveletTransform::DaubC20},
            {"Sym4", WaveletTransform::Sym4},
            {"Sym8", WaveletTransform::Sym8},
            {"Coif1", WaveletTransform::Coif1},
            {"Coif2", WaveletTransform::Coif2},
            // The long mothers (five of them are in the default list).
            {"Sym10", WaveletTransform::Sym10},
            {"Sym12", WaveletTransform::Sym12},
            {"Sym16", WaveletTransform::Sym16},
            {"Sym20", WaveletTransform::Sym20},
            {"Coif3", WaveletTransform::Coif3},
            {"Coif4", WaveletTransform::Coif4},
            {"Coif5", WaveletTransform::Coif5},
            {"DaubC24", WaveletTransform::DaubC24},
            {"DaubC32", WaveletTransform::DaubC32},
            {"DaubC40", WaveletTransform::DaubC40},
        };

        WDF2Classify::Basis ParseBasis(const std::string& name, unsigned int window) {
            std::string mother = name;
            unsigned int depth = 0;
            const std::size_t p = name.rfind('P');
            if (p != std::string::npos && p + 1 < name.size() && p > 0 &&
                name.find_first_not_of("0123456789", p + 1) == std::string::npos) {
                mother = name.substr(0, p);
                depth = static_cast<unsigned int>(std::stoul(name.substr(p + 1)));
                if (depth == 0) {
                    throw std::invalid_argument("WDF2Classify: packet depth 0 in basis " + name);
                }
            }
            for (const auto& m : kMothers) {
                if (mother == m.first) {
                    if ((static_cast<std::size_t>(1) << depth) > window) {
                        throw std::invalid_argument("WDF2Classify: packet depth of " + name +
                                                    " exceeds log2 of the window");
                    }
                    return WDF2Classify::Basis{name, m.second, depth};
                }
            }
            throw std::invalid_argument("WDF2Classify: unknown basis " + name +
                                        " (only orthonormal mothers are candidates)");
        }
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
        for (const char* name : kCandidateBases) {
            mSpecs.push_back(ParseBasis(name, mWindow));
        }
        Build();
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
            mWindowing(from.mWindowing),
            mSpecs(from.mSpecs) {
        Build();
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
        mSpecs = from.mSpecs;
        Build();
        return *this;
    }

    // Each candidate owns its transform, built from its specification, so a
    // copy of the classifier rebuilds its candidates rather than sharing them.
    void WDF2Classify::Build() {
        mBases.clear();
        mBaseNames.clear();
        mBases.reserve(mSpecs.size());
        mBaseNames.reserve(mSpecs.size());
        for (const auto& spec : mSpecs) {
            mBases.push_back(std::unique_ptr<WaveletTransform>(
                new WaveletTransform(mWindow, spec.type, spec.depth)));
            mBaseNames.push_back(spec.name);
        }
    }

    void WDF2Classify::SetBases(const std::string& names) {
        std::vector<Basis> specs;
        std::size_t start = 0;
        while (start <= names.size()) {
            std::size_t end = names.find(',', start);
            if (end == std::string::npos) {
                end = names.size();
            }
            std::string name = names.substr(start, end - start);
            const std::size_t first = name.find_first_not_of(" \t");
            const std::size_t last = name.find_last_not_of(" \t");
            name = (first == std::string::npos) ? std::string() : name.substr(first, last - first + 1);
            if (!name.empty()) {
                for (const auto& s : specs) {
                    if (s.name == name) {
                        throw std::invalid_argument("WDF2Classify: basis " + name + " named twice");
                    }
                }
                specs.push_back(ParseBasis(name, mWindow));
                // Under the block rule every band must hold at least one full
                // block of L, the length lambda = 4.505 is calibrated for.
                if (specs.back().depth > 0 && mT == WaveletThreshold::block &&
                    (mWindow >> specs.back().depth) < mWavThres.GetBlockLength()) {
                    throw std::invalid_argument("WDF2Classify: the bands of packet basis " + name +
                                                " are shorter than one block of the block rule");
                }
            }
            start = end + 1;
        }
        if (specs.empty()) {
            throw std::invalid_argument("WDF2Classify: no candidate basis");
        }
        mSpecs = specs;
        Build();
    }

    std::string WDF2Classify::GetBases() const {
        std::string out;
        for (std::size_t i = 0; i < mSpecs.size(); ++i) {
            if (i > 0) {
                out += ",";
            }
            out += mSpecs[i].name;
        }
        return out;
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
        double bestSigma = 0.1;
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
            mWavThres.SetLayout(mBases[b]->GetPacketDepth());
            mWavThres(mBuff, mT);

            double sigmaB = mWavThres.GetSigma();
            int levelB = mWavThres.GetLevel();

            double varB = 0.0;
            for (unsigned int i = 0; i < mWindow; i++) {
                varB += (mBuff(0, i) * mBuff(0, i));
            }
            varB = (sigmaB > 0) ? (sqrt(varB ) / sigmaB) : 0.0;

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

