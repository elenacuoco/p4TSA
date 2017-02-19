#include <RealFFT.hpp>

namespace tsa {

    RealFFT::RealFFT(int size, enum FFTPlanningMode mode, bool PreserveInput)
    :
    BaseFFT(size, mode, PreserveInput) {

    }

    RealFFT::RealFFT(const RealFFT& from)
    :
    BaseFFT(from) {

    }

    RealFFT::~RealFFT() {

    }

    void RealFFT::operator()(SeqViewDouble& in, SeqViewComplex& out) {
        // Get data
        Dmatrix* data_in = in.GetData();
        Cmatrix* data_out = out.GetData();

        // Check dimensions
        if ((data_in->size1() != data_out->size1()) || (data_in->size2() / 2 + 1 != data_out->size2())) {
            LogWarning("RealFFT: resizing output array (%d,%d)->(%d,%d)", data_out->size1(), data_out->size2(), data_in->size1(), data_in->size2() / 2 + 1);
            data_out->resize(data_in->size1(), data_in->size2() / 2 + 1);
        }

        execute(*data_in, *data_out);


        // Adjust attributes
        out.SetStart(0.0);
        out.SetSampling(1.0 / in.GetSlice());
        out.SetScale(in.GetScale() * in.GetSampling());
    }

    void RealFFT::execute(Dmatrix& indata, Cmatrix& outdata) throw (bad_matrix_size) {

        if ((indata.size1() != outdata.size1()) || (indata.size2() / 2 + 1 != outdata.size2())) {
            LogSevere("RealFFT::execute - bad matrix size");
            throw bad_matrix_size("RealFFT::execute");
        }

        if (indata.size2() != mLogicalSize) {
            mPlanNeedsUpdate = true;
        }

        if (mPlanNeedsUpdate) {
            mLogicalSize = indata.size2();
            MakePlan();
        }

        size_t isize1 = indata.size1();

        for (size_t i = 0; i < isize1; i++) {


            fftw_execute_dft_r2c(
                    mPlan,
                    (double*) &indata(i, 0),
                    (fftw_complex*) & outdata(i, 0)
                    );


        }

    }

    void RealFFT::execute(Dmatrix& indata, Cmatrix& outdata, unsigned int size, unsigned int offset) throw (bad_matrix_size) {

        if ((indata.size1() != outdata.size1()) || (size / 2 + 1 != outdata.size2())) {
            LogSevere("RealFFT::execute - bad matrix size");
            throw bad_matrix_size("RealFFT::execute");
        }

        if (size != mLogicalSize) {
            mPlanNeedsUpdate = true;
        }

        if (mPlanNeedsUpdate) {
            mLogicalSize = size;
            MakePlan();
        }

        size_t isize1 = indata.size1();

        for (size_t i = 0; i < isize1; i++) {

            fftw_execute_dft_r2c(
                    mPlan,
                    (double*) &indata(i, offset),
                    (fftw_complex*) & outdata(i, 0)
                    );

        }

    }

    void RealFFT::execute(Dvector& indata, Cvector& outdata) throw (bad_vector_size) {

        if (indata.size() / 2 + 1 != outdata.size()) {
            LogSevere("RealFFT::execute - bad vector size");
            throw bad_vector_size("RealFFT::execute");
        }

        if (indata.size() != mLogicalSize) {
            mPlanNeedsUpdate = true;
        }

        if (mPlanNeedsUpdate) {
            mLogicalSize = indata.size();
            MakePlan();
        }

        fftw_execute_dft_r2c(
                mPlan,
                (double*) &indata(0),
                (fftw_complex*) & outdata(0)
                );

    }

    void RealFFT::MakePlan() throw (std::runtime_error) {
        LogInfo("RealFFT::MakePlan start");
        if (mPlan) {
            fftw_destroy_plan(mPlan);
        }
        double *in = (double*) fftw_malloc(sizeof (double)*mLogicalSize);
        fftw_complex *out = (fftw_complex*) fftw_malloc(sizeof (fftw_complex)*(mLogicalSize / 2 + 1));
        mPlan = fftw_plan_dft_r2c_1d(mLogicalSize, in, out, FFTW_UNALIGNED | mPlanningRigor | mPlanningRestriction);
        if (mPlan == NULL) {
            LogSevere("RealFFT::MakePlan - error");
            throw std::runtime_error("RealFFT::MakePlan");
        }
        fftw_free(in);
        fftw_free(out);
        mPlanNeedsUpdate = false;
        LogInfo("RealFFT::MakePlan end");
    }


} // -- end namespace tsa
