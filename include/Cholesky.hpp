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
/// @file   Cholesky.hpp
/// @author Elena Cuoco <elena.cuoco@ego-gw.it>
/// @date   2006
///
/// @brief  Implement the Cholesky decomposition 
///
#ifndef __CHOLESKY_HPP
#define __CHOLESKY_HPP


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

    ///
    /** Perform the Cholesky decomposition

        @author Elena Cuoco <elena.cuoco@ego-gw.it>
     */
    ///
    ///

    class Cholesky {
    public:

        ///
        /// Constructor
        ///
        Cholesky(unsigned int N, double eps);

        ///
        /// Copy constructor
        ///
        /// @param from The instance that must be copied
        Cholesky(const Cholesky& from);

        ///
        /// Destructor
        ///
        ~Cholesky();

        ///
        /// Assignement operator
        ///
        /// @param from The instance to be assigned from
        ///
        /// @return a reference to a new object
        Cholesky& operator=(const Cholesky& from);

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
        void execute(Dvector& A, Dvector& B);
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
        unsigned int mN;
        Dvector mD;
        Dvector mY;
        Dmatrix mXL;
        int mIflag;
        double mEps;

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

#endif // __CHOLESKY_HPP



