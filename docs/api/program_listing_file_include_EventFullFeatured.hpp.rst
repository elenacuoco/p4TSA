
.. _program_listing_file_include_EventFullFeatured.hpp:

Program Listing for File EventFullFeatured.hpp
==============================================

|exhale_lsh| :ref:`Return to documentation for file <file_include_EventFullFeatured.hpp>` (``include/EventFullFeatured.hpp``)

.. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS

.. code-block:: none

   #ifndef __EVENTFULLFEATURED_hpp
   #define __EVENTFULLFEATURED_hpp
   
   
   
   
   #include <string>
   
   
   
   
   #include <AlgoBase.hpp>
   #include <BaseView.hpp>
   
   
   
   
   
   
   
   
   
   
   
   namespace tsa {
   
   
   
   
   
       /* This class contain the event found by WDF plus the vector of  wavelet coefficients up to @NumCoeff coefficients. */
   
   
   
       class EventFullFeatured {
       public:
           typedef boost::numeric::ublas::vector< double > Dvector;
           EventFullFeatured(unsigned int NumCoeff);
   
   
           virtual ~EventFullFeatured();
   
           void operator=(const EventFullFeatured& from);
   
           void EVcopy(const EventFullFeatured& from);
   
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
           double mSNR;
           Dvector mCoeff;
           double mlevel;
           std::string mWave;
       private:
       protected:
   
   
   
   
       };
   
   
   
   
   
   } //end namespace
   
   #endif // __EVENTFULLFEATURED_hpp
