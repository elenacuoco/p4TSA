
.. _program_listing_file_include_ButterworthFilter.hpp:

Program Listing for File ButterworthFilter.hpp
==============================================

|exhale_lsh| :ref:`Return to documentation for file <file_include_ButterworthFilter.hpp>` (``include/ButterworthFilter.hpp``)

.. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS

.. code-block:: none

   
   #ifndef __BUTTERWORTHFILTER_HPP
   #define __BUTTERWORTHFILTER_HPP
   
   #include <fparser.hpp>
   
   
   
   #include <AlgoBase.hpp>
   
   
   
   
   
   
   
   
   
   using namespace boost::numeric::ublas;
   
   namespace tsa {
   
       class ButterworthFilter : public AlgoBase {
       public:
   
           ButterworthFilter(double freq, int order);
   
           virtual ~ButterworthFilter();
   
           void operator()(SeqViewComplex& data);
   
   
           void operator()(SeqViewComplex& datain, SeqViewComplex& dataout);
   
   
   
           void execute(Cmatrix &datain, Cmatrix &dataout, double fstart, double fsample, double scale);
   
           void execute(Cmatrix &datain, double fstart, double fsample, double scale);
   
   
   
   
   
   
   
   
   
       protected:
   
       private:
           int mOrder;
           double mFreq;
           Cdouble *poles;
   
       };
   
   
   
   
   
   
   
   } // end namespace tsa
   
   #endif // __BUTTERWORTHFILTER_HPP
