
.. _program_listing_file_include_KaiserWindow.hpp:

Program Listing for File KaiserWindow.hpp
=========================================

|exhale_lsh| :ref:`Return to documentation for file <file_include_KaiserWindow.hpp>` (``include/KaiserWindow.hpp``)

.. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS

.. code-block:: none

   
   #ifndef __KAISERWINDOW_HPP
   #define __KAISERWINDOW_HPP
   
   
   
   #include <BaseWindow.hpp>
   #include <tsaUtilityFunctions.hpp>
   #include <gsl/gsl_sf_bessel.h>
   
   
   
   
   
   
   using namespace boost::numeric::ublas;
   
   
   namespace tsa {
   
       class KaiserWindow : public BaseWindow {
       public:
   
           KaiserWindow(int size)
           :
           BaseWindow(size) {
               mAlpha = 1.0;
               FillWindow();
           };
   
           KaiserWindow(int size, const std::string& par)
           :
           BaseWindow(size) {
               ParseParameterString parse(par);
               mAlpha = parse.GetFloat(0);
               FillWindow();
           };
   
           virtual ~KaiserWindow() {
   
           };
   
   
           void operator()(SeqViewDouble& v1) {
   
               if (v1.GetSize() != mWindow.size()) {
                   Resize(v1.GetSize());
                   LogWarning("KaiserWindow: Resizing window");
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
                   LogWarning("KaiserWindow: Resizing window");
               }
   
               if ((arg1->size1() != arg2->size1()) || (arg1->size2() != arg2->size2())) {
                   arg2->resize(arg1->size1(), arg1->size2());
                   LogWarning("KaiserWindow: Resizing output");
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
   
           double mAlpha;
   
           void FillWindow() {
               unsigned int n = mWindow.size() - 1;
   
               double norm = 1.0 / gsl_sf_bessel_I0(M_PI * mAlpha);
   
               for (unsigned int k = 0; k < n; k++) {
   
                   double p = double(2.0 * k) / n - 1.0;
                   double x = M_PI * mAlpha * sqrt(1.0 - p * p);
   
                   mWindow(k) = norm * gsl_sf_bessel_I0(x);
   
               }
   
               Normalize();
           };
   
   
       };
   
   
   
   
   
   
   } // end namespace tsa
   
   #endif // __KAISERWINDOW_HPP
