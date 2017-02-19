#include <ButterworthFilter.hpp>

using namespace boost::numeric::ublas;

namespace tsa {

    ButterworthFilter::ButterworthFilter(double freq, int order)
    :
    mFreq(freq),
    mOrder(order) {
        poles = new Cdouble[order];
        switch (order) {
            case 1:
                poles[0] = 1.0;
                break;
            case 2:
                poles[0] = 1.4142;
                poles[1] = 1.0;
        }
    }

    ButterworthFilter::~ButterworthFilter() {
        delete[] poles;
    }

    void ButterworthFilter::operator()(SeqViewComplex& data) {
        Cmatrix* arg1 = data.GetData();

        double fstart = data.GetStart();
        double fsampl = data.GetSampling();
        double scale = data.GetScale();


        data.SetStart(fstart);
        data.SetSampling(fsampl);
        data.SetScale(1.0);

        ButterworthFilter::execute(*arg1, fstart, fsampl, scale);


    }

    void ButterworthFilter::operator()(SeqViewComplex& datain, SeqViewComplex& dataout) {
        Cmatrix* arg1 = datain.GetData();
        Cmatrix* arg2 = dataout.GetData();

        if ((arg1->size1() != arg2->size1()) || (arg1->size2() != arg2->size2())) {
            LogWarning("Resizing output view");
            arg2->resize(arg1->size1(), arg1->size2());
        }

        double fstart = datain.GetStart();
        double fsampl = datain.GetSampling();
        double scale = datain.GetScale();


        dataout.SetStart(fstart);
        dataout.SetSampling(fsampl);
        dataout.SetScale(1.0);

        ButterworthFilter::execute(*arg1, *arg2, fstart, fsampl, scale);
    }

    void ButterworthFilter::execute(Cmatrix &dataout, double fstart, double fsample, double scale) {
        for (size_t i = 0; i < dataout.size2(); i++) {
            double f = i*fsample;
            Cdouble v = 1.0;
            Cdouble s = Cdouble(0, f / mFreq);
            Cdouble sN = s;

            for (int i = 0; i < mOrder; i++) {
                v += poles[i] * sN;
                sN *= s;
            }
            dataout(0, i) = 1.0 / v;
        }
    }

    void ButterworthFilter::execute(Cmatrix& datain, Cmatrix& dataout, double fstart, double fsample, double scale) {

        for (size_t i = 0; i < dataout.size2(); i++) {
            double f = i*fsample;
            Cdouble v = 1.0;
            Cdouble s = Cdouble(0, f / mFreq);
            Cdouble sN = s;

            for (int i = 0; i < mOrder; i++) {
                v += poles[i] * sN;
                sN *= s;
            }
            dataout(0, i) = datain(0, i) / v;
        }
    }

}

