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
 * @file   TF2PSD.hpp
 * @author Giancarlo Cella <giancarlo.cella@pi.infn.it>
 * @date   Sat Nov 13 17:21:06 2004
 * 
 * @brief  Estimate the PSD of a transfer function TF
 */
#ifndef __TF2PSD_HPP
#define __TF2PSD_HPP

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
     *  Convert a transfer function to a PSD 
     * 
     */
    class TF2PSD : public AlgoBase {
    public:

        /**
         * Constructor
         */
        TF2PSD(bool squared = false) {
            mSquaredFlag = squared;
        };

        /**
         * Copy constructor
         *
         * @param from The instance that must be copied
         */
        TF2PSD(const TF2PSD& from) {
            mSquaredFlag = from.mSquaredFlag;
        };

        /**
         * Destructor
         */
        virtual ~TF2PSD() {

        };

        /**
         * Assignement operator
         * 
         * @param from The instance to be assigned from
         *
         * @return a reference to a new object
         */
        TF2PSD& operator=(const TF2PSD& from) {
            mSquaredFlag = from.mSquaredFlag;
            return *this;
        }

        /**
         * @name Operations
         */
        //@{

        /**
         * @brief Brief documentation for the execute method.
         *
         * Start of the long documentation for execute method.
         *
         * @pre A precondition
         * @post A postcondition
         * @exception An exception
         *
         * @param a parameter
         *
         * @return a returned value
         */
        void execute(Cmatrix& tf, Dmatrix& psd) throw (bad_matrix_size) {
            if (
                    (tf.size1() != psd.size1())
                    ||
                    (tf.size2() != psd.size2())) {

                throw bad_matrix_size("TF2PSD::execute");
            }

            if (mSquaredFlag) {

                for (unsigned int i = 0; i < psd.size1(); i++) {
                    for (unsigned int j = 0; j < psd.size2(); j++) {
                        psd(i, j) = 2.0 * (tf(i, j).real() * tf(i, j).real() + tf(i, j).imag() * tf(i, j).imag());
                    }
                }

            } else {

                for (unsigned int i = 0; i < psd.size1(); i++) {
                    for (unsigned int j = 0; j < psd.size2(); j++) {
                        psd(i, j) = abs(2.0 * tf(i, j));
                    }
                }
            }

        }

        //@}

        /**
         * @name Getters
         */
        //@{

        bool GetSquared() {
            return mSquaredFlag;
        };

        //@}

        /**
         * @name Setters
         */
        //@{

        void SetSquared(bool squared = true) {
            mSquaredFlag = squared;
        };

        //@}

    protected:

    private:

        bool mSquaredFlag;
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

#endif // __TF2PSD_HPP
