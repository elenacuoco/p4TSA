
.. _program_listing_file_include_SeqView.hpp:

Program Listing for File SeqView.hpp
====================================

|exhale_lsh| :ref:`Return to documentation for file <file_include_SeqView.hpp>` (``include/SeqView.hpp``)

.. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS

.. code-block:: none

   #include <boost/numeric/ublas/matrix.hpp>
   #include <boost/numeric/ublas/matrix_proxy.hpp>
   #include <boost/numeric/ublas/io.hpp>
   
   #ifndef __SEQVIEW_HPP
   #define __SEQVIEW_HPP
   
   
   #include <BaseView.hpp>
   #include <FrameL.h> 
   
   namespace tsa {
   
   
       template<class T>
       class SeqView : public BaseView {
       public:
           typedef T numericType;
           typedef boost::numeric::ublas::matrix<T> matrixType;
   
   
           SeqView()
           :
           mData(1, 1024),
           mScale(1.0),
           mStart(0.0),
           mSampling(0.01) {
               Clear();
           };
   
   
   
   
           SeqView(
                   double aStart,
                   double aSampling,
                   unsigned int ChannelSize,
                   const std::string& aName = std::string(),
                   unsigned int ColumnDim = 1
                   )
           :
           BaseView(aName),
           mData(ColumnDim, ChannelSize),
           mScale(1.0),
           mStart(aStart),
           mSampling(aSampling) {
               Clear();
           };
   
           SeqView(const SeqView& from) {
               mScale = from.mScale;
               mData = from.mData;
               mStart = from.mStart;
               mSampling = from.mSampling;
           }
   
   
   
   
           ~SeqView() {
   
           };
   
   
   
   
           SeqView& operator=(const SeqView& from) {
               mScale = from.mScale;
               mData = from.mData;
               mStart = from.mStart;
               mSampling = from.mSampling;
   
               return *this;
           }
   
   
   
   
           void Clear() {
               mData.clear();
           };
   
           void MoveFrame(int n) {
               mStart += n * mSampling * mData.size2();
           }
   
           void Write(int fd) {
   
               // Write header
               unsigned int len = strlen(typeid (*this).name()) + 1;
               write(fd, &len, sizeof (unsigned int));
               write(fd, typeid (*this).name(), strlen(typeid (*this).name()) + 1);
   
               LogDebug(LOG_DEBUG_LEVEL_2, "Writing class %s header=%d", typeid (*this).name(), len);
   
   
               // Write data
               unsigned int d1, d2;
               d1 = mData.size1();
               d2 = mData.size2();
               write(fd, &d1, sizeof (unsigned int));
               write(fd, &d2, sizeof (unsigned int));
               write(fd, &mData(0, 0), d1 * d2 * sizeof (numericType));
               write(fd, &mScale, sizeof (double));
               write(fd, &mStart, sizeof (double));
               write(fd, &mSampling, sizeof (double));
           }
   
           void Read(int fd) {
               LogDebug(LOG_DEBUG_LEVEL_2, "Reading class %s", typeid (*this).name());
               // Get header
               unsigned int len;
               char name[256];
   
               read(fd, &len, sizeof (unsigned int));
               if (len > 256) {
                   LogSevere("Read: header too large: %d", len);
                   throw std::runtime_error("Read: header too large");
               }
               read(fd, name, len);
               if (strcmp(name, typeid (*this).name()) != 0) {
                   LogSevere("Read: expecting class %s, got class %s",
                           typeid (*this).name(),
                           name);
                   throw std::runtime_error("Read: got bad class");
               }
   
               // Get data
               unsigned int d1, d2;
               read(fd, &d1, sizeof (unsigned int));
               read(fd, &d2, sizeof (unsigned int));
               mData.resize(d1, d2);
               read(fd, &mData(0, 0), d1 * d2 * sizeof (numericType));
               read(fd, &mScale, sizeof (double));
               read(fd, &mStart, sizeof (double));
               read(fd, &mSampling, sizeof (double));
           }
   
   
   
   
   
   
   
   
   
           numericType& operator()(unsigned int f) {
               if (mScale != 1.0) Rescale();
               return mData(0, f);
           };
   
   
   
           numericType get(double x) {
               if (mScale != 1.0) Rescale();
               unsigned int i = (unsigned int) ((x - mStart) / mSampling);
               if (i >= mData.size2()) i = mData.size2() - 1;
               return mData(0, i);
           };
   
   
   
           numericType get(unsigned int c, double x) {
               if (mScale != 1.0) Rescale();
               unsigned int i = (unsigned int) ((x - mStart) / mSampling);
               if (i >= mData.size2()) i = mData.size2() - 1;
               return mData(c, i);
           };
   
   
   
   
           numericType& operator()(unsigned int channel, unsigned int f) {
               if (mScale != 1.0) Rescale();
               return mData(channel, f);
           };
   
   
           numericType& asVector(unsigned int channel, unsigned int f) {
               if (mScale != 1.0) Rescale();
               return mData(channel, f);
           };
   
   
   
           template<class MA>
           numericType& asMatrix(unsigned int i, unsigned int j, unsigned int f) {
               if (mScale != 1.0) Rescale();
               unsigned int lda = MA::Dimension(mData.size1());
               return mData(MA::Map(i, j, lda), f);
           };
   
   
   
   
   
   
           boost::numeric::ublas::matrix<numericType>* GetData() {
               return &mData;
           }
   
   
           double GetScale() {
               return mScale;
           }
   
   
           double GetStart() {
               return mStart;
           }
   
   
           double GetSampling() {
               return mSampling;
           }
   
   
   
           unsigned int GetSize() {
               return mData.size2();
           };
   
   
           unsigned int GetChannels() {
               return mData.size1();
           };
   
   
   
           double GetX(unsigned int k) {
               return mStart + mSampling*k;
           };
   
           double GetY(unsigned int channel, unsigned int f) {
   
               return mData(channel, f);
           };
   
   
           double GetEnd() {
               return mStart + mSampling * mData.size2();
           };
   
   
           double GetSlice() {
               return mSampling * mData.size2();
           };
   
   
           int GetIndex(double x) {
               return int((x - mStart) / mSampling);
           }
   
   
   
   
   
           double SetScale(double scale) {
               return mScale = scale;
           };
   
           double SetStart(double start) {
               return mStart = start;
           };
   
           double SetSampling(double sampling) {
               return mSampling = sampling;
           };
   
           void Fill(numericType v) {
               mScale = 1.0;
               for (unsigned int i = 0; i < mData.size1(); i++) {
                   for (unsigned int j = 0; j < mData.size2(); j++) {
                       mData(i, j) = v;
                   }
               }
           };
           void FillPoint(unsigned int i, unsigned int j, numericType v) {
               mScale = 1.0;
   
               mData(i, j) = v;
   
           };
   
           void SetData(FrVect* frv) {
               if ((mData.size1() != 1) || (mData.size2() != frv->nData)) {
                   mData.resize(1, frv->nData);
               }
               for (unsigned int i = 0; i < frv->nData; i++) {
                   mData(0, i) = numericType(frv->dataD[i]);
               }
               mScale = 1.0;
               mStart = frv->GTime;
               mSampling = *(frv->dx);
           };
   
           void SetDataF(FrVect* frv, double offset) {
               if ((mData.size1() != 1) || (mData.size2() != frv->nData)) {
                   mData.resize(1, frv->nData);
               }
   
               double slope = mScale;
               switch (frv->type) {
                   case FR_VECT_C:
                       for (unsigned int i = 0; i < frv->nData; i++) {
                           mData(0, i) = ((double) (frv->data[ i ]) * slope + offset);
                           LogDebug(LOG_DEBUG_LEVEL_3, "PUSH %20.20g %20.20g", mStart, mData(0, i));
                       }
                       break;
                   case FR_VECT_2S:
                       for (unsigned int i = 0; i < frv->nData; i++) {
                           mData(0, i) = ((double) (frv->dataS[ i ]) * slope + offset);
                           LogDebug(LOG_DEBUG_LEVEL_3, "PUSH %20.20g %20.20g", mStart, mData(0, i));
   
                       }
                       break;
                   case FR_VECT_4S:
                       for (unsigned int i = 0; i < frv->nData; i++) {
                           mData(0, i) = ((double) (frv->dataI[ i ]) * slope + offset);
                           LogDebug(LOG_DEBUG_LEVEL_3, "PUSH %20.20g %20.20g", mStart, mData(0, i));
                       }
                       break;
                   case FR_VECT_8S:
                       for (unsigned int i = 0; i < frv->nData; i++) {
                           mData(0, i) = ((double) (frv->dataL[ i ]) * slope + offset);
                           LogDebug(LOG_DEBUG_LEVEL_3, "PUSH %20.20g %20.20g", mStart, mData(0, i));
   
                       }
                       break;
                   case FR_VECT_1U:
                       for (unsigned int i = 0; i < frv->nData; i++) {
                           mData(0, i) = ((double) (frv->dataU[ i ]) * slope + offset);
                           LogDebug(LOG_DEBUG_LEVEL_3, "PUSH %20.20g %20.20g", mStart, mData(0, i));
   
                       }
                       break;
                   case FR_VECT_2U:
                       for (unsigned int i = 0; i < frv->nData; i++) {
                           mData(0, i) = ((double) (frv->dataUS[ i ]) * slope + offset);
                           LogDebug(LOG_DEBUG_LEVEL_3, "PUSH %20.20g %20.20g", mStart, mData(0, i));
   
                       }
                       break;
                   case FR_VECT_4U:
                       for (unsigned int i = 0; i < frv->nData; i++) {
                           mData(0, i) = ((double) (frv->dataUI[ i ]) * slope + offset);
                           LogDebug(LOG_DEBUG_LEVEL_3, "PUSH %20.20g %20.20g", mStart, mData(0, i));
   
                       }
                       break;
                   case FR_VECT_8U:
                       for (unsigned int i = 0; i < frv->nData; i++) {
                           mData(0, i) = ((double) (frv->dataUL[ i ]) * slope + offset);
                           LogDebug(LOG_DEBUG_LEVEL_3, "PUSH %20.20g %20.20g", mStart, mData(0, i));
   
                       }
                       break;
                   case FR_VECT_4R:
                       for (unsigned int i = 0; i < frv->nData; i++) {
                           mData(0, i) = ((double) (frv->dataF[ i ]) * slope + offset);
                           LogDebug(LOG_DEBUG_LEVEL_3, "PUSH %20.20g %20.20g", mStart, mData(0, i));
   
                       }
                       break;
                   case FR_VECT_8R:
                       for (unsigned int i = 0; i < frv->nData; i++) {
                           mData(0, i) = ((double) (frv->dataD[ i ]) * slope + offset);
                           LogDebug(LOG_DEBUG_LEVEL_3, "PUSH %20.20g %20.20g", mStart, mData(0, i));
                       }
                       break;
                   default:
                       LogSevere("FrVectCopy: unknown type");
                       throw std::runtime_error("FdChannel::Channel::PushFrVect - unknown type");
               }
   
   
           };
   
   
       protected:
   
           void Rescale() {
               mData *= mScale;
               mScale = 1.0;
           };
   
           boost::numeric::ublas::matrix<numericType> mData; 
           double mScale; 
           double mStart; 
           double mSampling; 
   
   
   
   
       };
   
   
       typedef class SeqView<double> SeqViewDouble; 
       typedef class SeqView<std::complex<double> > SeqViewComplex; 
   
   
   } // namespace tsa
   
   #endif // __SEQVIEW_HPP
   
