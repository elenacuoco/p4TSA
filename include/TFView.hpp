#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>

#ifndef __TFVIEW_HPP
#define __TFVIEW_HPP
///
/// @file   SeqView.hpp
/// @author Antonio Eleuteri <antonio.eleuteri@na.infn.it>
/// @date   Wed Nov 24 17:05:33 2004
/// 
/// @brief  Define Sequence view


#include <BaseView.hpp>


namespace tsa {

    ///
    /// @brief Time view: container for time series.
    ///

    template<class T>
    class TFView : public BaseView {
    public:
        typedef T numericType;

        /// Constructor.
        ///
        /// @param FrequencySize the number of data on frequency axis
        /// @param TimeSize the number of data on time axis
        /// @param aStartT start time
        /// @param aSamplingT time step
        /// @param aStartF start frequency
        /// @param aSamplingF frequency step
        ///
        ///  

        TFView(unsigned int FrequencySize,
                unsigned int TimeSize,
                double aStartT = 0.0,
                double aSamplingT = 1.0,
                double aStartF = 0.0,
                double aSamplingF = 1.0
                )
        :
        mData(FrequencySize, TimeSize),
        mScale(1.0),
        mStartT(aStartT),
        mSamplingT(aSamplingT),
        mStartF(aStartF),
        mSamplingF(aSamplingF) {
            Clear();
        };


        /// 
        ///
        /// Destructor
        /// 

        ~TFView() {

        };

        ///
        /// @name Operations
        ///
        //@{

        /// Clear the data in the view, which are 
        /// all initialized to zero.
        ///

        void Clear() {
            mData.clear();
        };


        //@}

        ///
        /// @name Data access
        ///
        //@{

        /// Get a value in a given channel at a given index. 
        ///
        /// @param i index on the time axis
        /// @param j index on the frequency axis
        ///
        /// @return the data value
        ///

        numericType& operator()(unsigned int i, unsigned int j) {
            if (mScale != 1.0) Rescale();
            return mData(i, j);
        };



        ///
        /// @name Getters
        ///
        //@{

        boost::numeric::ublas::matrix<numericType> *GetData() {
            return &mData;
        }

        unsigned int GetFrequencySize() {
            return mData.size1();
        };

        unsigned int GetTimeSize() {
            return mData.size2();
        };

        double GetStartT() {
            return mStartT;
        };

        double GetStartF() {
            return mStartF;
        };

        double GetFrequency(unsigned int k) {
            return mStartF + mSamplingF*k;
        };

        double GetTime(unsigned int k) {
            return mStartT + mSamplingT*k;
        };

        double GetEndF() {
            return mStartF + mSamplingF * mData.size1();
        };

        double GetEndT() {
            return mStartT + mSamplingT * mData.size2();
        };

        double GetFrequencySlice() {
            return mSamplingF * mData.size1();
        };

        double GetTimeSlice() {
            return mSamplingT * mData.size2();
        };

        double GetSamplingF() {
            return mSamplingF;
        };

        double GetSamplingT() {
            return mSamplingT;
        };


        //@}

        ///
        /// @name Setters
        ///
        //@{

        void SetStartT(double v) {
            mStartT = v;
        };

        void SetStartF(double v) {
            mStartF = v;
        };

        void SetSamplingT(double v) {
            mSamplingT = v;
        };

        void SetSamplingF(double v) {
            mSamplingF = v;
        };

        void SetScale(double aScale) {
            mScale = aScale;
        }

        //@}

    protected:
        /// Rescale the data, setting the auxiliary scale to one.
        ///
        ///

        void Rescale() {
            mData *= mScale;
            mScale = 1.0;
        };

        boost::numeric::ublas::matrix<numericType> mData; ///< The data array
        double mScale; ///< The auxiliary scale
        double mStartT; ///< The start time
        double mSamplingT; ///< The sampling in time
        double mStartF; ///< The start frequency
        double mSamplingF; ///< The sampling in frequency
    };


    typedef class TFView<double> TFViewDouble; ///< Double precision histogram
    typedef class TFView<std::complex<double> > TFViewComplex; ///< Complex histogram



} // namespace tsa

#endif // __TFVIEW_HPP

