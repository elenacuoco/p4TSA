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

#ifndef DYNAMIC_H
#define DYNAMIC_H

#include <stdio.h>
#include <typeinfo>
#include <string>

namespace eternity {

    /**
 Ifactory is the base abstract class design to manage in
 the same way all template classes factory<t>.
     */
    class Ifactory {
    public:

        virtual ~Ifactory() {
        };

        /** All instancied factory<t> are collect inside
an unique global list. m_pHead is the head of
that list.
         */
        /// The fist object in global factory<t> list
        static Ifactory *m_pHead;

        /** Each item in the gloabl list of factory<t>
            object has a pointer to the next item
            named m_pNext. The last element has a NULL
            value inside m_pNext.
         */
        /// The next item in global factory<t> list
        Ifactory *m_pNext;

        /** The signature of create method for derived classes.
         */
        virtual void* create(std::string& class_name) = 0;

        /** The signature of get_conventional_name method for derived classes.
         */
        virtual std::string get_conventional_name(std::string& compiler_name) = 0;
    };

    /** factory<t> is responsable for the creation
            of object derived by the class t at run-time.
     */
    template <class t>
    class factory : public Ifactory {
        /// An istance of the object to dynamic create
        std::string m_sConventionalName;

    public:
        /** The default constructor that add this
        to the gloab list of factory<t> object.
         */

        /// Default constructor
        factory();

        /// Constructor for cross compiler compatibility
        factory(std::string conventional_name);

        /// Remove this from the gloab list of factory<t> object.
        virtual ~factory();


        /** Return a pointer to a new istance of the class t (the only
        template parmeter of factory<t>) only if the string
        class_name is actually the name of class t.
        Otherwise return a NULL pointer
         */
        /// create an instance from class t if the same specified in class_name
        virtual void* create(std::string& class_name);

        /** Return the conventional name of class t if 
                typeid(t).name() match with compiler_name.
                Otherwise return an empty.
         */
        virtual std::string get_conventional_name(std::string& compiler_name);

    };

    template<class t>
    factory<t>::factory() {
        //We are the new m_pHead before the previous one
        m_pNext = m_pHead;
        m_pHead = this;

        // set compiler name 
        m_sConventionalName = typeid (t).name();
    }

    template<class t>
    factory<t>::factory(std::string conventional_name) : m_sConventionalName(conventional_name) {
        //We are the new m_pHead before the previous one
        m_pNext = m_pHead;
        m_pHead = this;
    }

    template<class t>
    void* factory<t>::create(std::string& class_name) {
        return (m_sConventionalName == class_name)
                ? (void*) (new t)
                : 0;
    }

    template<class t>
    std::string factory<t>::get_conventional_name(std::string& compiler_name) {
        return ( compiler_name == typeid (t).name())
                ? m_sConventionalName
                : std::string("");
    }

    template<class t>
    factory<t>::~factory() {
        Ifactory **ppNext = &Ifactory::m_pHead;

        for (; *ppNext; ppNext = &(*ppNext)->m_pNext) {
            if (*ppNext == this) {
                *ppNext = (*ppNext)->m_pNext;
                break;
            }
        }
    }

    /** This function return a pointer to an object
            that belong to the class specified by the
            string cls_name. If success put in *ppObj
            that pointer, otherwise put a NULL value
            in *ppObj.
     */
    template<class t>
    void create(std::string cls_name, t** ppObj) {
        Ifactory *pCurrent = Ifactory::m_pHead;

        //the follow line reinterpret several times
        //invalid null pointer so compilers could
        //segnal warining.
        for (; pCurrent; pCurrent = pCurrent->m_pNext)
            if ((*ppObj = reinterpret_cast<t*> (pCurrent->create(cls_name))) != NULL) break;

    }

    /** Search over all register facotry to found
            the conventional name of a class that the compiler
            identified with compiler_name.
            Otherwise return an empty string.
     */
    std::string get_conventional_name(std::string compiler_name);

    class exception : public std::exception {
    protected:
        std::string m_swhat;
    public:

        exception(std::string swhat);

        exception(const exception& right)
        : m_swhat(right.what()) {
        }

        exception& operator=(const exception& right) {
            m_swhat = right.what();
            return *this;
        }

        virtual ~exception() throw ();
        virtual const char *what() const throw ();


    };





};
#endif // DYNAMIC_H

