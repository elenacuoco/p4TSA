
.. _program_listing_file_include_EventDescription.hpp:

Program Listing for File EventDescription.hpp
=============================================

|exhale_lsh| :ref:`Return to documentation for file <file_include_EventDescription.hpp>` (``include/EventDescription.hpp``)

.. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS

.. code-block:: none

   #ifndef __EVENTDESCRIPTION_hpp
   #define __EVENTDESCRIPTION_hpp
   
   
   
   
   #include <string>
   
   
   
   
   #include <AlgoBase.hpp>
   #include <BaseView.hpp>
   
   
   
   
   
   
   
   
   
   
   using namespace boost::numeric::ublas;
   namespace tsa {
   
   
   
   
       class EventFull {
       public:
   
           EventFull()
           :
           mTime(0.0),
           mSNR(0.0),
           mCmax(0.0),
           mlevel(0.0) {
           }
           ;
   
           virtual ~EventFull() {
           }
           ;
           double mTime;
           double mSNR;
           double mCmax;
           double mlevel;
           std::string mWave;
   
           EventFull& operator=(const EventFull& from) {
   
               mTime = from.mTime;
               mSNR = from.mSNR;
               mCmax = from.mCmax;
               mlevel = from.mlevel;
               mWave = from.mWave;
           }
   
       };
   
       class Event {
       public:
   
           Event()
           :
           mTime(0.0),
           mSNR(0.0) {
           }
           ;
   
           virtual ~Event() {
           }
           ;
           double mTime;
           double mSNR;
           std::string mWave;
   
           Event& operator=(const Event& from) {
   
               mTime = from.mTime;
               mSNR = from.mSNR;
               mWave = from.mWave;
   
           }
   
       };
   
       class ClusterizedEvent {
       public:
   
           ClusterizedEvent()
           :
           mTime(0.0),
           mLenght(0.0),
           mSNR(0.0) {
           }
           ;
   
           virtual ~ClusterizedEvent() {
           }
           ;
           double mTime;
           double mLenght;
           double mSNR;
           std::string mWave;
   
           ClusterizedEvent& operator=(const ClusterizedEvent& from) {
   
               mTime = from.mTime;
               mSNR = from.mSNR;
               mLenght = from.mLenght;
               mWave = from.mWave;
           }
       };
   
       class ClusterizedEventFull {
       public:
   
           ClusterizedEventFull()
           :
           mTime(0.0),
           mTimeMax(0.0),
           mLenght(0.0),
           mSNR(0.0),
           mCmax(0.0),
           mlevel(0.0) {
           }
           ;
   
           virtual ~ClusterizedEventFull() {
           }
           ;
           double mTime;
           double mTimeMax;
           double mLenght;
           double mSNR;
           double mCmax;
           double mlevel;
           std::string mWave;
   
           ClusterizedEventFull& operator=(const ClusterizedEventFull& from) {
   
               mTime = from.mTime;
               mSNR = from.mSNR;
               mCmax = from.mCmax;
               mlevel = from.mlevel;
               mWave = from.mWave;
           }
       };
   
   
   
   
   
   
   
   } //end namespace
   
   #endif // __EVENTDESCRIPTION_hpp
