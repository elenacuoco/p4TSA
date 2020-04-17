
.. _program_listing_file_include_WindowFactory.hpp:

Program Listing for File WindowFactory.hpp
==========================================

|exhale_lsh| :ref:`Return to documentation for file <file_include_WindowFactory.hpp>` (``include/WindowFactory.hpp``)

.. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS

.. code-block:: none

   
   #ifndef __WINDOWFACTORY_HPP
   #define __WINDOWFACTORY_HPP
   
   
   
   #include <BartlettWindow.hpp>
   #include <WelchWindow.hpp>
   #include <TukeyHannWindow.hpp>
   #include <TukeyWindow.hpp>
   #include <Cs2HannWindow.hpp>
   #include <Cs2HammingWindow.hpp>
   #include <BisquareWindow.hpp>
   #include <KaiserWindow.hpp>
   
   
   
   
   
   
   
   namespace tsa {
   
       extern std::vector< std::string > GetWindowList();
   
       extern BaseWindow* WindowFactory(const std::string& name, unsigned int size);
   
   
       extern BaseWindow* WindowFactory(const std::string& name, const std::string& parameters,
               unsigned int size);
   
   
   } // end namespace tsa
   
   #endif // __WINDOWFACTORY_HPP
