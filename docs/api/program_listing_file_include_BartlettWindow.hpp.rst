
.. _program_listing_file_include_BartlettWindow.hpp:

Program Listing for File BartlettWindow.hpp
===========================================

|exhale_lsh| :ref:`Return to documentation for file <file_include_BartlettWindow.hpp>` (``include/BartlettWindow.hpp``)

.. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS

.. code-block:: none

   
   #ifndef __BARTLETTWINDOW_HPP
   #define __BARTLETTWINDOW_HPP
   
   
   
   #include <BaseWindow.hpp>
   
   
   
   
   
   
   using namespace boost::numeric::ublas;
   
   namespace tsa {
   
       class BartlettWindow : public BaseWindow {
       public:
   
           BartlettWindow(int size)
           :
           BaseWindow(size) {
               FillWindow();
           };
   
           BartlettWindow(int size, const std::string&)
           :
           BaseWindow(size) {
               FillWindow();
           };
   
           virtual ~BartlettWindow() {
   
           };
   
   
           void operator()(SeqViewDouble& v1) {
   
               if (v1.GetSize() != mWindow.size()) {
                   Resize(v1.GetSize());
                   LogWarning("BartlettWindow: Resizing window");
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
                   LogWarning("BartlettWindow: Resizing window");
               }
   
               if ((arg1->size1() != arg2->size1()) || (arg1->size2() != arg2->size2())) {
                   arg2->resize(arg1->size1(), arg1->size2());
                   LogWarning("BartlettWindow: Resizing output");
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
   
                   double x = 2.0 * i / (mWindow.size() - 1.0);
   
                   if (2 * i < mWindow.size()) {
   
                       mWindow(i) = x;
   
                   } else {
   
                       mWindow(i) = 2.0 - x;
   
                   }
               }
               Normalize();
           };
   
   
       };
   
   
   
   
   
   
   
   } // end namespace tsa
   
   #endif // __BARTLETTWINDOW_HPP
