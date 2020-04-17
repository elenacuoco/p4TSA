
.. _program_listing_file_include_TF2Psd.hpp:

Program Listing for File TF2Psd.hpp
===================================

|exhale_lsh| :ref:`Return to documentation for file <file_include_TF2Psd.hpp>` (``include/TF2Psd.hpp``)

.. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS

.. code-block:: none

   
   #ifndef __TF2PSD_HPP
   #define __TF2PSD_HPP
   
   
   
   
   #include <AlgoBase.hpp>
   
   
   
   
   
   
   
   
   namespace tsa {
   
       class TF2PSD : public AlgoBase {
       public:
   
           TF2PSD(bool squared = false) {
               mSquaredFlag = squared;
           };
   
           TF2PSD(const TF2PSD& from) {
               mSquaredFlag = from.mSquaredFlag;
           };
   
           virtual ~TF2PSD() {
   
           };
   
           TF2PSD& operator=(const TF2PSD& from) {
               mSquaredFlag = from.mSquaredFlag;
               return *this;
           }
   
   
           void execute(Cmatrix& tf, Dmatrix& psd) throw (bad_matrix_size) {
               if (
                       (tf.size1() != psd.size1())
                       ||
                       (tf.size2() != psd.size2())) {
   
                   throw bad_matrix_size("TF2PSD::execute");
               }
   
               if (mSquaredFlag) {
   
                   for (unsigned int i = 0; i < psd.size1(); i++) {
                       for (unsigned int j = 0; j < psd.size2(); j++) {
                           psd(i, j) = 2.0 * (tf(i, j).real() * tf(i, j).real() + tf(i, j).imag() * tf(i, j).imag());
                       }
                   }
   
               } else {
   
                   for (unsigned int i = 0; i < psd.size1(); i++) {
                       for (unsigned int j = 0; j < psd.size2(); j++) {
                           psd(i, j) = abs(2.0 * tf(i, j));
                       }
                   }
               }
   
           }
   
   
   
           bool GetSquared() {
               return mSquaredFlag;
           };
   
   
   
           void SetSquared(bool squared = true) {
               mSquaredFlag = squared;
           };
   
   
       protected:
   
       private:
   
           bool mSquaredFlag;
       };
   
   
   
   
   
   
   
   } // end namespace tsa
   
   #endif // __TF2PSD_HPP
