#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/matrix_proxy.hpp>
#include <boost/numeric/ublas/io.hpp>

#ifndef __SEQVIEW_HPP
#define __SEQVIEW_HPP
///
/// @file   SeqView.hpp
/// @author Antonio Eleuteri <antonio.eleuteri@na.infn.it>
/// @date   Wed Nov 24 17:05:33 2004
/// 
/// @brief  Define Sequence view


#include <BaseView.hpp>
#include <FrameL.h> 

namespace tsa {

    ///
    /// @brief Time view: container for time series.
    ///

    template<class T>
    class SeqView : public BaseView {
    public:
        typedef T numericType;
        typedef boost::numeric::ublas::matrix<T> matrixType;

        ///
        /// Constructor.
        ///
        ///    

        SeqView()
        :
        mData(1, 1024),
        mScale(1.0),
        mStart(0.0),
        mSampling(0.01) {
            Clear();
        };



        /// Constructor.
        ///
        /// @param aStart start of the sequence
        /// @param aSampling sampling the sequence
        /// @param ChannelSize the number of data in each channel
        /// @param aName a name for the data
        /// @param ColumnDim the dimension of the column structure
        ///
        ///  

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

        /**
         * Copy constructor
         *	
         * @param from The instance that must be copied
         **/
        SeqView(const SeqView& from) {
            mScale = from.mScale;
            mData = from.mData;
            mStart = from.mStart;
            mSampling = from.mSampling;
        }



        /// 
        ///
        /// Destructor
        /// 

        ~SeqView() {

        };

        ///
        /// @name Operations
        ///
        //@{

        ///
        /// Assignement operator
        /// 
        /// @param from The instance to be assigned from
        ///
        /// @return a reference to a new object

        SeqView& operator=(const SeqView& from) {
            mScale = from.mScale;
            mData = from.mData;
            mStart = from.mStart;
            mSampling = from.mSampling;

            return *this;
        }



        /// Clear the data in the view, which are 
        /// all initialized to zero.
        ///

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
               
            }
            read(fd, name, len);
            if (strcmp(name, typeid (*this).name()) != 0) {
                LogSevere("Read: expecting class %s, got class %s",
                        typeid (*this).name(),
                        name);
               
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




        //@}

        ///
        /// @name Data access
        ///
        //@{


        /// Get a value in the first channel at a given index. It is
        /// equivalent to @ref AsVector
        ///
        /// @param f the index
        ///
        /// @return the data value
        ///

        numericType& operator()(unsigned int f) {
            if (mScale != 1.0) Rescale();
            return mData(0, f);
        };


        /// Get a value in the first channel at a given value 
        /// of the time or frequency
        ///
        /// @param f the time/frequency value
        ///
        /// @return the data value
        ///

        numericType get(double x) {
            if (mScale != 1.0) Rescale();
            unsigned int i = (unsigned int) ((x - mStart) / mSampling);
            if (i >= mData.size2()) i = mData.size2() - 1;
            return mData(0, i);
        };


        /// Get a value in a channel at a given value 
        /// of the time or frequency
        ///
        /// @param c the channel
        /// @param f the time/frequency value
        ///
        /// @return the data value
        ///

        numericType get(unsigned int c, double x) {
            if (mScale != 1.0) Rescale();
            unsigned int i = (unsigned int) ((x - mStart) / mSampling);
            if (i >= mData.size2()) i = mData.size2() - 1;
            return mData(c, i);
        };



        /// Get a value in a given channel at a given index. It is
        /// equivalent to @ref AsVector
        ///
        /// @param channel the channel number
        /// @param f the index
        ///
        /// @return the data value
        ///

        numericType& operator()(unsigned int channel, unsigned int f) {
            if (mScale != 1.0) Rescale();
            return mData(channel, f);
        };

        /// Get a value in a given channel at a given index. It is 
        /// equivalent to @ref operator()
        ///
        /// @param channel the channel number
        /// @param f the index
        ///
        /// @return the data value
        ///

        numericType& asVector(unsigned int channel, unsigned int f) {
            if (mScale != 1.0) Rescale();
            return mData(channel, f);
        };


        /// Get a value in a given channel at a given index. Channels are
        /// organized accordingly with the matrix shape MA
        ///
        /// @param i the row index
        /// @param j the column index
        /// @param f the index
        ///
        /// @return the data value
        ///

        template<class MA>
        numericType& asMatrix(unsigned int i, unsigned int j, unsigned int f) {
            if (mScale != 1.0) Rescale();
            unsigned int lda = MA::Dimension(mData.size1());
            return mData(MA::Map(i, j, lda), f);
        };


        //@}


        ///
        /// @name Getters
        ///
        //@{

        boost::numeric::ublas::matrix<numericType>* GetData() {
            return &mData;
        }

        /// Get the scale of the sequence
        ///
        /// @return scale of the sequence
        ///  

        double GetScale() {
            return mScale;
        }

        /// Get the start of the sequence
        ///
        /// @return start of the sequence
        ///  

        double GetStart() {
            return mStart;
        }

        /// Get the sampling of the sequence
        ///
        ///
        /// @return the sampling of the sequence
        ///

        double GetSampling() {
            return mSampling;
        }


        /// Get the number of data in the time series
        ///
        ///
        /// @return the number of data in the time series
        ///

        unsigned int GetSize() {
            return mData.size2();
        };

        /// Get the number of channels in the view
        ///
        ///
        /// @return the number of channels
        ///

        unsigned int GetChannels() {
            return mData.size1();
        };


        /// Get the label (x value) of a particular value in the sequence
        ///
        /// @param k the index in the sequence
        ///
        /// @return the label that correspond to a given index in the sequence
        ///  

        double GetX(unsigned int k) {
            return mStart + mSampling*k;
        };

        numericType& GetY(unsigned int channel, unsigned int f) {

            return mData(channel, f);
        };

        /// Get the end label of the sequence
        ///
        /// @return end label of the sequence
        ///

        double GetEnd() {
            return mStart + mSampling * mData.size2();
        };

        /// Get the length of the sequence (in x unit)
        ///
        ///
        /// @return the length of the sequence in x unit
        ///

        double GetSlice() {
            return mSampling * mData.size2();
        };

        /// Get the index which correspond to a given x value.
        /// No check is done for the size of the index
        ///
        /// @param x the x value
        ///
        /// @return start of the sequence
        ///  

        int GetIndex(double x) {
            return int((x - mStart) / mSampling);
        }


        //@}

        ///
        /// @name Setters
        ///
        //@{

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
                  
            }


        };

        //@}

    protected:
        /// Rescale the data, setting the auxiliary scale to one.
        ///
        ///

        void Rescale() {
            mData *= mScale;
            mScale = 1.0;
        };

        boost::numeric::ublas::matrix<numericType> mData; ///< The data array
        double mScale; ///< The auxiliary scale 
        double mStart; ///< The start time
        double mSampling; ///< The sampling time




    };


    typedef class SeqView<double> SeqViewDouble; ///< Double precision histogram
    typedef class SeqView<std::complex<double> > SeqViewComplex; ///< Complex histogram


} // namespace tsa

#endif // __SEQVIEW_HPP

