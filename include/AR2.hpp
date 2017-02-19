/**
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
 * @file   AR2.hpp
 * @author Giancarlo Cella <giancarlo.cella@pi.infn.it>
 * @date   Sat Nov 13 17:21:06 2004
 * 
 * @brief  Implement an ARMA filter
 */
#ifndef __AR2_HPP
#define __AR2_HPP

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
     * 
     */
    class AR2 : public AlgoBase {
    public:

        /**
         * Constructor
         */
        AR2(const double f, const double gamma, const double h);


        /**
         * Destructor
         */
        virtual ~AR2();


        /**
         * @name Operations
         */
        //@{

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

        double mA;
        double mB;
        double mC;

        double mXm1;
        double mXm2;


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

#endif // __AR2_HPP
