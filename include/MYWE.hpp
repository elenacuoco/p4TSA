///
///   Copyright (C) 2004 by Elena Cuoco
///   elena.cuoco@ego-gw.it
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
/// @file   MYWE.hpp
/// @author Elena Cuoco <elena.cuoco@ego-gw.it>
/// @date   2006
///
/// @brief  description of MYWE
///
#ifndef __MYWE_HPP
#define __MYWE_HPP


///
/// @name System includes
///
//@{


//@}

///
/// @name Project includes
///
//@{

#include <AlgoBase.hpp>
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
/// namespace
///
namespace tsa {

    ///
    ///
    /// A more detailed description of MYWE
    ///
    ///
    ///

    class MYWE {
    public:

        ///
        /// Constructor
        ///
        MYWE(unsigned int mIP, unsigned int mIQ);

        ///
        /// Destructor
        ///
        ~MYWE();

        ///
        /// Assignement operator
        ///
        /// @param from The instance to be assigned from
        ///
        /// @return a reference to a new object
        MYWE& operator=(const MYWE& from);

        ///
        /// @name Operations
        ///
        ///@{

        ///
        /// @brief Brief documentation for the execute method.
        ///
        /// Start of the long documentation for execute method.
        ///
        /// @pre A precondition
        /// @post A postcondition
        /// @exception An exception
        ///
        /// @param a parameter
        ///
        /// @return a returned value
        ///
        /// Declaration of execute operation
        void execute(Dvector& Corr, Dvector& AR);
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
        unsigned int mIP;
        unsigned int mIQ;
        Dmatrix mA;
        Dmatrix mB;
        Dvector mRho;


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

} //end namespace

#endif // __MYWE_HPP



