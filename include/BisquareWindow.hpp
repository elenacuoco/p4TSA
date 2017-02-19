/**
 * @file   AlgoBisquareWindow.hpp
 * @author Giancarlo Cella <giancarlo.cella@pi.infn.it>
 * @date   Sat Nov 13 17:21:06 2004
 *
 * @brief  Bisquare windowing
 *
 *
 *   Copyright (C) 2004 by Giancarlo Cella
 *   giancarlo.cella@pi.infn.it
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation; either version 2 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program; if not, write to the
 *   Free Software Foundation, Inc.,
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 **/
#ifndef __ALGOBISQUAREWINDOW_HPP
#define __ALGOBISQUAREWINDOW_HPP

/**
 * @name System includes
 **/
//@{

//@}

/**
 * @name Project includes
 **/
//@{
#include <BaseWindow.hpp>
//@}

/**
 * @name Local includes
 **/
//@{

//@}

/**
 * @name Forward references
 **/
//@{

//@}


using namespace boost::numeric::ublas;

namespace tsa {

    /**
     * @class BisquareWindow
     * @brief Bisquare windowing algorithm
     *
     * 
     **/
    class BisquareWindow : public BaseWindow {
    public:

        /**
         * Constructor
         *
         * @param size the size of the window
         * @param cached true if the window must be preevaluated in a buffer
         **/
        BisquareWindow(int size)
        :
        BaseWindow(size) {
            FillWindow();
        };

        BisquareWindow(int size, const std::string&)
        :
        BaseWindow(size) {
            FillWindow();
        };

        /**
         * Destructor
         **/
        virtual ~BisquareWindow() {

        };

        /**
         * @name Operations
         **/
        //@{

        /** 
         * Apply the window to a given time view.
         * 
         * @param v1 the time view 
         */
        void operator()(SeqViewDouble& v1) {

            if (v1.GetSize() != mWindow.size()) {
                Resize(v1.GetSize());
                LogWarning("BisquareWindow: Resizing window");
            }

            execute(
                    *v1.GetData(),
                    *v1.GetData()
                    );

        };

        /** 
         * Apply a window to an input view and write the results on a 
         * output view.
         *
         * @param v1 the input view
         * @param v2 the output view
         * 
         */
        void operator()(SeqViewDouble& v1, SeqViewDouble& v2) {

            Dmatrix *arg1 = v1.GetData();
            Dmatrix *arg2 = v2.GetData();

            if (v1.GetSize() != mWindow.size()) {
                Resize(v1.GetSize());
                LogWarning("BisquareWindow: Resizing window");
            }

            if ((arg1->size1() != arg2->size1()) || (arg1->size2() != arg2->size2())) {
                arg2->resize(arg1->size1(), arg1->size2());
                LogWarning("BisquareWindow: Resizing output");
            }

            execute(*arg1, *arg2);

            v2.SetScale(v1.GetScale());
            v2.SetStart(v1.GetStart());
            v2.SetSampling(v1.GetSampling());


        };

        /** 
         * Resize the window dimension.
         * 
         * @param size new size for the window
         */
        void Resize(unsigned int size) {
            BaseWindow::Resize(size);
            FillWindow();
        }


        //@}

        /**
         * @name Getters
         **/
        //@{



        //@}

        /**
         * @name Setters
         **/
        //@{


        //@}

    protected:




    private:

        /** 
         * Initialize the window with the correct values, given
         * its actual size. This is a pure virtual function, which 
         * is redefined by each window class.
         * 
         */
        void FillWindow() {
            for (unsigned int i = 0; i < mWindow.size(); i++) {
                double x = 0.5 * mWindow.size() - 0.5;
                double q = fabs(i - x) / x;
                mWindow(i) = (1.0 - q * q)*(1.0 - q * q);
            }
            Normalize();
        };


    };

    /**
     * @name Inline methods
     **/
    //@{


    //@}

    /**
     * @name External references
     **/
    //@{

    //@}


} // end namespace tsa

#endif // __ALGOBISQUAREWINDOW_HPP
