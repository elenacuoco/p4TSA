
.. _program_listing_file_include_IDCT.hpp:

Program Listing for File IDCT.hpp
=================================

|exhale_lsh| :ref:`Return to documentation for file <file_include_IDCT.hpp>` (``include/IDCT.hpp``)

.. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS

.. code-block:: none

   
   #ifndef __IDCT_HPP
   #define __IDCT_HPP
   
   
   
   #include <BaseFFT.hpp>
   #include <SeqView.hpp>
   
   
   
   
   
   
   namespace tsa {
   
       class IDCT : public BaseFFT {
       public:
           IDCT(int size = 0, enum FFTPlanningMode mode = ESTIMATE, bool PreserveInput = true);
   
           IDCT(const IDCT& from);
   
           virtual ~IDCT();
   
   
           void operator()(SeqViewDouble& in, SeqViewDouble& out);
   
   
           void execute(Dmatrix& in, Dmatrix& out) throw (bad_matrix_size);
   
           void execute(Dvector& in, Dvector& out) throw (bad_vector_size);
   
   
           void MakePlan() throw (std::runtime_error);
   
   
   
   
   
   
   
   
   
   
       protected:
   
       private:
   
   
   
       };
   
   
   
   
   
   
   
   } // end namespace tsa
   
   #endif // __IDCT_HPP
