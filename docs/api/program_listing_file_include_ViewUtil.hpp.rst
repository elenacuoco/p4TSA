
.. _program_listing_file_include_ViewUtil.hpp:

Program Listing for File ViewUtil.hpp
=====================================

|exhale_lsh| :ref:`Return to documentation for file <file_include_ViewUtil.hpp>` (``include/ViewUtil.hpp``)

.. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS

.. code-block:: none

   
   #ifndef __VIEWUTIL_HPP
   #define __VIEWUTIL_HPP
   
   
   
   
   #include <AlgoBase.hpp>
   
   
   
   
   
   
   
   
   namespace tsa {
   
       class ViewUtil : public AlgoBase {
       public:
   
           ViewUtil() {
           };
   
           ~ViewUtil() {
           };
   
   
   
           static void Join(std::vector<SeqViewComplex>& sl, SeqViewComplex& joined, double start, double sampling, unsigned int length);
   
           static void Join(std::vector<SeqViewDouble>& sl, SeqViewDouble& joined, double start, double sampling, unsigned int length);
   
           static void Join(SeqViewDouble& s1, SeqViewDouble& s2, SeqViewDouble& joined);
   
           static void Append(SeqViewDouble& s1, SeqViewDouble& s2);
   
           static void Print(SeqViewDouble& s1, char *filename);
   
           static void Print(SeqViewComplex& s1, char *filename);
   
           static void Print(SeqViewDouble& s1);
   
           static void Range(SeqViewDouble& s1, int l, int m);
   
           static void Range(SeqViewComplex& s1, int l, int m);
   
           static void Range(SeqViewDouble& s1, SeqViewDouble& s2, int l, int m);
   
           static void LeftShift(SeqViewDouble& seq, SeqViewDouble& ins);
   
           static void PadLeft(SeqViewDouble& src, SeqViewDouble& dst, unsigned int size, double value = 0.0);
   
           static void PadRight(SeqViewDouble& src, SeqViewDouble& dst, unsigned int size, double value = 0.0);
   
           static double Dot(SeqViewDouble& s1, unsigned int ch1, SeqViewDouble& s2, unsigned int ch2);
   
           static void SumChannels(SeqViewDouble& s1, SeqViewDouble& sum);
   
           static void SumChannels(SeqViewDouble& s1, SeqViewDouble& sum, double wfirst, double wothers);
   
           static void Fill(SeqViewDouble& ts, double value);
           static void FillSeq(SeqViewDouble& ts, unsigned int i, unsigned int j, double value);
   
           static bool PeekRange(SeqViewDouble& src, SeqViewDouble& dst, double tstart, double tend);
   
           static void Apply(double (*func)(double), SeqViewDouble& ts);
   
           static void Apply(double (*func)(double), SeqViewDouble& ts, SeqViewDouble& res);
   
           static void BinOp(std::complex<double> (*func)(std::complex<double>, std::complex<double>), SeqViewComplex& ts1, SeqViewComplex& ts2, SeqViewComplex& res);
   
           static void BinOp(double (*func)(double, double), SeqViewDouble& ts1, SeqViewDouble& ts2, SeqViewDouble& res);
   
   
   
           static void Apply(std::complex<double> (*func)(std::complex<double>), SeqViewComplex& fs);
   
           static void Apply(std::complex<double> (*func)(std::complex<double>), SeqViewComplex& fs, SeqViewComplex& res);
   
           static void Sum(SeqViewDouble& res, double scale, SeqViewDouble& ts);
   
           static void Sum(SeqViewComplex& res, double scale, SeqViewComplex& ts);
   
           static void Inverse(SeqViewDouble& ts1, SeqViewDouble& res);
   
           static void AffineTransformation(SeqViewDouble& ts1, double a, double b, SeqViewDouble& res);
   
           static void Ratio(SeqViewDouble& ts1, SeqViewDouble& ts2, SeqViewDouble& res);
           static void Ratio(SeqViewComplex& ts1, SeqViewComplex& ts2, SeqViewComplex& res);
           static void Ratio(SeqViewDouble& ts1, SeqViewComplex& ts2, SeqViewComplex& res);
           static void Ratio(SeqViewComplex& ts1, SeqViewDouble& ts2, SeqViewComplex& res);
   
           static void ComplexToPolar(SeqViewComplex& ts1, SeqViewDouble& ts2);
   
           static void Norm(SeqViewComplex& ts1, SeqViewDouble& res);
           static void Abs(SeqViewComplex& ts1, SeqViewDouble& res);
   
           static void Abs2(SeqViewComplex& ts1, SeqViewDouble& res);
   
           static void Prod(SeqViewDouble& ts1, SeqViewDouble& ts2, SeqViewDouble& res);
   
           static void Prod(SeqViewDouble& ts1, SeqViewComplex& ts2, SeqViewComplex& res);
   
           static void ProdConj(SeqViewComplex& ts1, SeqViewComplex& ts2, SeqViewComplex& res);
   
           static void Phase(SeqViewComplex& ts1, SeqViewComplex& ts2, SeqViewComplex& res);
   
           static void BlockSum(SeqViewComplex& in, SeqViewComplex& out, int bsize);
   
           static std::complex<double> Integrate(SeqViewComplex& data, double f1, double f2);
   
           static double Integrate(SeqViewDouble& data, double f1, double f2);
   
           static std::complex<double> DelayIntegrate(SeqViewComplex& data, double tau, double f1, double f2);
   
           static std::complex<double> DelayIntegrate(SeqViewDouble& data, double tau, double f1, double f2);
   
           static void Multiply(SeqViewDouble& in1, SeqViewDouble& in2, SeqViewDouble& res);
           static void Multiply(SeqViewDouble& in1, SeqViewComplex& in2, SeqViewComplex& res);
           static void Multiply(SeqViewComplex& in1, SeqViewComplex& in2, SeqViewComplex& res);
   
   
   
   
   
   
   
   
   
   
   
   
   
       protected:
   
       private:
   
       };
   
   
   
   
   
   
   
   } // end namespace tsa
   
   #endif // __VIEWUTIL_HPP
