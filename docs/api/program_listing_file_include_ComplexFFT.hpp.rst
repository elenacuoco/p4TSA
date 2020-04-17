
.. _program_listing_file_include_ComplexFFT.hpp:

Program Listing for File ComplexFFT.hpp
=======================================

|exhale_lsh| :ref:`Return to documentation for file <file_include_ComplexFFT.hpp>` (``include/ComplexFFT.hpp``)

.. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS

.. code-block:: none

   
   #ifndef __COMPLEXFFT_HPP
   #define __COMPLEXFFT_HPP
   
   
   
   #include <BaseFFT.hpp>
   
   
   
   
   
   
   namespace tsa {
   
       class ComplexFFT : public BaseFFT {
       public:
   
           enum TransformSign {
               FORWARD, //*< Transform sign = -1
               BACKWARD //*< Transform sign = +1
           };
   
   
           ComplexFFT(int size = 0, enum TransformSign s = FORWARD, enum FFTPlanningMode mode = ESTIMATE, bool PreserveInput = true);
   
           ComplexFFT(const ComplexFFT& from);
   
           ~ComplexFFT();
   
           ComplexFFT& operator=(const ComplexFFT& from);
   
   
           void execute(Cmatrix& in, Cmatrix& out) throw (bad_matrix_size);
   
           void MakePlan() throw (std::runtime_error);
   
   
   
   
   
   
           void SetSign(enum TransformSign s);
   
   
   
       protected:
   
       private:
   
           int mSign; 
       };
   
   
   
   
   
   
   
   } // end namespace tsa
   
   #endif // __COMPLEXFFT_HPP
