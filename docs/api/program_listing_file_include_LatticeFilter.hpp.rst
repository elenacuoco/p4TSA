
.. _program_listing_file_include_LatticeFilter.hpp:

Program Listing for File LatticeFilter.hpp
==========================================

|exhale_lsh| :ref:`Return to documentation for file <file_include_LatticeFilter.hpp>` (``include/LatticeFilter.hpp``)

.. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS

.. code-block:: none

   
   #ifndef __LATTICEFILTER_HPP
   #define __LATTICEFILTER_HPP
   
   
   
   
   
   
   #include <AlgoBase.hpp>
   #include <SeqView.hpp>
   #include <LatticeView.hpp>
   
   
   
   
   
   
   
   using namespace boost::numeric::ublas;
   
   namespace tsa {
   
       class LatticeFilter : public AlgoBase {
       public:
   
           LatticeFilter(LatticeView& LV);
   
           LatticeFilter(Dvector& ParcorF, Dvector& ParcorB, Dmatrix& ErrF, Dmatrix& ErrB);
   
           virtual ~LatticeFilter();
   
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
   
               } else {
   
                   snprintf(buffer, 1024, "%s.mOrder", p);
                   xml.write(buffer, mOrder);
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
   
   
   
               }
           }
   
   
   
   
           void operator()(SeqViewDouble& InputData, SeqViewDouble& WhitenedData) {
               Dmatrix* in = InputData.GetData();
               Dmatrix* out = WhitenedData.GetData();
   
               if ((in->size1() != out->size1()) || (in->size2() != out->size2())) {
                   out->resize(in->size1(), in->size2());
                   LogWarning("LatticeFilter: resizing output view");
               }
               WhitenedData.SetStart(InputData.GetStart());
               WhitenedData.SetSampling(InputData.GetSampling());
   
               for (unsigned int r = 0; r < in->size1(); r++) {
                   execute(row(*in, r), row(*out, r));
               }
           }
   
   
           void init(LatticeView& LV);
           void execute(matrix_row<Dmatrix> Input, matrix_row<Dmatrix> Output);
   
   
   
   
   
   
   
   
       protected:
   
       private:
           unsigned int mOrder;
           Dvector mParcorF;
           Dvector mParcorB;
           Dmatrix mErrF;
           Dmatrix mErrB;
           int mStatus;
   
   
   
   
       };
   
   
   
   
   
   
   } //end namespace
   
   #endif // ___LATTICEFILTER_HPP
   
