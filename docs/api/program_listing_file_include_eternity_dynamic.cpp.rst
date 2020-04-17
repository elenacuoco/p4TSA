
.. _program_listing_file_include_eternity_dynamic.cpp:

Program Listing for File dynamic.cpp
====================================

|exhale_lsh| :ref:`Return to documentation for file <file_include_eternity_dynamic.cpp>` (``include/eternity/dynamic.cpp``)

.. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS

.. code-block:: none

   // Eternity persistence system
   // 
   // 1999-2003 Nicola Santi.
   //
   // This software is released under the terms of Eternity Artistic 
   // License. Please read the file eternity-licence to learn details. 
   // 
   // The above copyright notice and this permission notice shall be included
   // in all copies or substantial portions of the Software.
   
   // THIS PACKAGE IS PROVIDED "AS IS" AND WITHOUT ANY EXPRESS OR
   // IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
   // WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
   //
   // Except as contained in this notice, the name of Nicola Santi
   // shall not be used in advertising or otherwise to promote the sale, 
   // use or other dealings in this Software without prior written 
   // authorization from Nicola Santi.
   
   #include "dynamic.hpp"
   
   namespace eternity {
       /*static*/ Ifactory *Ifactory::m_pHead = 0;
   
       std::string get_conventional_name(std::string compiler_name) {
           std::string conventional_name;
           Ifactory *pCurrent = Ifactory::m_pHead;
   
           for (; pCurrent; pCurrent = pCurrent->m_pNext) {
               conventional_name = pCurrent->get_conventional_name(compiler_name);
               if (!conventional_name.empty()) break;
           }
   
           return conventional_name;
       }
   
       /* move here to fix bcc32 Warning W8026 */
       eternity::exception::exception(std::string swhat) : m_swhat(swhat) {
       };
   
       eternity::exception::~exception() throw () {
       }
   
       const char* eternity::exception::what() const throw () {
           return m_swhat.c_str();
       }
   
   
   }
   
   
   
   
   
   
   
   
   
