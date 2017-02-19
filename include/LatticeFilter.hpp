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
 * @file   LatticeFilter.hpp
 * @author Elena Cuoco <elena.cuoco@ego-gw.it>
 * @date   2005
 *
 * @brief  Implement a filter in the lattice structure
 */
#ifndef __LATTICEFILTER_HPP
#define __LATTICEFILTER_HPP


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
#include <LatticeView.hpp>
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
 * namespace
 */
namespace tsa {

    /**
     *
     *@brief Implement the lattice filter
     *
     */
    class LatticeFilter : public AlgoBase {
    public:

        /**
         * Constructor
         *
         * @param LV is the view containg the parameters for the Lattice Filter
         * @return 
         */
        LatticeFilter(LatticeView& LV);

        /**
         * Constructor
         */
        LatticeFilter(Dvector& ParcorF, Dvector& ParcorB, Dmatrix& ErrF, Dmatrix& ErrB);

        /**
         * Destructor
         */
        virtual ~LatticeFilter();

        void Load(const char *filename, const char *fmt = "txt") {
            eternity::xml_archive fa;
            fa.open(filename, eternity::archive::load);
            xml_serialize(fa, "");
            fa.close();
        }

        void Save(const char *filename, const char *fmt = "txt") {
            eternity::xml_archive fa;
            fa.open(filename, eternity::archive::store);
            xml_serialize(fa, "");
            fa.close();
        }

        void xml_serialize(eternity::xml_archive& xml, const char* p) {
            char buffer[1024];

            if (xml.is_loading()) {

                snprintf(buffer, 1024, "%s.mOrder", p);
                xml.read(buffer, mOrder, 0);
                snprintf(buffer, 1024, "%s.mParcorF", p);
                DVECTOR_XML_SERIALIZE(mParcorF, xml, buffer);
                snprintf(buffer, 1024, "%s.mParcorB", p);
                DVECTOR_XML_SERIALIZE(mParcorB, xml, buffer);
                snprintf(buffer, 1024, "%s.mErrF", p);
                DMATRIX_XML_SERIALIZE(mErrF, xml, buffer);
                snprintf(buffer, 1024, "%s.mErrB", p);
                DMATRIX_XML_SERIALIZE(mErrB, xml, buffer);
                snprintf(buffer, 1024, "%s.mStatus", p);
                xml.read(buffer, mStatus, 0);

            } else {

                snprintf(buffer, 1024, "%s.mOrder", p);
                xml.write(buffer, mOrder);
                snprintf(buffer, 1024, "%s.mParcorF", p);
                DVECTOR_XML_SERIALIZE(mParcorF, xml, buffer);
                snprintf(buffer, 1024, "%s.mParcorB", p);
                DVECTOR_XML_SERIALIZE(mParcorB, xml, buffer);
                snprintf(buffer, 1024, "%s.mErrF", p);
                DMATRIX_XML_SERIALIZE(mErrF, xml, buffer);
                snprintf(buffer, 1024, "%s.mErrB", p);
                DMATRIX_XML_SERIALIZE(mErrB, xml, buffer);
                snprintf(buffer, 1024, "%s.mStatus", p);
                xml.write(buffer, mStatus);



            }
        }



        /**
         * @name Operations
         */
        //@{

        /**
         * Declaration of execute operation
         *
         * @param InputData Matrix containing Time Series
         * @param WhitenedData Matrix containing the WhitenedData
         */
        void operator()(SeqViewDouble& InputData, SeqViewDouble& WhitenedData) {
            Dmatrix* in = InputData.GetData();
            Dmatrix* out = WhitenedData.GetData();

            if ((in->size1() != out->size1()) || (in->size2() != out->size2())) {
                out->resize(in->size1(), in->size2());
                LogWarning("LatticeFilter: resizing output view");
            }
            WhitenedData.SetStart(InputData.GetStart());
            WhitenedData.SetSampling(InputData.GetSampling());

            for (unsigned int r = 0; r < in->size1(); r++) {
                execute(row(*in, r), row(*out, r));
            }
        }


        /**
         * @brief Initialization function
         * @param LV lattice view
         */
        void init(LatticeView& LV);
        /**
         * @brief The execute method implemts the filter in the lattice form.
         *
         *
         * @pre
         * @post A postcondition
         * @exception An exception
         *
         * Declaration of execute operation
         * 
         * @param Input is the input vector of data
         * @param Output is the output  (whitened) data
         */
        void execute(matrix_row<Dmatrix> Input, matrix_row<Dmatrix> Output);

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
        unsigned int mOrder;
        Dvector mParcorF;
        Dvector mParcorB;
        Dmatrix mErrF;
        Dmatrix mErrB;
        int mStatus;




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

#endif // ___LATTICEFILTER_HPP

