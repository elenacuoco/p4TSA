///
///   Copyright (C) 2004 by Giancarlo Cella
///   giancarlo.cella@pi.infn.it
///
///   This program is free software; you can redistribute it and/or modify
///   it under the terms of the GNU General Public License as published by
///   the Free Software Foundation; either version 2 of the License, or
///   (at your option) any later version.
///
///   This program is distributed in the hope that it will be useful,
///   but WITHOUT ANY WARRANTY; without even the implied warranty of
///   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
///   GNU General Public License for more details.
///
///   You should have received a copy of the GNU General Public License
///   along with this program; if not, write to the
///   Free Software Foundation, Inc.,
///   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
///
/// @file   FrameIStream.hpp/// @author Giancarlo Cella <giancarlo.cella@pi.infn.it>
/// @date   Sat Nov 13 17:21:06 2004
///
/// @brief  Interface for FrameIStream
///
#ifndef __FRAMEISTREAM_HPP
#define __FRAMEISTREAM_HPP

////// @name System includes
///
//@{
#include <deque>
#include <FrameL.h>
//@}

///
/// @name Project includes
///
//@{
#include <AlgoBase.hpp>
#include <SeqView.hpp>

//@}

///
/// @name Local includes
///
//@{

//@}

///
/// @name Forward references
///
//@{

//@}

///
/// tsa namespace
///
namespace tsa {


    class FrameIStream;

    /**
     * A small structure which contains informations about
     * a data loss period.
     * 
     */
    struct DataException {

        /**
         * Type of problem.
         * 
         */
        enum exception_type {
            data_loss /**< Data loss */
        };

        /** 
         * Constructor
         * 
         * @param ts start of data loss (included)
         * @param te end of data loss (excluded)
         * @param e problem type
         * 
         */
        DataException(double ts, double te, exception_type e) :
        Exception(e), StartTime(ts), EndTime(te) {
        };
        exception_type Exception; /**< Exception type */
        double StartTime; /**< Start time of data loss (included) */
        double EndTime; /**< End time of data loss (excluded)   */
    };

    /**
     * A base class for the descriptor of a data channel.
     * 
     */
    class ChannelDescriptor : public AlgoBase {
    public:

        /** 
         * Constructor.
         * 
         * @param id number of data channel
         * 
         */
        ChannelDescriptor(unsigned int id) : mId(id) {
        };

        /** 
         * This function must be called when there are not enough data 
         * to fill the output view. In this base class does nothing.
         * 
         */
        virtual void AddData() {
        };

        /** 
         * Get the maximul time length of data that can be currently filled
         * without calling AddData.
         * 
         * @return the time length of the data available in seconds
         */
        virtual double GetLength() {
            return 0.0;
        };

        /** 
         * Get the channel time rate
         * 
         * 
         * @return the channel time rate
         */
        virtual double GetRate() {
            return mRate;
        };

        /** 
         * A function to write the available data on an output view. Be careful
         * that if there are not enough data available we get a data loss exception.
         * 
         * @param v output view where the available data are written
         */
        virtual void WriteView(SeqViewDouble& v);

        virtual void FillView(SeqViewDouble& v, double tstart, double tend);


        /** 
         * A function to write the available data on an output view. Be careful
         * that if there are not enough data available we get a data loss exception.
         * At the same time a second view is filled with ones which correspond to 
         * avaliable data, or zeros which correspond to unavailable data.
         * 
         * @param v output view where the available data are written
         * @param validation output view where the available data flags are written
         */
        virtual void WriteView(SeqViewDouble& v, SeqViewDouble& validation);

        /**
         * Destructor
         * 
         */
        virtual ~ChannelDescriptor() {
        };

    protected:
        /** 
         * Call @see Queue n times, passing the given value and the corresponding time.
         * 
         * @param value the value that must be added to the queue
         * @param t the time which correspond to the data
         * @param n number of copies of the data that must be added
         */
        void PushValue(double value, double t, unsigned int n);

        /** 
         * Call @see Queue for a sequence of numerical values. The values are contained
         * inside a FrVect, starting from a given offset. The effective value which is passed
         * to @see Queue is given by y=offset+slope*x, where x is the value contained in the 
         * FrVect.
         * 
         * @param frv pointer to the FrVect containing data
         * @param t time corresponding to the first data contained in the FrVect (neglecting the offset)
         * @param off offset in the FrVect
         * @param offset an optional offset to correct the data
         * @param slope an optional scaling factor to correct the data
         */
        void PushFrVect(FrVect *frv, double t, unsigned int off, double offset, double slope);

        /** 
         * Push a given value v, at the given time t, in the output queue. The value is pushed
         * only if its time is larger or equal that the current mNextTime. If it is larger that the current
         * mNextTime value a data loss is registered.
         *
         * The value of mNextTime is updated.
         *
         * @param v the value
         * @param t the time
         */
        void Queue(double v, double t);

        /** 
         * Check the availability of a value at a given time, looking in the
         * set of registered data losses. Remove from this set all the exceptions
         * which correspond to times lower than t.
         * 
         * @param t requested time
         * 
         * @return true if a number is available at the given time, false otherwise
         */
        bool data_available(double t);


        FrameIStream* mFIS; /**< Pointer to the FrameIStream class which contains this descriptor */
        unsigned int mId; /**< The numerical id of the class */
        double mRate; /**< The rate of the data */
        double mNextTime; /**< The time at which the next data to push on the queue is expected */
        std::deque<double> mData; /**< The data queue */
        std::deque<DataException> mExceptions; /**< The set of data loss exceptions */
    };

    /**
     * A descriptor for an ADC channel
     * 
     */
    class ADC_Channel : public ChannelDescriptor {
    public:
        /** 
         * Constructor
         * 
         * @param FIS pointer to the FrameIStream class
         * @param adc pointer to the first FrAdcData structure
         * @param id id of the channel
         * 
         */
        ADC_Channel(FrameIStream* FIS, FrAdcData* adc, unsigned int id);

        /**
         * Destructor
         * 
         */
        virtual ~ADC_Channel();

        /** 
         * This function must be called when there are not enough data 
         * to fill the output view. It reads a chunk of data from the 
         * current frame
         * 
         */
        virtual void AddData();

        /** 
         * Get the maximul time length of data that can be currently filled
         * without calling AddData.
         * 
         * @return the time length of the data available in seconds
         */
        virtual double GetLength();

        /** 
         * Create, if possible, an instance of the class
         * 
         * @param FIS pointer to the FrameIStream class instance
         * @param name name of the channel
         * @param id index of the channel
         * 
         * @return pointer to the created class instance or null
         */
        static ADC_Channel* Create(FrameIStream* FIS, char* name, unsigned int id);

    private:
        char *mName;


    };

    /**
     * A descriptor for a proc channel
     * 
     */
    class PROC_Channel : public ChannelDescriptor {
    public:

        /** 
         * Constructor
         * 
         * @param FIS pointer to the FrameIStream class
         * @param proc pointer to the first FrProcData structure
         * @param id id of the channel
         * 
         */
        PROC_Channel(FrameIStream* FIS, FrProcData* proc, unsigned int id);

        /**
         * Destructor
         * 
         */
        virtual ~PROC_Channel();

        /** 
         * This function must be called when there are not enough data 
         * to fill the output view. It reads a chunk of data from the next
         * FrProcData structure.
         * 
         */
        virtual void AddData();

        /** 
         * Get the maximul time length of data that can be currently filled
         * without calling AddData.
         * 
         * @return the time length of the data available in seconds
         */
        virtual double GetLength();

        /** 
         * Create, if possible, an instance of the class
         * 
         * @param FIS pointer to the FrameIStream class instance
         * @param name name of the channel
         * @param id index of the channel
         * 
         * @return pointer to the created class instance or null
         */
        static PROC_Channel* Create(FrameIStream* FIS, char* name, unsigned int id);


        virtual void FillView(SeqViewDouble& v, double tstart, double tend);

    private:
        char *mName; /**< The channel's name */


    };

    /**
     * A descriptor for a SIM channel
     * 
     */
    class SIM_Channel : public ChannelDescriptor {
    public:

        /** 
         * Constructor
         * 
         * @param FIS pointer to the FrameIStream class
         * @param sim pointer to the first FrSimData structure
         * @param id id of the channel
         * 
         */
        SIM_Channel(FrameIStream* FIS, FrSimData* sim, unsigned int id);

        /**
         * Destructor
         * 
         */
        virtual ~SIM_Channel();

        /** 
         * This function must be called when there are not enough data 
         * to fill the output view. It reads a chunk of data from the next
         * FrSimData structure.
         * 
         */
        virtual void AddData();

        /** 
         * Get the maximul time length of data that can be currently filled
         * without calling AddData.
         * 
         * @return the time length of the data available in seconds
         */
        virtual double GetLength();

        /** 
         * Create, if possible, an instance of the class
         * 
         * @param FIS pointer to the FrameIStream class instance
         * @param name name of the channel
         * @param id index of the channel
         * 
         * @return pointer to the created class instance or null
         */
        static SIM_Channel* Create(FrameIStream* FIS, char* name, unsigned int id);

    private:
        char *mName; /**< The channel's name */

    };

    /**
     * A descriptor for a SER channel
     * 
     */
    class SER_Channel : public ChannelDescriptor {
    public:

        /** 
         * Constructor
         * 
         * @param FIS pointer to the FrameIStream class
         * @param smsName the serial structure name
         * @param smsParam the serial parameter name
         * @param id id of the channel
         * 
         */
        SER_Channel(FrameIStream* FIS, char* smsName, char* smsParam, unsigned int id);

        /**
         * Destructor
         * 
         */
        virtual ~SER_Channel();

        /** 
         * This function must be called when there are not enough data 
         * to fill the output view. It reads a chunk of data from the next
         * serial data structure.
         * 
         */
        virtual void AddData();

        /** 
         * Get the maximul time length of data that can be currently filled
         * without calling AddData.
         * 
         * @return the time length of the data available in seconds
         */
        virtual double GetLength();

        /** 
         * Create, if possible, an instance of the class
         * 
         * @param FIS pointer to the FrameIStream class instance
         * @param name name of the channel
         * @param id index of the channel
         * 
         * @return pointer to the created class instance or null
         */
        static SER_Channel* Create(FrameIStream* FIS, char *name, unsigned int id);

    private:
        char *mSmsName; /**< The serial channel name */
        char *mSmsParam; /**< The serial channel parameter name */

    };

    /**
     * Descriptor for a FrameH field channel.
     * 
     */
    class FRAMEH_Channel : public ChannelDescriptor {
    public:

        /**
         * Field type in the frame to dump on channel
         * 
         */
        enum field_type {
            field_run, /**< Run number */
            field_frame, /**< Frame number */
            field_dataQuality, /**< Data quality */
            field_GTimeS, /**< GTimeS */
            field_GTimeN, /**< GTimeN */
            field_ULeapS, /**< ULeapS */
            field_dt, /**< dt */
            field_time /**< time */
        };

        /** 
         * Constructor
         * 
         * @param FIS pointer to the FrameIStream class
         * @param ft the field type of the requested channel
         * @param id id of the channel
         * 
         */
        FRAMEH_Channel(FrameIStream* FIS, enum field_type ft, unsigned int id);

        /**
         * Destructor
         * 
         */
        virtual ~FRAMEH_Channel();

        /** 
         * This function must be called when there are not enough data 
         * to fill the output view. It reads a chunk of data from the 
         * current frame.
         * 
         */
        virtual void AddData();

        /** 
         * Get the maximul time length of data that can be currently filled
         * without calling AddData.
         * 
         * @return the time length of the data available in seconds
         */
        virtual double GetLength();

        /** 
         * Create, if possible, an instance of the class
         * 
         * @param FIS pointer to the FrameIStream class instance
         * @param name name of the channel
         * @param id index of the channel
         * 
         * @return pointer to the created class instance or null
         */
        static FRAMEH_Channel* Create(FrameIStream* FIS, char *field_name, unsigned int id);

    private:
        char *mFieldName; /**< Field name */
        enum field_type mFieldType; /**< Field type */

    };

    /**
     * @brief A source of data taken from a Frame file
     *
     * This class can be used to read data from a frame file. 
     * A set of channels can be specified, which are returned together.
     *
     * 
     *
     * Ser data:
     *
     * Channel:Parameter:Frequency:Default
     *
     **/
    class FrameIStream : public AlgoBase {
    public:

        /// Constructor
        ///
        /// @param fileName the name of the frame file (or a ffl file)
        /// @param StartTime start time of the data chunk we want
        ///
        ///
        FrameIStream(
                const std::string& fileName,
                const double& StartTime
                );



        /// Constructor
        ///
        /// @param fileName the name of the frame file (or a ffl file)
        /// @param StartTime start time of the data chunk we want
        /// @param TimeLength time length of requested data
        /// @param channelNames a list of channel's names
        ///
        ///
        FrameIStream(
                const std::string& fileName,
                const double& StartTime,
                const double& TimeLength,
                const std::vector<std::string>& channelNames
                );

        ///
        /// Destructor
        ///
        ~FrameIStream();

        ///
        /// @name Operations
        ///
        //@{

        void Init();



        /// Read data from the frame file. 
        ///
        /// @param rSeqView A list of time views to fill with data. 
        /// Each view contain a single channel.
        ///
        /// @return a reference to the instance of the class
        ///
        FrameIStream& operator>>(std::vector<SeqViewDouble>& rSeqView);


       // unsigned int ReadDataUntil(SeqViewDouble& rSeqView, double time, unsigned int maxlen);



        /// Read data from the frame file. 
        ///
        /// @param rSeqView A list a time view to fill with data.  It contains a single channel.
        ///
        /// @return a reference to the instance of the class
        ///
        FrameIStream& operator>>(SeqViewDouble& rSeqView);


        void FillView(SeqViewDouble& rSeqView, double tstart, double tend);



        //@}

        ///
        /// @name Getters
        ///
        //@{

        std::string GetInfo(int gtime = 0);


        /// Get the file name of the frame file used.
        ///
        ///
        /// @return the file name of the frame file
        ///
        const std::string& GetFileName(void) const;

        /// Get the list of the channel's names.
        ///
        ///
        /// @return a list of channel's names
        ///
        const std::vector<std::string>& GetChannelNames(void) const;

        /// Get the actual start time, which is the start time
        /// of the next data chunk that will be read.
        ///
        /// @return the actual start time
        ///
        double GetStartTime(void) const;

        /// Get the actual end time, which is the end time
        /// of the next data chunk that will be read.
        ///
        /// @return the actual end time
        ///
        double GetEndTime(void) const;

        /// Get the sampling time of a channel
        ///
        /// @param cname the channel's name
        ///
        /// @return the channel's sampling time
        ///
        double GetSampling(unsigned int cn) const;

        /// Get the time duration of the next data chunk that will be 
        /// read.
        ///
        /// @return the actual time duration.
        ///

        double GetTimeLength() {
            return mTimeLength;
        };

        /** 
         * Get a pointer to the current FrameH structure.
         * 
         * 
         * @return a pointer to the current FrameH
         */
        FrameH* GetFrame() {
            return mpFrame;
        };

        struct FrFile* GetFrameFile() {
            return mpFrameFile;
        };

        /** 
         * Get the value of the data loss flag. It is
         * true if a data loss event is occurred.
         * 
         * @return the data loss flag value
         */
        bool GetDataLossFlag() {
            return mDataLoss;
        };

        //@}

        ///
        /// @name Setters
        ///
        //@{

        /** 
         * Set the channels which should be opened
         * 
         * @param channelNames vector of names for the channels
         */
        void SetChannels(const std::vector<std::string>& channelNames);

        /**
         * Set the length of the data buffer that will be returned from now on
         * @param length the new length
         */
        void SetTimeLength(double length);

        /** 
         * Set to zero the validation view. No validation data are
         * written.
         */
        void ResetValidationView();

        /** 
         * Set the current validation view. From now on the validation 
         * data are written on the given views every time some data is read.
         * 
         * @param rValidationView pointer to a vector of validation views
         */
        void SetValidationView(std::vector<SeqViewDouble> *rValidationView);

        /** 
         * Set the value of the data loss flag.
         * 
         * @param status new value of the data loss flag
         */
        void SetDataLossFlag(bool status) {
            mDataLoss = status;
        }

        /** 
         * Ad an exception to the set of data losses.
         * 
         * @param msg exception textual message
         * @param miss_start start time for data loss
         * @param miss_end end time for data loss (excluded)
         * @param channel channel where the data loss occurred
         */
        void AddException(const std::string& msg, double miss_start, double miss_end, unsigned int channel) {
            mMissExceptions.push_back(missing_data(msg, miss_start, miss_end, channel));
        }

        //@}

    protected:

    private:

        /** 
         * Create a new channel descriptor.
         * 
         * @param cname the name of the requested channel descriptor
         * @param id the index of the desired channel descriptor
         * 
         * @return a pointer to the new channel descriptor structure, or null
         */
        ChannelDescriptor* CreateChannelDescriptor(const std::string& cname, unsigned int id);

        /** 
         * Test if some data are required.
         * 
         * 
         * @return true if soem data are required
         */
        bool DataRequired();

        /** 
         * Get new data from the file
         * 
         */
        void GetData();


        double mStartTime; /**< Start time for the data queue */
        double mTimeLength; /**< Time length of the data given at each request */
        struct FrFile* mpFrameFile; /**< The current frame file */
        FrameH* mpFrame; /**< The current FrameH structure */
        std::vector<std::string> mChannelNames; /**< The list of channel names */
        std::string mFileName; /**< The file name */
        std::vector<ChannelDescriptor*> mChannelDescriptors; /**< list of channel descriptor */
        std::vector<SeqViewDouble> *mValidationView; /**< Pointer to the validation views */
        bool mDataLoss; /**< Data loss flag */
        std::deque<missing_data> mMissExceptions; /**< Set of data loss exception */
    };

    ///
    /// @name Inline methods
    ///
    //@{


    //@}

    ///
    /// @name External references
    ///
    //@{

    //@}


} // end namespace tsa

#endif // __FRAMEISTREAM_HPP
