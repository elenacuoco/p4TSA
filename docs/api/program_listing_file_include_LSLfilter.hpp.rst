
.. _program_listing_file_include_LSLfilter.hpp:

Program Listing for File LSLfilter.hpp
======================================

|exhale_lsh| :ref:`Return to documentation for file <file_include_LSLfilter.hpp>` (``include/LSLfilter.hpp``)

.. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS

.. code-block:: none

   
   #ifndef __LSLFILTER_HPP
   #define __LSLFILTER_HPP
   
   
   
   
   
   #include <AlgoBase.hpp>
   #include <SeqView.hpp>
   #include <LatticeView.hpp>
   #include <FifoBuffer.hpp>
   #include <LSLLearning.hpp>
   
   
   
   
   
   
   
   using namespace boost::numeric::ublas;
   
   namespace tsa {
   
       class LSLfilter : public AlgoBase {
       public:
   
           LSLfilter(LSLLearning& LSL, double lambda = 1.0, unsigned int size = 1, bool Norm = false);
   
   
   
           ~LSLfilter();
   
           void Load(const char *filename, const char *fmt = "txt") {
               eternity::xml_archive fa;
               fa.open(filename, eternity::archive::load);
               xml_serialize(fa, "");
               fa.close();
           }
   
           void Save(const char *filename, const char *fmt = "txt") {
               eternity::xml_archive fa;
               fa.open(filename, eternity::archive::store);
               xml_serialize(fa, "");
               fa.close();
           }
   
           void xml_serialize(eternity::xml_archive& xml, const char *p) {
               char buffer[1024];
   
               snprintf(buffer, 1024, "%s.mBuffer", p);
               mBuffer.xml_serialize(xml, buffer);
   
               if (xml.is_loading()) {
   
                   snprintf(buffer, 1024, "%s.mWinSize", p);
                   xml.read(buffer, mWinSize, 0);
                   snprintf(buffer, 1024, "%s.mOrder", p);
                   xml.read(buffer, mOrder, 0);
                   snprintf(buffer, 1024, "%s.mLambda", p);
                   xml.read(buffer, mLambda, 0);
                   snprintf(buffer, 1024, "%s.mSigma", p);
                   DVECTOR_XML_SERIALIZE(mSigma, xml, buffer);
                   snprintf(buffer, 1024, "%s.mNorm", p);
                   BOOL_XML_SERIALIZE(mNorm, xml, buffer);
                   snprintf(buffer, 1024, "%s.mSigma0", p);
                   xml.read(buffer, mSigma0, 0);
                   snprintf(buffer, 1024, "%s.mStartTime", p);
                   xml.read(buffer, mStartTime, 0);
                   snprintf(buffer, 1024, "%s.mSampling", p);
                   xml.read(buffer, mSampling, 0);
                   snprintf(buffer, 1024, "%s.mFirstCall", p);
                   BOOL_XML_SERIALIZE(mFirstCall, xml, buffer);
                   snprintf(buffer, 1024, "%s.mEF", p);
                   DMATRIX_XML_SERIALIZE(mEF, xml, buffer);
                   snprintf(buffer, 1024, "%s.mEB", p);
                   DMATRIX_XML_SERIALIZE(mEB, xml, buffer);
                   snprintf(buffer, 1024, "%s.mEpf", p);
                   DMATRIX_XML_SERIALIZE(mEpf, xml, buffer);
                   snprintf(buffer, 1024, "%s.mEpb", p);
                   DMATRIX_XML_SERIALIZE(mEpb, xml, buffer);
                   snprintf(buffer, 1024, "%s.mKf", p);
                   DVECTOR_XML_SERIALIZE(mKf, xml, buffer);
                   snprintf(buffer, 1024, "%s.mKb", p);
                   DVECTOR_XML_SERIALIZE(mKb, xml, buffer);
                   snprintf(buffer, 1024, "%s.mNG", p);
                   DVECTOR_XML_SERIALIZE(mG, xml, buffer);
                   snprintf(buffer, 1024, "%s.mF0", p);
                   xml.read(buffer, mF0, 0);
   
               } else {
   
                   snprintf(buffer, 1024, "%s.mWinSize", p);
                   xml.write(buffer, mWinSize);
                   snprintf(buffer, 1024, "%s.mOrder", p);
                   xml.write(buffer, mOrder);
                   snprintf(buffer, 1024, "%s.mLambda", p);
                   xml.write(buffer, mLambda);
                   snprintf(buffer, 1024, "%s.mSigma", p);
                   DVECTOR_XML_SERIALIZE(mSigma, xml, buffer);
                   snprintf(buffer, 1024, "%s.mNorm", p);
                   BOOL_XML_SERIALIZE(mNorm, xml, buffer);
                   snprintf(buffer, 1024, "%s.mSigma0", p);
                   xml.write(buffer, mSigma0);
                   snprintf(buffer, 1024, "%s.mStartTime", p);
                   xml.write(buffer, mStartTime);
                   snprintf(buffer, 1024, "%s.mSampling", p);
                   xml.write(buffer, mSampling);
                   snprintf(buffer, 1024, "%s.mFirstCall", p);
                   BOOL_XML_SERIALIZE(mFirstCall, xml, buffer);
                   snprintf(buffer, 1024, "%s.mEF", p);
                   DMATRIX_XML_SERIALIZE(mEF, xml, buffer);
                   snprintf(buffer, 1024, "%s.mEB", p);
                   DMATRIX_XML_SERIALIZE(mEB, xml, buffer);
                   snprintf(buffer, 1024, "%s.mEpf", p);
                   DMATRIX_XML_SERIALIZE(mEpf, xml, buffer);
                   snprintf(buffer, 1024, "%s.mEpb", p);
                   DMATRIX_XML_SERIALIZE(mEpb, xml, buffer);
                   snprintf(buffer, 1024, "%s.mKf", p);
                   DVECTOR_XML_SERIALIZE(mKf, xml, buffer);
                   snprintf(buffer, 1024, "%s.mKb", p);
                   DVECTOR_XML_SERIALIZE(mKb, xml, buffer);
                   snprintf(buffer, 1024, "%s.mNG", p);
                   DVECTOR_XML_SERIALIZE(mG, xml, buffer);
                   snprintf(buffer, 1024, "%s.mF0", p);
                   xml.write(buffer, mF0);
   
   
               }
           }
   
   
   
   
           void operator<<(SeqViewDouble& Data) {
               Dmatrix* in = Data.GetData();
   
               if (in->size1() != 1) {
                   LogSevere("LSLfilter: multichannels not implemented resize");
                   throw bad_matrix_size("Wrong Matrix size");
               }
   
               SetData(*in, Data.GetScale());
   
               if (mFirstCall) {
                   mFirstCall = false;
                   mStartTime = Data.GetStart();
                   mSampling = Data.GetSampling();
               }
           }
   
           void operator>>(SeqViewDouble& outdata) {
               Dmatrix *out = outdata.GetData();
               out->resize(1, mWinSize);
               GetData(*out);
               outdata.SetStart(mStartTime);
               outdata.SetSampling(mSampling);
               outdata.SetScale(1.0);
               mStartTime += mSampling*mWinSize;
           }
   
           //for the online process  
   
           void operator()(SeqViewDouble& Data, SeqViewDouble& outdata) {
               Dmatrix* in = Data.GetData();
   
               if (in->size1() != 1) {
                   LogSevere("LSLfilter: multichannels not implemented resize");
                   throw bad_matrix_size("Wrong Matrix size");
               }
   
               SetData(*in, Data.GetScale());
   
               mStartTime = Data.GetStart();
               mSampling = Data.GetSampling();
   
   
               Dmatrix *out = outdata.GetData();
               out->resize(1, mWinSize);
               GetData(*out);
               outdata.SetStart(Data.GetStart());
               outdata.SetSampling(Data.GetSampling());
               outdata.SetScale(1.0);
   
           }
   
   
   
   
   
           void GetData(Dmatrix& DWOutput);
   
   
           Dmatrix *GetWhitenedMatrix() {
               return &mEF;
           }
   
           int GetDataNeeded();
   
           void SetData(Dmatrix& Data, double scale);
   
   
   
           unsigned int GetOrder() {
               return mOrder - 1;
           }
   
           double GetParcorForward(unsigned int j) {
               return mKf(j);
           }
   
           double GetParcorBackward(unsigned int j) {
               return mKb(j);
           }
   
           double GetEpf(unsigned int j) {
               return mEpf(mF0, j);
           }
   
           double GetErrorForward(unsigned int j) {
               return mEF(mF0, j);
           }
   
           double GetErrorBackward(unsigned int j) {
               return mEB(mF0, j);
           }
   
           double GetSigma(unsigned int j) {
               return mSigma(j);
           }
   
   
   
   
   
       protected:
   
       private:
           FifoBuffer mBuffer;
           unsigned int mWinSize;
           unsigned int mOrder; 
           double mLambda; 
           Dvector mSigma; 
           bool mNorm;
           double mSigma0;
           double mStartTime;
           double mSampling;
           bool mFirstCall;
           Dmatrix mEF; 
           Dmatrix mEB; 
           Dmatrix mEpf; 
           Dmatrix mEpb; 
           Dvector mKf; 
           Dvector mKb; 
           Dvector mG; 
           unsigned int mF0; 
       };
   
   
   
   
   
   
   } //end namespace
   
   #endif // ___LSLFILTER_HPP
