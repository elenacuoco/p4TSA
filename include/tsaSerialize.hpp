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
#include "tsaTypes.hpp"



// -- Local includes

// -- Forward references

///
/// tsa namespace
///
/// `Tag()` is a small XML-tag-name formatting helper, kept (and still bound
/// to Python, see pytsa.cpp) even though its original caller -- the
/// DVECTOR_XML_SERIALIZE/DMATRIX_XML_SERIALIZE/BOOL_XML_SERIALIZE macros
/// this file used to also define, wrapping the now-removed `eternity` XML
/// persistence framework -- is gone (see CerealPersistence.hpp for the
/// modern replacement, plain Cereal `serialize()` members, no string tags
/// needed).
///
namespace tsa {

    extern char* Tag(char *buffer, int n, const char* base, const char* rec);
    extern char* Tag(char *buffer, int n, const char* base, const char* rec, unsigned int i);
    extern char* Tag(char *buffer, int n, const char* base, const char* rec, unsigned int i, unsigned int j);

} // end namespace tsa

#endif // __SERIALIZE_HPP
