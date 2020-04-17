
.. _program_listing_file_include_tsaTraits.hpp:

Program Listing for File tsaTraits.hpp
======================================

|exhale_lsh| :ref:`Return to documentation for file <file_include_tsaTraits.hpp>` (``include/tsaTraits.hpp``)

.. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS

.. code-block:: none

   #ifndef __NAPTRAITS_HPP
   #define __NAPTRAITS_HPP
   
   
   #include <complex>
   
   
   
   
   
   
   
   
   
   
   
   
   
   
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
