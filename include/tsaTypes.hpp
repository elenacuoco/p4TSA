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
/// @file   tsaTypes.hpp
/// @author Giancarlo Cella <giancarlo.cella@pi.infn.it>
/// @date   Sat Nov 13 17:21:06 2004
///
/// @brief  Define the tsa types
///
#ifndef __NAPTYPES_HPP
#define __NAPTYPES_HPP

///
/// @name System includes
///
//@{
#include <fstream>

#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/matrix_proxy.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <eternity.hpp>

//@}

///
/// @name Project includes
///
//@{

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

    typedef std::complex<double> Cdouble;

    // Arrays
    typedef boost::numeric::ublas::matrix<int> Imatrix;
    typedef boost::numeric::ublas::matrix<unsigned int> UImatrix;
    typedef boost::numeric::ublas::matrix<double> Dmatrix;


    typedef boost::numeric::ublas::matrix< std::complex<double> > Cmatrix;

    // Vectors
    typedef boost::numeric::ublas::vector<int> Ivector;
    typedef boost::numeric::ublas::vector<unsigned int> UIvector;


    typedef boost::numeric::ublas::vector< double > Dvector;
    typedef boost::numeric::ublas::vector< long double > LDvector;




    typedef boost::numeric::ublas::vector< std::complex<double> > Cvector;

    // Vectors of arrays
    typedef std::vector< Cmatrix > VCmatrix;
    typedef std::vector< Dmatrix > VDmatrix;

    // Matrix rows
    typedef boost::numeric::ublas::matrix_row<Dmatrix> DmatrixRow;
    typedef boost::numeric::ublas::matrix_column<Dmatrix> DmatrixCol;

    typedef boost::numeric::ublas::matrix_row<Cmatrix> CmatrixRow;
    typedef boost::numeric::ublas::matrix_column<Cmatrix> CmatrixCol;


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

#endif // __NAPTYPES_HPP
