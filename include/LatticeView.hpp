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
/// @file   LatticeView.hpp 
/// @author Elena Cuoco <elena.cuoco@ego-gw.it>
/// @date   2004
///
/// @brief  Define a LatticeView for the Whitening filters
///
#ifndef __LATTICEVIEW_HPP
#define __LATTICEVIEW_HPP


///
/// @name System includes
///
//@{

#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <eternity.hpp>
//@}

///
/// @name Project includes
///
//@{
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
using namespace boost::numeric::ublas;
namespace tsa {

    ///
    /// @brief  Define the object needed to implement the Lattice filter
    ///
    ///
    ///

    class LatticeView : public BaseView {
    public:
        ///
        /// Constructor
        ///

        LatticeView(unsigned int ArOrder = 1)
        :
        mOrder(ArOrder),
        mErrorForward(2, ArOrder + 1),
        mErrorBackward(2, ArOrder + 1),
        mParcorF(ArOrder + 1),
        mParcorB(ArOrder + 1) {
            mErrorForward.clear();
            mErrorBackward.clear();
            mParcorF.clear();
            mParcorB.clear();
        }

        ///

        ~LatticeView() {
        }

        void Load(const char *filename, const char *fmt = "txt") {
            eternity::xml_archive fa;
            fa.open(filename, eternity::archive::load);
            xml_serialize(fa, "");
            fa.close();
        }

        void Save(const char *filename, const char *fmt = "txt") {
            eternity::xml_archive fa;
            fa.open(filename, eternity::archive::store);
            xml_serialize(fa, "");
            fa.close();
        }

        void xml_serialize(eternity::xml_archive& xml, const char* prefix) {
            char buffer[1024];

            if (xml.is_loading()) {

                snprintf(buffer, 1024, "%s.mOrder", prefix);
                xml.read(buffer, mOrder, 0);
                snprintf(buffer, 1024, "%s.mErrorForward", prefix);
                DMATRIX_XML_SERIALIZE(mErrorForward, xml, buffer);
                snprintf(buffer, 1024, "%s.mErrorBackward", prefix);
                DMATRIX_XML_SERIALIZE(mErrorBackward, xml, buffer);
                snprintf(buffer, 1024, "%s.mParcorF", prefix);
                DVECTOR_XML_SERIALIZE(mParcorF, xml, buffer);
                snprintf(buffer, 1024, "%s.mParcorB", prefix);
                DVECTOR_XML_SERIALIZE(mParcorB, xml, buffer);
            } else {
                snprintf(buffer, 1024, "%s.mOrder", prefix);
                xml.write(buffer, mOrder);
                snprintf(buffer, 1024, "%s.mErrorForward", prefix);
                DMATRIX_XML_SERIALIZE(mErrorForward, xml, buffer);
                snprintf(buffer, 1024, "%s.mErrorBackward", prefix);
                DMATRIX_XML_SERIALIZE(mErrorBackward, xml, buffer);
                snprintf(buffer, 1024, "%s.mParcorF", prefix);
                DVECTOR_XML_SERIALIZE(mParcorF, xml, buffer);
                snprintf(buffer, 1024, "%s.mParcorB", prefix);
                DVECTOR_XML_SERIALIZE(mParcorB, xml, buffer);
            }
        }



        ///
        /// @name Getters
        ///
        //@{

        /**
         * 
         * @return Order of the LatticeView 
         */
        unsigned int GetOrder() {
            return mOrder;
        }
        ///

        /**
         * 
         * 
         * @param j index of the vector 
         * @return The Parcor parameter
         */
        double GetParcor(unsigned int j) {
            return mParcorF(j);
        }
        ///

        Dvector* GetParcorF() {
            return &mParcorF;
        }

        Dvector* GetParcorB() {
            return &mParcorB;
        }

        /**
         * 
         * 
         * @param j index of the vector 
         * @return The Parcor parameter
         */
        double GetParcorF(unsigned int j) {
            return mParcorF(j);
        }

        /**
         * 
         * 
         * @param j index of the vector 
         * @return The Parcor parameter
         */
        double GetParcorB(unsigned int j) {
            return mParcorB(j);
        }

        Dmatrix* GetErrorForward() {
            return &mErrorForward;
        }

        Dmatrix* GetErrorBackward() {
            return &mErrorBackward;
        }


        ///
        ///
        ///

        double GetErrorForward(unsigned int i, unsigned int j) {
            return mErrorForward(i, j);
        }
        ///
        ///
        ///

        double GetErrorBackward(unsigned int i, unsigned int j) {
            return mErrorBackward(i, j);
        }
        ///
        //@}


        ///
        /// @name Setters
        ///
        //@{

        void SetOrder(unsigned int v) {
            mOrder = v;
        };

        void SetParcorF(unsigned int j, double v) {
            mParcorF(j) = v;
        }

        void SetParcorB(unsigned int j, double v) {
            mParcorB(j) = v;
        }

        void SetErrorForward(unsigned int j, double v) {
            mErrorForward(0, j) = v;
            mErrorForward(1, j) = v;
        }

        void SetErrorBackward(unsigned int j, double v) {
            mErrorBackward(0, j) = v;
            mErrorBackward(1, j) = v;
        }

        //@}


    protected:

    private:
        unsigned int mOrder; ///< the Order of the View
        Dmatrix mErrorForward; ///< the Error Forward for the Lattice Filter
        Dmatrix mErrorBackward; ///< the Error Backward for the Lattice Filter
        Dvector mParcorF; ///< the vector of forward Parcor
        Dvector mParcorB; ///< the vector of backward Parcor

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

} //end namespace tsa

#endif // ___LATTICEVIEW_HPP
