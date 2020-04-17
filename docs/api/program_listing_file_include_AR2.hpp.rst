
.. _program_listing_file_include_AR2.hpp:

Program Listing for File AR2.hpp
================================

|exhale_lsh| :ref:`Return to documentation for file <file_include_AR2.hpp>` (``include/AR2.hpp``)

.. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS

.. code-block:: none

   
   #ifndef __AR2_HPP
   #define __AR2_HPP
   
   
   
   
   #include <AlgoBase.hpp>
   
   
   
   
   
   
   
   
   namespace tsa {
   
       class AR2 : public AlgoBase {
       public:
   
           AR2(const double f, const double gamma, const double h);
   
   
           virtual ~AR2();
   
   
   
           void operator()(SeqViewDouble& in, SeqViewDouble& out);
   
           void execute(Dmatrix& in, Dmatrix& out, double scale);
   
   
   
   
   
   
   
       protected:
   
       private:
   
           double mA;
           double mB;
           double mC;
   
           double mXm1;
           double mXm2;
   
   
       };
   
   
   
   
   
   
   
   } // end namespace tsa
   
   #endif // __AR2_HPP
