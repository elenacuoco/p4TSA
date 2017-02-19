
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
/// @file   BaseView.hpp
/// @author Giancarlo Cella <giancarlo.cella@pi.infn.it>
/// @date   Sat Nov 13 17:21:06 2004
/// 
/// @brief  Base class for Views
/// 
#ifndef __BASEVIEW_HPP
#define __BASEVIEW_HPP

///
/// @name System includes
///
//@{
#include <map>
#include <string>

//@}

///
/// @name Project includes
///
//@{
#include <tsaTypes.hpp>
#include <tsaTraits.hpp>
#include <tsaUtilityFunctions.hpp>
#include <tsaSerialize.hpp>
#include <tsaLog.hpp>
//@}

///
/// @name Local includes
///
//@{


//@}

/// 
/// tsa namespace
///
namespace tsa {


    ///
    /// @name Forward references
    ///
    //@{
    class AlgoBase;
    //@}

    ///

    class BaseView {
    public:
        friend class AlgoBase;
        ///
        /// Constructor
        ///

        BaseView(const std::string& aName = std::string())
        :
        mName(aName) {

        }

        ///
        /// Copy constructor
        ///
        /// @param from The instance that must be copied

        BaseView(const BaseView& from) {
            mName = from.mName;
        }

        ///
        /// Destructor
        ///

        ~BaseView() {

        }

        ///
        /// Assignement operator
        /// 
        /// @param from The instance to be assigned from
        ///
        /// @return a reference to a new object

        BaseView& operator=(const BaseView& from) {
            mName = from.mName;
            return *this;
        }

        ///
        /// @name Operations
        ///
        //@{



        //@}

        ///
        /// @name Getters
        ///
        //@{

        std::string GetName() {
            return mName;
        }


        //@}

        ///
        /// @name Setters
        ///
        //@{

        void SetName(const std::string& aName) {
            mName = aName;
        }


        //@}



    protected:


        std::string mName;

    private:


    };





    ///
    /// @name Inline methods
    ///
    //@{

    //@}


    /// 
    /// @name External references
    ///
    //@{

    //@}


} // end namespace tsa

#endif // __BASEVIEW_HPP
