#include <FrameIStream.hpp>
#include <values.h>
#include <sstream>
///
/// tsa namespace
///
namespace tsa {

    ChannelDescriptor* FrameIStream::CreateChannelDescriptor(const std::string& cname, unsigned int id) {
        if (mpFrame == NULL) {
            LogSevere("Can't create channels: no frame available");
            return 0;
        }
        ChannelDescriptor* res = 0;

        res = ADC_Channel::Create(this, const_cast<char *> (cname.c_str()), id);
        if (res != 0) return res;

        res = PROC_Channel::Create(this, const_cast<char *> (cname.c_str()), id);
        if (res != 0) return res;

        res = SIM_Channel::Create(this, const_cast<char *> (cname.c_str()), id);
        if (res != 0) return res;

        res = SER_Channel::Create(this, const_cast<char *> (cname.c_str()), id);
        if (res != 0) return res;

        res = FRAMEH_Channel::Create(this, const_cast<char *> (cname.c_str()), id);
        if (res != 0) return res;

        return 0;
    }

    void ChannelDescriptor::Queue(double v, double t) {
        double delta = t - mNextTime;

        if (delta > .5 * mRate) {

            LogDebug(2, "Data loss. Added exception. t=%.18g mNextTime=%.18g delta=%.18g mRate/2=%.18g",
                    t,
                    mNextTime,
                    delta,
                    .5 * mRate);

            std::stringstream s;
            s << "Data loss in channel " << mId << ". From t=" << mNextTime << " to t=" << t;
            mFIS->AddException(s.str(), mNextTime, t, mId);

            mExceptions.push_back(DataException(mNextTime, t, DataException::data_loss));
            mNextTime = t + mRate;
            mData.push_back(v);
        } else if (delta > -.5 * mRate) {
            mData.push_back(v);
            mNextTime = t + mRate;
        } else {
            LogDebug(2, "Data ignored");
        }
    }

    void ChannelDescriptor::PushValue(double value, double t, unsigned int n) {
        for (unsigned int i = 0; i < n; i++) {
            Queue(value, t + mRate * i);
        }
    }

    void ChannelDescriptor::PushFrVect(FrVect *frv, double t, unsigned int off, double offset, double slope) {

        switch (frv->type) {
            case FR_VECT_C:
                for (unsigned int i = off; i < frv->nData; i++) {
                    Queue((double) (frv->data[ i ]) * slope + offset, t + mRate * i);
                }
                break;
            case FR_VECT_2S:
                for (unsigned int i = off; i < frv->nData; i++) {
                    Queue((double) (frv->dataS[ i ]) * slope + offset, t + mRate * i);
                }
                break;
            case FR_VECT_4S:
                for (unsigned int i = off; i < frv->nData; i++) {
                    Queue((double) (frv->dataI[ i ]) * slope + offset, t + mRate * i);
                }
                break;
            case FR_VECT_8S:
                for (unsigned int i = off; i < frv->nData; i++) {
                    Queue((double) (frv->dataL[ i ]) * slope + offset, t + mRate * i);
                }
                break;
            case FR_VECT_1U:
                for (unsigned int i = off; i < frv->nData; i++) {
                    Queue((double) (frv->dataU[ i ]) * slope + offset, t + mRate * i);
                }
                break;
            case FR_VECT_2U:
                for (unsigned int i = off; i < frv->nData; i++) {
                    Queue((double) (frv->dataUS[ i ]) * slope + offset, t + mRate * i);
                }
                break;
            case FR_VECT_4U:
                for (unsigned int i = off; i < frv->nData; i++) {
                    Queue((double) (frv->dataUI[ i ]) * slope + offset, t + mRate * i);
                }
                break;
            case FR_VECT_8U:
                for (unsigned int i = off; i < frv->nData; i++) {
                    Queue((double) (frv->dataUL[ i ]) * slope + offset, t + mRate * i);
                }
                break;
            case FR_VECT_4R:
                for (unsigned int i = off; i < frv->nData; i++) {
                    Queue((double) (frv->dataF[ i ]) * slope + offset, t + mRate * i);
                }
                break;
            case FR_VECT_8R:
                for (unsigned int i = off; i < frv->nData; i++) {
                    Queue((double) (frv->dataD[ i ]) * slope + offset, t + mRate * i);
                }
                break;
            default:
                LogSevere("FrVectCopy: unknown type");
              
        }
    }

    bool ChannelDescriptor::data_available(double t) {
        if (mExceptions.size() == 0) {
            return true;
        }
        switch (mExceptions.front().Exception) {
            case DataException::data_loss:
                if ((t >= mExceptions.front().StartTime)) {

                    if (t < mExceptions.front().EndTime) {
                        return false;
                    }

                    mExceptions.pop_front();
                    return data_available(t);

                } else {
                    return true;
                }
                break;
            default:
               
        }
    }

    void ChannelDescriptor::WriteView(SeqViewDouble& v) {
        //Dmatrix* d = &Attribute<Dmatrix>(v,"Data");
        Dmatrix* d = v.GetData();
        v.SetStart(mFIS->GetStartTime());
        v.SetSampling(mRate);
        v.SetScale(1.0);

        double tl = mFIS->GetTimeLength();
        unsigned int n = (unsigned int) floor(tl / mRate);

        if ((d->size1() != 1) || (d->size2() != n)) {
            d->resize(1, n);
        }

        double tm = mFIS->GetStartTime();
        for (unsigned int k = 0; k < n; k++) {
            if (data_available(tm)) {
                (*d)(0, k) = mData.front();
                mData.pop_front();
            } else {
                (*d)(0, k) = 0.0;
                mFIS->SetDataLossFlag(true);
            }
            tm += mRate;
        }
    }

    void ChannelDescriptor::FillView(SeqViewDouble& rSeqView, double tstart, double tend) {

    }

    void ChannelDescriptor::WriteView(SeqViewDouble& v, SeqViewDouble& validation) {
        Dmatrix* d = v.GetData();
        v.SetStart(mFIS->GetStartTime());
        v.SetSampling(mRate);
        v.SetScale(1.0);

        Dmatrix* val = validation.GetData();
        validation.SetStart(mFIS->GetStartTime());
        validation.SetSampling(mRate);
        validation.SetScale(1.0);


        double tl = mFIS->GetTimeLength();
        unsigned int n = (unsigned int) floor(tl / mRate);

        if ((d->size1() != 1) || (d->size2() != n)) {
            d->resize(1, n);
        }

        if ((val->size1() != 1) || (val->size2() != n)) {
            val->resize(1, n);
        }

        double tm = mFIS->GetStartTime();
        for (unsigned int k = 0; k < n; k++) {
            if (data_available(tm)) {
                (*d)(0, k) = mData.front();
                (*val)(0, k) = 1.0;
                mData.pop_front();
            } else {
                (*d)(0, k) = 0.0;
                (*val)(0, k) = 0.0;
                mFIS->SetDataLossFlag(true);
            }
            tm += mRate;
        }
    }

    ADC_Channel* ADC_Channel::Create(FrameIStream* FIS, char* name, unsigned int id) {
        LogDebug(2, "Trying ADC channel %s", name);
        FrAdcData *adc = FrAdcDataFind(FIS->GetFrame(), name);
        if (adc != NULL) {
            LogDebug(2, "Success");
            return new ADC_Channel(FIS, adc, id);
        }
        LogDebug(2, "Failed");
        return 0;
    }

    ADC_Channel::ADC_Channel(FrameIStream* FIS, FrAdcData *adc, unsigned int id)
    :
    ChannelDescriptor(id) {
        LogDebug(3, "Found ADC channel %s", adc->name);
        mFIS = FIS;
        mName = new char[strlen(adc->name) + 1];
        strncpy(mName, adc->name, strlen(adc->name) + 1);
        mRate = adc->data->dx[0];
        mNextTime = FIS->GetStartTime();
        AddData();
    }

    ADC_Channel::~ADC_Channel() {
        delete[] mName;
    }

    void ADC_Channel::AddData() {
        FrAdcData *adc = FrAdcDataFind(mFIS->GetFrame(), mName);
        if (adc != NULL) {
            double tstart = mFIS->GetFrame()->GTimeS + mFIS->GetFrame()->GTimeN * 1.0e9 + adc->timeOffset;
            PushFrVect(adc->data, tstart, 0, adc->bias, adc->slope);
            LogDebug(3, "Data now: %d (%f seconds)", mData.size(), mRate * mData.size());
        }
    }

    double ADC_Channel::GetLength() {
        return mRate * mData.size();
    }

    PROC_Channel* PROC_Channel::Create(FrameIStream* FIS, char* name, unsigned int id) {
        LogDebug(2, "Trying PROC channel %s", name);
        FrProcData *proc = FrProcDataFind(FIS->GetFrame(), name);
        if (proc != NULL) {
            LogDebug(2, "Success");
            return new PROC_Channel(FIS, proc, id);
        }
        LogDebug(2, "Failed");
        return 0;
    }

    PROC_Channel::PROC_Channel(FrameIStream* FIS, FrProcData *proc, unsigned int id)
    :
    ChannelDescriptor(id) {
        mFIS = FIS;
        mName = new char[strlen(proc->name) + 1];
        strncpy(mName, proc->name, strlen(proc->name) + 1);
        mRate = proc->data->dx[0];
        mNextTime = FIS->GetStartTime();
        LogDebug(3, "Found PROC channel %s rate %f", proc->name, mRate);
        AddData();
    }

    PROC_Channel::~PROC_Channel() {
        delete[] mName;
    }

    void PROC_Channel::AddData() {
        FrProcData *proc = FrProcDataFind(mFIS->GetFrame(), mName);
        if (proc != NULL) {
            double tstart = mFIS->GetFrame()->GTimeS + mFIS->GetFrame()->GTimeN * 1.0e9 + proc->timeOffset;
            PushFrVect(proc->data, tstart, 0, 0.0, 1.0);
            LogDebug(3, "Data now: %d (%f seconds)", mData.size(), mRate * mData.size());
        }
    }

    double PROC_Channel::GetLength() {
        return mRate * mData.size();
    }

    void PROC_Channel::FillView(SeqViewDouble& v, double tstart, double tend) {
        FrProcData *proc = FrProcDataReadT(mFIS->GetFrameFile(), mName, tstart);
        if (proc == NULL) {
            LogSevere("PROC_Channel::FillView - data not found");
           
        }


        FrProcDataFree(proc);
    }

    SIM_Channel* SIM_Channel::Create(FrameIStream* FIS, char* name, unsigned int id) {
        LogDebug(2, "Trying SIM channel %s", name);
        FrSimData *sim = FrSimDataFind(FIS->GetFrame(), name);
        if (sim != NULL) {
            LogDebug(2, "Success");
            return new SIM_Channel(FIS, sim, id);
        }
        LogDebug(2, "Failed");
        return 0;
    }

    SIM_Channel::SIM_Channel(FrameIStream* FIS, FrSimData *sim, unsigned int id)
    :
    ChannelDescriptor(id) {
        LogDebug(3, "Found SIM channel %s", sim->name);
        mFIS = FIS;
        mName = new char[strlen(sim->name) + 1];
        strncpy(mName, sim->name, strlen(sim->name) + 1);
        mRate = sim->data->dx[0];
        mNextTime = FIS->GetStartTime();
        AddData();
    }

    SIM_Channel::~SIM_Channel() {
        delete[] mName;
    }

    void SIM_Channel::AddData() {
        FrSimData *sim = FrSimDataFind(mFIS->GetFrame(), mName);
        if (sim != NULL) {
            double tstart = mFIS->GetFrame()->GTimeS + mFIS->GetFrame()->GTimeN * 1.0e9 + sim->timeOffset;
            PushFrVect(sim->data, tstart, 0, 0.0, 1.0);
            LogDebug(3, "Data now: %d (%f seconds)", mData.size(), mRate * mData.size());
        }
    }

    double SIM_Channel::GetLength() {
        return mRate * mData.size();
    }

    SER_Channel* SER_Channel::Create(FrameIStream* FIS, char* name, unsigned int id) {
        char *buffer = new char[strlen(name) + 1];
        strncpy(buffer, name, strlen(name) + 1);
        char *delim = strstr(buffer, "..");
        if (delim == NULL) return 0;

        char *smsName = buffer;
        char *smsParam = delim + 2;
        delim[0] = 0;
        delim[1] = 0;


        double value;

        LogDebug(2, "Trying SER channel %s (%s)", smsName, smsParam);
        int ret = FrSerDataGet(FIS->GetFrame(), smsName, smsParam, &value);
        if (ret == 0.0) {
            SER_Channel *ret = new SER_Channel(FIS, smsName, smsParam, id);
            delete[] buffer;
            LogDebug(2, "Success");
            return ret;
        }
        delete[] buffer;
        LogDebug(2, "Failed");
        return 0;
    }

    SER_Channel::SER_Channel(FrameIStream* FIS, char *smsName, char *smsParam, unsigned int id)
    :
    ChannelDescriptor(id) {

        mFIS = FIS;
        FrSerData *ser = FrSerDataFind(FIS->GetFrame(), smsName, NULL);
        mRate = 1.0 / ser->sampleRate;
        mNextTime = FIS->GetStartTime();

        mSmsName = new char[strlen(smsName) + 1];
        strncpy(mSmsName, smsName, strlen(smsName) + 1);

        mSmsParam = new char[strlen(smsParam) + 1];
        strncpy(mSmsParam, smsParam, strlen(smsParam) + 1);

        LogDebug(3, "Found SER channel %s..%s", mSmsName, mSmsParam);
        LogDebug(3, "Frequency: %f", 1.0 / mRate);

        AddData();
    }

    SER_Channel::~SER_Channel() {
        delete[] mSmsName;
        delete[] mSmsParam;
    }

    void SER_Channel::AddData() {
        double value;
        if (FrSerDataGet(mFIS->GetFrame(), mSmsName, mSmsParam, &value) == 0) {
            double tstart = mFIS->GetFrame()->GTimeS + mFIS->GetFrame()->GTimeN * 1.0e9;
            PushValue(value, tstart, 1);
        }
        LogDebug(3, "Data now: %d (%f seconds)", mData.size(), mRate * mData.size());
    }

    double SER_Channel::GetLength() {
        return mRate * mData.size();
    }


    //////////////////////////////////////////////////////////// FRAMEH_Channel

    FRAMEH_Channel* FRAMEH_Channel::Create(FrameIStream* FIS, char* name, unsigned int id) {
        char *buffer = new char[strlen(name) + 1];
        strncpy(buffer, name, strlen(name) + 1);
        char *delim = strstr(buffer, "..");
        if (delim == NULL) return 0;

        char *smsName = buffer;
        char *smsParam = delim + 2;
        delim[0] = 0;
        delim[1] = 0;

        if (strcmp(smsName, "FrameH") != 0) {
            delete[] buffer;
            return 0;
        }

        LogDebug(3, "FRAMEH %s %s", smsName, smsParam);

        if (strcmp(smsParam, "run") == 0) {
            FRAMEH_Channel *ret = new FRAMEH_Channel(FIS, field_run, id);
            delete[] buffer;
            return ret;
        } else if (strcmp(smsParam, "frame") == 0) {
            FRAMEH_Channel *ret = new FRAMEH_Channel(FIS, field_frame, id);
            delete[] buffer;
            return ret;
        } else if (strcmp(smsParam, "dataQuality") == 0) {
            FRAMEH_Channel *ret = new FRAMEH_Channel(FIS, field_dataQuality, id);
            delete[] buffer;
            return ret;
        } else if (strcmp(smsParam, "GTimeS") == 0) {
            FRAMEH_Channel *ret = new FRAMEH_Channel(FIS, field_GTimeS, id);
            delete[] buffer;
            return ret;
        } else if (strcmp(smsParam, "GTimeN") == 0) {
            FRAMEH_Channel *ret = new FRAMEH_Channel(FIS, field_GTimeN, id);
            delete[] buffer;
            return ret;
        } else if (strcmp(smsParam, "ULeapS") == 0) {
            FRAMEH_Channel *ret = new FRAMEH_Channel(FIS, field_ULeapS, id);
            delete[] buffer;
            return ret;
        } else if (strcmp(smsParam, "dt") == 0) {
            FRAMEH_Channel *ret = new FRAMEH_Channel(FIS, field_dt, id);
            delete[] buffer;
            return ret;
        } else if (strcmp(smsParam, "time") == 0) {
            FRAMEH_Channel *ret = new FRAMEH_Channel(FIS, field_time, id);
            delete[] buffer;
            return ret;
        }

        delete[] buffer;
        return 0;
    }

    FRAMEH_Channel::FRAMEH_Channel(FrameIStream* FIS, enum field_type ft, unsigned int id)
    :
    ChannelDescriptor(id) {

        mFIS = FIS;
        mFieldType = ft;
        FIS->GetFrame()->dt;
        mNextTime = FIS->GetStartTime();

        switch (ft) {
            case field_run:
                mFieldName = new char[strlen("run") + 1];
                strcpy(mFieldName, "run");
                break;
            case field_frame:
                mFieldName = new char[strlen("frame") + 1];
                strcpy(mFieldName, "frame");
                break;
            case field_dataQuality:
                mFieldName = new char[strlen("dataQuality") + 1];
                strcpy(mFieldName, "dataQuality");
                break;
            case field_GTimeS:
                mFieldName = new char[strlen("GTimeS") + 1];
                strcpy(mFieldName, "GTimeS");
                break;
            case field_GTimeN:
                mFieldName = new char[strlen("GTimeN") + 1];
                strcpy(mFieldName, "GTimeN");
                break;
            case field_ULeapS:
                mFieldName = new char[strlen("ULeapS") + 1];
                strcpy(mFieldName, "ULeapS");
                break;
            case field_dt:
                mFieldName = new char[strlen("dt") + 1];
                strcpy(mFieldName, "dt");
                break;
            case field_time:
                mFieldName = new char[strlen("time") + 1];
                strcpy(mFieldName, "time");
                break;
            default:
                break;
        }

        LogDebug(3, "Found FRAMEH channel FrameH..%s", mFieldName);
        LogDebug(3, "Frequency: %f", 1.0 / mRate);

        AddData();

    }

    FRAMEH_Channel::~FRAMEH_Channel() {
        delete[] mFieldName;
    }

    void FRAMEH_Channel::AddData() {
        double value = 0.0;

        switch (mFieldType) {
            case field_run:
                value = double(mFIS->GetFrame()->run);
                break;
            case field_frame:
                value = double(mFIS->GetFrame()->frame);
                break;
            case field_dataQuality:
                value = double(mFIS->GetFrame()->dataQuality);
                break;
            case field_GTimeS:
                value = double(mFIS->GetFrame()->GTimeS);
                break;
            case field_GTimeN:
                value = double(mFIS->GetFrame()->GTimeN);
                break;
            case field_ULeapS:
                value = double(mFIS->GetFrame()->ULeapS);
                break;
            case field_dt:
                value = double(mFIS->GetFrame()->dt);
                break;
            case field_time:
                value = double(mFIS->GetFrame()->GTimeS + 1e-9 * mFIS->GetFrame()->GTimeN);
                break;
            default:
                break;
        }
        double tstart = mFIS->GetFrame()->GTimeS + mFIS->GetFrame()->GTimeN * 1.0e9;
        PushValue(value, tstart, 1);
        LogDebug(3, "Data now: %d (%f seconds)", mData.size(), mRate * mData.size());
    }

    double FRAMEH_Channel::GetLength() {
        return mRate * mData.size();
    }

    FrameIStream::FrameIStream(
            const std::string& fileName,
            const double& StartTime,
            const double& TimeLength,
            const std::vector<std::string>& channelNames
            )
    :
    mStartTime(StartTime),
    mTimeLength(0.0),
    mpFrameFile(NULL),
    mpFrame(NULL),
    mValidationView(0),
    mDataLoss(false) {
        mFileName = fileName;
        Init();
        SetTimeLength(TimeLength);
        SetChannels(channelNames);
    }

    FrameIStream::FrameIStream(
            const std::string& fileName,
            const double& StartTime
            )
    :
    mStartTime(StartTime),
    mTimeLength(0.0),
    mpFrameFile(NULL),
    mpFrame(NULL),
    mValidationView(0),
    mDataLoss(false) {
        mFileName = fileName;
        Init();

    }

    void FrameIStream::Init() {
        // Open the frame file
        mpFrameFile = FrFileINew(const_cast<char *> (mFileName.c_str()));
        if (mpFrameFile == NULL) {
            std::stringstream s;
            s << "File " << mFileName << " open error";
            std::string emsg = s.str();
            LogSevere("%s", emsg.c_str());
           
        } else {
            LogDebug(3, "File %s opened", mFileName.c_str());
        }

        // Try to get the first frame using TOC
        mpFrame = FrameReadT(mpFrameFile, mStartTime);
        if (mpFrame == NULL) {
            // Find the first frame without TOC
            mpFrame = FrameRead(mpFrameFile);
            if (mpFrame == NULL) {
                std::stringstream s;
                s << "No frames inside file " << mFileName;
                std::string emsg = s.str();
                LogSevere("%s", emsg.c_str());
             
            }
            if (mpFrame->GTimeS > mStartTime) {
                std::stringstream s;
                s << "No frames at the given time inside file " << mFileName;
                std::string emsg = s.str();
                LogSevere("%s", emsg.c_str());
               
            }
            while (mpFrame->GTimeS + mpFrame->dt < mStartTime) {
                FrameFree(mpFrame);
                mpFrame = FrameRead(mpFrameFile);
                if (mpFrame == NULL) {
                    std::stringstream s;
                    s << "No frames a the given time inside file " << mFileName;
                    std::string emsg = s.str();
                    LogSevere("%s", emsg.c_str());
                   
                }
            }
            LogDebug(3, "FrameRead: got frame starting at %f", mpFrame->GTimeS);
        } else {
            LogDebug(3, "FrameReadT: success. Got frame starting at %f", mpFrame->GTimeS);
        }
    }

    FrameIStream::~FrameIStream() {
        if (mpFrame != NULL) {
            FrameFree(mpFrame);
        }
        if (mpFrameFile != NULL) {
            FrFileIEnd(mpFrameFile);
        }
    }

    std::string FrameIStream::GetInfo(int gtime) {
        if (mpFrameFile != NULL) {
            if (gtime == 0) {
                if (mpFrame != NULL) {
                    gtime = mpFrame->GTimeS;
                } else {
                    return std::string("No frame");
                }
            }
            char *msg = FrFileIGetChannelList(mpFrameFile, gtime);
            std::string res(msg);
            free(msg);
            return res;
        } else {
            return std::string("no file");
        }
    }

   /* unsigned int ReadDataUntil(SeqViewDouble& rSeqView, double time, unsigned int maxlen) {


        return 0;
    }*/

    FrameIStream& FrameIStream::operator>>(SeqViewDouble& rSeqView) {
        mDataLoss = false;

        while (DataRequired()) GetData();

        if (mChannelDescriptors.size() != 1) {
          
        }

        if (mValidationView) {

            mChannelDescriptors[0]->WriteView(rSeqView, (*mValidationView)[0]);

        } else {

            mChannelDescriptors[0]->WriteView(rSeqView);

        }

        mStartTime += mTimeLength;

        while (mMissExceptions.size() > 0) {
          
            mMissExceptions.pop_front();
        }
        return *this;
    }

    FrameIStream& FrameIStream::operator>>(std::vector<SeqViewDouble>& rSeqView) {

        mDataLoss = false;

        while (DataRequired()) GetData();

        if (mChannelDescriptors.size() != rSeqView.size()) {

           

        unsigned int sz = mChannelDescriptors.size();

        if (mValidationView) {

            for (unsigned int i = 0; i < sz; i++) {

                mChannelDescriptors[i]->WriteView(rSeqView[i], (*mValidationView)[i]);

            }

        } else {

            for (unsigned int i = 0; i < sz; i++) {

                mChannelDescriptors[i]->WriteView(rSeqView[i]);

            }
        }
        mStartTime += mTimeLength;
        while (mMissExceptions.size() > 0) {
          
            mMissExceptions.pop_front();
        }
        return *this;
    }

    const std::string& FrameIStream::GetFileName(void) const {
        return mFileName;
    }

    const std::vector<std::string>& FrameIStream::GetChannelNames(void) const {
        return mChannelNames;
    }

    double FrameIStream::GetStartTime(void) const {
        return mStartTime;
    }

    double FrameIStream::GetEndTime(void) const {
        return mStartTime + mTimeLength;
    }

    double FrameIStream::GetSampling(unsigned int cn) const {
        return mChannelDescriptors[cn]->GetRate();
    }

    void FrameIStream::SetChannels(const std::vector<std::string>& channelNames) {
        mChannelNames = channelNames;

        // Erase old channels
        for (std::vector<ChannelDescriptor*>::iterator cd = mChannelDescriptors.begin();
                cd != mChannelDescriptors.end();
                cd++) {
            delete *cd;
        }
        mChannelDescriptors.clear();

        // Add new channels 
        unsigned int k = 0;
        for (std::vector<std::string>::iterator name = mChannelNames.begin(); name != mChannelNames.end(); name++) {
            ChannelDescriptor *cd = CreateChannelDescriptor(*name, k);
            if (cd != 0) {
                LogInfo("rate = %f", cd->GetRate());
                mChannelDescriptors.push_back(cd);
                k++;
            }
        }

        // Resize the time length if needed



    }

    void FrameIStream::SetTimeLength(double length) {
        mTimeLength = length;
    }

    void FrameIStream::GetData() {
        FrameFree(mpFrame);
        mpFrame = FrameRead(mpFrameFile);
        if (mpFrame == NULL) {

            LogSevere("end of file");
        }
        LogDebug(3, "Reading frame %d", mpFrame->frame);
        for (std::vector<ChannelDescriptor*>::iterator cd = mChannelDescriptors.begin();
                cd != mChannelDescriptors.end();
                cd++) {

            (*cd)->AddData();


        }
    }

    bool FrameIStream::DataRequired() {
        bool required = false;

        for (std::vector<ChannelDescriptor*>::iterator cd = mChannelDescriptors.begin();
                cd != mChannelDescriptors.end();
                cd++) {

            LogDebug(2, "==> %f %f", (*cd)->GetLength(), mTimeLength);
            if ((*cd)->GetLength() < mTimeLength) {
                required = true;
                break;
            }
        }
        return required;
    }

    void FrameIStream::ResetValidationView() {
        mValidationView = 0;
    }

    void FrameIStream::SetValidationView(std::vector<SeqViewDouble> *rValidationView) {
        mValidationView = rValidationView;
    }

    void FrameIStream::FillView(SeqViewDouble& rSeqView, double tstart, double tend) {
        mChannelDescriptors[0]->FillView(rSeqView, tstart, tend);
    }



}
// end namespace tsa

