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
/// @file   tsaTraits.hpp
/// @author Giancarlo Cella <giancarlo.cella@pi.infn.it>
/// @date   Sat Nov 13 17:21:06 2004
/// 
/// @brief  Define the  tsa Traits
/// 
#ifndef __NAPTRAITS_HPP
#define __NAPTRAITS_HPP

///
/// @name System includes
///
//@{
#include <complex>

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

    template<typename T>
    class ViewTraits;


    template<typename T>
    class TypeTraits;

    template<>
    class TypeTraits<double> {
    public:

        static double conj(const double& x) {
            return x;
        };

        static double real(const double& x) {
            return x;
        };

        static double imag(const double&) {
            return 0.0;
        };

        static double abs(const double& x) {
            return fabs(x);
        };

        static double abs2(const double& x) {
            return x*x;
        };

        static double phase(const double& x) {
            return (x > 0.0) ? 0.0 : M_PI;
        };
    };

    template<>
    class TypeTraits< std::complex<double> > {
    public:

        static std::complex<double> conj(const std::complex<double>& x) {
            return conj(x);
        };

        static double real(const std::complex<double>& x) {
            return x.real();
        };

        static double imag(const std::complex<double>& x) {
            return x.imag();
        };

        static double abs(std::complex<double> x) {
            return abs(x);
        };

        static double abs2(const std::complex<double>& x) {
            return x.real() * x.real() + x.imag() * x.imag();
        };

        static double phase(const std::complex<double>& x) {
            return arg(x);
        };

    };




} // end namespace tsa

#endif // __NAPTRAITS_HPP
