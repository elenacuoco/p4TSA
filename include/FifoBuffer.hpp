

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
 * @file   FifoBuffer.hpp
 * @author Giancarlo Cella <giancarlo.cella@pi.infn.it>
 * @date   Sat Nov 13 17:21:06 2004
 * 
 * @brief  Band limited interpolation
 */
#ifndef __FIFOBUFFER_HPP
#define __FIFOBUFFER_HPP

/**
 * @name System includes
 */
//@{
#include <queue>
#include <deque>

//@}

/**
 * @name Project includes
 */
//@{
#include <eternity.hpp>
#include <tsaTypes.hpp>
#include <tsaSerialize.hpp>
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
     * @brief Band limited interpolation.
     *
     * 
     */
    class FifoBuffer {
    public:

        /** 
         * Constructor.
         * 
         * @param channels number of channels
         *
         */
        FifoBuffer(unsigned int channels);


        /**
         * Copy constructor
         *
         * @param from The instance that must be copied
         */
        FifoBuffer(const FifoBuffer& from);

        /**
         * Destructor
         */
        ~FifoBuffer();

        /**
         * Assignement operator
         * 
         * @param from The instance to be assigned from
         *
         * @return a reference to a new object
         */
        FifoBuffer& operator=(const FifoBuffer& from);


        /** 
         * @name User interface
         */
        //@{



        //@}


        /**
         * @name Operations
         */
        //@{



        /** 
         * Insert in the back of the buffer n data contained in a matrix, starting from a given
         * offset. If n = 0 (default) all the data starting from the offset are copied.
         * 
         * @param data the matrix containing the data that must be inserted in the buffer
         * @param n the number of data to insert
         * @param offset the offset of the data to insert
         */
        void AddPoints(Dmatrix& data, double scale, int n = 0, int offset = 0);

        /** 
         * Insert in the back of the buffer a single data contained in a vector
         * 
         * @param data the vector containing the data that must be inserted in the buffer
         * @param scale the scale of the data
         */
        void AddPoint(Dvector& data, double scale);

        /** 
         * Insert in the back of the buffer a single uninitialized data
         * 
         */
        void AddPoint();

        /** 
         * Access to the last inserted data
         * 
         * @param i the index inside the last inserted data
         * 
         * @return reference to the last inserted data
         */
        inline double& Back(unsigned int i) {
            return (*(mBuffer.back()))(i);
        }


        /** 
         * Delete some data from the front of the buffer.
         * 
         * @param n number of data to delete
         */
        void DelPoints(int n);

        /** 
         * Get the present size of the buffer.
         * 
         * 
         * @return the size of the buffer
         */
        inline unsigned int Size() {
            return mBuffer.size();
        }

        /** 
         * Access to the buffer data.
         * 
         * @param r buffer row
         * @param c buffer column
         * 
         * @return the data
         */
        inline double& operator()(int r, int c) {
            return (*mBuffer[c])(r);
        }

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

        void xml_serialize(eternity::xml_archive& xml, const char* prefix) {
            char buffer[1024];

            if (xml.is_loading()) {
                unsigned int sz = 0;
                snprintf(buffer, 1024, "%s.sz", prefix);
                xml.read(buffer, sz, 0);
                snprintf(buffer, 1024, "%s.mChannels", prefix);
                xml.read(buffer, mChannels, 0);
                DelPoints(sz);
                for (unsigned int i = 0; i < sz; i++) {
                    snprintf(buffer, 1024, "%s.mBuffer.%d", prefix, i);
                    AddPoint();
                    DVECTOR_XML_SERIALIZE(*(mBuffer.back()), xml, buffer);
                }

            } else {
                unsigned int sz = mBuffer.size();
                snprintf(buffer, 1024, "%s.sz", prefix);
                xml.write(buffer, sz);
                snprintf(buffer, 1024, "%s.mChannels", prefix);
                xml.write(buffer, mChannels);
                for (unsigned int i = 0; i < sz; i++) {
                    snprintf(buffer, 1024, "%s.mBuffer.%d", prefix, i);
                    DVECTOR_XML_SERIALIZE(*mBuffer[i], xml, buffer);
                }
            }
        }



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




        unsigned int mChannels; /**< Number of channels to resample */
        std::queue<Dvector*> mRepository; /**< Repository for unused data points */
        std::deque<Dvector*> mBuffer; /**< Buffer for incoming data points */




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

#endif // __FIFOBUFFER_HPP
