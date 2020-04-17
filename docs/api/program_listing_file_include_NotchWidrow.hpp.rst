
.. _program_listing_file_include_NotchWidrow.hpp:

Program Listing for File NotchWidrow.hpp
========================================

|exhale_lsh| :ref:`Return to documentation for file <file_include_NotchWidrow.hpp>` (``include/NotchWidrow.hpp``)

.. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS

.. code-block:: none

   
   #ifndef __NOTCHWIDROW_HPP
   #define __NOTCHWIDROW_HPP
   
   
   
   
   
   #include <AlgoBase.hpp>
   #include <SeqView.hpp>
   
   
   
   
   
   
   
   namespace tsa {
   
       class NotchWidrow : public AlgoBase {
       public:
   
           NotchWidrow(unsigned int channels, Dmatrix& FrequencyList, double C = 1.0);
   
           NotchWidrow(const NotchWidrow& from);
   
           virtual ~NotchWidrow();
   
   
           void operator()(SeqViewDouble& InputData, SeqViewDouble& CleanedData);
   
           void operator()(SeqViewDouble& InputData, SeqViewDouble& CleanedData, SeqViewDouble& ReferenceSignal);
           NotchWidrow& operator=(const NotchWidrow& from);
   
   
           void execute(Dmatrix& Input, Dmatrix& Output);
   
   
   
           double Getlstart() {
               return mlstart;
           }
   
   
   
   
   
       protected:
   
       private:
           Dmatrix mFrequencyList; // The Frequency list containing the frequency and the Q
           Dmatrix mWeight1;
           Dmatrix mWeight2;
           Dvector mX1;
           Dvector mX2;
           Dvector mCs;
           Dvector mSn;
           double mlstart;
           Dmatrix mRefSign;
           double mAmp;
   
       };
   
   
   
   
   
   
   
   } //end namespace
   
   #endif // ___NOTCHWIDROW_HPP
   
   
   
