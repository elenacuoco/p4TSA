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

#include "persist_xml.hpp"

namespace eternity {

    /** initialize and XML archive using the file
  named file_name. If mode is load create
  the file. Anyway init update archive to
  begin persistence operations.
     */
    void xml_archive::open(std::string file_name, opening_mode mode) {
        init(file_name, mode == load);
    }

    /** initialize and XML archive using the file
  named file_name. If loading is true create
  the file. Anyway init update archive to
  begin persistence operations.
      Deprecated: use open instead
     */
    void xml_archive::init(std::string file_name, bool loading) {
        done();
        if (loading) {
            //throw eternity::exception("opening XML archive " + file_name + " error");;
            m_pCurElement = m_oParser.scan_file(file_name);

            if (m_pCurElement == NULL) throw eternity::exception("opening XML archive " + file_name + " error");

            m_pCurElement = m_pCurElement->foundChild("archive", 0);

            if (m_pCurElement == NULL) throw eternity::exception("file " + file_name + " is not a valid eternity XML archive");

        } else {
            m_oOut.open(file_name.c_str());

            m_oOut << "<?xml version=\"1.0\"?>" << endl;
            m_oOut << "<!-- eternity persistence framework   -->" << endl;
            m_oOut << "<!-- Nicola Santi - www.winghands.it  -->" << endl;
            m_oOut << "<archive version=\"4.0\" sub=\"beta1\">" << endl;
        }

        set_loading(loading);
    }

    void xml_archive::formatting() {
        for (size_t i = 0; i < m_nTab; ++i) m_oOut << "\t";
    }

    /// read (and return) a string with label key at position pos

    std::string xml_archive::read(std::string key, int pos) {
        if (!is_loading()) throw eternity::exception("read attempt on an archive open for storing.");
        if (m_pCurElement) {
            //const SimpleXMLParser::Element& e = (*m_pCurElement)(key.c_str(), pos);
            //string tmp(e.GetValue());
            //return tmp;

            if (m_pCurElement->foundChild(key, pos) == NULL) throw eternity::exception("archive not compatible with class to load.");

            return m_pCurElement->foundChild(key, pos)->value;
            //return  std::string((*m_pCurElement)(key.c_str(), pos).GetValue());
        } else return "";
    }

    /// read (and put in value) a string with label key at position pos

    void xml_archive::read(std::string key, std::string &value, int pos) {
        value = read(key, pos);
    }

    /// read (and put in value) a int with label key at position pos

    void xml_archive::read(std::string key, int &value, int pos) {
        if (!is_loading()) throw eternity::exception("read attempt on an archive open for storing.");
        value = atoi(read(key, pos).c_str());
    }

    /// read (and put in value) a int with label key at position pos

    void xml_archive::read(std::string key, unsigned int &value, int pos) {
        if (!is_loading()) throw eternity::exception("read attempt on an archive open for storing.");
        value = atoi(read(key, pos).c_str());
    }

    /// read (and put in value) a float with label key at position pos

    void xml_archive::read(std::string key, float &value, int pos) {
        if (!is_loading()) throw eternity::exception("read attempt on an archive open for storing.");
        value = (float) atof(read(key, pos).c_str());
    }

    /// read (and put in value) a double with label key at position pos

    void xml_archive::read(std::string key, double &value, int pos) {
        if (!is_loading()) throw eternity::exception("read attempt on an archive open for storing.");
        value = atof(read(key, pos).c_str());
    }

    /// Create a node (e.g. <name attributes>) and set it as current one (enter branch)

    void xml_archive::make_branch(std::string name, std::map<std::string, std::string> attributes) {
        if (is_loading()) throw new eternity::exception("called make_branch on a loading archive");

        formatting();
        m_oOut << "<" << name;

        std::map<std::string, std::string>::iterator i = attributes.begin();

        for (; i != attributes.end(); ++i)
            m_oOut << " " << (*i).first << "=\"" << (*i).second << "\"";

        m_oOut << ">" << endl;

        m_nTab++;

        m_dBranches.push_front(new node(name));

    }

    /// Enter in the node with tag equals to name and return its attributes

    std::map<std::string, std::string> xml_archive::enter_branch(std::string name, size_t pos) {
        if (is_storing()) throw new eternity::exception("called enter_branch on a storing archive");

        node* m_pPrevElement = m_pCurElement;

        //Save current XML element before move to the next one
        m_pCurElement = m_pCurElement->foundChild(name, pos);

        m_dBranches.push_front(m_pPrevElement);

        return m_pCurElement->attributes;
    }

    /// Leaves current node and returns to its parent

    void xml_archive::leave_current_branch() {
        if (is_storing()) {
            if (m_dBranches.size() == 0) throw new eternity::exception("make_branch()/leave_current_branch() mismatch");
            m_nTab--;
            formatting();
            m_oOut << "</" << m_dBranches[0]->name << ">" << endl;
            delete m_dBranches[0];
            m_dBranches.pop_front();
        } else {
            if (m_dBranches.size() == 0) throw new eternity::exception("enter_branch()/leave_current_branch() mismatch");
            m_pCurElement = m_dBranches[0];
            m_dBranches.pop_front();
        }
    }


}









