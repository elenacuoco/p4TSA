
.. _program_listing_file_include_LeastSquaresLattice.hpp:

Program Listing for File LeastSquaresLattice.hpp
================================================

|exhale_lsh| :ref:`Return to documentation for file <file_include_LeastSquaresLattice.hpp>` (``include/LeastSquaresLattice.hpp``)

.. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS

.. code-block:: none

   
   #ifndef __LEASTSQUARESLATTICE_HPP
   #define __LEASTSQUARESLATTICE_HPP
   
   
   
   
   
   
   #include <AlgoBase.hpp>
   #include <LSLLearning.hpp>
   
   
   
   
   
   
   
   using namespace boost::numeric::ublas;
   
   namespace tsa {
   
       class LeastSquaresLattice : public AlgoBase {
       public:
   
           LeastSquaresLattice(matrix_row<Dmatrix>& LearnData,
                   matrix_row<Dmatrix>& WhitenData,
                   unsigned int P, double lambda, unsigned int D);
   
   
           virtual ~LeastSquaresLattice();
   
           LeastSquaresLattice& operator=(const LeastSquaresLattice& from);
   
   
           void execute(Dvector& Input, Dvector& Output);
   
   
   
   
   
   
       protected:
   
       private:
           unsigned int mOrder;
           unsigned int mLwsp;
           double mLambda;
           Dmatrix mLast;
           unsigned mDirection;
           unsigned int mStep;
           LSLLearning mLSLlearn;
   
       };
   
   
   
   
   
   
   } //end namespace
   
   #endif // ___LEASTSQUARESLATTICE_HPP
