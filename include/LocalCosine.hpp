///
///   Copyright (C) 2026 by Elena Cuoco
///   elena.cuoco@unibo.it
///
///   This program is free software; you can redistribute it and/or modify
///   it under the terms of the GNU General Public License as published by
///   the Free Software Foundation; either version 2 of the License, or
///   (at your option) any later version.
///
/// @file   LocalCosine.hpp
/// @author Elena Cuoco <elena.cuoco@unibo.it>
/// @date   2026
///
/// @brief  Orthonormal local cosine bases (Coifman-Meyer) and cosine packets
///         with the best-basis search of Coifman and Wickerhauser.
///
/// A local cosine basis cuts the window into segments and gives each segment
/// the orthonormal DCT-IV of its samples, after the samples near every
/// segment edge have been folded with a smooth bell. The bell makes the basis
/// functions smooth across the edges (the plain block DCT-IV has jumps there)
/// while the basis stays orthonormal: folding is a rotation of each pair of
/// samples mirrored about an edge, and the DCT-IV is orthonormal.
///
/// Conventions, shared by every class of this file:
///
/// - Segment edges sit between samples: the edge a separates sample a - 1
///   from sample a. The bell of half-width eps (the overlap) acts on the 2 eps
///   samples a - eps .. a + eps - 1. Adjacent edges must not share a sample,
///   so 2 eps <= the shortest segment length; eps = 0 is the rectangular
///   (block DCT-IV) case.
/// - The rising cut-off is r(t) = sin(pi/4 (1 + beta(t))) at the sample
///   centres t = (j + 1/2) / eps, j = -eps .. eps - 1, with r(t)^2 + r(-t)^2 = 1
///   because beta is odd. The Coifman-Meyer bell (the default) uses the
///   iterated sine beta = s(s(s(t))), s(t) = sin(pi t / 2), three times; the
///   sine bell uses beta(t) = t (the MDCT/Princen-Bradley window when
///   eps = M / 2).
/// - Folding at edge a, for t = 0 .. eps - 1, with x+ = x(a + t),
///   x- = x(a - 1 - t), r+ = r((t + 1/2)/eps), r- = r(-(t + 1/2)/eps):
///   y(a + t) = r+ x+ + r- x-, y(a - 1 - t) = r+ x- - r- x+. The DCT-IV is
///   even about the left edge of a segment and odd about the right one, which
///   is what these signs prepare. Unfolding is the transposed rotation.
/// - The DCT-IV of a segment of M samples is orthonormal:
///   c_k = sqrt(2/M) sum_n y_n cos(pi/M (n + 1/2)(k + 1/2)), computed with
///   FFTW's REDFT11 (which omits the sqrt(2/M) and doubles the sum, so its
///   output is scaled by 1/sqrt(2M)). It is its own inverse.
/// - Window edges: @c periodic folds at 0 = N too, wrapping the samples
///   (x(-1) is x(N - 1)), so the basis is a basis of the circle, as the
///   periodized DWT is; @c free does not fold at 0 and N, so the first and the
///   last segment start and end with a sharp cut-off (the classic local
///   cosine basis of an interval). Both are orthonormal.
///
#ifndef __LOCALCOSINE_HPP
#define __LOCALCOSINE_HPP

#include <fftw3.h>
#include <cstddef>
#include <utility>
#include <vector>

namespace tsa {

    ///
    /// The orthonormal DCT-IV of a fixed length M, FFTW_REDFT11 scaled by
    /// 1/sqrt(2M). It is its own inverse.
    ///
    class DCT4 {
    public:
        ///
        /// @param M transform length, positive
        /// @exception std::invalid_argument when M is 0
        /// @exception std::runtime_error when FFTW cannot plan the transform
        ///
        explicit DCT4(unsigned int M);
        /// A copy plans its own transform on its own buffer.
        DCT4(const DCT4& from);
        /// Assignment: the target takes the length and plans its own transform.
        DCT4& operator=(const DCT4& from);
        ~DCT4();

        /// The transform of M values; in and out may be the same array.
        void operator()(const double* in, double* out);

        /// The transform length M.
        unsigned int GetSize() const {
            return mM;
        }

    private:
        void Plan();    ///< allocates the buffer and plans REDFT11 on it
        void Release(); ///< destroys the plan and frees the buffer

        unsigned int mM;  ///< transform length
        double mScale;    ///< 1 / sqrt(2M), the orthonormal scale of REDFT11
        double* mBuf;     ///< FFTW buffer the plan works on
        fftw_plan mPlan;  ///< in-place REDFT11 plan on mBuf
    };

    ///
    /// A local cosine basis of segment length M on a window of N samples.
    ///
    /// Forward writes the coefficients frequency-major: index k (N / M) + j
    /// holds DCT-IV bin k of segment j, so row k is the bin of centre
    /// (k + 1/2) fs / (2M), its N / M coefficients in time order, segment j
    /// covering samples [j M, (j + 1) M). That is the layout of a uniform
    /// wavelet-packet level of depth D = log2 M (2^D rows of N / 2^D), so the
    /// thresholds, the block rule and the trigger geometry of a packet level
    /// apply unchanged. ForwardSegments writes the same coefficients
    /// segment-major (index j M + k).
    ///
    class LocalCosineTransform {
    public:
        /// What happens at the window edges 0 and N.
        enum Edge {
            periodic, ///< bells at the window edges too, wrapping round
            free      ///< no bell at the window edges
        };

        /// The shape of the rising cut-off r of every bell.
        enum Bell {
            coifmanMeyer, ///< r = sin(pi/4 (1 + s(s(s(t))))), s(t) = sin(pi t / 2)
            sine          ///< r = sin(pi/4 (1 + t))
        };

        ///
        /// @param N window length, a multiple of M
        /// @param M segment length, a power of 2
        /// @param overlap bell half-width eps, at most M / 2; negative for M / 2
        /// @param edge what happens at the window edges
        /// @param bell the shape of the cut-off
        /// @exception std::invalid_argument on an inadmissible combination
        ///
        LocalCosineTransform(unsigned int N, unsigned int M, int overlap = -1,
                             enum Edge edge = periodic, enum Bell bell = coifmanMeyer);

        /// In place, N values, frequency-major output.
        void Forward(double* data);
        /// In place, N values, frequency-major input.
        void Inverse(double* data);
        /// In place, N values, segment-major output.
        void ForwardSegments(double* data);
        /// In place, N values, segment-major input.
        void InverseSegments(double* data);

        /// The window length N.
        unsigned int GetLength() const {
            return mN;
        }

        /// The segment length M.
        unsigned int GetSegment() const {
            return mM;
        }

        /// The bell half-width eps.
        unsigned int GetOverlap() const {
            return mEps;
        }

        /// The treatment of the window edges.
        enum Edge GetEdge() const {
            return mEdge;
        }

        /// The shape of the cut-off.
        enum Bell GetBell() const {
            return mBell;
        }

        ///
        /// The cut-off r at the 2 eps sample centres t = (j + 1/2) / eps,
        /// j = -eps .. eps - 1.
        ///
        static std::vector<double> Ramp(unsigned int eps, enum Bell bell);

        ///
        /// Fold (forward true) or unfold (forward false) the 2 eps samples
        /// about edge a of a window of N, in place; ramp is the output of
        /// Ramp(eps, bell). Indices wrap modulo N.
        ///
        static void Fold(double* data, unsigned int N, unsigned int a,
                         const std::vector<double>& ramp, bool forward);

    private:
        unsigned int mN;           ///< window length
        unsigned int mM;           ///< segment length
        unsigned int mEps;         ///< bell half-width
        enum Edge mEdge;           ///< window-edge treatment
        enum Bell mBell;           ///< cut-off shape
        std::vector<double> mRamp; ///< the cut-off at the 2 eps sample centres
        DCT4 mDct;                 ///< DCT-IV of length M
        std::vector<double> mWork; ///< reordering buffer, N values
    };

    ///
    /// Cosine packets: the local cosine bases of every dyadic segmentation of
    /// the window, and the best basis among them (Coifman-Wickerhauser).
    ///
    /// The tree has levels l = 0 .. levels - 1 of segment length
    /// maxSegment / 2^l, down to minSegment; node (l, i) is the segment
    /// [i m, (i + 1) m), m = maxSegment / 2^l, and its two children are its
    /// halves. Every node uses the same bell half-width eps at its edges, so
    /// an edge is folded the same way whatever level it belongs to: the
    /// coefficients of a node depend only on its own two edges, and any
    /// segmentation built from tree nodes (a "segmentation" below: segments
    /// in time order, each a tree node) is an orthonormal basis of the window.
    ///
    /// The coefficients of a segmentation are written segment by segment in
    /// time order, each segment's DCT-IV bins in frequency order.
    ///
    /// The best basis minimises an additive cost, the sum over segments of a
    /// function of each segment's coefficients, by the bottom-up search:
    /// a node is split when the best costs of its two children add up to
    /// strictly less than its own cost (a tie keeps the longer segment).
    ///
    class CosinePackets {
    public:
        /// The additive cost the best basis minimises.
        enum Cost {
            l1,           ///< sum |c|
            entropy,      ///< - sum p ln p, p = c^2 / |x|^2 (Coifman-Wickerhauser)
            wdfUniversal, ///< - sum (c/sigma)^2 over |c| > sqrt(2 ln N) sigma
            wdfBlock      ///< - kept energy / sigma^2 of the block rule along each segment's bins
        };

        ///
        /// @param N window length, a power of 2
        /// @param minSegment shortest segment, a power of 2
        /// @param maxSegment longest segment, a power of 2 from minSegment to
        ///        N; 0 for N
        /// @param overlap bell half-width, at most minSegment / 2; negative for
        ///        minSegment / 2
        /// @param edge what happens at the window edges
        /// @param bell the shape of the cut-off
        /// @exception std::invalid_argument on an inadmissible combination
        ///
        CosinePackets(unsigned int N, unsigned int minSegment, unsigned int maxSegment = 0,
                      int overlap = -1,
                      enum LocalCosineTransform::Edge edge = LocalCosineTransform::periodic,
                      enum LocalCosineTransform::Bell bell = LocalCosineTransform::coifmanMeyer);

        ///
        /// The best basis of the window x (N values) for the cost. For the
        /// WDF costs sigma is the noise scale; zero or negative takes
        /// median |c| / 0.6745 over the coefficients of the finest level, which
        /// every basis of the tree shares for white noise. The block rule uses
        /// L = round(ln N) and lambda = 4.505, as WaveletThreshold; set them
        /// with SetBlock. l1 and entropy ignore sigma.
        ///
        /// @return the cost of the best basis
        ///
        double BestBasis(const double* x, enum Cost cost, double sigma = 0.0);

        /// The chosen segmentation: segment lengths in time order.
        const std::vector<unsigned int>& GetSegmentation() const {
            return mBest;
        }

        /// The coefficients of x on the chosen segmentation (N values).
        const std::vector<double>& GetCoefficients() const {
            return mBestCoeff;
        }

        /// The sigma the last BestBasis used (0 for l1 and entropy).
        double GetSigma() const {
            return mSigma;
        }

        ///
        /// Cost of node (level, index), from the last BestBasis.
        ///
        /// @exception std::out_of_range for a node outside the tree, or
        ///            before the first BestBasis
        ///
        double GetNodeCost(unsigned int level, unsigned int index) const;

        ///
        /// Best cost of the subtree under node (level, index), from the last
        /// BestBasis.
        ///
        /// @exception std::out_of_range as GetNodeCost
        ///
        double GetBestCost(unsigned int level, unsigned int index) const;

        ///
        /// Sum of the node costs of a segmentation, from the last BestBasis.
        ///
        /// @exception std::invalid_argument when the segmentation is not
        ///            made of tree nodes covering the window
        /// @exception std::out_of_range before the first BestBasis
        ///
        double SegmentationCost(const std::vector<unsigned int>& segmentation) const;

        ///
        /// The coefficients of x (N values) on a segmentation, into out (N
        /// values): segment by segment in time order, each segment's DCT-IV
        /// bins in frequency order.
        ///
        /// @exception std::invalid_argument when the segmentation is not
        ///            made of tree nodes covering the window
        ///
        void Analyse(const double* x, const std::vector<unsigned int>& segmentation, double* out);

        ///
        /// The window (N values) from its coefficients on a segmentation, the
        /// exact inverse of Analyse.
        ///
        /// @exception std::invalid_argument as Analyse
        ///
        void Inverse(const double* coeff, const std::vector<unsigned int>& segmentation, double* x);

        /// The additive cost of the M coefficients of one segment, with the
        /// sigma and the window energy of the last BestBasis.
        double SegmentCost(const double* c, unsigned int M, enum Cost cost) const;

        ///
        /// The parameters of the wdfBlock cost: the block length L in
        /// coefficients, 0 (the default) for round(ln N), and the energy
        /// threshold lambda in units of L sigma^2, 4.505 by default.
        ///
        void SetBlock(unsigned int length, double lambda) {
            mBlockLength = length;
            mBlockLambda = lambda;
        }

        /// The block length L in force.
        unsigned int GetBlockLength() const;

        /// The block threshold lambda in force.
        double GetBlockLambda() const {
            return mBlockLambda;
        }

        /// The window length N.
        unsigned int GetLength() const {
            return mN;
        }

        /// The number of levels of the tree, log2(maxSegment / minSegment) + 1.
        unsigned int GetLevels() const {
            return static_cast<unsigned int>(mLengths.size());
        }

        ///
        /// Segment length of a level, maxSegment / 2^level.
        ///
        /// @exception std::out_of_range for a level outside the tree
        ///
        unsigned int GetSegmentLength(unsigned int level) const;

        /// The bell half-width eps shared by every edge.
        unsigned int GetOverlap() const {
            return mEps;
        }

    private:
        /// The level of a segment length; throws std::invalid_argument if none.
        unsigned int LevelOf(unsigned int length) const;
        /// Throws std::invalid_argument unless the segmentation is made of
        /// tree nodes covering the window.
        void Check(const std::vector<unsigned int>& segmentation) const;
        /// Collects the best segmentation under node (level, index).
        void Walk(unsigned int level, unsigned int index);

        unsigned int mN;                          ///< window length
        unsigned int mEps;                        ///< bell half-width
        enum LocalCosineTransform::Edge mEdge;    ///< window-edge treatment
        std::vector<double> mRamp;                ///< the cut-off at the 2 eps sample centres
        std::vector<unsigned int> mLengths;       ///< segment length per level
        std::vector<LocalCosineTransform> mLevel; ///< the uniform segmentation per level
        std::vector<DCT4> mDct;                   ///< DCT-IV per level
        std::vector<std::vector<double> > mCoeff; ///< segment-major coefficients per level
        std::vector<std::vector<double> > mCost;  ///< node cost per level
        std::vector<std::vector<double> > mBestCost; ///< best cost below each node
        std::vector<std::vector<char> > mSplit;      ///< whether each node is split
        std::vector<unsigned int> mBest;             ///< best segmentation
        std::vector<double> mBestCoeff;              ///< coefficients of the best segmentation
        std::vector<double> mWork;                   ///< work buffer, N values
        double mSigma;                               ///< sigma of the last BestBasis
        double mNorm2;                               ///< energy of the last window
        unsigned int mBlockLength;                   ///< block length of wdfBlock, 0 for round(ln N)
        double mBlockLambda;                         ///< lambda of wdfBlock
        bool mDone;                                  ///< whether BestBasis has run
    };

} // namespace tsa

#endif // __LOCALCOSINE_HPP
