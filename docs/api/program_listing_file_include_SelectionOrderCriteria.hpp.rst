
.. _program_listing_file_include_SelectionOrderCriteria.hpp:

Program Listing for File SelectionOrderCriteria.hpp
===================================================

|exhale_lsh| :ref:`Return to documentation for file <file_include_SelectionOrderCriteria.hpp>` (``include/SelectionOrderCriteria.hpp``)

.. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS

.. code-block:: none

   #ifndef __SELECTIONORDERCRITERIA_HPP
   #define __SELECTIONORDERCRITERIA_HPP
   
   
   
   
   
   
   
   
   #include <AlgoBase.hpp>
   #include <SeqView.hpp>
   
   
   
   
   
   
   
   
   
   
   using namespace boost::numeric::ublas;
   namespace tsa {
   
   
   
       class SelectionOrderCriteria : AlgoBase {
       public:
   
           SelectionOrderCriteria(unsigned int N, unsigned int Order);
   
           virtual ~SelectionOrderCriteria();
   
   
   
           void execute(Dvector& Parcor);
   
   
   
           double GetEps(unsigned int j) {
               return mEps(j);
           }
   
           double GetFpe(unsigned int j) {
               return mFpe(j);
           }
   
           double GetMdl(unsigned int j) {
               return mMdl(j);
           }
   
           double GetAic(unsigned int j) {
               return mAic(j);
           }
   
           double GetAicC(unsigned int j) {
               return mAicC(j);
           }
   
           double GetCat(unsigned int j) {
               return mCat(j);
           }
   
           double GetHQ(unsigned int j) {
               return mHQ(j);
           }
   
           double GetCic(unsigned int j) {
               return mCic(j);
           }
   
           double GetFsic(unsigned int j) {
               return mFsic(j);
           }
   
   
   
   
   
   
       protected:
   
       private:
           unsigned int mMaxOrder;
           unsigned int mN;
           unsigned int mSelOrd;
           Dvector mEps;
           Dvector mFpe;
           Dvector mMdl;
           Dvector mAic;
           Dvector mAicC;
           Dvector mCat;
           Dvector mHQ;
           Dvector mFsic;
           Dvector mCic;
   
   
       };
   
   
   
   
   
   
   
   
   } //end namespace
   
   #endif //  __SELECTIONORDERCRITERIA_HPP
