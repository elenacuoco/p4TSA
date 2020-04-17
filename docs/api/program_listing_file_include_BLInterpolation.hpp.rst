
.. _program_listing_file_include_BLInterpolation.hpp:

Program Listing for File BLInterpolation.hpp
============================================

|exhale_lsh| :ref:`Return to documentation for file <file_include_BLInterpolation.hpp>` (``include/BLInterpolation.hpp``)

.. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS

.. code-block:: none

   
   #ifndef __BLINTERPOLATION_HPP
   #define __BLINTERPOLATION_HPP
   
   #include <queue>
   #include <deque>
   #include <gsl/gsl_sf.h>
   
   #include <AlgoBase.hpp>
   #include <SeqView.hpp>
   
   
   
   
   
   
   
   namespace tsa {
   
       class BLInterpolation : public AlgoBase {
       public:
   
           enum NormalizationType {
               NONormalization,
               DCNormalization
           };
   
           BLInterpolation(unsigned int channels,
                   unsigned int outdata,
                   unsigned int irate,
                   unsigned int orate,
                   unsigned int order,
                   double alpha = 1.0,
                   enum NormalizationType nt = NONormalization
                   );
   
           BLInterpolation(const BLInterpolation& from);
   
           ~BLInterpolation();
   
           BLInterpolation& operator=(const BLInterpolation& from);
   
   
   
           BLInterpolation& Input(SeqViewDouble& indata);
           BLInterpolation& Output(SeqViewDouble& outdata);
   
   
   
   
   
   
   
   
   
           long int GetDataAvailable() {
               return resampled_available();
           }
   
           unsigned int GetData(Dmatrix& outdata);
   
           double GetStartTime();
   
   
   
   
          void SetData(Dmatrix& indata, double scale);
   
   
   
   
   
       protected:
   
       private:
   
   
           void Init();
   
           void NORenormalization();
   
           void DCRenormalization();
   
           double Kaiser(double x);
   
           unsigned int mChannels; 
           unsigned int mOutData; 
           unsigned int mInputRate; 
           unsigned int mOutputRate; 
           unsigned int mOrder; 
           double mAlpha; 
           std::queue<Dvector*> mRepository; 
           std::deque<Dvector*> mBuffer; 
           long int mBufferBase; 
           double mRho; 
           Dvector *mFilter; 
           long int mFilterCenter; 
           Dvector mNormalization;
           NormalizationType mNormalizationType;
   
           bool mFirstData; 
           double mStartTime; 
           double mSampling; 
           void add_back_point();
   
           void del_front_point(unsigned int n);
   
           long int resampled_available();
       };
   
   
   
   
   
   
   
   } // end namespace tsa
   
   #endif // __BLINTERPOLATION_HPP
