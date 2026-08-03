///
///   Copyright (C) 2004 by Elena Cuoco
///   elena.cuoco@unibo.it
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
/// @file   ARMAView.hpp
/// @author Elena Cuoco <elena.cuoco@unibo.it>
/// @date   2004
///
/// @brief  ARMAView is a view for arma parametrization
///
#ifndef __ARMAVIEW_HPP
#define __ARMAVIEW_HPP


///
/// @name System includes
///
//@{
#include <vector>

//@}

///
/// @name Project includes
///
//@{
#include <BaseView.hpp>
#include <CerealPersistence.hpp>

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
/// namespace
///
namespace tsa {

    ///
    /// @brief ARMA view: container for (vectorial) ARMA processes
    ///
    ///
    /// A view for ARMA parametrization. It defines a general (V)ARMA process, which
    /// can be written as
    /// \f[
    /// \sum_{k=0}^{p} A^{(k)} \vec{y}_{n-k} = \sum_{k=0}^{q} B^{(k)} \vec{x}_{n-k}
    /// \f]
    /// where A,B are square matrix of dimension d equal to the dimension of the input
    /// and output vectors x,y.
    /// If the order of the part MA q is equal to zero the process is an AR process.
    /// If the order of the AR part p is equal to zero the process is an MA process.
    /// Note that the matrix \f$A^{(0)}\f$ is assumed to be the identity.
    ///

    class ARMAView : public BaseView {
    public:
        ///
        /// Constructor
        ///@param maxP the order of the AR part
        ///@param maxQ the order of the MA part
        ///@param channels the dimension of
        ///

        ARMAView(unsigned int maxP, unsigned int maxQ, int channels = 1)
        :
        mAR(maxP + 1),
        mMA(maxQ + 1),
        mChannels(channels) {
            ResizeAR(maxP + 1);
            ResizeMA(maxQ + 1);
        };

        ///
        /// Copy constructor
        ///
        /// @param from The instance that must be copied

        ARMAView(const ARMAView& from)
        :
        BaseView(from) {
            mChannels = from.mChannels;
            mAR = from.mAR;
            mMA = from.mMA;
        };


        ///
        /// Destructor
        ///

        ~ARMAView() {
        }

        void Load(const char *filename, const char *fmt = nullptr) {
            tsa::LoadBinary(filename, *this);
        }

        void Save(const char *filename, const char *fmt = nullptr) {
            tsa::SaveBinary(filename, *this);
        }

        template<class Archive>
        void serialize(Archive& ar) {
            ar(mChannels, VDmatrixProxy(mAR), VDmatrixProxy(mMA));
        }


        ///
        /// @name Getters
        ///
        //@{

        /// This method gives the value of the AR[i] coefficient for one of the channels.
        /// It is assumed that the VARMA process is diagonal, which means that there is
        /// and independent ARMA process for each channel.
        ///
        /// @param i the index of the AR coefficient
        /// @param channel the channel
        ///
        /// @return the value of the AR[i] coefficient
        ///

        const double& GetAR(int i, unsigned int channel = 0) const {
            return mAR[i](channel, channel);
        };


        /// This method gives the value of the MA[i] coefficient for one of the channels.
        /// It is assumed that the VARMA process is diagonal, which means that there is
        /// and independent ARMA process for each channel.
        ///
        /// @param i the index of the MA coefficient
        /// @param channel the channel
        ///
        /// @return the value of the MA[i] coefficient
        ///

        const double& GetMA(int i, unsigned int channel = 0) const {
            return mMA[i](channel, channel);
        };

        /// This method gives the value of the \f$A^{(i)}_{jk}\f$ coefficient for the VARMA process
        ///
        /// @param i the index of the VAR coefficient
        /// @param channel1 the first channel (index j)
        /// @param channel2 the se channel (index k)
        ///
        /// @return the value of the coefficient \f$A^{(i)}_{jk}\f$
        ///

        const double& GetVAR(int i, unsigned int channel1, unsigned int channel2) const {
            return mAR[i](channel1, channel2);
        };

        /// This method gives the value of the \f$B^{(i)}_{jk}\f$ coefficient for the VARMA process
        ///
        /// @param i the index of the VMA coefficient
        /// @param channel1 the first channel (index j)
        /// @param channel2 the se channel (index k)
        ///
        /// @return the value of the coefficient \f$B^{(i)}_{jk}\f$
        ///

        const double& GetVMA(int i, unsigned int channel1, unsigned int channel2) const {
            return mMA[i](channel1, channel2);
        };


        /// Get the order of the AR part of the process.
        ///
        ///
        /// @return the order of the AR part of the process
        ///

        unsigned int GetArOrder() const {
            return (mAR.size() - 1);
        };

        /// Get the order of the MA part of the process.
        ///
        ///
        /// @return the order of the MA part of the process
        ///

        unsigned int GetMaOrder() const {
            return (mMA.size() - 1);
        };

        /// Get the dimension of the VARMA process.
        ///
        ///
        /// @return the dimension of the VARMA process
        ///

        unsigned int GetChannels() const {
            return mMA[0].size1();
        };

        //@}

        ///
        /// @name Setters
        ///
        //@{


        /// This method sets the value of the AR[i] coefficient for one of the channels.
        /// It is assumed that the VARMA process is diagonal, which means that there is
        /// and independent ARMA process for each channel.
        ///
        /// @param i the index of the AR part
        /// @param v the new value of AR[i]
        /// @param channel the channel
        ///

        void SetAR(int i, double v, unsigned int channel = 0) {
            mAR[i](channel, channel) = v;
        };

        /// This method sets the value of the MA[i] coefficient for one of the channels.
        /// It is assumed that the VARMA process is diagonal, which means that there is
        /// and independent ARMA process for each channel.
        ///
        /// @param i the index of the MA part
        /// @param v the new value of MA[i]
        /// @param channel the channel
        ///

        void SetMA(int i, double v, unsigned int channel = 0) {
            mMA[i](channel, channel) = v;
        };


        /// This method sets the value of the \f$A^{(i)}_{jk}\f$ coefficient for the VARMA process
        ///
        /// @param i the index of the VAR coefficient
        /// @param v the new value of \f$A^{(i)}_{jk}\f$
        /// @param channel1 the first channel (index j)
        /// @param channel2 the se channel (index k)
        ///
        ///

        void SetVAR(int i, double v, unsigned int channel1, unsigned int channel2) {
            mAR[i](channel1, channel2) = v;
        }


        /// This method sets the value of the \f$B^{(i)}_{jk}\f$ coefficient for the VARMA process
        ///
        /// @param i the index of the VAR coefficient
        /// @param v the new value of \f$B^{(i)}_{jk}\f$
        /// @param channel1 the first channel (index j)
        /// @param channel2 the se channel (index k)
        ///
        ///

        void SetVMA(int i, double v, unsigned int channel1, unsigned int channel2) {
            mMA[i](channel1, channel2) = v;
        };


        /// This methods sets the order (p,q) of the (V)ARMA process
        ///
        /// @param maxP the order of the AR part of the process
        /// @param maxQ the order of the MA part of the process
        ///

        void SetOrder(unsigned int maxP, unsigned int maxQ) {
            if (maxP + 1 != mAR.size())
                ResizeAR(maxP + 1);
            if (maxQ + 1 != mMA.size())
                ResizeMA(maxQ + 1);
        };


        /// This method sets the dimension of the VARMA process
        ///
        /// @param channels the dimension of the VARMA process
        ///

        void SetChannels(unsigned int channels) {
            if (channels != mChannels) {
                mChannels = channels;
                ResizeAR(mAR.size());
                ResizeMA(mMA.size());
            }
        };

        //@}


    protected:

    private:


        /// This method change the order of the AR part of the process
        ///
        /// @param order the new order of the AR part
        ///

        void ResizeAR(unsigned int order) {
            if (order != mAR.size()) {
                mAR.resize(order);
                mAR.clear();
            }

            for (unsigned int i = 0; i < mAR.size(); i++) {
                mAR[i].resize(mChannels, mChannels);
                mAR[i].clear();
            }
        };

        /// This method change the order of the MA part of the process
        ///
        /// @param order the new order of the MA part
        ///

        void ResizeMA(unsigned int order) {
            if (order != mMA.size()) {
                mMA.resize(order);
                mMA.clear();
            }
            for (unsigned int i = 0; i < mMA.size(); i++) {
                mMA[i].resize(mChannels, mChannels);
                mMA[i].clear();
            }
        };

        VDmatrix mAR; ///<  The AR part of the process
        VDmatrix mMA; ///<  The MA part of the process
        unsigned int mChannels; ///< The dimension of the VARMA process

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

} //end namespace

#endif // ___ARMAVIEW_HPP



