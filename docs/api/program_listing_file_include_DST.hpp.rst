
.. _program_listing_file_include_DST.hpp:

Program Listing for File DST.hpp
================================

|exhale_lsh| :ref:`Return to documentation for file <file_include_DST.hpp>` (``include/DST.hpp``)

.. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS

.. code-block:: none

   
   #ifndef __DST_HPP
   #define __DST_HPP
   
   
   
   #include <BaseFFT.hpp>
   #include <SeqView.hpp>
   
   
   
   
   
   
   namespace tsa {
   
       class DST : public BaseFFT {
       public:
           DST(int size = 0, enum FFTPlanningMode mode = ESTIMATE, bool PreserveInput = true);
   
           DST(const DST& from);
   
           virtual ~DST();
   
   
           void operator()(SeqViewDouble& in, SeqViewDouble& out);
   
   
           void execute(Dmatrix& in, Dmatrix& out) throw (bad_matrix_size);
   
           void execute(Dvector& in, Dvector& out) throw (bad_vector_size);
   
   
           void MakePlan() throw (std::runtime_error);
   
   
   
   
   
   
   
   
   
   
       protected:
   
       private:
   
   
   
       };
   
   
   
   
   
   
   
   } // end namespace tsa
   
   #endif // __DST_HPP
