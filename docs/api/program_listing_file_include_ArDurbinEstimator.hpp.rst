
.. _program_listing_file_include_ArDurbinEstimator.hpp:

Program Listing for File ArDurbinEstimator.hpp
==============================================

|exhale_lsh| :ref:`Return to documentation for file <file_include_ArDurbinEstimator.hpp>` (``include/ArDurbinEstimator.hpp``)

.. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS

.. code-block:: none

   
   #ifndef __ARDURBINESTIMATOR_HPP
   #define __ARDURBINESTIMATOR_HPP
   
   
   #include <boost/numeric/ublas/matrix.hpp>
   
   
   
   
   
   #include <AlgoBase.hpp>
   
   
   
   
   
   
   
   using namespace boost::numeric::ublas;
   
   
   namespace tsa {
   
       class ArDurbinEstimator : public AlgoBase {
       public:
   
           ArDurbinEstimator(unsigned int ArOrder);
   
   
           virtual~ArDurbinEstimator();
   
   
   
   
   
           void execute(Dvector& AutoCorr, Dvector& ArParcor);
   
   
           unsigned int GetArOrder() {
               return mArOrder;
           }
   
   
   
           void SetArOrder(unsigned int P) {
               mArOrder = P + 1;
           }
   
   
   
       protected:
   
       private:
           unsigned int mArOrder;
   
       };
   
   
   
   
   
   
   } //end namespace
   
   #endif // __ARDURBINESTIMATOR_HPP
   
   
