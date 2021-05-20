/**
 *
 *   Copyright (C) 2004
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
 * @file   ARMAFilter.hpp
 * @date   Sat Nov 13 17:21:06 2004
 * 
 * @brief  Implement an ARMA filter
 */
#ifndef __ARMAFILTER_HPP
#define __ARMAFILTER_HPP

/**
 * @name System includes
 */
//@{


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

/** 
 * tsa namespace
 */
namespace tsa {

    /**  
     * @brief  Implement the   ARMA filtering
     *
     * This class implement a general ARMA filter. Given an input sequence x(n)
     * and an output sequence y(n) an ARMA filter is defined by the relation
     * (look at the signs definitions..)
     *
     * a(0) y(n) =  a(1) y(n-1) + ... + a(N) y(n-N) + b(0) x(n) + b(1) x(n-1) + .... + b(M) x(n-M)
     *
     * 
     */
    class ARMAFilter : public AlgoBase {
    public:
          
         
        

        
        /**
         * Constructor
         */
        ARMAFilter(unsigned int ARorder, unsigned int MAorder, double gain);
        
        

        /**
         * Destructor
         */
        virtual ~ARMAFilter();


        /**
         * @name Operations
         */
        //@{
        void SetARFilter( unsigned int i, double AR);
        void SetMAFilter( unsigned int i, double MA);    

        void operator()(SeqViewDouble& in, SeqViewDouble& out);

        /**
         *
         * 
         * @param in  Input Data
         * @param out Filtered Data
         * @return 
         */
        void execute(Dmatrix& in, Dmatrix& out, double scale);
        //@}

        /**
         * @name Getters
         *
         */
        //@{

        //@}

        /**
         * @name Setters
         *
         */
        //@{

       
       
        //@}


    protected:

    private:

        LDvector mAR;
        LDvector mMA;
        long double mGain;

        int mInPointer;
        int mOutPointer;
        LDvector mInBuffer;
        LDvector mOutBuffer;


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

#endif // __ARMAFILTER_HPP
