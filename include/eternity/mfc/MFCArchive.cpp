//////////////////////////////////////////////////////////////////////
// Eternity persistence system
//////////////////////////////////////////////////////////////////////
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
//////////////////////////////////////////////////////////////////////
// MFCarchive.cpp: implementation of the MFCarchive class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "eternity/mfc/MFCarchive.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

MFCarchive::MFCarchive(Carchive& ar) : m_ar(ar) {
    archive::init();
    m_bloading = ar.is_loading() ? true : false;
}

size_t MFCarchive::write(const void *buffer, size_t size, size_t count) {
    m_ar.write(buffer, size);
    return size;
}

size_t MFCarchive::read(void *buffer, size_t size, size_t count) {
    return m_ar.read(buffer, size);
}
