
.. _program_listing_file_include_FrameIStream.hpp:

Program Listing for File FrameIStream.hpp
=========================================

|exhale_lsh| :ref:`Return to documentation for file <file_include_FrameIStream.hpp>` (``include/FrameIStream.hpp``)

.. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS

.. code-block:: none

   #ifndef __FRAMEISTREAM_HPP
   #define __FRAMEISTREAM_HPP
   
   
   #include <deque>
   #include <FrameL.h>
   
   
   #include <AlgoBase.hpp>
   #include <SeqView.hpp>
   
   
   
   
   
   
   
   
   namespace tsa {
   
   
       class FrameIStream;
   
       struct DataException {
   
           enum exception_type {
               data_loss 
           };
   
           DataException(double ts, double te, exception_type e) :
           Exception(e), StartTime(ts), EndTime(te) {
           };
           exception_type Exception; 
           double StartTime; 
           double EndTime; 
       };
   
       class ChannelDescriptor : public AlgoBase {
       public:
   
           ChannelDescriptor(unsigned int id) : mId(id) {
           };
   
           virtual void AddData() {
           };
   
           virtual double GetLength() {
               return 0.0;
           };
   
           virtual double GetRate() {
               return mRate;
           };
   
           virtual void WriteView(SeqViewDouble& v);
   
           virtual void FillView(SeqViewDouble& v, double tstart, double tend);
   
   
           virtual void WriteView(SeqViewDouble& v, SeqViewDouble& validation);
   
           virtual ~ChannelDescriptor() {
           };
   
       protected:
           void PushValue(double value, double t, unsigned int n);
   
           void PushFrVect(FrVect *frv, double t, unsigned int off, double offset, double slope);
   
           void Queue(double v, double t);
   
           bool data_available(double t);
   
   
           FrameIStream* mFIS; 
           unsigned int mId; 
           double mRate; 
           double mNextTime; 
           std::deque<double> mData; 
           std::deque<DataException> mExceptions; 
       };
   
       class ADC_Channel : public ChannelDescriptor {
       public:
           ADC_Channel(FrameIStream* FIS, FrAdcData* adc, unsigned int id);
   
           virtual ~ADC_Channel();
   
           virtual void AddData();
   
           virtual double GetLength();
   
           static ADC_Channel* Create(FrameIStream* FIS, char* name, unsigned int id);
   
       private:
           char *mName;
   
   
       };
   
       class PROC_Channel : public ChannelDescriptor {
       public:
   
           PROC_Channel(FrameIStream* FIS, FrProcData* proc, unsigned int id);
   
           virtual ~PROC_Channel();
   
           virtual void AddData();
   
           virtual double GetLength();
   
           static PROC_Channel* Create(FrameIStream* FIS, char* name, unsigned int id);
   
   
           virtual void FillView(SeqViewDouble& v, double tstart, double tend);
   
       private:
           char *mName; 
       };
   
       class SIM_Channel : public ChannelDescriptor {
       public:
   
           SIM_Channel(FrameIStream* FIS, FrSimData* sim, unsigned int id);
   
           virtual ~SIM_Channel();
   
           virtual void AddData();
   
           virtual double GetLength();
   
           static SIM_Channel* Create(FrameIStream* FIS, char* name, unsigned int id);
   
       private:
           char *mName; 
       };
   
       class SER_Channel : public ChannelDescriptor {
       public:
   
           SER_Channel(FrameIStream* FIS, char* smsName, char* smsParam, unsigned int id);
   
           virtual ~SER_Channel();
   
           virtual void AddData();
   
           virtual double GetLength();
   
           static SER_Channel* Create(FrameIStream* FIS, char *name, unsigned int id);
   
       private:
           char *mSmsName; 
           char *mSmsParam; 
       };
   
       class FRAMEH_Channel : public ChannelDescriptor {
       public:
   
           enum field_type {
               field_run, 
               field_frame, 
               field_dataQuality, 
               field_GTimeS, 
               field_GTimeN, 
               field_ULeapS, 
               field_dt, 
               field_time 
           };
   
           FRAMEH_Channel(FrameIStream* FIS, enum field_type ft, unsigned int id);
   
           virtual ~FRAMEH_Channel();
   
           virtual void AddData();
   
           virtual double GetLength();
   
           static FRAMEH_Channel* Create(FrameIStream* FIS, char *field_name, unsigned int id);
   
       private:
           char *mFieldName; 
           enum field_type mFieldType; 
       };
   
       class FrameIStream : public AlgoBase {
       public:
   
           FrameIStream(
                   const std::string& fileName,
                   const double& StartTime
                   );
   
   
   
           FrameIStream(
                   const std::string& fileName,
                   const double& StartTime,
                   const double& TimeLength,
                   const std::vector<std::string>& channelNames
                   );
   
           ~FrameIStream();
   
   
   
           void Init();
   
   
   
           FrameIStream& operator>>(std::vector<SeqViewDouble>& rSeqView);
   
   
          // unsigned int ReadDataUntil(SeqViewDouble& rSeqView, double time, unsigned int maxlen);
   
   
   
           FrameIStream& operator>>(SeqViewDouble& rSeqView);
   
   
           void FillView(SeqViewDouble& rSeqView, double tstart, double tend);
   
   
   
   
   
   
           std::string GetInfo(int gtime = 0);
   
   
           const std::string& GetFileName(void) const;
   
           const std::vector<std::string>& GetChannelNames(void) const;
   
           double GetStartTime(void) const;
   
           double GetEndTime(void) const;
   
           double GetSampling(unsigned int cn) const;
   
   
           double GetTimeLength() {
               return mTimeLength;
           };
   
           FrameH* GetFrame() {
               return mpFrame;
           };
   
           struct FrFile* GetFrameFile() {
               return mpFrameFile;
           };
   
           bool GetDataLossFlag() {
               return mDataLoss;
           };
   
   
   
   
           void SetChannels(const std::vector<std::string>& channelNames);
   
           void SetTimeLength(double length);
   
           void ResetValidationView();
   
           void SetValidationView(std::vector<SeqViewDouble> *rValidationView);
   
           void SetDataLossFlag(bool status) {
               mDataLoss = status;
           }
   
           void AddException(const std::string& msg, double miss_start, double miss_end, unsigned int channel) {
               mMissExceptions.push_back(missing_data(msg, miss_start, miss_end, channel));
           }
   
   
       protected:
   
       private:
   
           ChannelDescriptor* CreateChannelDescriptor(const std::string& cname, unsigned int id);
   
           bool DataRequired();
   
           void GetData();
   
   
           double mStartTime; 
           double mTimeLength; 
           struct FrFile* mpFrameFile; 
           FrameH* mpFrame; 
           std::vector<std::string> mChannelNames; 
           std::string mFileName; 
           std::vector<ChannelDescriptor*> mChannelDescriptors; 
           std::vector<SeqViewDouble> *mValidationView; 
           bool mDataLoss; 
           std::deque<missing_data> mMissExceptions; 
       };
   
   
   
   
   
   
   
   
   
   } // end namespace tsa
   
   #endif // __FRAMEISTREAM_HPP
