
.. _program_listing_file_include_Arma2TF.hpp:

Program Listing for File Arma2TF.hpp
====================================

|exhale_lsh| :ref:`Return to documentation for file <file_include_Arma2TF.hpp>` (``include/Arma2TF.hpp``)

.. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS

.. code-block:: none

   
   #ifndef __ARMA2TF_HPP
   #define __ARMA2TF_HPP
   
   
   
   
   
   #include <AlgoBase.hpp>
   #include <ARMAView.hpp>
   #include <SeqView.hpp>
   
   
   
   
   
   
   
   namespace tsa {
   
       class Arma2TF : public AlgoBase {
       public:
   
           Arma2TF();
   
           Arma2TF(const Arma2TF& from);
   
           virtual ~Arma2TF();
   
           Arma2TF& operator=(const Arma2TF& from);
   
   
           void operator()(ARMAView& arma, SeqViewComplex& TF);
   
   
           void execute(Dvector& AR, Dvector& MA, Cvector& TF);
   
   
   
   
   
   
   
       protected:
   
       private:
   
       };
   
   
   
   
   
   
   } //end namespace
   
   #endif // ___ARMA2TF_HPP
   
   
   
   
   
   
