
.. _program_listing_file_include_eternity_MFCArchive.h:

Program Listing for File MFCArchive.h
=====================================

|exhale_lsh| :ref:`Return to documentation for file <file_include_eternity_MFCArchive.h>` (``include/eternity/MFCArchive.h``)

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
   // MFCarchive.h: interface for the MFCarchive class.
   //
   
   #if !defined(AFX_MFCARCHIVE_H__F2817351_A251_11D3_8D8C_00104B92DE46__INCLUDED_)
   #define AFX_MFCARCHIVE_H__F2817351_A251_11D3_8D8C_00104B92DE46__INCLUDED_
   
   #if _MSC_VER > 1000
   #pragma once
   #endif // _MSC_VER > 1000
   
   #include "../persist.hpp"
   using namespace eternity;
   
   class MFCarchive : public bin_archive {
   public:
       virtual size_t write(const void *buffer, size_t size, size_t count);
       virtual size_t read(void *buffer, size_t size, size_t count);
   
       MFCarchive(Carchive& ar);
   
       virtual ~MFCarchive() {
       }
   protected:
       Carchive& m_ar;
   };
   
   #endif // !defined(AFX_MFCARCHIVE_H__F2817351_A251_11D3_8D8C_00104B92DE46__INCLUDED_)
