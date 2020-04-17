
.. _program_listing_file_include_BaseView.hpp:

Program Listing for File BaseView.hpp
=====================================

|exhale_lsh| :ref:`Return to documentation for file <file_include_BaseView.hpp>` (``include/BaseView.hpp``)

.. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS

.. code-block:: none

   
   #ifndef __BASEVIEW_HPP
   #define __BASEVIEW_HPP
   
   
   #include <map>
   #include <string>
   
   
   
   #include <tsaTypes.hpp>
   #include <tsaTraits.hpp>
   #include <tsaUtilityFunctions.hpp>
   #include <tsaSerialize.hpp>
   #include <tsaLog.hpp>
   
   
   
   
   
   namespace tsa {
   
   
   
       class AlgoBase;
   
   
       class BaseView {
       public:
           friend class AlgoBase;
   
           BaseView(const std::string& aName = std::string())
           :
           mName(aName) {
   
           }
   
   
           BaseView(const BaseView& from) {
               mName = from.mName;
           }
   
   
           ~BaseView() {
   
           }
   
   
           BaseView& operator=(const BaseView& from) {
               mName = from.mName;
               return *this;
           }
   
   
   
   
   
   
   
   
           std::string GetName() {
               return mName;
           }
   
   
   
   
   
           void SetName(const std::string& aName) {
               mName = aName;
           }
   
   
   
   
   
       protected:
   
   
           std::string mName;
   
       private:
   
   
       };
   
   
   
   
   
   
   
   
   
   
   
   
   
   } // end namespace tsa
   
   #endif // __BASEVIEW_HPP
