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
 * @file   RLSCanceler.hpp
 * @author Elena Cuoco <elena.cuoco@ego-gw.it>
 * @date   2005
 *
 * @brief  Implement the Recursive Least Squares wieghts estimation 
 */
#ifndef __RLSCANCELER_HPP
#define __RLSCANCELER_HPP


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
 * namespace
 */
namespace tsa {

    /**
     *
     */
    class RLSCanceler : public AlgoBase {
    public:

        /**
         * Constructor
         *
         * 
         * @param Order order of the filter
         * @param delta guessed inverse rms
         * @param lambda forgetting factor
         * @param Channels number of channels of the incoming data
         * @return 
         */
        RLSCanceler(unsigned int Order, double delta, double lambda, unsigned int Channels);

        /**
         * Copy constructor
         *
         * @param from The instance that must be copied
         */
        RLSCanceler(const RLSCanceler& from);

        /**
         * Destructor
         */
        virtual ~RLSCanceler();

        /**
         * Assignement operator
         *
         * @param from The instance to be assigned from
         *
         * @return a reference to a new object
         */
        RLSCanceler& operator=(const RLSCanceler& from);

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
         * @name Operations
         */
        //@{
        /**
         * 
         * @param Input input data
         * @param ReferenceSignal noise reference signal
         * @param Output cleaned data
         */
        void execute(Dmatrix& Input, Dmatrix& Output, Dmatrix& ReferenceSigna);

        /**
         * 
         * @param Input input data
         * @param Output whitened data
         */
        void execute(Dmatrix& Input, Dmatrix& Output);

        //@}

        /**
         * @name Getters
         */
        //@{

        /**
         * 
         * @return the last step
         */
        double Getlstart() {
            return mlstart;
        }

        /**
         * 
         * @param j index of the weights
         * @param channel channel to which the weights belong
         * @return yhe weights of the RLS filter
         */
        double GetWeights(unsigned int j, unsigned int channel) {
            return mWeights(channel, j);
        }

        //@}

        /**
         * @name Setters
         */
        //@{

        //@}


    protected:

    private:
        unsigned int mP; /**< order of the model */
        double mdelta; /**< guessed average 1.0/sigma*sigma */
        double mlambda; /**< forgetting factor */
        Dmatrix mWeights; /**< P weights for noise removal */
        Dmatrix mC; /**< Gain matrix */
        Dvector mX; /**< P-length data buffer */
        Dvector mM; /**< learning parameter */
        Dvector mG; /**< gain vector */
        double mlstart; /**< starting point for buffered inputs */
        double msigma; /**< estimation of sigma of the data */

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

#endif // ___RLSCANCELER_HPP
