/**
 * @file   BaseWindow.hpp
 * @author Giancarlo Cella <giancarlo.cella@pi.infn.it>
 * @date   Sat Nov 13 17:21:06 2004
 *
 * @brief  Base class for Windowing
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
 *
 **/
#ifndef __BASEWINDOW_HPP
#define __BASEWINDOW_HPP

/**
 * @name System includes
 **/
//@{
#include <map>
#include <stdio.h>
#include <boost/numeric/ublas/matrix.hpp>

//@}

/**
 * @name Project includes
 **/
//@{
#include <AlgoBase.hpp>

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
     * @class BaseWindow
     * @brief Base class for various windowing algorithms
     *
     * 
     **/
    class BaseWindow : public AlgoBase {
    public:
        /**
         * Constructor
         *
         **/
        BaseWindow(unsigned int size);

        /**
         * Destructor
         **/
        virtual ~BaseWindow();

        /**
         * @name Operations
         **/
        //@{

        static double CrossAverage(BaseWindow& w1, BaseWindow& w2);

        static double CrossSquareAverage(BaseWindow& w1, BaseWindow& w2);


        virtual void operator()(SeqViewDouble& v1);

        virtual void operator()(SeqViewDouble& v1, SeqViewDouble& v2);


        /** 
         * Apply the window to each row of the input data matrix, writing
         * the result on the output data matrix.
         * 
         * @param in input matrix of data
         * @param out output matrix of data
         */
        void execute(Dmatrix& in, Dmatrix& out);

        void execute(Dmatrix& in, Dmatrix& out, unsigned int offset);


        /** 
         * Apply the window to each row of the data matrix, writing
         * the result on the matrix itself.
         * 
         * @param inout data matrix
         */
        void execute(Dmatrix& inout);

        void execute(Dvector& inout);

        /** 
         * Get the value of the window at a given index.
         * 
         * 
         * @return the value of the window at the given plage
         */
        double operator()(int i);

        /** 
         * Resize the window dimension.
         * 
         * @param size new size for the window
         */
        virtual void Resize(unsigned int size);

        //@}

        /**
         * @name Getters
         **/
        //@{

        /** 
         * Get the actual size of the window.
         * 
         * 
         * @return the actual size of the window
         */
        unsigned int GetSize();

        //@}

        /**
         * @name Setters
         **/
        //@{


        //@}
        virtual void Normalize();
    protected:

        /**
         * Initialize the window with the correct values, given
         * its actual size. This is a pure virtual function, which
         * is redefined by each window class.
         *
         */
        virtual void FillWindow();



        /**
         * Window data
         */
        Dvector mWindow;

    private:



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

#endif // __BASEWINDOW_HPP
