
.. _program_listing_file_include_TukeyHannWindow.hpp:

Program Listing for File TukeyHannWindow.hpp
============================================

|exhale_lsh| :ref:`Return to documentation for file <file_include_TukeyHannWindow.hpp>` (``include/TukeyHannWindow.hpp``)

.. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS

.. code-block:: none

   
   #ifndef __TUKEYHANNWINDOW_HPP
   #define __TUKEYHANNWINDOW_HPP
   
   
   
   #include <BaseWindow.hpp>
   
   
   
   
   
   
   using namespace boost::numeric::ublas;
   
   namespace tsa {
   
       class TukeyHannWindow : public BaseWindow {
       public:
   
           TukeyHannWindow(int size)
           :
           BaseWindow(size) {
               LogInfo(LOGH1);
               LogInfo("TukeyHannWindow");
               LogInfo(LOGH2);
               LogInfo("Size: %d", size);
               LogInfo(LOGH1);
               FillWindow();
           };
   
           TukeyHannWindow(int size, const std::string& p)
           :
           BaseWindow(size) {
               LogInfo(LOGH1);
               LogInfo("TukeyHannWindow");
               LogInfo(LOGH2);
               LogInfo("Size: %d", size);
               LogInfo("Parameters: %s", p.c_str());
               LogInfo(LOGH1);
               FillWindow();
           };
   
           virtual ~TukeyHannWindow() {
   
           };
   
   
           void operator()(SeqViewDouble& v1) {
   
               if (v1.GetSize() != mWindow.size()) {
                   Resize(v1.GetSize());
                   LogWarning("TukeyHannWindow: Resizing window");
               }
   
               execute(
                       *v1.GetData(),
                       *v1.GetData()
                       );
   
           };
   
           void operator()(SeqViewDouble& v1, SeqViewDouble& v2) {
   
               Dmatrix *arg1 = v1.GetData();
               Dmatrix *arg2 = v2.GetData();
   
               if (v1.GetSize() != mWindow.size()) {
                   Resize(v1.GetSize());
                   LogWarning("TukeyHannWindow: Resizing window");
               }
   
               if ((arg1->size1() != arg2->size1()) || (arg1->size2() != arg2->size2())) {
                   arg2->resize(arg1->size1(), arg1->size2());
                   LogWarning("TukeyHannWindow: Resizing output");
               }
   
               execute(*arg1, *arg2);
   
               v2.SetScale(v1.GetScale());
               v2.SetStart(v1.GetStart());
               v2.SetSampling(v1.GetSampling());
   
           };
   
           void Resize(unsigned int size) {
               BaseWindow::Resize(size);
               FillWindow();
           }
   
   
   
   
   
   
   
   
   
   
       protected:
   
   
   
   
       private:
   
           void FillWindow() {
               double n = mWindow.size();
   
               for (unsigned int i = 0; i < mWindow.size(); i++) {
                   mWindow(i) = 0.25 * Dirichlet(2 * (i / (n - 1)) - 1.0 - 0.5)+(1.0 - 2.0 * 0.25) * Dirichlet(2 * (i / (n - 1)) - 1.0)
                           + 0.25 * Dirichlet(2 * (i / (n - 1)) - 1.0 + 0.5);
               }
               Normalize();
           };
   
           double Dirichlet(double theta) {
               return sin((2 * M_PI + 0.5) * theta) / (2 * M_PI * sin(0.5 * theta));
           };
   
       };
   
   
   
   
   
   
   
   } // end namespace tsa
   
   #endif // __TUKEYHANNWINDOW_HPP
