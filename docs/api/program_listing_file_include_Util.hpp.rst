
.. _program_listing_file_include_Util.hpp:

Program Listing for File Util.hpp
=================================

|exhale_lsh| :ref:`Return to documentation for file <file_include_Util.hpp>` (``include/Util.hpp``)

.. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS

.. code-block:: none

   #ifndef __UTIL_HPP
   #define __UTIL_HPP
   
   
   #include <complex>
   
   
   #include <AlgoBase.hpp>
   #include <SeqView.hpp>
   
   
   
   
   
   
   
   
   namespace tsa {
   
       class Util : public AlgoBase {
       public:
   
           static void Apply(double (*func)(double), SeqViewDouble& ts) {
               Dmatrix* data = ts.GetData();
               unsigned int s1 = data->size1();
               unsigned int s2 = data->size2();
   
               for (unsigned int i = 0; i < s1; i++) {
                   for (unsigned int j = 0; j < s2; j++) {
                       (*data)(i, j) = func((*data)(i, j));
                   }
               }
           };
   
           static void Apply(double (*func)(double), SeqViewDouble& ts, SeqViewDouble& res) {
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
           };
   
           static void BinOp(double (*func)(double, double), SeqViewDouble& ts1, SeqViewDouble& ts2, SeqViewDouble& res) {
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
           };
   
           static void Norm(double (*func)(double), SeqViewDouble& ts1, SeqViewDouble& res) {
               Dmatrix* data1 = ts1.GetData();
               Dmatrix* rs = res.GetData();
               unsigned int s1 = data1->size1();
               unsigned int s2 = data1->size2();
               if (rs->size1() != 1 || (rs->size2() != s2)) {
                   LogWarning("Util::Norm : Resizing output view");
                   rs->resize(1, s2);
               }
               res.SetStart(ts1.GetStart());
               res.SetSampling(ts1.GetSampling());
               res.SetScale(ts1.GetScale());
   
               for (unsigned int j = 0; j < s2; j++) {
                   (*rs)(0, j) = 0;
               }
   
               for (unsigned int j = 0; j < s2; j++) {
                   for (unsigned int i = 0; i < s1; i++) {
                       (*rs)(0, j) += func((*data1)(i, j));
                   }
                   (*rs)(0, j) = sqrt((*rs)(0, j));
               }
           };
   
           void Apply(std::complex<double> (*func)(std::complex<double>), SeqViewComplex& fs) {
               Cmatrix* data = fs.GetData();
               unsigned int s1 = data->size1();
               unsigned int s2 = data->size2();
   
               for (unsigned int i = 0; i < s1; i++) {
                   for (unsigned int j = 0; j < s2; j++) {
                       (*data)(i, j) = func((*data)(i, j));
                   }
               }
           };
   
           void Apply(std::complex<double> (*func)(std::complex<double>), SeqViewComplex& fs, SeqViewComplex& res) {
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
                       (*rs)(i, j) = func((*data)(i, j));
                   }
               }
           };
   
           static void Sum(SeqViewDouble& res, double scale, SeqViewDouble& ts) {
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
           };
   
       };
   
   } // end namespace tsa
   
   #endif // __UTIL_HPP
