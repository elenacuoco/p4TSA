
.. _program_listing_file_include_ARMAFilter.hpp:

Program Listing for File ARMAFilter.hpp
=======================================

|exhale_lsh| :ref:`Return to documentation for file <file_include_ARMAFilter.hpp>` (``include/ARMAFilter.hpp``)

.. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS

.. code-block:: none

   
   #ifndef __ARMAFILTER_HPP
   #define __ARMAFILTER_HPP
   
   
   
   
   #include <AlgoBase.hpp>
   
   
   
   
   
   
   
   
   namespace tsa {
   
       class ARMAFilter : public AlgoBase {
       public:
   
           ARMAFilter(const std::vector<double>& mAR, const std::vector<double>& mMA, double gain);
   
   
           virtual ~ARMAFilter();
   
   
   
           void operator()(SeqViewDouble& in, SeqViewDouble& out);
   
           void execute(Dmatrix& in, Dmatrix& out, double scale);
   
   
   
   
           void SetFilter(const std::vector<double>& mAR, const std::vector<double>& mMA, double gain);
   
   
   
   
       protected:
   
       private:
   
           LDvector mAR;
           LDvector mMA;
           long double mGain;
   
           int mInPointer;
           int mOutPointer;
           LDvector mInBuffer;
           LDvector mOutBuffer;
   
   
       };
   
   
   
   
   
   
   
   } // end namespace tsa
   
   #endif // __ARMAFILTER_HPP
