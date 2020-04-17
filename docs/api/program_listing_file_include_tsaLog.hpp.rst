
.. _program_listing_file_include_tsaLog.hpp:

Program Listing for File tsaLog.hpp
===================================

|exhale_lsh| :ref:`Return to documentation for file <file_include_tsaLog.hpp>` (``include/tsaLog.hpp``)

.. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS

.. code-block:: none

   #ifndef __NAPLOG_HPP
   #define __NAPLOG_HPP
   
   
   #define RLOG_COMPONENT tsa
   
   
   #include <iostream>
   #include <fstream>
   #include <unistd.h>
   
   
   
   //#include <LogAPI.h>
   
   
   
   
   
   
   
   
   
   
   namespace tsa {
   #define LOG_DEBUG_LEVEL_2 2 
   #define LOG_DEBUG_LEVEL_3 3     
   
   #define LOGH1 "============================================"
   #define LOGH2 "--------------------------------------------"
   
       void LogInfo(const std::string &s, ...);
   
       void LogWarning(const std::string &s, ...);
   
       void LogSevere(const std::string &s, ...);
       void LogSevere(int lvl, const std::string &s, ...);
   
   
       void LogFatal(const std::string &s, ...);
       void LogDebug(int lvl, const std::string &s, ...);
   
   } // end namespace tsa
   
   #endif // __NAPLOG_HPP
