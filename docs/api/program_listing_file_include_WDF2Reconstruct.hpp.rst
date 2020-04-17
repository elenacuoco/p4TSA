
.. _program_listing_file_include_WDF2Reconstruct.hpp:

Program Listing for File WDF2Reconstruct.hpp
============================================

|exhale_lsh| :ref:`Return to documentation for file <file_include_WDF2Reconstruct.hpp>` (``include/WDF2Reconstruct.hpp``)

.. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS

.. code-block:: none

   #ifndef __WDF2RECONSTRUCT_HPP
   #define __WDF2RECONSTRUCT_HPP
   
   
   
   #include <string>
   
   
   
   
   
   
   #include <AlgoBase.hpp>
   #include <SeqView.hpp>
   #include <FifoBuffer.hpp>
   #include <AlgoExceptions.hpp>
   
   #include <EventFullFeatured.hpp>
   #include <WaveletTransform.hpp>
   #include <WaveletThreshold.hpp>
   #include <Cs2HammingWindow.hpp>
   #include <BaseView.hpp>
   #include <math.h>
   
   
   
   
   
   using namespace boost::numeric::ublas;
   namespace tsa {
   
   
       class WDF2Reconstruct : public AlgoBase {
       public:
   
           WDF2Reconstruct(unsigned int window, unsigned int overlap, double thresh, double sigma,
                        unsigned int ncoeff, enum WaveletThreshold::WaveletThresholding WTh = WaveletThreshold::cuoco);
   
           ~WDF2Reconstruct();
   
   
   
           void operator<<(SeqViewDouble& Data) {
               Dmatrix* in = Data.GetData();
   
               if (in->size1() != 1) {
                   LogSevere("TransientDetection: multichannels not implemented resize");
                   throw bad_matrix_size("Wrong Matrix size");
               }
   
               SetData(*in, Data.GetScale());
               mStartTime = Data.GetStart();
               mSampling = Data.GetSampling();
               //mStartTime -= mSampling * static_cast<double> (WDF2Reconstruct::GetDataNeeded());
           }
   
           void operator()(SeqViewDouble& Data, double sigma) {
               Dmatrix* in = Data.GetData();
   
               if (in->size1() != 1) {
                   LogSevere("TransientDetection: multichannels not implemented resize");
                   throw bad_matrix_size("Wrong Matrix size");
               }
   
               SetData(*in, Data.GetScale());
               mStartTime = Data.GetStart();
               mSampling = Data.GetSampling();
               mWavThres.SetSigma(sigma);
   
           }
   
   
   
   
   
           int operator()(EventFullFeatured& Ev) {
               double abov;
               Dvector Cmax;
               int level;
               std::string Wave;
               unsigned int res = GetDataVector(abov, Cmax, level, Wave);
   
               if (res == 1) {
   
                   mEvFF.mlevel = static_cast<double> (level);
   
                   for (unsigned int i = 0; i < mNCoeff; i++) {
                       mEvFF.mCoeff[i] = Cmax[i];
                   }
                   mEvFF.mTime = mStartTime;
                   mEvFF.mSNR = abov;
                   mEvFF.mWave = Wave;
                   Ev = mEvFF;
               }
   
               mStartTime += mSampling * static_cast<double> (mStep);
               return res;
           }
   
   
   
   
   
           unsigned int GetDataVector(double& abov, Dvector& Cmax, int& levelR, std::string& Wave);
   
           void GetEvent(EventFullFeatured &Ev) {
   
               Ev.mTime = mEvFF.mTime;
               Ev.mSNR = mEvFF.mSNR;
               Ev.mWave = mEvFF.mWave;
               Ev.mCoeff = mEvFF.mCoeff;
           }
   
           int GetDataNeeded();
   
   
   
   
   
           void SetData(Dmatrix& Data, double scale);
   
   
   
   
   
       protected:
   
       private:
           unsigned int mWindow;
           unsigned int mOverlap;
           unsigned int mStep;
           unsigned int mNCoeff;
           double mThresh;
           double mSigma;
           double mSigmaH;
           double mSigmaBsC309;
           FifoBuffer mBuffer;
   
           double mStartTime;
           double mSampling;
           Dmatrix mBuff;
           EventFullFeatured mEvFF;
   
           enum WaveletTransform::WaveletType mWtH;
           WaveletTransform mWTH;
           enum WaveletTransform::WaveletType mWtBsC309;
           WaveletTransform mWTBsC309;
           enum WaveletThreshold::WaveletThresholding mT;
           WaveletThreshold mWavThres;
           Cs2HammingWindow mWindowing;
   
       };
   
   
   
   
   
   
   
   
   }
   //end namespace
   
   #endif //  __WAVTRANSIENTDETECTION_HPP
