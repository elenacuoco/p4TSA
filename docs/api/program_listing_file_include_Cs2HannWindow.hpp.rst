
.. _program_listing_file_include_Cs2HannWindow.hpp:

Program Listing for File Cs2HannWindow.hpp
==========================================

|exhale_lsh| :ref:`Return to documentation for file <file_include_Cs2HannWindow.hpp>` (``include/Cs2HannWindow.hpp``)

.. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS

.. code-block:: none

   
   #ifndef __CS2HANNWINDOW_HPP
   #define __CS2HANNWINDOW_HPP
   
   
   
   #include <BaseWindow.hpp>
   
   
   
   
   
   
   using namespace boost::numeric::ublas;
   
   
   namespace tsa {
   
       class Cs2HannWindow : public BaseWindow {
       public:
   
           Cs2HannWindow(int size)
           :
           BaseWindow(size) {
               FillWindow();
           };
   
           Cs2HannWindow(int size, const std::string&)
           :
           BaseWindow(size) {
               FillWindow();
           };
   
           virtual ~Cs2HannWindow() {
   
           };
   
   
           void operator()(SeqViewDouble& v1) {
   
               if (v1.GetSize() != mWindow.size()) {
                   Resize(v1.GetSize());
                   LogWarning("Cs2HannWindow: Resizing window");
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
                   LogWarning("Cs2HannWindow: Resizing window");
               }
   
               if ((arg1->size1() != arg2->size1()) || (arg1->size2() != arg2->size2())) {
                   arg2->resize(arg1->size1(), arg1->size2());
                   LogWarning("Cs2HannWindow: Resizing output");
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
   
                   mWindow(i) = 0.5 - 0.5 * cos(2.0 * M_PI * i / (mWindow.size() - 1.0));
   
               }
               Normalize();
           };
   
   
       };
   
   
   
   
   
   
   
   } // end namespace tsa
   
   #endif // __CS2HANNWINDOW_HPP
