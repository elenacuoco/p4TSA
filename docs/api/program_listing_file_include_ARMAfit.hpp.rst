
.. _program_listing_file_include_ARMAfit.hpp:

Program Listing for File ARMAfit.hpp
====================================

|exhale_lsh| :ref:`Return to documentation for file <file_include_ARMAfit.hpp>` (``include/ARMAfit.hpp``)

.. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS

.. code-block:: none

   #ifndef __ARMAFIT_HPP
   #define __ARMAFIT_HPP
   
   
   
   
   
   
   
   
   #include <AlgoBase.hpp>
   
   
   #include <MYWE.hpp>
   
   
   
   
   
   
   namespace tsa {
   
   
       class ARMAfit {
       public:
   
           ARMAfit(unsigned int P, unsigned int Q);
   
   
           ~ARMAfit();
   
           ARMAfit& operator=(const ARMAfit& from);
   
   
           void execute(Dvector& PSD);
   
   
   
   
   
   
   
   
       protected:
   
       private:
           unsigned int mP;
           unsigned int mQ;
           Dvector mAR;
           Dvector mMA;
           MYWE mMethod;
   
       };
   
   
   
   
   
   
   
   
   } //end namespace
   
   #endif // __ARMAFIT_HPP
   
