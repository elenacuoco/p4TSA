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

#include "persist.hpp"

namespace eternity {

    /* move here to fix bcc32 Warning W8026 */
    int archive::put_pointer(void* object) {
        for (size_t i = 0; i < m_vPointerstored.size(); ++i) {
            if (m_vPointerstored[i] == object) return (int) i;
        }

        //There isn't inside list
        m_vPointerstored.push_back(object);

        return -1;
    }

    /// Put a string in the archive

    bin_archive& bin_archive::operator<<(std::string& str) {
        unsigned int len = static_cast<unsigned int> (str.length());
        write(&len, sizeof (len), 1);

        if (len > 0) {
            //write (&len, sizeof(len), 1);
            for (unsigned int i = 0; i < len; ++i) {
                char ch = str[i];
                write(&ch, sizeof (ch), 1);
            }
        }

        return (*this);
    }

    /// Extract a string from the archive

    bin_archive& bin_archive::operator>>(std::string& str) {
        unsigned int len = 0;
        operator>>(len);

        std::string str1(len, ' ');
        for (unsigned int i = 0; i < len; ++i) {
            char ch;
            read(&ch, sizeof (ch), 1);
            str1[i] = ch;
        }

        str = str1;
        return (*this);
    }

    file_archive::file_archive(std::string file_name, opening_mode mode) {
        open(file_name, mode == load);
    }

    size_t file_archive::write(const void *buffer, size_t size, size_t count) {
        //size_t written= fwrite( buffer, size, count, fp );
        size_t written = 0;
        for (size_t i = 0; i < count; ++i)
            stream.write((char*) buffer, (int) size);

        return written;
    }

    size_t file_archive::read(void *buffer, size_t size, size_t count) {
        //size_t ridden= fread( buffer, size, count, fp );
        size_t ridden = 0;
        for (size_t i = 0; i < count; ++i)
            stream.read((char*) buffer, (int) size);
        return ridden;
    }

    /** initialize the file_archive using the file
    named file_name. If mode is load create
    the file. Anyway init update archive to
    begin persistence operations.
     */
    void file_archive::open(std::string file_name, opening_mode mode) {
        open(file_name, mode == load);
    }

    /// open the archive file and update this for the serialization

    void file_archive::open(std::string sName, bool loading) {
        close();
        //fp=fopen(sName.c_str(), loading ? "r" : "w");
        stream.open(sName.c_str(), (loading ? std::ios_base::in : std::ios_base::out) | std::ios_base::binary);

        set_loading(loading);
    }


}









