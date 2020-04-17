
.. _program_listing_file_include_WaveletThreshold.hpp:

Program Listing for File WaveletThreshold.hpp
=============================================

|exhale_lsh| :ref:`Return to documentation for file <file_include_WaveletThreshold.hpp>` (``include/WaveletThreshold.hpp``)

.. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS

.. code-block:: none

   #ifndef __WAVELETTHRESHOLD_HPP
   #define __WAVELETTHRESHOLD_HPP
   
   
   
   
   
   
   
   
   #include <AlgoBase.hpp>
   #include <SeqView.hpp>
   
   
   #include <gsl/gsl_sort.h>
   #include <gsl/gsl_statistics.h>
   
   
   
   
   
   
   namespace tsa {
   
   
       class WaveletThreshold {
       public:
   
           enum WaveletThresholding {
               highest,
               dohonojohnston,
               cuoco
           };
   
           enum ThresholdingMode {
               hard,
               soft
           };
           WaveletThreshold(unsigned int N, unsigned int ncoeff = 0, double sigma = 1.0);
           ~WaveletThreshold();
   
   
           void operator()(SeqViewDouble& WT, enum WaveletThresholding t, enum ThresholdingMode m = soft);
           void operator()(Dmatrix& WT, enum WaveletThresholding t, enum ThresholdingMode m = soft);
   
   
   
           double GetSigma() {
               return mSigma;
           }
   
           double GetLevel() {
               return mlevel;
           }
   
           double GetCm() {
               return mC;
           }
   
   
   
   
           void SetSigma(double sigma) {
               mSigma = sigma;
           }
   
   
       protected:
   
       private:
           double * mAbsCoeff;
           size_t * mP;
           size_t * mPAC;
           double * mOrd;
           unsigned int mN;
           double mMedian;
           double mThresh;
           unsigned int mNcoeff;
           double mSigma;
           int mlevel;
           double mC;
   
   
       };
   
   
   
   
   
   
   
   
   } //end namespace
   
   #endif // ___WAVELETTHRESHOLD_HPP
