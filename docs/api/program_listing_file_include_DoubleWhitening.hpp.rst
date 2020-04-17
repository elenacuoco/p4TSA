
.. _program_listing_file_include_DoubleWhitening.hpp:

Program Listing for File DoubleWhitening.hpp
============================================

|exhale_lsh| :ref:`Return to documentation for file <file_include_DoubleWhitening.hpp>` (``include/DoubleWhitening.hpp``)

.. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS

.. code-block:: none

   #ifndef __DOUBLEWHITENING_HPP
   #define __DOUBLEWHITENING_HPP
   
   #include <boost/config.hpp>
   
   
   
   
   
   
   
   #include <SeqView.hpp>
   #include <LatticeView.hpp>
   #include <AlgoBase.hpp>
   #include <FifoBuffer.hpp>
   
   
   
   
   
   
   
   using namespace boost::numeric::ublas;
   namespace tsa {
   
   
   
       class DoubleWhitening : public AlgoBase {
       public:
   
   
           DoubleWhitening(LatticeView &LV, unsigned int OutputSize, unsigned int ExtraSize);
   
           DoubleWhitening(Dvector &ParcorF, Dvector &ParcorB, Dmatrix &ErrF, Dmatrix &ErrB, unsigned int OutputSize,
                           unsigned int ExtraSize);
   
   
           void init(LatticeView &LV);
   
           virtual ~DoubleWhitening();
   
   
           void operator<<(SeqViewDouble &Data) {
               Dmatrix *in = Data.GetData();
   
               if (in->size1() != 1) {
                   LogSevere("DoubleWhitening: multichannels not implemented resize");
                   throw bad_matrix_size("Wrong Matrix size");
               }
   
               SetData(*in, Data.GetScale());
   
               if (mFirstCall) {
                   mFirstCall = false;
                   mStartTime = Data.GetStart();
                   mSampling = Data.GetSampling();
               }
           }
   
           void operator>>(SeqViewDouble &outdata) {
               Dmatrix *out = outdata.GetData();
               out->resize(1, mOutputSize);
               GetData(*out);
               outdata.SetStart(mStartTime);
               outdata.SetSampling(mSampling);
               outdata.SetScale(1.0);
               mStartTime += mSampling * mOutputSize;
           }
   
           DoubleWhitening& Input(SeqViewDouble &Data);
   
           DoubleWhitening& Output(SeqViewDouble &outdata);
   
   
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
   
           void xml_serialize(eternity::xml_archive &xml, const char *p) {
               char buffer[1024];
   
               if (xml.is_loading()) {
   
                   snprintf(buffer, 1024, "%s.mBuffer", p);
                   mBuffer.xml_serialize(xml, buffer);
                   snprintf(buffer, 1024, "%s.mFirstCall", p);
                   BOOL_XML_SERIALIZE(mFirstCall, xml, buffer);
                   snprintf(buffer, 1024, "%s.mOutputSize", p);
                   xml.read(buffer, mOutputSize, 0);
                   snprintf(buffer, 1024, "%s.mTotSize", p);
                   xml.read(buffer, mTotSize, 0);
                   snprintf(buffer, 1024, "%s.mOrder", p);
                   xml.read(buffer, mOrder, 0);
                   snprintf(buffer, 1024, "%s.mStartTime", p);
                   xml.read(buffer, mStartTime, 0);
                   snprintf(buffer, 1024, "%s.mSampling", p);
                   xml.read(buffer, mSampling, 0);
                   snprintf(buffer, 1024, "%s.mParcorF", p);
                   DVECTOR_XML_SERIALIZE(mParcorF, xml, buffer);
                   snprintf(buffer, 1024, "%s.mParcorB", p);
                   DVECTOR_XML_SERIALIZE(mParcorB, xml, buffer);
                   snprintf(buffer, 1024, "%s.mErrF", p);
                   DMATRIX_XML_SERIALIZE(mErrF, xml, buffer);
                   snprintf(buffer, 1024, "%s.mErrB", p);
                   DMATRIX_XML_SERIALIZE(mErrB, xml, buffer);
                   snprintf(buffer, 1024, "%s.mStatus", p);
                   xml.read(buffer, mStatus, 0);
                   snprintf(buffer, 1024, "%s.mEf", p);
                   DMATRIX_XML_SERIALIZE(mEf, xml, buffer);
                   snprintf(buffer, 1024, "%s.mEb", p);
                   DMATRIX_XML_SERIALIZE(mEb, xml, buffer);
                   snprintf(buffer, 1024, "%s.mWhitened", p);
                   DMATRIX_XML_SERIALIZE(mWhitened, xml, buffer);
   
   
               } else {
   
                   snprintf(buffer, 1024, "%s.mBuffer", p);
                   mBuffer.xml_serialize(xml, buffer);
                   snprintf(buffer, 1024, "%s.mFirstCall", p);
                   BOOL_XML_SERIALIZE(mFirstCall, xml, buffer);
                   snprintf(buffer, 1024, "%s.mOutputSize", p);
                   xml.write(buffer, mOutputSize);
                   snprintf(buffer, 1024, "%s.mTotSize", p);
                   xml.write(buffer, mTotSize);
                   snprintf(buffer, 1024, "%s.mOrder", p);
                   xml.write(buffer, mOrder);
                   snprintf(buffer, 1024, "%s.mStartTime", p);
                   xml.write(buffer, mStartTime);
                   snprintf(buffer, 1024, "%s.mSampling", p);
                   xml.write(buffer, mSampling);
                   snprintf(buffer, 1024, "%s.mParcorF", p);
                   DVECTOR_XML_SERIALIZE(mParcorF, xml, buffer);
                   snprintf(buffer, 1024, "%s.mParcorB", p);
                   DVECTOR_XML_SERIALIZE(mParcorB, xml, buffer);
                   snprintf(buffer, 1024, "%s.mErrF", p);
                   DMATRIX_XML_SERIALIZE(mErrF, xml, buffer);
                   snprintf(buffer, 1024, "%s.mErrB", p);
                   DMATRIX_XML_SERIALIZE(mErrB, xml, buffer);
                   snprintf(buffer, 1024, "%s.mStatus", p);
                   xml.write(buffer, mStatus);
                   snprintf(buffer, 1024, "%s.mEf", p);
                   DMATRIX_XML_SERIALIZE(mEf, xml, buffer);
                   snprintf(buffer, 1024, "%s.mEb", p);
                   DMATRIX_XML_SERIALIZE(mEb, xml, buffer);
                   snprintf(buffer, 1024, "%s.mWhitened", p);
                   DMATRIX_XML_SERIALIZE(mWhitened, xml, buffer);
   
   
               }
           }
   
   
   
   
   
           void GetData(Dmatrix &DWOutput);
   
   
           Dmatrix *GetWhitenedMatrix() {
               return &mWhitened;
           }
   
   
           void SetData(Dmatrix &Data, double scale);
   
   
       protected:
   
       private:
           FifoBuffer mBuffer;
           bool mFirstCall;
           unsigned int mOutputSize;
           unsigned int mTotSize;
           unsigned int mOrder;
           double mStartTime;
           double mSampling;
           Dvector mParcorF;
           Dvector mParcorB;
           Dmatrix mErrF;
           Dmatrix mErrB;
           int mStatus;
           Dmatrix mEf;
           Dmatrix mEb;
           Dmatrix mWhitened;
   
   
       };
   
   
   
   
   
   
   
   
   
   
   
   } //end namespace
   
   #endif // ___DOUBLEWHITENING_HPP
   
   
