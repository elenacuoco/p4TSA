#include <BaseWindow.hpp>

namespace tsa {

    BaseWindow::BaseWindow(unsigned int size) {
        mWindow.resize(size);
        mWindow.clear();
    }

    BaseWindow::~BaseWindow() {

    }

    void BaseWindow::operator()(SeqViewDouble& v1) {

    }

    void BaseWindow::operator()(SeqViewDouble& v1, SeqViewDouble& v2) {

    }

    void BaseWindow::execute(Dmatrix& in, Dmatrix& out) {
        unsigned int rows = in.size1();
        for (unsigned int ch = 0; ch < rows; ch++) {
            for (unsigned int i = 0; i < mWindow.size(); i++) {
                out(ch, i) = in(ch, i) * mWindow(i);
            }
        }
    }

    void BaseWindow::execute(Dmatrix& in, Dmatrix& out, unsigned int offset) {
        unsigned int rows = in.size1();
        for (unsigned int ch = 0; ch < rows; ch++) {
            for (unsigned int i = 0; i < mWindow.size(); i++) {
                out(ch, i) = in(ch, i + offset) * mWindow(i);
            }
        }
    }

    void BaseWindow::execute(Dmatrix& inout) {
        unsigned int rows = inout.size1();
        for (unsigned int ch = 0; ch < rows; ch++) {
            for (unsigned int i = 0; i < mWindow.size(); i++) {
                inout(ch, i) *= mWindow(i);
            }
        }
    }

    void BaseWindow::execute(Dvector& inout) {
        for (unsigned int i = 0; i < mWindow.size(); i++) {
            inout(i) *= mWindow(i);
        }
    }

    double BaseWindow::operator()(int i) {
        return mWindow(i);
    }

    void BaseWindow::Resize(unsigned int size) {
        mWindow.resize(size);
        mWindow.clear();
    }

    unsigned int BaseWindow::GetSize() {
        return mWindow.size();
    }

    void BaseWindow::FillWindow() {
    }

    void BaseWindow::Normalize() {
        unsigned int wsize = mWindow.size();
        double norm = 0.0;
        for (unsigned int i = 0; i < wsize; i++) {
            norm += mWindow(i) * mWindow(i);
        }
        norm = sqrt(wsize / norm);
        for (unsigned int i = 0; i < wsize; i++) {
            mWindow(i) *= norm;
        }
    }

    double BaseWindow::CrossAverage(BaseWindow& w1, BaseWindow& w2) {
        unsigned int wsize1 = w1.GetSize();
        unsigned int wsize2 = w2.GetSize();
        unsigned int wsize;

        if (wsize1 > wsize2) {
            w2.Resize(wsize1);
            wsize = wsize1;
        } else {
            w1.Resize(wsize2);
            wsize = wsize2;
        }
        double W1W2 = 0.0;
        for (unsigned int i = 0; i < wsize; i++) {
            W1W2 += w1(i) * w2(i);
        }
        W1W2 /= wsize;
        w1.Resize(wsize1);
        w2.Resize(wsize2);

        return W1W2;
    }

    double BaseWindow::CrossSquareAverage(BaseWindow& w1, BaseWindow& w2) {
        unsigned int wsize1 = w1.GetSize();
        unsigned int wsize2 = w2.GetSize();
        unsigned int wsize;

        if (wsize1 > wsize2) {
            w2.Resize(wsize1);
            wsize = wsize1;
        } else {
            w1.Resize(wsize2);
            wsize = wsize2;
        }
        double W1W2 = 0.0;
        for (unsigned int i = 0; i < wsize; i++) {
            W1W2 += w1(i) * w1(i) * w2(i) * w2(i);
        }
        W1W2 /= wsize;
        w1.Resize(wsize1);
        w2.Resize(wsize2);

        return W1W2;
    }




};
