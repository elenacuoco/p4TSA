
.. _program_listing_file_include_tsaUtilityFunctions.hpp:

Program Listing for File tsaUtilityFunctions.hpp
================================================

|exhale_lsh| :ref:`Return to documentation for file <file_include_tsaUtilityFunctions.hpp>` (``include/tsaUtilityFunctions.hpp``)

.. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS

.. code-block:: none

   #ifndef __NAPUTILITYFUNCTIONS_HPP
   #define __NAPUTILITYFUNCTIONS_HPP
   
   
   #include <string.h>
   #include <fparser.hpp>
   #include <complex>
   
   
   
   
   
   
   
   #include <fstream>
   
   
   
   
   
   
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
   
   #endif // __NAPUTILITYFUNCTIONS_HPP
