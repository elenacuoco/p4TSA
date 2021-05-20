#include <ARMAFilter.hpp>

namespace tsa {

        ARMAFilter::ARMAFilter(unsigned int ARorder, unsigned int MAorder, double gain):
        mAR(ARorder),
        mMA(MAorder),
        mGain(1.0 / gain),
        mInPointer(0),
        mOutPointer(0),
        mInBuffer(mMA.size()),
        mOutBuffer(mAR.size())
        {
        mInBuffer.clear();
        mOutBuffer.clear();
        };

         


    ARMAFilter::~ARMAFilter() {

    }
    void ARMAFilter::SetARFilter( unsigned int i, double AR)
    {
         mAR(i) = AR ;
         
    }
    void ARMAFilter::SetMAFilter( unsigned int i, double MA)
    {
          mMA(i) = MA;
         
    }
    void ARMAFilter::operator()(SeqViewDouble& in, SeqViewDouble& out) {
        Dmatrix* data_in = in.GetData();
        Dmatrix* data_out = out.GetData();

        if (data_in->size1() != 1) {

        }
        if ((data_in->size2() != data_out->size2()) || (data_in->size1() != data_out->size1())) {
            data_out->resize(data_in->size1(), data_in->size2());
            LogWarning("ARMAFilter: resizing output view");
        }

        execute(*data_in, *data_out, in.GetScale());


        // Adjust attributes
        out.SetStart(in.GetStart());
        out.SetSampling(in.GetSampling());
        out.SetScale(1.0);
    }

    void ARMAFilter::execute(Dmatrix& in, Dmatrix& out, double scale) {
        unsigned int data = in.size2();
        int m = mAR.size();
        int n = mMA.size();
        // ---- filters all the data ----
        for (unsigned int i = 0; i < data; i++) {
            mInBuffer(mInPointer) = mGain * scale * in(0, i);
            long double val = 0.0;
            for (int j = 0; j < n; j++) val += mMA[j] * mInBuffer((mInPointer + j) % n);
            for (int j = 1; j < m; j++) val += mAR[j] * mOutBuffer((mOutPointer + j) % m);
            mOutBuffer(mOutPointer) = val;
            out(0, i) = val;
            //fprintf(stderr,"%g\n",out(0,i));
            mInPointer = ((mInPointer - 1 + n) % n);
            mOutPointer = ((mOutPointer - 1 + m) % m);
        }
    }

   


}
