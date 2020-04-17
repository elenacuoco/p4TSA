
.. _program_listing_file_include_MYWE.hpp:

Program Listing for File MYWE.hpp
=================================

|exhale_lsh| :ref:`Return to documentation for file <file_include_MYWE.hpp>` (``include/MYWE.hpp``)

.. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS

.. code-block:: none

   #ifndef __MYWE_HPP
   #define __MYWE_HPP
   
   
   
   
   
   
   
   
   #include <AlgoBase.hpp>
   
   
   
   
   
   
   
   
   
   namespace tsa {
   
   
       class MYWE {
       public:
   
           MYWE(unsigned int mIP, unsigned int mIQ);
   
           ~MYWE();
   
           MYWE& operator=(const MYWE& from);
   
   
           void execute(Dvector& Corr, Dvector& AR);
   
   
   
   
   
   
   
   
       protected:
   
       private:
           unsigned int mIP;
           unsigned int mIQ;
           Dmatrix mA;
           Dmatrix mB;
           Dvector mRho;
   
   
       };
   
   
   
   
   
   
   
   
   } //end namespace
   
   #endif // __MYWE_HPP
   
   
   
