#include <FifoBuffer.hpp>

namespace tsa {

    FifoBuffer::FifoBuffer(unsigned int channels)
    :
    mChannels(channels) {


    }

    FifoBuffer::FifoBuffer(const FifoBuffer& from)
    :
    mChannels(from.mChannels) {

    }

    FifoBuffer::~FifoBuffer() {
        while (mRepository.size() > 0) {
            delete mRepository.front();
            mRepository.pop();
        }

        while (mBuffer.size() > 0) {
            delete mBuffer.front();
            mBuffer.pop_front();
        }

    }

    FifoBuffer& FifoBuffer::operator=(const FifoBuffer& from) {

        while (mRepository.size() > 0) {
            delete mRepository.front();
            mRepository.pop();
        }

        while (mBuffer.size() > 0) {
            delete mBuffer.front();
            mBuffer.pop_front();
        }

        mChannels = from.mChannels;

        return *this;
    }

    void FifoBuffer::AddPoint() {
        if (mRepository.empty()) {
            mBuffer.push_back(new Dvector(mChannels));
        } else {
            mBuffer.push_back(mRepository.front());
            mRepository.pop();
        }
    }

    void FifoBuffer::AddPoint(Dvector& data, double scale) {
        if (mRepository.empty()) {
            mBuffer.push_back(new Dvector(mChannels));
        } else {
            mBuffer.push_back(mRepository.front());
            mRepository.pop();
        }
        Dvector *p = mBuffer.back();

        for (int k = 0; k<int(mChannels); k++) {
            (*p)(k) = scale * data(k);
        }

    }

    void FifoBuffer::AddPoints(Dmatrix& data, double scale, int n, int offset) {
        if (n == 0) n = data.size2() - offset;

        for (int i = 0; i < n; i++) {

            if (mRepository.empty()) {
                mBuffer.push_back(new Dvector(mChannels));
            } else {
                mBuffer.push_back(mRepository.front());
                mRepository.pop();
            }

            Dvector *p = mBuffer.back();

            for (int k = 0; k<int(mChannels); k++) {
                (*p)(k) = scale * data(k, i + offset);
            }
        }

    }

    void FifoBuffer::DelPoints(int n) {
        while ((n > 0) && (mBuffer.size() > 0)) {
            mRepository.push(mBuffer.front());
            n--;
            mBuffer.pop_front();

        }

    }





}
