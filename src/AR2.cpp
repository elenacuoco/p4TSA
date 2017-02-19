#include <AR2.hpp>

namespace tsa {

    AR2::AR2(const double f, const double gamma, const double h) {
        double w = 2.0 * M_PI*f;
        double scale = 1.0 + 0.5 * gamma*h;
        mA = (2.0 - w * w * h * h) / scale;
        mB = (0.5 * gamma * h - 1.0) / scale;
        mC = h * h / scale;
        mXm1 = 0.0;
        mXm2 = 0.0;
    }

    AR2::~AR2() {

    }

    void AR2::operator()(SeqViewDouble& in, SeqViewDouble& out) {
        Dmatrix* data_in = in.GetData();
        Dmatrix* data_out = out.GetData();

        if ((data_in->size2() != data_out->size2()) || (data_in->size1() != data_out->size1())) {
            data_out->resize(data_in->size1(), data_in->size2());
            LogWarning("AR2: resizing output view");
        }

        execute(*data_in, *data_out, in.GetScale());

        // Adjust attributes
        out.SetStart(in.GetStart());
        out.SetSampling(in.GetSampling());
        out.SetScale(1.0);
    }

    void AR2::execute(Dmatrix& in, Dmatrix& out, double scale) {
        unsigned int data = in.size2();
        unsigned int chan = in.size1();
        // filters all the data
        for (unsigned int i = 0; i < data; i++) {
            out(0, i) = mA * mXm1 + mB * mXm2 + scale * mC * in(0, i);
            mXm2 = mXm1;
            mXm1 = out(0, i);
        }
    }


}
