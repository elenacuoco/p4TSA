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
/// @file   tsaLog.hpp
/// @author Giancarlo Cella <giancarlo.cella@pi.infn.it>
/// @date   Sat Nov 13 17:21:06 2004
/// 
/// @brief  Interface for tsaLog
/// 
#ifndef __NAPLOG_HPP
#define __NAPLOG_HPP


#define RLOG_COMPONENT tsa

///
/// @name System includes
///
//@{
#include <iostream>
#include <fstream>
#include <unistd.h>
//@}

///
/// @name Project includes
///
//@{

//#include <LogAPI.h>

//@}

///
/// @name Local includes
///
//@{


//@}

///
/// @name Forward references
///
//@{


//@}

/// 
/// tsa namespace
///
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
