//////////////////////////////////////////////////////////////////////
// Eternity persistence system
//////////////////////////////////////////////////////////////////////
// 
// 1999-2003 Nicola Santi.
//
// This software is released under the terms of Eternity Artistic 
// License. Please read the file eternity-licence to learn details. 
// 
// The above copyright notice and this permission notice shall be included
// in all copies or substantial portions of the Software.

// THIS PACKAGE IS PROVIDED "AS IS" AND WITHOUT ANY EXPRESS OR
// IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
// WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
//
// Except as contained in this notice, the name of Nicola Santi
// shall not be used in advertising or otherwise to promote the sale, 
// use or other dealings in this Software without prior written 
// authorization from Nicola Santi.
//////////////////////////////////////////////////////////////////////

#ifndef PERSIST_H
#define PERSIST_H

#include "dynamic.hpp"

#include <math.h>
#include <stdlib.h>

#include <vector>
#include <algorithm>
#include <fstream>



namespace eternity {

    class bin_archive;

    /** This class supply common services for all
        kind of persistence archives. The major one
        is the ability to stored doubled pointers only
        one time and so avoid circularity, broken links
        and lost spaces on hard disks.
     */
    class archive {
    protected:
        bool m_bloading;
        std::vector<void*> m_vPointerstored;

    public:

        enum opening_mode {
            load, store        };

        /// Simply the default constructor

        archive() : m_bloading(true) {
        }

        void init() {
            m_vPointerstored.clear();
            m_vPointerstored.push_back(NULL);
            m_bloading = true;
        }

        /** Verify that object is stored only
     once.
         */
        int put_pointer(void* object);

        /// Set the archive mode (loading or storing)

        bool set_loading(bool val) {
            return m_bloading = val;
        }
        /// Verify the archive is in loading mode

        bool is_loading() {
            return m_bloading;
        }
        /// Verify the archive is in storing mode

        bool is_storing() {
            return !m_bloading;
        }


    };

    /**
            Bin(ary)archive realize the persistence by serialization
        using a stream archive where to store in sequence all data
        in binary format.
     */
    class bin_archive : public archive {
    public:

        virtual ~bin_archive() {
        }

        /// write a buffer of a certain legnth n time in the archive
        virtual size_t write(const void *buffer, size_t size, size_t count) = 0;
        /// read a buffer of a certain legnth n time in the archive
        virtual size_t read(void *buffer, size_t size, size_t count) = 0;

        /** Template operator to put any type ( except string)
      of proprieties in the archive.
         */
        template <class T>
        bin_archive& operator<<(T& ogg) {
            if (is_loading()) throw eternity::exception("write attempt on an archive open for loading.");
            write(&ogg, sizeof (ogg), 1);
            return (*this);
        }

        /** Template operator to extract any type ( except string)
            of proprieties from the archive.
         */
        template <class T>
        bin_archive& operator>>(T& ogg) {
            if (!is_loading()) throw eternity::exception("read attempt on an archive open for storing.");
            read(&ogg, sizeof (ogg), 1);
            return (*this);
        }

        /// Put a string in the archive
        bin_archive& operator<<(std::string& str);


        /// Extract a string from the archive
        bin_archive& operator>>(std::string& str);

        /// Extract an object pointer from the archive

        template<class t>
        t* get_object(t** ppObj) {
            std::string cls_name;
            *ppObj = NULL;

            operator>>(cls_name);

            if ("NULL" != cls_name) {
                create(cls_name, ppObj);

                if (NULL != (*ppObj)) {
                    m_vPointerstored.push_back(*ppObj);
                    (*ppObj)->serialize(*this);
                }


            } else {
                int pos = 0;

                operator>>(pos);

                *ppObj = static_cast<t*> (m_vPointerstored[pos]);

            }

            return *ppObj;
        }

        /// Put an object pointer in the archive

        template <class t>
        t* put_object(t* pObj) {
            int pos = put_pointer(pObj);

            if (pos == -1) {
                //New Object, we have to full serialize it	
                std::string str = get_conventional_name(typeid (*pObj).name());
                if (str.empty()) str = typeid (*pObj).name();
                operator<<(str);
                pObj->serialize(*this);
            } else {
                //Object in list, yet. Only store position
                std::string str = "NULL";
                operator<<(str);
                operator<<(pos);
            }

            return pObj;
        }
    };

    /**
            Realize an binary archive using the common file
        like stream.
     */

    class file_archive : public bin_archive {
        std::fstream stream;
    public:

        file_archive() {
            stream.exceptions(std::ios::failbit | std::ios::eofbit | std::ios::badbit);
        }

        file_archive(std::string file_name, opening_mode mode);

        ~file_archive() {
            close();
        }

        /// close the archive file and release memory used.

        void close() {

            if (stream.is_open()) {
                stream.close();
            }

            archive::init();
        }

        /** initialize the file_archive using the file
      named file_name. If mode is load create
      the file. Anyway init update archive to
      begin persistence operations.
         */
        void open(std::string file_name, opening_mode mode);

        /// open the archive file and update this for the serialization
        void open(std::string sName, bool loading = true);

        virtual size_t write(const void *buffer, size_t size, size_t count);

        virtual size_t read(void *buffer, size_t size, size_t count);
    };


}
#endif // PERSIST_H
