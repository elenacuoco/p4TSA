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

#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP

#include "persist.hpp"
#include "persist_xml.hpp"

#include "xmlscanner.hpp"

//#include <iostream>
//#include <iomanip>
#include <sstream>


namespace eternity {

    /** Manage persistence of primitive containers (e.g. collections of int, float, double. etc.)
            This struct is not intended to direct use but must be passed as template parameter of
            sequence struct.
     */
    struct primitives {
        template<class T, class Archive>
        void xml_write(Archive& archive, std::string key, T& x);

        template< class ValueType, class Archive>
        void xml_read(Archive& archive, std::string key, /*out*/ValueType* var, size_t pos);

        template<class T, class Archive>
        void write(Archive& archive, T& x);

        template< class ValueType, class Archive>
        void read(Archive& archive, /*out*/ValueType* var);
    };

    template<class T, class Archive>
    void primitives::xml_write(Archive& archive, std::string key, T& x) {
        archive.write(key, x);
    }

    template< class ValueType, class Archive>
    void primitives::xml_read(Archive& archive, std::string key, /*out*/ValueType* var, size_t pos) {
        archive.read(key, *var, (int) pos);
    }

    template<class T, class Archive>
    void primitives::write(Archive& archive, T& x) {
        archive << x;
    }

    template< class ValueType, class Archive>
    void primitives::read(Archive& archive, /*out*/ValueType* var) {
        archive >> *var;
    }

    /** Manage persistence of object containers (e.g. collections of stack allocated objects)
            This struct is not intended to direct use but must be passed as template parameter of
            sequence struct.
     */
    struct objects {
        template<class T, class Archive>
        void xml_write(Archive& archive, std::string key, T& x);

        template< class ValueType, class Archive>
        void xml_read(Archive& archive, std::string key, /*out*/ValueType* var, size_t pos);

        template<class T, class Archive>
        void write(Archive& archive, T& x);

        template< class ValueType, class Archive>
        void read(Archive& archive, /*out*/ValueType* var);
    };

    template<class T, class Archive>
    void objects::xml_write(Archive& archive, std::string key, T& x) {
        archive.put_stack_object(key, x);
    }

    template< class ValueType, class Archive>
    void objects::xml_read(Archive& archive, std::string key, /*out*/ValueType* var, size_t pos) {
        archive.get_stack_object(key, *var, (int) pos);
    }

    template<class T, class Archive>
    void objects::write(Archive& archive, T& x) {
        x.serialize(archive);
    }

    template< class ValueType, class Archive>
    void objects::read(Archive& archive, /*out*/ValueType* var) {
        (*var).serialize(archive);
    }

    /** Manage persistence of object pointers containers (e.g. collections of heap allocated objects)
            This struct is not intended to direct use but must be passed as template parameter of
            sequence struct.
     */
    struct pointers {
        template<class T, class Archive>
        void xml_write(Archive& archive, std::string key, T& x);

        template< class ValueType, class Archive>
        void xml_read(Archive& archive, std::string key, /*out*/ValueType* var, size_t pos);

        template<class T, class Archive>
        void write(Archive& archive, T& x);

        template< class ValueType, class Archive>
        void read(Archive& archive, /*out*/ValueType* var);
    };

    template<class T, class Archive>
    void pointers::xml_write(Archive& archive, std::string key, T& x) {
        archive.put_object(key, x);
    }

    template< class ValueType, class Archive>
    void pointers::xml_read(Archive& archive, std::string key, /*out*/ValueType* var, size_t pos) {
        archive.get_object(key, var, (int) pos);
    }

    template<class T, class Archive>
    void pointers::write(Archive& archive, T& x) {
        archive.put_object(x);
    }

    template< class ValueType, class Archive>
    void pointers::read(Archive& archive, /*out*/ValueType* var) {
        archive.get_object(var);
    }

    /** Manage persistence of sequence containers (e.g. vector, list).
            Use template parameter to specify contents type (e.g. primitives, objects or pointers).
            This struct is not intended to direct use but must be passed as template parameter of
            xml_serialize() or serialize() algorithms.
     */
    template <class CollectionContent>
    struct sequence {
        template <class InputIterator, class Archive>
        size_t xml_write(InputIterator first, InputIterator last, Archive& archive);

        template <class Container, class InputIterator, class Archive>
        void xml_read(Container& container, InputIterator insert, size_t len, Archive& archive);

        template <class InputIterator, class Archive>
        size_t write(InputIterator first, InputIterator last, Archive& archive);

        template <class Container, class InputIterator, class Archive>
        void read(Container& container, InputIterator insert, size_t len, Archive& archive);
    };

    template <class CollectionContent> template< class InputIterator, class Archive>
    size_t sequence<CollectionContent>::xml_write(InputIterator first, InputIterator last, Archive& archive) {
        CollectionContent content;
        size_t len = 0;
        for (; first != last; ++first) {
            ++len;
            content.xml_write(archive, "item", (*first));
        }

        return len;
    }

    template <class CollectionContent> template <class Container, class InputIterator, class Archive>
    void sequence<CollectionContent>::xml_read(Container& container, InputIterator insert, size_t len, Archive& archive) {
        CollectionContent content;
        insert_iterator<Container > ii(container, insert);
        typename iterator_traits< InputIterator >::value_type var;

        for (size_t pos = 0; pos < len; ++pos) {
            content.xml_read(archive, "item", &var, pos);
            *ii++ = var;
        }
    }

    template <class CollectionContent> template< class InputIterator, class Archive>
    size_t sequence<CollectionContent>::write(InputIterator first, InputIterator last, Archive& archive) {
        CollectionContent content;
        size_t len = 0;
        for (; first != last; ++first) {
            ++len;
            content.write(archive, (*first));
        }

        return len;
    }

    template <class CollectionContent> template <class Container, class InputIterator, class Archive>
    void sequence<CollectionContent>::read(Container& container, InputIterator insert, size_t len, Archive& archive) {
        CollectionContent content;
        insert_iterator<Container > ii(container, insert);
        typename iterator_traits< InputIterator >::value_type var;

        for (size_t pos = 0; pos < len; ++pos) {
            content.read(archive, &var);
            *ii++ = var;
        }
    }

    /** Manage persistence of associtative containers (e.g. map or set).
            Use template parameter to specify contents type of key (e.g. primitives, objects or pointers)
            and the content type of data (again one from primitives, objects or pointers).
            This struct is not intended to direct use but must be passed as template parameter of
            xml_serialize() or serialize() algorithms.
     */
    template <class FirstContent, class SecondContent>
    struct association {
        template <class InputIterator, class Archive>
        size_t xml_write(InputIterator first, InputIterator last, Archive& archive);

        template <class Container, class InputIterator, class Archive>
        void xml_read(Container& container, InputIterator insert, size_t len, Archive& archive);

        template <class InputIterator, class Archive>
        size_t write(InputIterator first, InputIterator last, Archive& archive);

        template <class Container, class InputIterator, class Archive>
        void read(Container& container, InputIterator insert, size_t len, Archive& archive);
    };

    template <class FirstContent, class SecondContent> template <class InputIterator, class Archive>
    size_t association<FirstContent, SecondContent>::xml_write(InputIterator first, InputIterator last, Archive& archive) {
        FirstContent first_content;
        SecondContent second_content;
        size_t len = 0;
        for (; first != last; ++first) {
            ++len;
            first_content.xml_write(archive, "first", (*first).first);
            second_content.xml_write(archive, "second", (*first).second);
        }

        return len;
    }

    template <class FirstContent, class SecondContent> template <class Container, class InputIterator, class Archive>
    void association<FirstContent, SecondContent>::xml_read(Container& container, InputIterator insert, size_t len, Archive& archive) {
        FirstContent first_content;
        SecondContent second_content;

        insert_iterator<Container > ii(container, insert);
        typename Container::key_type first;
        typename iterator_traits< InputIterator >::value_type::second_type second;

        for (size_t pos = 0; pos < len; ++pos) {
            first_content.xml_read(archive, "first", &first, pos);
            second_content.xml_read(archive, "second", &second, pos);

            typename iterator_traits< InputIterator >::value_type my_pair(first, second);

            *ii++ = my_pair;
        }
    }

    template <class FirstContent, class SecondContent> template <class InputIterator, class Archive>
    size_t association<FirstContent, SecondContent>::write(InputIterator first, InputIterator last, Archive& archive) {
        FirstContent first_content;
        SecondContent second_content;
        size_t len = 0;
        for (; first != last; ++first) {
            ++len;
            first_content.write(archive, (*first).first);
            second_content.write(archive, (*first).second);
        }

        return len;
    }

    template <class FirstContent, class SecondContent> template <class Container, class InputIterator, class Archive>
    void association<FirstContent, SecondContent>::read(Container& container, InputIterator insert, size_t len, Archive& archive) {
        FirstContent first_content;
        SecondContent second_content;

        insert_iterator<Container > ii(container, insert);
        typename Container::key_type first;
        typename iterator_traits< InputIterator >::value_type::second_type second;

        for (size_t pos = 0; pos < len; ++pos) {
            first_content.read(archive, &first);
            second_content.read(archive, &second);

            typename iterator_traits< InputIterator >::value_type my_pair(first, second);

            *ii++ = my_pair;
        }
    }

    /** Pass to this function the container to persist with informtion about
        it's nature (sequence or associative) and the type of items collected ( primitives,
            objects or pointers).
     */

    template <class InputIterator, class CollectionCategory>
    void xml_write(CollectionCategory, InputIterator first, InputIterator last, xml_archive& archive, std::string label) {
        map<string, string> attr;
        CollectionCategory category;

        if (archive.is_loading()) throw new eternity::exception("called xml_serialize 4 params overload with a storing archive");

        size_t size = distance(first, last);

        ostringstream os;
        os << (unsigned int) size;
        attr["size"] = string(os.str());
        //os.str("");  // delete buffer

        archive.make_branch(label, attr);
        category.xml_write(first, last, archive);

        archive.leave_current_branch();

    };

    template <class Container, class InputIterator, class CollectionCategory>
    void xml_read(CollectionCategory, Container& container, InputIterator inserter, xml_archive& archive, std::string label) {
        map<string, string> attr;
        CollectionCategory category;
        size_t len;

        if (archive.is_storing()) throw new eternity::exception("called xml_serialize 3 params overload with a storing archive");

        attr = archive.enter_branch(label, 0);

        if (attr["size"].empty()) throw new eternity::exception("missing size attribute for node " + label);
        len = atoi(attr["size"].c_str());

        //archive.read("size",len,0); 
        category.xml_read(container, inserter, len, archive);
        archive.leave_current_branch();

    };

    template <class InputIterator, class CollectionCategory>
    void binary_write(CollectionCategory, InputIterator first, InputIterator last, bin_archive& archive) {
        map<string, string> attr;
        CollectionCategory category;

        if (archive.is_loading()) throw new eternity::exception("called xml_serialize 4 params overload with a storing archive");

        size_t size = distance(first, last);

        archive << size;

        category.write(first, last, archive);

    };

    template <class Container, class InputIterator, class CollectionCategory>
    void binary_read(CollectionCategory, Container& container, InputIterator inserter, bin_archive& archive) {
        map<string, string> attr;
        CollectionCategory category;
        size_t len;

        if (archive.is_storing()) throw new eternity::exception("called xml_serialize 3 params overload with a storing archive");

        archive >> len;

        category.read(container, inserter, len, archive);

    };


}
#endif // ALGORITHMS
