/**
 * @file   TukeyWindow.hpp
 * @author Giancarlo Cella <giancarlo.cella@pi.infn.it>
 * @date   Sat Nov 13 17:21:06 2004
 *
 * @brief  Cs2Hamming windowing
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
#ifndef __TUKEYWINDOW_HPP
#define __TUKEYWINDOW_HPP

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
#include <tsaUtilityFunctions.hpp>
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


/**
 * @namespace tsa
 *
 * @brief The main namespace of the library.
 **/
namespace tsa {

    /**
     * @class TukeyWindow
     * @brief Tukey windowing algorithm
     * Harris, F. J. "On the Use of Windows for Harmonic Analysis with the Discrete Fourier Transform." 
     * Proceedings of the IEEE. Vol. 66 (January 1978). pp. 66-67.
     **/
    class TukeyWindow : public BaseWindow {
    public:

        /**
         * Constructor
         *
         * @param size the size of the window
         * @param cached true if the window must be preevaluated in a buffer
         **/
        TukeyWindow(int size)
        :
        BaseWindow(size) {
            LogInfo(LOGH1);
            LogInfo("TukeyHannWindow");
            LogInfo(LOGH2);
            LogInfo("Size: %d", size);
            LogInfo("Parameters: 0.5");
            LogInfo(LOGH1);
            FillWindow();

            mR = 0.5;
            FillWindow();
        };

        TukeyWindow(int size, const std::string& par)
        :
        BaseWindow(size) {
            LogInfo(LOGH1);
            LogInfo("TukeyHannWindow");
            LogInfo(LOGH2);
            LogInfo("Size: %d", size);
            LogInfo("Parameters: %s", par.c_str());
            LogInfo(LOGH1);
            FillWindow();
            ParseParameterString parse(par);
            mR = parse.GetFloat(0);
            FillWindow();
        };

        /**
         * Destructor
         **/
        virtual ~TukeyWindow() {

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
                LogWarning("TukeyWindow: Resizing window");
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
                LogWarning("TukeyWindow: Resizing window");
            }

            if ((arg1->size1() != arg2->size1()) || (arg1->size2() != arg2->size2())) {
                arg2->resize(arg1->size1(), arg1->size2());
                LogWarning("TukeyWindow: Resizing output");
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

        /** 
         * Get the value of the window at a given index.
         * 
         * 
         * @return the value of the window at the given plage
         */
        double operator()(int i) {
            return mWindow(i);
        };


        //@}

        /**
         * @name Setters
         **/
        //@{


        //@}

    protected:



    private:

        double mR;

        /** 
         * Initialize the window with the correct values, given
         * its actual size. This is a pure virtual function, which 
         * is redefined by each window class.
         * 
         */
        void FillWindow() {
            double n = (double) mWindow.size();

            double nn = n - 1.0;
            double a = 1.0 - mR;

            for (unsigned int i = 0; i < mWindow.size(); i++) {
                double np = i - 0.5 * n;
                if (fabs(np) < a * 0.5 * nn) {
                    mWindow(i) = 1.0;
                } else {
                    mWindow(i) = 0.5 * (1.0 + cos(M_PI * (fabs(np) - a * 0.5 * nn) / (0.5 * (1.0 - a) * nn)));
                }
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

#endif // __TUKEYWINDOW_HPP
