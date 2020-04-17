
.. _program_listing_file_include_Parcor2AR.hpp:

Program Listing for File Parcor2AR.hpp
======================================

|exhale_lsh| :ref:`Return to documentation for file <file_include_Parcor2AR.hpp>` (``include/Parcor2AR.hpp``)

.. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS

.. code-block:: none

   
   #ifndef __PARCOR2AR_HPP
   #define __PARCOR2AR_HPP
   
   
   
   
   
   
   #include <AlgoBase.hpp>
   #include <CreateDvector.hpp>
   
   
   
   
   
   
   
   namespace tsa {
   
       class Parcor2AR : public AlgoBase {
       public:
   
           Parcor2AR();
   
           virtual ~Parcor2AR();
   
           Dvector operator()(Dvector Parcor);
   
   
   
           void execute(Dvector& Parcor, Dvector& AR);
   
   
   
   
   
   
   
       protected:
   
       private:
   
       };
   
   
   
   
   
   
   } //end namespace
   
   #endif // ___PARCOR2AR_HPP
   
   
   
