
.. _program_listing_file_include_InverseRealFFT.hpp:

Program Listing for File InverseRealFFT.hpp
===========================================

|exhale_lsh| :ref:`Return to documentation for file <file_include_InverseRealFFT.hpp>` (``include/InverseRealFFT.hpp``)

.. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS

.. code-block:: none

   
   #ifndef __INVERSEREALFFT_HPP
   #define __INVERSEREALFFT_HPP
   
   
   
   #include <BaseFFT.hpp>
   
   
   
   
   
   namespace tsa {
   
       class InverseRealFFT : public BaseFFT {
       public:
           InverseRealFFT(int size = 0, enum FFTPlanningMode mode = ESTIMATE, bool PreserveInput = false);
   
           InverseRealFFT(const InverseRealFFT& from);
   
           ~InverseRealFFT();
   
   
   
           void operator()(SeqViewComplex& in, SeqViewDouble& out);
   
   
           void execute(Cmatrix& in, Dmatrix& out) throw (bad_matrix_size);
   
   
           void execute(Cvector& in, Dvector& out) throw (bad_vector_size);
   
           void execute(CmatrixRow& in, DmatrixRow& out) throw (bad_vector_size);
   
           void execute(CmatrixRow& in, DmatrixRow& out, unsigned int insize) throw (bad_vector_size);
   
   
           void MakePlan() throw (std::runtime_error);
   
   
   
   
   
   
   
   
   
       protected:
   
       private:
   
   
       };
   
   
   
   
   
   
   
   } // end namespace tsa
   
   #endif // __INVERSEREALFFT_HPP
