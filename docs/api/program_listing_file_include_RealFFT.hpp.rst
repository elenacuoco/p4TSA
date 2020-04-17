
.. _program_listing_file_include_RealFFT.hpp:

Program Listing for File RealFFT.hpp
====================================

|exhale_lsh| :ref:`Return to documentation for file <file_include_RealFFT.hpp>` (``include/RealFFT.hpp``)

.. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS

.. code-block:: none

   
   #ifndef __REALFFT_HPP
   #define __REALFFT_HPP
   
   
   
   #include <BaseFFT.hpp>
   #include <SeqView.hpp>
   
   
   
   
   
   
   namespace tsa {
   
       class RealFFT : public BaseFFT {
       public:
           RealFFT(int size = 0, enum FFTPlanningMode mode = ESTIMATE, bool PreserveInput = true);
   
           RealFFT(const RealFFT& from);
   
           virtual ~RealFFT();
   
   
           void operator()(SeqViewDouble& in, SeqViewComplex& out);
   
   
           void execute(Dmatrix& in, Cmatrix& out) throw (bad_matrix_size);
   
           void execute(Dmatrix& indata, Cmatrix& outdata, unsigned int size, unsigned int offset) throw (bad_matrix_size);
   
   
           void execute(Dvector& in, Cvector& out) throw (bad_vector_size);
   
   
           void MakePlan() throw (std::runtime_error);
   
   
   
   
   
   
   
   
   
   
       protected:
   
       private:
   
   
   
       };
   
   
   
   
   
   
   
   } // end namespace tsa
   
   #endif // __REALFFT_HPP
