
.. _program_listing_file_include_eternity_dynamic.hpp:

Program Listing for File dynamic.hpp
====================================

|exhale_lsh| :ref:`Return to documentation for file <file_include_eternity_dynamic.hpp>` (``include/eternity/dynamic.hpp``)

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
   
   #ifndef DYNAMIC_H
   #define DYNAMIC_H
   
   #include <stdio.h>
   #include <typeinfo>
   #include <string>
   
   namespace eternity {
   
       class Ifactory {
       public:
   
           virtual ~Ifactory() {
           };
   
           static Ifactory *m_pHead;
   
           Ifactory *m_pNext;
   
           virtual void* create(std::string& class_name) = 0;
   
           virtual std::string get_conventional_name(std::string& compiler_name) = 0;
       };
   
       template <class t>
       class factory : public Ifactory {
           std::string m_sConventionalName;
   
       public:
           factory();
   
           factory(std::string conventional_name);
   
           virtual ~factory();
   
   
           virtual void* create(std::string& class_name);
   
           virtual std::string get_conventional_name(std::string& compiler_name);
   
       };
   
       template<class t>
       factory<t>::factory() {
           //We are the new m_pHead before the previous one
           m_pNext = m_pHead;
           m_pHead = this;
   
           // set compiler name 
           m_sConventionalName = typeid (t).name();
       }
   
       template<class t>
       factory<t>::factory(std::string conventional_name) : m_sConventionalName(conventional_name) {
           //We are the new m_pHead before the previous one
           m_pNext = m_pHead;
           m_pHead = this;
       }
   
       template<class t>
       void* factory<t>::create(std::string& class_name) {
           return (m_sConventionalName == class_name)
                   ? (void*) (new t)
                   : 0;
       }
   
       template<class t>
       std::string factory<t>::get_conventional_name(std::string& compiler_name) {
           return ( compiler_name == typeid (t).name())
                   ? m_sConventionalName
                   : std::string("");
       }
   
       template<class t>
       factory<t>::~factory() {
           Ifactory **ppNext = &Ifactory::m_pHead;
   
           for (; *ppNext; ppNext = &(*ppNext)->m_pNext) {
               if (*ppNext == this) {
                   *ppNext = (*ppNext)->m_pNext;
                   break;
               }
           }
       }
   
       template<class t>
       void create(std::string cls_name, t** ppObj) {
           Ifactory *pCurrent = Ifactory::m_pHead;
   
           //the follow line reinterpret several times
           //invalid null pointer so compilers could
           //segnal warining.
           for (; pCurrent; pCurrent = pCurrent->m_pNext)
               if ((*ppObj = reinterpret_cast<t*> (pCurrent->create(cls_name))) != NULL) break;
   
       }
   
       std::string get_conventional_name(std::string compiler_name);
   
       class exception : public std::exception {
       protected:
           std::string m_swhat;
       public:
   
           exception(std::string swhat);
   
           exception(const exception& right)
           : m_swhat(right.what()) {
           }
   
           exception& operator=(const exception& right) {
               m_swhat = right.what();
               return *this;
           }
   
           virtual ~exception() throw ();
           virtual const char *what() const throw ();
   
   
       };
   
   
   
   
   
   };
   #endif // DYNAMIC_H
   
