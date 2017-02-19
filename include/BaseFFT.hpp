/**
 * @file   BaseFFT.hpp
 * @author Giancarlo Cella <giancarlo.cella@pi.infn.it>
 * @date   Sat Nov 13 17:21:06 2004
 *
 * @brief  Interface for BaseFFT
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
#ifndef __BASEFFT_HPP
#define __BASEFFT_HPP

/**
 * @name System includes
 **/
//@{
#include <stdio.h>
#include <boost/numeric/ublas/matrix.hpp>
#include <fftw3.h>
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
     * Planning modes. They describe the way in which the planning
     * is done. See the fftw documentation.
     **/
    enum FFTPlanningMode {
        ESTIMATE, //*< Simple heuristic, fast
        MEASURE, //*< More time consuming. Usually close to optimal.
        PATIENT, //*< More consuming than MEASURE
        EXHAUSTIVE //*< Very demanding
    };

    inline int FFTsize(int n) {
        return n / 2 + 1;
    }

    /**
     * @class BaseFFT
     * @brief Base class for various FFT
     *
     * 
     **/
    class BaseFFT : public AlgoBase {
    public:

        /**
         * Constructor
         *
         * @param size the size of the transform
         * @param mode specify the way in which plans are calculated
         * @param PreserveInput true if the input buffer must be preserved during the transform, false otherwise
         **/
        BaseFFT(int size, enum FFTPlanningMode mode, bool PreserveInput) {
            mPlan = NULL;
            mPlanNeedsUpdate = false;
            mLogicalSize = size;
            SetPlanningMode(mode);
            SetPreserveInput(PreserveInput);
        };

        /**
         * Copy constructor
         *
         * @param from The instance that must be copied
         **/
        BaseFFT(const BaseFFT& from) {
            mPlan = NULL;
            mPlanNeedsUpdate = false;
            mLogicalSize = from.mLogicalSize;
            mPlanningRigor = from.mPlanningRigor;
            mPlanningRestriction = from.mPlanningRestriction;
        };

        /**
         * Destructor
         **/
        virtual ~BaseFFT() {
            if (mPlan) {
                fftw_destroy_plan(mPlan);
            }
        };

        /**
         * @name Operations
         **/
        //@{

        /**
         * Save the actual wisdom for plan generation on a file
         *
         * @param filename the name of the file
         **/
        static void SaveWisdomOnFile(std::string filename) {
            FILE *out = fopen(filename.c_str(), "w");
            if (out == 0) {
                throw std::runtime_error("Can't open wisdom file for saving");
            }
            fftw_export_wisdom_to_file(out);
            fclose(out);
        }

        /**
         * Load the actual wisdom for plan generation from a file
         *
         * @param filename the name of the file
         **/
        static void LoadWisdomFromFile(std::string filename) {
            FILE *in = fopen(filename.c_str(), "r");
            if (in == 0) {
                throw;
            }
            if (fftw_import_wisdom_from_file(in) == 0) {
                throw std::runtime_error("Can't open wisdom file for reading");
            }
            fclose(in);
        }

        /**
         * Forget wisdom
         */
        static void ForgetWisdom() {
            fftw_forget_wisdom();
        }

        /**
         * Make a new plan, with the current parameters.
         **/
        virtual void MakePlan() = 0;


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

        /**
         * Set the way in which the plan is constructed. No new plan is generated.
         *
         * @param mode the requested planning mode.
         **/
        void SetPlanningMode(enum FFTPlanningMode mode) {
            unsigned int mPlanningRigorNew = FFTW_ESTIMATE;
            switch (mode) {
                case ESTIMATE:
                    mPlanningRigorNew = FFTW_ESTIMATE;
                    break;
                case MEASURE:
                    mPlanningRigorNew = FFTW_MEASURE;
                    break;
                case PATIENT:
                    mPlanningRigorNew = FFTW_PATIENT;
                    break;
                case EXHAUSTIVE:
                    mPlanningRigorNew = FFTW_EXHAUSTIVE;
                    break;
            }
            if (mPlanningRigorNew != mPlanningRigor) {
                mPlanningRigor = mPlanningRigorNew;
                mPlanNeedsUpdate = true;
            }
        };

        /**
         * Request that the input buffer is preserved during the transformation.
         * No new plan is generated.
         *
         * @param flag true (default) if input buffer must be preserved, false otherwise
         **/
        void SetPreserveInput(bool flag = true) {
            unsigned int mPlanningRestrictionNew;
            if (flag) {
                mPlanningRestrictionNew = FFTW_PRESERVE_INPUT;
            } else {
                mPlanningRestrictionNew = FFTW_DESTROY_INPUT;
            }
            if (mPlanningRestrictionNew != mPlanningRestriction) {
                mPlanningRestriction = mPlanningRestrictionNew;
                mPlanNeedsUpdate = true;
            }
        }



        //@}

    protected:


        /**
         * The current plan, or NULL if no plan is available
         **/
        fftw_plan mPlan;

        /**
         * Flag: a parameter is changed and plan needs to be updated
         **/
        bool mPlanNeedsUpdate;

        /**
         * The size of the current plan
         **/
        unsigned int mLogicalSize;

        /**
         * The planning mode flag
         **/
        unsigned int mPlanningRigor;

        /**
         * The planning restriction flag.
         **/
        unsigned int mPlanningRestriction;


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

#endif // __BASEFFT_HPP
