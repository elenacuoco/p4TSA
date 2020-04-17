
.. _program_listing_file_include_LSLLearning.hpp:

Program Listing for File LSLLearning.hpp
========================================

|exhale_lsh| :ref:`Return to documentation for file <file_include_LSLLearning.hpp>` (``include/LSLLearning.hpp``)

.. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS

.. code-block:: none

   
   #ifndef __LSLLEARNING_HPP
   #define __LSLLEARNING_HPP
   
   
   
   
   
   #include <AlgoBase.hpp>
   #include <SeqView.hpp>
   #include <LatticeView.hpp>
   
   
   
   
   
   
   
   using namespace boost::numeric::ublas;
   
   namespace tsa {
   
       class LSLLearning : public AlgoBase {
       public:
   
           LSLLearning(unsigned int Order, double sigma, double lambda = 1.0);
   
           LSLLearning(const LSLLearning& from);
   
           ~LSLLearning();
   
           LSLLearning& operator=(const LSLLearning& from);
   
   
           void operator()(SeqViewDouble& InputData, SeqViewDouble& WhitenedData);
   
           void operator()(SeqViewDouble& InputData, LatticeView& LatView);
   
           void operator()(SeqViewDouble& InputData, Dvector& Parcor);
   
   
   
           void execute(matrix_row<Dmatrix> InputData, matrix_row<Dmatrix> OutputData);
   
   
           unsigned int GetOrder() {
               return mOrder - 1;
           }
   
           double GetParcorForward(unsigned int j) {
               return mKf(j);
           }
   
           double GetParcorBackward(unsigned int j) {
               return mKb(j);
           }
   
           double GetErrorForward(unsigned int i, unsigned int j) {
               return mEF(i, j);
           }
   
           double GetErrorBackward(unsigned int i, unsigned int j) {
               return mEB(i, j);
           }
   
           double GetEpf(unsigned int i, unsigned int j) {
               return mEpf(i, j);
           }
   
           double GetEpb(unsigned int i, unsigned int j) {
               return mEpb(i, j);
           }
   
           double GetGamma(unsigned int j) {
               return mG(j);
           }
   
           unsigned int GetStatus() {
               return mF0;
           }
   
           double GetSigma() {
               return mSigma;
           }
   
   
   
   
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
   
           void xml_serialize(eternity::xml_archive& xml, const char* p) {
               char buffer[1024];
   
               if (xml.is_loading()) {
   
                   snprintf(buffer, 1024, "%s.mOrder", p);
                   xml.read(buffer, mOrder, 0);
                   snprintf(buffer, 1024, "%s.mKf", p);
                   DVECTOR_XML_SERIALIZE(mKf, xml, buffer);
                   snprintf(buffer, 1024, "%s.mKb", p);
                   DVECTOR_XML_SERIALIZE(mKb, xml, buffer);
                   snprintf(buffer, 1024, "%s.mEF", p);
                   DMATRIX_XML_SERIALIZE(mEF, xml, buffer);
                   snprintf(buffer, 1024, "%s.mEB", p);
                   DMATRIX_XML_SERIALIZE(mEB, xml, buffer);
                   snprintf(buffer, 1024, "%s.mF0", p);
                   xml.read(buffer, mF0, 0);
   
               } else {
   
                   snprintf(buffer, 1024, "%s.mOrder", p);
                   xml.write(buffer, mOrder);
                   snprintf(buffer, 1024, "%s.mKf", p);
                   DVECTOR_XML_SERIALIZE(mKf, xml, buffer);
                   snprintf(buffer, 1024, "%s.mKb", p);
                   DVECTOR_XML_SERIALIZE(mKb, xml, buffer);
                   snprintf(buffer, 1024, "%s.mEF", p);
                   DMATRIX_XML_SERIALIZE(mEF, xml, buffer);
                   snprintf(buffer, 1024, "%s.mEB", p);
                   DMATRIX_XML_SERIALIZE(mEB, xml, buffer);
                   snprintf(buffer, 1024, "%s.mF0", p);
                   xml.write(buffer, mF0);
   
   
   
               }
           }
   
   
       protected:
   
       private:
           unsigned int mOrder; 
           double mSigma; 
           Dmatrix mEF; 
           Dmatrix mEB; 
           Dmatrix mEpf; 
           Dmatrix mEpb; 
           Dvector mKf; 
           Dvector mKb; 
           Dvector mG; 
           double mLambda; 
           unsigned int mF0; 
       };
   
   
   
   
   
   
   } //end namespace
   
   #endif // ___LSLLEARNING_HPP
