#include <BLInterpolation.hpp>

namespace tsa {

    BLInterpolation::BLInterpolation(unsigned int channels,
            unsigned int outdata,
            unsigned int irate,
            unsigned int orate,
            unsigned int order,
            double alpha,
            NormalizationType nt)
    :
    mChannels(channels),
    mOutData(outdata),
    mInputRate(irate),
    mOutputRate(orate),
    mOrder(order),
    mAlpha(alpha),
    mFilter(0),
    mNormalizationType(nt) {
        Init();
    }

    BLInterpolation::BLInterpolation(const BLInterpolation& from)
    :
    mChannels(from.mChannels),
    mOutData(from.mOutData),
    mInputRate(from.mInputRate),
    mOutputRate(from.mOutputRate),
    mOrder(from.mOrder),
    mAlpha(from.mAlpha),
    mFilter(0) {
        Init();
    }

    BLInterpolation::~BLInterpolation() {
        while (mRepository.size() > 0) {
            delete mRepository.front();
            mRepository.pop();
        }

        while (mBuffer.size() > 0) {
            delete mBuffer.front();
            mBuffer.pop_front();
        }
        if (mFilter != 0) {
            delete mFilter;
        }
    }

    BLInterpolation& BLInterpolation::operator=(const BLInterpolation& from) {
        mChannels = from.mChannels;
        mOutData = from.mOutData;
        mInputRate = from.mInputRate;
        mOutputRate = from.mOutputRate;
        mOrder = from.mOrder;
        mAlpha = from.mAlpha;
        mFilter = 0;

        Init();

        return *this;
    }



    BLInterpolation& BLInterpolation::Input(SeqViewDouble& indata) {
        Dmatrix* data_in = indata.GetData();

        if (mFirstData) {
            mStartTime = indata.GetStart();
            mSampling = indata.GetSampling();
            mFirstData = false;
        }

        SetData(*data_in, indata.GetScale());

        return *this;
    }

    BLInterpolation& BLInterpolation::Output(SeqViewDouble& outdata) {
        Dmatrix* data_out = outdata.GetData();
        if ((data_out->size1() != mChannels) || (data_out->size2() != mOutData)) {
            LogWarning("Resizing output data");
            data_out->resize(mChannels, mOutData);
        }

        unsigned int ret = GetData(*data_out);

        if (ret == 0) {
            LogWarning("No resampled data available");
            throw no_data_available("BLInterpolation::operator>>");
        }

        outdata.SetStart(mStartTime);
        outdata.SetSampling((mSampling * mInputRate) / mOutputRate);
        outdata.SetScale(1.0);

        mStartTime += (ret * mSampling * mInputRate) / mOutputRate;

        return *this;

    }

    double BLInterpolation::GetStartTime() {
        return mStartTime;
    }

    unsigned int BLInterpolation::GetData(Dmatrix& output) {
        if (resampled_available() < int(mOutData)) {
            LogDebug(LOG_DEBUG_LEVEL_2, "Failed: needed: %d Available: %ld", mOutData, resampled_available());
            return 0;
        }
        if (output.size1() != mChannels) {
            LogSevere("Bad number of channels");
            throw bad_matrix_size("BLInterpolation::GetData");
        }
        if (output.size2() != mOutData) {
            LogSevere("Bad number of data");
            throw bad_matrix_size("BLInterpolation::GetData");
        }

        LogDebug(LOG_DEBUG_LEVEL_2, "Success: needed: %d Available: %ld", mOutData, resampled_available());

        for (long int i = 0; i<int(mOutData); i++) {

            long int filter_bottom = mFilterCenter - mFilter->size() + 1;
            long int filter_top = mFilterCenter + mFilter->size() - 1;
            long int bptr = (filter_bottom - mBufferBase - 1 + mOutputRate) / mOutputRate;
            long int fptr = mOutputRate * bptr + mBufferBase;

            // For normalization only
            int offset = fptr - filter_bottom;

            for (long int j = 0; j<int(mChannels); j++) {
                output(j, i) = (*mBuffer[bptr])(j)*(*mFilter)(abs(mFilterCenter - fptr));
            }
            bptr++;
            fptr += mOutputRate;
            while (fptr <= filter_top) {
                for (long int j = 0; j<int(mChannels); j++) {
                    output(j, i) += (*mBuffer[bptr])(j)*(*mFilter)(abs(mFilterCenter - fptr));
                }
                bptr++;
                fptr += mOutputRate;
            }

            // Normalization
            for (long int j = 0; j<int(mChannels); j++) {
                output(j, i) *= mNormalization(offset);
            }

            mFilterCenter += mInputRate;
        }

        long int filter_bottom = mFilterCenter - mFilter->size() + 1;
        long int bptr = (filter_bottom - mBufferBase - 1 + mOutputRate) / mOutputRate;
        if (bptr > 0) {
            del_front_point(bptr);
        }
        long int delta = mBufferBase - (mBufferBase % (mInputRate * mOutputRate));
        mBufferBase -= delta;
        mFilterCenter -= delta;

        return mOutData;
        ;
    }

    void BLInterpolation::SetData(Dmatrix& input, double scale) {
        LogDebug(LOG_DEBUG_LEVEL_2, "SetData");
        if (input.size1() != mChannels) {
            LogSevere("Bad number of channels");
            throw bad_matrix_size("BLInterpolation::SetData");
        }
        for (unsigned int i = 0; i < input.size2(); i++) {

            add_back_point();

            for (unsigned int j = 0; j < mChannels; j++) {
                (*mBuffer.back())(j) = scale * input(j, i);
            }

        }
        LogDebug(LOG_DEBUG_LEVEL_2, "New buffer size is %d", mBuffer.size());
    }

    void BLInterpolation::Init() {
        unsigned int gcd = MathUtils::gcd(mInputRate, mOutputRate);
        mInputRate /= gcd;
        mOutputRate /= gcd;
        LogInfo("Reduced rates: Input = %d  Output = %d", mInputRate, mOutputRate);
        mRho = double(mOutputRate) / double(mInputRate);
        mRho = (mRho < 1.0) ? mRho : 1.0;
        unsigned int maxrate = (mInputRate > mOutputRate) ? mInputRate : mOutputRate;
        LogDebug(LOG_DEBUG_LEVEL_2, "Prepare the lookup table. length = %d rho = %f", mOrder * maxrate + 1, mRho);
        if (mFilter == 0) {
            delete mFilter;
        }
        mFilter = new Dvector(mOrder * maxrate + 1);
        if (mFilter == 0) {
            LogSevere("Memory allocation error");
            throw std::runtime_error("Memory allocation error");
        }

        for (unsigned i = 0; i < mFilter->size(); i++) {
            (*mFilter)(i) = mRho * gsl_sf_sinc(double(i) / maxrate) * Kaiser(double(i) / (mFilter->size() - 1));
        }

        switch (mNormalizationType) {
            case DCNormalization:
                DCRenormalization();
                break;
            case NONormalization:
            default:
                NORenormalization();
                break;
        }

        mBufferBase = 0;
        mFilterCenter = (1 + (mOrder * maxrate) / mOutputRate) * mOutputRate;

        for (int i = 0; i < mFilterCenter; i += mOutputRate) {
            add_back_point();
            for (unsigned int j = 0; j < mChannels; j++) {
                (*mBuffer.back())(j) = 0.0;
            }

        }

        mFirstData = true;

        LogDebug(LOG_DEBUG_LEVEL_2, "End Init()");
    }

    double BLInterpolation::Kaiser(double w) {
        double q = M_PI*mAlpha;
        return gsl_sf_bessel_I0(q * sqrt(1.0 - w * w)) / gsl_sf_bessel_I0(q);
    }

    void BLInterpolation::add_back_point() {
        if (mRepository.empty()) {
            mBuffer.push_back(new Dvector(mChannels));
        } else {
            mBuffer.push_back(mRepository.front());
            mRepository.pop();
        }
    }

    void BLInterpolation::del_front_point(unsigned int n) {
        while ((n > 0) && (mBuffer.size() > 0)) {
            mRepository.push(mBuffer.front());
            //Dvector* tmp=mBuffer.front();
            mBuffer.pop_front();
            //delete tmp;
            mBufferBase += mOutputRate;
            n--;
        }
    }

    long int BLInterpolation::resampled_available() {
        long int filter_top = mFilterCenter + mFilter->size();
        long int buffer_top = mBufferBase + mOutputRate * mBuffer.size();
        long int avail = (buffer_top - filter_top) / mInputRate;
        return (avail > 0) ? avail : 0;
    }

    void BLInterpolation::NORenormalization() {
        mNormalization.resize(mInputRate);

        for (int offset = 0; offset<int(mInputRate); offset++) {
            mNormalization(offset) = 1.0;
        }

    }

    void BLInterpolation::DCRenormalization() {
        mNormalization.resize(mInputRate);

        for (int offset = 0; offset<int(mInputRate); offset++) {
            mNormalization(offset) = 0.0;
            for (int k = -int(mFilter->size() - 1) + offset; k<int(mFilter->size()); k += mOutputRate) {
                mNormalization(offset) += (*mFilter)(abs(k));
            }
            mNormalization(offset) = 1.0 / mNormalization(offset);
            //LogDebug(LOG_DEBUG_LEVEL_2,"Offset: %d Norm: %g",offset,mNormalization(offset));
        }

    }


}


