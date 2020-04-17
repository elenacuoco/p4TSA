
.. _program_listing_file_include_FrameIChannel.hpp:

Program Listing for File FrameIChannel.hpp
==========================================

|exhale_lsh| :ref:`Return to documentation for file <file_include_FrameIChannel.hpp>` (``include/FrameIChannel.hpp``)

.. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS

.. code-block:: none

   #ifndef __FRAMEICHANNEL_HPP
   #define __FRAMEICHANNEL_HPP
   
   
   
   
   
   #include <sys/types.h>
   #include <sys/stat.h>
   #include <unistd.h>
   
   
   
   #include <deque>
   #include <FrameL.h>
   
   
   
   #include <AlgoBase.hpp>
   #include <SeqView.hpp>
   
   
   
   
   
   
   
   
   namespace tsa {
   
       class FrameIChannel : public AlgoBase {
       public:
   
   
           FrameIChannel(const std::string& fileName, const std::string& channelName,
                   double dLength = 1.0, double tStart = 0.0);
   
   
           ~FrameIChannel();
   
   
   
           double NextSlice();
   
   
   
   
   
           bool GetData(SeqViewDouble& rSeqView, double tStart, double dLength);
   
           bool GetData(SeqViewDouble& rSeqView);
   
           static std::string GetChannelList(const std::string& fileName, int gtime = 0);
   
   
   
   
           void SetStartTime(double tStart);
   
           void SetDataLength(double dLength);
   
           void SetAutoIncrement(bool status);
   
   
       protected:
   
       private:
   
           void PushFrVect(FrVect *frv, Dmatrix& data, unsigned int row, double offset, double slope);
   
           bool ReopenIfModified();
   
           std::string mFileName;
           FrFile *miFile;
           std::string mChannelName;
           double mStartTime;
           double mDataLength;
           FrVect *mFrameVect;
           bool mAutoIncrement;
           time_t mLastModification;
       };
   
   
   
   
   
   
   
   
   
   
   } // end namespace tsa
   
   #endif // __FRAMEICHANNEL_HPP
   
