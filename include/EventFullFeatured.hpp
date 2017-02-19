///
///   Copyright (C) 2004 by Elena Cuoco
///   elena.cuoco@ego-gw.it
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
/// @file   EventDescription.hpp
/// @author Elena Cuoco <elena.cuoco@ego-gw.it>
/// @date   2005
///
/// @brief  EventDescription is a class container for a transient event
///
#ifndef __EVENTFULLFEATURED_hpp
#define __EVENTFULLFEATURED_hpp


///
/// @name System includes
///
//@{

#include <string>

//@}

///
/// @name Project includes
///
//@{

#include <AlgoBase.hpp>
#include <BaseView.hpp>

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
    ///
    ///

    /* This class contain the event found by WDF plus the vector of  wavelet coefficients up to @NumCoeff coefficients. */



    class EventFullFeatured {
    public:
        typedef boost::numeric::ublas::vector< double > Dvector;
        EventFullFeatured(unsigned int NumCoeff);


        /**
         * Destructor
         */
        virtual ~EventFullFeatured();

        void operator=(const EventFullFeatured& from);

        void EVcopy(const EventFullFeatured& from);

        void outprint() {
            std::cout << "Time" << " " << mTime << "\n";
            std::cout << "SNR" << " " << mSNR << "\n";
            std::cout << "freq" << " " << mlevel << "\n";
            std::cout << "wavelet type" << " " << mWave << "\n";
            std::cout << "dimension" << " " << mCoeff.size() << "\n";

            for (unsigned int i = 0; i < mCoeff.size(); i++) {
                std::cout << "coeff" << "-" << i << " " << mCoeff[i] << "\n";
            }

        }

        void SetCoeff(int i, double v) {
            mCoeff(i) = v;
        }

        double GetCoeff(unsigned int i) {
            return mCoeff(i);

        }


        double mTime;
        double mSNR;
        Dvector mCoeff;
        double mlevel;
        std::string mWave;
    private:
    protected:




    };





} //end namespace

#endif // __EVENTFULLFEATURED_hpp
