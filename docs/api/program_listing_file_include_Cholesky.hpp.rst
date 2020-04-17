
.. _program_listing_file_include_Cholesky.hpp:

Program Listing for File Cholesky.hpp
=====================================

|exhale_lsh| :ref:`Return to documentation for file <file_include_Cholesky.hpp>` (``include/Cholesky.hpp``)

.. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS

.. code-block:: none

   #ifndef __CHOLESKY_HPP
   #define __CHOLESKY_HPP
   
   
   
   
   
   
   
   
   #include <AlgoBase.hpp>
   
   
   
   
   
   
   
   
   
   namespace tsa {
   
   
   
   
       class Cholesky {
       public:
   
           Cholesky(unsigned int N, double eps);
   
           Cholesky(const Cholesky& from);
   
           ~Cholesky();
   
           Cholesky& operator=(const Cholesky& from);
   
   
           void execute(Dvector& A, Dvector& B);
   
   
   
   
   
   
   
   
       protected:
   
       private:
           unsigned int mN;
           Dvector mD;
           Dvector mY;
           Dmatrix mXL;
           int mIflag;
           double mEps;
   
       };
   
   
   
   
   
   
   
   
   } //end namespace
   
   #endif // __CHOLESKY_HPP
   
   
   
