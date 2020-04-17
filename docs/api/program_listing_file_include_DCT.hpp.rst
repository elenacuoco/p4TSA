
.. _program_listing_file_include_DCT.hpp:

Program Listing for File DCT.hpp
================================

|exhale_lsh| :ref:`Return to documentation for file <file_include_DCT.hpp>` (``include/DCT.hpp``)

.. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS

.. code-block:: none

   
   #ifndef __DCT_HPP
   #define __DCT_HPP
   
   
   
   #include <BaseFFT.hpp>
   #include <SeqView.hpp>
   
   
   
   
   
   
   namespace tsa {
   
       class DCT : public BaseFFT {
       public:
           DCT(int size = 0, enum FFTPlanningMode mode = ESTIMATE, bool PreserveInput = true);
   
           DCT(const DCT& from);
   
           virtual ~DCT();
   
   
           void operator()(SeqViewDouble& in, SeqViewDouble& out);
   
   
           void execute(Dmatrix& in, Dmatrix& out) throw (bad_matrix_size);
   
           void execute(Dvector& in, Dvector& out) throw (bad_vector_size);
   
   
           void MakePlan() throw (std::runtime_error);
   
   
   
   
   
   
   
   
   
   
       protected:
   
       private:
   
   
   
       };
   
   
   
   
   
   
   
   } // end namespace tsa
   
   #endif // __DCT_HPP
