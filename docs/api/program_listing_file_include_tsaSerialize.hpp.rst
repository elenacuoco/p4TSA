
.. _program_listing_file_include_tsaSerialize.hpp:

Program Listing for File tsaSerialize.hpp
=========================================

|exhale_lsh| :ref:`Return to documentation for file <file_include_tsaSerialize.hpp>` (``include/tsaSerialize.hpp``)

.. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS

.. code-block:: none

   #ifndef __SERIALIZE_HPP
   #define __SERIALIZE_HPP
   
   // -- System includes
   #include <stdexcept>
   #include <iostream>
   #include <fstream>
   // -- Project includes
   #include "eternity.hpp"
   #include "tsaTypes.hpp"
   
   
   
   // -- Local includes
   
   // -- Forward references
   
   namespace tsa {
   
       extern char* Tag(char *buffer, int n, const char* base, const char* rec);
       extern char* Tag(char *buffer, int n, const char* base, const char* rec, unsigned int i);
       extern char* Tag(char *buffer, int n, const char* base, const char* rec, unsigned int i, unsigned int j);
   
   
   
   #define DVECTOR_XML_SERIALIZE(v,xml,tag)         \
     if( (xml).is_loading() ) {           \
       unsigned int sz = 0;           \
       char b[1024]; \
       (xml).read(Tag(b,1024,(tag),"size"),sz,0);          \
       (v).resize(sz);            \
       for(unsigned int i=0;i<sz;i++) {          \
         (xml).read(Tag(b,1024,(tag),"e",i),(v)(i),0);         \
       }              \
     } else   { \
       char b[1024];            \
       (xml).write(Tag(b,1024,(tag),"size"),(v).size());         \
       for(unsigned int i=0;i<(v).size();i++) {         \
         (xml).write(Tag(b,1024,(tag),"e",i),(v)(i));         \
       }              \
     }              
   
   
   
   
   #define DMATRIX_XML_SERIALIZE(m,xml,tag)         \
     if( (xml).is_loading() )  {           \
       unsigned int sz1 = 0;           \
       unsigned int sz2 = 0;           \
       char b[1024]; \
       (xml).read(Tag(b,1024,(tag),"size1"),sz1,0);         \
       (xml).read(Tag(b,1024,(tag),"size2"),sz2,0);         \
       (m).resize(sz1,sz2);           \
       for(unsigned int i=0;i<sz1;i++) {          \
         for(unsigned int j=0;j<sz2;j++) {          \
           (xml).read(Tag(b,1024,(tag),"e",i,j),(m)(i,j),0);        \
         }              \
       }              \
     } else {             \
       char b[1024]; \
       (xml).write(Tag(b,1024,(tag),"size1"),(m).size1());        \
       (xml).write(Tag(b,1024,(tag),"size2"),(m).size2());        \
       for(unsigned int i=0;i<(m).size1();i++) {         \
         for(unsigned int j=0;j<(m).size2();j++) {         \
           (xml).write(Tag(b,1024,(tag),"e",i,j),(m)(i,j));        \
         }              \
       }              \
     }              
   
   
   
   #define BOOL_XML_SERIALIZE(m,xml,tag)         \
     if( (xml).is_loading() )  {           \
       int tmp;             \
       (xml).read(tag,tmp,0);         \
       m = bool(tmp); \
       } else {   \
       int tmp;   \
       tmp = int(m); \
       (xml).write(tag,tmp); \
     }              
   
   
   
   } // end namespace tsa
   
   #endif // __SERIALIZE_HPP
