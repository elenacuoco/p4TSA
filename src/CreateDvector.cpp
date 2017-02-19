//
//
// C++ Implementation: CreateDvector.cpp
//
// Description:
//
//
// Author: Elena Cuoco <elena.cuoco@ego-gw.it>, (C) 2005
//
// Copyright: See COPYING file that comes with this distribution
//
//
//

#include <CreateDvector.hpp>

namespace tsa {

    Dvector create_dvector(int size) {
        Dvector tmp;
        tmp.resize(size);
        return tmp;

    }



}
