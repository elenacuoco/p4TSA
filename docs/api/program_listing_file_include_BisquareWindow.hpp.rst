
.. _program_listing_file_include_BisquareWindow.hpp:

Program Listing for File BisquareWindow.hpp
===========================================

|exhale_lsh| :ref:`Return to documentation for file <file_include_BisquareWindow.hpp>` (``include/BisquareWindow.hpp``)

.. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS

.. code-block:: none

   
   #ifndef __ALGOBISQUAREWINDOW_HPP
   #define __ALGOBISQUAREWINDOW_HPP
   
   
   
   #include <BaseWindow.hpp>
   
   
   
   
   
   
   using namespace boost::numeric::ublas;
   
   namespace tsa {
   
       class BisquareWindow : public BaseWindow {
       public:
   
           BisquareWindow(int size)
           :
           BaseWindow(size) {
               FillWindow();
           };
   
           BisquareWindow(int size, const std::string&)
           :
           BaseWindow(size) {
               FillWindow();
           };
   
           virtual ~BisquareWindow() {
   
           };
   
   
           void operator()(SeqViewDouble& v1) {
   
               if (v1.GetSize() != mWindow.size()) {
                   Resize(v1.GetSize());
                   LogWarning("BisquareWindow: Resizing window");
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
                   LogWarning("BisquareWindow: Resizing window");
               }
   
               if ((arg1->size1() != arg2->size1()) || (arg1->size2() != arg2->size2())) {
                   arg2->resize(arg1->size1(), arg1->size2());
                   LogWarning("BisquareWindow: Resizing output");
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
               for (unsigned int i = 0; i < mWindow.size(); i++) {
                   double x = 0.5 * mWindow.size() - 0.5;
                   double q = fabs(i - x) / x;
                   mWindow(i) = (1.0 - q * q)*(1.0 - q * q);
               }
               Normalize();
           };
   
   
       };
   
   
   
   
   
   
   
   } // end namespace tsa
   
   #endif // __ALGOBISQUAREWINDOW_HPP
