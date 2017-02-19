/**
 *
 *   Copyright (C) 2004 by Elena Cuoco
 *   elena.cuoco@ego-gw.it
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
 * @file   NotchWidrow.hpp
 * @author Elena Cuoco <elena.cuoco@ego-gw.it>
 * @date   18 January 2005
 *
 * @brief  NotchWidrow perform the fit and the removal of lines, using the LMS method
 */
#ifndef __NOTCHWIDROW_HPP
#define __NOTCHWIDROW_HPP


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
#include <SeqView.hpp>
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
 * namespace
 */
namespace tsa {

    /**
     * @brief Implement the lines removal using adaptive notch filters, with the Least Mean Squared method, Widrow's like.
     */
    class NotchWidrow : public AlgoBase {
    public:

        /**
         * Constructor
         * @param FrequencyList is a matrix containing the list of frequency to be removed.
         */
        NotchWidrow(unsigned int channels, Dmatrix& FrequencyList, double C = 1.0);

        /**
         * Copy constructor
         *
         * @param from The instance that must be copied
         */
        NotchWidrow(const NotchWidrow& from);

        /**
         * Destructor
         */
        virtual ~NotchWidrow();


        /**
         *
         * @param InputData
         * @param CleanedData
         */
        void operator()(SeqViewDouble& InputData, SeqViewDouble& CleanedData);

        /**
         *
         * @param InputData
         * @param CleanedData
         * @param ReferenceSignal
         */
        void operator()(SeqViewDouble& InputData, SeqViewDouble& CleanedData, SeqViewDouble& ReferenceSignal);
        /**
         * Assignement operator
         *
         * @param from The instance to be assigned from
         *
         * @return a reference to a new object
         */
        NotchWidrow& operator=(const NotchWidrow& from);

        /**
         * @name Operations
         */
        //@{

        /**
         * @pre The starting frequency list and its parameters must be given
         *
         *
         *
         * @param Input Input Sequence of Data
         *
         * @param Output the cleaned sequence of data, with lines removed
         *
         * Declaration of execute operation
         */
        void execute(Dmatrix& Input, Dmatrix& Output);

        //@}

        /**
         * @name Getters
         */
        //@{

        double Getlstart() {
            return mlstart;
        }

        //@}

        /**
         * @name Setters
         */

        //@{

        //@}


    protected:

    private:
        Dmatrix mFrequencyList; // The Frequency list containing the frequency and the Q
        Dmatrix mWeight1;
        Dmatrix mWeight2;
        Dvector mX1;
        Dvector mX2;
        Dvector mCs;
        Dvector mSn;
        double mlstart;
        Dmatrix mRefSign;
        double mAmp;

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


} //end namespace

#endif // ___NOTCHWIDROW_HPP



