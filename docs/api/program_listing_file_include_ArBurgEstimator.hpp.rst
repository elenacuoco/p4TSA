
.. _program_listing_file_include_ArBurgEstimator.hpp:

Program Listing for File ArBurgEstimator.hpp
============================================

|exhale_lsh| :ref:`Return to documentation for file <file_include_ArBurgEstimator.hpp>` (``include/ArBurgEstimator.hpp``)

.. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS

.. code-block:: none

   
   #ifndef __ARBURGESTIMATOR_HPP
   #define __ARBURGESTIMATOR_HPP
   
   
   
   
   
   #include <eternity.hpp>
   #include <AlgoBase.hpp>
   #include <SeqView.hpp>
   #include <LatticeView.hpp>
   #include <Parcor2AR.hpp>
   
   
   
   
   
   
   
   using namespace boost::numeric::ublas;
   namespace tsa {
   
       class ArBurgEstimator : public AlgoBase {
       public:
   
           ArBurgEstimator(unsigned int ArOrder);
   
           virtual ~ArBurgEstimator();
   
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
   
           void xml_serialize(eternity::xml_archive& xml, const char* prefix) {
               char buffer[1024];
   
               if (xml.is_loading()) {
   
                   snprintf(buffer, 1024, "%s.mArOrder", prefix);
                   xml.read(buffer, mArOrder, 0);
                   snprintf(buffer, 1024, "%s.mAR", prefix);
                   DVECTOR_XML_SERIALIZE(mAR, xml, buffer);
   
               } else {
   
                   snprintf(buffer, 1024, "%s.mArOrder", prefix);
                   xml.write(buffer, mArOrder);
                   snprintf(buffer, 1024, "%s.mAR", prefix);
                   DVECTOR_XML_SERIALIZE(mAR, xml, buffer);
   
               }
           }
   
   
   
   
           void operator()(SeqViewDouble& InputData, SeqViewDouble& WhitenedData);
   
   
           void Color(SeqViewDouble& WhitenedData, SeqViewDouble& ColoredData);
           void operator()(SeqViewDouble& InputData);
           void execute(matrix_row<Dmatrix> InputData);
   
           void color(matrix_row<Dmatrix> WhitenedData, matrix_row<Dmatrix> ColoredData);
   
   
   
   
           void GetLatticeView(LatticeView& LV);
   
   
   
           unsigned int GetArOrder();
   
           double GetParcor(unsigned int j);
           double GetAR(unsigned int j);
   
           double GetErrorForward(unsigned int j);
   
           double GetErrorBackward(unsigned int j);
   
   
   
           void SetArOrder(unsigned int P);
   
           void SetAR(unsigned int j, double value);
   
   
       protected:
   
       private:
   
           unsigned int mArOrder; 
           Dvector mParcor; 
           Dvector mAR;
           Dvector mErrorForward; 
           Dvector mErrorBackward; 
           Dvector mWhitenedData;
           Dvector mColoredData;
   
       };
   
   
   
   
   
   
   } //end namespace
   
   #endif // ___ARBURGESTIMATOR_HPP
   
   
