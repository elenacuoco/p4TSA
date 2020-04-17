
.. _program_listing_file_include_WelchWindow.hpp:

Program Listing for File WelchWindow.hpp
========================================

|exhale_lsh| :ref:`Return to documentation for file <file_include_WelchWindow.hpp>` (``include/WelchWindow.hpp``)

.. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS

.. code-block:: none

   
   #ifndef __WELCHWINDOW_HPP
   #define __WELCHWINDOW_HPP
   
   
   
   #include <BaseWindow.hpp>
   
   
   
   
   
   
   using namespace boost::numeric::ublas;
   
   namespace tsa {
   
       class WelchWindow : public BaseWindow {
       public:
   
           WelchWindow(int size)
           :
           BaseWindow(size) {
               LogInfo(LOGH1);
               LogInfo("WelchWindow");
               LogInfo(LOGH2);
               LogInfo("Size: %d", size);
               LogInfo(LOGH1);
               FillWindow();
           };
   
           WelchWindow(int size, const std::string& p)
           :
           BaseWindow(size) {
               LogInfo(LOGH1);
               LogInfo("WelchWindow");
               LogInfo(LOGH2);
               LogInfo("Size: %d", size);
               LogInfo("Parameters: %s", p.c_str());
               LogInfo(LOGH1);
               FillWindow();
           };
   
           virtual ~WelchWindow() {
   
           };
   
   
   
           void operator()(SeqViewDouble& v1) {
   
               if (v1.GetSize() != mWindow.size()) {
                   Resize(v1.GetSize());
                   LogWarning("WelchWindow: Resizing window");
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
                   LogWarning("WelchWindow: Resizing window");
               }
   
               if ((arg1->size1() != arg2->size1()) || (arg1->size2() != arg2->size2())) {
                   arg2->resize(arg1->size1(), arg1->size2());
                   LogWarning("WelchWindow: Resizing output");
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
               double norm = 0.0;
               for (unsigned int i = 0; i < mWindow.size(); i++) {
                   double x = mWindow.size() - 1;
                   double q = (x - 2 * i) / x;
                   mWindow(i) = 1.0 - q*q;
               }
               Normalize();
           };
   
   
       };
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   } // end namespace tsa
   
   #endif // __WELCHWINDOW_HPP
