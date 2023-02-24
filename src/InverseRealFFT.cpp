#include <InverseRealFFT.hpp>

namespace tsa {

    InverseRealFFT::InverseRealFFT(int size, enum FFTPlanningMode mode, bool PreserveInput)
    :
    BaseFFT(size, mode, PreserveInput) {

    }

    InverseRealFFT::InverseRealFFT(const InverseRealFFT& from)
    :
    BaseFFT(from) {

    }

    InverseRealFFT::~InverseRealFFT() {

    }

    void InverseRealFFT::execute(Cmatrix& indata, Dmatrix& outdata)  {
        if ((indata.size1() != outdata.size1()) || (outdata.size2() / 2 + 1 != indata.size2())) {
            LogSevere("bad_matrix_size:InverseRealFFT::execute");
        }

        if (outdata.size2() != mLogicalSize) {
            mPlanNeedsUpdate = true;
        }
        if (mPlanNeedsUpdate) {
            mLogicalSize = outdata.size2();
            MakePlan();
        }

        size_t isize1 = indata.size1();

        for (size_t i = 0; i < isize1; i++) {

            fftw_execute_dft_c2r(
                    mPlan,
                    (fftw_complex*) & indata(i, 0),
                    (double*) &outdata(i, 0)
                    );

        }
    }

    void InverseRealFFT::operator()(SeqViewComplex& in, SeqViewDouble& out) {
        // Get data
        Cmatrix* data_in = in.GetData();
        Dmatrix* data_out = out.GetData();

        // Check dimensions
        if ((data_in->size1() != data_out->size1()) || (data_out->size2() / 2 + 1 != data_in->size2())) {
            LogWarning("InverseRealFFT: resizing output array (%d,%d)->(%d,%d)", data_out->size1(), data_out->size2(), data_in->size1(), 2 * (data_in->size2() - 1));
            data_out->resize(data_in->size1(), 2 * (data_in->size2() - 1));
        }

        execute(*data_in, *data_out);


        // Adjust attributes
        out.SetStart(0.0);
        out.SetSampling(1.0 / in.GetSlice());
        out.SetScale(in.GetScale() * in.GetSampling());


    }

    void InverseRealFFT::execute(Cvector& indata, Dvector& outdata)  {
        if ((indata.size() != outdata.size() / 2 + 1)) {
            LogSevere("bad_vector_size:InverseRealFFT::execute");
        }
        if (outdata.size() != mLogicalSize) {
            mPlanNeedsUpdate = true;
        }
        if (mPlanNeedsUpdate) {
            mLogicalSize = outdata.size();
            MakePlan();
        }

        fftw_execute_dft_c2r(
                mPlan,
                (fftw_complex*) & indata(0),
                (double*) &outdata(0)
                );
    }

    void InverseRealFFT::execute(CmatrixRow& indata, DmatrixRow& outdata)  {
        if ((indata.size() != outdata.size() / 2 + 1)) {
            LogSevere("bad_vector_size: InverseRealFFT::execute");
        }
        if (outdata.size() != mLogicalSize) {
            mPlanNeedsUpdate = true;
        }
        if (mPlanNeedsUpdate) {
            mLogicalSize = outdata.size();
            MakePlan();
        }

        fftw_execute_dft_c2r(
                mPlan,
                (fftw_complex*) & indata(0),
                (double*) &outdata(0)
                );
    }

    void InverseRealFFT::execute(CmatrixRow& indata, DmatrixRow& outdata, unsigned int insize)
      {
        if (insize > indata.size()) {
            LogSevere( "bad_vector_size: InverseRealFFT::execute");
        }
        if ((insize != outdata.size() / 2 + 1)) {
            LogSevere("bad_vector_size: InverseRealFFT::execute");
        }
        if (outdata.size() != mLogicalSize) {
            mPlanNeedsUpdate = true;
        }
        if (mPlanNeedsUpdate) {
            mLogicalSize = outdata.size();
            MakePlan();
        }

        fftw_execute_dft_c2r(
                mPlan,
                (fftw_complex*) & indata(0),
                (double*) &outdata(0)
                );
    }

    void InverseRealFFT::MakePlan()  {
        if (mPlan) {
            fftw_destroy_plan(mPlan);
        }

        fftw_complex *in = (fftw_complex*) fftw_malloc(sizeof (fftw_complex)*(mLogicalSize / 2 + 1));
        double *out = (double*) fftw_malloc(sizeof (double)*mLogicalSize);

        mPlan = fftw_plan_dft_c2r_1d(mLogicalSize, in, out, FFTW_UNALIGNED | mPlanningRigor | mPlanningRestriction);
        if (mPlan == NULL) {
            LogSevere("runtime_error: InverseRealFFT::MakePlan");
        }
        fftw_free(in);
        fftw_free(out);
        mPlanNeedsUpdate = true;
    }

} // -- end namespace tsa
