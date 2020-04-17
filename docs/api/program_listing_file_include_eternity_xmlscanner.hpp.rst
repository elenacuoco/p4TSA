
.. _program_listing_file_include_eternity_xmlscanner.hpp:

Program Listing for File xmlscanner.hpp
=======================================

|exhale_lsh| :ref:`Return to documentation for file <file_include_eternity_xmlscanner.hpp>` (``include/eternity/xmlscanner.hpp``)

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
   
   #ifndef XMLSCANNER_HPP
   #define XMLSCANNER_HPP
   
   #include <math.h>
   #include <stdlib.h>
   
   #include <vector>
   #include <map>
   #include <algorithm>
   #include <fstream>
   #include <string>
   #include <iostream>
   
   namespace eternity {
   
       class node {
       public:
           std::string name;
           std::map<std::string, std::string> attributes;
   
           std::string value;
           std::vector<node*> childs;
           node* parent;
   
           void dump(size_t indent);
           void intent(size_t pos);
           void done();
           node* foundChild(std::string tagName, size_t pos);
   
           node();
           node(std::string _name);
           node(node* parentnode);
   
   
           virtual ~node();
       };
   
       class xml_scanner {
       private:
           std::fstream stream;
           node rootnode;
           node* currnode;
   
           std::string currAttribute;
   
           enum context_mode {
               value, tagname, comment, doctype, attr, attrvalue, closebracket, closetag, endfile
           } context;
   
       public:
           xml_scanner(void);
           ~xml_scanner(void);
   
           void close();
           node* scan_file(std::string filePath);
   
       protected:
           char read_next_char(void);
           char read_next_non_space_char(void);
           std::string read_literal(void);
           std::string read_word(void);
           void read_value(void);
           void read_tag_name(void);
           void read_close_tag(void);
           void read_attributes(void);
           void read_attribute_value(void);
           void close_bracket(void);
           void read_comment(void);
           void read_doc_type(void);
   
       };
   
   };
   
   #endif //XMLSCANNER_HPP
