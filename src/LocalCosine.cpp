//
// C++ Implementation: LocalCosine.cpp
//
// Description: orthonormal local cosine bases and cosine packets, see
// include/LocalCosine.hpp for the conventions.
//
// Author: Elena Cuoco <elena.cuoco@unibo.it>, (C) 2026
//
// Copyright: See COPYING file that comes with this distribution
//

#include <LocalCosine.hpp>

#include <algorithm>
#include <cmath>
#include <stdexcept>
#include <string>

namespace tsa {

    namespace {
        bool PowerOfTwo(unsigned int n) {
            return n > 0 && (n & (n - 1)) == 0;
        }

        // M_PI is not guaranteed by <cmath>.
        const double kPi = 3.14159265358979323846264338327950288;
    }

    // ------------------------------------------------------------ DCT4

    DCT4::DCT4(unsigned int M)
    :
    mM(M),
    mScale(1.0 / std::sqrt(2.0 * M)),
    mBuf(0),
    mPlan(0) {
        if (M == 0) {
            throw std::invalid_argument("DCT4: the length must be positive");
        }
        Plan();
    }

    // FFTW's planner writes into the array it plans on, so the plan is made on
    // the instance's own buffer, before any data are there. FFTW_ESTIMATE
    // makes no measurement, so the plan, and the result, are deterministic.
    void DCT4::Plan() {
        mBuf = static_cast<double*>(fftw_malloc(sizeof(double) * mM));
        if (!mBuf) {
            throw std::bad_alloc();
        }
        mPlan = fftw_plan_r2r_1d(static_cast<int>(mM), mBuf, mBuf, FFTW_REDFT11, FFTW_ESTIMATE);
        if (!mPlan) {
            fftw_free(mBuf);
            mBuf = 0;
            throw std::runtime_error("DCT4: FFTW could not plan the DCT-IV");
        }
    }

    void DCT4::Release() {
        if (mPlan) {
            fftw_destroy_plan(mPlan);
        }
        if (mBuf) {
            fftw_free(mBuf);
        }
        mPlan = 0;
        mBuf = 0;
    }

    DCT4::DCT4(const DCT4& from)
    :
    mM(from.mM),
    mScale(from.mScale),
    mBuf(0),
    mPlan(0) {
        Plan();
    }

    DCT4& DCT4::operator=(const DCT4& from) {
        if (this != &from) {
            DCT4 copy(from);
            std::swap(mM, copy.mM);
            std::swap(mScale, copy.mScale);
            std::swap(mBuf, copy.mBuf);
            std::swap(mPlan, copy.mPlan);
        }
        return *this;
    }

    DCT4::~DCT4() {
        Release();
    }

    void DCT4::operator()(const double* in, double* out) {
        for (unsigned int i = 0; i < mM; i++) {
            mBuf[i] = in[i];
        }
        fftw_execute(mPlan);
        for (unsigned int i = 0; i < mM; i++) {
            out[i] = mScale * mBuf[i];
        }
    }

    // ------------------------------------------------------------ local cosine

    std::vector<double> LocalCosineTransform::Ramp(unsigned int eps, enum Bell bell) {
        std::vector<double> r(2 * eps);
        for (unsigned int j = 0; j < 2 * eps; j++) {
            double beta = (static_cast<double>(j) - eps + 0.5) / eps;
            if (bell == coifmanMeyer) {
                for (int k = 0; k < 3; k++) {
                    beta = std::sin(0.5 * kPi * beta);
                }
            }
            r[j] = std::sin(0.25 * kPi * (1.0 + beta));
        }
        return r;
    }

    void LocalCosineTransform::Fold(double* data, unsigned int N, unsigned int a,
                                    const std::vector<double>& ramp, bool forward) {
        const unsigned int eps = static_cast<unsigned int>(ramp.size() / 2);
        for (unsigned int t = 0; t < eps; t++) {
            const unsigned int right = (a + t) % N;
            const unsigned int left = (a + N - 1 - t) % N;
            const double rp = ramp[eps + t];
            const double rm = ramp[eps - 1 - t];
            const double xr = data[right];
            const double xl = data[left];
            if (forward) {
                data[right] = rp * xr + rm * xl;
                data[left] = rp * xl - rm * xr;
            } else {
                data[right] = rp * xr - rm * xl;
                data[left] = rm * xr + rp * xl;
            }
        }
    }

    LocalCosineTransform::LocalCosineTransform(unsigned int N, unsigned int M, int overlap,
                                               enum Edge edge, enum Bell bell)
    :
    mN(N),
    mM(M),
    mEps(overlap < 0 ? M / 2 : static_cast<unsigned int>(overlap)),
    mEdge(edge),
    mBell(bell),
    mDct(M > 0 ? M : 1),
    mWork(N, 0.0) {
        if (!PowerOfTwo(M)) {
            throw std::invalid_argument("LocalCosineTransform: the segment length must be a power of 2");
        }
        if (N < M || N % M != 0) {
            throw std::invalid_argument("LocalCosineTransform: the window length must be a multiple of the segment length");
        }
        if (2 * static_cast<unsigned long>(mEps) > M) {
            throw std::invalid_argument("LocalCosineTransform: the overlap exceeds half the segment length");
        }
        mRamp = Ramp(mEps, bell);
    }

    void LocalCosineTransform::ForwardSegments(double* data) {
        if (mEps > 0) {
            for (unsigned int a = 0; a < mN; a += mM) {
                if (a == 0 && mEdge == free) {
                    continue;
                }
                Fold(data, mN, a, mRamp, true);
            }
        }
        for (unsigned int a = 0; a < mN; a += mM) {
            mDct(data + a, data + a);
        }
    }

    void LocalCosineTransform::InverseSegments(double* data) {
        for (unsigned int a = 0; a < mN; a += mM) {
            mDct(data + a, data + a);
        }
        if (mEps > 0) {
            for (unsigned int a = 0; a < mN; a += mM) {
                if (a == 0 && mEdge == free) {
                    continue;
                }
                Fold(data, mN, a, mRamp, false);
            }
        }
    }

    // Segment-major j M + k to frequency-major k (N / M) + j and back.
    void LocalCosineTransform::Forward(double* data) {
        ForwardSegments(data);
        const unsigned int segments = mN / mM;
        for (unsigned int j = 0; j < segments; j++) {
            for (unsigned int k = 0; k < mM; k++) {
                mWork[k * segments + j] = data[j * mM + k];
            }
        }
        std::copy(mWork.begin(), mWork.end(), data);
    }

    void LocalCosineTransform::Inverse(double* data) {
        const unsigned int segments = mN / mM;
        for (unsigned int j = 0; j < segments; j++) {
            for (unsigned int k = 0; k < mM; k++) {
                mWork[j * mM + k] = data[k * segments + j];
            }
        }
        std::copy(mWork.begin(), mWork.end(), data);
        InverseSegments(data);
    }

    // ------------------------------------------------------------ cosine packets

    CosinePackets::CosinePackets(unsigned int N, unsigned int minSegment, unsigned int maxSegment,
                                 int overlap, enum LocalCosineTransform::Edge edge,
                                 enum LocalCosineTransform::Bell bell)
    :
    mN(N),
    mEps(overlap < 0 ? minSegment / 2 : static_cast<unsigned int>(overlap)),
    mEdge(edge),
    mWork(N, 0.0),
    mSigma(0.0),
    mNorm2(0.0),
    mBlockLength(0),
    mBlockLambda(4.505),
    mDone(false) {
        if (maxSegment == 0) {
            maxSegment = N;
        }
        if (!PowerOfTwo(N) || !PowerOfTwo(minSegment) || !PowerOfTwo(maxSegment)) {
            throw std::invalid_argument("CosinePackets: the window and segment lengths must be powers of 2");
        }
        if (minSegment > maxSegment || maxSegment > N) {
            throw std::invalid_argument("CosinePackets: need minSegment <= maxSegment <= N");
        }
        if (2 * static_cast<unsigned long>(mEps) > minSegment) {
            throw std::invalid_argument("CosinePackets: the overlap exceeds half the shortest segment");
        }
        mRamp = LocalCosineTransform::Ramp(mEps, bell);
        for (unsigned int m = maxSegment; m >= minSegment; m /= 2) {
            mLengths.push_back(m);
            mLevel.push_back(LocalCosineTransform(N, m, static_cast<int>(mEps), edge, bell));
            mDct.push_back(DCT4(m));
            mCoeff.push_back(std::vector<double>(N, 0.0));
            mCost.push_back(std::vector<double>(N / m, 0.0));
            mBestCost.push_back(std::vector<double>(N / m, 0.0));
            mSplit.push_back(std::vector<char>(N / m, 0));
            if (m == 1) {
                break;
            }
        }
    }

    unsigned int CosinePackets::GetSegmentLength(unsigned int level) const {
        if (level >= mLengths.size()) {
            throw std::out_of_range("CosinePackets: no such level");
        }
        return mLengths[level];
    }

    unsigned int CosinePackets::GetBlockLength() const {
        if (mBlockLength > 0) {
            return mBlockLength;
        }
        const unsigned int L = static_cast<unsigned int>(std::floor(std::log(static_cast<double>(mN)) + 0.5));
        return L > 0 ? L : 1;
    }

    double CosinePackets::SegmentCost(const double* c, unsigned int M, enum Cost cost) const {
        double s = 0.0;
        switch (cost) {
            case l1:
                for (unsigned int k = 0; k < M; k++) {
                    s += std::fabs(c[k]);
                }
                return s;
            case entropy:
                if (mNorm2 <= 0.0) {
                    return 0.0;
                }
                for (unsigned int k = 0; k < M; k++) {
                    const double p = c[k] * c[k] / mNorm2;
                    if (p > 0.0) {
                        s -= p * std::log(p);
                    }
                }
                return s;
            case wdfUniversal: {
                if (mSigma <= 0.0) {
                    return 0.0;
                }
                const double T = std::sqrt(2.0 * std::log(static_cast<double>(mN)));
                for (unsigned int k = 0; k < M; k++) {
                    const double a = std::fabs(c[k]) / mSigma;
                    if (a > T) {
                        s -= a * a;
                    }
                }
                return s;
            }
            case wdfBlock: {
                if (mSigma <= 0.0) {
                    return 0.0;
                }
                const unsigned int L = GetBlockLength();
                for (unsigned int b = 0; b < M; b += L) {
                    const unsigned int e = std::min(b + L, M);
                    double energy = 0.0;
                    for (unsigned int k = b; k < e; k++) {
                        energy += (c[k] / mSigma) * (c[k] / mSigma);
                    }
                    if (energy > mBlockLambda * (e - b)) {
                        s -= energy;
                    }
                }
                return s;
            }
        }
        throw std::invalid_argument("CosinePackets: unknown cost");
    }

    double CosinePackets::BestBasis(const double* x, enum Cost cost, double sigma) {
        const std::size_t levels = mLengths.size();
        mNorm2 = 0.0;
        for (unsigned int i = 0; i < mN; i++) {
            mNorm2 += x[i] * x[i];
        }
        for (std::size_t l = 0; l < levels; l++) {
            std::copy(x, x + mN, mCoeff[l].begin());
            mLevel[l].ForwardSegments(mCoeff[l].data());
        }
        mSigma = 0.0;
        if (cost == wdfUniversal || cost == wdfBlock) {
            if (sigma > 0.0) {
                mSigma = sigma;
            } else {
                std::vector<double> a(mN);
                for (unsigned int i = 0; i < mN; i++) {
                    a[i] = std::fabs(mCoeff[levels - 1][i]);
                }
                std::sort(a.begin(), a.end());
                const double median = (mN % 2) ? a[mN / 2] : 0.5 * (a[mN / 2 - 1] + a[mN / 2]);
                mSigma = median / 0.6745;
            }
        }
        for (std::size_t l = 0; l < levels; l++) {
            const unsigned int m = mLengths[l];
            for (unsigned int i = 0; i < mN / m; i++) {
                mCost[l][i] = SegmentCost(mCoeff[l].data() + i * m, m, cost);
            }
        }
        // Bottom-up: a leaf's best is its cost; a node splits only when its
        // children's best costs add up to strictly less than its own.
        mBestCost[levels - 1] = mCost[levels - 1];
        std::fill(mSplit[levels - 1].begin(), mSplit[levels - 1].end(), 0);
        for (std::size_t l = levels - 1; l-- > 0;) {
            for (std::size_t i = 0; i < mCost[l].size(); i++) {
                const double children = mBestCost[l + 1][2 * i] + mBestCost[l + 1][2 * i + 1];
                mSplit[l][i] = children < mCost[l][i];
                mBestCost[l][i] = mSplit[l][i] ? children : mCost[l][i];
            }
        }
        mBest.clear();
        mBestCoeff.clear();
        double total = 0.0;
        for (unsigned int i = 0; i < mCost[0].size(); i++) {
            Walk(0, i);
            total += mBestCost[0][i];
        }
        mDone = true;
        return total;
    }

    void CosinePackets::Walk(unsigned int level, unsigned int index) {
        if (level + 1 < mLengths.size() && mSplit[level][index]) {
            Walk(level + 1, 2 * index);
            Walk(level + 1, 2 * index + 1);
            return;
        }
        const unsigned int m = mLengths[level];
        mBest.push_back(m);
        const double* c = mCoeff[level].data() + index * m;
        mBestCoeff.insert(mBestCoeff.end(), c, c + m);
    }

    double CosinePackets::GetNodeCost(unsigned int level, unsigned int index) const {
        if (!mDone || level >= mCost.size() || index >= mCost[level].size()) {
            throw std::out_of_range("CosinePackets: no such node, or no best basis yet");
        }
        return mCost[level][index];
    }

    double CosinePackets::GetBestCost(unsigned int level, unsigned int index) const {
        if (!mDone || level >= mCost.size() || index >= mCost[level].size()) {
            throw std::out_of_range("CosinePackets: no such node, or no best basis yet");
        }
        return mBestCost[level][index];
    }

    unsigned int CosinePackets::LevelOf(unsigned int length) const {
        for (unsigned int l = 0; l < mLengths.size(); l++) {
            if (mLengths[l] == length) {
                return l;
            }
        }
        throw std::invalid_argument("CosinePackets: segment length " + std::to_string(length) +
                                    " is not a level of the tree");
    }

    void CosinePackets::Check(const std::vector<unsigned int>& segmentation) const {
        unsigned long a = 0;
        for (unsigned int m : segmentation) {
            LevelOf(m);
            if (a % m != 0) {
                throw std::invalid_argument("CosinePackets: a segment does not start on a multiple of its length");
            }
            a += m;
        }
        if (a != mN) {
            throw std::invalid_argument("CosinePackets: the segmentation does not cover the window");
        }
    }

    double CosinePackets::SegmentationCost(const std::vector<unsigned int>& segmentation) const {
        Check(segmentation);
        if (!mDone) {
            throw std::out_of_range("CosinePackets: no best basis yet");
        }
        double s = 0.0;
        unsigned int a = 0;
        for (unsigned int m : segmentation) {
            s += mCost[LevelOf(m)][a / m];
            a += m;
        }
        return s;
    }

    // Fold at every edge of the segmentation, then a DCT-IV per segment. The
    // folds of distinct edges touch distinct samples (2 eps <= every length).
    void CosinePackets::Analyse(const double* x, const std::vector<unsigned int>& segmentation, double* out) {
        Check(segmentation);
        std::copy(x, x + mN, out);
        unsigned int a = 0;
        if (mEps > 0) {
            for (unsigned int m : segmentation) {
                if (!(a == 0 && mEdge == LocalCosineTransform::free)) {
                    LocalCosineTransform::Fold(out, mN, a, mRamp, true);
                }
                a += m;
            }
        }
        a = 0;
        for (unsigned int m : segmentation) {
            mDct[LevelOf(m)](out + a, out + a);
            a += m;
        }
    }

    void CosinePackets::Inverse(const double* coeff, const std::vector<unsigned int>& segmentation, double* x) {
        Check(segmentation);
        std::copy(coeff, coeff + mN, x);
        unsigned int a = 0;
        for (unsigned int m : segmentation) {
            mDct[LevelOf(m)](x + a, x + a);
            a += m;
        }
        a = 0;
        if (mEps > 0) {
            for (unsigned int m : segmentation) {
                if (!(a == 0 && mEdge == LocalCosineTransform::free)) {
                    LocalCosineTransform::Fold(x, mN, a, mRamp, false);
                }
                a += m;
            }
        }
    }

} // namespace tsa
