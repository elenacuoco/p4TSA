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
/// @file   tsatsaUtilityFunctions.hpp
/// @author Giancarlo Cella <giancarlo.cella@pi.infn.it>
/// @date   Sat Nov 13 17:21:06 2004
/// 
/// @brief  Define some tsa Utility Functions
/// 
#ifndef __TSAUTILITYFUNCTIONS_HPP
#define __TSAUTILITYFUNCTIONS_HPP

///
/// @name System includes
///
//@{
#include <string.h>
#include <fparser.hpp>
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
#include <fstream>

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

    extern std::string tsaVersion();

    extern std::complex<double>CRATIO(std::complex<double> v1, std::complex<double> v2);

    extern void DmatrixPrint(const Dmatrix& m, const char *filename, bool transpose = false);

    class ParseParameterString {
    public:

        ParseParameterString(const std::string& parlist) {
            mParList = new char[parlist.size() + 1];
            mTmp = new char[parlist.size() + 1];
            strcpy(mParList, parlist.c_str());
        }

        ~ParseParameterString() {
            delete mParList;
        }

        double GetFloat(int n) {
            int k = 0;
            strcpy(mTmp, mParList);
            char *p = strtok(mTmp, " ");
            while (p != NULL) {
                if (k == n) {
                    fparser.Parse(p, "");
                    return fparser.Eval(0);
                }
                p = strtok(NULL, " ");
                k++;
            }
            return 0;
        }

        int GetInt(int n) {
            int k = 0;
            strcpy(mTmp, mParList);
            char *p = strtok(mTmp, " ");
            while (p != NULL) {
                if (k == n) {
                    fparser.Parse(p, "");
                    return (int) fparser.Eval(0);
                }
                p = strtok(NULL, " ");
                k++;
            }
            return 0;
        }

        std::string GetString(int n) {
            int k = 0;
            strcpy(mTmp, mParList);
            char *p = strtok(mTmp, " ");
            while (p != NULL) {
                if (k == n) {
                    return std::string(p);
                }
                p = strtok(NULL, " ");
                k++;
            }
            return 0;
        }




    private:
        FunctionParser fparser;
        char *mParList;
        char *mTmp;
    };

    class MathUtils {
    public:

        /** 
         * Evaluate the integer square root of a number.
         * 
         * @param val input number
         * 
         * @return integer square root of val
         */
        static unsigned int isqrt(unsigned long val) {
            unsigned long temp, g = 0, b = 0x8000, bshft = 15;
            do {
                if (val >= (temp = (((g << 1) + b) << bshft--))) {
                    g += b;
                    val -= temp;
                }
            } while (b >>= 1);
            return g;
        };

        /** 
         * Find the great common divisor between two numbers u and v
         * 
         * @param u first number
         * @param v second number
         * 
         * @return the great common divisor between u and v
         */
        static int gcd(int u, int v) {
            int t;
            while (u > 0) {
                if (u < v) {
                    t = u;
                    u = v;
                    v = t;
                }
                u = u - v;
            }
            return v;
        };

        static int max(int u, int v) {
            return (u > v) ? u : v;
        };

        static int min(int u, int v) {
            return (u < v) ? u : v;
        }


    };

    class UpperTriangular {
    public:

        static unsigned int Map(unsigned int i, unsigned int j, unsigned int dim) {
            return i * dim - i * (i + 1) / 2 + j;
        };

        static unsigned int Size(unsigned int dim) {
            return dim * (dim + 1) / 2;
        };

        static unsigned int Dimension(unsigned int sz) {
            return (-1 + MathUtils::isqrt(1 + 8 * sz)) / 2;
        };
    private:

    };

    class LowerTriangular {
    public:

        static unsigned int Map(unsigned int i, unsigned int j, unsigned int) {
            return i * (i + 1) / 2 + j;
        };

        static unsigned int Size(unsigned int dim) {
            return dim * (dim + 1) / 2;
        };

        static unsigned int Dimension(unsigned int sz) {
            return (-1 + MathUtils::isqrt(1 + 8 * sz)) / 2;
        };


    };

    class StrictUpperTriangular {
    public:

        static unsigned int Map(unsigned int i, unsigned int j, unsigned int dim) {
            return (i - 1)*(dim - 1)-(i - 1)*(i - 2) / 2 + j - 1;
        };

        static unsigned int Size(unsigned int dim) {
            return dim * (dim - 1) / 2;
        };

        static unsigned int Dimension(unsigned int sz) {
            return (1 + MathUtils::isqrt(1 + 8 * sz)) / 2;
        };

    };

    class StrictLowerTriangular {
    public:

        static unsigned int Map(unsigned int i, unsigned int j, unsigned int) {
            return i * (i - 1) / 2 + (j - 1);
        };

        static unsigned int Size(unsigned int dim) {
            return dim * (dim - 1) / 2;
        };

        static unsigned int Dimension(unsigned int sz) {
            return (-1 + MathUtils::isqrt(1 + 8 * sz)) / 2;
        };
    };

    class Square {
    public:

        static unsigned int Map(unsigned int i, unsigned int j, unsigned lda) {
            return i * lda + j;
        };

        static unsigned int Size(unsigned int dim) {
            return dim*dim;
        };

        static unsigned int Dimension(unsigned int sz) {
            return MathUtils::isqrt(sz);
        };

    };

    class GetRe {
    public:

        template<typename T>
        static double convert_double(const T& value) {
            return TypeTraits< T >::real(value);
        }
    };

    class GetIm {
    public:

        template<typename T>
        static double convert_double(const T& value) {
            return TypeTraits< T >::imag(value);
        }

    };

    class GetAbs {
    public:

        template<typename T>
        static double convert_double(const T& value) {
            return TypeTraits< T >::abs(value);
        }

    };

    class GetAbs2 {
    public:

        template<typename T>
        static double convert_double(const T& value) {
            return TypeTraits< T >::abs2(value);
        }

    };

    class GetPhase {
    public:

        template<typename T>
        static double convert_double(const T& value) {
            return TypeTraits< T >::phase(value);
        }

    };






} // end namespace tsa

#endif // __TSAUTILITYFUNCTIONS_HPP
