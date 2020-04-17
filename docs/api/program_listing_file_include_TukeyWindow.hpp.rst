
.. _program_listing_file_include_TukeyWindow.hpp:

Program Listing for File TukeyWindow.hpp
========================================

|exhale_lsh| :ref:`Return to documentation for file <file_include_TukeyWindow.hpp>` (``include/TukeyWindow.hpp``)

.. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS

.. code-block:: none

   
   #ifndef __TUKEYWINDOW_HPP
   #define __TUKEYWINDOW_HPP
   
   
   
   #include <BaseWindow.hpp>
   #include <tsaUtilityFunctions.hpp>
   
   
   
   
   
   
   using namespace boost::numeric::ublas;
   
   
   namespace tsa {
   
       class TukeyWindow : public BaseWindow {
       public:
   
           TukeyWindow(int size)
           :
           BaseWindow(size) {
               LogInfo(LOGH1);
               LogInfo("TukeyHannWindow");
               LogInfo(LOGH2);
               LogInfo("Size: %d", size);
               LogInfo("Parameters: 0.5");
               LogInfo(LOGH1);
               FillWindow();
   
               mR = 0.5;
               FillWindow();
           };
   
           TukeyWindow(int size, const std::string& par)
           :
           BaseWindow(size) {
               LogInfo(LOGH1);
               LogInfo("TukeyHannWindow");
               LogInfo(LOGH2);
               LogInfo("Size: %d", size);
               LogInfo("Parameters: %s", par.c_str());
               LogInfo(LOGH1);
               FillWindow();
               ParseParameterString parse(par);
               mR = parse.GetFloat(0);
               FillWindow();
           };
   
           virtual ~TukeyWindow() {
   
           };
   
   
           void operator()(SeqViewDouble& v1) {
   
               if (v1.GetSize() != mWindow.size()) {
                   Resize(v1.GetSize());
                   LogWarning("TukeyWindow: Resizing window");
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
                   LogWarning("TukeyWindow: Resizing window");
               }
   
               if ((arg1->size1() != arg2->size1()) || (arg1->size2() != arg2->size2())) {
                   arg2->resize(arg1->size1(), arg1->size2());
                   LogWarning("TukeyWindow: Resizing output");
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
   
   
   
   
           double operator()(int i) {
               return mWindow(i);
           };
   
   
   
   
   
   
       protected:
   
   
   
       private:
   
           double mR;
   
           void FillWindow() {
               double n = (double) mWindow.size();
   
               double nn = n - 1.0;
               double a = 1.0 - mR;
   
               for (unsigned int i = 0; i < mWindow.size(); i++) {
                   double np = i - 0.5 * n;
                   if (fabs(np) < a * 0.5 * nn) {
                       mWindow(i) = 1.0;
                   } else {
                       mWindow(i) = 0.5 * (1.0 + cos(M_PI * (fabs(np) - a * 0.5 * nn) / (0.5 * (1.0 - a) * nn)));
                   }
               }
               Normalize();
           };
   
   
       };
   
   
   
   
   
   
   } // end namespace tsa
   
   #endif // __TUKEYWINDOW_HPP
