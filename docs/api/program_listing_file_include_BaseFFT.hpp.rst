
.. _program_listing_file_include_BaseFFT.hpp:

Program Listing for File BaseFFT.hpp
====================================

|exhale_lsh| :ref:`Return to documentation for file <file_include_BaseFFT.hpp>` (``include/BaseFFT.hpp``)

.. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS

.. code-block:: none

   
   #ifndef __BASEFFT_HPP
   #define __BASEFFT_HPP
   
   #include <stdio.h>
   #include <boost/numeric/ublas/matrix.hpp>
   #include <fftw3.h>
   
   #include <AlgoBase.hpp>
   
   
   
   
   
   
   
   using namespace boost::numeric::ublas;
   
   
   namespace tsa {
   
       enum FFTPlanningMode {
           ESTIMATE, //*< Simple heuristic, fast
           MEASURE, //*< More time consuming. Usually close to optimal.
           PATIENT, //*< More consuming than MEASURE
           EXHAUSTIVE //*< Very demanding
       };
   
       inline int FFTsize(int n) {
           return n / 2 + 1;
       }
   
       class BaseFFT : public AlgoBase {
       public:
   
           BaseFFT(int size, enum FFTPlanningMode mode, bool PreserveInput) {
               mPlan = NULL;
               mPlanNeedsUpdate = false;
               mLogicalSize = size;
               SetPlanningMode(mode);
               SetPreserveInput(PreserveInput);
           };
   
           BaseFFT(const BaseFFT& from) {
               mPlan = NULL;
               mPlanNeedsUpdate = false;
               mLogicalSize = from.mLogicalSize;
               mPlanningRigor = from.mPlanningRigor;
               mPlanningRestriction = from.mPlanningRestriction;
           };
   
           virtual ~BaseFFT() {
               if (mPlan) {
                   fftw_destroy_plan(mPlan);
               }
           };
   
   
           static void SaveWisdomOnFile(std::string filename) {
               FILE *out = fopen(filename.c_str(), "w");
               if (out == 0) {
                   throw std::runtime_error("Can't open wisdom file for saving");
               }
               fftw_export_wisdom_to_file(out);
               fclose(out);
           }
   
           static void LoadWisdomFromFile(std::string filename) {
               FILE *in = fopen(filename.c_str(), "r");
               if (in == 0) {
                   throw;
               }
               if (fftw_import_wisdom_from_file(in) == 0) {
                   throw std::runtime_error("Can't open wisdom file for reading");
               }
               fclose(in);
           }
   
           static void ForgetWisdom() {
               fftw_forget_wisdom();
           }
   
           virtual void MakePlan() = 0;
   
   
   
   
   
   
   
           void SetPlanningMode(enum FFTPlanningMode mode) {
               unsigned int mPlanningRigorNew = FFTW_ESTIMATE;
               switch (mode) {
                   case ESTIMATE:
                       mPlanningRigorNew = FFTW_ESTIMATE;
                       break;
                   case MEASURE:
                       mPlanningRigorNew = FFTW_MEASURE;
                       break;
                   case PATIENT:
                       mPlanningRigorNew = FFTW_PATIENT;
                       break;
                   case EXHAUSTIVE:
                       mPlanningRigorNew = FFTW_EXHAUSTIVE;
                       break;
               }
               if (mPlanningRigorNew != mPlanningRigor) {
                   mPlanningRigor = mPlanningRigorNew;
                   mPlanNeedsUpdate = true;
               }
           };
   
           void SetPreserveInput(bool flag = true) {
               unsigned int mPlanningRestrictionNew;
               if (flag) {
                   mPlanningRestrictionNew = FFTW_PRESERVE_INPUT;
               } else {
                   mPlanningRestrictionNew = FFTW_DESTROY_INPUT;
               }
               if (mPlanningRestrictionNew != mPlanningRestriction) {
                   mPlanningRestriction = mPlanningRestrictionNew;
                   mPlanNeedsUpdate = true;
               }
           }
   
   
   
   
       protected:
   
   
           fftw_plan mPlan;
   
           bool mPlanNeedsUpdate;
   
           unsigned int mLogicalSize;
   
           unsigned int mPlanningRigor;
   
           unsigned int mPlanningRestriction;
   
   
       private:
   
       };
   
   
   
   
   
   
   
   
   
   } // end namespace tsa
   
   #endif // __BASEFFT_HPP
