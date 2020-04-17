
.. _program_listing_file_include_AlgoExceptions.hpp:

Program Listing for File AlgoExceptions.hpp
===========================================

|exhale_lsh| :ref:`Return to documentation for file <file_include_AlgoExceptions.hpp>` (``include/AlgoExceptions.hpp``)

.. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS

.. code-block:: none

   
   #ifndef __ALGOEXCEPTIONS_HPP
   #define __ALGOEXCEPTIONS_HPP
   
   
   #include <stdexcept>
   #include <string>
   
   
   
   
   
   
   
   
   
   
   
   
   
   namespace tsa {
   
   
       class bad_matrix_size : public std::invalid_argument {
       public:
   
           bad_matrix_size(const std::string& msg)
           :
           std::invalid_argument(msg) {
   
           };
   
   
       private:
   
       };
   
   
   
   
       class bad_vector_size : public std::invalid_argument {
       public:
   
           bad_vector_size(const std::string& msg)
           :
           std::invalid_argument(msg) {
   
           };
   
   
       private:
   
       };
   
   
   
       class no_data_available : public std::runtime_error {
       public:
   
           no_data_available(const std::string& msg)
           :
           std::runtime_error(msg) {
   
           };
   
       private:
   
       };
   
   
   
       class bad_value : public std::runtime_error {
       public:
   
           bad_value()
           :
           std::runtime_error("") {
   
           };
   
       private:
   
       };
   
   
   
       class missing_data : public std::runtime_error {
       public:
   
           missing_data(const std::string& msg, double miss_start, double miss_end, unsigned int channel)
           :
           std::runtime_error(msg),
           mStartPeriod(miss_start),
           mEndPeriod(miss_end),
           mChannel(channel) {
   
           };
   
           double Start() {
               return mStartPeriod;
           }
   
           double End() {
               return mEndPeriod;
           }
   
           double Channel() {
               return mChannel;
           }
       private:
           double mStartPeriod;
           double mEndPeriod;
           unsigned int mChannel;
       };
   
   
   
       class quality_change : public std::runtime_error {
       public:
   
           quality_change(const std::string& msg, double change_time, unsigned int old_flag, unsigned int new_flag)
           :
           std::runtime_error(msg),
           mEventTime(change_time),
           mOldFlag(old_flag),
           mNewFlag(new_flag) {
   
           };
   
           double EventTime() {
               return mEventTime;
           }
   
           unsigned int OldFlag() {
               return mOldFlag;
           }
   
           unsigned int NewFlag() {
               return mNewFlag;
           }
       private:
           double mEventTime;
           unsigned int mOldFlag;
           unsigned int mNewFlag;
       };
   
   
   
   
   
   } // end namespace tsa
   
   #endif // __ALGOEXCEPTIONS_HPP
