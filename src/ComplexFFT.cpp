#include <ComplexFFT.hpp>

using namespace boost::numeric::ublas;

namespace tsa {

    ComplexFFT::ComplexFFT(int size, enum TransformSign s, enum FFTPlanningMode mode, bool PreserveInput)
    :
    BaseFFT(size, mode, PreserveInput) {
        mSign = s;
    }

    ComplexFFT::ComplexFFT(const ComplexFFT& from)
    :
    BaseFFT(from) {
        mSign = from.mSign;
    }

    ComplexFFT::~ComplexFFT() {

    }

    void ComplexFFT::execute(Cmatrix& indata, Cmatrix& outdata) throw (bad_matrix_size) {
        if ((indata.size1() != outdata.size1()) || (indata.size2() != outdata.size2())) {
            throw bad_matrix_size("ComplexFFT::execute");
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

            fftw_execute_dft(
                    mPlan,
                    (fftw_complex*) & indata(i, 0),
                    (fftw_complex*) & outdata(i, 0)
                    );

        }
    }

    void ComplexFFT::MakePlan() throw (std::runtime_error) {
        if (mPlan) {
            fftw_destroy_plan(mPlan);
        }
        fftw_complex *in = (fftw_complex*) fftw_malloc(sizeof (fftw_complex) * mLogicalSize);
        fftw_complex *out = (fftw_complex*) fftw_malloc(sizeof (fftw_complex) * mLogicalSize);
        mPlan = fftw_plan_dft_1d(mLogicalSize, in, out, mSign, FFTW_UNALIGNED | mPlanningRigor | mPlanningRestriction);
        if (mPlan == NULL) {
            throw std::runtime_error("ComplexFFT::MakePlan");
        }
        fftw_free(in);
        fftw_free(out);
        mPlanNeedsUpdate = true;
    }

    void ComplexFFT::SetSign(enum TransformSign s) {
        int SignNew = FFTW_FORWARD;
        switch (s) {
            case FORWARD:
                SignNew = FFTW_FORWARD;
                break;
            case BACKWARD:
                SignNew = FFTW_BACKWARD;
                break;
        }
        if (SignNew != mSign) {
            mSign = SignNew;
            mPlanNeedsUpdate = true;
        }
    }

} // -- end namespace tsa
