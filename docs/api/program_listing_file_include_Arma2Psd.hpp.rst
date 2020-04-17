
.. _program_listing_file_include_Arma2Psd.hpp:

Program Listing for File Arma2Psd.hpp
=====================================

|exhale_lsh| :ref:`Return to documentation for file <file_include_Arma2Psd.hpp>` (``include/Arma2Psd.hpp``)

.. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS

.. code-block:: none

   
   #ifndef __ARMA2PSD_HPP
   #define __ARMA2PSD_HPP
   
   
   
   
   
   #include <AlgoBase.hpp>
   #include <ARMAView.hpp>
   #include <SeqView.hpp>
   
   
   
   
   
   
   
   namespace tsa {
   
       class Arma2Psd : public AlgoBase {
       public:
   
           Arma2Psd();
   
           Arma2Psd(const Arma2Psd& from);
   
           virtual ~Arma2Psd();
   
           Arma2Psd& operator=(const Arma2Psd& from);
   
   
           void operator()(ARMAView& arma, SeqViewDouble& Psd);
   
   
           void execute(Dvector& AR, Dvector& MA, Dvector& psd);
   
   
   
   
   
   
   
       protected:
   
       private:
   
       };
   
   
   
   
   
   
   } //end namespace
   
   #endif // ___ARMA2PSD_HPP
   
   
   
   
