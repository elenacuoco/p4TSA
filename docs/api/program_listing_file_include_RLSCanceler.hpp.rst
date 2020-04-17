
.. _program_listing_file_include_RLSCanceler.hpp:

Program Listing for File RLSCanceler.hpp
========================================

|exhale_lsh| :ref:`Return to documentation for file <file_include_RLSCanceler.hpp>` (``include/RLSCanceler.hpp``)

.. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS

.. code-block:: none

   
   #ifndef __RLSCANCELER_HPP
   #define __RLSCANCELER_HPP
   
   
   
   
   
   
   #include <AlgoBase.hpp>
   
   
   
   
   
   
   
   namespace tsa {
   
       class RLSCanceler : public AlgoBase {
       public:
   
           RLSCanceler(unsigned int Order, double delta, double lambda, unsigned int Channels);
   
           RLSCanceler(const RLSCanceler& from);
   
           virtual ~RLSCanceler();
   
           RLSCanceler& operator=(const RLSCanceler& from);
   
           void operator()(SeqViewDouble& InputData, SeqViewDouble& CleanedData);
   
           void operator()(SeqViewDouble& InputData, SeqViewDouble& CleanedData, SeqViewDouble& ReferenceSignal);
   
           void execute(Dmatrix& Input, Dmatrix& Output, Dmatrix& ReferenceSigna);
   
           void execute(Dmatrix& Input, Dmatrix& Output);
   
   
   
           double Getlstart() {
               return mlstart;
           }
   
           double GetWeights(unsigned int j, unsigned int channel) {
               return mWeights(channel, j);
           }
   
   
   
   
   
       protected:
   
       private:
           unsigned int mP; 
           double mdelta; 
           double mlambda; 
           Dmatrix mWeights; 
           Dmatrix mC; 
           Dvector mX; 
           Dvector mM; 
           Dvector mG; 
           double mlstart; 
           double msigma; 
       };
   
   
   
   
   
   
   } //end namespace
   
   #endif // ___RLSCANCELER_HPP
