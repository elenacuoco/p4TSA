
.. _program_listing_file_include_TFView.hpp:

Program Listing for File TFView.hpp
===================================

|exhale_lsh| :ref:`Return to documentation for file <file_include_TFView.hpp>` (``include/TFView.hpp``)

.. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS

.. code-block:: none

   #include <boost/numeric/ublas/matrix.hpp>
   #include <boost/numeric/ublas/io.hpp>
   
   #ifndef __TFVIEW_HPP
   #define __TFVIEW_HPP
   
   
   #include <BaseView.hpp>
   
   
   namespace tsa {
   
   
       template<class T>
       class TFView : public BaseView {
       public:
           typedef T numericType;
   
   
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
   
   
   
           ~TFView() {
   
           };
   
   
   
   
           void Clear() {
               mData.clear();
           };
   
   
   
   
   
   
           numericType& operator()(unsigned int i, unsigned int j) {
               if (mScale != 1.0) Rescale();
               return mData(i, j);
           };
   
   
   
   
   
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
   
   
       protected:
   
           void Rescale() {
               mData *= mScale;
               mScale = 1.0;
           };
   
           boost::numeric::ublas::matrix<numericType> mData; 
           double mScale; 
           double mStartT; 
           double mSamplingT; 
           double mStartF; 
           double mSamplingF; 
       };
   
   
       typedef class TFView<double> TFViewDouble; 
       typedef class TFView<std::complex<double> > TFViewComplex; 
   
   
   
   } // namespace tsa
   
   #endif // __TFVIEW_HPP
   
