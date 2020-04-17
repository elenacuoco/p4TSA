
.. _program_listing_file_include_VArma2TF.hpp:

Program Listing for File VArma2TF.hpp
=====================================

|exhale_lsh| :ref:`Return to documentation for file <file_include_VArma2TF.hpp>` (``include/VArma2TF.hpp``)

.. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS

.. code-block:: none

   
   #ifndef __VARMA2TF_HPP
   #define __VARMA2TF_HPP
   
   
   
   
   #include <AlgoBase.hpp>
   
   #include <LUComplexSolve.hpp>
   
   
   
   
   namespace tsa {
   
       class VArma2TF : public AlgoBase {
       public:
   
           VArma2TF();
   
           VArma2TF(const VArma2TF& from);
   
           virtual ~VArma2TF();
   
           VArma2TF& operator=(const VArma2TF& from);
   
   
           void execute(VDmatrix& AR, VDmatrix& MA, Cmatrix& TF);
   
   
   
   
   
   
   
       protected:
   
       private:
   
           LUComplexSolve mLUsolver;
   
       };
   
   
   
   
   
   
   } //end namespace
   
   #endif // ___VARMA2TF_HPP
   
   
   
   
   
   
