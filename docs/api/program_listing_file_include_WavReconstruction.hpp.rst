
.. _program_listing_file_include_WavReconstruction.hpp:

Program Listing for File WavReconstruction.hpp
==============================================

|exhale_lsh| :ref:`Return to documentation for file <file_include_WavReconstruction.hpp>` (``include/WavReconstruction.hpp``)

.. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS

.. code-block:: none

   #ifndef __WAVRECONSTRUCTION_HPP
   #define __WAVRECONSTRUCTION_HPP
   
   
   
   
   
   
   
   #include <AlgoBase.hpp>
   #include <WaveletTransform.hpp>
   #include <SeqView.hpp>
   #include <AlgoExceptions.hpp>
   #include <WaveletThreshold.hpp>
   
   
   
   
   
   
   
   
   
   namespace tsa {
   
   
       class WavReconstruction : public AlgoBase {
       public:
   
           WavReconstruction(unsigned int N, enum WaveletTransform::WaveletType F, double Th);
   
   
           ~WavReconstruction();
   
   
           void operator()(SeqViewDouble& InputData);
   
           void execute(Dmatrix& buffer);
   
   
   
   
   
   
   
   
       protected:
   
       private:
           unsigned int mN;
           Dmatrix mBuff;
           enum WaveletTransform::WaveletType mWt;
           WaveletTransform mWT;
           enum WaveletThreshold::WaveletThresholding mT;
           WaveletThreshold mWavThres;
   
       };
   
   
   
   
   
   
   
   
   } //end namespace
   
   #endif // ___WAVRECONSTRUCTION_HPP
   
   
   
