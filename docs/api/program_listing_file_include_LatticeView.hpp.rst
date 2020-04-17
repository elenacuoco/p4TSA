
.. _program_listing_file_include_LatticeView.hpp:

Program Listing for File LatticeView.hpp
========================================

|exhale_lsh| :ref:`Return to documentation for file <file_include_LatticeView.hpp>` (``include/LatticeView.hpp``)

.. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS

.. code-block:: none

   #ifndef __LATTICEVIEW_HPP
   #define __LATTICEVIEW_HPP
   
   
   
   
   #include <boost/numeric/ublas/matrix.hpp>
   #include <boost/numeric/ublas/io.hpp>
   #include <eternity.hpp>
   
   
   #include <BaseView.hpp>
   
   
   
   
   
   
   
   
   
   using namespace boost::numeric::ublas;
   namespace tsa {
   
   
       class LatticeView : public BaseView {
       public:
   
           LatticeView(unsigned int ArOrder = 1)
           :
           mOrder(ArOrder),
           mErrorForward(2, ArOrder + 1),
           mErrorBackward(2, ArOrder + 1),
           mParcorF(ArOrder + 1),
           mParcorB(ArOrder + 1) {
               mErrorForward.clear();
               mErrorBackward.clear();
               mParcorF.clear();
               mParcorB.clear();
           }
   
   
           ~LatticeView() {
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
   
           void xml_serialize(eternity::xml_archive& xml, const char* prefix) {
               char buffer[1024];
   
               if (xml.is_loading()) {
   
                   snprintf(buffer, 1024, "%s.mOrder", prefix);
                   xml.read(buffer, mOrder, 0);
                   snprintf(buffer, 1024, "%s.mErrorForward", prefix);
                   DMATRIX_XML_SERIALIZE(mErrorForward, xml, buffer);
                   snprintf(buffer, 1024, "%s.mErrorBackward", prefix);
                   DMATRIX_XML_SERIALIZE(mErrorBackward, xml, buffer);
                   snprintf(buffer, 1024, "%s.mParcorF", prefix);
                   DVECTOR_XML_SERIALIZE(mParcorF, xml, buffer);
                   snprintf(buffer, 1024, "%s.mParcorB", prefix);
                   DVECTOR_XML_SERIALIZE(mParcorB, xml, buffer);
               } else {
                   snprintf(buffer, 1024, "%s.mOrder", prefix);
                   xml.write(buffer, mOrder);
                   snprintf(buffer, 1024, "%s.mErrorForward", prefix);
                   DMATRIX_XML_SERIALIZE(mErrorForward, xml, buffer);
                   snprintf(buffer, 1024, "%s.mErrorBackward", prefix);
                   DMATRIX_XML_SERIALIZE(mErrorBackward, xml, buffer);
                   snprintf(buffer, 1024, "%s.mParcorF", prefix);
                   DVECTOR_XML_SERIALIZE(mParcorF, xml, buffer);
                   snprintf(buffer, 1024, "%s.mParcorB", prefix);
                   DVECTOR_XML_SERIALIZE(mParcorB, xml, buffer);
               }
           }
   
   
   
   
   
           unsigned int GetOrder() {
               return mOrder;
           }
   
           double GetParcor(unsigned int j) {
               return mParcorF(j);
           }
   
           Dvector* GetParcorF() {
               return &mParcorF;
           }
   
           Dvector* GetParcorB() {
               return &mParcorB;
           }
   
           double GetParcorF(unsigned int j) {
               return mParcorF(j);
           }
   
           double GetParcorB(unsigned int j) {
               return mParcorB(j);
           }
   
           Dmatrix* GetErrorForward() {
               return &mErrorForward;
           }
   
           Dmatrix* GetErrorBackward() {
               return &mErrorBackward;
           }
   
   
   
           double GetErrorForward(unsigned int i, unsigned int j) {
               return mErrorForward(i, j);
           }
   
           double GetErrorBackward(unsigned int i, unsigned int j) {
               return mErrorBackward(i, j);
           }
   
   
   
   
   
           void SetOrder(unsigned int v) {
               mOrder = v;
           };
   
           void SetParcorF(unsigned int j, double v) {
               mParcorF(j) = v;
           }
   
           void SetParcorB(unsigned int j, double v) {
               mParcorB(j) = v;
           }
   
           void SetErrorForward(unsigned int j, double v) {
               mErrorForward(0, j) = v;
               mErrorForward(1, j) = v;
           }
   
           void SetErrorBackward(unsigned int j, double v) {
               mErrorBackward(0, j) = v;
               mErrorBackward(1, j) = v;
           }
   
   
   
       protected:
   
       private:
           unsigned int mOrder; 
           Dmatrix mErrorForward; 
           Dmatrix mErrorBackward; 
           Dvector mParcorF; 
           Dvector mParcorB; 
   
       };
   
   
   
   
   
   
   
   
   
   } //end namespace tsa
   
   #endif // ___LATTICEVIEW_HPP
