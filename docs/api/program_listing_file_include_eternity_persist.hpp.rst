
.. _program_listing_file_include_eternity_persist.hpp:

Program Listing for File persist.hpp
====================================

|exhale_lsh| :ref:`Return to documentation for file <file_include_eternity_persist.hpp>` (``include/eternity/persist.hpp``)

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
   
   #ifndef PERSIST_H
   #define PERSIST_H
   
   #include "dynamic.hpp"
   
   #include <math.h>
   #include <stdlib.h>
   
   #include <vector>
   #include <algorithm>
   #include <fstream>
   
   
   
   namespace eternity {
   
       class bin_archive;
   
       class archive {
       protected:
           bool m_bloading;
           std::vector<void*> m_vPointerstored;
   
       public:
   
           enum opening_mode {
               load, store        };
   
   
           archive() : m_bloading(true) {
           }
   
           void init() {
               m_vPointerstored.clear();
               m_vPointerstored.push_back(NULL);
               m_bloading = true;
           }
   
           int put_pointer(void* object);
   
   
           bool set_loading(bool val) {
               return m_bloading = val;
           }
   
           bool is_loading() {
               return m_bloading;
           }
   
           bool is_storing() {
               return !m_bloading;
           }
   
   
       };
   
       class bin_archive : public archive {
       public:
   
           virtual ~bin_archive() {
           }
   
           virtual size_t write(const void *buffer, size_t size, size_t count) = 0;
           virtual size_t read(void *buffer, size_t size, size_t count) = 0;
   
           template <class T>
           bin_archive& operator<<(T& ogg) {
               if (is_loading()) throw eternity::exception("write attempt on an archive open for loading.");
               write(&ogg, sizeof (ogg), 1);
               return (*this);
           }
   
           template <class T>
           bin_archive& operator>>(T& ogg) {
               if (!is_loading()) throw eternity::exception("read attempt on an archive open for storing.");
               read(&ogg, sizeof (ogg), 1);
               return (*this);
           }
   
           bin_archive& operator<<(std::string& str);
   
   
           bin_archive& operator>>(std::string& str);
   
   
           template<class t>
           t* get_object(t** ppObj) {
               std::string cls_name;
               *ppObj = NULL;
   
               operator>>(cls_name);
   
               if ("NULL" != cls_name) {
                   create(cls_name, ppObj);
   
                   if (NULL != (*ppObj)) {
                       m_vPointerstored.push_back(*ppObj);
                       (*ppObj)->serialize(*this);
                   }
   
   
               } else {
                   int pos = 0;
   
                   operator>>(pos);
   
                   *ppObj = static_cast<t*> (m_vPointerstored[pos]);
   
               }
   
               return *ppObj;
           }
   
   
           template <class t>
           t* put_object(t* pObj) {
               int pos = put_pointer(pObj);
   
               if (pos == -1) {
                   //New Object, we have to full serialize it  
                   std::string str = get_conventional_name(typeid (*pObj).name());
                   if (str.empty()) str = typeid (*pObj).name();
                   operator<<(str);
                   pObj->serialize(*this);
               } else {
                   //Object in list, yet. Only store position
                   std::string str = "NULL";
                   operator<<(str);
                   operator<<(pos);
               }
   
               return pObj;
           }
       };
   
       class file_archive : public bin_archive {
           std::fstream stream;
       public:
   
           file_archive() {
               stream.exceptions(std::ios::failbit | std::ios::eofbit | std::ios::badbit);
           }
   
           file_archive(std::string file_name, opening_mode mode);
   
           ~file_archive() {
               close();
           }
   
   
           void close() {
   
               if (stream.is_open()) {
                   stream.close();
               }
   
               archive::init();
           }
   
           void open(std::string file_name, opening_mode mode);
   
           void open(std::string sName, bool loading = true);
   
           virtual size_t write(const void *buffer, size_t size, size_t count);
   
           virtual size_t read(void *buffer, size_t size, size_t count);
       };
   
   
   }
   #endif // PERSIST_H
