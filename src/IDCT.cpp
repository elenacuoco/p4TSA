#include <IDCT.hpp>

namespace tsa {

    IDCT::IDCT(int size, enum FFTPlanningMode mode, bool PreserveInput)
    :
    BaseFFT((2 * size - 1), mode, PreserveInput) {

    }

    IDCT::IDCT(const IDCT& from)
    :
    BaseFFT(from) {

    }

    IDCT::~IDCT() {

    }

    void IDCT::operator()(SeqViewDouble& in, SeqViewDouble& out) {
        // Get data
        Dmatrix* data_in = in.GetData();
        Dmatrix* data_out = out.GetData();

        // Check dimensions
        if ((data_in->size1() != data_out->size1()) || (data_in->size2() != data_out->size2())) {
            data_out->resize(data_in->size1(), data_in->size2());
            LogWarning("IDCT: resizing output array");
        }

        execute(*data_in, *data_out);


        // Adjust attributes
        out.SetStart(0.0);
        out.SetSampling(1.0 / in.GetSlice());
        out.SetScale(in.GetScale() * in.GetSampling() / in.GetSize());

    }

    void IDCT::execute(Dmatrix& indata, Dmatrix& outdata)  {

        if ((indata.size1() != outdata.size1()) || (indata.size2() != outdata.size2())) {
            LogSevere("IDCT::execute - bad matrix size");
           
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

            fftw_execute_r2r(
                    mPlan,
                    (double*) &indata(i, 0),
                    (double*) &outdata(i, 0)
                    );
        }

    }

    void IDCT::execute(Dvector& indata, Dvector& outdata)  {

        if (indata.size() != outdata.size()) {
            LogSevere("IDCT::execute - bad vector size");
           
        }

        if (indata.size() != mLogicalSize) {
            mPlanNeedsUpdate = true;
        }

        if (mPlanNeedsUpdate) {
            mLogicalSize = indata.size();
            MakePlan();
        }

        fftw_execute_r2r(
                mPlan,
                (double*) &indata(0),
                (double*) &outdata(0)
                );

    }

    void IDCT::MakePlan()  {
        LogInfo("IDCT::MakePlan start");
        if (mPlan) {
            fftw_destroy_plan(mPlan);
        }
        double *in = (double*) fftw_malloc(sizeof (double)*mLogicalSize);
        double *out = (double*) fftw_malloc(sizeof (double)*((mLogicalSize / 2) + 1));
        
        mPlan = fftw_plan_r2r_1d(mLogicalSize, in, out, FFTW_REDFT01, FFTW_UNALIGNED | mPlanningRigor | mPlanningRestriction);
        if (mPlan == NULL) {
            LogSevere("IDCT::MakePlan - error");
           
        }
        fftw_free(in);
        fftw_free(out);
        mPlanNeedsUpdate = false;
        LogInfo("IDCT::MakePlan end");
    }


 

} // -- end namespace tsa
