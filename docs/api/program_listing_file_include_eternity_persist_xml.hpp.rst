
.. _program_listing_file_include_eternity_persist_xml.hpp:

Program Listing for File persist_xml.hpp
========================================

|exhale_lsh| :ref:`Return to documentation for file <file_include_eternity_persist_xml.hpp>` (``include/eternity/persist_xml.hpp``)

.. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS

.. code-block:: none

   // Eternity persistence system
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
   
   #ifndef PERSIST_XML_HPP
   #define PERSIST_XML_HPP
   
   #include "persist.hpp"
   
   #include "xmlscanner.hpp"
   
   #include <deque>
   
   namespace eternity {
   
       using namespace std;
   
       class xml_archive : public archive {
       public:
   
           xml_archive() {
               done();
           }
   
           ~xml_archive() {
               done();
           }
   
           void open(std::string file_name, opening_mode mode);
   
           void init(std::string file_name, bool loading);
   
           void close() {
               return done();
           }
   
           void done() {
               archive::init();
   
               m_pCurElement = NULL;
               m_nTab = 0;
               m_vPointerstored.clear();
   
               if (m_oOut.is_open()) {
                   m_oOut << "</archive>" << endl;
                   m_oOut.close();
               }
   
               m_oParser.close();
   
               if (m_dBranches.size() != 0) throw new eternity::exception("enter_branch()/leave_current_branch() or make_branch()/leave_current_branch() mismatch");
   
           }
   
           void formatting();
   
           std::string read(std::string key, int pos);
   
           void read(std::string key, std::string &value, int pos);
   
           void read(std::string key, int &value, int pos);
   
           void read(std::string key, unsigned int &value, int pos);
   
           void read(std::string key, float &value, int pos);
   
           void read(std::string key, double &value, int pos);
   
           template <class T>
           void write(std::string key, T value);
   
           template<class t> t* get_object(std::string key, t** ppObj, int pos);
   
           template <class t> t* put_object(std::string key, t* pObj);
   
           template<class t> void get_stack_object(std::string key, t& Obj, int pos);
   
           template <class t> void put_stack_object(std::string key, t& Obj);
   
           void make_branch(std::string name, std::map<std::string, std::string> attributes);
   
           std::map<std::string, std::string> enter_branch(std::string name, size_t pos);
   
           void leave_current_branch();
   
       protected:
           xml_scanner m_oParser;
           std::ofstream m_oOut;
           size_t m_nTab;
           node* m_pCurElement;
           deque<node*> m_dBranches;
   
       };
   
       template <class T>
       void xml_archive::write(std::string key, T value) {
           if (is_loading()) throw eternity::exception("write attempt on an archive open for loading.");
           formatting();
           m_oOut << "<" << key << ">";
           m_oOut << value;
           m_oOut << "</" << key << ">" << endl;
       }
   
   
       template<class t>
       t* xml_archive::get_object(std::string key, t** ppObj, int pos) {
           std::string cls_name;
           *ppObj = NULL;
           node* m_pPrevElement;
   
           //Save current XML element before move to the next one
           m_pPrevElement = m_pCurElement;
           m_pCurElement = m_pCurElement->foundChild(key, pos);
   
           cls_name = m_pCurElement->attributes["class"];
           //cls_name=read("Name", 0) ;
   
           //Template use <> to pass argument but XML use the
           //same symbols to open/close tags: we have to change
           //them before use this kind of persistence      
           replace(cls_name.begin(), cls_name.end(), '(', '<');
           replace(cls_name.begin(), cls_name.end(), ')', '>');
   
           //RTTI return the class name with the string 
           //"class " before: so if cls_name.length()>5
           //it is a valid name. Otherwise it is a pointer 
           //to an object loaded yet.
           if (!cls_name.empty()) {
               create(cls_name, ppObj);
   
               if (NULL != (*ppObj)) {
                   m_vPointerstored.push_back(*ppObj);
                   (*ppObj)->xml_serialize(*this);
               }
           } else {
               int pos = atoi(m_pCurElement->attributes["position"].c_str());
               //read("Position", pos, 0);
   
               if (pos>-1) *ppObj = static_cast<t*> (m_vPointerstored[pos]);
           }
   
           //Restore parent XML element
           m_pCurElement = m_pPrevElement;
           return *ppObj;
       }
   
   
       template <class t>
       t* xml_archive::put_object(std::string key, t* pObj) {
           int pos = put_pointer(pObj);
   
           if (pos == -1) {
               //New Object, we have to full serialize it          
               std::string buf = get_conventional_name(typeid (*pObj).name());
               if (buf.empty()) buf = typeid (*pObj).name();
   
               //Template use <> to pass argument but XML use the
               //same symbols to open/close tags: we have to change
               //them before use this kind of persistence      
               replace(buf.begin(), buf.end(), '<', '(');
               replace(buf.begin(), buf.end(), '>', ')');
   
               formatting();
               m_oOut << "<" << key << " class=\"" << buf << "\">" << endl;
   
               m_nTab++;
   
               //std::string key="Name";
               //write(key, buf);
   
               pObj->xml_serialize(*this);
               m_nTab--;
               formatting();
               m_oOut << "</" << key << ">" << endl;
           } else {
               //Object in list, yet. Only store position
               std::string buf = "NULL";
   
               m_oOut << "<" << key << " position=\"" << pos << "\" />" << endl;
               m_nTab++;
   
               //std::string key="Name";
               //write(key, buf);
   
               //buf="Position";
               //write(buf, pos);
   
               m_nTab--;
               //m_oOut << "</" << key << ">" << endl;
           }
           return pObj;
       }
   
   
       template<class t>
       void xml_archive::get_stack_object(std::string key, t& Obj, int pos) {
           node* m_pPrevElement;
   
           //Save current XML element before move to the next one
           m_pPrevElement = m_pCurElement;
           m_pCurElement = m_pCurElement->foundChild(key, pos);
   
           Obj.xml_serialize(*this);
   
   
           //Restore parent XML element
           m_pCurElement = m_pPrevElement;
   
       }
   
   
       template <class t>
       void xml_archive::put_stack_object(std::string key, t& Obj) {
           formatting();
           m_oOut << "<" << key << ">" << endl;
   
           m_nTab++;
           Obj.xml_serialize(*this);
           m_nTab--;
           formatting();
           m_oOut << "</" << key << ">" << endl;
   
   
       }
   
   }
   #endif // PERSIST_XML_HPP
