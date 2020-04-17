
.. _program_listing_file_include_WaveletTransform.hpp:

Program Listing for File WaveletTransform.hpp
=============================================

|exhale_lsh| :ref:`Return to documentation for file <file_include_WaveletTransform.hpp>` (``include/WaveletTransform.hpp``)

.. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS

.. code-block:: none

   #ifndef __WAVELETTRANSFORM_HPP
   #define __WAVELETTRANSFORM_HPP
   
   
   
   #include <gsl/gsl_wavelet.h>
   #include <gsl/gsl_errno.h>
   
   
   
   #include <AlgoBase.hpp>
   #include <SeqView.hpp>
   
   
   
   
   
   
   
   
   
   namespace tsa {
   
   
       class WaveletTransform : AlgoBase {
       public:
   
           enum WaveletType {
               Daub4,
               Daub6,
               Daub8,
               Daub10,
               Daub12,
               Daub14,
               Daub16,
               Daub18,
               Daub20,
               DaubC4,
               DaubC6,
               DaubC8,
               DaubC10,
               DaubC12,
               DaubC14,
               DaubC16,
               DaubC18,
               DaubC20,
               Haar,
               HaarC,
               Bspline103,
               Bspline105,
               Bspline202,
               Bspline204,
               Bspline206,
               Bspline208,
               Bspline301,
               Bspline303,
               Bspline305,
               Bspline307,
               Bspline309,
               BsplineC103,
               BsplineC105,
               BsplineC202,
               BsplineC204,
               BsplineC206,
               BsplineC208,
               BsplineC301,
               BsplineC303,
               BsplineC305,
               BsplineC307,
               BsplineC309
           };
   
           WaveletTransform(unsigned int N, enum WaveletType wt);
   
           WaveletTransform(const WaveletTransform& from);
   
           ~WaveletTransform();
   
           WaveletTransform& operator=(const WaveletTransform& from);
   
   
           void Forward(SeqViewDouble& In);
           void Inverse(SeqViewDouble& In);
           void Forward(Dmatrix& In);
           void Inverse(Dmatrix& In);
   
   
   
           void WaveletPrint();
           void WaveletWaveform(Dvector& V);
   
   
   
   
   
   
       protected:
   
       private:
           gsl_wavelet *mW;
           gsl_wavelet_workspace *mWork;
           unsigned int mN; 
       };
   
   
   
   
   
   
   
   
   } //end namespace
   
   #endif // ___WAVELETTRANSFORM_HPP
   
   
