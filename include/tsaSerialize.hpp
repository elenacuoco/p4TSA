///
///   Copyright (C) 2004 by Giancarlo Cella
///   giancarlo.cella@pi.infn.it
///
///   This program is free software; you can redistribute it and/or modify
///   it under the terms of the GNU General Public License as published by
///   the Free Software Foundation; either version 2 of the License, or
///   (at your option) any later version.
///
///   This program is distributed in the hope that it will be useful,
///   but WITHOUT ANY WARRANTY; without even the implied warranty of
///   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
///   GNU General Public License for more details.
///
///   You should have received a copy of the GNU General Public License
///   along with this program; if not, write to the
///   Free Software Foundation, Inc.,
///   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
///
/// @file   tsaSerialize.hpp
/// @author Giancarlo Cella <giancarlo.cella@pi.infn.it>
/// @date   Sat Nov 13 17:21:06 2004
///
///
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

///
/// tsa namespace
///
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
