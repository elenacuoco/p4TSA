#include <FrameIChannel.hpp>
#include <values.h>
#include <sstream>
///
/// tsa namespace
///
namespace tsa {

    bool FrameIChannel::ReopenIfModified() {
        struct stat tmp;
        int ecode = stat((const_cast<char *> (mFileName.c_str())), &tmp);

        if (miFile == NULL) {
            mLastModification = tmp.st_mtime;
            miFile = FrFileINew((const_cast<char *> (mFileName.c_str())));
            if (miFile == NULL) {
                std::stringstream s;
                s << "File " << mFileName << " open error";
                std::string emsg = s.str();
                LogSevere("%s", emsg.c_str());
                throw std::runtime_error(emsg);
            }
            LogDebug(3, "File %s opened", const_cast<char *> (mFileName.c_str()));
            return true;
        }
        if (mLastModification < tmp.st_mtime) {
            mLastModification = tmp.st_mtime;
            FrFileIEnd(miFile);
            miFile = FrFileINew((const_cast<char *> (mFileName.c_str())));
            if (miFile == NULL) {
                std::stringstream s;
                s << "File " << mFileName << " open error";
                std::string emsg = s.str();
                LogSevere("%s", emsg.c_str());
                throw std::runtime_error(emsg);
            }
            LogDebug(3, "File %s reopened (changed)", const_cast<char *> (mFileName.c_str()));
            return true;
        }
        return false;
    }

    FrameIChannel::FrameIChannel(const std::string& fileName, const std::string& channelName, double dLength, double tStart) {
        mFileName = fileName;
        miFile = NULL;

        while (ReopenIfModified());

        mChannelName = channelName;
        mDataLength = dLength;
        mStartTime = tStart;
        mFrameVect = NULL;
        mAutoIncrement = true;
    }

    FrameIChannel::~FrameIChannel() {
        if (mFrameVect != NULL) {
            FrVectFree(mFrameVect);
            mFrameVect = NULL;
        }
        FrFileIEnd(miFile);
    }

    bool FrameIChannel::GetData(SeqViewDouble& rSeqView, double tStart, double dLength) {
        mStartTime = tStart;
        mDataLength = dLength;
        return GetData(rSeqView);
    }

    bool FrameIChannel::GetData(SeqViewDouble& rSeqView) {
        bool status = true;

        if (mFrameVect != NULL) {
            FrVectFree(mFrameVect);
            mFrameVect = NULL;
        }
        while (ReopenIfModified());
        mFrameVect = FrFileIGetVectDN(miFile, const_cast<char *> (mChannelName.c_str()), mStartTime, mDataLength);
        if (mFrameVect == NULL) {
            std::stringstream s;
            s << std::fixed << "Can't get data for tstart=" << mStartTime << " tlength=" << mDataLength << " in channel " << mChannelName;
            std::string emsg = s.str();
            LogSevere("%s", emsg.c_str());
            mStartTime += mDataLength;
            throw std::runtime_error(emsg);
        }
        Dmatrix* data = rSeqView.GetData();

        if (mFrameVect->next == NULL) {
            // No missed data
            if ((data->size1() != 1) || (data->size2() != mFrameVect->nx[0])) {
                data->resize(1, mFrameVect->nData);
            }
            PushFrVect(mFrameVect, *data, 0, 0.0, 1.0);
        } else {
            // Missed data
            status = false;
            if ((data->size1() != 2) || (data->size2() != mFrameVect->nx[0])) {
                data->resize(2, mFrameVect->nData);
            }
            PushFrVect(mFrameVect, *data, 0, 0.0, 1.0);
            PushFrVect(mFrameVect->next, *data, 0, 0.0, 1.0);
        }
        rSeqView.SetStart(mStartTime);
        rSeqView.SetSampling(mFrameVect->dx[0]);
        rSeqView.SetScale(1.0);
        if (mAutoIncrement) {
            NextSlice();
        }

        return status;
    }

    void FrameIChannel::SetStartTime(double tStart) {
        mStartTime = tStart;
    }

    void FrameIChannel::SetDataLength(double dLength) {
        mDataLength = dLength;

    }

    std::string FrameIChannel::GetChannelList(const std::string& fileName, int gtime) {
        FrFile *iFile = FrFileINew((const_cast<char *> (fileName.c_str())));
        std::string tmp(FrFileIGetChannelList(iFile, gtime));
        FrFileIEnd(iFile);
        return tmp;
    }

    double FrameIChannel::NextSlice() {
        mStartTime += mDataLength;
    }

    void FrameIChannel::SetAutoIncrement(bool status) {
        mAutoIncrement = status;
    }

    void FrameIChannel::PushFrVect(FrVect *frv, Dmatrix& data, unsigned int row, double offset, double slope) {
        switch (frv->type) {
            case FR_VECT_C:
                for (unsigned int i = 0; i < frv->nData; i++) {
                    data(row, i) = (double) (frv->data[ i ]) * slope + offset;
                }
                break;
            case FR_VECT_2S:
                for (unsigned int i = 0; i < frv->nData; i++) {
                    data(row, i) = (double) (frv->dataS[ i ]) * slope + offset;
                }
                break;
            case FR_VECT_4S:
                for (unsigned int i = 0; i < frv->nData; i++) {
                    data(row, i) = (double) (frv->dataI[ i ]) * slope + offset;
                }
                break;
            case FR_VECT_8S:
                for (unsigned int i = 0; i < frv->nData; i++) {
                    data(row, i) = (double) (frv->dataL[ i ]) * slope + offset;
                }
                break;
            case FR_VECT_1U:
                for (unsigned int i = 0; i < frv->nData; i++) {
                    data(row, i) = (double) (frv->dataU[ i ]) * slope + offset;
                }
                break;
            case FR_VECT_2U:
                for (unsigned int i = 0; i < frv->nData; i++) {
                    data(row, i) = (double) (frv->dataUS[ i ]) * slope + offset;
                }
                break;
            case FR_VECT_4U:
                for (unsigned int i = 0; i < frv->nData; i++) {
                    data(row, i) = (double) (frv->dataUI[ i ]) * slope + offset;
                }
                break;
            case FR_VECT_8U:
                for (unsigned int i = 0; i < frv->nData; i++) {
                    data(row, i) = (double) (frv->dataUL[ i ]) * slope + offset;
                }
                break;
            case FR_VECT_4R:
                for (unsigned int i = 0; i < frv->nData; i++) {
                    data(row, i) = (double) (frv->dataF[ i ]) * slope + offset;
                }
                break;
            case FR_VECT_8R:
                for (unsigned int i = 0; i < frv->nData; i++) {
                    data(row, i) = (double) (frv->dataD[ i ]) * slope + offset;
                }
                break;
            default:
                LogSevere("FrVectCopy: unknown type");
                throw std::runtime_error("FdChannel::Channel::PushFrVect - unknown type");
        }
    }



}
// end namespace tsa

