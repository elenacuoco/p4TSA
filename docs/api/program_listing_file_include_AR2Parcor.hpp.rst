
.. _program_listing_file_include_AR2Parcor.hpp:

Program Listing for File AR2Parcor.hpp
======================================

|exhale_lsh| :ref:`Return to documentation for file <file_include_AR2Parcor.hpp>` (``include/AR2Parcor.hpp``)

.. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS

.. code-block:: none

   
   #ifndef __AR2PARCOR_HPP
   #define __AR2PARCOR_HPP
   
   
   
   
   
   
   #include <AlgoBase.hpp>
   
   
   
   
   
   
   
   namespace tsa {
   
       class AR2Parcor : public AlgoBase {
       public:
   
           AR2Parcor();
   
           virtual ~AR2Parcor();
   
   
           void execute(Dvector& AR, Dvector& Parcor);
   
   
   
   
   
   
   
       protected:
   
       private:
   
       };
   
   
   
   
   
   
   } //end namespace
   
   #endif // ___AR2PARCOR_HPP
   
   
   
