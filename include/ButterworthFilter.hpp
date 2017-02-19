/**
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
 * @file   Sin.hpp
 * @author Giancarlo Cella <giancarlo.cella@pi.infn.it>
 * @date   Sat Nov 13 17:21:06 2004
 * 
 * @brief  Interface for Sin
 */
#ifndef __BUTTERWORTHFILTER_HPP
#define __BUTTERWORTHFILTER_HPP

/**
 * @name System includes
 */
//@{
#include <fparser.hpp>


//@}

/**
 * @name Project includes
 */
//@{
#include <AlgoBase.hpp>

//@}

/**
 * @name Local includes
 */
//@{


//@}

/**
 * @name Forward references
 */
//@{


//@}


using namespace boost::numeric::ublas;

/** 
 * tsa namespace
 */
namespace tsa {

    /** 
     *  A generator of random normal numbers.
     * 
     */
    class ButterworthFilter : public AlgoBase {
    public:

        /**
         * Constructor
         *
         */
        ButterworthFilter(double freq, int order);

        /**
         * Destructor
         */
        virtual ~ButterworthFilter();

        /**
         * Write the filter on a view
         *
         */
        void operator()(SeqViewComplex& data);


        /**
         * Apply the filter on a view
         *
         */
        void operator()(SeqViewComplex& datain, SeqViewComplex& dataout);


        /**
         * @name Operations
         */
        //@{

        /**
         * 
         */
        void execute(Cmatrix &datain, Cmatrix &dataout, double fstart, double fsample, double scale);

        void execute(Cmatrix &datain, double fstart, double fsample, double scale);


        //@}

        /**
         * @name Getters
         */
        //@{


        //@}

        /**
         * @name Setters
         */
        //@{

        //@}


    protected:

    private:
        int mOrder;
        double mFreq;
        Cdouble *poles;

    };

    /**
     * @name Inline methods
     */
    //@{

    //@}


    /** 
     * @name External references
     */
    //@{

    //@}


} // end namespace tsa

#endif // __BUTTERWORTHFILTER_HPP
