
.. _program_listing_file_include_WDF2Classify.hpp:

Program Listing for File WDF2Classify.hpp
=========================================

|exhale_lsh| :ref:`Return to documentation for file <file_include_WDF2Classify.hpp>` (``include/WDF2Classify.hpp``)

.. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS

.. code-block:: none

   #ifndef __WDF2CLASSIFY_HPP
   #define __WDF2CLASSIFY_HPP
   
   
   
   #include <string>
   
   
   
   
   
   
   #include <AlgoBase.hpp>
   #include <SeqView.hpp>
   #include <FifoBuffer.hpp>
   #include <AlgoExceptions.hpp>
   
   #include <EventFullFeatured.hpp>
   #include <WaveletTransform.hpp>
   #include <WaveletThreshold.hpp>
   #include <DCT.hpp>
   #include <Cs2HammingWindow.hpp>
   #include <BaseView.hpp>
   #include <math.h>
   
   
   
   
   
   using namespace boost::numeric::ublas;
   namespace tsa {
   
   
       class WDF2Classify : public AlgoBase {
       public:
   
           WDF2Classify(unsigned int window, unsigned int overlap, double thresh, double sigma,
                        unsigned int ncoeff, enum WaveletThreshold::WaveletThresholding WTh = WaveletThreshold::cuoco);
   
           ~WDF2Classify();
   
   
   
           void operator<<(SeqViewDouble& Data) {
               Dmatrix* in = Data.GetData();
   
               if (in->size1() != 1) {
                   LogSevere("TransientDetection: multichannels not implemented resize");
                   throw bad_matrix_size("Wrong Matrix size");
               }
   
               SetData(*in, Data.GetScale());
               mStartTime = Data.GetStart();
               mSampling = Data.GetSampling();
               //mStartTime -= mSampling * static_cast<double> (WDF2Classify::GetDataNeeded());
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
           double mSigma4;
           double mSigmaC8;
           double mSigma10;
           double mSigma12;
           double mSigmaC16;
           double mSigma20;
           double mSigmaC20;
           double mSigmaBsC206;
           double mSigmaBsC103;
           double mSigmaBsC309;
           double mSigmaDCT;
           FifoBuffer mBuffer;
   
           double mStartTime;
           double mSampling;
           Dmatrix mBuff;
           EventFullFeatured mEvFF;
   
           enum WaveletTransform::WaveletType mWtH;
           WaveletTransform mWTH;
           enum WaveletTransform::WaveletType mWt4;
           WaveletTransform mWT4;
           enum WaveletTransform::WaveletType mWtC8;
           WaveletTransform mWTC8;
           enum WaveletTransform::WaveletType mWt10;
           WaveletTransform mWT10;
           enum WaveletTransform::WaveletType mWt12;
           WaveletTransform mWT12;
           enum WaveletTransform::WaveletType mWtC16;
           WaveletTransform mWTC16;
           enum WaveletTransform::WaveletType mWt20;
           WaveletTransform mWT20;
           enum WaveletTransform::WaveletType mWtC20;
           WaveletTransform mWTC20;
           enum WaveletTransform::WaveletType mWtBsC206;
           WaveletTransform mWTBsC206;
           enum WaveletTransform::WaveletType mWtBsC103;
           WaveletTransform mWTBsC103;
           enum WaveletTransform::WaveletType mWtBsC309;
           WaveletTransform mWTBsC309;
           enum WaveletThreshold::WaveletThresholding mT;
           WaveletThreshold mWavThres;
           DCT mDct;
           Dmatrix mBuffDct;
           Cs2HammingWindow mWindowing;
   
       };
   
   
   
   
   
   
   
   
   }
   //end namespace
   
   #endif //  __WAVTRANSIENTDETECTION_HPP
