
.. _program_listing_file_include_ClusterizedEventFullFeatured.hpp:

Program Listing for File ClusterizedEventFullFeatured.hpp
=========================================================

|exhale_lsh| :ref:`Return to documentation for file <file_include_ClusterizedEventFullFeatured.hpp>` (``include/ClusterizedEventFullFeatured.hpp``)

.. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS

.. code-block:: none

   #ifndef __CLUSTERIZEDEVENTFULLFEATURED_hpp
   #define __CLUSTERIZEDEVENTFULLFEATURED_hpp
   
   
   
   
   #include <string>
   
   
   
   
   #include <AlgoBase.hpp>
   #include <BaseView.hpp>
   
   
   
   
   
   
   
   
   
   
   
   namespace tsa {
   
       class ClusterizedEventFullFeatured {
       public:
   
           typedef boost::numeric::ublas::vector< double > Dvector;
   
           ClusterizedEventFullFeatured(unsigned int NumCoeff);
   
   
           virtual ~ClusterizedEventFullFeatured();
   
   
   
           void operator=(const ClusterizedEventFullFeatured& from);
           void CEVcopy(const ClusterizedEventFullFeatured& from);
   
           void outprint() {
               std::cout << "Time" << " " << mTime << "\n";
               std::cout << "SNR" << " " << mSNR << "\n";
               std::cout << "freq" << " " << mlevel << "\n";
               std::cout << "wavelet type" << " " << mWave << "\n";
               std::cout << "dimension" << " " << mCoeff.size() << "\n";
   
               for (unsigned int i = 0; i < mCoeff.size(); i++) {
                   std::cout << "coeff" << "-" << i << " " << mCoeff[i] << "\n";
               }
   
           }
   
           void SetCoeff(int i, double v) {
               mCoeff(i) = v;
           }
   
           double GetCoeff(unsigned int i) {
               return mCoeff(i);
   
           }
   
           double mTime;
           double mTimeMax;
           double mLenght;
           double mSNR;
           Dvector mCoeff;
           double mlevel;
           std::string mWave;
           unsigned int mNumCoeff;
       private:
       protected:
   
   
       };
   
   } //end namespace
   
   #endif // __CLUSTERIZEDEVENTFULLFEATURED_hpp
