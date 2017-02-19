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
/// @file   AlgoBase.hpp
/// @author Giancarlo Cella <giancarlo.cella@pi.infn.it>
/// @date   Sat Nov 13 17:21:06 2004
///
///
#ifndef __ALGOBASE_HPP
#define __ALGOBASE_HPP

// -- System includes
#include <stdexcept>
#include <iostream>
#include <fstream>
// -- Project includes
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <string>



// -- Local includes
#include <tsaSerialize.hpp>
#include <tsaTypes.hpp>
#include <tsaLog.hpp>
#include <BaseView.hpp>
#include <SeqView.hpp>
#include <AlgoExceptions.hpp>
#include <tsaSerialize.hpp>
// -- Forward references

///
/// tsa namespace
///
namespace tsa {



    ///
    /// @brief AlgoBase is the abstract base class for all algorithm.
    ///
    /// AlgoBase is the abstract base class for all the algorithm classes.
    /// It contain the definition of the common methods. An algorithm is a class
    /// with one or more execute() methods, with a variable number of parameters.
    ///

    class AlgoBase {
    public:


        ///
        /// @name Operations
        ///
        //@{



        //@}

        ///
        /// @name Getters
        ///
        //@{


        //@}

        ///
        /// @name Setters 
        ///
        //@{


        //@}

    protected:


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

#endif // __ALGOBASE_HPP
