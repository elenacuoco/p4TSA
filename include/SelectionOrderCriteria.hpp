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
/// @file   SelectionOrderCriteria.hpp
/// @author Elena Cuoco <elena.cuoco@ego-gw.it>
/// @date   2005
///
/// @brief  Estimate the function for the AR Selection Order Criteria
///
#ifndef __SELECTIONORDERCRITERIA_HPP
#define __SELECTIONORDERCRITERIA_HPP


///
/// @name System includes
///
//@{


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

/// @name Forward references
///
//@{


//@}

///
/// namespace
///
using namespace boost::numeric::ublas;
namespace tsa {

    ///
    ///
    /// A more detailed description of SelectionOrderCriteria
    ///
    /**
    Produce order selection criteria*/
    ///
    ///

    class SelectionOrderCriteria : AlgoBase {
    public:

        ///
        /// Constructor
        ///
        SelectionOrderCriteria(unsigned int N, unsigned int Order);

        ///
        /// Destructor
        ///
        virtual ~SelectionOrderCriteria();


        ///
        /// @name Operations
        ///
        ///@{

        ///
        /// @brief Brief documentation for the execute method.
        ///
        /// Start of the long documentation for execute method.
        ///
        /// @pre A precondition
        /// @post A postcondition
        /// @exception An exception
        ///
        /// @param a parameter
        ///
        /// @return a returned value
        ///
        /// Declaration of execute operation
        void execute(Dvector& Parcor);
        //@}

        ///
        /// @name Getters
        /// @return values for selected selection criteria
        //@{

        double GetEps(unsigned int j) {
            return mEps(j);
        }
        /// @return values for selected selection criteria

        double GetFpe(unsigned int j) {
            return mFpe(j);
        }
        /// @return values for selected selection criteria

        double GetMdl(unsigned int j) {
            return mMdl(j);
        }
        /// @return values for selected selection criteria

        double GetAic(unsigned int j) {
            return mAic(j);
        }
        /// @return values for selected selection criteria

        double GetAicC(unsigned int j) {
            return mAicC(j);
        }
        /// @return values for selected selection criteria

        double GetCat(unsigned int j) {
            return mCat(j);
        }
        /// @return values for selected selection criteria

        double GetHQ(unsigned int j) {
            return mHQ(j);
        }
        /// @return values for selected selection criteria

        double GetCic(unsigned int j) {
            return mCic(j);
        }
        /// @return values for selected selection criteria

        double GetFsic(unsigned int j) {
            return mFsic(j);
        }

        //@}

        ///
        /// @name Setters
        ///
        //@{

        //@}


    protected:

    private:
        unsigned int mMaxOrder;
        unsigned int mN;
        unsigned int mSelOrd;
        Dvector mEps;
        Dvector mFpe;
        Dvector mMdl;
        Dvector mAic;
        Dvector mAicC;
        Dvector mCat;
        Dvector mHQ;
        Dvector mFsic;
        Dvector mCic;


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

#endif //  __SELECTIONORDERCRITERIA_HPP
