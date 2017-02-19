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

#ifndef XMLSCANNER_CPP
#define XMLSCANNER_CPP

#include "dynamic.hpp"
#include "xmlscanner.hpp"


using namespace std;

namespace eternity {

    node::node() : parent(NULL) {
    }

    node::node(std::string _name) : name(_name), parent(NULL) {
    }

    node::node(node* parentnode) {
        parent = parentnode;
        parent->childs.push_back(this);
    }

    node::~node() {
        done();
    }

    void node::dump(size_t indent) {
        intent(indent);
        std::cout << name << ":" << value << std::endl;

        std::map<std::string, std::string>::iterator iter = attributes.begin();
        while (iter != attributes.end()) {
            intent(indent);
            std::cout << (*iter).first << "=\"" << (*iter).second << "\"" << std::endl;
            iter++;
        }

        for (size_t i = 0; i < childs.size(); ++i) {
            childs[i]->dump(indent + 1);
        }
    }

    void node::intent(size_t pos) {
        for (size_t i = 0; i < pos; ++i) std::cout << " ";
    };

    void node::done() {
        for (size_t i = 0; i < childs.size(); ++i) {
            delete childs[i];
        }

        childs.clear();
    }

    node* node::foundChild(std::string tagName, size_t pos) {
        size_t found = 0;
        for (size_t i = 0; i < childs.size(); ++i) {
            if (childs[i]->name == tagName) {
                if (found++ == pos) return childs[i];
            }
        }

        return NULL;
    }

    xml_scanner::xml_scanner(void) {
        //stream.exceptions(std::ios::failbit | std::ios::eofbit | std::ios::badbit);
    }

    xml_scanner::~xml_scanner(void) {
        close();
    }

    /// close the archive file and release memory used.

    void xml_scanner::close() {
        rootnode.done();

    }

    char xml_scanner::read_next_char(void) {
        char buffer = 0;
        if (stream.is_open() && !stream.eof()) {
            stream.read(&buffer, 1);
        } else context = endfile;

        return buffer;
    }

    char xml_scanner::read_next_non_space_char(void) {
        char x;
        while ((x = read_next_char()) != 0 && (x == ' '));

        return x;
    }

    string xml_scanner::read_word() {
        string word;
        char x;

        //skip initial spaces
        while ((x = read_next_char()) != 0 && (x == ' ' || x == '\n' || x == '\r')) {
        }
        stream.unget();

        while ((x = read_next_char()) != 0 && (x != ' ' && x != '>' && x != '?' && x != '=' && x != '/')) {
            if (x != '\n' && x != '\r') word += x;
        }

        stream.unget();
        return word;
    }

    string xml_scanner::read_literal(void) {
        string word;
        char x;

        //skip initial spaces
        //while ( (x = read_next_char()) &&  x != '"') {}

        while ((x = read_next_char()) != 0 && x != '"') word += x;

        return word;
    }

    node* xml_scanner::scan_file(string filePath) {
        currnode = &rootnode;
        context = value;

        stream.open(filePath.c_str(), ios_base::in | std::ios_base::binary);

        if (!stream) {
            // Unable to open the file, so check error type
            // Get the state of the I/O State Flags
            unsigned int i = stream.rdstate();

            if (i & ios::eofbit)throw eternity::exception("EOF Encountered");
            else if (i & ios::failbit) throw eternity::exception("Non-fatal I/O Error occurred");
            else if (i & ios::badbit)
                // Set when 'catastrophic' errors occur in I/O operations
                // For example, when file does not exist. Note, however, that
                // this behaviour may not be totally platform independant.
                // That is, on my system (Borland 5.0 under Windows NT 4.0)
                // masking ios::badbit with the state flag gives true when the file
                // cannot be found; whether this
                // is definitely true on other systems, I cannot say
                throw eternity::exception("Fatal I/O Error occurred");

            // NOTE: Instead of using 'rdstate' etc..., you could use the
            //       following member functions
            //       * fin.eof()      ==> true if (state & ios::eofbit) true
            //       * fin.fail()     ==> true if (state & ios::failbit) true
            //       * fin.bad()      ==> true if (state & ios::badbit) true

        }

        while (context != endfile) {
            switch (context) {
                case (value): read_value();
                    break;
                case (tagname): read_tag_name();
                    break;
                case (closebracket): close_bracket();
                    break;
                case (closetag): read_close_tag();
                    break;
                case (attr): read_attributes();
                    break;
                case (attrvalue): read_attribute_value();
                    break;
                case (comment): read_comment();
                    break;
                case (doctype): read_doc_type();
                    break;
                default:
                    break;
            }
        }

        //debug only
        //rootnode.dump(0);

        stream.clear();

        if (stream.is_open()) {
            stream.close();
        }

        return &rootnode;
    }

    void xml_scanner::read_value(void) {
        while (true) {
            char x = read_next_char();

            // reach the end of file?
            if (context == endfile) return;

            // opening tag?
            if (x == '<') {
                x = read_next_non_space_char();

                // reach the end of file?
                if (context == endfile) return;

                //here looking for comment : if x=="--" ecc.)
                if (x == '/') {
                    //stream.unget();
                    context = closetag;
                    return;
                }
                if (x == '?') {
                    // here will mangage <? ... ?>
                    node* _node = new node(currnode);
                    currnode = _node;
                    context = tagname;
                    return;
                }
                if (x == '!') {
                    x = read_next_non_space_char();
                    // reach the end of file?
                    if (context == endfile) return;

                    if (x == '-') {
                        context = comment;
                        return;
                    } else {
                        context = doctype;
                        return;
                    }
                } else {
                    stream.unget();
                    node* _node = new node(currnode);
                    currnode = _node;
                    context = tagname;
                    return;
                }

            } else currnode->value += x;


        }
    }

    void xml_scanner::read_tag_name(void) {
        currnode->name = read_word();

        // reach the end of file?
        if (context == endfile) return;

        if (currnode->name.empty()) throw new eternity::exception("tag without name");

        context = attr;

    }

    void xml_scanner::read_attributes(void) {
        currAttribute = read_word();

        // reach the end of file?
        if (context == endfile) return;

        // closing tag?
        if (currAttribute.empty()) {
            context = closebracket;
            return;
        } else context = attrvalue;
    }

    void xml_scanner::close_bracket(void) {
        char x = read_next_non_space_char();

        // reach the end of file?
        if (context == endfile) return;

        // simply exit like <tag >
        if (x == '>') {
            context = value;
            return;
        }

        // closing tag with <tag ^/> ?
        if (x != '/' && x != '?') throw new eternity::exception("irregular closing bracket");

        x = read_next_non_space_char();

        // reach the end of file?
        if (context == endfile) return;

        if (x != '>') throw new eternity::exception("irregular closing bracket");
        context = value;
        currnode = currnode->parent;

    }

    void xml_scanner::read_attribute_value(void) {
        char x = read_next_non_space_char();

        // reach the end of file?
        if (context == endfile) return;

        // closing tag?
        if (x != '=') {
            stream.unget();
            currnode->attributes[currAttribute] = "";
            context = attr;
            return;
        }

        x = read_next_non_space_char();

        // reach the end of file?
        if (context == endfile) return;

        string value;

        if (x == '"') value = read_literal();
        else {
            stream.unget();
            value = read_word();
        };

        currnode->attributes[currAttribute] = value;

        context = attr;

    }

    void xml_scanner::read_close_tag(void) {
        string tag = read_word();

        // reach the end of file?
        if (context == endfile) return;

        if (tag != currnode->name) throw new eternity::exception("closing tag " + tag + " doesn't match");

        char x = read_next_non_space_char();

        // reach the end of file?
        if (context == endfile) return;


        // closing tag?
        if (x != '>') throw new eternity::exception("irregular closing of tag " + tag + " doesn't match");

        context = value;
        currnode = currnode->parent;

    }

    void xml_scanner::read_comment(void) {
        size_t step = 0;
        while (true) {
            char x = read_next_char();

            // reach the end of file?
            if (context == endfile) return;

            if (step == 0 && x == '-') ++step;
            else if (step == 1) {
                if (x == '-') ++step;
                else step = 0;
            } else if (step == 2) {
                if (x == '>') {
                    context = value;
                    return;
                } else step = 0;
            }

        }
    }

    void xml_scanner::read_doc_type(void) {
        while (true) {
            char x = read_next_char();

            // reach the end of file?
            if (context == endfile) return;

            if (x == '>') {
                context = value;
                return;
            }


        }
    }

};

#endif //XMLSCANNER_CPP

