#include <ViewUtil.hpp>
#include <iomanip>

namespace tsa {

    std::complex<double> ViewUtil::DelayIntegrate(SeqViewComplex& data, double tau, double f1, double f2) {
        Cmatrix* d = data.GetData();
        double scale = data.GetScale();
        std::complex<double> sum = 0.0;
        unsigned int i1 = (f1 - data.GetStart()) / data.GetSampling();
        unsigned int i2 = (f2 - data.GetStart()) / data.GetSampling();
        for (unsigned int i = i1; i <= i2; i++) {
            std::complex<double> ex = std::exp(std::complex<double>(0.0, 2.0 * M_PI * i * data.GetSampling() * tau));
            sum += (*d)(0, i) * ex;
        }
        sum *= scale * data.GetSampling();
        return sum;
    }

    std::complex<double> ViewUtil::DelayIntegrate(SeqViewDouble& data, double tau, double f1, double f2) {
        Dmatrix* d = data.GetData();
        double scale = data.GetScale();
        std::complex<double> sum = 0.0;
        unsigned int i1 = (f1 - data.GetStart()) / data.GetSampling();
        unsigned int i2 = (f2 - data.GetStart()) / data.GetSampling();
        for (unsigned int i = i1; i <= i2; i++) {
            std::complex<double> ex = std::exp(std::complex<double>(0.0, 2.0 * M_PI * i * data.GetSampling() * tau));
            sum += (*d)(0, i) * ex;
        }
        sum *= scale * data.GetSampling();
        return sum;
    }

    std::complex<double> ViewUtil::Integrate(SeqViewComplex& data, double f1, double f2) {
        Cmatrix* d = data.GetData();
        double scale = data.GetScale();
        std::complex<double> sum = 0.0;
        unsigned int i1 = (f1 - data.GetStart()) / data.GetSampling();
        unsigned int i2 = (f2 - data.GetStart()) / data.GetSampling();
        for (unsigned int i = i1; i <= i2; i++) {
            sum += (*d)(0, i);
        }
        sum *= scale * data.GetSampling();
        return sum;
    }

    double ViewUtil::Integrate(SeqViewDouble& data, double f1, double f2) {
        Dmatrix* d = data.GetData();
        double scale = data.GetScale();
        double sum = 0.0;
        unsigned int i1 = (f1 - data.GetStart()) / data.GetSampling();
        unsigned int i2 = (f2 - data.GetStart()) / data.GetSampling();
        for (unsigned int i = i1; i <= i2; i++) {
            sum += (*d)(0, i);
        }
        sum *= scale * data.GetSampling();
        return sum;
    }

    void ViewUtil::Print(SeqViewDouble& s1, char * filename) {
        unsigned int channels = s1.GetChannels();
        unsigned int len = s1.GetSize();

        std::ofstream out(filename);

        out << std::setiosflags(std::ios::scientific) << std::setprecision(20);

        for (unsigned int i = 0; i < len; i++) {

            out << s1.GetX(i) << " ";

            for (unsigned int j = 0; j < channels; j++) {

                out << s1(j, i) << " ";

            }

            out << "\n";

        }

    }

    void ViewUtil::Print(SeqViewComplex& s1, char * filename) {
        unsigned int channels = s1.GetChannels();
        unsigned int len = s1.GetSize();

        std::ofstream out(filename);

        out << std::setiosflags(std::ios::scientific) << std::setprecision(20);

        for (unsigned int i = 0; i < len; i++) {

            out << s1.GetX(i) << " ";

            for (unsigned int j = 0; j < channels; j++) {

                out << abs(s1(j, i)) << " " << arg(s1(j, i)) << " ";

            }

            out << "\n";

        }

    }

    void ViewUtil::Print(SeqViewDouble& s1) {
        unsigned int channels = s1.GetChannels();
        unsigned int len = s1.GetSize();


        for (unsigned int i = 0; i < len; i++) {

            std::cout << s1.GetX(i) << " ";

            for (unsigned int j = 0; j < channels; j++) {

                std::cout << s1(j, i) << " ";

            }

            std::cout << "\n";

        }

    }

    void ViewUtil::Range(SeqViewDouble& s1, int l, int m) {
        Dmatrix* data = s1.GetData();

        if (l < 0) {
            l = data->size2() + l;
            if (l < 0) {
                LogSevere("Bad index");
                throw std::runtime_error("ViewUtil::Range - Bad index");
            }
        }
        if (m < 0) {
            m = data->size2() + m;
            if (m < 0) {
                LogSevere("Bad index");
                throw std::runtime_error("ViewUtil::Range - Bad index");
            }
        }
        if (((unsigned int) l >= data->size2()) || ((unsigned int) m >= data->size2())) {
            LogSevere("Bad index");
            throw std::runtime_error("ViewUtil::Range - Bad index");
        }


        unsigned int ch = data->size1();
        unsigned int nsz = (l > m) ? l - m + 1 : m - l + 1;
        unsigned int mn = (l > m) ? m : l;

        for (unsigned int i = 0; i < ch; i++) {
            for (unsigned int j = 0; j < nsz; j++) {
                (*data)(i, j) = (*data)(i, j + mn);
            }
        }

        data->resize(data->size1(), nsz);
        s1.SetStart(s1.GetStart() + mn * s1.GetSampling());
    }

    void ViewUtil::Range(SeqViewComplex& s1, int l, int m) {
        Cmatrix* data = s1.GetData();

        if (l < 0) {
            l = data->size2() + l;
            if (l < 0) {
                LogSevere("Bad index");
                throw std::runtime_error("ViewUtil::Range - Bad index");
            }
        }
        if (m < 0) {
            m = data->size2() + m;
            if (m < 0) {
                LogSevere("Bad index");
                throw std::runtime_error("ViewUtil::Range - Bad index");
            }
        }
        if (((unsigned int) l >= data->size2()) || ((unsigned int) m >= data->size2())) {
            LogSevere("Bad index");
            throw std::runtime_error("ViewUtil::Range - Bad index");
        }

        unsigned int ch = data->size1();
        unsigned int nsz = (l > m) ? l - m + 1 : m - l + 1;
        unsigned int mn = (l > m) ? m : l;

        for (unsigned int i = 0; i < ch; i++) {
            for (unsigned int j = 0; j < nsz; j++) {
                (*data)(i, j) = (*data)(i, j + mn);
            }
        }

        data->resize(data->size1(), nsz);
        s1.SetStart(s1.GetStart() + mn * s1.GetSampling());
    }

    void ViewUtil::Range(SeqViewDouble& s1, SeqViewDouble& s2, int l, int m) {
        Dmatrix* data = s1.GetData();
        Dmatrix* res = s2.GetData();
        if (l < 0) {
            l = data->size2() + l;
            if (l < 0) {
                LogSevere("Bad index");
                throw std::runtime_error("ViewUtil::Range - Bad index");
            }
        }
        if (m < 0) {
            m = data->size2() + m;
            if (m < 0) {
                LogSevere("Bad index");
                throw std::runtime_error("ViewUtil::Range - Bad index");
            }
        }
        if (((unsigned int) l >= data->size2()) || ((unsigned int) m >= data->size2())) {
            LogSevere("Bad index");
            throw std::runtime_error("ViewUtil::Range - Bad index");
        }


        //unsigned int sz = data->size2();
        unsigned int ch = data->size1();
        unsigned int nsz = (l > m) ? l - m + 1 : m - l + 1;
        unsigned int mn = (l > m) ? m : l;

        if ((res->size1() != data->size1()) || (res->size2() != nsz)) {
            LogWarning("ViewUtil::Range - resizing output view");
            res->resize(data->size1(), nsz);
        }

        for (unsigned int i = 0; i < ch; i++) {
            for (unsigned int j = 0; j < nsz; j++) {
                (*res)(i, j) = (*data)(i, j + mn);
            }
        }
        s2.SetStart(s1.GetStart() + mn * s1.GetSampling());
        s2.SetSampling(s1.GetSampling());
        s2.SetScale(s1.GetScale());

    }

    void ViewUtil::Join(std::vector<SeqViewComplex>& sl, SeqViewComplex& joined, double start, double sampling, unsigned int length) {
        unsigned int totsize = 0;
        for (std::vector<SeqViewComplex>::iterator pc = sl.begin(); pc != sl.end(); pc++) {
            totsize += pc->GetChannels();
        }

        Cmatrix* datar = joined.GetData();
        if ((datar->size1() != totsize) || (datar->size2() != length)) {
            LogWarning("Join: resizing output view: %d %d", totsize, length);
            datar->resize(totsize, length);
        }
        joined.SetScale(1.0);
        joined.SetStart(start);
        joined.SetSampling(sampling);

        unsigned int row = 0;
        for (std::vector<SeqViewComplex>::iterator pc = sl.begin(); pc != sl.end(); pc++) {
            double scale = pc->GetScale();
            Cmatrix* datas = pc->GetData();

            for (unsigned int i = 0; i < datas->size1(); i++) {

                if (datas->size2() >= length) {
                    for (unsigned int j = 0; j < length; j++) {
                        (*datar)(row, j) = scale * (*datas)(i, j);
                    }
                } else {
                    unsigned int j;
                    for (j = 0; j < datas->size2(); j++) {
                        (*datar)(row, j) = scale * (*datas)(i, j);
                    }
                    for (; j < length; j++) {
                        (*datar)(row, j) = std::complex<double>(1.0, 0.0);
                    }
                }
                row++;

            }
        }
    }

    void ViewUtil::Join(std::vector<SeqViewDouble>& sl, SeqViewDouble& joined, double start, double sampling, unsigned int length) {
        unsigned int totsize = 0;
        for (std::vector<SeqViewDouble>::iterator pc = sl.begin(); pc != sl.end(); pc++) {
            totsize += pc->GetChannels();
        }

        Dmatrix* datar = joined.GetData();
        if ((datar->size1() != totsize) || (datar->size2() != length)) {
            LogWarning("Join: resizing output view");
            datar->resize(totsize, length);
        }
        joined.SetScale(1.0);
        joined.SetStart(start);
        joined.SetSampling(sampling);

        unsigned int row = 0;
        for (std::vector<SeqViewDouble>::iterator pc = sl.begin(); pc != sl.end(); pc++) {

            double scale = pc->GetScale();

            Dmatrix* datas = pc->GetData();

            for (unsigned int i = 0; i < datas->size1(); i++) {
                if (datas->size2() >= length) {
                    for (unsigned int j = 0; j < length; j++) {
                        (*datar)(row, j) = scale * (*datas)(i, j);
                    }
                } else {
                    unsigned int j;
                    for (j = 0; j < datas->size2(); j++) {
                        (*datar)(row, j) = scale * (*datas)(i, j);
                    }
                    for (; j < length; j++) {
                        (*datar)(row, j) = 0.0;
                    }
                }
                row++;
            }
        }
    }

    void ViewUtil::Join(SeqViewDouble& s1, SeqViewDouble& s2, SeqViewDouble& joined) {
        Dmatrix* data1 = s1.GetData();
        Dmatrix* data2 = s2.GetData();
        Dmatrix* datar = joined.GetData();

        double scale1 = s1.GetScale();
        double scale2 = s2.GetScale();


        if (data1->size2() != data2->size2()) {
            LogSevere("Views of different length");
            throw std::runtime_error("ViewUtil::Join");
        }

        Dmatrix tmp(data1->size1() + data2->size1(), data1->size2());

        unsigned int sz1 = data1->size1();
        unsigned int sz2 = data1->size2();

        for (unsigned int i = 0; i < sz1; i++) {
            for (unsigned int j = 0; j < sz2; j++) {
                tmp(i, j) = scale1 * (*data1)(i, j);
            }
        }

        unsigned int bottom = sz1;
        sz1 = data2->size1();
        sz2 = data2->size2();

        for (unsigned int i = 0; i < sz1; i++) {
            for (unsigned int j = 0; j < sz2; j++) {
                tmp(i + bottom, j) = scale2 * (*data2)(i, j);
            }
        }

        *datar = tmp;

        joined.SetScale(1.0);
        joined.SetStart(s1.GetStart());
        joined.SetSampling(s1.GetSampling());

        if (s1.GetStart() != s2.GetStart()) {
            LogWarning("Views with different starting times: %g %g (forced to %g)",
                    s1.GetStart(),
                    s2.GetStart(),
                    s1.GetStart());
        }


        if (s1.GetSampling() != s2.GetSampling()) {
            LogWarning("Views with different sampling times: %g %g (forced to %g)",
                    s1.GetSampling(),
                    s2.GetSampling(),
                    s1.GetSampling());
        }
    }

    void ViewUtil::Append(SeqViewDouble& s1, SeqViewDouble& s2) {
        Dmatrix* data1 = s1.GetData();
        Dmatrix* data2 = s2.GetData();

        double scale1 = s1.GetScale();
        double scale2 = s2.GetScale();


        if (data1->size2() != data2->size2()) {
            LogSevere("Views of different length");
            throw std::runtime_error("ViewUtil::Append");
        }

        data1->resize(data1->size1() + data2->size1(), data1->size2(), true);


        unsigned int bottom = data1->size1();
        unsigned int sz1 = data2->size1();
        unsigned int sz2 = data2->size2();

        double ratio = scale2 / scale1;

        for (unsigned int i = 0; i < sz1; i++) {
            for (unsigned int j = 0; j < sz2; j++) {
                (*data1)(i + bottom, j) = ratio * (*data2)(i, j);
            }
        }

        if (s1.GetStart() != s2.GetStart()) {
            LogWarning("Views with different starting times: %g %g (forced to %g)",
                    s1.GetStart(),
                    s2.GetStart(),
                    s1.GetStart());
        }


        if (s1.GetSampling() != s2.GetSampling()) {
            LogWarning("Views with different sampling times: %g %g (forced to %g)",
                    s1.GetSampling(),
                    s2.GetSampling(),
                    s1.GetSampling());
        }


    }

    void ViewUtil::LeftShift(SeqViewDouble& seq, SeqViewDouble& ins) {
        Dmatrix* data1 = seq.GetData();
        Dmatrix* data2 = ins.GetData();
        double scale1 = seq.GetScale();
        double scale2 = ins.GetScale();

        if (data1->size1() != data2->size1()) {
            LogSevere("Views with different channels");
            throw std::runtime_error("ViewUtil::LeftShift - Views with different channels");
        }

        unsigned int channels = data1->size1();
        unsigned int sz = data1->size2();
        unsigned int ins_sz = data2->size2();

        if (sz >= ins_sz) {
            for (unsigned int i = 0; i < channels; i++) {
                for (unsigned int j = 0; j < sz - ins_sz; j++) {
                    (*data1)(i, j) = scale1 * (*data1)(i, j + ins_sz);
                }
                for (unsigned int j = sz - ins_sz; j < sz; j++) {
                    (*data1)(i, j) = scale2 * (*data2)(i, j - sz + ins_sz);
                }
            }
            seq.SetStart(seq.GetStart() + ins_sz * seq.GetSampling());
            seq.SetScale(1.0);
        } else {
            for (unsigned int i = 0; i < channels; i++) {
                for (unsigned int j = 0; j < sz; j++) {
                    (*data1)(i, j) = scale2 * (*data2)(i, j + ins_sz - sz);
                }
            }
            seq.SetStart(seq.GetStart() + sz * seq.GetSampling());
            seq.SetScale(1.0);
        }
    }

    void ViewUtil::PadLeft(SeqViewDouble& src, SeqViewDouble& dst, unsigned int size, double value) {
        Dmatrix* datas = src.GetData();
        Dmatrix* datad = dst.GetData();

        if ((datas->size1() != datad->size1()) || (datas->size2() + size != datad->size2())) {
            LogWarning("PadLeft: resizing output view");
            datad->resize(datas->size1(), datas->size2() + size);
        }

        double v = value / src.GetScale();


        for (unsigned int c = 0; c < datas->size1(); c++) {

            for (unsigned int i = 0; i < datas->size2(); i++) {
                (*datad)(c, i) = (*datas)(c, i);
            }
            for (unsigned int i = datas->size2(); i < datas->size2() + size; i++) {
                (*datad)(c, i) = v;
            }
        }

        dst.SetScale(src.GetScale());
        dst.SetStart(src.GetStart());
        dst.SetSampling(src.GetSampling());

    }

    void ViewUtil::PadRight(SeqViewDouble& src, SeqViewDouble& dst, unsigned int size, double value) {

        Dmatrix* datas = src.GetData();
        Dmatrix* datad = dst.GetData();

        if ((datas->size1() != datad->size1()) || (datas->size2() + size != datad->size2())) {
            LogWarning("PadRight: resizing output view");
            datad->resize(datas->size1(), datas->size2() + size);
        }

        double v = value / src.GetScale();


        for (unsigned int c = 0; c < datas->size1(); c++) {

            for (unsigned int i = 0; i < size; i++) {
                (*datad)(c, i) = v;
            }
            for (unsigned int i = size; i < datas->size2() + size; i++) {
                (*datad)(c, i) = (*datas)(c, i - size);
            }
        }

        dst.SetScale(src.GetScale());
        dst.SetStart(src.GetStart());
        dst.SetSampling(src.GetSampling());

    }

    double ViewUtil::Dot(SeqViewDouble& s1, unsigned int ch1, SeqViewDouble& s2, unsigned int ch2) {
        Dmatrix* data1 = s1.GetData();
        Dmatrix* data2 = s2.GetData();

        if ((data1->size1() <= ch1) || (data2->size1() <= ch2) || (data1->size2() != data2->size2())) {
            LogSevere("Dot: wrong parameters");
            throw std::runtime_error("Dot: wrong parameters");
        }
        double scale1 = s1.GetScale();
        double scale2 = s2.GetScale();

        double dot = 0.0;
        unsigned int sz = data1->size2();
        for (unsigned int i = 0; i < sz; i++) {

            dot += (*data1)(ch1, i)*(*data2)(ch2, i);

        }

        return scale1 * scale2*dot;

    }

    void ViewUtil::SumChannels(SeqViewDouble& s1, SeqViewDouble& sum) {
        Dmatrix* src = s1.GetData();
        Dmatrix* dst = sum.GetData();

        if ((src->size2() != dst->size2()) || (dst->size1() != 1)) {
            LogWarning("SumChannels: resizing output view");
            dst->resize(1, src->size2());
        }

        unsigned int sz1 = src->size1();
        unsigned int sz2 = src->size2();

        for (unsigned int i = 0; i < sz2; i++) {
            (*dst)(0, i) = (*src)(0, i);
            for (unsigned int j = 1; j < sz1; j++) {
                (*dst)(0, i) += (*src)(j, i);
            }
        }
        sum.SetScale(s1.GetScale());
        sum.SetStart(s1.GetStart());
        sum.SetSampling(s1.GetSampling());
    }

    void ViewUtil::SumChannels(SeqViewDouble& s1, SeqViewDouble& sum, double wfirst, double wothers) {
        Dmatrix* src = s1.GetData();
        Dmatrix* dst = sum.GetData();

        if ((src->size2() != dst->size2()) || (dst->size1() != 1)) {
            LogWarning("SumChannels: resizing output view");
            dst->resize(1, src->size2());
        }

        unsigned int sz1 = src->size1();
        unsigned int sz2 = src->size2();

        for (unsigned int i = 0; i < sz2; i++) {
            (*dst)(0, i) = wfirst * (*src)(0, i);
            for (unsigned int j = 1; j < sz1; j++) {
                (*dst)(0, i) += wothers * (*src)(j, i);
            }
        }
        sum.SetScale(s1.GetScale());
        sum.SetStart(s1.GetStart());
        sum.SetSampling(s1.GetSampling());
    }

    bool ViewUtil::PeekRange(SeqViewDouble& src, SeqViewDouble& dst, double tstart, double tend) {
        Dmatrix* dsrc = src.GetData();
        Dmatrix* ddst = dst.GetData();
        double t1 = src.GetStart();
        double t2 = src.GetEnd();

        if (tstart > tend) {
            LogSevere("ViewUtil::PeekRange - tsart>tend");
            throw std::runtime_error("ViewUtil::PeekRange - tsart>tend");
        }

        bool ans = true;

        if (tstart < t1) {
            tstart = t1;
            ans = false;
        }

        if (tend > t2) {
            tend = t2;
            ans = false;
        }

        unsigned int ch = src.GetChannels();
        unsigned int i1 = src.GetIndex(t1);
        unsigned int i2 = src.GetIndex(t2);

        ddst->resize(dsrc->size1(), i2 - i1 + 1);

        double scale = dst.GetScale();

        for (unsigned int c = 0; c < ch; c++) {
            for (unsigned int i = i1; i <= i2; i++) {

                (*ddst)(c, i - i1) = scale * (*dsrc)(c, i);

            }
        }

        dst.SetScale(1.0);
        dst.SetStart(t1);
        dst.SetSampling(src.GetSampling());

        return ans;
    }

    void ViewUtil::Fill(SeqViewDouble& ts, double value) {
        Dmatrix* data = ts.GetData();
        unsigned int s1 = data->size1();
        unsigned int s2 = data->size2();

        for (unsigned int i = 0; i < s1; i++) {
            for (unsigned int j = 0; j < s2; j++) {
                (*data)(i, j) = value;
            }
        }
        ts.SetScale(1.0);
    }

    void ViewUtil::FillSeq(SeqViewDouble& ts, unsigned int i, unsigned int j, double value) {
        Dmatrix* data = ts.GetData();
        unsigned int s1 = data->size1();
        unsigned int s2 = data->size2();


        (*data)(i, j) = value;

        ts.SetScale(1.0);
    }

    void ViewUtil::Apply(double (*func)(double), SeqViewDouble& ts) {
        Dmatrix* data = ts.GetData();
        unsigned int s1 = data->size1();
        unsigned int s2 = data->size2();

        for (unsigned int i = 0; i < s1; i++) {
            for (unsigned int j = 0; j < s2; j++) {
                (*data)(i, j) = func((*data)(i, j));
            }
        }
    }

    void ViewUtil::Apply(double (*func)(double), SeqViewDouble& ts, SeqViewDouble& res) {
        Dmatrix* data = ts.GetData();
        Dmatrix* rs = res.GetData();
        unsigned int s1 = data->size1();
        unsigned int s2 = data->size2();
        rs->resize(s1, s2);
        res.SetStart(ts.GetStart());
        res.SetSampling(ts.GetSampling());
        res.SetScale(ts.GetScale());

        for (unsigned int i = 0; i < s1; i++) {
            for (unsigned int j = 0; j < s2; j++) {
                (*rs)(i, j) = func((*data)(i, j));
            }
        }
    }

    void ViewUtil::AffineTransformation(SeqViewDouble& ts, double a, double b, SeqViewDouble& res) {
        Dmatrix* data = ts.GetData();
        Dmatrix* rs = res.GetData();
        unsigned int s1 = data->size1();
        unsigned int s2 = data->size2();
        rs->resize(s1, s2);
        res.SetStart(ts.GetStart());
        res.SetSampling(ts.GetSampling());
        res.SetScale(ts.GetScale());

        for (unsigned int i = 0; i < s1; i++) {
            for (unsigned int j = 0; j < s2; j++) {
                (*rs)(i, j) = a * (*data)(i, j) + b;
            }
        }
    }

    void ViewUtil::BinOp(std::complex<double> (*func)(std::complex<double>, std::complex<double>), SeqViewComplex& ts1, SeqViewComplex& ts2, SeqViewComplex& res) {
        Cmatrix* data1 = ts1.GetData();
        Cmatrix* data2 = ts2.GetData();
        Cmatrix* rs = res.GetData();
        unsigned int s1 = data1->size1();
        unsigned int s2 = data2->size2();
        if ((data2->size1() != s1) || (data2->size2() != s2)) {
            LogSevere("Wrong size for input views");
            throw std::runtime_error("Util::BinOp");
        }
        rs->resize(s1, s2);
        res.SetStart(ts1.GetStart());
        res.SetSampling(ts1.GetSampling());
        res.SetScale(ts1.GetScale());

        for (unsigned int i = 0; i < s1; i++) {
            for (unsigned int j = 0; j < s2; j++) {
                (*rs)(i, j) = func((*data1)(i, j), (*data2)(i, j));
            }
        }
    }

    void ViewUtil::BinOp(double (*func)(double, double), SeqViewDouble& ts1, SeqViewDouble& ts2, SeqViewDouble& res) {
        Dmatrix* data1 = ts1.GetData();
        Dmatrix* data2 = ts2.GetData();
        Dmatrix* rs = res.GetData();
        unsigned int s1 = data1->size1();
        unsigned int s2 = data2->size2();
        if ((data2->size1() != s1) || (data2->size2() != s2)) {
            LogSevere("Wrong size for input views");
            throw std::runtime_error("Util::BinOp");
        }
        rs->resize(s1, s2);
        res.SetStart(ts1.GetStart());
        res.SetSampling(ts1.GetSampling());
        res.SetScale(ts1.GetScale());

        for (unsigned int i = 0; i < s1; i++) {
            for (unsigned int j = 0; j < s2; j++) {
                (*rs)(i, j) = func((*data1)(i, j), (*data2)(i, j));
            }
        }
    }

    void ViewUtil::Apply(std::complex<double> (*func)(std::complex<double>), SeqViewComplex& fs) {
        Cmatrix* data = fs.GetData();
        unsigned int s1 = data->size1();
        unsigned int s2 = data->size2();

        for (unsigned int i = 0; i < s1; i++) {
            for (unsigned int j = 0; j < s2; j++) {
                (*data)(i, j) = func((*data)(i, j));
            }
        }
    }

    void ViewUtil::ComplexToPolar(SeqViewComplex& ts1, SeqViewDouble& ts2) {
        Cmatrix* dataIn = ts1.GetData();
        unsigned int s1In = dataIn->size1();
        unsigned int s2In = dataIn->size2();

        Dmatrix* dataOut = ts2.GetData();
        unsigned int s1Out = dataOut->size1();
        unsigned int s2Out = dataOut->size2();

        if ((2 * s1In != s1Out) || (s2In != s2Out)) {
            LogWarning("Util::Complex : Resizing output view");
            dataOut->resize(2 * s1In, s2In);
        }

        for (unsigned int i = 0; i < s1In; i++) {
            for (unsigned int j = 0; j < s2In; j++) {
                (*dataOut)(i * 2, j) = abs((*dataIn)(i, j));
                (*dataOut)(i * 2 + 1, j) = arg((*dataIn)(i, j));
            }
        }
        ts2.SetScale(ts1.GetScale());
        ts2.SetStart(ts1.GetStart());
        ts2.SetSampling(ts1.GetSampling());

    }

    void ViewUtil::Apply(std::complex<double> (*func)(std::complex<double>), SeqViewComplex& fs, SeqViewComplex& res) {
        Cmatrix* data = fs.GetData();
        Cmatrix* rs = res.GetData();
        unsigned int s1 = data->size1();
        unsigned int s2 = data->size2();
        rs->resize(s1, s2);
        res.SetStart(fs.GetStart());
        res.SetSampling(fs.GetSampling());
        res.SetScale(fs.GetScale());

        for (unsigned int i = 0; i < s1; i++) {
            for (unsigned int j = 0; j < s2; j++) {
                (*rs)(i, j) = abs((*data)(i, j));
            }
        }
    }

    void ViewUtil::Sum(SeqViewDouble& res, double scale, SeqViewDouble& ts) {
        Dmatrix* data = ts.GetData();
        Dmatrix* rs = res.GetData();
        unsigned int s1 = data->size1();
        unsigned int s2 = data->size2();
        rs->resize(s1, s2);
        res.SetStart(ts.GetStart());
        res.SetSampling(ts.GetSampling());
        res.SetScale(ts.GetScale());

        for (unsigned int i = 0; i < s1; i++) {
            for (unsigned int j = 0; j < s2; j++) {
                (*rs)(i, j) = (*rs)(i, j) + scale * (*data)(i, j);
            }
        }
    }

    void ViewUtil::Sum(SeqViewComplex& res, double scale, SeqViewComplex& ts) {
        Cmatrix* data = ts.GetData();
        Cmatrix* rs = res.GetData();
        unsigned int s1 = data->size1();
        unsigned int s2 = data->size2();
        rs->resize(s1, s2);
        res.SetStart(ts.GetStart());
        res.SetSampling(ts.GetSampling());
        res.SetScale(ts.GetScale());

        for (unsigned int i = 0; i < s1; i++) {
            for (unsigned int j = 0; j < s2; j++) {
                (*rs)(i, j) = (*rs)(i, j) + scale * (*data)(i, j);
            }
        }
    }

    void ViewUtil::Inverse(SeqViewDouble& ts1, SeqViewDouble& res) {
        Dmatrix* data1 = ts1.GetData();
        Dmatrix* rs = res.GetData();
        unsigned int s1 = data1->size1();
        unsigned int s2 = data1->size2();

        rs->resize(s1, s2);
        res.SetStart(ts1.GetStart());
        res.SetSampling(ts1.GetSampling());
        res.SetScale(ts1.GetScale());


        for (unsigned int i = 0; i < s1; i++) {
            for (unsigned int j = 0; j < s2; j++) {
                (*rs)(i, j) = 1.0 / (*data1)(i, j);
            }
        }
        res.SetScale(ts1.GetScale());
        res.SetStart(ts1.GetStart());
        res.SetSampling(ts1.GetSampling());
    }

    void ViewUtil::Ratio(SeqViewDouble& ts1, SeqViewDouble& ts2, SeqViewDouble& res) {
        Dmatrix* data1 = ts1.GetData();
        Dmatrix* data2 = ts2.GetData();
        Dmatrix* rs = res.GetData();
        unsigned int s1 = data1->size1();

        if ((data2->size1() != s1)) {
            LogSevere("Wrong size for input views");
            throw std::runtime_error("Util::BinOp");
        }

        unsigned int s2 = (data1->size2() > data2->size2()) ? data2->size2() : data1->size2();

        rs->resize(s1, s2);
        res.SetStart(ts1.GetStart());
        res.SetSampling(ts1.GetSampling());
        res.SetScale(ts1.GetScale());


        for (unsigned int i = 0; i < s1; i++) {
            for (unsigned int j = 0; j < s2; j++) {
                (*rs)(i, j) = (*data1)(i, j) / (*data2)(i, j);
            }
        }

        res.SetScale(ts1.GetScale() / ts2.GetScale());
        res.SetStart(ts1.GetStart());
        res.SetSampling(ts1.GetSampling());

    }

    void ViewUtil::Ratio(SeqViewComplex& ts1, SeqViewComplex& ts2, SeqViewComplex& res) {
        Cmatrix* data1 = ts1.GetData();
        Cmatrix* data2 = ts2.GetData();
        Cmatrix* rs = res.GetData();
        unsigned int s1 = data1->size1();

        if ((data2->size1() != s1)) {
            LogSevere("Wrong size for input views");
            throw std::runtime_error("Util::BinOp");
        }

        unsigned int s2 = (data1->size2() > data2->size2()) ? data2->size2() : data1->size2();

        rs->resize(s1, s2);
        res.SetStart(ts1.GetStart());
        res.SetSampling(ts1.GetSampling());
        res.SetScale(ts1.GetScale());


        for (unsigned int i = 0; i < s1; i++) {
            for (unsigned int j = 0; j < s2; j++) {
                (*rs)(i, j) = (*data1)(i, j) / (*data2)(i, j);
            }
        }

        res.SetScale(ts1.GetScale() / ts2.GetScale());
        res.SetStart(ts1.GetStart());
        res.SetSampling(ts1.GetSampling());

    }

    void ViewUtil::Norm(SeqViewComplex& ts1, SeqViewDouble& res) {

        Cmatrix* data1 = ts1.GetData();
        Dmatrix* rs = res.GetData();
        unsigned int s1 = data1->size1();
        unsigned int s2 = data1->size2();

        rs->resize(s1, s2);
        res.SetStart(ts1.GetStart());
        res.SetSampling(ts1.GetSampling());
        res.SetScale(ts1.GetScale());


        for (unsigned int i = 0; i < s1; i++) {
            for (unsigned int j = 0; j < s2; j++) {
                (*rs)(i, j) = norm((*data1)(i, j));
            }
        }

        res.SetScale(ts1.GetScale());
        res.SetStart(ts1.GetStart());
        res.SetSampling(ts1.GetSampling());


    }

    void ViewUtil::Abs(SeqViewComplex& ts1, SeqViewDouble& res) {

        Cmatrix* data1 = ts1.GetData();
        Dmatrix* rs = res.GetData();
        unsigned int s1 = data1->size1();
        unsigned int s2 = data1->size2();

        rs->resize(s1, s2);
        res.SetStart(ts1.GetStart());
        res.SetSampling(ts1.GetSampling());
        res.SetScale(ts1.GetScale());


        for (unsigned int i = 0; i < s1; i++) {
            for (unsigned int j = 0; j < s2; j++) {
                (*rs)(i, j) = abs((*data1)(i, j));
            }
        }

        res.SetScale(ts1.GetScale());
        res.SetStart(ts1.GetStart());
        res.SetSampling(ts1.GetSampling());


    }

    void ViewUtil::Abs2(SeqViewComplex& ts1, SeqViewDouble& res) {

        Cmatrix* data1 = ts1.GetData();
        Dmatrix* rs = res.GetData();
        unsigned int s1 = data1->size1();
        unsigned int s2 = data1->size2();

        rs->resize(s1, s2);
        res.SetStart(ts1.GetStart());
        res.SetSampling(ts1.GetSampling());
        res.SetScale(ts1.GetScale());


        for (unsigned int i = 0; i < s1; i++) {
            for (unsigned int j = 0; j < s2; j++) {
                (*rs)(i, j) = (*data1)(i, j).real()*(*data1)(i, j).real()+(*data1)(i, j).imag()*(*data1)(i, j).imag();
            }
        }

        res.SetScale(ts1.GetScale());
        res.SetStart(ts1.GetStart());
        res.SetSampling(ts1.GetSampling());


    }

    void ViewUtil::Prod(SeqViewDouble& ts1, SeqViewDouble& ts2, SeqViewDouble& res) {

        Dmatrix* data1 = ts1.GetData();
        Dmatrix* data2 = ts2.GetData();
        Dmatrix* rs = res.GetData();
        unsigned int s1 = data1->size1();

        if ((data2->size1() != s1)) {
            LogSevere("Wrong size for input views");
            throw std::runtime_error("Util::BinOp");
        }

        unsigned int s2 = (data1->size2() > data2->size2()) ? data2->size2() : data1->size2();

        rs->resize(s1, s2);
        res.SetStart(ts1.GetStart());
        res.SetSampling(ts1.GetSampling());
        res.SetScale(ts1.GetScale());


        for (unsigned int i = 0; i < s1; i++) {
            for (unsigned int j = 0; j < s2; j++) {
                (*rs)(i, j) = (*data1)(i, j)*(*data2)(i, j);
            }
        }

        res.SetScale(ts1.GetScale() * ts2.GetScale());
        res.SetStart(ts1.GetStart());
        res.SetSampling(ts1.GetSampling());


    }

    void ViewUtil::Prod(SeqViewDouble& ts1, SeqViewComplex& ts2, SeqViewComplex& res) {

        Dmatrix* data1 = ts1.GetData();
        Cmatrix* data2 = ts2.GetData();
        Cmatrix* rs = res.GetData();
        unsigned int s1 = data1->size1();

        if ((data2->size1() != s1)) {
            LogSevere("Wrong size for input views");
            throw std::runtime_error("Util::Prod");
        }

        unsigned int s2 = (data1->size2() > data2->size2()) ? data2->size2() : data1->size2();

        rs->resize(s1, s2);
        res.SetStart(ts1.GetStart());
        res.SetSampling(ts1.GetSampling());
        res.SetScale(ts1.GetScale());


        for (unsigned int i = 0; i < s1; i++) {
            for (unsigned int j = 0; j < s2; j++) {
                (*rs)(i, j) = (*data1)(i, j)*(*data2)(i, j);
            }
        }

        res.SetScale(ts1.GetScale() * ts2.GetScale());
        res.SetStart(ts1.GetStart());
        res.SetSampling(ts1.GetSampling());

    }

    void ViewUtil::Phase(SeqViewComplex& ts1, SeqViewComplex& ts2, SeqViewComplex& res) {

        Cmatrix* data1 = ts1.GetData();
        Cmatrix* data2 = ts2.GetData();
        Cmatrix* rs = res.GetData();

        unsigned int sa = data1->size1();
        unsigned int sb = data2->size1();
        unsigned int s1res = sa*sb;
        unsigned int s2res = (data1->size2() < data2->size2()) ? data1->size2() : data2->size2();

        if ((rs->size1() != s1res) || (rs->size2() != s2res)) {
            LogWarning("Resizing output view");
            rs->resize(s1res, s2res);
        }

        res.SetStart(ts1.GetStart());
        res.SetSampling(ts1.GetSampling());
        res.SetScale(1.0);


        for (unsigned int i = 0; i < sa; i++) {
            for (unsigned int j = 0; j < sb; j++) {
                for (unsigned k = 0; k < s2res; k++) {
                    tsa::Cdouble a = (*data1)(i, k);
                    tsa::Cdouble b = (*data2)(j, k);
                    (*rs)(i * sb + j, k) = conj(a) * b / sqrt((a.real() * a.real() + a.imag() * a.imag())*(b.real() * b.real() + b.imag() * b.imag()));
                }
            }
        }
    }

    void ViewUtil::ProdConj(SeqViewComplex& ts1, SeqViewComplex& ts2, SeqViewComplex& res) {

        Cmatrix* data1 = ts1.GetData();
        Cmatrix* data2 = ts2.GetData();
        Cmatrix* rs = res.GetData();
        unsigned int s1 = data1->size1();

        if (((unsigned int) data2->size1() != s1)) {
            fprintf(stderr, "%d %d\n", data1->size1(), data2->size1());
            LogSevere("Wrong size for input views");
            throw std::runtime_error("Util::ProdConj");
        }

        unsigned int s2 = (data1->size2() > data2->size2()) ? data2->size2() : data1->size2();

        rs->resize(s1, s2);
        res.SetStart(ts1.GetStart());
        res.SetSampling(ts1.GetSampling());
        res.SetScale(ts1.GetScale());


        for (unsigned int i = 0; i < s1; i++) {
            for (unsigned int j = 0; j < s2; j++) {
                (*rs)(i, j) = (*data1)(i, j) * conj((*data2)(i, j));
            }
        }

        res.SetScale(ts1.GetScale() * ts2.GetScale());
        res.SetStart(ts1.GetStart());
        res.SetSampling(ts1.GetSampling());


    }

    void ViewUtil::Ratio(SeqViewDouble& ts1, SeqViewComplex& ts2, SeqViewComplex& res) {
        Dmatrix* data1 = ts1.GetData();
        Cmatrix* data2 = ts2.GetData();
        Cmatrix* rs = res.GetData();
        unsigned int s1 = data1->size1();

        if ((data2->size1() != s1)) {
            LogSevere("Wrong size for input views");
            throw std::runtime_error("Util::BinOp");
        }

        unsigned int s2 = (data1->size2() > data2->size2()) ? data2->size2() : data1->size2();

        rs->resize(s1, s2);
        res.SetStart(ts1.GetStart());
        res.SetSampling(ts1.GetSampling());
        res.SetScale(ts1.GetScale());


        for (unsigned int i = 0; i < s1; i++) {
            for (unsigned int j = 0; j < s2; j++) {
                (*rs)(i, j) = (*data1)(i, j) / (*data2)(i, j);
            }
        }

        res.SetScale(ts1.GetScale() / ts2.GetScale());
        res.SetStart(ts1.GetStart());
        res.SetSampling(ts1.GetSampling());

    }

    void ViewUtil::BlockSum(SeqViewComplex& in, SeqViewComplex& out, int bsize) {
        Cmatrix* data1 = in.GetData();
        Cmatrix* data2 = out.GetData();
        unsigned int s1 = data1->size1();
        unsigned int s2 = data1->size2();

        s2 = s2 / bsize;

        if ((data2->size1() != s1) || (data2->size2() != s2)) {
            data2->resize(s1, s2);
        }
        out.SetStart(in.GetStart());
        out.SetSampling(in.GetSampling() * bsize);
        out.SetScale(in.GetScale());

        for (unsigned int i = 0; i < s1; i++) {
            for (unsigned int j = 0; j < s2; j++) {
                (*data2)(i, j) = (*data1)(i, bsize * j);
                for (unsigned int k = 1; k < bsize; k++) {
                    (*data2)(i, j) += (*data1)(i, bsize * j + k);
                }
            }
        }
    }

    void ViewUtil::Ratio(SeqViewComplex& ts1, SeqViewDouble& ts2, SeqViewComplex& res) {
        Cmatrix* data1 = ts1.GetData();
        Dmatrix* data2 = ts2.GetData();
        Cmatrix* rs = res.GetData();
        unsigned int s1 = data1->size1();

        if ((data2->size1() != s1)) {
            LogSevere("Wrong size for input views");
            throw std::runtime_error("Util::BinOp");
        }

        unsigned int s2 = (data1->size2() > data2->size2()) ? data2->size2() : data1->size2();

        rs->resize(s1, s2);
        res.SetStart(ts1.GetStart());
        res.SetSampling(ts1.GetSampling());
        res.SetScale(ts1.GetScale());


        for (unsigned int i = 0; i < s1; i++) {
            for (unsigned int j = 0; j < s2; j++) {
                (*rs)(i, j) = (*data1)(i, j) / (*data2)(i, j);
            }
        }

        res.SetScale(ts1.GetScale() / ts2.GetScale());
        res.SetStart(ts1.GetStart());
        res.SetSampling(ts1.GetSampling());

    }

    void ViewUtil::Multiply(SeqViewDouble& ts1, SeqViewDouble& ts2, SeqViewDouble& res) {
        Dmatrix* data1 = ts1.GetData();
        Dmatrix* data2 = ts2.GetData();
        Dmatrix* rs = res.GetData();
        unsigned int s1 = data1->size1();
        unsigned int s2 = data1->size2();

        if ((data2->size1() != s1) || (data2->size2() != s2)) {
            LogSevere("Wrong size for input views");
            throw std::runtime_error("Util::Multiply");
        }

        rs->resize(s1, s2);
        res.SetStart(ts1.GetStart());
        res.SetSampling(ts1.GetSampling());
        res.SetScale(ts1.GetScale() * ts2.GetScale());

        for (unsigned int i = 0; i < s1; i++) {
            for (unsigned int j = 0; j < s2; j++) {
                (*rs)(i, j) = (*data1)(i, j)*(*data2)(i, j);
            }
        }



    }

    void ViewUtil::Multiply(SeqViewDouble& ts1, SeqViewComplex& ts2, SeqViewComplex& res) {
        Dmatrix* data1 = ts1.GetData();
        Cmatrix* data2 = ts2.GetData();
        Cmatrix* rs = res.GetData();
        unsigned int s1 = data1->size1();
        unsigned int s2 = data1->size2();

        if ((data2->size1() != s1) || (data2->size2() != s2)) {
            LogSevere("Wrong size for input views");
            throw std::runtime_error("Util::Multiply");
        }

        rs->resize(s1, s2);
        res.SetStart(ts1.GetStart());
        res.SetSampling(ts1.GetSampling());
        res.SetScale(ts1.GetScale() * ts2.GetScale());

        for (unsigned int i = 0; i < s1; i++) {
            for (unsigned int j = 0; j < s2; j++) {
                (*rs)(i, j) = (*data1)(i, j)*(*data2)(i, j);
            }
        }
    }

    void ViewUtil::Multiply(SeqViewComplex& ts1, SeqViewComplex& ts2, SeqViewComplex& res) {
        Cmatrix* data1 = ts1.GetData();
        Cmatrix* data2 = ts2.GetData();
        Cmatrix* rs = res.GetData();
        unsigned int s1 = data1->size1();
        unsigned int s2 = data1->size2();

        if ((data2->size1() != s1) || (data2->size2() != s2)) {
            LogSevere("Wrong size for input views");
            throw std::runtime_error("Util::Multiply");
        }

        rs->resize(s1, s2);
        res.SetStart(ts1.GetStart());
        res.SetSampling(ts1.GetSampling());
        res.SetScale(ts1.GetScale() * ts2.GetScale());

        for (unsigned int i = 0; i < s1; i++) {
            for (unsigned int j = 0; j < s2; j++) {
                (*rs)(i, j) = (*data1)(i, j)*(*data2)(i, j);
            }
        }
    }


}
