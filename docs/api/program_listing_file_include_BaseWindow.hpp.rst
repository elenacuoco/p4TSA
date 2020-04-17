
.. _program_listing_file_include_BaseWindow.hpp:

Program Listing for File BaseWindow.hpp
=======================================

|exhale_lsh| :ref:`Return to documentation for file <file_include_BaseWindow.hpp>` (``include/BaseWindow.hpp``)

.. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS

.. code-block:: none

   
   #ifndef __BASEWINDOW_HPP
   #define __BASEWINDOW_HPP
   
   #include <map>
   #include <stdio.h>
   #include <boost/numeric/ublas/matrix.hpp>
   
   
   #include <AlgoBase.hpp>
   
   
   
   
   
   
   
   
   using namespace boost::numeric::ublas;
   namespace tsa {
   
       class BaseWindow : public AlgoBase {
       public:
           BaseWindow(unsigned int size);
   
           virtual ~BaseWindow();
   
   
           static double CrossAverage(BaseWindow& w1, BaseWindow& w2);
   
           static double CrossSquareAverage(BaseWindow& w1, BaseWindow& w2);
   
   
           virtual void operator()(SeqViewDouble& v1);
   
           virtual void operator()(SeqViewDouble& v1, SeqViewDouble& v2);
   
   
           void execute(Dmatrix& in, Dmatrix& out);
   
           void execute(Dmatrix& in, Dmatrix& out, unsigned int offset);
   
   
           void execute(Dmatrix& inout);
   
           void execute(Dvector& inout);
   
           double operator()(int i);
   
           virtual void Resize(unsigned int size);
   
   
   
           unsigned int GetSize();
   
   
   
   
           virtual void Normalize();
       protected:
   
           virtual void FillWindow();
   
   
   
           Dvector mWindow;
   
       private:
   
   
   
       };
   
   
   
   
   
   
   
   
   } // end namespace tsa
   
   #endif // __BASEWINDOW_HPP
