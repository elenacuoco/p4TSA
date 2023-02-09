// File: std/exception.cpp
#include <exception>
#include <sstream> // __str__

#include <functional>
#include <pybind11/pybind11.h>
#include <string>

#ifndef BINDER_PYBIND11_TYPE_CASTER
	#define BINDER_PYBIND11_TYPE_CASTER
	PYBIND11_DECLARE_HOLDER_TYPE(T, std::shared_ptr<T>)
	PYBIND11_DECLARE_HOLDER_TYPE(T, T*)
	PYBIND11_MAKE_OPAQUE(std::shared_ptr<void>)
#endif

// std::exception file:bits/exception.h line:61
struct PyCallBack_std_exception : public std::exception {
	using std::exception::exception;

	const char * what() const throw() override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const std::exception *>(this), "what");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>();
			if (pybind11::detail::cast_is_temporary_value_reference<const char *>::value) {
				static pybind11::detail::override_caster_t<const char *> caster;
				return pybind11::detail::cast_ref<const char *>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<const char *>(std::move(o));
		}
		return exception::what();
	}
};

void bind_std_exception(std::function< pybind11::module &(std::string const &namespace_) > &M)
{
	{ // std::exception file:bits/exception.h line:61
		pybind11::class_<std::exception, std::shared_ptr<std::exception>, PyCallBack_std_exception> cl(M("std"), "exception", "");
		cl.def( pybind11::init( [](){ return new std::exception(); }, [](){ return new PyCallBack_std_exception(); } ) );
		cl.def( pybind11::init( [](PyCallBack_std_exception const &o){ return new PyCallBack_std_exception(o); } ) );
		cl.def( pybind11::init( [](std::exception const &o){ return new std::exception(o); } ) );
		cl.def("assign", (class std::exception & (std::exception::*)(const class std::exception &)) &std::exception::operator=, "C++: std::exception::operator=(const class std::exception &) --> class std::exception &", pybind11::return_value_policy::automatic, pybind11::arg(""));
		cl.def("what", (const char * (std::exception::*)() const) &std::exception::what, "C++: std::exception::what() const --> const char *", pybind11::return_value_policy::automatic);
	}
}


// File: std/stl_vector.cpp
#include <iterator>
#include <memory>
#include <sstream> // __str__
#include <string>
#include <vector>

#include <functional>
#include <pybind11/pybind11.h>
#include <string>

#ifndef BINDER_PYBIND11_TYPE_CASTER
	#define BINDER_PYBIND11_TYPE_CASTER
	PYBIND11_DECLARE_HOLDER_TYPE(T, std::shared_ptr<T>)
	PYBIND11_DECLARE_HOLDER_TYPE(T, T*)
	PYBIND11_MAKE_OPAQUE(std::shared_ptr<void>)
#endif

void bind_std_stl_vector(std::function< pybind11::module &(std::string const &namespace_) > &M)
{
	{ // std::vector file:bits/stl_vector.h line:423
		pybind11::class_<std::vector<std::string>, std::shared_ptr<std::vector<std::string>>> cl(M("std"), "vector_std_string_t", "");
		cl.def( pybind11::init( [](){ return new std::vector<std::string>(); } ) );
		cl.def( pybind11::init<const class std::allocator<std::string > &>(), pybind11::arg("__a") );

		cl.def( pybind11::init( [](unsigned long const & a0){ return new std::vector<std::string>(a0); } ), "doc" , pybind11::arg("__n"));
		cl.def( pybind11::init<unsigned long, const class std::allocator<std::string > &>(), pybind11::arg("__n"), pybind11::arg("__a") );

		cl.def( pybind11::init( [](unsigned long const & a0, const std::string & a1){ return new std::vector<std::string>(a0, a1); } ), "doc" , pybind11::arg("__n"), pybind11::arg("__value"));
		cl.def( pybind11::init<unsigned long, const std::string &, const class std::allocator<std::string > &>(), pybind11::arg("__n"), pybind11::arg("__value"), pybind11::arg("__a") );

		cl.def( pybind11::init( [](std::vector<std::string> const &o){ return new std::vector<std::string>(o); } ) );
		cl.def( pybind11::init<const class std::vector<std::string > &, const class std::allocator<std::string > &>(), pybind11::arg("__x"), pybind11::arg("__a") );

		cl.def("assign", (class std::vector<std::string > & (std::vector<std::string>::*)(const class std::vector<std::string > &)) &std::vector<std::string>::operator=, "C++: std::vector<std::string>::operator=(const class std::vector<std::string > &) --> class std::vector<std::string > &", pybind11::return_value_policy::automatic, pybind11::arg("__x"));
		cl.def("assign", (void (std::vector<std::string>::*)(unsigned long, const std::string &)) &std::vector<std::string>::assign, "C++: std::vector<std::string>::assign(unsigned long, const std::string &) --> void", pybind11::arg("__n"), pybind11::arg("__val"));
		cl.def("begin", (class __gnu_cxx::__normal_iterator<std::string *, class std::vector<std::string > > (std::vector<std::string>::*)()) &std::vector<std::string>::begin, "C++: std::vector<std::string>::begin() --> class __gnu_cxx::__normal_iterator<std::string *, class std::vector<std::string > >");
		cl.def("end", (class __gnu_cxx::__normal_iterator<std::string *, class std::vector<std::string > > (std::vector<std::string>::*)()) &std::vector<std::string>::end, "C++: std::vector<std::string>::end() --> class __gnu_cxx::__normal_iterator<std::string *, class std::vector<std::string > >");
		cl.def("cbegin", (class __gnu_cxx::__normal_iterator<const std::string *, class std::vector<std::string > > (std::vector<std::string>::*)() const) &std::vector<std::string>::cbegin, "C++: std::vector<std::string>::cbegin() const --> class __gnu_cxx::__normal_iterator<const std::string *, class std::vector<std::string > >");
		cl.def("cend", (class __gnu_cxx::__normal_iterator<const std::string *, class std::vector<std::string > > (std::vector<std::string>::*)() const) &std::vector<std::string>::cend, "C++: std::vector<std::string>::cend() const --> class __gnu_cxx::__normal_iterator<const std::string *, class std::vector<std::string > >");
		cl.def("size", (unsigned long (std::vector<std::string>::*)() const) &std::vector<std::string>::size, "C++: std::vector<std::string>::size() const --> unsigned long");
		cl.def("max_size", (unsigned long (std::vector<std::string>::*)() const) &std::vector<std::string>::max_size, "C++: std::vector<std::string>::max_size() const --> unsigned long");
		cl.def("resize", (void (std::vector<std::string>::*)(unsigned long)) &std::vector<std::string>::resize, "C++: std::vector<std::string>::resize(unsigned long) --> void", pybind11::arg("__new_size"));
		cl.def("resize", (void (std::vector<std::string>::*)(unsigned long, const std::string &)) &std::vector<std::string>::resize, "C++: std::vector<std::string>::resize(unsigned long, const std::string &) --> void", pybind11::arg("__new_size"), pybind11::arg("__x"));
		cl.def("shrink_to_fit", (void (std::vector<std::string>::*)()) &std::vector<std::string>::shrink_to_fit, "C++: std::vector<std::string>::shrink_to_fit() --> void");
		cl.def("capacity", (unsigned long (std::vector<std::string>::*)() const) &std::vector<std::string>::capacity, "C++: std::vector<std::string>::capacity() const --> unsigned long");
		cl.def("empty", (bool (std::vector<std::string>::*)() const) &std::vector<std::string>::empty, "C++: std::vector<std::string>::empty() const --> bool");
		cl.def("reserve", (void (std::vector<std::string>::*)(unsigned long)) &std::vector<std::string>::reserve, "C++: std::vector<std::string>::reserve(unsigned long) --> void", pybind11::arg("__n"));
		cl.def("__getitem__", (std::string & (std::vector<std::string>::*)(unsigned long)) &std::vector<std::string>::operator[], "C++: std::vector<std::string>::operator[](unsigned long) --> std::string &", pybind11::return_value_policy::automatic, pybind11::arg("__n"));
		cl.def("at", (std::string & (std::vector<std::string>::*)(unsigned long)) &std::vector<std::string>::at, "C++: std::vector<std::string>::at(unsigned long) --> std::string &", pybind11::return_value_policy::automatic, pybind11::arg("__n"));
		cl.def("front", (std::string & (std::vector<std::string>::*)()) &std::vector<std::string>::front, "C++: std::vector<std::string>::front() --> std::string &", pybind11::return_value_policy::automatic);
		cl.def("back", (std::string & (std::vector<std::string>::*)()) &std::vector<std::string>::back, "C++: std::vector<std::string>::back() --> std::string &", pybind11::return_value_policy::automatic);
		cl.def("data", (std::string * (std::vector<std::string>::*)()) &std::vector<std::string>::data, "C++: std::vector<std::string>::data() --> std::string *", pybind11::return_value_policy::automatic);
		cl.def("push_back", (void (std::vector<std::string>::*)(const std::string &)) &std::vector<std::string>::push_back, "C++: std::vector<std::string>::push_back(const std::string &) --> void", pybind11::arg("__x"));
		cl.def("pop_back", (void (std::vector<std::string>::*)()) &std::vector<std::string>::pop_back, "C++: std::vector<std::string>::pop_back() --> void");
		cl.def("insert", (class __gnu_cxx::__normal_iterator<std::string *, class std::vector<std::string > > (std::vector<std::string>::*)(class __gnu_cxx::__normal_iterator<const std::string *, class std::vector<std::string > >, const std::string &)) &std::vector<std::string>::insert, "C++: std::vector<std::string>::insert(class __gnu_cxx::__normal_iterator<const std::string *, class std::vector<std::string > >, const std::string &) --> class __gnu_cxx::__normal_iterator<std::string *, class std::vector<std::string > >", pybind11::arg("__position"), pybind11::arg("__x"));
		cl.def("insert", (class __gnu_cxx::__normal_iterator<std::string *, class std::vector<std::string > > (std::vector<std::string>::*)(class __gnu_cxx::__normal_iterator<const std::string *, class std::vector<std::string > >, unsigned long, const std::string &)) &std::vector<std::string>::insert, "C++: std::vector<std::string>::insert(class __gnu_cxx::__normal_iterator<const std::string *, class std::vector<std::string > >, unsigned long, const std::string &) --> class __gnu_cxx::__normal_iterator<std::string *, class std::vector<std::string > >", pybind11::arg("__position"), pybind11::arg("__n"), pybind11::arg("__x"));
		cl.def("erase", (class __gnu_cxx::__normal_iterator<std::string *, class std::vector<std::string > > (std::vector<std::string>::*)(class __gnu_cxx::__normal_iterator<const std::string *, class std::vector<std::string > >)) &std::vector<std::string>::erase, "C++: std::vector<std::string>::erase(class __gnu_cxx::__normal_iterator<const std::string *, class std::vector<std::string > >) --> class __gnu_cxx::__normal_iterator<std::string *, class std::vector<std::string > >", pybind11::arg("__position"));
		cl.def("erase", (class __gnu_cxx::__normal_iterator<std::string *, class std::vector<std::string > > (std::vector<std::string>::*)(class __gnu_cxx::__normal_iterator<const std::string *, class std::vector<std::string > >, class __gnu_cxx::__normal_iterator<const std::string *, class std::vector<std::string > >)) &std::vector<std::string>::erase, "C++: std::vector<std::string>::erase(class __gnu_cxx::__normal_iterator<const std::string *, class std::vector<std::string > >, class __gnu_cxx::__normal_iterator<const std::string *, class std::vector<std::string > >) --> class __gnu_cxx::__normal_iterator<std::string *, class std::vector<std::string > >", pybind11::arg("__first"), pybind11::arg("__last"));
		cl.def("swap", (void (std::vector<std::string>::*)(class std::vector<std::string > &)) &std::vector<std::string>::swap, "C++: std::vector<std::string>::swap(class std::vector<std::string > &) --> void", pybind11::arg("__x"));
		cl.def("clear", (void (std::vector<std::string>::*)()) &std::vector<std::string>::clear, "C++: std::vector<std::string>::clear() --> void");
	}
}


// File: std/stl_map.cpp
#include <functional>
#include <iterator>
#include <map>
#include <memory>
#include <sstream> // __str__
#include <string>
#include <utility>

#include <functional>
#include <pybind11/pybind11.h>
#include <string>

#ifndef BINDER_PYBIND11_TYPE_CASTER
	#define BINDER_PYBIND11_TYPE_CASTER
	PYBIND11_DECLARE_HOLDER_TYPE(T, std::shared_ptr<T>)
	PYBIND11_DECLARE_HOLDER_TYPE(T, T*)
	PYBIND11_MAKE_OPAQUE(std::shared_ptr<void>)
#endif

void bind_std_stl_map(std::function< pybind11::module &(std::string const &namespace_) > &M)
{
	{ // std::map file:bits/stl_map.h line:100
		pybind11::class_<std::map<std::string,std::string>, std::shared_ptr<std::map<std::string,std::string>>> cl(M("std"), "map_std_string_std_string_t", "");
		cl.def( pybind11::init( [](){ return new std::map<std::string,std::string>(); } ) );
		cl.def( pybind11::init( [](const struct std::less<std::string > & a0){ return new std::map<std::string,std::string>(a0); } ), "doc" , pybind11::arg("__comp"));
		cl.def( pybind11::init<const struct std::less<std::string > &, const class std::allocator<struct std::pair<const std::string, std::string > > &>(), pybind11::arg("__comp"), pybind11::arg("__a") );

		cl.def( pybind11::init( [](std::map<std::string,std::string> const &o){ return new std::map<std::string,std::string>(o); } ) );
		cl.def( pybind11::init<const class std::allocator<struct std::pair<const std::string, std::string > > &>(), pybind11::arg("__a") );

		cl.def( pybind11::init<const class std::map<std::string, std::string > &, const class std::allocator<struct std::pair<const std::string, std::string > > &>(), pybind11::arg("__m"), pybind11::arg("__a") );

		cl.def("assign", (class std::map<std::string, std::string > & (std::map<std::string,std::string>::*)(const class std::map<std::string, std::string > &)) &std::map<std::string, std::string>::operator=, "C++: std::map<std::string, std::string>::operator=(const class std::map<std::string, std::string > &) --> class std::map<std::string, std::string > &", pybind11::return_value_policy::automatic, pybind11::arg(""));
		cl.def("get_allocator", (class std::allocator<struct std::pair<const std::string, std::string > > (std::map<std::string,std::string>::*)() const) &std::map<std::string, std::string>::get_allocator, "C++: std::map<std::string, std::string>::get_allocator() const --> class std::allocator<struct std::pair<const std::string, std::string > >");
		cl.def("empty", (bool (std::map<std::string,std::string>::*)() const) &std::map<std::string, std::string>::empty, "C++: std::map<std::string, std::string>::empty() const --> bool");
		cl.def("size", (unsigned long (std::map<std::string,std::string>::*)() const) &std::map<std::string, std::string>::size, "C++: std::map<std::string, std::string>::size() const --> unsigned long");
		cl.def("max_size", (unsigned long (std::map<std::string,std::string>::*)() const) &std::map<std::string, std::string>::max_size, "C++: std::map<std::string, std::string>::max_size() const --> unsigned long");
		cl.def("__getitem__", (std::string & (std::map<std::string,std::string>::*)(const std::string &)) &std::map<std::string, std::string>::operator[], "C++: std::map<std::string, std::string>::operator[](const std::string &) --> std::string &", pybind11::return_value_policy::automatic, pybind11::arg("__k"));
		cl.def("at", (std::string & (std::map<std::string,std::string>::*)(const std::string &)) &std::map<std::string, std::string>::at, "C++: std::map<std::string, std::string>::at(const std::string &) --> std::string &", pybind11::return_value_policy::automatic, pybind11::arg("__k"));
		cl.def("insert", (struct std::pair<struct std::_Rb_tree_iterator<struct std::pair<const std::string, std::string > >, bool> (std::map<std::string,std::string>::*)(const struct std::pair<const std::string, std::string > &)) &std::map<std::string, std::string>::insert, "C++: std::map<std::string, std::string>::insert(const struct std::pair<const std::string, std::string > &) --> struct std::pair<struct std::_Rb_tree_iterator<struct std::pair<const std::string, std::string > >, bool>", pybind11::arg("__x"));
		cl.def("erase", (unsigned long (std::map<std::string,std::string>::*)(const std::string &)) &std::map<std::string, std::string>::erase, "C++: std::map<std::string, std::string>::erase(const std::string &) --> unsigned long", pybind11::arg("__x"));
		cl.def("swap", (void (std::map<std::string,std::string>::*)(class std::map<std::string, std::string > &)) &std::map<std::string, std::string>::swap, "C++: std::map<std::string, std::string>::swap(class std::map<std::string, std::string > &) --> void", pybind11::arg("__x"));
		cl.def("clear", (void (std::map<std::string,std::string>::*)()) &std::map<std::string, std::string>::clear, "C++: std::map<std::string, std::string>::clear() --> void");
		cl.def("key_comp", (struct std::less<std::string > (std::map<std::string,std::string>::*)() const) &std::map<std::string, std::string>::key_comp, "C++: std::map<std::string, std::string>::key_comp() const --> struct std::less<std::string >");
		cl.def("count", (unsigned long (std::map<std::string,std::string>::*)(const std::string &) const) &std::map<std::string, std::string>::count, "C++: std::map<std::string, std::string>::count(const std::string &) const --> unsigned long", pybind11::arg("__x"));
		cl.def("equal_range", (struct std::pair<struct std::_Rb_tree_iterator<struct std::pair<const std::string, std::string > >, struct std::_Rb_tree_iterator<struct std::pair<const std::string, std::string > > > (std::map<std::string,std::string>::*)(const std::string &)) &std::map<std::string, std::string>::equal_range, "C++: std::map<std::string, std::string>::equal_range(const std::string &) --> struct std::pair<struct std::_Rb_tree_iterator<struct std::pair<const std::string, std::string > >, struct std::_Rb_tree_iterator<struct std::pair<const std::string, std::string > > >", pybind11::arg("__x"));
	}
}


// File: std/stdexcept.cpp
#include <iterator>
#include <memory>
#include <sstream> // __str__
#include <stdexcept>
#include <string>

#include <functional>
#include <pybind11/pybind11.h>
#include <string>

#ifndef BINDER_PYBIND11_TYPE_CASTER
	#define BINDER_PYBIND11_TYPE_CASTER
	PYBIND11_DECLARE_HOLDER_TYPE(T, std::shared_ptr<T>)
	PYBIND11_DECLARE_HOLDER_TYPE(T, T*)
	PYBIND11_MAKE_OPAQUE(std::shared_ptr<void>)
#endif

// std::logic_error file:stdexcept line:113
struct PyCallBack_std_logic_error : public std::logic_error {
	using std::logic_error::logic_error;

	const char * what() const throw() override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const std::logic_error *>(this), "what");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>();
			if (pybind11::detail::cast_is_temporary_value_reference<const char *>::value) {
				static pybind11::detail::override_caster_t<const char *> caster;
				return pybind11::detail::cast_ref<const char *>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<const char *>(std::move(o));
		}
		return logic_error::what();
	}
};

// std::invalid_argument file:stdexcept line:168
struct PyCallBack_std_invalid_argument : public std::invalid_argument {
	using std::invalid_argument::invalid_argument;

	const char * what() const throw() override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const std::invalid_argument *>(this), "what");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>();
			if (pybind11::detail::cast_is_temporary_value_reference<const char *>::value) {
				static pybind11::detail::override_caster_t<const char *> caster;
				return pybind11::detail::cast_ref<const char *>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<const char *>(std::move(o));
		}
		return logic_error::what();
	}
};

// std::runtime_error file:stdexcept line:219
struct PyCallBack_std_runtime_error : public std::runtime_error {
	using std::runtime_error::runtime_error;

	const char * what() const throw() override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const std::runtime_error *>(this), "what");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>();
			if (pybind11::detail::cast_is_temporary_value_reference<const char *>::value) {
				static pybind11::detail::override_caster_t<const char *> caster;
				return pybind11::detail::cast_ref<const char *>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<const char *>(std::move(o));
		}
		return runtime_error::what();
	}
};

void bind_std_stdexcept(std::function< pybind11::module &(std::string const &namespace_) > &M)
{
	{ // std::logic_error file:stdexcept line:113
		pybind11::class_<std::logic_error, std::shared_ptr<std::logic_error>, PyCallBack_std_logic_error, std::exception> cl(M("std"), "logic_error", "");
		cl.def( pybind11::init<const std::string &>(), pybind11::arg("__arg") );

		cl.def( pybind11::init<const char *>(), pybind11::arg("") );

		cl.def( pybind11::init( [](PyCallBack_std_logic_error const &o){ return new PyCallBack_std_logic_error(o); } ) );
		cl.def( pybind11::init( [](std::logic_error const &o){ return new std::logic_error(o); } ) );
		cl.def("assign", (class std::logic_error & (std::logic_error::*)(const class std::logic_error &)) &std::logic_error::operator=, "C++: std::logic_error::operator=(const class std::logic_error &) --> class std::logic_error &", pybind11::return_value_policy::automatic, pybind11::arg(""));
		cl.def("what", (const char * (std::logic_error::*)() const) &std::logic_error::what, "C++: std::logic_error::what() const --> const char *", pybind11::return_value_policy::automatic);
	}
	{ // std::invalid_argument file:stdexcept line:168
		pybind11::class_<std::invalid_argument, std::shared_ptr<std::invalid_argument>, PyCallBack_std_invalid_argument, std::logic_error> cl(M("std"), "invalid_argument", "");
		cl.def( pybind11::init<const std::string &>(), pybind11::arg("__arg") );

		cl.def( pybind11::init<const char *>(), pybind11::arg("") );

		cl.def( pybind11::init( [](PyCallBack_std_invalid_argument const &o){ return new PyCallBack_std_invalid_argument(o); } ) );
		cl.def( pybind11::init( [](std::invalid_argument const &o){ return new std::invalid_argument(o); } ) );
		cl.def("assign", (class std::invalid_argument & (std::invalid_argument::*)(const class std::invalid_argument &)) &std::invalid_argument::operator=, "C++: std::invalid_argument::operator=(const class std::invalid_argument &) --> class std::invalid_argument &", pybind11::return_value_policy::automatic, pybind11::arg(""));
	}
	{ // std::runtime_error file:stdexcept line:219
		pybind11::class_<std::runtime_error, std::shared_ptr<std::runtime_error>, PyCallBack_std_runtime_error, std::exception> cl(M("std"), "runtime_error", "");
		cl.def( pybind11::init<const std::string &>(), pybind11::arg("__arg") );

		cl.def( pybind11::init<const char *>(), pybind11::arg("") );

		cl.def( pybind11::init( [](PyCallBack_std_runtime_error const &o){ return new PyCallBack_std_runtime_error(o); } ) );
		cl.def( pybind11::init( [](std::runtime_error const &o){ return new std::runtime_error(o); } ) );
		cl.def("assign", (class std::runtime_error & (std::runtime_error::*)(const class std::runtime_error &)) &std::runtime_error::operator=, "C++: std::runtime_error::operator=(const class std::runtime_error &) --> class std::runtime_error &", pybind11::return_value_policy::automatic, pybind11::arg(""));
		cl.def("what", (const char * (std::runtime_error::*)() const) &std::runtime_error::what, "C++: std::runtime_error::what() const --> const char *", pybind11::return_value_policy::automatic);
	}
}


// File: eternity/persist.cpp
#include <eternity/persist.hpp>
#include <sstream> // __str__

#include <functional>
#include <pybind11/pybind11.h>
#include <string>

#ifndef BINDER_PYBIND11_TYPE_CASTER
	#define BINDER_PYBIND11_TYPE_CASTER
	PYBIND11_DECLARE_HOLDER_TYPE(T, std::shared_ptr<T>)
	PYBIND11_DECLARE_HOLDER_TYPE(T, T*)
	PYBIND11_MAKE_OPAQUE(std::shared_ptr<void>)
#endif

void bind_eternity_persist(std::function< pybind11::module &(std::string const &namespace_) > &M)
{
	{ // eternity::archive file:eternity/persist.hpp line:47
		pybind11::class_<eternity::archive, std::shared_ptr<eternity::archive>> cl(M("eternity"), "archive", "This class supply common services for all\n        kind of persistence archives. The major one\n        is the ability to stored doubled pointers only\n        one time and so avoid circularity, broken links\n        and lost spaces on hard disks.");
		cl.def( pybind11::init( [](){ return new eternity::archive(); } ) );
		cl.def( pybind11::init( [](eternity::archive const &o){ return new eternity::archive(o); } ) );

		pybind11::enum_<eternity::archive::opening_mode>(cl, "opening_mode", pybind11::arithmetic(), "")
			.value("load", eternity::archive::load)
			.value("store", eternity::archive::store)
			.export_values();

		cl.def("init", (void (eternity::archive::*)()) &eternity::archive::init, "C++: eternity::archive::init() --> void");
		cl.def("put_pointer", (int (eternity::archive::*)(void *)) &eternity::archive::put_pointer, "Verify that object is stored only\n     once.\n\nC++: eternity::archive::put_pointer(void *) --> int", pybind11::arg("object"));
		cl.def("set_loading", (bool (eternity::archive::*)(bool)) &eternity::archive::set_loading, "Set the archive mode (loading or storing)\n\nC++: eternity::archive::set_loading(bool) --> bool", pybind11::arg("val"));
		cl.def("is_loading", (bool (eternity::archive::*)()) &eternity::archive::is_loading, "Verify the archive is in loading mode\n\nC++: eternity::archive::is_loading() --> bool");
		cl.def("is_storing", (bool (eternity::archive::*)()) &eternity::archive::is_storing, "Verify the archive is in storing mode\n\nC++: eternity::archive::is_storing() --> bool");
		cl.def("assign", (class eternity::archive & (eternity::archive::*)(const class eternity::archive &)) &eternity::archive::operator=, "C++: eternity::archive::operator=(const class eternity::archive &) --> class eternity::archive &", pybind11::return_value_policy::automatic, pybind11::arg(""));
	}
}


// File: eternity/persist_xml.cpp
#include <eternity/persist.hpp>
#include <eternity/persist_xml.hpp>
#include <functional>
#include <iterator>
#include <map>
#include <memory>
#include <sstream> // __str__
#include <string>
#include <utility>

#include <functional>
#include <pybind11/pybind11.h>
#include <string>

#ifndef BINDER_PYBIND11_TYPE_CASTER
	#define BINDER_PYBIND11_TYPE_CASTER
	PYBIND11_DECLARE_HOLDER_TYPE(T, std::shared_ptr<T>)
	PYBIND11_DECLARE_HOLDER_TYPE(T, T*)
	PYBIND11_MAKE_OPAQUE(std::shared_ptr<void>)
#endif

void bind_eternity_persist_xml(std::function< pybind11::module &(std::string const &namespace_) > &M)
{
	{ // eternity::xml_archive file:eternity/persist_xml.hpp line:39
		pybind11::class_<eternity::xml_archive, std::shared_ptr<eternity::xml_archive>, eternity::archive> cl(M("eternity"), "xml_archive", "xml_archive is the specialization of class archive able\n        to manage XML persistence.");
		cl.def( pybind11::init( [](){ return new eternity::xml_archive(); } ) );
		cl.def("write", (void (eternity::xml_archive::*)(std::string, unsigned int)) &eternity::xml_archive::write<unsigned int>, "C++: eternity::xml_archive::write(std::string, unsigned int) --> void", pybind11::arg("key"), pybind11::arg("value"));
		cl.def("write", (void (eternity::xml_archive::*)(std::string, unsigned long)) &eternity::xml_archive::write<unsigned long>, "C++: eternity::xml_archive::write(std::string, unsigned long) --> void", pybind11::arg("key"), pybind11::arg("value"));
		cl.def("write", (void (eternity::xml_archive::*)(std::string, double)) &eternity::xml_archive::write<double>, "C++: eternity::xml_archive::write(std::string, double) --> void", pybind11::arg("key"), pybind11::arg("value"));
		cl.def("write", (void (eternity::xml_archive::*)(std::string, int)) &eternity::xml_archive::write<int>, "C++: eternity::xml_archive::write(std::string, int) --> void", pybind11::arg("key"), pybind11::arg("value"));
		cl.def("open", (void (eternity::xml_archive::*)(std::string, enum eternity::archive::opening_mode)) &eternity::xml_archive::open, "initialize and XML archive using the file\n      named file_name. If mode is load create\n      the file. Anyway init update archive to\n      begin persistence operations.\n\nC++: eternity::xml_archive::open(std::string, enum eternity::archive::opening_mode) --> void", pybind11::arg("file_name"), pybind11::arg("mode"));
		cl.def("init", (void (eternity::xml_archive::*)(std::string, bool)) &eternity::xml_archive::init, "initialize and XML archive using the file\n      named file_name. If loading is true create\n      the file. Anyway init update archive to\n      begin persistence operations.\n          Deprecated: use open instead\n\nC++: eternity::xml_archive::init(std::string, bool) --> void", pybind11::arg("file_name"), pybind11::arg("loading"));
		cl.def("close", (void (eternity::xml_archive::*)()) &eternity::xml_archive::close, "End the persistence operation, release the file\n      handle and clear all allocated buffers.\n\nC++: eternity::xml_archive::close() --> void");
		cl.def("done", (void (eternity::xml_archive::*)()) &eternity::xml_archive::done, "End the persistence operation, release the file\n      handle and clear all allocated buffers.\n          Deprecated: use close instead\n\nC++: eternity::xml_archive::done() --> void");
		cl.def("formatting", (void (eternity::xml_archive::*)()) &eternity::xml_archive::formatting, "Indent XML output for nested class persistence\n\nC++: eternity::xml_archive::formatting() --> void");
		cl.def("read", (std::string (eternity::xml_archive::*)(std::string, int)) &eternity::xml_archive::read, "read (and return) a string with label key at position pos\n deprecated, use read(std::string key, std::string &value, int pos) instead\n\nC++: eternity::xml_archive::read(std::string, int) --> std::string", pybind11::arg("key"), pybind11::arg("pos"));
		cl.def("read", (void (eternity::xml_archive::*)(std::string, std::string &, int)) &eternity::xml_archive::read, "read (and put in value) a string with label key at position pos\n\nC++: eternity::xml_archive::read(std::string, std::string &, int) --> void", pybind11::arg("key"), pybind11::arg("value"), pybind11::arg("pos"));
		cl.def("read", (void (eternity::xml_archive::*)(std::string, int &, int)) &eternity::xml_archive::read, "read (and put in value) a int with label key at position pos\n\nC++: eternity::xml_archive::read(std::string, int &, int) --> void", pybind11::arg("key"), pybind11::arg("value"), pybind11::arg("pos"));
		cl.def("read", (void (eternity::xml_archive::*)(std::string, unsigned int &, int)) &eternity::xml_archive::read, "read (and put in value) a int with label key at position pos\n\nC++: eternity::xml_archive::read(std::string, unsigned int &, int) --> void", pybind11::arg("key"), pybind11::arg("value"), pybind11::arg("pos"));
		cl.def("read", (void (eternity::xml_archive::*)(std::string, float &, int)) &eternity::xml_archive::read, "read (and put in value) a float with label key at position pos\n\nC++: eternity::xml_archive::read(std::string, float &, int) --> void", pybind11::arg("key"), pybind11::arg("value"), pybind11::arg("pos"));
		cl.def("read", (void (eternity::xml_archive::*)(std::string, double &, int)) &eternity::xml_archive::read, "read (and put in value) a double with label key at position pos\n\nC++: eternity::xml_archive::read(std::string, double &, int) --> void", pybind11::arg("key"), pybind11::arg("value"), pybind11::arg("pos"));
		cl.def("make_branch", (void (eternity::xml_archive::*)(std::string, class std::map<std::string, std::string >)) &eternity::xml_archive::make_branch, "Create a node (e.g. <name attributes>) and set it as current one (enter branch)\n\nC++: eternity::xml_archive::make_branch(std::string, class std::map<std::string, std::string >) --> void", pybind11::arg("name"), pybind11::arg("attributes"));
		cl.def("enter_branch", (class std::map<std::string, std::string > (eternity::xml_archive::*)(std::string, unsigned long)) &eternity::xml_archive::enter_branch, "Enter in the node with tag equals to name and return its attributes\n\nC++: eternity::xml_archive::enter_branch(std::string, unsigned long) --> class std::map<std::string, std::string >", pybind11::arg("name"), pybind11::arg("pos"));
		cl.def("leave_current_branch", (void (eternity::xml_archive::*)()) &eternity::xml_archive::leave_current_branch, "Leaves current node and returns to its parent\n\nC++: eternity::xml_archive::leave_current_branch() --> void");
	}
}


// File: tsaTraits.cpp
#include <complex>
#include <sstream> // __str__
#include <tsaTraits.hpp>

#include <functional>
#include <pybind11/pybind11.h>
#include <string>

#ifndef BINDER_PYBIND11_TYPE_CASTER
	#define BINDER_PYBIND11_TYPE_CASTER
	PYBIND11_DECLARE_HOLDER_TYPE(T, std::shared_ptr<T>)
	PYBIND11_DECLARE_HOLDER_TYPE(T, T*)
	PYBIND11_MAKE_OPAQUE(std::shared_ptr<void>)
#endif

void bind_tsaTraits(std::function< pybind11::module &(std::string const &namespace_) > &M)
{
	{ // tsa::TypeTraits file:tsaTraits.hpp line:74
		pybind11::class_<tsa::TypeTraits<double>, std::shared_ptr<tsa::TypeTraits<double>>> cl(M("tsa"), "TypeTraits_double_t", "");
		cl.def( pybind11::init( [](){ return new tsa::TypeTraits<double>(); } ) );
		cl.def_static("conj", (double (*)(const double &)) &tsa::TypeTraits<double>::conj, "C++: tsa::TypeTraits<double>::conj(const double &) --> double", pybind11::arg("x"));
		cl.def_static("real", (double (*)(const double &)) &tsa::TypeTraits<double>::real, "C++: tsa::TypeTraits<double>::real(const double &) --> double", pybind11::arg("x"));
		cl.def_static("imag", (double (*)(const double &)) &tsa::TypeTraits<double>::imag, "C++: tsa::TypeTraits<double>::imag(const double &) --> double", pybind11::arg(""));
		cl.def_static("abs", (double (*)(const double &)) &tsa::TypeTraits<double>::abs, "C++: tsa::TypeTraits<double>::abs(const double &) --> double", pybind11::arg("x"));
		cl.def_static("abs2", (double (*)(const double &)) &tsa::TypeTraits<double>::abs2, "C++: tsa::TypeTraits<double>::abs2(const double &) --> double", pybind11::arg("x"));
		cl.def_static("phase", (double (*)(const double &)) &tsa::TypeTraits<double>::phase, "C++: tsa::TypeTraits<double>::phase(const double &) --> double", pybind11::arg("x"));
	}
	{ // tsa::TypeTraits file:tsaTraits.hpp line:103
		pybind11::class_<tsa::TypeTraits<std::complex<double>>, std::shared_ptr<tsa::TypeTraits<std::complex<double>>>> cl(M("tsa"), "TypeTraits_std_complex_double_t", "");
		cl.def( pybind11::init( [](){ return new tsa::TypeTraits<std::complex<double>>(); } ) );
		cl.def_static("conj", (class std::complex<double> (*)(const class std::complex<double> &)) &tsa::TypeTraits<std::complex<double>>::conj, "C++: tsa::TypeTraits<std::complex<double>>::conj(const class std::complex<double> &) --> class std::complex<double>", pybind11::arg("x"));
		cl.def_static("real", (double (*)(const class std::complex<double> &)) &tsa::TypeTraits<std::complex<double>>::real, "C++: tsa::TypeTraits<std::complex<double>>::real(const class std::complex<double> &) --> double", pybind11::arg("x"));
		cl.def_static("imag", (double (*)(const class std::complex<double> &)) &tsa::TypeTraits<std::complex<double>>::imag, "C++: tsa::TypeTraits<std::complex<double>>::imag(const class std::complex<double> &) --> double", pybind11::arg("x"));
		cl.def_static("abs", (double (*)(class std::complex<double>)) &tsa::TypeTraits<std::complex<double>>::abs, "C++: tsa::TypeTraits<std::complex<double>>::abs(class std::complex<double>) --> double", pybind11::arg("x"));
		cl.def_static("abs2", (double (*)(const class std::complex<double> &)) &tsa::TypeTraits<std::complex<double>>::abs2, "C++: tsa::TypeTraits<std::complex<double>>::abs2(const class std::complex<double> &) --> double", pybind11::arg("x"));
		cl.def_static("phase", (double (*)(const class std::complex<double> &)) &tsa::TypeTraits<std::complex<double>>::phase, "C++: tsa::TypeTraits<std::complex<double>>::phase(const class std::complex<double> &) --> double", pybind11::arg("x"));
	}
}


// File: tsaUtilityFunctions.cpp
#include <ARMAView.hpp>
#include <BaseView.hpp>
#include <complex>
#include <eternity/persist.hpp>
#include <eternity/persist_xml.hpp>
#include <functional>
#include <iterator>
#include <map>
#include <memory>
#include <sstream> // __str__
#include <string>
#include <tsaLog.hpp>
#include <tsaSerialize.hpp>
#include <tsaUtilityFunctions.hpp>
#include <utility>

#include <functional>
#include <pybind11/pybind11.h>
#include <string>

#ifndef BINDER_PYBIND11_TYPE_CASTER
	#define BINDER_PYBIND11_TYPE_CASTER
	PYBIND11_DECLARE_HOLDER_TYPE(T, std::shared_ptr<T>)
	PYBIND11_DECLARE_HOLDER_TYPE(T, T*)
	PYBIND11_MAKE_OPAQUE(std::shared_ptr<void>)
#endif

void bind_tsaUtilityFunctions(std::function< pybind11::module &(std::string const &namespace_) > &M)
{
	// tsa::tsaVersion() file:tsaUtilityFunctions.hpp line:68
	M("tsa").def("tsaVersion", (std::string (*)()) &tsa::tsaVersion, "C++: tsa::tsaVersion() --> std::string");

	// tsa::CRATIO(class std::complex<double>, class std::complex<double>) file:tsaUtilityFunctions.hpp line:70
	M("tsa").def("CRATIO", (class std::complex<double> (*)(class std::complex<double>, class std::complex<double>)) &tsa::CRATIO, "C++: tsa::CRATIO(class std::complex<double>, class std::complex<double>) --> class std::complex<double>", pybind11::arg("v1"), pybind11::arg("v2"));

	{ // tsa::ParseParameterString file:tsaUtilityFunctions.hpp line:74
		pybind11::class_<tsa::ParseParameterString, std::shared_ptr<tsa::ParseParameterString>> cl(M("tsa"), "ParseParameterString", "");
		cl.def( pybind11::init<const std::string &>(), pybind11::arg("parlist") );

		cl.def( pybind11::init( [](tsa::ParseParameterString const &o){ return new tsa::ParseParameterString(o); } ) );
		cl.def("GetFloat", (double (tsa::ParseParameterString::*)(int)) &tsa::ParseParameterString::GetFloat, "C++: tsa::ParseParameterString::GetFloat(int) --> double", pybind11::arg("n"));
		cl.def("GetInt", (int (tsa::ParseParameterString::*)(int)) &tsa::ParseParameterString::GetInt, "C++: tsa::ParseParameterString::GetInt(int) --> int", pybind11::arg("n"));
		cl.def("GetString", (std::string (tsa::ParseParameterString::*)(int)) &tsa::ParseParameterString::GetString, "C++: tsa::ParseParameterString::GetString(int) --> std::string", pybind11::arg("n"));
		cl.def("assign", (class tsa::ParseParameterString & (tsa::ParseParameterString::*)(const class tsa::ParseParameterString &)) &tsa::ParseParameterString::operator=, "C++: tsa::ParseParameterString::operator=(const class tsa::ParseParameterString &) --> class tsa::ParseParameterString &", pybind11::return_value_policy::automatic, pybind11::arg(""));
	}
	{ // tsa::MathUtils file:tsaUtilityFunctions.hpp line:140
		pybind11::class_<tsa::MathUtils, std::shared_ptr<tsa::MathUtils>> cl(M("tsa"), "MathUtils", "");
		cl.def( pybind11::init( [](){ return new tsa::MathUtils(); } ) );
		cl.def_static("isqrt", (unsigned int (*)(unsigned long)) &tsa::MathUtils::isqrt, "Evaluate the integer square root of a number.\n\n \n input number\n\n \n integer square root of val\n\nC++: tsa::MathUtils::isqrt(unsigned long) --> unsigned int", pybind11::arg("val"));
		cl.def_static("gcd", (int (*)(int, int)) &tsa::MathUtils::gcd, "Find the great common divisor between two numbers u and v\n\n \n first number\n \n\n second number\n\n \n the great common divisor between u and v\n\nC++: tsa::MathUtils::gcd(int, int) --> int", pybind11::arg("u"), pybind11::arg("v"));
		cl.def_static("max", (int (*)(int, int)) &tsa::MathUtils::max, "C++: tsa::MathUtils::max(int, int) --> int", pybind11::arg("u"), pybind11::arg("v"));
		cl.def_static("min", (int (*)(int, int)) &tsa::MathUtils::min, "C++: tsa::MathUtils::min(int, int) --> int", pybind11::arg("u"), pybind11::arg("v"));
	}
	{ // tsa::UpperTriangular file:tsaUtilityFunctions.hpp line:193
		pybind11::class_<tsa::UpperTriangular, std::shared_ptr<tsa::UpperTriangular>> cl(M("tsa"), "UpperTriangular", "");
		cl.def( pybind11::init( [](){ return new tsa::UpperTriangular(); } ) );
		cl.def_static("Map", (unsigned int (*)(unsigned int, unsigned int, unsigned int)) &tsa::UpperTriangular::Map, "C++: tsa::UpperTriangular::Map(unsigned int, unsigned int, unsigned int) --> unsigned int", pybind11::arg("i"), pybind11::arg("j"), pybind11::arg("dim"));
		cl.def_static("Size", (unsigned int (*)(unsigned int)) &tsa::UpperTriangular::Size, "C++: tsa::UpperTriangular::Size(unsigned int) --> unsigned int", pybind11::arg("dim"));
		cl.def_static("Dimension", (unsigned int (*)(unsigned int)) &tsa::UpperTriangular::Dimension, "C++: tsa::UpperTriangular::Dimension(unsigned int) --> unsigned int", pybind11::arg("sz"));
	}
	{ // tsa::LowerTriangular file:tsaUtilityFunctions.hpp line:211
		pybind11::class_<tsa::LowerTriangular, std::shared_ptr<tsa::LowerTriangular>> cl(M("tsa"), "LowerTriangular", "");
		cl.def( pybind11::init( [](){ return new tsa::LowerTriangular(); } ) );
		cl.def_static("Map", (unsigned int (*)(unsigned int, unsigned int, unsigned int)) &tsa::LowerTriangular::Map, "C++: tsa::LowerTriangular::Map(unsigned int, unsigned int, unsigned int) --> unsigned int", pybind11::arg("i"), pybind11::arg("j"), pybind11::arg(""));
		cl.def_static("Size", (unsigned int (*)(unsigned int)) &tsa::LowerTriangular::Size, "C++: tsa::LowerTriangular::Size(unsigned int) --> unsigned int", pybind11::arg("dim"));
		cl.def_static("Dimension", (unsigned int (*)(unsigned int)) &tsa::LowerTriangular::Dimension, "C++: tsa::LowerTriangular::Dimension(unsigned int) --> unsigned int", pybind11::arg("sz"));
	}
	{ // tsa::StrictUpperTriangular file:tsaUtilityFunctions.hpp line:229
		pybind11::class_<tsa::StrictUpperTriangular, std::shared_ptr<tsa::StrictUpperTriangular>> cl(M("tsa"), "StrictUpperTriangular", "");
		cl.def( pybind11::init( [](){ return new tsa::StrictUpperTriangular(); } ) );
		cl.def_static("Map", (unsigned int (*)(unsigned int, unsigned int, unsigned int)) &tsa::StrictUpperTriangular::Map, "C++: tsa::StrictUpperTriangular::Map(unsigned int, unsigned int, unsigned int) --> unsigned int", pybind11::arg("i"), pybind11::arg("j"), pybind11::arg("dim"));
		cl.def_static("Size", (unsigned int (*)(unsigned int)) &tsa::StrictUpperTriangular::Size, "C++: tsa::StrictUpperTriangular::Size(unsigned int) --> unsigned int", pybind11::arg("dim"));
		cl.def_static("Dimension", (unsigned int (*)(unsigned int)) &tsa::StrictUpperTriangular::Dimension, "C++: tsa::StrictUpperTriangular::Dimension(unsigned int) --> unsigned int", pybind11::arg("sz"));
	}
	{ // tsa::StrictLowerTriangular file:tsaUtilityFunctions.hpp line:246
		pybind11::class_<tsa::StrictLowerTriangular, std::shared_ptr<tsa::StrictLowerTriangular>> cl(M("tsa"), "StrictLowerTriangular", "");
		cl.def( pybind11::init( [](){ return new tsa::StrictLowerTriangular(); } ) );
		cl.def_static("Map", (unsigned int (*)(unsigned int, unsigned int, unsigned int)) &tsa::StrictLowerTriangular::Map, "C++: tsa::StrictLowerTriangular::Map(unsigned int, unsigned int, unsigned int) --> unsigned int", pybind11::arg("i"), pybind11::arg("j"), pybind11::arg(""));
		cl.def_static("Size", (unsigned int (*)(unsigned int)) &tsa::StrictLowerTriangular::Size, "C++: tsa::StrictLowerTriangular::Size(unsigned int) --> unsigned int", pybind11::arg("dim"));
		cl.def_static("Dimension", (unsigned int (*)(unsigned int)) &tsa::StrictLowerTriangular::Dimension, "C++: tsa::StrictLowerTriangular::Dimension(unsigned int) --> unsigned int", pybind11::arg("sz"));
	}
	{ // tsa::Square file:tsaUtilityFunctions.hpp line:262
		pybind11::class_<tsa::Square, std::shared_ptr<tsa::Square>> cl(M("tsa"), "Square", "");
		cl.def( pybind11::init( [](){ return new tsa::Square(); } ) );
		cl.def_static("Map", (unsigned int (*)(unsigned int, unsigned int, unsigned int)) &tsa::Square::Map, "C++: tsa::Square::Map(unsigned int, unsigned int, unsigned int) --> unsigned int", pybind11::arg("i"), pybind11::arg("j"), pybind11::arg("lda"));
		cl.def_static("Size", (unsigned int (*)(unsigned int)) &tsa::Square::Size, "C++: tsa::Square::Size(unsigned int) --> unsigned int", pybind11::arg("dim"));
		cl.def_static("Dimension", (unsigned int (*)(unsigned int)) &tsa::Square::Dimension, "C++: tsa::Square::Dimension(unsigned int) --> unsigned int", pybind11::arg("sz"));
	}
	{ // tsa::GetRe file:tsaUtilityFunctions.hpp line:279
		pybind11::class_<tsa::GetRe, std::shared_ptr<tsa::GetRe>> cl(M("tsa"), "GetRe", "");
		cl.def( pybind11::init( [](){ return new tsa::GetRe(); } ) );
	}
	{ // tsa::GetIm file:tsaUtilityFunctions.hpp line:288
		pybind11::class_<tsa::GetIm, std::shared_ptr<tsa::GetIm>> cl(M("tsa"), "GetIm", "");
		cl.def( pybind11::init( [](){ return new tsa::GetIm(); } ) );
	}
	{ // tsa::GetAbs file:tsaUtilityFunctions.hpp line:298
		pybind11::class_<tsa::GetAbs, std::shared_ptr<tsa::GetAbs>> cl(M("tsa"), "GetAbs", "");
		cl.def( pybind11::init( [](){ return new tsa::GetAbs(); } ) );
	}
	{ // tsa::GetAbs2 file:tsaUtilityFunctions.hpp line:308
		pybind11::class_<tsa::GetAbs2, std::shared_ptr<tsa::GetAbs2>> cl(M("tsa"), "GetAbs2", "");
		cl.def( pybind11::init( [](){ return new tsa::GetAbs2(); } ) );
	}
	{ // tsa::GetPhase file:tsaUtilityFunctions.hpp line:318
		pybind11::class_<tsa::GetPhase, std::shared_ptr<tsa::GetPhase>> cl(M("tsa"), "GetPhase", "");
		cl.def( pybind11::init( [](){ return new tsa::GetPhase(); } ) );
	}
	// tsa::Tag(char *, int, const char *, const char *) file:tsaSerialize.hpp line:47
	M("tsa").def("Tag", (char * (*)(char *, int, const char *, const char *)) &tsa::Tag, "C++: tsa::Tag(char *, int, const char *, const char *) --> char *", pybind11::return_value_policy::automatic, pybind11::arg("buffer"), pybind11::arg("n"), pybind11::arg("base"), pybind11::arg("rec"));

	// tsa::Tag(char *, int, const char *, const char *, unsigned int) file:tsaSerialize.hpp line:48
	M("tsa").def("Tag", (char * (*)(char *, int, const char *, const char *, unsigned int)) &tsa::Tag, "C++: tsa::Tag(char *, int, const char *, const char *, unsigned int) --> char *", pybind11::return_value_policy::automatic, pybind11::arg("buffer"), pybind11::arg("n"), pybind11::arg("base"), pybind11::arg("rec"), pybind11::arg("i"));

	// tsa::Tag(char *, int, const char *, const char *, unsigned int, unsigned int) file:tsaSerialize.hpp line:49
	M("tsa").def("Tag", (char * (*)(char *, int, const char *, const char *, unsigned int, unsigned int)) &tsa::Tag, "C++: tsa::Tag(char *, int, const char *, const char *, unsigned int, unsigned int) --> char *", pybind11::return_value_policy::automatic, pybind11::arg("buffer"), pybind11::arg("n"), pybind11::arg("base"), pybind11::arg("rec"), pybind11::arg("i"), pybind11::arg("j"));

	// tsa::LogInfo(const std::string &) file:tsaLog.hpp line:76
	M("tsa").def("LogInfo", [](const std::string & a0) -> void { return tsa::LogInfo(a0); }, "", pybind11::arg("s"));

	// tsa::LogWarning(const std::string &) file:tsaLog.hpp line:78
	M("tsa").def("LogWarning", [](const std::string & a0) -> void { return tsa::LogWarning(a0); }, "", pybind11::arg("s"));

	// tsa::LogSevere(const std::string &) file:tsaLog.hpp line:80
	M("tsa").def("LogSevere", [](const std::string & a0) -> void { return tsa::LogSevere(a0); }, "", pybind11::arg("s"));

	// tsa::LogSevere(int, const std::string &) file:tsaLog.hpp line:81
	M("tsa").def("LogSevere", [](int const & a0, const std::string & a1) -> void { return tsa::LogSevere(a0, a1); }, "", pybind11::arg("lvl"), pybind11::arg("s"));

	// tsa::LogFatal(const std::string &) file:tsaLog.hpp line:84
	M("tsa").def("LogFatal", [](const std::string & a0) -> void { return tsa::LogFatal(a0); }, "", pybind11::arg("s"));

	// tsa::LogDebug(int, const std::string &) file:tsaLog.hpp line:85
	M("tsa").def("LogDebug", [](int const & a0, const std::string & a1) -> void { return tsa::LogDebug(a0, a1); }, "", pybind11::arg("lvl"), pybind11::arg("s"));

	{ // tsa::BaseView file:BaseView.hpp line:73
		pybind11::class_<tsa::BaseView, std::shared_ptr<tsa::BaseView>> cl(M("tsa"), "BaseView", "");
		cl.def( pybind11::init( [](){ return new tsa::BaseView(); } ), "doc" );
		cl.def( pybind11::init<const std::string &>(), pybind11::arg("aName") );

		cl.def( pybind11::init( [](tsa::BaseView const &o){ return new tsa::BaseView(o); } ) );
		cl.def("assign", (class tsa::BaseView & (tsa::BaseView::*)(const class tsa::BaseView &)) &tsa::BaseView::operator=, "Assignement operator\n\n \n The instance to be assigned from\n\n \n a reference to a new object\n\nC++: tsa::BaseView::operator=(const class tsa::BaseView &) --> class tsa::BaseView &", pybind11::return_value_policy::automatic, pybind11::arg("from"));
		cl.def("GetName", (std::string (tsa::BaseView::*)()) &tsa::BaseView::GetName, "C++: tsa::BaseView::GetName() --> std::string");
		cl.def("SetName", (void (tsa::BaseView::*)(const std::string &)) &tsa::BaseView::SetName, "C++: tsa::BaseView::SetName(const std::string &) --> void", pybind11::arg("aName"));
	}
	{ // tsa::ARMAView file:ARMAView.hpp line:83
		pybind11::class_<tsa::ARMAView, std::shared_ptr<tsa::ARMAView>, tsa::BaseView> cl(M("tsa"), "ARMAView", "ARMA view: container for (vectorial) ARMA processes\n\n A view for ARMA parametrization. It defines a general (V)ARMA process, which\n can be written as\n \n\n\n\n where A,B are square matrix of dimension d equal to the dimension of the input\n and output vectors x,y.\n If the order of the part MA q is equal to zero the process is an AR process.\n If the order of the AR part p is equal to zero the process is an MA process.\n Note that the matrix \n\n is assumed to be the identity.");
		cl.def( pybind11::init( [](unsigned int const & a0, unsigned int const & a1){ return new tsa::ARMAView(a0, a1); } ), "doc" , pybind11::arg("maxP"), pybind11::arg("maxQ"));
		cl.def( pybind11::init<unsigned int, unsigned int, int>(), pybind11::arg("maxP"), pybind11::arg("maxQ"), pybind11::arg("channels") );

		cl.def( pybind11::init( [](tsa::ARMAView const &o){ return new tsa::ARMAView(o); } ) );
		cl.def("Load", [](tsa::ARMAView &o, const char * a0) -> void { return o.Load(a0); }, "", pybind11::arg("filename"));
		cl.def("Load", (void (tsa::ARMAView::*)(const char *, const char *)) &tsa::ARMAView::Load, "C++: tsa::ARMAView::Load(const char *, const char *) --> void", pybind11::arg("filename"), pybind11::arg("fmt"));
		cl.def("Save", [](tsa::ARMAView &o, const char * a0) -> void { return o.Save(a0); }, "", pybind11::arg("filename"));
		cl.def("Save", (void (tsa::ARMAView::*)(const char *, const char *)) &tsa::ARMAView::Save, "C++: tsa::ARMAView::Save(const char *, const char *) --> void", pybind11::arg("filename"), pybind11::arg("fmt"));
		cl.def("xml_serialize", (void (tsa::ARMAView::*)(class eternity::xml_archive &, const char *)) &tsa::ARMAView::xml_serialize, "C++: tsa::ARMAView::xml_serialize(class eternity::xml_archive &, const char *) --> void", pybind11::arg("xml"), pybind11::arg("prefix"));
		cl.def("GetAR", [](tsa::ARMAView const &o, int const & a0) -> const double & { return o.GetAR(a0); }, "", pybind11::return_value_policy::automatic, pybind11::arg("i"));
		cl.def("GetAR", (const double & (tsa::ARMAView::*)(int, unsigned int) const) &tsa::ARMAView::GetAR, "This method gives the value of the AR[i] coefficient for one of the channels.\n It is assumed that the VARMA process is diagonal, which means that there is\n and independent ARMA process for each channel.\n\n \n the index of the AR coefficient\n \n\n the channel\n\n \n the value of the AR[i] coefficient\n\nC++: tsa::ARMAView::GetAR(int, unsigned int) const --> const double &", pybind11::return_value_policy::automatic, pybind11::arg("i"), pybind11::arg("channel"));
		cl.def("GetMA", [](tsa::ARMAView const &o, int const & a0) -> const double & { return o.GetMA(a0); }, "", pybind11::return_value_policy::automatic, pybind11::arg("i"));
		cl.def("GetMA", (const double & (tsa::ARMAView::*)(int, unsigned int) const) &tsa::ARMAView::GetMA, "This method gives the value of the MA[i] coefficient for one of the channels.\n It is assumed that the VARMA process is diagonal, which means that there is\n and independent ARMA process for each channel.\n\n \n the index of the MA coefficient\n \n\n the channel\n\n \n the value of the MA[i] coefficient\n\nC++: tsa::ARMAView::GetMA(int, unsigned int) const --> const double &", pybind11::return_value_policy::automatic, pybind11::arg("i"), pybind11::arg("channel"));
		cl.def("GetVAR", (const double & (tsa::ARMAView::*)(int, unsigned int, unsigned int) const) &tsa::ARMAView::GetVAR, "This method gives the value of the \n coefficient for the VARMA process\n\n \n the index of the VAR coefficient\n \n\n the first channel (index j)\n \n\n the se channel (index k)\n\n \n the value of the coefficient \n\nC++: tsa::ARMAView::GetVAR(int, unsigned int, unsigned int) const --> const double &", pybind11::return_value_policy::automatic, pybind11::arg("i"), pybind11::arg("channel1"), pybind11::arg("channel2"));
		cl.def("GetVMA", (const double & (tsa::ARMAView::*)(int, unsigned int, unsigned int) const) &tsa::ARMAView::GetVMA, "This method gives the value of the \n coefficient for the VARMA process\n\n \n the index of the VMA coefficient\n \n\n the first channel (index j)\n \n\n the se channel (index k)\n\n \n the value of the coefficient \n\nC++: tsa::ARMAView::GetVMA(int, unsigned int, unsigned int) const --> const double &", pybind11::return_value_policy::automatic, pybind11::arg("i"), pybind11::arg("channel1"), pybind11::arg("channel2"));
		cl.def("GetArOrder", (unsigned int (tsa::ARMAView::*)() const) &tsa::ARMAView::GetArOrder, "Get the order of the AR part of the process.\n\n \n the order of the AR part of the process\n\nC++: tsa::ARMAView::GetArOrder() const --> unsigned int");
		cl.def("GetMaOrder", (unsigned int (tsa::ARMAView::*)() const) &tsa::ARMAView::GetMaOrder, "Get the order of the MA part of the process.\n\n \n the order of the MA part of the process\n\nC++: tsa::ARMAView::GetMaOrder() const --> unsigned int");
		cl.def("GetChannels", (unsigned int (tsa::ARMAView::*)() const) &tsa::ARMAView::GetChannels, "Get the dimension of the VARMA process.\n\n \n the dimension of the VARMA process\n\nC++: tsa::ARMAView::GetChannels() const --> unsigned int");
		cl.def("SetAR", [](tsa::ARMAView &o, int const & a0, double const & a1) -> void { return o.SetAR(a0, a1); }, "", pybind11::arg("i"), pybind11::arg("v"));
		cl.def("SetAR", (void (tsa::ARMAView::*)(int, double, unsigned int)) &tsa::ARMAView::SetAR, "This method sets the value of the AR[i] coefficient for one of the channels.\n It is assumed that the VARMA process is diagonal, which means that there is\n and independent ARMA process for each channel.\n\n \n the index of the AR part\n \n\n the new value of AR[i]\n \n\n the channel\n\nC++: tsa::ARMAView::SetAR(int, double, unsigned int) --> void", pybind11::arg("i"), pybind11::arg("v"), pybind11::arg("channel"));
		cl.def("SetMA", [](tsa::ARMAView &o, int const & a0, double const & a1) -> void { return o.SetMA(a0, a1); }, "", pybind11::arg("i"), pybind11::arg("v"));
		cl.def("SetMA", (void (tsa::ARMAView::*)(int, double, unsigned int)) &tsa::ARMAView::SetMA, "This method sets the value of the MA[i] coefficient for one of the channels.\n It is assumed that the VARMA process is diagonal, which means that there is\n and independent ARMA process for each channel.\n\n \n the index of the MA part\n \n\n the new value of MA[i]\n \n\n the channel\n\nC++: tsa::ARMAView::SetMA(int, double, unsigned int) --> void", pybind11::arg("i"), pybind11::arg("v"), pybind11::arg("channel"));
		cl.def("SetVAR", (void (tsa::ARMAView::*)(int, double, unsigned int, unsigned int)) &tsa::ARMAView::SetVAR, "This method sets the value of the \n coefficient for the VARMA process\n\n \n the index of the VAR coefficient\n \n\n the new value of \n\n \n the first channel (index j)\n \n\n the se channel (index k)\n\nC++: tsa::ARMAView::SetVAR(int, double, unsigned int, unsigned int) --> void", pybind11::arg("i"), pybind11::arg("v"), pybind11::arg("channel1"), pybind11::arg("channel2"));
		cl.def("SetVMA", (void (tsa::ARMAView::*)(int, double, unsigned int, unsigned int)) &tsa::ARMAView::SetVMA, "This method sets the value of the \n coefficient for the VARMA process\n\n \n the index of the VAR coefficient\n \n\n the new value of \n\n \n the first channel (index j)\n \n\n the se channel (index k)\n\nC++: tsa::ARMAView::SetVMA(int, double, unsigned int, unsigned int) --> void", pybind11::arg("i"), pybind11::arg("v"), pybind11::arg("channel1"), pybind11::arg("channel2"));
		cl.def("SetOrder", (void (tsa::ARMAView::*)(unsigned int, unsigned int)) &tsa::ARMAView::SetOrder, "This methods sets the order (p,q) of the (V)ARMA process\n\n \n the order of the AR part of the process\n \n\n the order of the MA part of the process\n\nC++: tsa::ARMAView::SetOrder(unsigned int, unsigned int) --> void", pybind11::arg("maxP"), pybind11::arg("maxQ"));
		cl.def("SetChannels", (void (tsa::ARMAView::*)(unsigned int)) &tsa::ARMAView::SetChannels, "This method sets the dimension of the VARMA process\n\n \n the dimension of the VARMA process\n\nC++: tsa::ARMAView::SetChannels(unsigned int) --> void", pybind11::arg("channels"));
		cl.def("assign", (class tsa::ARMAView & (tsa::ARMAView::*)(const class tsa::ARMAView &)) &tsa::ARMAView::operator=, "C++: tsa::ARMAView::operator=(const class tsa::ARMAView &) --> class tsa::ARMAView &", pybind11::return_value_policy::automatic, pybind11::arg(""));
	}
}


// File: LatticeView.cpp
#include <LatticeView.hpp>
#include <boost/numeric/ublas/functional.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/storage.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include <eternity/persist.hpp>
#include <eternity/persist_xml.hpp>
#include <functional>
#include <map>
#include <memory>
#include <sstream> // __str__
#include <string>
#include <utility>

#include <functional>
#include <pybind11/pybind11.h>
#include <string>

#ifndef BINDER_PYBIND11_TYPE_CASTER
	#define BINDER_PYBIND11_TYPE_CASTER
	PYBIND11_DECLARE_HOLDER_TYPE(T, std::shared_ptr<T>)
	PYBIND11_DECLARE_HOLDER_TYPE(T, T*)
	PYBIND11_MAKE_OPAQUE(std::shared_ptr<void>)
#endif

void bind_LatticeView(std::function< pybind11::module &(std::string const &namespace_) > &M)
{
	{ // tsa::LatticeView file:LatticeView.hpp line:75
		pybind11::class_<tsa::LatticeView, std::shared_ptr<tsa::LatticeView>, tsa::BaseView> cl(M("tsa"), "LatticeView", "Define the object needed to implement the Lattice filter");
		cl.def( pybind11::init( [](){ return new tsa::LatticeView(); } ), "doc" );
		cl.def( pybind11::init<unsigned int>(), pybind11::arg("ArOrder") );

		cl.def( pybind11::init( [](tsa::LatticeView const &o){ return new tsa::LatticeView(o); } ) );
		cl.def("Load", [](tsa::LatticeView &o, const char * a0) -> void { return o.Load(a0); }, "", pybind11::arg("filename"));
		cl.def("Load", (void (tsa::LatticeView::*)(const char *, const char *)) &tsa::LatticeView::Load, "C++: tsa::LatticeView::Load(const char *, const char *) --> void", pybind11::arg("filename"), pybind11::arg("fmt"));
		cl.def("Save", [](tsa::LatticeView &o, const char * a0) -> void { return o.Save(a0); }, "", pybind11::arg("filename"));
		cl.def("Save", (void (tsa::LatticeView::*)(const char *, const char *)) &tsa::LatticeView::Save, "C++: tsa::LatticeView::Save(const char *, const char *) --> void", pybind11::arg("filename"), pybind11::arg("fmt"));
		cl.def("xml_serialize", (void (tsa::LatticeView::*)(class eternity::xml_archive &, const char *)) &tsa::LatticeView::xml_serialize, "C++: tsa::LatticeView::xml_serialize(class eternity::xml_archive &, const char *) --> void", pybind11::arg("xml"), pybind11::arg("prefix"));
		cl.def("GetOrder", (unsigned int (tsa::LatticeView::*)()) &tsa::LatticeView::GetOrder, "Order of the LatticeView \n\nC++: tsa::LatticeView::GetOrder() --> unsigned int");
		cl.def("GetParcor", (double (tsa::LatticeView::*)(unsigned int)) &tsa::LatticeView::GetParcor, "index of the vector \n \n\n The Parcor parameter\n\nC++: tsa::LatticeView::GetParcor(unsigned int) --> double", pybind11::arg("j"));
		cl.def("GetParcorF", (double (tsa::LatticeView::*)(unsigned int)) &tsa::LatticeView::GetParcorF, "index of the vector \n \n\n The Parcor parameter\n\nC++: tsa::LatticeView::GetParcorF(unsigned int) --> double", pybind11::arg("j"));
		cl.def("GetParcorB", (double (tsa::LatticeView::*)(unsigned int)) &tsa::LatticeView::GetParcorB, "index of the vector \n \n\n The Parcor parameter\n\nC++: tsa::LatticeView::GetParcorB(unsigned int) --> double", pybind11::arg("j"));
		cl.def("GetErrorForward", (double (tsa::LatticeView::*)(unsigned int, unsigned int)) &tsa::LatticeView::GetErrorForward, "C++: tsa::LatticeView::GetErrorForward(unsigned int, unsigned int) --> double", pybind11::arg("i"), pybind11::arg("j"));
		cl.def("GetErrorBackward", (double (tsa::LatticeView::*)(unsigned int, unsigned int)) &tsa::LatticeView::GetErrorBackward, "C++: tsa::LatticeView::GetErrorBackward(unsigned int, unsigned int) --> double", pybind11::arg("i"), pybind11::arg("j"));
		cl.def("SetOrder", (void (tsa::LatticeView::*)(unsigned int)) &tsa::LatticeView::SetOrder, "C++: tsa::LatticeView::SetOrder(unsigned int) --> void", pybind11::arg("v"));
		cl.def("SetParcorF", (void (tsa::LatticeView::*)(unsigned int, double)) &tsa::LatticeView::SetParcorF, "C++: tsa::LatticeView::SetParcorF(unsigned int, double) --> void", pybind11::arg("j"), pybind11::arg("v"));
		cl.def("SetParcorB", (void (tsa::LatticeView::*)(unsigned int, double)) &tsa::LatticeView::SetParcorB, "C++: tsa::LatticeView::SetParcorB(unsigned int, double) --> void", pybind11::arg("j"), pybind11::arg("v"));
		cl.def("SetErrorForward", (void (tsa::LatticeView::*)(unsigned int, double)) &tsa::LatticeView::SetErrorForward, "C++: tsa::LatticeView::SetErrorForward(unsigned int, double) --> void", pybind11::arg("j"), pybind11::arg("v"));
		cl.def("SetErrorBackward", (void (tsa::LatticeView::*)(unsigned int, double)) &tsa::LatticeView::SetErrorBackward, "C++: tsa::LatticeView::SetErrorBackward(unsigned int, double) --> void", pybind11::arg("j"), pybind11::arg("v"));
		cl.def("assign", (class tsa::LatticeView & (tsa::LatticeView::*)(const class tsa::LatticeView &)) &tsa::LatticeView::operator=, "C++: tsa::LatticeView::operator=(const class tsa::LatticeView &) --> class tsa::LatticeView &", pybind11::return_value_policy::automatic, pybind11::arg(""));
	}
}


// File: FrameL.cpp
#include <FrameL.h>
#include <sstream> // __str__

#include <functional>
#include <pybind11/pybind11.h>
#include <string>

#ifndef BINDER_PYBIND11_TYPE_CASTER
	#define BINDER_PYBIND11_TYPE_CASTER
	PYBIND11_DECLARE_HOLDER_TYPE(T, std::shared_ptr<T>)
	PYBIND11_DECLARE_HOLDER_TYPE(T, T*)
	PYBIND11_MAKE_OPAQUE(std::shared_ptr<void>)
#endif

void bind_FrameL(std::function< pybind11::module &(std::string const &namespace_) > &M)
{
	{ // FrameH file:FrameL.h line:151
		pybind11::class_<FrameH, std::shared_ptr<FrameH>> cl(M(""), "FrameH", "");
		cl.def( pybind11::init( [](){ return new FrameH(); } ) );
		cl.def_readwrite("run", &FrameH::run);
		cl.def_readwrite("frame", &FrameH::frame);
		cl.def_readwrite("dataQuality", &FrameH::dataQuality);
		cl.def_readwrite("GTimeS", &FrameH::GTimeS);
		cl.def_readwrite("GTimeN", &FrameH::GTimeN);
		cl.def_readwrite("ULeapS", &FrameH::ULeapS);
		cl.def_readwrite("dt", &FrameH::dt);
	}
	{ // FrAdcData file:FrameL.h line:287
		pybind11::class_<FrAdcData, std::shared_ptr<FrAdcData>> cl(M(""), "FrAdcData", "");
		cl.def( pybind11::init( [](){ return new FrAdcData(); } ) );
		cl.def_readwrite("channelGroup", &FrAdcData::channelGroup);
		cl.def_readwrite("channelNumber", &FrAdcData::channelNumber);
		cl.def_readwrite("nBits", &FrAdcData::nBits);
		cl.def_readwrite("bias", &FrAdcData::bias);
		cl.def_readwrite("slope", &FrAdcData::slope);
		cl.def_readwrite("sampleRate", &FrAdcData::sampleRate);
		cl.def_readwrite("timeOffset", &FrAdcData::timeOffset);
		cl.def_readwrite("fShift", &FrAdcData::fShift);
		cl.def_readwrite("phase", &FrAdcData::phase);
		cl.def_readwrite("dataValid", &FrAdcData::dataValid);
	}
	{ // FrFile file:FrameL.h line:505
		pybind11::class_<FrFile, std::shared_ptr<FrFile>> cl(M(""), "FrFile", "");
		cl.def( pybind11::init( [](){ return new FrFile(); } ) );
		cl.def_readwrite("inMemory", &FrFile::inMemory);
		cl.def_readwrite("compress", &FrFile::compress);
		cl.def_readwrite("gzipLevel", &FrFile::gzipLevel);
		cl.def_readwrite("maxSH", &FrFile::maxSH);
		cl.def_readwrite("fmType", &FrFile::fmType);
		cl.def_readwrite("fmLong", &FrFile::fmLong);
		cl.def_readwrite("endOfFrame", &FrFile::endOfFrame);
		cl.def_readwrite("fmtVersion", &FrFile::fmtVersion);
		cl.def_readwrite("run", &FrFile::run);
		cl.def_readwrite("nFrames", &FrFile::nFrames);
		cl.def_readwrite("nBytes", &FrFile::nBytes);
		cl.def_readwrite("nBytesE", &FrFile::nBytesE);
		cl.def_readwrite("nBytesF", &FrFile::nBytesF);
		cl.def_readwrite("nBytesR", &FrFile::nBytesR);
		cl.def_readwrite("error", &FrFile::error);
		cl.def_readwrite("bufSize", &FrFile::bufSize);
		cl.def_readwrite("oldLocalTime", &FrFile::oldLocalTime);
		cl.def_readwrite("length", &FrFile::length);
		cl.def_readwrite("vectorType", &FrFile::vectorType);
		cl.def_readwrite("detectorType", &FrFile::detectorType);
		cl.def_readwrite("type", &FrFile::type);
		cl.def_readwrite("instance", &FrFile::instance);
		cl.def_readwrite("instanceH", &FrFile::instanceH);
		cl.def_readwrite("vectInstance", &FrFile::vectInstance);
		cl.def_readwrite("nSH", &FrFile::nSH);
		cl.def_readwrite("nSE", &FrFile::nSE);
		cl.def_readwrite("noTOCts", &FrFile::noTOCts);
		cl.def_readwrite("fLength", &FrFile::fLength);
		cl.def_readwrite("dirPeriod", &FrFile::dirPeriod);
		cl.def_readwrite("startTime", &FrFile::startTime);
		cl.def_readwrite("closingTime", &FrFile::closingTime);
		cl.def_readwrite("currentEndTime", &FrFile::currentEndTime);
		cl.def_readwrite("convertH", &FrFile::convertH);
		cl.def_readwrite("aligned", &FrFile::aligned);
		cl.def_readwrite("chkSumFiFlag", &FrFile::chkSumFiFlag);
		cl.def_readwrite("chkSumFrFlag", &FrFile::chkSumFrFlag);
		cl.def_readwrite("chkSumFi", &FrFile::chkSumFi);
		cl.def_readwrite("chkSumFr", &FrFile::chkSumFr);
		cl.def_readwrite("chkSumFrHeader", &FrFile::chkSumFrHeader);
		cl.def_readwrite("chkSumFiRead", &FrFile::chkSumFiRead);
		cl.def_readwrite("chkSumFrRead", &FrFile::chkSumFrRead);
		cl.def_readwrite("chkTypeFiRead", &FrFile::chkTypeFiRead);
		cl.def_readwrite("chkTypeFrRead", &FrFile::chkTypeFrRead);
		cl.def_readwrite("relocation", &FrFile::relocation);
		cl.def_readwrite("nRef", &FrFile::nRef);
		cl.def_readwrite("lastSlope", &FrFile::lastSlope);
		cl.def_readwrite("lastBias", &FrFile::lastBias);
	}
	{ // FrProcData file:FrameL.h line:746
		pybind11::class_<FrProcData, std::shared_ptr<FrProcData>> cl(M(""), "FrProcData", "");
		cl.def( pybind11::init( [](){ return new FrProcData(); } ) );
		cl.def_readwrite("type", &FrProcData::type);
		cl.def_readwrite("subType", &FrProcData::subType);
		cl.def_readwrite("timeOffset", &FrProcData::timeOffset);
		cl.def_readwrite("tRange", &FrProcData::tRange);
		cl.def_readwrite("fShift", &FrProcData::fShift);
		cl.def_readwrite("phase", &FrProcData::phase);
		cl.def_readwrite("fRange", &FrProcData::fRange);
		cl.def_readwrite("BW", &FrProcData::BW);
		cl.def_readwrite("nAuxParam", &FrProcData::nAuxParam);
	}
	{ // FrSimData file:FrameL.h line:905
		pybind11::class_<FrSimData, std::shared_ptr<FrSimData>> cl(M(""), "FrSimData", "");
		cl.def( pybind11::init( [](){ return new FrSimData(); } ) );
		cl.def_readwrite("sampleRate", &FrSimData::sampleRate);
		cl.def_readwrite("timeOffset", &FrSimData::timeOffset);
		cl.def_readwrite("fShift", &FrSimData::fShift);
		cl.def_readwrite("phase", &FrSimData::phase);
	}
	{ // FrVect file: line:41
		pybind11::class_<FrVect, std::shared_ptr<FrVect>> cl(M(""), "FrVect", "");
		cl.def( pybind11::init( [](){ return new FrVect(); } ) );
		cl.def_readwrite("compress", &FrVect::compress);
		cl.def_readwrite("type", &FrVect::type);
		cl.def_readwrite("nData", &FrVect::nData);
		cl.def_readwrite("nBytes", &FrVect::nBytes);
		cl.def_readwrite("nDim", &FrVect::nDim);
		cl.def_readwrite("wSize", &FrVect::wSize);
		cl.def_readwrite("space", &FrVect::space);
		cl.def_readwrite("GTime", &FrVect::GTime);
		cl.def_readwrite("ULeapS", &FrVect::ULeapS);
		cl.def_readwrite("localTime", &FrVect::localTime);
		cl.def_readwrite("nDataUnzoomed", &FrVect::nDataUnzoomed);
		cl.def_readwrite("startXUnzoomed", &FrVect::startXUnzoomed);
	}
}


// File: SeqView.cpp
#include <AlgoExceptions.hpp>
#include <SeqView.hpp>
#include <boost/numeric/ublas/functional.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/storage.hpp>
#include <complex>
#include <iterator>
#include <memory>
#include <sstream> // __str__
#include <stdexcept>
#include <string>

#include <functional>
#include <pybind11/pybind11.h>
#include <string>

#ifndef BINDER_PYBIND11_TYPE_CASTER
	#define BINDER_PYBIND11_TYPE_CASTER
	PYBIND11_DECLARE_HOLDER_TYPE(T, std::shared_ptr<T>)
	PYBIND11_DECLARE_HOLDER_TYPE(T, T*)
	PYBIND11_MAKE_OPAQUE(std::shared_ptr<void>)
#endif

// tsa::bad_matrix_size file:AlgoExceptions.hpp line:72
struct PyCallBack_tsa_bad_matrix_size : public tsa::bad_matrix_size {
	using tsa::bad_matrix_size::bad_matrix_size;

	const char * what() const throw() override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const tsa::bad_matrix_size *>(this), "what");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>();
			if (pybind11::detail::cast_is_temporary_value_reference<const char *>::value) {
				static pybind11::detail::override_caster_t<const char *> caster;
				return pybind11::detail::cast_ref<const char *>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<const char *>(std::move(o));
		}
		return logic_error::what();
	}
};

void bind_SeqView(std::function< pybind11::module &(std::string const &namespace_) > &M)
{
	{ // tsa::SeqView file:SeqView.hpp line:25
		pybind11::class_<tsa::SeqView<double>, std::shared_ptr<tsa::SeqView<double>>, tsa::BaseView> cl(M("tsa"), "SeqView_double_t", "");
		cl.def( pybind11::init( [](){ return new tsa::SeqView<double>(); } ) );
		cl.def( pybind11::init( [](double const & a0, double const & a1, unsigned int const & a2){ return new tsa::SeqView<double>(a0, a1, a2); } ), "doc" , pybind11::arg("aStart"), pybind11::arg("aSampling"), pybind11::arg("ChannelSize"));
		cl.def( pybind11::init( [](double const & a0, double const & a1, unsigned int const & a2, const std::string & a3){ return new tsa::SeqView<double>(a0, a1, a2, a3); } ), "doc" , pybind11::arg("aStart"), pybind11::arg("aSampling"), pybind11::arg("ChannelSize"), pybind11::arg("aName"));
		cl.def( pybind11::init<double, double, unsigned int, const std::string &, unsigned int>(), pybind11::arg("aStart"), pybind11::arg("aSampling"), pybind11::arg("ChannelSize"), pybind11::arg("aName"), pybind11::arg("ColumnDim") );

		cl.def( pybind11::init( [](tsa::SeqView<double> const &o){ return new tsa::SeqView<double>(o); } ) );
		cl.def("assign", (class tsa::SeqView<double> & (tsa::SeqView<double>::*)(const class tsa::SeqView<double> &)) &tsa::SeqView<double>::operator=, "C++: tsa::SeqView<double>::operator=(const class tsa::SeqView<double> &) --> class tsa::SeqView<double> &", pybind11::return_value_policy::automatic, pybind11::arg("from"));
		cl.def("Clear", (void (tsa::SeqView<double>::*)()) &tsa::SeqView<double>::Clear, "C++: tsa::SeqView<double>::Clear() --> void");
		cl.def("MoveFrame", (void (tsa::SeqView<double>::*)(int)) &tsa::SeqView<double>::MoveFrame, "C++: tsa::SeqView<double>::MoveFrame(int) --> void", pybind11::arg("n"));
		cl.def("Write", (void (tsa::SeqView<double>::*)(int)) &tsa::SeqView<double>::Write, "C++: tsa::SeqView<double>::Write(int) --> void", pybind11::arg("fd"));
		cl.def("Read", (void (tsa::SeqView<double>::*)(int)) &tsa::SeqView<double>::Read, "C++: tsa::SeqView<double>::Read(int) --> void", pybind11::arg("fd"));
		cl.def("__call__", (double & (tsa::SeqView<double>::*)(unsigned int)) &tsa::SeqView<double>::operator(), "C++: tsa::SeqView<double>::operator()(unsigned int) --> double &", pybind11::return_value_policy::automatic, pybind11::arg("f"));
		cl.def("get", (double (tsa::SeqView<double>::*)(double)) &tsa::SeqView<double>::get, "C++: tsa::SeqView<double>::get(double) --> double", pybind11::arg("x"));
		cl.def("get", (double (tsa::SeqView<double>::*)(unsigned int, double)) &tsa::SeqView<double>::get, "C++: tsa::SeqView<double>::get(unsigned int, double) --> double", pybind11::arg("c"), pybind11::arg("x"));
		cl.def("__call__", (double & (tsa::SeqView<double>::*)(unsigned int, unsigned int)) &tsa::SeqView<double>::operator(), "C++: tsa::SeqView<double>::operator()(unsigned int, unsigned int) --> double &", pybind11::return_value_policy::automatic, pybind11::arg("channel"), pybind11::arg("f"));
		cl.def("asVector", (double & (tsa::SeqView<double>::*)(unsigned int, unsigned int)) &tsa::SeqView<double>::asVector, "C++: tsa::SeqView<double>::asVector(unsigned int, unsigned int) --> double &", pybind11::return_value_policy::automatic, pybind11::arg("channel"), pybind11::arg("f"));
		cl.def("GetScale", (double (tsa::SeqView<double>::*)()) &tsa::SeqView<double>::GetScale, "C++: tsa::SeqView<double>::GetScale() --> double");
		cl.def("GetStart", (double (tsa::SeqView<double>::*)()) &tsa::SeqView<double>::GetStart, "C++: tsa::SeqView<double>::GetStart() --> double");
		cl.def("GetSampling", (double (tsa::SeqView<double>::*)()) &tsa::SeqView<double>::GetSampling, "C++: tsa::SeqView<double>::GetSampling() --> double");
		cl.def("GetSize", (unsigned int (tsa::SeqView<double>::*)()) &tsa::SeqView<double>::GetSize, "C++: tsa::SeqView<double>::GetSize() --> unsigned int");
		cl.def("GetChannels", (unsigned int (tsa::SeqView<double>::*)()) &tsa::SeqView<double>::GetChannels, "C++: tsa::SeqView<double>::GetChannels() --> unsigned int");
		cl.def("GetX", (double (tsa::SeqView<double>::*)(unsigned int)) &tsa::SeqView<double>::GetX, "C++: tsa::SeqView<double>::GetX(unsigned int) --> double", pybind11::arg("k"));
		cl.def("GetY", (double & (tsa::SeqView<double>::*)(unsigned int, unsigned int)) &tsa::SeqView<double>::GetY, "C++: tsa::SeqView<double>::GetY(unsigned int, unsigned int) --> double &", pybind11::return_value_policy::automatic, pybind11::arg("channel"), pybind11::arg("f"));
		cl.def("GetEnd", (double (tsa::SeqView<double>::*)()) &tsa::SeqView<double>::GetEnd, "C++: tsa::SeqView<double>::GetEnd() --> double");
		cl.def("GetSlice", (double (tsa::SeqView<double>::*)()) &tsa::SeqView<double>::GetSlice, "C++: tsa::SeqView<double>::GetSlice() --> double");
		cl.def("GetIndex", (int (tsa::SeqView<double>::*)(double)) &tsa::SeqView<double>::GetIndex, "C++: tsa::SeqView<double>::GetIndex(double) --> int", pybind11::arg("x"));
		cl.def("SetScale", (double (tsa::SeqView<double>::*)(double)) &tsa::SeqView<double>::SetScale, "C++: tsa::SeqView<double>::SetScale(double) --> double", pybind11::arg("scale"));
		cl.def("SetStart", (double (tsa::SeqView<double>::*)(double)) &tsa::SeqView<double>::SetStart, "C++: tsa::SeqView<double>::SetStart(double) --> double", pybind11::arg("start"));
		cl.def("SetSampling", (double (tsa::SeqView<double>::*)(double)) &tsa::SeqView<double>::SetSampling, "C++: tsa::SeqView<double>::SetSampling(double) --> double", pybind11::arg("sampling"));
		cl.def("Fill", (void (tsa::SeqView<double>::*)(double)) &tsa::SeqView<double>::Fill, "C++: tsa::SeqView<double>::Fill(double) --> void", pybind11::arg("v"));
		cl.def("FillPoint", (void (tsa::SeqView<double>::*)(unsigned int, unsigned int, double)) &tsa::SeqView<double>::FillPoint, "C++: tsa::SeqView<double>::FillPoint(unsigned int, unsigned int, double) --> void", pybind11::arg("i"), pybind11::arg("j"), pybind11::arg("v"));
		cl.def("SetData", (void (tsa::SeqView<double>::*)(struct FrVect *)) &tsa::SeqView<double>::SetData, "C++: tsa::SeqView<double>::SetData(struct FrVect *) --> void", pybind11::arg("frv"));
		cl.def("SetDataF", (void (tsa::SeqView<double>::*)(struct FrVect *, double)) &tsa::SeqView<double>::SetDataF, "C++: tsa::SeqView<double>::SetDataF(struct FrVect *, double) --> void", pybind11::arg("frv"), pybind11::arg("offset"));
		cl.def("assign", (class tsa::BaseView & (tsa::BaseView::*)(const class tsa::BaseView &)) &tsa::BaseView::operator=, "Assignement operator\n\n \n The instance to be assigned from\n\n \n a reference to a new object\n\nC++: tsa::BaseView::operator=(const class tsa::BaseView &) --> class tsa::BaseView &", pybind11::return_value_policy::automatic, pybind11::arg("from"));
		cl.def("GetName", (std::string (tsa::BaseView::*)()) &tsa::BaseView::GetName, "C++: tsa::BaseView::GetName() --> std::string");
		cl.def("SetName", (void (tsa::BaseView::*)(const std::string &)) &tsa::BaseView::SetName, "C++: tsa::BaseView::SetName(const std::string &) --> void", pybind11::arg("aName"));
	}
	{ // tsa::SeqView file:SeqView.hpp line:25
		pybind11::class_<tsa::SeqView<std::complex<double>>, std::shared_ptr<tsa::SeqView<std::complex<double>>>, tsa::BaseView> cl(M("tsa"), "SeqView_std_complex_double_t", "");
		cl.def( pybind11::init( [](){ return new tsa::SeqView<std::complex<double>>(); } ) );
		cl.def( pybind11::init( [](double const & a0, double const & a1, unsigned int const & a2){ return new tsa::SeqView<std::complex<double>>(a0, a1, a2); } ), "doc" , pybind11::arg("aStart"), pybind11::arg("aSampling"), pybind11::arg("ChannelSize"));
		cl.def( pybind11::init( [](double const & a0, double const & a1, unsigned int const & a2, const std::string & a3){ return new tsa::SeqView<std::complex<double>>(a0, a1, a2, a3); } ), "doc" , pybind11::arg("aStart"), pybind11::arg("aSampling"), pybind11::arg("ChannelSize"), pybind11::arg("aName"));
		cl.def( pybind11::init<double, double, unsigned int, const std::string &, unsigned int>(), pybind11::arg("aStart"), pybind11::arg("aSampling"), pybind11::arg("ChannelSize"), pybind11::arg("aName"), pybind11::arg("ColumnDim") );

		cl.def( pybind11::init( [](tsa::SeqView<std::complex<double>> const &o){ return new tsa::SeqView<std::complex<double>>(o); } ) );
		cl.def("assign", (class tsa::SeqView<class std::complex<double> > & (tsa::SeqView<std::complex<double>>::*)(const class tsa::SeqView<class std::complex<double> > &)) &tsa::SeqView<std::complex<double>>::operator=, "C++: tsa::SeqView<std::complex<double>>::operator=(const class tsa::SeqView<class std::complex<double> > &) --> class tsa::SeqView<class std::complex<double> > &", pybind11::return_value_policy::automatic, pybind11::arg("from"));
		cl.def("Clear", (void (tsa::SeqView<std::complex<double>>::*)()) &tsa::SeqView<std::complex<double>>::Clear, "C++: tsa::SeqView<std::complex<double>>::Clear() --> void");
		cl.def("MoveFrame", (void (tsa::SeqView<std::complex<double>>::*)(int)) &tsa::SeqView<std::complex<double>>::MoveFrame, "C++: tsa::SeqView<std::complex<double>>::MoveFrame(int) --> void", pybind11::arg("n"));
		cl.def("Write", (void (tsa::SeqView<std::complex<double>>::*)(int)) &tsa::SeqView<std::complex<double>>::Write, "C++: tsa::SeqView<std::complex<double>>::Write(int) --> void", pybind11::arg("fd"));
		cl.def("Read", (void (tsa::SeqView<std::complex<double>>::*)(int)) &tsa::SeqView<std::complex<double>>::Read, "C++: tsa::SeqView<std::complex<double>>::Read(int) --> void", pybind11::arg("fd"));
		cl.def("__call__", (class std::complex<double> & (tsa::SeqView<std::complex<double>>::*)(unsigned int)) &tsa::SeqView<std::complex<double>>::operator(), "C++: tsa::SeqView<std::complex<double>>::operator()(unsigned int) --> class std::complex<double> &", pybind11::return_value_policy::automatic, pybind11::arg("f"));
		cl.def("get", (class std::complex<double> (tsa::SeqView<std::complex<double>>::*)(double)) &tsa::SeqView<std::complex<double>>::get, "C++: tsa::SeqView<std::complex<double>>::get(double) --> class std::complex<double>", pybind11::arg("x"));
		cl.def("get", (class std::complex<double> (tsa::SeqView<std::complex<double>>::*)(unsigned int, double)) &tsa::SeqView<std::complex<double>>::get, "C++: tsa::SeqView<std::complex<double>>::get(unsigned int, double) --> class std::complex<double>", pybind11::arg("c"), pybind11::arg("x"));
		cl.def("__call__", (class std::complex<double> & (tsa::SeqView<std::complex<double>>::*)(unsigned int, unsigned int)) &tsa::SeqView<std::complex<double>>::operator(), "C++: tsa::SeqView<std::complex<double>>::operator()(unsigned int, unsigned int) --> class std::complex<double> &", pybind11::return_value_policy::automatic, pybind11::arg("channel"), pybind11::arg("f"));
		cl.def("asVector", (class std::complex<double> & (tsa::SeqView<std::complex<double>>::*)(unsigned int, unsigned int)) &tsa::SeqView<std::complex<double>>::asVector, "C++: tsa::SeqView<std::complex<double>>::asVector(unsigned int, unsigned int) --> class std::complex<double> &", pybind11::return_value_policy::automatic, pybind11::arg("channel"), pybind11::arg("f"));
		cl.def("GetScale", (double (tsa::SeqView<std::complex<double>>::*)()) &tsa::SeqView<std::complex<double>>::GetScale, "C++: tsa::SeqView<std::complex<double>>::GetScale() --> double");
		cl.def("GetStart", (double (tsa::SeqView<std::complex<double>>::*)()) &tsa::SeqView<std::complex<double>>::GetStart, "C++: tsa::SeqView<std::complex<double>>::GetStart() --> double");
		cl.def("GetSampling", (double (tsa::SeqView<std::complex<double>>::*)()) &tsa::SeqView<std::complex<double>>::GetSampling, "C++: tsa::SeqView<std::complex<double>>::GetSampling() --> double");
		cl.def("GetSize", (unsigned int (tsa::SeqView<std::complex<double>>::*)()) &tsa::SeqView<std::complex<double>>::GetSize, "C++: tsa::SeqView<std::complex<double>>::GetSize() --> unsigned int");
		cl.def("GetChannels", (unsigned int (tsa::SeqView<std::complex<double>>::*)()) &tsa::SeqView<std::complex<double>>::GetChannels, "C++: tsa::SeqView<std::complex<double>>::GetChannels() --> unsigned int");
		cl.def("GetX", (double (tsa::SeqView<std::complex<double>>::*)(unsigned int)) &tsa::SeqView<std::complex<double>>::GetX, "C++: tsa::SeqView<std::complex<double>>::GetX(unsigned int) --> double", pybind11::arg("k"));
		cl.def("GetY", (class std::complex<double> & (tsa::SeqView<std::complex<double>>::*)(unsigned int, unsigned int)) &tsa::SeqView<std::complex<double>>::GetY, "C++: tsa::SeqView<std::complex<double>>::GetY(unsigned int, unsigned int) --> class std::complex<double> &", pybind11::return_value_policy::automatic, pybind11::arg("channel"), pybind11::arg("f"));
		cl.def("GetEnd", (double (tsa::SeqView<std::complex<double>>::*)()) &tsa::SeqView<std::complex<double>>::GetEnd, "C++: tsa::SeqView<std::complex<double>>::GetEnd() --> double");
		cl.def("GetSlice", (double (tsa::SeqView<std::complex<double>>::*)()) &tsa::SeqView<std::complex<double>>::GetSlice, "C++: tsa::SeqView<std::complex<double>>::GetSlice() --> double");
		cl.def("GetIndex", (int (tsa::SeqView<std::complex<double>>::*)(double)) &tsa::SeqView<std::complex<double>>::GetIndex, "C++: tsa::SeqView<std::complex<double>>::GetIndex(double) --> int", pybind11::arg("x"));
		cl.def("SetScale", (double (tsa::SeqView<std::complex<double>>::*)(double)) &tsa::SeqView<std::complex<double>>::SetScale, "C++: tsa::SeqView<std::complex<double>>::SetScale(double) --> double", pybind11::arg("scale"));
		cl.def("SetStart", (double (tsa::SeqView<std::complex<double>>::*)(double)) &tsa::SeqView<std::complex<double>>::SetStart, "C++: tsa::SeqView<std::complex<double>>::SetStart(double) --> double", pybind11::arg("start"));
		cl.def("SetSampling", (double (tsa::SeqView<std::complex<double>>::*)(double)) &tsa::SeqView<std::complex<double>>::SetSampling, "C++: tsa::SeqView<std::complex<double>>::SetSampling(double) --> double", pybind11::arg("sampling"));
		cl.def("Fill", (void (tsa::SeqView<std::complex<double>>::*)(class std::complex<double>)) &tsa::SeqView<std::complex<double>>::Fill, "C++: tsa::SeqView<std::complex<double>>::Fill(class std::complex<double>) --> void", pybind11::arg("v"));
		cl.def("FillPoint", (void (tsa::SeqView<std::complex<double>>::*)(unsigned int, unsigned int, class std::complex<double>)) &tsa::SeqView<std::complex<double>>::FillPoint, "C++: tsa::SeqView<std::complex<double>>::FillPoint(unsigned int, unsigned int, class std::complex<double>) --> void", pybind11::arg("i"), pybind11::arg("j"), pybind11::arg("v"));
		cl.def("SetData", (void (tsa::SeqView<std::complex<double>>::*)(struct FrVect *)) &tsa::SeqView<std::complex<double>>::SetData, "C++: tsa::SeqView<std::complex<double>>::SetData(struct FrVect *) --> void", pybind11::arg("frv"));
		cl.def("SetDataF", (void (tsa::SeqView<std::complex<double>>::*)(struct FrVect *, double)) &tsa::SeqView<std::complex<double>>::SetDataF, "C++: tsa::SeqView<std::complex<double>>::SetDataF(struct FrVect *, double) --> void", pybind11::arg("frv"), pybind11::arg("offset"));
		cl.def("assign", (class tsa::BaseView & (tsa::BaseView::*)(const class tsa::BaseView &)) &tsa::BaseView::operator=, "Assignement operator\n\n \n The instance to be assigned from\n\n \n a reference to a new object\n\nC++: tsa::BaseView::operator=(const class tsa::BaseView &) --> class tsa::BaseView &", pybind11::return_value_policy::automatic, pybind11::arg("from"));
		cl.def("GetName", (std::string (tsa::BaseView::*)()) &tsa::BaseView::GetName, "C++: tsa::BaseView::GetName() --> std::string");
		cl.def("SetName", (void (tsa::BaseView::*)(const std::string &)) &tsa::BaseView::SetName, "C++: tsa::BaseView::SetName(const std::string &) --> void", pybind11::arg("aName"));
	}
	{ // tsa::bad_matrix_size file:AlgoExceptions.hpp line:72
		pybind11::class_<tsa::bad_matrix_size, std::shared_ptr<tsa::bad_matrix_size>, PyCallBack_tsa_bad_matrix_size, std::invalid_argument> cl(M("tsa"), "bad_matrix_size", "This exception should be used when a matrix argument of an algorithm\n   has an incorrect size. It contains information about the correct expected size.");
		cl.def( pybind11::init<const std::string &>(), pybind11::arg("msg") );

		cl.def( pybind11::init( [](PyCallBack_tsa_bad_matrix_size const &o){ return new PyCallBack_tsa_bad_matrix_size(o); } ) );
		cl.def( pybind11::init( [](tsa::bad_matrix_size const &o){ return new tsa::bad_matrix_size(o); } ) );
		cl.def("assign", (class tsa::bad_matrix_size & (tsa::bad_matrix_size::*)(const class tsa::bad_matrix_size &)) &tsa::bad_matrix_size::operator=, "C++: tsa::bad_matrix_size::operator=(const class tsa::bad_matrix_size &) --> class tsa::bad_matrix_size &", pybind11::return_value_policy::automatic, pybind11::arg(""));
	}
}


// File: AlgoExceptions.cpp
#include <AlgoBase.hpp>
#include <AlgoExceptions.hpp>
#include <SeqView.hpp>
#include <ViewUtil.hpp>
#include <boost/numeric/ublas/functional.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/storage.hpp>
#include <complex>
#include <iterator>
#include <memory>
#include <sstream> // __str__
#include <stdexcept>
#include <string>

#include <functional>
#include <pybind11/pybind11.h>
#include <string>

#ifndef BINDER_PYBIND11_TYPE_CASTER
	#define BINDER_PYBIND11_TYPE_CASTER
	PYBIND11_DECLARE_HOLDER_TYPE(T, std::shared_ptr<T>)
	PYBIND11_DECLARE_HOLDER_TYPE(T, T*)
	PYBIND11_MAKE_OPAQUE(std::shared_ptr<void>)
#endif

// tsa::bad_vector_size file:AlgoExceptions.hpp line:98
struct PyCallBack_tsa_bad_vector_size : public tsa::bad_vector_size {
	using tsa::bad_vector_size::bad_vector_size;

	const char * what() const throw() override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const tsa::bad_vector_size *>(this), "what");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>();
			if (pybind11::detail::cast_is_temporary_value_reference<const char *>::value) {
				static pybind11::detail::override_caster_t<const char *> caster;
				return pybind11::detail::cast_ref<const char *>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<const char *>(std::move(o));
		}
		return logic_error::what();
	}
};

// tsa::no_data_available file:AlgoExceptions.hpp line:122
struct PyCallBack_tsa_no_data_available : public tsa::no_data_available {
	using tsa::no_data_available::no_data_available;

	const char * what() const throw() override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const tsa::no_data_available *>(this), "what");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>();
			if (pybind11::detail::cast_is_temporary_value_reference<const char *>::value) {
				static pybind11::detail::override_caster_t<const char *> caster;
				return pybind11::detail::cast_ref<const char *>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<const char *>(std::move(o));
		}
		return runtime_error::what();
	}
};

// tsa::bad_value file:AlgoExceptions.hpp line:145
struct PyCallBack_tsa_bad_value : public tsa::bad_value {
	using tsa::bad_value::bad_value;

	const char * what() const throw() override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const tsa::bad_value *>(this), "what");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>();
			if (pybind11::detail::cast_is_temporary_value_reference<const char *>::value) {
				static pybind11::detail::override_caster_t<const char *> caster;
				return pybind11::detail::cast_ref<const char *>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<const char *>(std::move(o));
		}
		return runtime_error::what();
	}
};

// tsa::missing_data file:AlgoExceptions.hpp line:168
struct PyCallBack_tsa_missing_data : public tsa::missing_data {
	using tsa::missing_data::missing_data;

	const char * what() const throw() override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const tsa::missing_data *>(this), "what");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>();
			if (pybind11::detail::cast_is_temporary_value_reference<const char *>::value) {
				static pybind11::detail::override_caster_t<const char *> caster;
				return pybind11::detail::cast_ref<const char *>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<const char *>(std::move(o));
		}
		return runtime_error::what();
	}
};

// tsa::quality_change file:AlgoExceptions.hpp line:207
struct PyCallBack_tsa_quality_change : public tsa::quality_change {
	using tsa::quality_change::quality_change;

	const char * what() const throw() override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const tsa::quality_change *>(this), "what");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>();
			if (pybind11::detail::cast_is_temporary_value_reference<const char *>::value) {
				static pybind11::detail::override_caster_t<const char *> caster;
				return pybind11::detail::cast_ref<const char *>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<const char *>(std::move(o));
		}
		return runtime_error::what();
	}
};

void bind_AlgoExceptions(std::function< pybind11::module &(std::string const &namespace_) > &M)
{
	{ // tsa::bad_vector_size file:AlgoExceptions.hpp line:98
		pybind11::class_<tsa::bad_vector_size, std::shared_ptr<tsa::bad_vector_size>, PyCallBack_tsa_bad_vector_size, std::invalid_argument> cl(M("tsa"), "bad_vector_size", "This exception should be used when a vector argument of an algorithm\n   has an incorrect size. It contains information about the correct expected size.");
		cl.def( pybind11::init<const std::string &>(), pybind11::arg("msg") );

		cl.def( pybind11::init( [](PyCallBack_tsa_bad_vector_size const &o){ return new PyCallBack_tsa_bad_vector_size(o); } ) );
		cl.def( pybind11::init( [](tsa::bad_vector_size const &o){ return new tsa::bad_vector_size(o); } ) );
		cl.def("assign", (class tsa::bad_vector_size & (tsa::bad_vector_size::*)(const class tsa::bad_vector_size &)) &tsa::bad_vector_size::operator=, "C++: tsa::bad_vector_size::operator=(const class tsa::bad_vector_size &) --> class tsa::bad_vector_size &", pybind11::return_value_policy::automatic, pybind11::arg(""));
	}
	{ // tsa::no_data_available file:AlgoExceptions.hpp line:122
		pybind11::class_<tsa::no_data_available, std::shared_ptr<tsa::no_data_available>, PyCallBack_tsa_no_data_available, std::runtime_error> cl(M("tsa"), "no_data_available", "This exception should be used when some processed data cannot be returned");
		cl.def( pybind11::init<const std::string &>(), pybind11::arg("msg") );

		cl.def( pybind11::init( [](PyCallBack_tsa_no_data_available const &o){ return new PyCallBack_tsa_no_data_available(o); } ) );
		cl.def( pybind11::init( [](tsa::no_data_available const &o){ return new tsa::no_data_available(o); } ) );
		cl.def("assign", (class tsa::no_data_available & (tsa::no_data_available::*)(const class tsa::no_data_available &)) &tsa::no_data_available::operator=, "C++: tsa::no_data_available::operator=(const class tsa::no_data_available &) --> class tsa::no_data_available &", pybind11::return_value_policy::automatic, pybind11::arg(""));
	}
	{ // tsa::bad_value file:AlgoExceptions.hpp line:145
		pybind11::class_<tsa::bad_value, std::shared_ptr<tsa::bad_value>, PyCallBack_tsa_bad_value, std::runtime_error> cl(M("tsa"), "bad_value", "This exception should be used when some processed data cannot be returned");
		cl.def( pybind11::init( [](){ return new tsa::bad_value(); }, [](){ return new PyCallBack_tsa_bad_value(); } ) );
		cl.def( pybind11::init( [](PyCallBack_tsa_bad_value const &o){ return new PyCallBack_tsa_bad_value(o); } ) );
		cl.def( pybind11::init( [](tsa::bad_value const &o){ return new tsa::bad_value(o); } ) );
		cl.def("assign", (class tsa::bad_value & (tsa::bad_value::*)(const class tsa::bad_value &)) &tsa::bad_value::operator=, "C++: tsa::bad_value::operator=(const class tsa::bad_value &) --> class tsa::bad_value &", pybind11::return_value_policy::automatic, pybind11::arg(""));
	}
	{ // tsa::missing_data file:AlgoExceptions.hpp line:168
		pybind11::class_<tsa::missing_data, std::shared_ptr<tsa::missing_data>, PyCallBack_tsa_missing_data, std::runtime_error> cl(M("tsa"), "missing_data", "This exception should be used when some frames are missing");
		cl.def( pybind11::init<const std::string &, double, double, unsigned int>(), pybind11::arg("msg"), pybind11::arg("miss_start"), pybind11::arg("miss_end"), pybind11::arg("channel") );

		cl.def( pybind11::init( [](PyCallBack_tsa_missing_data const &o){ return new PyCallBack_tsa_missing_data(o); } ) );
		cl.def( pybind11::init( [](tsa::missing_data const &o){ return new tsa::missing_data(o); } ) );
		cl.def("Start", (double (tsa::missing_data::*)()) &tsa::missing_data::Start, "C++: tsa::missing_data::Start() --> double");
		cl.def("End", (double (tsa::missing_data::*)()) &tsa::missing_data::End, "C++: tsa::missing_data::End() --> double");
		cl.def("Channel", (double (tsa::missing_data::*)()) &tsa::missing_data::Channel, "C++: tsa::missing_data::Channel() --> double");
		cl.def("assign", (class tsa::missing_data & (tsa::missing_data::*)(const class tsa::missing_data &)) &tsa::missing_data::operator=, "C++: tsa::missing_data::operator=(const class tsa::missing_data &) --> class tsa::missing_data &", pybind11::return_value_policy::automatic, pybind11::arg(""));
	}
	{ // tsa::quality_change file:AlgoExceptions.hpp line:207
		pybind11::class_<tsa::quality_change, std::shared_ptr<tsa::quality_change>, PyCallBack_tsa_quality_change, std::runtime_error> cl(M("tsa"), "quality_change", "This exception should be used when data quality change");
		cl.def( pybind11::init<const std::string &, double, unsigned int, unsigned int>(), pybind11::arg("msg"), pybind11::arg("change_time"), pybind11::arg("old_flag"), pybind11::arg("new_flag") );

		cl.def( pybind11::init( [](PyCallBack_tsa_quality_change const &o){ return new PyCallBack_tsa_quality_change(o); } ) );
		cl.def( pybind11::init( [](tsa::quality_change const &o){ return new tsa::quality_change(o); } ) );
		cl.def("EventTime", (double (tsa::quality_change::*)()) &tsa::quality_change::EventTime, "C++: tsa::quality_change::EventTime() --> double");
		cl.def("OldFlag", (unsigned int (tsa::quality_change::*)()) &tsa::quality_change::OldFlag, "C++: tsa::quality_change::OldFlag() --> unsigned int");
		cl.def("NewFlag", (unsigned int (tsa::quality_change::*)()) &tsa::quality_change::NewFlag, "C++: tsa::quality_change::NewFlag() --> unsigned int");
		cl.def("assign", (class tsa::quality_change & (tsa::quality_change::*)(const class tsa::quality_change &)) &tsa::quality_change::operator=, "C++: tsa::quality_change::operator=(const class tsa::quality_change &) --> class tsa::quality_change &", pybind11::return_value_policy::automatic, pybind11::arg(""));
	}
	{ // tsa::AlgoBase file:AlgoBase.hpp line:65
		pybind11::class_<tsa::AlgoBase, std::shared_ptr<tsa::AlgoBase>> cl(M("tsa"), "AlgoBase", "AlgoBase is the abstract base class for all algorithm.\n\n AlgoBase is the abstract base class for all the algorithm classes.\n It contain the definition of the common methods. An algorithm is a class\n with one or more execute() methods, with a variable number of parameters.");
		cl.def( pybind11::init( [](){ return new tsa::AlgoBase(); } ) );
		cl.def( pybind11::init( [](tsa::AlgoBase const &o){ return new tsa::AlgoBase(o); } ) );
		cl.def("assign", (class tsa::AlgoBase & (tsa::AlgoBase::*)(const class tsa::AlgoBase &)) &tsa::AlgoBase::operator=, "C++: tsa::AlgoBase::operator=(const class tsa::AlgoBase &) --> class tsa::AlgoBase &", pybind11::return_value_policy::automatic, pybind11::arg(""));
	}
	{ // tsa::ViewUtil file:ViewUtil.hpp line:73
		pybind11::class_<tsa::ViewUtil, std::shared_ptr<tsa::ViewUtil>, tsa::AlgoBase> cl(M("tsa"), "ViewUtil", "This is a short description of the class ViewUtil\n\n A more detailed description of ViewUtil start here");
		cl.def( pybind11::init( [](){ return new tsa::ViewUtil(); } ) );
		cl.def_static("Join", (void (*)(class tsa::SeqView<double> &, class tsa::SeqView<double> &, class tsa::SeqView<double> &)) &tsa::ViewUtil::Join, "C++: tsa::ViewUtil::Join(class tsa::SeqView<double> &, class tsa::SeqView<double> &, class tsa::SeqView<double> &) --> void", pybind11::arg("s1"), pybind11::arg("s2"), pybind11::arg("joined"));
		cl.def_static("Append", (void (*)(class tsa::SeqView<double> &, class tsa::SeqView<double> &)) &tsa::ViewUtil::Append, "C++: tsa::ViewUtil::Append(class tsa::SeqView<double> &, class tsa::SeqView<double> &) --> void", pybind11::arg("s1"), pybind11::arg("s2"));
		cl.def_static("Print", (void (*)(class tsa::SeqView<double> &, char *)) &tsa::ViewUtil::Print, "C++: tsa::ViewUtil::Print(class tsa::SeqView<double> &, char *) --> void", pybind11::arg("s1"), pybind11::arg("filename"));
		cl.def_static("Print", (void (*)(class tsa::SeqView<class std::complex<double> > &, char *)) &tsa::ViewUtil::Print, "C++: tsa::ViewUtil::Print(class tsa::SeqView<class std::complex<double> > &, char *) --> void", pybind11::arg("s1"), pybind11::arg("filename"));
		cl.def_static("Print", (void (*)(class tsa::SeqView<double> &)) &tsa::ViewUtil::Print, "C++: tsa::ViewUtil::Print(class tsa::SeqView<double> &) --> void", pybind11::arg("s1"));
		cl.def_static("Range", (void (*)(class tsa::SeqView<double> &, int, int)) &tsa::ViewUtil::Range, "C++: tsa::ViewUtil::Range(class tsa::SeqView<double> &, int, int) --> void", pybind11::arg("s1"), pybind11::arg("l"), pybind11::arg("m"));
		cl.def_static("Range", (void (*)(class tsa::SeqView<class std::complex<double> > &, int, int)) &tsa::ViewUtil::Range, "C++: tsa::ViewUtil::Range(class tsa::SeqView<class std::complex<double> > &, int, int) --> void", pybind11::arg("s1"), pybind11::arg("l"), pybind11::arg("m"));
		cl.def_static("Range", (void (*)(class tsa::SeqView<double> &, class tsa::SeqView<double> &, int, int)) &tsa::ViewUtil::Range, "C++: tsa::ViewUtil::Range(class tsa::SeqView<double> &, class tsa::SeqView<double> &, int, int) --> void", pybind11::arg("s1"), pybind11::arg("s2"), pybind11::arg("l"), pybind11::arg("m"));
		cl.def_static("LeftShift", (void (*)(class tsa::SeqView<double> &, class tsa::SeqView<double> &)) &tsa::ViewUtil::LeftShift, "C++: tsa::ViewUtil::LeftShift(class tsa::SeqView<double> &, class tsa::SeqView<double> &) --> void", pybind11::arg("seq"), pybind11::arg("ins"));
		cl.def_static("PadLeft", [](class tsa::SeqView<double> & a0, class tsa::SeqView<double> & a1, unsigned int const & a2) -> void { return tsa::ViewUtil::PadLeft(a0, a1, a2); }, "", pybind11::arg("src"), pybind11::arg("dst"), pybind11::arg("size"));
		cl.def_static("PadLeft", (void (*)(class tsa::SeqView<double> &, class tsa::SeqView<double> &, unsigned int, double)) &tsa::ViewUtil::PadLeft, "C++: tsa::ViewUtil::PadLeft(class tsa::SeqView<double> &, class tsa::SeqView<double> &, unsigned int, double) --> void", pybind11::arg("src"), pybind11::arg("dst"), pybind11::arg("size"), pybind11::arg("value"));
		cl.def_static("PadRight", [](class tsa::SeqView<double> & a0, class tsa::SeqView<double> & a1, unsigned int const & a2) -> void { return tsa::ViewUtil::PadRight(a0, a1, a2); }, "", pybind11::arg("src"), pybind11::arg("dst"), pybind11::arg("size"));
		cl.def_static("PadRight", (void (*)(class tsa::SeqView<double> &, class tsa::SeqView<double> &, unsigned int, double)) &tsa::ViewUtil::PadRight, "C++: tsa::ViewUtil::PadRight(class tsa::SeqView<double> &, class tsa::SeqView<double> &, unsigned int, double) --> void", pybind11::arg("src"), pybind11::arg("dst"), pybind11::arg("size"), pybind11::arg("value"));
		cl.def_static("Dot", (double (*)(class tsa::SeqView<double> &, unsigned int, class tsa::SeqView<double> &, unsigned int)) &tsa::ViewUtil::Dot, "C++: tsa::ViewUtil::Dot(class tsa::SeqView<double> &, unsigned int, class tsa::SeqView<double> &, unsigned int) --> double", pybind11::arg("s1"), pybind11::arg("ch1"), pybind11::arg("s2"), pybind11::arg("ch2"));
		cl.def_static("SumChannels", (void (*)(class tsa::SeqView<double> &, class tsa::SeqView<double> &)) &tsa::ViewUtil::SumChannels, "C++: tsa::ViewUtil::SumChannels(class tsa::SeqView<double> &, class tsa::SeqView<double> &) --> void", pybind11::arg("s1"), pybind11::arg("sum"));
		cl.def_static("SumChannels", (void (*)(class tsa::SeqView<double> &, class tsa::SeqView<double> &, double, double)) &tsa::ViewUtil::SumChannels, "C++: tsa::ViewUtil::SumChannels(class tsa::SeqView<double> &, class tsa::SeqView<double> &, double, double) --> void", pybind11::arg("s1"), pybind11::arg("sum"), pybind11::arg("wfirst"), pybind11::arg("wothers"));
		cl.def_static("Fill", (void (*)(class tsa::SeqView<double> &, double)) &tsa::ViewUtil::Fill, "C++: tsa::ViewUtil::Fill(class tsa::SeqView<double> &, double) --> void", pybind11::arg("ts"), pybind11::arg("value"));
		cl.def_static("FillSeq", (void (*)(class tsa::SeqView<double> &, unsigned int, unsigned int, double)) &tsa::ViewUtil::FillSeq, "C++: tsa::ViewUtil::FillSeq(class tsa::SeqView<double> &, unsigned int, unsigned int, double) --> void", pybind11::arg("ts"), pybind11::arg("i"), pybind11::arg("j"), pybind11::arg("value"));
		cl.def_static("PeekRange", (bool (*)(class tsa::SeqView<double> &, class tsa::SeqView<double> &, double, double)) &tsa::ViewUtil::PeekRange, "Extract from the src view the data included in a given time range, tstart<=t<=tend,\n and put it in the dst view. \n\n \n the source view\n \n\n the destination view\n \n\n start time of the range\n \n\n end time for the range\n\n \n true if the range is fully inside src, false otherwise\n\nC++: tsa::ViewUtil::PeekRange(class tsa::SeqView<double> &, class tsa::SeqView<double> &, double, double) --> bool", pybind11::arg("src"), pybind11::arg("dst"), pybind11::arg("tstart"), pybind11::arg("tend"));
		cl.def_static("Sum", (void (*)(class tsa::SeqView<double> &, double, class tsa::SeqView<double> &)) &tsa::ViewUtil::Sum, "C++: tsa::ViewUtil::Sum(class tsa::SeqView<double> &, double, class tsa::SeqView<double> &) --> void", pybind11::arg("res"), pybind11::arg("scale"), pybind11::arg("ts"));
		cl.def_static("Sum", (void (*)(class tsa::SeqView<class std::complex<double> > &, double, class tsa::SeqView<class std::complex<double> > &)) &tsa::ViewUtil::Sum, "C++: tsa::ViewUtil::Sum(class tsa::SeqView<class std::complex<double> > &, double, class tsa::SeqView<class std::complex<double> > &) --> void", pybind11::arg("res"), pybind11::arg("scale"), pybind11::arg("ts"));
		cl.def_static("Inverse", (void (*)(class tsa::SeqView<double> &, class tsa::SeqView<double> &)) &tsa::ViewUtil::Inverse, "C++: tsa::ViewUtil::Inverse(class tsa::SeqView<double> &, class tsa::SeqView<double> &) --> void", pybind11::arg("ts1"), pybind11::arg("res"));
		cl.def_static("AffineTransformation", (void (*)(class tsa::SeqView<double> &, double, double, class tsa::SeqView<double> &)) &tsa::ViewUtil::AffineTransformation, "C++: tsa::ViewUtil::AffineTransformation(class tsa::SeqView<double> &, double, double, class tsa::SeqView<double> &) --> void", pybind11::arg("ts1"), pybind11::arg("a"), pybind11::arg("b"), pybind11::arg("res"));
		cl.def_static("Ratio", (void (*)(class tsa::SeqView<double> &, class tsa::SeqView<double> &, class tsa::SeqView<double> &)) &tsa::ViewUtil::Ratio, "C++: tsa::ViewUtil::Ratio(class tsa::SeqView<double> &, class tsa::SeqView<double> &, class tsa::SeqView<double> &) --> void", pybind11::arg("ts1"), pybind11::arg("ts2"), pybind11::arg("res"));
		cl.def_static("Ratio", (void (*)(class tsa::SeqView<class std::complex<double> > &, class tsa::SeqView<class std::complex<double> > &, class tsa::SeqView<class std::complex<double> > &)) &tsa::ViewUtil::Ratio, "C++: tsa::ViewUtil::Ratio(class tsa::SeqView<class std::complex<double> > &, class tsa::SeqView<class std::complex<double> > &, class tsa::SeqView<class std::complex<double> > &) --> void", pybind11::arg("ts1"), pybind11::arg("ts2"), pybind11::arg("res"));
		cl.def_static("Ratio", (void (*)(class tsa::SeqView<double> &, class tsa::SeqView<class std::complex<double> > &, class tsa::SeqView<class std::complex<double> > &)) &tsa::ViewUtil::Ratio, "C++: tsa::ViewUtil::Ratio(class tsa::SeqView<double> &, class tsa::SeqView<class std::complex<double> > &, class tsa::SeqView<class std::complex<double> > &) --> void", pybind11::arg("ts1"), pybind11::arg("ts2"), pybind11::arg("res"));
		cl.def_static("Ratio", (void (*)(class tsa::SeqView<class std::complex<double> > &, class tsa::SeqView<double> &, class tsa::SeqView<class std::complex<double> > &)) &tsa::ViewUtil::Ratio, "C++: tsa::ViewUtil::Ratio(class tsa::SeqView<class std::complex<double> > &, class tsa::SeqView<double> &, class tsa::SeqView<class std::complex<double> > &) --> void", pybind11::arg("ts1"), pybind11::arg("ts2"), pybind11::arg("res"));
		cl.def_static("ComplexToPolar", (void (*)(class tsa::SeqView<class std::complex<double> > &, class tsa::SeqView<double> &)) &tsa::ViewUtil::ComplexToPolar, "C++: tsa::ViewUtil::ComplexToPolar(class tsa::SeqView<class std::complex<double> > &, class tsa::SeqView<double> &) --> void", pybind11::arg("ts1"), pybind11::arg("ts2"));
		cl.def_static("Norm", (void (*)(class tsa::SeqView<class std::complex<double> > &, class tsa::SeqView<double> &)) &tsa::ViewUtil::Norm, "C++: tsa::ViewUtil::Norm(class tsa::SeqView<class std::complex<double> > &, class tsa::SeqView<double> &) --> void", pybind11::arg("ts1"), pybind11::arg("res"));
		cl.def_static("Abs", (void (*)(class tsa::SeqView<class std::complex<double> > &, class tsa::SeqView<double> &)) &tsa::ViewUtil::Abs, "C++: tsa::ViewUtil::Abs(class tsa::SeqView<class std::complex<double> > &, class tsa::SeqView<double> &) --> void", pybind11::arg("ts1"), pybind11::arg("res"));
		cl.def_static("Abs2", (void (*)(class tsa::SeqView<class std::complex<double> > &, class tsa::SeqView<double> &)) &tsa::ViewUtil::Abs2, "C++: tsa::ViewUtil::Abs2(class tsa::SeqView<class std::complex<double> > &, class tsa::SeqView<double> &) --> void", pybind11::arg("ts1"), pybind11::arg("res"));
		cl.def_static("Prod", (void (*)(class tsa::SeqView<double> &, class tsa::SeqView<double> &, class tsa::SeqView<double> &)) &tsa::ViewUtil::Prod, "C++: tsa::ViewUtil::Prod(class tsa::SeqView<double> &, class tsa::SeqView<double> &, class tsa::SeqView<double> &) --> void", pybind11::arg("ts1"), pybind11::arg("ts2"), pybind11::arg("res"));
		cl.def_static("Prod", (void (*)(class tsa::SeqView<double> &, class tsa::SeqView<class std::complex<double> > &, class tsa::SeqView<class std::complex<double> > &)) &tsa::ViewUtil::Prod, "C++: tsa::ViewUtil::Prod(class tsa::SeqView<double> &, class tsa::SeqView<class std::complex<double> > &, class tsa::SeqView<class std::complex<double> > &) --> void", pybind11::arg("ts1"), pybind11::arg("ts2"), pybind11::arg("res"));
		cl.def_static("ProdConj", (void (*)(class tsa::SeqView<class std::complex<double> > &, class tsa::SeqView<class std::complex<double> > &, class tsa::SeqView<class std::complex<double> > &)) &tsa::ViewUtil::ProdConj, "C++: tsa::ViewUtil::ProdConj(class tsa::SeqView<class std::complex<double> > &, class tsa::SeqView<class std::complex<double> > &, class tsa::SeqView<class std::complex<double> > &) --> void", pybind11::arg("ts1"), pybind11::arg("ts2"), pybind11::arg("res"));
		cl.def_static("Phase", (void (*)(class tsa::SeqView<class std::complex<double> > &, class tsa::SeqView<class std::complex<double> > &, class tsa::SeqView<class std::complex<double> > &)) &tsa::ViewUtil::Phase, "C++: tsa::ViewUtil::Phase(class tsa::SeqView<class std::complex<double> > &, class tsa::SeqView<class std::complex<double> > &, class tsa::SeqView<class std::complex<double> > &) --> void", pybind11::arg("ts1"), pybind11::arg("ts2"), pybind11::arg("res"));
		cl.def_static("BlockSum", (void (*)(class tsa::SeqView<class std::complex<double> > &, class tsa::SeqView<class std::complex<double> > &, int)) &tsa::ViewUtil::BlockSum, "C++: tsa::ViewUtil::BlockSum(class tsa::SeqView<class std::complex<double> > &, class tsa::SeqView<class std::complex<double> > &, int) --> void", pybind11::arg("in"), pybind11::arg("out"), pybind11::arg("bsize"));
		cl.def_static("Integrate", (class std::complex<double> (*)(class tsa::SeqView<class std::complex<double> > &, double, double)) &tsa::ViewUtil::Integrate, "C++: tsa::ViewUtil::Integrate(class tsa::SeqView<class std::complex<double> > &, double, double) --> class std::complex<double>", pybind11::arg("data"), pybind11::arg("f1"), pybind11::arg("f2"));
		cl.def_static("Integrate", (double (*)(class tsa::SeqView<double> &, double, double)) &tsa::ViewUtil::Integrate, "C++: tsa::ViewUtil::Integrate(class tsa::SeqView<double> &, double, double) --> double", pybind11::arg("data"), pybind11::arg("f1"), pybind11::arg("f2"));
		cl.def_static("DelayIntegrate", (class std::complex<double> (*)(class tsa::SeqView<class std::complex<double> > &, double, double, double)) &tsa::ViewUtil::DelayIntegrate, "C++: tsa::ViewUtil::DelayIntegrate(class tsa::SeqView<class std::complex<double> > &, double, double, double) --> class std::complex<double>", pybind11::arg("data"), pybind11::arg("tau"), pybind11::arg("f1"), pybind11::arg("f2"));
		cl.def_static("DelayIntegrate", (class std::complex<double> (*)(class tsa::SeqView<double> &, double, double, double)) &tsa::ViewUtil::DelayIntegrate, "C++: tsa::ViewUtil::DelayIntegrate(class tsa::SeqView<double> &, double, double, double) --> class std::complex<double>", pybind11::arg("data"), pybind11::arg("tau"), pybind11::arg("f1"), pybind11::arg("f2"));
		cl.def_static("Multiply", (void (*)(class tsa::SeqView<double> &, class tsa::SeqView<double> &, class tsa::SeqView<double> &)) &tsa::ViewUtil::Multiply, "C++: tsa::ViewUtil::Multiply(class tsa::SeqView<double> &, class tsa::SeqView<double> &, class tsa::SeqView<double> &) --> void", pybind11::arg("in1"), pybind11::arg("in2"), pybind11::arg("res"));
		cl.def_static("Multiply", (void (*)(class tsa::SeqView<double> &, class tsa::SeqView<class std::complex<double> > &, class tsa::SeqView<class std::complex<double> > &)) &tsa::ViewUtil::Multiply, "C++: tsa::ViewUtil::Multiply(class tsa::SeqView<double> &, class tsa::SeqView<class std::complex<double> > &, class tsa::SeqView<class std::complex<double> > &) --> void", pybind11::arg("in1"), pybind11::arg("in2"), pybind11::arg("res"));
		cl.def_static("Multiply", (void (*)(class tsa::SeqView<class std::complex<double> > &, class tsa::SeqView<class std::complex<double> > &, class tsa::SeqView<class std::complex<double> > &)) &tsa::ViewUtil::Multiply, "C++: tsa::ViewUtil::Multiply(class tsa::SeqView<class std::complex<double> > &, class tsa::SeqView<class std::complex<double> > &, class tsa::SeqView<class std::complex<double> > &) --> void", pybind11::arg("in1"), pybind11::arg("in2"), pybind11::arg("res"));
	}
}


// File: Parcor2AR.cpp
#include <AR2.hpp>
#include <AR2Parcor.hpp>
#include <ARMAFilter.hpp>
#include <ARMAView.hpp>
#include <ARMAfit.hpp>
#include <ArBurgEstimator.hpp>
#include <ArDurbinEstimator.hpp>
#include <Arma2Psd.hpp>
#include <Arma2TF.hpp>
#include <BartlettWindow.hpp>
#include <BaseWindow.hpp>
#include <LatticeView.hpp>
#include <MYWE.hpp>
#include <Parcor2AR.hpp>
#include <SeqView.hpp>
#include <boost/numeric/ublas/functional.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/matrix_expression.hpp>
#include <boost/numeric/ublas/matrix_proxy.hpp>
#include <boost/numeric/ublas/storage.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include <complex>
#include <eternity/persist.hpp>
#include <eternity/persist_xml.hpp>
#include <functional>
#include <iterator>
#include <map>
#include <memory>
#include <sstream> // __str__
#include <string>
#include <utility>

#include <functional>
#include <pybind11/pybind11.h>
#include <string>

#ifndef BINDER_PYBIND11_TYPE_CASTER
	#define BINDER_PYBIND11_TYPE_CASTER
	PYBIND11_DECLARE_HOLDER_TYPE(T, std::shared_ptr<T>)
	PYBIND11_DECLARE_HOLDER_TYPE(T, T*)
	PYBIND11_MAKE_OPAQUE(std::shared_ptr<void>)
#endif

// tsa::BaseWindow file:BaseWindow.hpp line:74
struct PyCallBack_tsa_BaseWindow : public tsa::BaseWindow {
	using tsa::BaseWindow::BaseWindow;

	void operator()(class tsa::SeqView<double> & a0) override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const tsa::BaseWindow *>(this), "__call__");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::override_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return BaseWindow::operator()(a0);
	}
	void operator()(class tsa::SeqView<double> & a0, class tsa::SeqView<double> & a1) override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const tsa::BaseWindow *>(this), "__call__");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0, a1);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::override_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return BaseWindow::operator()(a0, a1);
	}
	void Resize(unsigned int a0) override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const tsa::BaseWindow *>(this), "Resize");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::override_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return BaseWindow::Resize(a0);
	}
	void Normalize() override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const tsa::BaseWindow *>(this), "Normalize");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>();
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::override_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return BaseWindow::Normalize();
	}
	void FillWindow() override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const tsa::BaseWindow *>(this), "FillWindow");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>();
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::override_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return BaseWindow::FillWindow();
	}
};

// tsa::BartlettWindow file:BartlettWindow.hpp line:68
struct PyCallBack_tsa_BartlettWindow : public tsa::BartlettWindow {
	using tsa::BartlettWindow::BartlettWindow;

	void operator()(class tsa::SeqView<double> & a0) override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const tsa::BartlettWindow *>(this), "__call__");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::override_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return BartlettWindow::operator()(a0);
	}
	void operator()(class tsa::SeqView<double> & a0, class tsa::SeqView<double> & a1) override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const tsa::BartlettWindow *>(this), "__call__");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0, a1);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::override_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return BartlettWindow::operator()(a0, a1);
	}
	void Resize(unsigned int a0) override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const tsa::BartlettWindow *>(this), "Resize");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::override_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return BartlettWindow::Resize(a0);
	}
	void Normalize() override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const tsa::BartlettWindow *>(this), "Normalize");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>();
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::override_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return BaseWindow::Normalize();
	}
	void FillWindow() override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const tsa::BartlettWindow *>(this), "FillWindow");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>();
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::override_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return BaseWindow::FillWindow();
	}
};

void bind_Parcor2AR(std::function< pybind11::module &(std::string const &namespace_) > &M)
{
	{ // tsa::Parcor2AR file:Parcor2AR.hpp line:72
		pybind11::class_<tsa::Parcor2AR, std::shared_ptr<tsa::Parcor2AR>, tsa::AlgoBase> cl(M("tsa"), "Parcor2AR", "Estimate the AR parameters by the Parcor");
		cl.def( pybind11::init( [](){ return new tsa::Parcor2AR(); } ) );
		cl.def("assign", (class tsa::Parcor2AR & (tsa::Parcor2AR::*)(const class tsa::Parcor2AR &)) &tsa::Parcor2AR::operator=, "C++: tsa::Parcor2AR::operator=(const class tsa::Parcor2AR &) --> class tsa::Parcor2AR &", pybind11::return_value_policy::automatic, pybind11::arg(""));
	}
	{ // tsa::ArBurgEstimator file:ArBurgEstimator.hpp line:77
		pybind11::class_<tsa::ArBurgEstimator, std::shared_ptr<tsa::ArBurgEstimator>, tsa::AlgoBase> cl(M("tsa"), "ArBurgEstimator", "Estimate the Parcor and AR parameters on a sequence of data\n\n     ");
		cl.def( pybind11::init<unsigned int>(), pybind11::arg("ArOrder") );

		cl.def( pybind11::init( [](tsa::ArBurgEstimator const &o){ return new tsa::ArBurgEstimator(o); } ) );
		cl.def("Load", [](tsa::ArBurgEstimator &o, const char * a0) -> void { return o.Load(a0); }, "", pybind11::arg("filename"));
		cl.def("Load", (void (tsa::ArBurgEstimator::*)(const char *, const char *)) &tsa::ArBurgEstimator::Load, "C++: tsa::ArBurgEstimator::Load(const char *, const char *) --> void", pybind11::arg("filename"), pybind11::arg("fmt"));
		cl.def("Save", [](tsa::ArBurgEstimator &o, const char * a0) -> void { return o.Save(a0); }, "", pybind11::arg("filename"));
		cl.def("Save", (void (tsa::ArBurgEstimator::*)(const char *, const char *)) &tsa::ArBurgEstimator::Save, "C++: tsa::ArBurgEstimator::Save(const char *, const char *) --> void", pybind11::arg("filename"), pybind11::arg("fmt"));
		cl.def("xml_serialize", (void (tsa::ArBurgEstimator::*)(class eternity::xml_archive &, const char *)) &tsa::ArBurgEstimator::xml_serialize, "C++: tsa::ArBurgEstimator::xml_serialize(class eternity::xml_archive &, const char *) --> void", pybind11::arg("xml"), pybind11::arg("prefix"));
		cl.def("__call__", (void (tsa::ArBurgEstimator::*)(class tsa::SeqView<double> &, class tsa::SeqView<double> &)) &tsa::ArBurgEstimator::operator(), "Implements the estimation of the AR paramenters using the Burg method.\n\n \n Input data time series\n \n\n Whitened time series\n\nC++: tsa::ArBurgEstimator::operator()(class tsa::SeqView<double> &, class tsa::SeqView<double> &) --> void", pybind11::arg("InputData"), pybind11::arg("WhitenedData"));
		cl.def("Color", (void (tsa::ArBurgEstimator::*)(class tsa::SeqView<double> &, class tsa::SeqView<double> &)) &tsa::ArBurgEstimator::Color, "Implements the estimation of the AR paramenters using the Burg method.\n\n \n Input data time series\n \n\n Whitened time series\n\nC++: tsa::ArBurgEstimator::Color(class tsa::SeqView<double> &, class tsa::SeqView<double> &) --> void", pybind11::arg("WhitenedData"), pybind11::arg("ColoredData"));
		cl.def("__call__", (void (tsa::ArBurgEstimator::*)(class tsa::SeqView<double> &)) &tsa::ArBurgEstimator::operator(), "Implements the estimation of the AR paramenters using the Burg method.\n\n \n Input data time series\n \n\n Parcor coefficients\n\nC++: tsa::ArBurgEstimator::operator()(class tsa::SeqView<double> &) --> void", pybind11::arg("InputData"));
		cl.def("GetLatticeView", (void (tsa::ArBurgEstimator::*)(class tsa::LatticeView &)) &tsa::ArBurgEstimator::GetLatticeView, "the target lattice view\n\nC++: tsa::ArBurgEstimator::GetLatticeView(class tsa::LatticeView &) --> void", pybind11::arg("LV"));
		cl.def("GetArOrder", (unsigned int (tsa::ArBurgEstimator::*)()) &tsa::ArBurgEstimator::GetArOrder, "the Ar Order\n\nC++: tsa::ArBurgEstimator::GetArOrder() --> unsigned int");
		cl.def("GetParcor", (double (tsa::ArBurgEstimator::*)(unsigned int)) &tsa::ArBurgEstimator::GetParcor, "Get The Parcor values\n\nC++: tsa::ArBurgEstimator::GetParcor(unsigned int) --> double", pybind11::arg("j"));
		cl.def("GetAR", (double (tsa::ArBurgEstimator::*)(unsigned int)) &tsa::ArBurgEstimator::GetAR, "Get The AR values\n\nC++: tsa::ArBurgEstimator::GetAR(unsigned int) --> double", pybind11::arg("j"));
		cl.def("GetErrorForward", (double (tsa::ArBurgEstimator::*)(unsigned int)) &tsa::ArBurgEstimator::GetErrorForward, "Get the ErrorForward values\n\nC++: tsa::ArBurgEstimator::GetErrorForward(unsigned int) --> double", pybind11::arg("j"));
		cl.def("GetErrorBackward", (double (tsa::ArBurgEstimator::*)(unsigned int)) &tsa::ArBurgEstimator::GetErrorBackward, "Get the ErrorBackward values\n\nC++: tsa::ArBurgEstimator::GetErrorBackward(unsigned int) --> double", pybind11::arg("j"));
		cl.def("SetArOrder", (void (tsa::ArBurgEstimator::*)(unsigned int)) &tsa::ArBurgEstimator::SetArOrder, "the Ar order \n\nC++: tsa::ArBurgEstimator::SetArOrder(unsigned int) --> void", pybind11::arg("P"));
		cl.def("SetAR", (void (tsa::ArBurgEstimator::*)(unsigned int, double)) &tsa::ArBurgEstimator::SetAR, "C++: tsa::ArBurgEstimator::SetAR(unsigned int, double) --> void", pybind11::arg("j"), pybind11::arg("value"));
		cl.def("assign", (class tsa::ArBurgEstimator & (tsa::ArBurgEstimator::*)(const class tsa::ArBurgEstimator &)) &tsa::ArBurgEstimator::operator=, "C++: tsa::ArBurgEstimator::operator=(const class tsa::ArBurgEstimator &) --> class tsa::ArBurgEstimator &", pybind11::return_value_policy::automatic, pybind11::arg(""));
	}
	{ // tsa::ArDurbinEstimator file:ArDurbinEstimator.hpp line:78
		pybind11::class_<tsa::ArDurbinEstimator, std::shared_ptr<tsa::ArDurbinEstimator>, tsa::AlgoBase> cl(M("tsa"), "ArDurbinEstimator", "Estimate the AR coefficients and the PARCOR of a time series using its correlation function\n\n     ");
		cl.def( pybind11::init<unsigned int>(), pybind11::arg("ArOrder") );

		cl.def("GetArOrder", (unsigned int (tsa::ArDurbinEstimator::*)()) &tsa::ArDurbinEstimator::GetArOrder, "C++: tsa::ArDurbinEstimator::GetArOrder() --> unsigned int");
		cl.def("SetArOrder", (void (tsa::ArDurbinEstimator::*)(unsigned int)) &tsa::ArDurbinEstimator::SetArOrder, "C++: tsa::ArDurbinEstimator::SetArOrder(unsigned int) --> void", pybind11::arg("P"));
		cl.def("assign", (class tsa::ArDurbinEstimator & (tsa::ArDurbinEstimator::*)(const class tsa::ArDurbinEstimator &)) &tsa::ArDurbinEstimator::operator=, "C++: tsa::ArDurbinEstimator::operator=(const class tsa::ArDurbinEstimator &) --> class tsa::ArDurbinEstimator &", pybind11::return_value_policy::automatic, pybind11::arg(""));
	}
	{ // tsa::Arma2Psd file:Arma2Psd.hpp line:72
		pybind11::class_<tsa::Arma2Psd, std::shared_ptr<tsa::Arma2Psd>, tsa::AlgoBase> cl(M("tsa"), "Arma2Psd", "Estimate the PSD for a ARMA model");
		cl.def( pybind11::init( [](){ return new tsa::Arma2Psd(); } ) );
		cl.def( pybind11::init( [](tsa::Arma2Psd const &o){ return new tsa::Arma2Psd(o); } ) );
		cl.def("assign", (class tsa::Arma2Psd & (tsa::Arma2Psd::*)(const class tsa::Arma2Psd &)) &tsa::Arma2Psd::operator=, "Assignement operator\n\n \n The instance to be assigned from\n\n \n a reference to a new object\n\nC++: tsa::Arma2Psd::operator=(const class tsa::Arma2Psd &) --> class tsa::Arma2Psd &", pybind11::return_value_policy::automatic, pybind11::arg("from"));
		cl.def("__call__", (void (tsa::Arma2Psd::*)(class tsa::ARMAView &, class tsa::SeqView<double> &)) &tsa::Arma2Psd::operator(), "The P or the Q order must be greater than 0\n\n \n the Arma View\n\n \n Psd the Power Spectral density\n\nC++: tsa::Arma2Psd::operator()(class tsa::ARMAView &, class tsa::SeqView<double> &) --> void", pybind11::arg("arma"), pybind11::arg("Psd"));
	}
	{ // tsa::Arma2TF file:Arma2TF.hpp line:75
		pybind11::class_<tsa::Arma2TF, std::shared_ptr<tsa::Arma2TF>, tsa::AlgoBase> cl(M("tsa"), "Arma2TF", "Estimate the Transfer function using the ARMA parametrization\n\n     ");
		cl.def( pybind11::init( [](){ return new tsa::Arma2TF(); } ) );
		cl.def( pybind11::init( [](tsa::Arma2TF const &o){ return new tsa::Arma2TF(o); } ) );
		cl.def("assign", (class tsa::Arma2TF & (tsa::Arma2TF::*)(const class tsa::Arma2TF &)) &tsa::Arma2TF::operator=, "Assignement operator\n\n \n The instance to be assigned from\n\n \n a reference to a new object\n\nC++: tsa::Arma2TF::operator=(const class tsa::Arma2TF &) --> class tsa::Arma2TF &", pybind11::return_value_policy::automatic, pybind11::arg("from"));
		cl.def("__call__", (void (tsa::Arma2TF::*)(class tsa::ARMAView &, class tsa::SeqView<class std::complex<double> > &)) &tsa::Arma2TF::operator(), "Brief documentation for the execute method.\n\n Start of the long documentation for execute method.\n\n \n A precondition\n \n\n A postcondition\n \n\n An exception\n\n \n parameter\n\n \n a returned value\n\nC++: tsa::Arma2TF::operator()(class tsa::ARMAView &, class tsa::SeqView<class std::complex<double> > &) --> void", pybind11::arg("arma"), pybind11::arg("TF"));
	}
	{ // tsa::AR2 file:AR2.hpp line:70
		pybind11::class_<tsa::AR2, std::shared_ptr<tsa::AR2>, tsa::AlgoBase> cl(M("tsa"), "AR2", "");
		cl.def( pybind11::init<const double, const double, const double>(), pybind11::arg("f"), pybind11::arg("gamma"), pybind11::arg("h") );

		cl.def("__call__", (void (tsa::AR2::*)(class tsa::SeqView<double> &, class tsa::SeqView<double> &)) &tsa::AR2::operator(), "C++: tsa::AR2::operator()(class tsa::SeqView<double> &, class tsa::SeqView<double> &) --> void", pybind11::arg("in"), pybind11::arg("out"));
		cl.def("assign", (class tsa::AR2 & (tsa::AR2::*)(const class tsa::AR2 &)) &tsa::AR2::operator=, "C++: tsa::AR2::operator=(const class tsa::AR2 &) --> class tsa::AR2 &", pybind11::return_value_policy::automatic, pybind11::arg(""));
	}
	{ // tsa::AR2Parcor file:AR2Parcor.hpp line:71
		pybind11::class_<tsa::AR2Parcor, std::shared_ptr<tsa::AR2Parcor>, tsa::AlgoBase> cl(M("tsa"), "AR2Parcor", "Estimate the AR parameters by the Parcor");
		cl.def( pybind11::init( [](){ return new tsa::AR2Parcor(); } ) );
		cl.def("assign", (class tsa::AR2Parcor & (tsa::AR2Parcor::*)(const class tsa::AR2Parcor &)) &tsa::AR2Parcor::operator=, "C++: tsa::AR2Parcor::operator=(const class tsa::AR2Parcor &) --> class tsa::AR2Parcor &", pybind11::return_value_policy::automatic, pybind11::arg(""));
	}
	{ // tsa::ARMAFilter file:ARMAFilter.hpp line:76
		pybind11::class_<tsa::ARMAFilter, std::shared_ptr<tsa::ARMAFilter>, tsa::AlgoBase> cl(M("tsa"), "ARMAFilter", "Implement the   ARMA filtering\n\n This class implement a general ARMA filter. Given an input sequence x(n)\n and an output sequence y(n) an ARMA filter is defined by the relation\n (look at the signs definitions..)\n\n a(0) y(n) =  a(1) y(n-1) + ... + a(N) y(n-N) + b(0) x(n) + b(1) x(n-1) + .... + b(M) x(n-M)\n\n ");
		cl.def( pybind11::init<unsigned int, unsigned int, double>(), pybind11::arg("ARorder"), pybind11::arg("MAorder"), pybind11::arg("gain") );

		cl.def( pybind11::init( [](tsa::ARMAFilter const &o){ return new tsa::ARMAFilter(o); } ) );
		cl.def("SetARFilter", (void (tsa::ARMAFilter::*)(unsigned int, double)) &tsa::ARMAFilter::SetARFilter, "C++: tsa::ARMAFilter::SetARFilter(unsigned int, double) --> void", pybind11::arg("i"), pybind11::arg("AR"));
		cl.def("SetMAFilter", (void (tsa::ARMAFilter::*)(unsigned int, double)) &tsa::ARMAFilter::SetMAFilter, "C++: tsa::ARMAFilter::SetMAFilter(unsigned int, double) --> void", pybind11::arg("i"), pybind11::arg("MA"));
		cl.def("__call__", (void (tsa::ARMAFilter::*)(class tsa::SeqView<double> &, class tsa::SeqView<double> &)) &tsa::ARMAFilter::operator(), "C++: tsa::ARMAFilter::operator()(class tsa::SeqView<double> &, class tsa::SeqView<double> &) --> void", pybind11::arg("in"), pybind11::arg("out"));
		cl.def("assign", (class tsa::ARMAFilter & (tsa::ARMAFilter::*)(const class tsa::ARMAFilter &)) &tsa::ARMAFilter::operator=, "C++: tsa::ARMAFilter::operator=(const class tsa::ARMAFilter &) --> class tsa::ARMAFilter &", pybind11::return_value_policy::automatic, pybind11::arg(""));
	}
	{ // tsa::MYWE file:MYWE.hpp line:74
		pybind11::class_<tsa::MYWE, std::shared_ptr<tsa::MYWE>> cl(M("tsa"), "MYWE", "A more detailed description of MYWE");
		cl.def( pybind11::init<unsigned int, unsigned int>(), pybind11::arg("mIP"), pybind11::arg("mIQ") );

		cl.def( pybind11::init( [](tsa::MYWE const &o){ return new tsa::MYWE(o); } ) );
		cl.def("assign", (class tsa::MYWE & (tsa::MYWE::*)(const class tsa::MYWE &)) &tsa::MYWE::operator=, "Assignement operator\n\n \n The instance to be assigned from\n\n \n a reference to a new object\n\nC++: tsa::MYWE::operator=(const class tsa::MYWE &) --> class tsa::MYWE &", pybind11::return_value_policy::automatic, pybind11::arg("from"));
	}
	{ // tsa::ARMAfit file:ARMAfit.hpp line:75
		pybind11::class_<tsa::ARMAfit, std::shared_ptr<tsa::ARMAfit>> cl(M("tsa"), "ARMAfit", "implement the ARMA fit to a PSD");
		cl.def( pybind11::init<unsigned int, unsigned int>(), pybind11::arg("P"), pybind11::arg("Q") );

		cl.def( pybind11::init( [](tsa::ARMAfit const &o){ return new tsa::ARMAfit(o); } ) );
		cl.def("assign", (class tsa::ARMAfit & (tsa::ARMAfit::*)(const class tsa::ARMAfit &)) &tsa::ARMAfit::operator=, "Assignement operator\n\n \n The instance to be assigned from\n\n \n a reference to a new object\n\nC++: tsa::ARMAfit::operator=(const class tsa::ARMAfit &) --> class tsa::ARMAfit &", pybind11::return_value_policy::automatic, pybind11::arg("from"));
	}
	{ // tsa::BaseWindow file:BaseWindow.hpp line:74
		pybind11::class_<tsa::BaseWindow, std::shared_ptr<tsa::BaseWindow>, PyCallBack_tsa_BaseWindow, tsa::AlgoBase> cl(M("tsa"), "BaseWindow", "Base class for various windowing algorithms\n\n ");
		cl.def( pybind11::init<unsigned int>(), pybind11::arg("size") );

		cl.def( pybind11::init( [](PyCallBack_tsa_BaseWindow const &o){ return new PyCallBack_tsa_BaseWindow(o); } ) );
		cl.def( pybind11::init( [](tsa::BaseWindow const &o){ return new tsa::BaseWindow(o); } ) );
		cl.def_static("CrossAverage", (double (*)(class tsa::BaseWindow &, class tsa::BaseWindow &)) &tsa::BaseWindow::CrossAverage, "C++: tsa::BaseWindow::CrossAverage(class tsa::BaseWindow &, class tsa::BaseWindow &) --> double", pybind11::arg("w1"), pybind11::arg("w2"));
		cl.def_static("CrossSquareAverage", (double (*)(class tsa::BaseWindow &, class tsa::BaseWindow &)) &tsa::BaseWindow::CrossSquareAverage, "C++: tsa::BaseWindow::CrossSquareAverage(class tsa::BaseWindow &, class tsa::BaseWindow &) --> double", pybind11::arg("w1"), pybind11::arg("w2"));
		cl.def("__call__", (void (tsa::BaseWindow::*)(class tsa::SeqView<double> &)) &tsa::BaseWindow::operator(), "C++: tsa::BaseWindow::operator()(class tsa::SeqView<double> &) --> void", pybind11::arg("v1"));
		cl.def("__call__", (void (tsa::BaseWindow::*)(class tsa::SeqView<double> &, class tsa::SeqView<double> &)) &tsa::BaseWindow::operator(), "C++: tsa::BaseWindow::operator()(class tsa::SeqView<double> &, class tsa::SeqView<double> &) --> void", pybind11::arg("v1"), pybind11::arg("v2"));
		cl.def("__call__", (double (tsa::BaseWindow::*)(int)) &tsa::BaseWindow::operator(), "Get the value of the window at a given index.\n\n \n \n\n the value of the window at the given plage\n\nC++: tsa::BaseWindow::operator()(int) --> double", pybind11::arg("i"));
		cl.def("Resize", (void (tsa::BaseWindow::*)(unsigned int)) &tsa::BaseWindow::Resize, "Resize the window dimension.\n\n \n new size for the window\n\nC++: tsa::BaseWindow::Resize(unsigned int) --> void", pybind11::arg("size"));
		cl.def("GetSize", (unsigned int (tsa::BaseWindow::*)()) &tsa::BaseWindow::GetSize, "Get the actual size of the window.\n\n \n \n\n the actual size of the window\n\nC++: tsa::BaseWindow::GetSize() --> unsigned int");
		cl.def("Normalize", (void (tsa::BaseWindow::*)()) &tsa::BaseWindow::Normalize, "C++: tsa::BaseWindow::Normalize() --> void");
		cl.def("assign", (class tsa::BaseWindow & (tsa::BaseWindow::*)(const class tsa::BaseWindow &)) &tsa::BaseWindow::operator=, "C++: tsa::BaseWindow::operator=(const class tsa::BaseWindow &) --> class tsa::BaseWindow &", pybind11::return_value_policy::automatic, pybind11::arg(""));
	}
	{ // tsa::BartlettWindow file:BartlettWindow.hpp line:68
		pybind11::class_<tsa::BartlettWindow, std::shared_ptr<tsa::BartlettWindow>, PyCallBack_tsa_BartlettWindow, tsa::BaseWindow> cl(M("tsa"), "BartlettWindow", "Bartlett windowing algorithm");
		cl.def( pybind11::init<int>(), pybind11::arg("size") );

		cl.def( pybind11::init<int, const std::string &>(), pybind11::arg("size"), pybind11::arg("") );

		cl.def( pybind11::init( [](PyCallBack_tsa_BartlettWindow const &o){ return new PyCallBack_tsa_BartlettWindow(o); } ) );
		cl.def( pybind11::init( [](tsa::BartlettWindow const &o){ return new tsa::BartlettWindow(o); } ) );
		cl.def("__call__", (void (tsa::BartlettWindow::*)(class tsa::SeqView<double> &)) &tsa::BartlettWindow::operator(), "Apply the window to a given time view.\n\n \n the time view \n\nC++: tsa::BartlettWindow::operator()(class tsa::SeqView<double> &) --> void", pybind11::arg("v1"));
		cl.def("__call__", (void (tsa::BartlettWindow::*)(class tsa::SeqView<double> &, class tsa::SeqView<double> &)) &tsa::BartlettWindow::operator(), "Apply a window to an input view and write the results on a \n output view.\n\n \n the input view\n \n\n the output view\n\n         \n\nC++: tsa::BartlettWindow::operator()(class tsa::SeqView<double> &, class tsa::SeqView<double> &) --> void", pybind11::arg("v1"), pybind11::arg("v2"));
		cl.def("Resize", (void (tsa::BartlettWindow::*)(unsigned int)) &tsa::BartlettWindow::Resize, "Resize the window dimension.\n\n \n new size for the window\n\nC++: tsa::BartlettWindow::Resize(unsigned int) --> void", pybind11::arg("size"));
		cl.def("assign", (class tsa::BartlettWindow & (tsa::BartlettWindow::*)(const class tsa::BartlettWindow &)) &tsa::BartlettWindow::operator=, "C++: tsa::BartlettWindow::operator=(const class tsa::BartlettWindow &) --> class tsa::BartlettWindow &", pybind11::return_value_policy::automatic, pybind11::arg(""));
	}
}


// File: BaseFFT.cpp
#include <BaseFFT.hpp>
#include <BaseWindow.hpp>
#include <BisquareWindow.hpp>
#include <ButterworthFilter.hpp>
#include <SeqView.hpp>
#include <boost/numeric/ublas/functional.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/storage.hpp>
#include <complex>
#include <iterator>
#include <memory>
#include <sstream> // __str__
#include <string>

#include <functional>
#include <pybind11/pybind11.h>
#include <string>

#ifndef BINDER_PYBIND11_TYPE_CASTER
	#define BINDER_PYBIND11_TYPE_CASTER
	PYBIND11_DECLARE_HOLDER_TYPE(T, std::shared_ptr<T>)
	PYBIND11_DECLARE_HOLDER_TYPE(T, T*)
	PYBIND11_MAKE_OPAQUE(std::shared_ptr<void>)
#endif

// tsa::BaseFFT file:BaseFFT.hpp line:88
struct PyCallBack_tsa_BaseFFT : public tsa::BaseFFT {
	using tsa::BaseFFT::BaseFFT;

	void MakePlan() override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const tsa::BaseFFT *>(this), "MakePlan");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>();
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::override_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		pybind11::pybind11_fail("Tried to call pure virtual function \"BaseFFT::MakePlan\"");
	}
};

// tsa::BisquareWindow file:BisquareWindow.hpp line:69
struct PyCallBack_tsa_BisquareWindow : public tsa::BisquareWindow {
	using tsa::BisquareWindow::BisquareWindow;

	void operator()(class tsa::SeqView<double> & a0) override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const tsa::BisquareWindow *>(this), "__call__");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::override_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return BisquareWindow::operator()(a0);
	}
	void operator()(class tsa::SeqView<double> & a0, class tsa::SeqView<double> & a1) override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const tsa::BisquareWindow *>(this), "__call__");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0, a1);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::override_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return BisquareWindow::operator()(a0, a1);
	}
	void Resize(unsigned int a0) override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const tsa::BisquareWindow *>(this), "Resize");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::override_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return BisquareWindow::Resize(a0);
	}
	void Normalize() override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const tsa::BisquareWindow *>(this), "Normalize");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>();
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::override_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return BaseWindow::Normalize();
	}
	void FillWindow() override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const tsa::BisquareWindow *>(this), "FillWindow");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>();
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::override_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return BaseWindow::FillWindow();
	}
};

void bind_BaseFFT(std::function< pybind11::module &(std::string const &namespace_) > &M)
{
	// tsa::FFTPlanningMode file:BaseFFT.hpp line:71
	pybind11::enum_<tsa::FFTPlanningMode>(M("tsa"), "FFTPlanningMode", pybind11::arithmetic(), "Planning modes. They describe the way in which the planning\n is done. See the fftw documentation.")
		.value("ESTIMATE", tsa::ESTIMATE)
		.value("MEASURE", tsa::MEASURE)
		.value("PATIENT", tsa::PATIENT)
		.value("EXHAUSTIVE", tsa::EXHAUSTIVE)
		.export_values();

;

	// tsa::FFTsize(int) file:BaseFFT.hpp line:78
	M("tsa").def("FFTsize", (int (*)(int)) &tsa::FFTsize, "C++: tsa::FFTsize(int) --> int", pybind11::arg("n"));

	{ // tsa::BaseFFT file:BaseFFT.hpp line:88
		pybind11::class_<tsa::BaseFFT, std::shared_ptr<tsa::BaseFFT>, PyCallBack_tsa_BaseFFT, tsa::AlgoBase> cl(M("tsa"), "BaseFFT", "Base class for various FFT\n\n ");
		cl.def( pybind11::init<int, enum tsa::FFTPlanningMode, bool>(), pybind11::arg("size"), pybind11::arg("mode"), pybind11::arg("PreserveInput") );

		cl.def(pybind11::init<PyCallBack_tsa_BaseFFT const &>());
		cl.def_static("SaveWisdomOnFile", (void (*)(std::string)) &tsa::BaseFFT::SaveWisdomOnFile, "Save the actual wisdom for plan generation on a file\n\n \n the name of the file\n\nC++: tsa::BaseFFT::SaveWisdomOnFile(std::string) --> void", pybind11::arg("filename"));
		cl.def_static("LoadWisdomFromFile", (void (*)(std::string)) &tsa::BaseFFT::LoadWisdomFromFile, "Load the actual wisdom for plan generation from a file\n\n \n the name of the file\n\nC++: tsa::BaseFFT::LoadWisdomFromFile(std::string) --> void", pybind11::arg("filename"));
		cl.def_static("ForgetWisdom", (void (*)()) &tsa::BaseFFT::ForgetWisdom, "Forget wisdom\n\nC++: tsa::BaseFFT::ForgetWisdom() --> void");
		cl.def("MakePlan", (void (tsa::BaseFFT::*)()) &tsa::BaseFFT::MakePlan, "Make a new plan, with the current parameters.\n\nC++: tsa::BaseFFT::MakePlan() --> void");
		cl.def("SetPlanningMode", (void (tsa::BaseFFT::*)(enum tsa::FFTPlanningMode)) &tsa::BaseFFT::SetPlanningMode, "Set the way in which the plan is constructed. No new plan is generated.\n\n \n the requested planning mode.\n\nC++: tsa::BaseFFT::SetPlanningMode(enum tsa::FFTPlanningMode) --> void", pybind11::arg("mode"));
		cl.def("SetPreserveInput", [](tsa::BaseFFT &o) -> void { return o.SetPreserveInput(); }, "");
		cl.def("SetPreserveInput", (void (tsa::BaseFFT::*)(bool)) &tsa::BaseFFT::SetPreserveInput, "Request that the input buffer is preserved during the transformation.\n No new plan is generated.\n\n \n true (default) if input buffer must be preserved, false otherwise\n\nC++: tsa::BaseFFT::SetPreserveInput(bool) --> void", pybind11::arg("flag"));
		cl.def("assign", (class tsa::BaseFFT & (tsa::BaseFFT::*)(const class tsa::BaseFFT &)) &tsa::BaseFFT::operator=, "C++: tsa::BaseFFT::operator=(const class tsa::BaseFFT &) --> class tsa::BaseFFT &", pybind11::return_value_policy::automatic, pybind11::arg(""));
	}
	{ // tsa::BisquareWindow file:BisquareWindow.hpp line:69
		pybind11::class_<tsa::BisquareWindow, std::shared_ptr<tsa::BisquareWindow>, PyCallBack_tsa_BisquareWindow, tsa::BaseWindow> cl(M("tsa"), "BisquareWindow", "Bisquare windowing algorithm\n\n ");
		cl.def( pybind11::init<int>(), pybind11::arg("size") );

		cl.def( pybind11::init<int, const std::string &>(), pybind11::arg("size"), pybind11::arg("") );

		cl.def( pybind11::init( [](PyCallBack_tsa_BisquareWindow const &o){ return new PyCallBack_tsa_BisquareWindow(o); } ) );
		cl.def( pybind11::init( [](tsa::BisquareWindow const &o){ return new tsa::BisquareWindow(o); } ) );
		cl.def("__call__", (void (tsa::BisquareWindow::*)(class tsa::SeqView<double> &)) &tsa::BisquareWindow::operator(), "Apply the window to a given time view.\n\n \n the time view \n\nC++: tsa::BisquareWindow::operator()(class tsa::SeqView<double> &) --> void", pybind11::arg("v1"));
		cl.def("__call__", (void (tsa::BisquareWindow::*)(class tsa::SeqView<double> &, class tsa::SeqView<double> &)) &tsa::BisquareWindow::operator(), "Apply a window to an input view and write the results on a \n output view.\n\n \n the input view\n \n\n the output view\n\n         \n\nC++: tsa::BisquareWindow::operator()(class tsa::SeqView<double> &, class tsa::SeqView<double> &) --> void", pybind11::arg("v1"), pybind11::arg("v2"));
		cl.def("Resize", (void (tsa::BisquareWindow::*)(unsigned int)) &tsa::BisquareWindow::Resize, "Resize the window dimension.\n\n \n new size for the window\n\nC++: tsa::BisquareWindow::Resize(unsigned int) --> void", pybind11::arg("size"));
		cl.def("assign", (class tsa::BisquareWindow & (tsa::BisquareWindow::*)(const class tsa::BisquareWindow &)) &tsa::BisquareWindow::operator=, "C++: tsa::BisquareWindow::operator=(const class tsa::BisquareWindow &) --> class tsa::BisquareWindow &", pybind11::return_value_policy::automatic, pybind11::arg(""));
	}
	{ // tsa::ButterworthFilter file:ButterworthFilter.hpp line:74
		pybind11::class_<tsa::ButterworthFilter, std::shared_ptr<tsa::ButterworthFilter>, tsa::AlgoBase> cl(M("tsa"), "ButterworthFilter", "A generator of random normal numbers.\n\n     ");
		cl.def( pybind11::init<double, int>(), pybind11::arg("freq"), pybind11::arg("order") );

		cl.def("__call__", (void (tsa::ButterworthFilter::*)(class tsa::SeqView<class std::complex<double> > &)) &tsa::ButterworthFilter::operator(), "Write the filter on a view\n\n         \n\nC++: tsa::ButterworthFilter::operator()(class tsa::SeqView<class std::complex<double> > &) --> void", pybind11::arg("data"));
		cl.def("__call__", (void (tsa::ButterworthFilter::*)(class tsa::SeqView<class std::complex<double> > &, class tsa::SeqView<class std::complex<double> > &)) &tsa::ButterworthFilter::operator(), "Apply the filter on a view\n\n         \n\nC++: tsa::ButterworthFilter::operator()(class tsa::SeqView<class std::complex<double> > &, class tsa::SeqView<class std::complex<double> > &) --> void", pybind11::arg("datain"), pybind11::arg("dataout"));
		cl.def("assign", (class tsa::ButterworthFilter & (tsa::ButterworthFilter::*)(const class tsa::ButterworthFilter &)) &tsa::ButterworthFilter::operator=, "C++: tsa::ButterworthFilter::operator=(const class tsa::ButterworthFilter &) --> class tsa::ButterworthFilter &", pybind11::return_value_policy::automatic, pybind11::arg(""));
	}
}


// File: BLInterpolation.cpp
#include <BLInterpolation.hpp>
#include <BaseFFT.hpp>
#include <BaseWindow.hpp>
#include <Cs2HammingWindow.hpp>
#include <Cs2HannWindow.hpp>
#include <DCT.hpp>
#include <DST.hpp>
#include <FifoBuffer.hpp>
#include <IDCT.hpp>
#include <SeqView.hpp>
#include <boost/numeric/ublas/functional.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/storage.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include <eternity/persist.hpp>
#include <eternity/persist_xml.hpp>
#include <functional>
#include <iterator>
#include <map>
#include <memory>
#include <sstream> // __str__
#include <string>
#include <utility>

#include <functional>
#include <pybind11/pybind11.h>
#include <string>

#ifndef BINDER_PYBIND11_TYPE_CASTER
	#define BINDER_PYBIND11_TYPE_CASTER
	PYBIND11_DECLARE_HOLDER_TYPE(T, std::shared_ptr<T>)
	PYBIND11_DECLARE_HOLDER_TYPE(T, T*)
	PYBIND11_MAKE_OPAQUE(std::shared_ptr<void>)
#endif

// tsa::Cs2HammingWindow file:Cs2HammingWindow.hpp line:73
struct PyCallBack_tsa_Cs2HammingWindow : public tsa::Cs2HammingWindow {
	using tsa::Cs2HammingWindow::Cs2HammingWindow;

	void operator()(class tsa::SeqView<double> & a0) override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const tsa::Cs2HammingWindow *>(this), "__call__");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::override_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return Cs2HammingWindow::operator()(a0);
	}
	void operator()(class tsa::SeqView<double> & a0, class tsa::SeqView<double> & a1) override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const tsa::Cs2HammingWindow *>(this), "__call__");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0, a1);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::override_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return Cs2HammingWindow::operator()(a0, a1);
	}
	void Resize(unsigned int a0) override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const tsa::Cs2HammingWindow *>(this), "Resize");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::override_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return Cs2HammingWindow::Resize(a0);
	}
	void Normalize() override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const tsa::Cs2HammingWindow *>(this), "Normalize");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>();
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::override_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return BaseWindow::Normalize();
	}
	void FillWindow() override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const tsa::Cs2HammingWindow *>(this), "FillWindow");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>();
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::override_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return BaseWindow::FillWindow();
	}
};

// tsa::Cs2HannWindow file:Cs2HannWindow.hpp line:73
struct PyCallBack_tsa_Cs2HannWindow : public tsa::Cs2HannWindow {
	using tsa::Cs2HannWindow::Cs2HannWindow;

	void operator()(class tsa::SeqView<double> & a0) override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const tsa::Cs2HannWindow *>(this), "__call__");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::override_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return Cs2HannWindow::operator()(a0);
	}
	void operator()(class tsa::SeqView<double> & a0, class tsa::SeqView<double> & a1) override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const tsa::Cs2HannWindow *>(this), "__call__");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0, a1);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::override_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return Cs2HannWindow::operator()(a0, a1);
	}
	void Resize(unsigned int a0) override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const tsa::Cs2HannWindow *>(this), "Resize");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::override_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return Cs2HannWindow::Resize(a0);
	}
	void Normalize() override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const tsa::Cs2HannWindow *>(this), "Normalize");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>();
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::override_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return BaseWindow::Normalize();
	}
	void FillWindow() override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const tsa::Cs2HannWindow *>(this), "FillWindow");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>();
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::override_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return BaseWindow::FillWindow();
	}
};

// tsa::DCT file:DCT.hpp line:73
struct PyCallBack_tsa_DCT : public tsa::DCT {
	using tsa::DCT::DCT;

	void MakePlan() throw() override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const tsa::DCT *>(this), "MakePlan");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>();
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::override_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return DCT::MakePlan();
	}
};

// tsa::IDCT file:IDCT.hpp line:73
struct PyCallBack_tsa_IDCT : public tsa::IDCT {
	using tsa::IDCT::IDCT;

	void MakePlan() throw() override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const tsa::IDCT *>(this), "MakePlan");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>();
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::override_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return IDCT::MakePlan();
	}
};

// tsa::DST file:DST.hpp line:73
struct PyCallBack_tsa_DST : public tsa::DST {
	using tsa::DST::DST;

	void MakePlan() throw() override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const tsa::DST *>(this), "MakePlan");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>();
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::override_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return DST::MakePlan();
	}
};

void bind_BLInterpolation(std::function< pybind11::module &(std::string const &namespace_) > &M)
{
	{ // tsa::BLInterpolation file:BLInterpolation.hpp line:74
		pybind11::class_<tsa::BLInterpolation, std::shared_ptr<tsa::BLInterpolation>, tsa::AlgoBase> cl(M("tsa"), "BLInterpolation", "Band limited interpolation.\n\n ");
		cl.def( pybind11::init( [](unsigned int const & a0, unsigned int const & a1, unsigned int const & a2, unsigned int const & a3, unsigned int const & a4){ return new tsa::BLInterpolation(a0, a1, a2, a3, a4); } ), "doc" , pybind11::arg("channels"), pybind11::arg("outdata"), pybind11::arg("irate"), pybind11::arg("orate"), pybind11::arg("order"));
		cl.def( pybind11::init( [](unsigned int const & a0, unsigned int const & a1, unsigned int const & a2, unsigned int const & a3, unsigned int const & a4, double const & a5){ return new tsa::BLInterpolation(a0, a1, a2, a3, a4, a5); } ), "doc" , pybind11::arg("channels"), pybind11::arg("outdata"), pybind11::arg("irate"), pybind11::arg("orate"), pybind11::arg("order"), pybind11::arg("alpha"));
		cl.def( pybind11::init<unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, double, enum tsa::BLInterpolation::NormalizationType>(), pybind11::arg("channels"), pybind11::arg("outdata"), pybind11::arg("irate"), pybind11::arg("orate"), pybind11::arg("order"), pybind11::arg("alpha"), pybind11::arg("nt") );

		cl.def( pybind11::init( [](tsa::BLInterpolation const &o){ return new tsa::BLInterpolation(o); } ) );

		pybind11::enum_<tsa::BLInterpolation::NormalizationType>(cl, "NormalizationType", pybind11::arithmetic(), "")
			.value("NONormalization", tsa::BLInterpolation::NONormalization)
			.value("DCNormalization", tsa::BLInterpolation::DCNormalization)
			.export_values();

		cl.def("assign", (class tsa::BLInterpolation & (tsa::BLInterpolation::*)(const class tsa::BLInterpolation &)) &tsa::BLInterpolation::operator=, "Assignement operator\n\n \n The instance to be assigned from\n\n \n a reference to a new object\n\nC++: tsa::BLInterpolation::operator=(const class tsa::BLInterpolation &) --> class tsa::BLInterpolation &", pybind11::return_value_policy::automatic, pybind11::arg("from"));
		cl.def("Input", (class tsa::BLInterpolation & (tsa::BLInterpolation::*)(class tsa::SeqView<double> &)) &tsa::BLInterpolation::Input, "Add data to be resampled. This method can be called repeatedly,\n each time with a different chunk of data. The chunks are considered\n as consecutive pieces of a continuous stream.\n\n \n view containing input data\n\n \n a reference to an instance of this class\n\n \n the number of rows in indata must be equal to the number of channels \n\n         \n\nC++: tsa::BLInterpolation::Input(class tsa::SeqView<double> &) --> class tsa::BLInterpolation &", pybind11::return_value_policy::automatic, pybind11::arg("indata"));
		cl.def("Output", (class tsa::BLInterpolation & (tsa::BLInterpolation::*)(class tsa::SeqView<double> &)) &tsa::BLInterpolation::Output, "Get resampled data. If there are enough resampled data available\n these are returned, otherwise an exception is raised.\n\n \n view which will be filled with resampled data\n\n \n a reference to an instance of this class\n\n \n no_data_available there are not enough resampled data available\n\n \n if no exception is raised outdata has a number of rows equal to the number\n of channels and a number of columns equal to the number of returned data\n\n         \n\nC++: tsa::BLInterpolation::Output(class tsa::SeqView<double> &) --> class tsa::BLInterpolation &", pybind11::return_value_policy::automatic, pybind11::arg("outdata"));
		cl.def("GetDataAvailable", (long (tsa::BLInterpolation::*)()) &tsa::BLInterpolation::GetDataAvailable, "C++: tsa::BLInterpolation::GetDataAvailable() --> long");
		cl.def("GetStartTime", (double (tsa::BLInterpolation::*)()) &tsa::BLInterpolation::GetStartTime, "Start time of the next sequence of resampled data.\n\n \n \n\n the start time of the next sequence of resampled data\n\nC++: tsa::BLInterpolation::GetStartTime() --> double");
	}
	{ // tsa::Cs2HammingWindow file:Cs2HammingWindow.hpp line:73
		pybind11::class_<tsa::Cs2HammingWindow, std::shared_ptr<tsa::Cs2HammingWindow>, PyCallBack_tsa_Cs2HammingWindow, tsa::BaseWindow> cl(M("tsa"), "Cs2HammingWindow", "Cs2Hamming windowing algorithm");
		cl.def( pybind11::init<int>(), pybind11::arg("size") );

		cl.def( pybind11::init<int, const std::string &>(), pybind11::arg("size"), pybind11::arg("") );

		cl.def( pybind11::init( [](PyCallBack_tsa_Cs2HammingWindow const &o){ return new PyCallBack_tsa_Cs2HammingWindow(o); } ) );
		cl.def( pybind11::init( [](tsa::Cs2HammingWindow const &o){ return new tsa::Cs2HammingWindow(o); } ) );
		cl.def("__call__", (void (tsa::Cs2HammingWindow::*)(class tsa::SeqView<double> &)) &tsa::Cs2HammingWindow::operator(), "Apply the window to a given time view.\n\n \n the time view \n\nC++: tsa::Cs2HammingWindow::operator()(class tsa::SeqView<double> &) --> void", pybind11::arg("v1"));
		cl.def("__call__", (void (tsa::Cs2HammingWindow::*)(class tsa::SeqView<double> &, class tsa::SeqView<double> &)) &tsa::Cs2HammingWindow::operator(), "Apply a window to an input view and write the results on a \n output view.\n\n \n the input view\n \n\n the output view\n\n         \n\nC++: tsa::Cs2HammingWindow::operator()(class tsa::SeqView<double> &, class tsa::SeqView<double> &) --> void", pybind11::arg("v1"), pybind11::arg("v2"));
		cl.def("Resize", (void (tsa::Cs2HammingWindow::*)(unsigned int)) &tsa::Cs2HammingWindow::Resize, "Resize the window dimension.\n\n \n new size for the window\n\nC++: tsa::Cs2HammingWindow::Resize(unsigned int) --> void", pybind11::arg("size"));
		cl.def("__call__", (double (tsa::Cs2HammingWindow::*)(int)) &tsa::Cs2HammingWindow::operator(), "Get the value of the window at a given index.\n\n \n \n\n the value of the window at the given plage\n\nC++: tsa::Cs2HammingWindow::operator()(int) --> double", pybind11::arg("i"));
		cl.def("assign", (class tsa::Cs2HammingWindow & (tsa::Cs2HammingWindow::*)(const class tsa::Cs2HammingWindow &)) &tsa::Cs2HammingWindow::operator=, "C++: tsa::Cs2HammingWindow::operator=(const class tsa::Cs2HammingWindow &) --> class tsa::Cs2HammingWindow &", pybind11::return_value_policy::automatic, pybind11::arg(""));
	}
	{ // tsa::Cs2HannWindow file:Cs2HannWindow.hpp line:73
		pybind11::class_<tsa::Cs2HannWindow, std::shared_ptr<tsa::Cs2HannWindow>, PyCallBack_tsa_Cs2HannWindow, tsa::BaseWindow> cl(M("tsa"), "Cs2HannWindow", "Cs2Hann windowing algorithm");
		cl.def( pybind11::init<int>(), pybind11::arg("size") );

		cl.def( pybind11::init<int, const std::string &>(), pybind11::arg("size"), pybind11::arg("") );

		cl.def( pybind11::init( [](PyCallBack_tsa_Cs2HannWindow const &o){ return new PyCallBack_tsa_Cs2HannWindow(o); } ) );
		cl.def( pybind11::init( [](tsa::Cs2HannWindow const &o){ return new tsa::Cs2HannWindow(o); } ) );
		cl.def("__call__", (void (tsa::Cs2HannWindow::*)(class tsa::SeqView<double> &)) &tsa::Cs2HannWindow::operator(), "Apply the window to a given time view.\n\n \n the time view \n\nC++: tsa::Cs2HannWindow::operator()(class tsa::SeqView<double> &) --> void", pybind11::arg("v1"));
		cl.def("__call__", (void (tsa::Cs2HannWindow::*)(class tsa::SeqView<double> &, class tsa::SeqView<double> &)) &tsa::Cs2HannWindow::operator(), "Apply a window to an input view and write the results on a \n output view.\n\n \n the input view\n \n\n the output view\n\n         \n\nC++: tsa::Cs2HannWindow::operator()(class tsa::SeqView<double> &, class tsa::SeqView<double> &) --> void", pybind11::arg("v1"), pybind11::arg("v2"));
		cl.def("Resize", (void (tsa::Cs2HannWindow::*)(unsigned int)) &tsa::Cs2HannWindow::Resize, "Resize the window dimension.\n\n \n new size for the window\n\nC++: tsa::Cs2HannWindow::Resize(unsigned int) --> void", pybind11::arg("size"));
		cl.def("assign", (class tsa::Cs2HannWindow & (tsa::Cs2HannWindow::*)(const class tsa::Cs2HannWindow &)) &tsa::Cs2HannWindow::operator=, "C++: tsa::Cs2HannWindow::operator=(const class tsa::Cs2HannWindow &) --> class tsa::Cs2HannWindow &", pybind11::return_value_policy::automatic, pybind11::arg(""));
	}
	{ // tsa::DCT file:DCT.hpp line:73
		pybind11::class_<tsa::DCT, std::shared_ptr<tsa::DCT>, PyCallBack_tsa_DCT, tsa::BaseFFT> cl(M("tsa"), "DCT", "Multichannel Discrete Cosine Transform.");
		cl.def( pybind11::init( [](){ return new tsa::DCT(); }, [](){ return new PyCallBack_tsa_DCT(); } ), "doc");
		cl.def( pybind11::init( [](int const & a0){ return new tsa::DCT(a0); }, [](int const & a0){ return new PyCallBack_tsa_DCT(a0); } ), "doc");
		cl.def( pybind11::init( [](int const & a0, enum tsa::FFTPlanningMode const & a1){ return new tsa::DCT(a0, a1); }, [](int const & a0, enum tsa::FFTPlanningMode const & a1){ return new PyCallBack_tsa_DCT(a0, a1); } ), "doc");
		cl.def( pybind11::init<int, enum tsa::FFTPlanningMode, bool>(), pybind11::arg("size"), pybind11::arg("mode"), pybind11::arg("PreserveInput") );

		cl.def( pybind11::init( [](PyCallBack_tsa_DCT const &o){ return new PyCallBack_tsa_DCT(o); } ) );
		cl.def( pybind11::init( [](tsa::DCT const &o){ return new tsa::DCT(o); } ) );
		cl.def("__call__", (void (tsa::DCT::*)(class tsa::SeqView<double> &, class tsa::SeqView<double> &)) &tsa::DCT::operator(), "Apply the transformation on the data\n\n \n a reference to the buffer containing the input data\n \n\n a reference to the buffer containing the input data\n\n \n a reference to this instance of the class\n\nC++: tsa::DCT::operator()(class tsa::SeqView<double> &, class tsa::SeqView<double> &) --> void", pybind11::arg("in"), pybind11::arg("out"));
		cl.def("MakePlan", (void (tsa::DCT::*)()) &tsa::DCT::MakePlan, "Make a new plan, with the current parameters.\n\n \n std::runtime_error The new plan cannot be created\n\nC++: tsa::DCT::MakePlan() --> void");
		cl.def("assign", (class tsa::DCT & (tsa::DCT::*)(const class tsa::DCT &)) &tsa::DCT::operator=, "C++: tsa::DCT::operator=(const class tsa::DCT &) --> class tsa::DCT &", pybind11::return_value_policy::automatic, pybind11::arg(""));
	}
	{ // tsa::IDCT file:IDCT.hpp line:73
		pybind11::class_<tsa::IDCT, std::shared_ptr<tsa::IDCT>, PyCallBack_tsa_IDCT, tsa::BaseFFT> cl(M("tsa"), "IDCT", "Multichannel Discrete Cosine Transform.");
		cl.def( pybind11::init( [](){ return new tsa::IDCT(); }, [](){ return new PyCallBack_tsa_IDCT(); } ), "doc");
		cl.def( pybind11::init( [](int const & a0){ return new tsa::IDCT(a0); }, [](int const & a0){ return new PyCallBack_tsa_IDCT(a0); } ), "doc");
		cl.def( pybind11::init( [](int const & a0, enum tsa::FFTPlanningMode const & a1){ return new tsa::IDCT(a0, a1); }, [](int const & a0, enum tsa::FFTPlanningMode const & a1){ return new PyCallBack_tsa_IDCT(a0, a1); } ), "doc");
		cl.def( pybind11::init<int, enum tsa::FFTPlanningMode, bool>(), pybind11::arg("size"), pybind11::arg("mode"), pybind11::arg("PreserveInput") );

		cl.def( pybind11::init( [](PyCallBack_tsa_IDCT const &o){ return new PyCallBack_tsa_IDCT(o); } ) );
		cl.def( pybind11::init( [](tsa::IDCT const &o){ return new tsa::IDCT(o); } ) );
		cl.def("__call__", (void (tsa::IDCT::*)(class tsa::SeqView<double> &, class tsa::SeqView<double> &)) &tsa::IDCT::operator(), "Apply the transformation on the data\n\n \n a reference to the buffer containing the input data\n \n\n a reference to the buffer containing the input data\n\n \n a reference to this instance of the class\n\nC++: tsa::IDCT::operator()(class tsa::SeqView<double> &, class tsa::SeqView<double> &) --> void", pybind11::arg("in"), pybind11::arg("out"));
		cl.def("MakePlan", (void (tsa::IDCT::*)()) &tsa::IDCT::MakePlan, "Make a new plan, with the current parameters.\n\n \n std::runtime_error The new plan cannot be created\n\nC++: tsa::IDCT::MakePlan() --> void");
		cl.def("assign", (class tsa::IDCT & (tsa::IDCT::*)(const class tsa::IDCT &)) &tsa::IDCT::operator=, "C++: tsa::IDCT::operator=(const class tsa::IDCT &) --> class tsa::IDCT &", pybind11::return_value_policy::automatic, pybind11::arg(""));
	}
	{ // tsa::DST file:DST.hpp line:73
		pybind11::class_<tsa::DST, std::shared_ptr<tsa::DST>, PyCallBack_tsa_DST, tsa::BaseFFT> cl(M("tsa"), "DST", "Multichannel Discrete Sine Transform.");
		cl.def( pybind11::init( [](){ return new tsa::DST(); }, [](){ return new PyCallBack_tsa_DST(); } ), "doc");
		cl.def( pybind11::init( [](int const & a0){ return new tsa::DST(a0); }, [](int const & a0){ return new PyCallBack_tsa_DST(a0); } ), "doc");
		cl.def( pybind11::init( [](int const & a0, enum tsa::FFTPlanningMode const & a1){ return new tsa::DST(a0, a1); }, [](int const & a0, enum tsa::FFTPlanningMode const & a1){ return new PyCallBack_tsa_DST(a0, a1); } ), "doc");
		cl.def( pybind11::init<int, enum tsa::FFTPlanningMode, bool>(), pybind11::arg("size"), pybind11::arg("mode"), pybind11::arg("PreserveInput") );

		cl.def( pybind11::init( [](PyCallBack_tsa_DST const &o){ return new PyCallBack_tsa_DST(o); } ) );
		cl.def( pybind11::init( [](tsa::DST const &o){ return new tsa::DST(o); } ) );
		cl.def("__call__", (void (tsa::DST::*)(class tsa::SeqView<double> &, class tsa::SeqView<double> &)) &tsa::DST::operator(), "Apply the transformation on the data\n\n \n a reference to the buffer containing the input data\n \n\n a reference to the buffer containing the input data\n\n \n a reference to this instance of the class\n\nC++: tsa::DST::operator()(class tsa::SeqView<double> &, class tsa::SeqView<double> &) --> void", pybind11::arg("in"), pybind11::arg("out"));
		cl.def("MakePlan", (void (tsa::DST::*)()) &tsa::DST::MakePlan, "Make a new plan, with the current parameters.\n\n \n std::runtime_error The new plan cannot be created\n\nC++: tsa::DST::MakePlan() --> void");
		cl.def("assign", (class tsa::DST & (tsa::DST::*)(const class tsa::DST &)) &tsa::DST::operator=, "C++: tsa::DST::operator=(const class tsa::DST &) --> class tsa::DST &", pybind11::return_value_policy::automatic, pybind11::arg(""));
	}
	{ // tsa::FifoBuffer file:FifoBuffer.hpp line:76
		pybind11::class_<tsa::FifoBuffer, std::shared_ptr<tsa::FifoBuffer>> cl(M("tsa"), "FifoBuffer", "Band limited interpolation.\n\n ");
		cl.def( pybind11::init<unsigned int>(), pybind11::arg("channels") );

		cl.def( pybind11::init( [](tsa::FifoBuffer const &o){ return new tsa::FifoBuffer(o); } ) );
		cl.def("assign", (class tsa::FifoBuffer & (tsa::FifoBuffer::*)(const class tsa::FifoBuffer &)) &tsa::FifoBuffer::operator=, "Assignement operator\n\n \n The instance to be assigned from\n\n \n a reference to a new object\n\nC++: tsa::FifoBuffer::operator=(const class tsa::FifoBuffer &) --> class tsa::FifoBuffer &", pybind11::return_value_policy::automatic, pybind11::arg("from"));
		cl.def("AddPoint", (void (tsa::FifoBuffer::*)()) &tsa::FifoBuffer::AddPoint, "Insert in the back of the buffer a single uninitialized data\n\n         \n\nC++: tsa::FifoBuffer::AddPoint() --> void");
		cl.def("Back", (double & (tsa::FifoBuffer::*)(unsigned int)) &tsa::FifoBuffer::Back, "Access to the last inserted data\n\n \n the index inside the last inserted data\n\n \n reference to the last inserted data\n\nC++: tsa::FifoBuffer::Back(unsigned int) --> double &", pybind11::return_value_policy::automatic, pybind11::arg("i"));
		cl.def("DelPoints", (void (tsa::FifoBuffer::*)(int)) &tsa::FifoBuffer::DelPoints, "Delete some data from the front of the buffer.\n\n \n number of data to delete\n\nC++: tsa::FifoBuffer::DelPoints(int) --> void", pybind11::arg("n"));
		cl.def("Size", (unsigned int (tsa::FifoBuffer::*)()) &tsa::FifoBuffer::Size, "Get the present size of the buffer.\n\n \n \n\n the size of the buffer\n\nC++: tsa::FifoBuffer::Size() --> unsigned int");
		cl.def("__call__", (double & (tsa::FifoBuffer::*)(int, int)) &tsa::FifoBuffer::operator(), "Access to the buffer data.\n\n \n buffer row\n \n\n buffer column\n\n \n the data\n\nC++: tsa::FifoBuffer::operator()(int, int) --> double &", pybind11::return_value_policy::automatic, pybind11::arg("r"), pybind11::arg("c"));
		cl.def("Load", [](tsa::FifoBuffer &o, const char * a0) -> void { return o.Load(a0); }, "", pybind11::arg("filename"));
		cl.def("Load", (void (tsa::FifoBuffer::*)(const char *, const char *)) &tsa::FifoBuffer::Load, "C++: tsa::FifoBuffer::Load(const char *, const char *) --> void", pybind11::arg("filename"), pybind11::arg("fmt"));
		cl.def("Save", [](tsa::FifoBuffer &o, const char * a0) -> void { return o.Save(a0); }, "", pybind11::arg("filename"));
		cl.def("Save", (void (tsa::FifoBuffer::*)(const char *, const char *)) &tsa::FifoBuffer::Save, "C++: tsa::FifoBuffer::Save(const char *, const char *) --> void", pybind11::arg("filename"), pybind11::arg("fmt"));
		cl.def("xml_serialize", (void (tsa::FifoBuffer::*)(class eternity::xml_archive &, const char *)) &tsa::FifoBuffer::xml_serialize, "C++: tsa::FifoBuffer::xml_serialize(class eternity::xml_archive &, const char *) --> void", pybind11::arg("xml"), pybind11::arg("prefix"));
	}
}


// File: DoubleWhitening.cpp
#include <BaseFFT.hpp>
#include <BaseWindow.hpp>
#include <ClusterizedEventFullFeatured.hpp>
#include <DoubleWhitening.hpp>
#include <EventDescription.hpp>
#include <EventFullFeatured.hpp>
#include <InverseRealFFT.hpp>
#include <KaiserWindow.hpp>
#include <LatticeFilter.hpp>
#include <LatticeView.hpp>
#include <SeqView.hpp>
#include <boost/numeric/ublas/functional.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/matrix_expression.hpp>
#include <boost/numeric/ublas/matrix_proxy.hpp>
#include <boost/numeric/ublas/storage.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include <complex>
#include <eternity/persist.hpp>
#include <eternity/persist_xml.hpp>
#include <functional>
#include <iterator>
#include <map>
#include <memory>
#include <sstream> // __str__
#include <string>
#include <utility>

#include <functional>
#include <pybind11/pybind11.h>
#include <string>

#ifndef BINDER_PYBIND11_TYPE_CASTER
	#define BINDER_PYBIND11_TYPE_CASTER
	PYBIND11_DECLARE_HOLDER_TYPE(T, std::shared_ptr<T>)
	PYBIND11_DECLARE_HOLDER_TYPE(T, T*)
	PYBIND11_MAKE_OPAQUE(std::shared_ptr<void>)
#endif

// tsa::InverseRealFFT file:InverseRealFFT.hpp line:66
struct PyCallBack_tsa_InverseRealFFT : public tsa::InverseRealFFT {
	using tsa::InverseRealFFT::InverseRealFFT;

	void MakePlan() throw() override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const tsa::InverseRealFFT *>(this), "MakePlan");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>();
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::override_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return InverseRealFFT::MakePlan();
	}
};

// tsa::KaiserWindow file:KaiserWindow.hpp line:77
struct PyCallBack_tsa_KaiserWindow : public tsa::KaiserWindow {
	using tsa::KaiserWindow::KaiserWindow;

	void operator()(class tsa::SeqView<double> & a0) override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const tsa::KaiserWindow *>(this), "__call__");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::override_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return KaiserWindow::operator()(a0);
	}
	void operator()(class tsa::SeqView<double> & a0, class tsa::SeqView<double> & a1) override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const tsa::KaiserWindow *>(this), "__call__");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0, a1);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::override_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return KaiserWindow::operator()(a0, a1);
	}
	void Resize(unsigned int a0) override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const tsa::KaiserWindow *>(this), "Resize");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::override_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return KaiserWindow::Resize(a0);
	}
	void Normalize() override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const tsa::KaiserWindow *>(this), "Normalize");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>();
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::override_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return BaseWindow::Normalize();
	}
	void FillWindow() override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const tsa::KaiserWindow *>(this), "FillWindow");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>();
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::override_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return BaseWindow::FillWindow();
	}
};

void bind_DoubleWhitening(std::function< pybind11::module &(std::string const &namespace_) > &M)
{
	{ // tsa::DoubleWhitening file:DoubleWhitening.hpp line:81
		pybind11::class_<tsa::DoubleWhitening, std::shared_ptr<tsa::DoubleWhitening>, tsa::AlgoBase> cl(M("tsa"), "DoubleWhitening", "A more detailed description of DoubleWhitening\n\n     \n Implement the double whitening filter in time domain\n\n     ");
		cl.def( pybind11::init<class tsa::LatticeView &, unsigned int, unsigned int>(), pybind11::arg("LV"), pybind11::arg("OutputSize"), pybind11::arg("ExtraSize") );

		cl.def( pybind11::init( [](tsa::DoubleWhitening const &o){ return new tsa::DoubleWhitening(o); } ) );
		cl.def("init", (void (tsa::DoubleWhitening::*)(class tsa::LatticeView &)) &tsa::DoubleWhitening::init, "C++: tsa::DoubleWhitening::init(class tsa::LatticeView &) --> void", pybind11::arg("LV"));
		cl.def("__lshift__", (void (tsa::DoubleWhitening::*)(class tsa::SeqView<double> &)) &tsa::DoubleWhitening::operator<<, "Declaration of execute operation\n\n \n Matrix containing Time Series\n \n\n Matrix containing the WhitenedData\n\nC++: tsa::DoubleWhitening::operator<<(class tsa::SeqView<double> &) --> void", pybind11::arg("Data"));
		cl.def("__rshift__", (void (tsa::DoubleWhitening::*)(class tsa::SeqView<double> &)) &tsa::DoubleWhitening::operator>>, "C++: tsa::DoubleWhitening::operator>>(class tsa::SeqView<double> &) --> void", pybind11::arg("outdata"));
		cl.def("Input", (class tsa::DoubleWhitening & (tsa::DoubleWhitening::*)(class tsa::SeqView<double> &)) &tsa::DoubleWhitening::Input, "C++: tsa::DoubleWhitening::Input(class tsa::SeqView<double> &) --> class tsa::DoubleWhitening &", pybind11::return_value_policy::automatic, pybind11::arg("Data"));
		cl.def("Output", (class tsa::DoubleWhitening & (tsa::DoubleWhitening::*)(class tsa::SeqView<double> &)) &tsa::DoubleWhitening::Output, "C++: tsa::DoubleWhitening::Output(class tsa::SeqView<double> &) --> class tsa::DoubleWhitening &", pybind11::return_value_policy::automatic, pybind11::arg("outdata"));
		cl.def("__call__", (void (tsa::DoubleWhitening::*)(class tsa::SeqView<double> &, class tsa::SeqView<double> &)) &tsa::DoubleWhitening::operator(), "C++: tsa::DoubleWhitening::operator()(class tsa::SeqView<double> &, class tsa::SeqView<double> &) --> void", pybind11::arg("InputData"), pybind11::arg("OutData"));
		cl.def("Load", [](tsa::DoubleWhitening &o, const char * a0) -> void { return o.Load(a0); }, "", pybind11::arg("filename"));
		cl.def("Load", (void (tsa::DoubleWhitening::*)(const char *, const char *)) &tsa::DoubleWhitening::Load, "C++: tsa::DoubleWhitening::Load(const char *, const char *) --> void", pybind11::arg("filename"), pybind11::arg("fmt"));
		cl.def("Save", [](tsa::DoubleWhitening &o, const char * a0) -> void { return o.Save(a0); }, "", pybind11::arg("filename"));
		cl.def("Save", (void (tsa::DoubleWhitening::*)(const char *, const char *)) &tsa::DoubleWhitening::Save, "C++: tsa::DoubleWhitening::Save(const char *, const char *) --> void", pybind11::arg("filename"), pybind11::arg("fmt"));
		cl.def("xml_serialize", (void (tsa::DoubleWhitening::*)(class eternity::xml_archive &, const char *)) &tsa::DoubleWhitening::xml_serialize, "C++: tsa::DoubleWhitening::xml_serialize(class eternity::xml_archive &, const char *) --> void", pybind11::arg("xml"), pybind11::arg("p"));
		cl.def("assign", (class tsa::DoubleWhitening & (tsa::DoubleWhitening::*)(const class tsa::DoubleWhitening &)) &tsa::DoubleWhitening::operator=, "C++: tsa::DoubleWhitening::operator=(const class tsa::DoubleWhitening &) --> class tsa::DoubleWhitening &", pybind11::return_value_policy::automatic, pybind11::arg(""));
	}
	{ // tsa::EventFull file:EventDescription.hpp line:81
		pybind11::class_<tsa::EventFull, std::shared_ptr<tsa::EventFull>> cl(M("tsa"), "EventFull", "");
		cl.def( pybind11::init( [](){ return new tsa::EventFull(); } ) );
		cl.def( pybind11::init( [](tsa::EventFull const &o){ return new tsa::EventFull(o); } ) );
		cl.def_readwrite("mTime", &tsa::EventFull::mTime);
		cl.def_readwrite("mSNR", &tsa::EventFull::mSNR);
		cl.def_readwrite("mCmax", &tsa::EventFull::mCmax);
		cl.def_readwrite("mlevel", &tsa::EventFull::mlevel);
		cl.def_readwrite("mWave", &tsa::EventFull::mWave);
		cl.def("assign", (class tsa::EventFull & (tsa::EventFull::*)(const class tsa::EventFull &)) &tsa::EventFull::operator=, "C++: tsa::EventFull::operator=(const class tsa::EventFull &) --> class tsa::EventFull &", pybind11::return_value_policy::automatic, pybind11::arg("from"));
	}
	{ // tsa::Event file:EventDescription.hpp line:117
		pybind11::class_<tsa::Event, std::shared_ptr<tsa::Event>> cl(M("tsa"), "Event", "");
		cl.def( pybind11::init( [](){ return new tsa::Event(); } ) );
		cl.def( pybind11::init( [](tsa::Event const &o){ return new tsa::Event(o); } ) );
		cl.def_readwrite("mTime", &tsa::Event::mTime);
		cl.def_readwrite("mSNR", &tsa::Event::mSNR);
		cl.def_readwrite("mWave", &tsa::Event::mWave);
		cl.def("assign", (class tsa::Event & (tsa::Event::*)(const class tsa::Event &)) &tsa::Event::operator=, "C++: tsa::Event::operator=(const class tsa::Event &) --> class tsa::Event &", pybind11::return_value_policy::automatic, pybind11::arg("from"));
	}
	{ // tsa::ClusterizedEvent file:EventDescription.hpp line:153
		pybind11::class_<tsa::ClusterizedEvent, std::shared_ptr<tsa::ClusterizedEvent>> cl(M("tsa"), "ClusterizedEvent", "");
		cl.def( pybind11::init( [](){ return new tsa::ClusterizedEvent(); } ) );
		cl.def( pybind11::init( [](tsa::ClusterizedEvent const &o){ return new tsa::ClusterizedEvent(o); } ) );
		cl.def_readwrite("mTime", &tsa::ClusterizedEvent::mTime);
		cl.def_readwrite("mLenght", &tsa::ClusterizedEvent::mLenght);
		cl.def_readwrite("mSNR", &tsa::ClusterizedEvent::mSNR);
		cl.def_readwrite("mWave", &tsa::ClusterizedEvent::mWave);
		cl.def("assign", (class tsa::ClusterizedEvent & (tsa::ClusterizedEvent::*)(const class tsa::ClusterizedEvent &)) &tsa::ClusterizedEvent::operator=, "C++: tsa::ClusterizedEvent::operator=(const class tsa::ClusterizedEvent &) --> class tsa::ClusterizedEvent &", pybind11::return_value_policy::automatic, pybind11::arg("from"));
	}
	{ // tsa::ClusterizedEventFull file:EventDescription.hpp line:182
		pybind11::class_<tsa::ClusterizedEventFull, std::shared_ptr<tsa::ClusterizedEventFull>> cl(M("tsa"), "ClusterizedEventFull", "");
		cl.def( pybind11::init( [](){ return new tsa::ClusterizedEventFull(); } ) );
		cl.def( pybind11::init( [](tsa::ClusterizedEventFull const &o){ return new tsa::ClusterizedEventFull(o); } ) );
		cl.def_readwrite("mTime", &tsa::ClusterizedEventFull::mTime);
		cl.def_readwrite("mTimeMax", &tsa::ClusterizedEventFull::mTimeMax);
		cl.def_readwrite("mLenght", &tsa::ClusterizedEventFull::mLenght);
		cl.def_readwrite("mSNR", &tsa::ClusterizedEventFull::mSNR);
		cl.def_readwrite("mCmax", &tsa::ClusterizedEventFull::mCmax);
		cl.def_readwrite("mlevel", &tsa::ClusterizedEventFull::mlevel);
		cl.def_readwrite("mWave", &tsa::ClusterizedEventFull::mWave);
		cl.def("assign", (class tsa::ClusterizedEventFull & (tsa::ClusterizedEventFull::*)(const class tsa::ClusterizedEventFull &)) &tsa::ClusterizedEventFull::operator=, "C++: tsa::ClusterizedEventFull::operator=(const class tsa::ClusterizedEventFull &) --> class tsa::ClusterizedEventFull &", pybind11::return_value_policy::automatic, pybind11::arg("from"));
	}
	{ // tsa::EventFullFeatured file:EventFullFeatured.hpp line:82
		pybind11::class_<tsa::EventFullFeatured, std::shared_ptr<tsa::EventFullFeatured>> cl(M("tsa"), "EventFullFeatured", "");
		cl.def( pybind11::init<unsigned int>(), pybind11::arg("NumCoeff") );

		cl.def( pybind11::init( [](tsa::EventFullFeatured const &o){ return new tsa::EventFullFeatured(o); } ) );
		cl.def_readwrite("mTime", &tsa::EventFullFeatured::mTime);
		cl.def_readwrite("mSNR", &tsa::EventFullFeatured::mSNR);
		cl.def_readwrite("mCoeff", &tsa::EventFullFeatured::mCoeff);
		cl.def_readwrite("mlevel", &tsa::EventFullFeatured::mlevel);
		cl.def_readwrite("mWave", &tsa::EventFullFeatured::mWave);
		cl.def("assign", (void (tsa::EventFullFeatured::*)(const class tsa::EventFullFeatured &)) &tsa::EventFullFeatured::operator=, "C++: tsa::EventFullFeatured::operator=(const class tsa::EventFullFeatured &) --> void", pybind11::arg("from"));
		cl.def("EVcopy", (void (tsa::EventFullFeatured::*)(const class tsa::EventFullFeatured &)) &tsa::EventFullFeatured::EVcopy, "C++: tsa::EventFullFeatured::EVcopy(const class tsa::EventFullFeatured &) --> void", pybind11::arg("from"));
		cl.def("outprint", (void (tsa::EventFullFeatured::*)()) &tsa::EventFullFeatured::outprint, "C++: tsa::EventFullFeatured::outprint() --> void");
		cl.def("SetCoeff", (void (tsa::EventFullFeatured::*)(int, double)) &tsa::EventFullFeatured::SetCoeff, "C++: tsa::EventFullFeatured::SetCoeff(int, double) --> void", pybind11::arg("i"), pybind11::arg("v"));
		cl.def("GetCoeff", (double (tsa::EventFullFeatured::*)(unsigned int)) &tsa::EventFullFeatured::GetCoeff, "C++: tsa::EventFullFeatured::GetCoeff(unsigned int) --> double", pybind11::arg("i"));
	}
	{ // tsa::ClusterizedEventFullFeatured file:ClusterizedEventFullFeatured.hpp line:71
		pybind11::class_<tsa::ClusterizedEventFullFeatured, std::shared_ptr<tsa::ClusterizedEventFullFeatured>> cl(M("tsa"), "ClusterizedEventFullFeatured", "");
		cl.def( pybind11::init<unsigned int>(), pybind11::arg("NumCoeff") );

		cl.def( pybind11::init( [](tsa::ClusterizedEventFullFeatured const &o){ return new tsa::ClusterizedEventFullFeatured(o); } ) );
		cl.def_readwrite("mTime", &tsa::ClusterizedEventFullFeatured::mTime);
		cl.def_readwrite("mTimeMax", &tsa::ClusterizedEventFullFeatured::mTimeMax);
		cl.def_readwrite("mLenght", &tsa::ClusterizedEventFullFeatured::mLenght);
		cl.def_readwrite("mSNR", &tsa::ClusterizedEventFullFeatured::mSNR);
		cl.def_readwrite("mCoeff", &tsa::ClusterizedEventFullFeatured::mCoeff);
		cl.def_readwrite("mlevel", &tsa::ClusterizedEventFullFeatured::mlevel);
		cl.def_readwrite("mWave", &tsa::ClusterizedEventFullFeatured::mWave);
		cl.def_readwrite("mNumCoeff", &tsa::ClusterizedEventFullFeatured::mNumCoeff);
		cl.def("assign", (void (tsa::ClusterizedEventFullFeatured::*)(const class tsa::ClusterizedEventFullFeatured &)) &tsa::ClusterizedEventFullFeatured::operator=, "C++: tsa::ClusterizedEventFullFeatured::operator=(const class tsa::ClusterizedEventFullFeatured &) --> void", pybind11::arg("from"));
		cl.def("CEVcopy", (void (tsa::ClusterizedEventFullFeatured::*)(const class tsa::ClusterizedEventFullFeatured &)) &tsa::ClusterizedEventFullFeatured::CEVcopy, "C++: tsa::ClusterizedEventFullFeatured::CEVcopy(const class tsa::ClusterizedEventFullFeatured &) --> void", pybind11::arg("from"));
		cl.def("outprint", (void (tsa::ClusterizedEventFullFeatured::*)()) &tsa::ClusterizedEventFullFeatured::outprint, "C++: tsa::ClusterizedEventFullFeatured::outprint() --> void");
		cl.def("SetCoeff", (void (tsa::ClusterizedEventFullFeatured::*)(int, double)) &tsa::ClusterizedEventFullFeatured::SetCoeff, "C++: tsa::ClusterizedEventFullFeatured::SetCoeff(int, double) --> void", pybind11::arg("i"), pybind11::arg("v"));
		cl.def("GetCoeff", (double (tsa::ClusterizedEventFullFeatured::*)(unsigned int)) &tsa::ClusterizedEventFullFeatured::GetCoeff, "C++: tsa::ClusterizedEventFullFeatured::GetCoeff(unsigned int) --> double", pybind11::arg("i"));
	}
	{ // tsa::InverseRealFFT file:InverseRealFFT.hpp line:66
		pybind11::class_<tsa::InverseRealFFT, std::shared_ptr<tsa::InverseRealFFT>, PyCallBack_tsa_InverseRealFFT, tsa::BaseFFT> cl(M("tsa"), "InverseRealFFT", "Multichannel inverse real to complex FFT.\n\n This is the implementation of the FFT of a real multichannel buffer");
		cl.def( pybind11::init( [](){ return new tsa::InverseRealFFT(); }, [](){ return new PyCallBack_tsa_InverseRealFFT(); } ), "doc");
		cl.def( pybind11::init( [](int const & a0){ return new tsa::InverseRealFFT(a0); }, [](int const & a0){ return new PyCallBack_tsa_InverseRealFFT(a0); } ), "doc");
		cl.def( pybind11::init( [](int const & a0, enum tsa::FFTPlanningMode const & a1){ return new tsa::InverseRealFFT(a0, a1); }, [](int const & a0, enum tsa::FFTPlanningMode const & a1){ return new PyCallBack_tsa_InverseRealFFT(a0, a1); } ), "doc");
		cl.def( pybind11::init<int, enum tsa::FFTPlanningMode, bool>(), pybind11::arg("size"), pybind11::arg("mode"), pybind11::arg("PreserveInput") );

		cl.def( pybind11::init( [](PyCallBack_tsa_InverseRealFFT const &o){ return new PyCallBack_tsa_InverseRealFFT(o); } ) );
		cl.def( pybind11::init( [](tsa::InverseRealFFT const &o){ return new tsa::InverseRealFFT(o); } ) );
		cl.def("__call__", (void (tsa::InverseRealFFT::*)(class tsa::SeqView<class std::complex<double> > &, class tsa::SeqView<double> &)) &tsa::InverseRealFFT::operator(), "Apply the transformation on the data\n\n \n a reference to the buffer containing the input data\n \n\n a reference to the buffer containing the input data\n\n \n a reference to this instance of the class\n\nC++: tsa::InverseRealFFT::operator()(class tsa::SeqView<class std::complex<double> > &, class tsa::SeqView<double> &) --> void", pybind11::arg("in"), pybind11::arg("out"));
		cl.def("MakePlan", (void (tsa::InverseRealFFT::*)()) &tsa::InverseRealFFT::MakePlan, "Make a new plan, with the current parameters.\n\n \n std::runtime_error The new plan cannot be created\n\nC++: tsa::InverseRealFFT::MakePlan() --> void");
		cl.def("assign", (class tsa::InverseRealFFT & (tsa::InverseRealFFT::*)(const class tsa::InverseRealFFT &)) &tsa::InverseRealFFT::operator=, "C++: tsa::InverseRealFFT::operator=(const class tsa::InverseRealFFT &) --> class tsa::InverseRealFFT &", pybind11::return_value_policy::automatic, pybind11::arg(""));
	}
	{ // tsa::KaiserWindow file:KaiserWindow.hpp line:77
		pybind11::class_<tsa::KaiserWindow, std::shared_ptr<tsa::KaiserWindow>, PyCallBack_tsa_KaiserWindow, tsa::BaseWindow> cl(M("tsa"), "KaiserWindow", "Kaiser windowing algorithm\n Harris, F. J. \"On the Use of Windows for Harmonic Analysis with the Discrete Fourier Transform.\" \n Proceedings of the IEEE. Vol. 66 (January 1978). pp. 66-67.");
		cl.def( pybind11::init<int>(), pybind11::arg("size") );

		cl.def( pybind11::init<int, const std::string &>(), pybind11::arg("size"), pybind11::arg("par") );

		cl.def( pybind11::init( [](PyCallBack_tsa_KaiserWindow const &o){ return new PyCallBack_tsa_KaiserWindow(o); } ) );
		cl.def( pybind11::init( [](tsa::KaiserWindow const &o){ return new tsa::KaiserWindow(o); } ) );
		cl.def("__call__", (void (tsa::KaiserWindow::*)(class tsa::SeqView<double> &)) &tsa::KaiserWindow::operator(), "Apply the window to a given time view.\n\n \n the time view \n\nC++: tsa::KaiserWindow::operator()(class tsa::SeqView<double> &) --> void", pybind11::arg("v1"));
		cl.def("__call__", (void (tsa::KaiserWindow::*)(class tsa::SeqView<double> &, class tsa::SeqView<double> &)) &tsa::KaiserWindow::operator(), "Apply a window to an input view and write the results on a \n output view.\n\n \n the input view\n \n\n the output view\n\n         \n\nC++: tsa::KaiserWindow::operator()(class tsa::SeqView<double> &, class tsa::SeqView<double> &) --> void", pybind11::arg("v1"), pybind11::arg("v2"));
		cl.def("Resize", (void (tsa::KaiserWindow::*)(unsigned int)) &tsa::KaiserWindow::Resize, "Resize the window dimension.\n\n \n new size for the window\n\nC++: tsa::KaiserWindow::Resize(unsigned int) --> void", pybind11::arg("size"));
		cl.def("__call__", (double (tsa::KaiserWindow::*)(int)) &tsa::KaiserWindow::operator(), "Get the value of the window at a given index.\n\n \n \n\n the value of the window at the given plage\n\nC++: tsa::KaiserWindow::operator()(int) --> double", pybind11::arg("i"));
		cl.def("assign", (class tsa::KaiserWindow & (tsa::KaiserWindow::*)(const class tsa::KaiserWindow &)) &tsa::KaiserWindow::operator=, "C++: tsa::KaiserWindow::operator=(const class tsa::KaiserWindow &) --> class tsa::KaiserWindow &", pybind11::return_value_policy::automatic, pybind11::arg(""));
	}
	{ // tsa::LatticeFilter file:LatticeFilter.hpp line:77
		pybind11::class_<tsa::LatticeFilter, std::shared_ptr<tsa::LatticeFilter>, tsa::AlgoBase> cl(M("tsa"), "LatticeFilter", "Implement the lattice filter\n\n     ");
		cl.def( pybind11::init<class tsa::LatticeView &>(), pybind11::arg("LV") );

		cl.def( pybind11::init( [](tsa::LatticeFilter const &o){ return new tsa::LatticeFilter(o); } ) );
		cl.def("Load", [](tsa::LatticeFilter &o, const char * a0) -> void { return o.Load(a0); }, "", pybind11::arg("filename"));
		cl.def("Load", (void (tsa::LatticeFilter::*)(const char *, const char *)) &tsa::LatticeFilter::Load, "C++: tsa::LatticeFilter::Load(const char *, const char *) --> void", pybind11::arg("filename"), pybind11::arg("fmt"));
		cl.def("Save", [](tsa::LatticeFilter &o, const char * a0) -> void { return o.Save(a0); }, "", pybind11::arg("filename"));
		cl.def("Save", (void (tsa::LatticeFilter::*)(const char *, const char *)) &tsa::LatticeFilter::Save, "C++: tsa::LatticeFilter::Save(const char *, const char *) --> void", pybind11::arg("filename"), pybind11::arg("fmt"));
		cl.def("xml_serialize", (void (tsa::LatticeFilter::*)(class eternity::xml_archive &, const char *)) &tsa::LatticeFilter::xml_serialize, "C++: tsa::LatticeFilter::xml_serialize(class eternity::xml_archive &, const char *) --> void", pybind11::arg("xml"), pybind11::arg("p"));
		cl.def("__call__", (void (tsa::LatticeFilter::*)(class tsa::SeqView<double> &, class tsa::SeqView<double> &)) &tsa::LatticeFilter::operator(), "Declaration of execute operation\n\n \n Matrix containing Time Series\n \n\n Matrix containing the WhitenedData\n\nC++: tsa::LatticeFilter::operator()(class tsa::SeqView<double> &, class tsa::SeqView<double> &) --> void", pybind11::arg("InputData"), pybind11::arg("WhitenedData"));
		cl.def("init", (void (tsa::LatticeFilter::*)(class tsa::LatticeView &)) &tsa::LatticeFilter::init, "Initialization function\n \n\n lattice view\n\nC++: tsa::LatticeFilter::init(class tsa::LatticeView &) --> void", pybind11::arg("LV"));
		cl.def("assign", (class tsa::LatticeFilter & (tsa::LatticeFilter::*)(const class tsa::LatticeFilter &)) &tsa::LatticeFilter::operator=, "C++: tsa::LatticeFilter::operator=(const class tsa::LatticeFilter &) --> class tsa::LatticeFilter &", pybind11::return_value_policy::automatic, pybind11::arg(""));
	}
}


// File: LSLLearning.cpp
#include <BaseFFT.hpp>
#include <LSLLearning.hpp>
#include <LSLfilter.hpp>
#include <LatticeView.hpp>
#include <LeastSquaresLattice.hpp>
#include <NotchWidrow.hpp>
#include <RLSCanceler.hpp>
#include <RealFFT.hpp>
#include <SelectionOrderCriteria.hpp>
#include <SeqView.hpp>
#include <boost/numeric/ublas/functional.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/matrix_expression.hpp>
#include <boost/numeric/ublas/matrix_proxy.hpp>
#include <boost/numeric/ublas/storage.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include <complex>
#include <eternity/persist.hpp>
#include <eternity/persist_xml.hpp>
#include <functional>
#include <map>
#include <memory>
#include <sstream> // __str__
#include <string>
#include <utility>

#include <functional>
#include <pybind11/pybind11.h>
#include <string>

#ifndef BINDER_PYBIND11_TYPE_CASTER
	#define BINDER_PYBIND11_TYPE_CASTER
	PYBIND11_DECLARE_HOLDER_TYPE(T, std::shared_ptr<T>)
	PYBIND11_DECLARE_HOLDER_TYPE(T, T*)
	PYBIND11_MAKE_OPAQUE(std::shared_ptr<void>)
#endif

// tsa::RealFFT file:RealFFT.hpp line:74
struct PyCallBack_tsa_RealFFT : public tsa::RealFFT {
	using tsa::RealFFT::RealFFT;

	void MakePlan() throw() override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const tsa::RealFFT *>(this), "MakePlan");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>();
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::override_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return RealFFT::MakePlan();
	}
};

void bind_LSLLearning(std::function< pybind11::module &(std::string const &namespace_) > &M)
{
	{ // tsa::LSLLearning file:LSLLearning.hpp line:74
		pybind11::class_<tsa::LSLLearning, std::shared_ptr<tsa::LSLLearning>, tsa::AlgoBase> cl(M("tsa"), "LSLLearning", "rithm for the learning phase of the Adaptive Least Squares Lattice");
		cl.def( pybind11::init( [](unsigned int const & a0, double const & a1){ return new tsa::LSLLearning(a0, a1); } ), "doc" , pybind11::arg("Order"), pybind11::arg("sigma"));
		cl.def( pybind11::init<unsigned int, double, double>(), pybind11::arg("Order"), pybind11::arg("sigma"), pybind11::arg("lambda") );

		cl.def( pybind11::init( [](tsa::LSLLearning const &o){ return new tsa::LSLLearning(o); } ) );
		cl.def("assign", (class tsa::LSLLearning & (tsa::LSLLearning::*)(const class tsa::LSLLearning &)) &tsa::LSLLearning::operator=, "Assignement operator\n\n \n The instance to be assigned from\n\n \n a reference to a new object\n\nC++: tsa::LSLLearning::operator=(const class tsa::LSLLearning &) --> class tsa::LSLLearning &", pybind11::return_value_policy::automatic, pybind11::arg("from"));
		cl.def("__call__", (void (tsa::LSLLearning::*)(class tsa::SeqView<double> &, class tsa::SeqView<double> &)) &tsa::LSLLearning::operator(), "Time series \n \n\n Whitened Time series \n\nC++: tsa::LSLLearning::operator()(class tsa::SeqView<double> &, class tsa::SeqView<double> &) --> void", pybind11::arg("InputData"), pybind11::arg("WhitenedData"));
		cl.def("__call__", (void (tsa::LSLLearning::*)(class tsa::SeqView<double> &, class tsa::LatticeView &)) &tsa::LSLLearning::operator(), "C++: tsa::LSLLearning::operator()(class tsa::SeqView<double> &, class tsa::LatticeView &) --> void", pybind11::arg("InputData"), pybind11::arg("LatView"));
		cl.def("GetOrder", (unsigned int (tsa::LSLLearning::*)()) &tsa::LSLLearning::GetOrder, "C++: tsa::LSLLearning::GetOrder() --> unsigned int");
		cl.def("GetParcorForward", (double (tsa::LSLLearning::*)(unsigned int)) &tsa::LSLLearning::GetParcorForward, "C++: tsa::LSLLearning::GetParcorForward(unsigned int) --> double", pybind11::arg("j"));
		cl.def("GetParcorBackward", (double (tsa::LSLLearning::*)(unsigned int)) &tsa::LSLLearning::GetParcorBackward, "C++: tsa::LSLLearning::GetParcorBackward(unsigned int) --> double", pybind11::arg("j"));
		cl.def("GetErrorForward", (double (tsa::LSLLearning::*)(unsigned int, unsigned int)) &tsa::LSLLearning::GetErrorForward, "C++: tsa::LSLLearning::GetErrorForward(unsigned int, unsigned int) --> double", pybind11::arg("i"), pybind11::arg("j"));
		cl.def("GetErrorBackward", (double (tsa::LSLLearning::*)(unsigned int, unsigned int)) &tsa::LSLLearning::GetErrorBackward, "C++: tsa::LSLLearning::GetErrorBackward(unsigned int, unsigned int) --> double", pybind11::arg("i"), pybind11::arg("j"));
		cl.def("GetEpf", (double (tsa::LSLLearning::*)(unsigned int, unsigned int)) &tsa::LSLLearning::GetEpf, "C++: tsa::LSLLearning::GetEpf(unsigned int, unsigned int) --> double", pybind11::arg("i"), pybind11::arg("j"));
		cl.def("GetEpb", (double (tsa::LSLLearning::*)(unsigned int, unsigned int)) &tsa::LSLLearning::GetEpb, "C++: tsa::LSLLearning::GetEpb(unsigned int, unsigned int) --> double", pybind11::arg("i"), pybind11::arg("j"));
		cl.def("GetGamma", (double (tsa::LSLLearning::*)(unsigned int)) &tsa::LSLLearning::GetGamma, "C++: tsa::LSLLearning::GetGamma(unsigned int) --> double", pybind11::arg("j"));
		cl.def("GetStatus", (unsigned int (tsa::LSLLearning::*)()) &tsa::LSLLearning::GetStatus, "C++: tsa::LSLLearning::GetStatus() --> unsigned int");
		cl.def("GetSigma", (double (tsa::LSLLearning::*)()) &tsa::LSLLearning::GetSigma, "C++: tsa::LSLLearning::GetSigma() --> double");
		cl.def("Load", [](tsa::LSLLearning &o, const char * a0) -> void { return o.Load(a0); }, "", pybind11::arg("filename"));
		cl.def("Load", (void (tsa::LSLLearning::*)(const char *, const char *)) &tsa::LSLLearning::Load, "C++: tsa::LSLLearning::Load(const char *, const char *) --> void", pybind11::arg("filename"), pybind11::arg("fmt"));
		cl.def("Save", [](tsa::LSLLearning &o, const char * a0) -> void { return o.Save(a0); }, "", pybind11::arg("filename"));
		cl.def("Save", (void (tsa::LSLLearning::*)(const char *, const char *)) &tsa::LSLLearning::Save, "C++: tsa::LSLLearning::Save(const char *, const char *) --> void", pybind11::arg("filename"), pybind11::arg("fmt"));
		cl.def("xml_serialize", (void (tsa::LSLLearning::*)(class eternity::xml_archive &, const char *)) &tsa::LSLLearning::xml_serialize, "C++: tsa::LSLLearning::xml_serialize(class eternity::xml_archive &, const char *) --> void", pybind11::arg("xml"), pybind11::arg("p"));
	}
	{ // tsa::LeastSquaresLattice file:LeastSquaresLattice.hpp line:79
		pybind11::class_<tsa::LeastSquaresLattice, std::shared_ptr<tsa::LeastSquaresLattice>, tsa::AlgoBase> cl(M("tsa"), "LeastSquaresLattice", "Estimate the parameters for the Least Squares Lattice filter and implement the adaptive whitening. \n\n     ");
		cl.def( pybind11::init( [](tsa::LeastSquaresLattice const &o){ return new tsa::LeastSquaresLattice(o); } ) );
		cl.def("assign", (class tsa::LeastSquaresLattice & (tsa::LeastSquaresLattice::*)(const class tsa::LeastSquaresLattice &)) &tsa::LeastSquaresLattice::operator=, "Assignement operator\n\n \n The instance to be assigned from\n\n \n a reference to a new object\n\nC++: tsa::LeastSquaresLattice::operator=(const class tsa::LeastSquaresLattice &) --> class tsa::LeastSquaresLattice &", pybind11::return_value_policy::automatic, pybind11::arg("from"));
	}
	{ // tsa::LSLfilter file:LSLfilter.hpp line:76
		pybind11::class_<tsa::LSLfilter, std::shared_ptr<tsa::LSLfilter>, tsa::AlgoBase> cl(M("tsa"), "LSLfilter", "Algorithm for the filter phase of the Adaptive Least Squares Lattice");
		cl.def( pybind11::init( [](class tsa::LSLLearning & a0){ return new tsa::LSLfilter(a0); } ), "doc" , pybind11::arg("LSL"));
		cl.def( pybind11::init( [](class tsa::LSLLearning & a0, double const & a1){ return new tsa::LSLfilter(a0, a1); } ), "doc" , pybind11::arg("LSL"), pybind11::arg("lambda"));
		cl.def( pybind11::init( [](class tsa::LSLLearning & a0, double const & a1, unsigned int const & a2){ return new tsa::LSLfilter(a0, a1, a2); } ), "doc" , pybind11::arg("LSL"), pybind11::arg("lambda"), pybind11::arg("size"));
		cl.def( pybind11::init<class tsa::LSLLearning &, double, unsigned int, bool>(), pybind11::arg("LSL"), pybind11::arg("lambda"), pybind11::arg("size"), pybind11::arg("Norm") );

		cl.def( pybind11::init( [](tsa::LSLfilter const &o){ return new tsa::LSLfilter(o); } ) );
		cl.def("Load", [](tsa::LSLfilter &o, const char * a0) -> void { return o.Load(a0); }, "", pybind11::arg("filename"));
		cl.def("Load", (void (tsa::LSLfilter::*)(const char *, const char *)) &tsa::LSLfilter::Load, "C++: tsa::LSLfilter::Load(const char *, const char *) --> void", pybind11::arg("filename"), pybind11::arg("fmt"));
		cl.def("Save", [](tsa::LSLfilter &o, const char * a0) -> void { return o.Save(a0); }, "", pybind11::arg("filename"));
		cl.def("Save", (void (tsa::LSLfilter::*)(const char *, const char *)) &tsa::LSLfilter::Save, "C++: tsa::LSLfilter::Save(const char *, const char *) --> void", pybind11::arg("filename"), pybind11::arg("fmt"));
		cl.def("xml_serialize", (void (tsa::LSLfilter::*)(class eternity::xml_archive &, const char *)) &tsa::LSLfilter::xml_serialize, "C++: tsa::LSLfilter::xml_serialize(class eternity::xml_archive &, const char *) --> void", pybind11::arg("xml"), pybind11::arg("p"));
		cl.def("__lshift__", (void (tsa::LSLfilter::*)(class tsa::SeqView<double> &)) &tsa::LSLfilter::operator<<, "Declaration of execute operation\n\n \n Matrix containing Time Series\n \n\n Matrix containing the WhitenedData\n \n\n to be used only when data are contiguos (offline analysis)\n\nC++: tsa::LSLfilter::operator<<(class tsa::SeqView<double> &) --> void", pybind11::arg("Data"));
		cl.def("__rshift__", (void (tsa::LSLfilter::*)(class tsa::SeqView<double> &)) &tsa::LSLfilter::operator>>, "C++: tsa::LSLfilter::operator>>(class tsa::SeqView<double> &) --> void", pybind11::arg("outdata"));
		cl.def("__call__", (void (tsa::LSLfilter::*)(class tsa::SeqView<double> &, class tsa::SeqView<double> &)) &tsa::LSLfilter::operator(), "for online process\n\nC++: tsa::LSLfilter::operator()(class tsa::SeqView<double> &, class tsa::SeqView<double> &) --> void", pybind11::arg("Data"), pybind11::arg("outdata"));
		cl.def("GetDataNeeded", (int (tsa::LSLfilter::*)()) &tsa::LSLfilter::GetDataNeeded, "Get the number of data needed in order to be able to \n call GetData successfully. If the returned value is less or \n equal than zero no data are needed.\n\n \n the needed data\n\nC++: tsa::LSLfilter::GetDataNeeded() --> int");
		cl.def("GetOrder", (unsigned int (tsa::LSLfilter::*)()) &tsa::LSLfilter::GetOrder, "C++: tsa::LSLfilter::GetOrder() --> unsigned int");
		cl.def("GetParcorForward", (double (tsa::LSLfilter::*)(unsigned int)) &tsa::LSLfilter::GetParcorForward, "C++: tsa::LSLfilter::GetParcorForward(unsigned int) --> double", pybind11::arg("j"));
		cl.def("GetParcorBackward", (double (tsa::LSLfilter::*)(unsigned int)) &tsa::LSLfilter::GetParcorBackward, "C++: tsa::LSLfilter::GetParcorBackward(unsigned int) --> double", pybind11::arg("j"));
		cl.def("GetEpf", (double (tsa::LSLfilter::*)(unsigned int)) &tsa::LSLfilter::GetEpf, "C++: tsa::LSLfilter::GetEpf(unsigned int) --> double", pybind11::arg("j"));
		cl.def("GetErrorForward", (double (tsa::LSLfilter::*)(unsigned int)) &tsa::LSLfilter::GetErrorForward, "C++: tsa::LSLfilter::GetErrorForward(unsigned int) --> double", pybind11::arg("j"));
		cl.def("GetErrorBackward", (double (tsa::LSLfilter::*)(unsigned int)) &tsa::LSLfilter::GetErrorBackward, "C++: tsa::LSLfilter::GetErrorBackward(unsigned int) --> double", pybind11::arg("j"));
		cl.def("GetSigma", (double (tsa::LSLfilter::*)(unsigned int)) &tsa::LSLfilter::GetSigma, "C++: tsa::LSLfilter::GetSigma(unsigned int) --> double", pybind11::arg("j"));
		cl.def("assign", (class tsa::LSLfilter & (tsa::LSLfilter::*)(const class tsa::LSLfilter &)) &tsa::LSLfilter::operator=, "C++: tsa::LSLfilter::operator=(const class tsa::LSLfilter &) --> class tsa::LSLfilter &", pybind11::return_value_policy::automatic, pybind11::arg(""));
	}
	{ // tsa::NotchWidrow file:NotchWidrow.hpp line:71
		pybind11::class_<tsa::NotchWidrow, std::shared_ptr<tsa::NotchWidrow>, tsa::AlgoBase> cl(M("tsa"), "NotchWidrow", "Implement the lines removal using adaptive notch filters, with the Least Mean Squared method, Widrow's like.");
		cl.def( pybind11::init( [](tsa::NotchWidrow const &o){ return new tsa::NotchWidrow(o); } ) );
		cl.def("__call__", (void (tsa::NotchWidrow::*)(class tsa::SeqView<double> &, class tsa::SeqView<double> &)) &tsa::NotchWidrow::operator(), "C++: tsa::NotchWidrow::operator()(class tsa::SeqView<double> &, class tsa::SeqView<double> &) --> void", pybind11::arg("InputData"), pybind11::arg("CleanedData"));
		cl.def("__call__", (void (tsa::NotchWidrow::*)(class tsa::SeqView<double> &, class tsa::SeqView<double> &, class tsa::SeqView<double> &)) &tsa::NotchWidrow::operator(), "C++: tsa::NotchWidrow::operator()(class tsa::SeqView<double> &, class tsa::SeqView<double> &, class tsa::SeqView<double> &) --> void", pybind11::arg("InputData"), pybind11::arg("CleanedData"), pybind11::arg("ReferenceSignal"));
		cl.def("assign", (class tsa::NotchWidrow & (tsa::NotchWidrow::*)(const class tsa::NotchWidrow &)) &tsa::NotchWidrow::operator=, "Assignement operator\n\n \n The instance to be assigned from\n\n \n a reference to a new object\n\nC++: tsa::NotchWidrow::operator=(const class tsa::NotchWidrow &) --> class tsa::NotchWidrow &", pybind11::return_value_policy::automatic, pybind11::arg("from"));
		cl.def("Getlstart", (double (tsa::NotchWidrow::*)()) &tsa::NotchWidrow::Getlstart, "C++: tsa::NotchWidrow::Getlstart() --> double");
	}
	{ // tsa::RealFFT file:RealFFT.hpp line:74
		pybind11::class_<tsa::RealFFT, std::shared_ptr<tsa::RealFFT>, PyCallBack_tsa_RealFFT, tsa::BaseFFT> cl(M("tsa"), "RealFFT", "Multichannel real to complex FFT.\n\n This is the implementation of the FFT of a real multichannel buffer");
		cl.def( pybind11::init( [](){ return new tsa::RealFFT(); }, [](){ return new PyCallBack_tsa_RealFFT(); } ), "doc");
		cl.def( pybind11::init( [](int const & a0){ return new tsa::RealFFT(a0); }, [](int const & a0){ return new PyCallBack_tsa_RealFFT(a0); } ), "doc");
		cl.def( pybind11::init( [](int const & a0, enum tsa::FFTPlanningMode const & a1){ return new tsa::RealFFT(a0, a1); }, [](int const & a0, enum tsa::FFTPlanningMode const & a1){ return new PyCallBack_tsa_RealFFT(a0, a1); } ), "doc");
		cl.def( pybind11::init<int, enum tsa::FFTPlanningMode, bool>(), pybind11::arg("size"), pybind11::arg("mode"), pybind11::arg("PreserveInput") );

		cl.def( pybind11::init( [](PyCallBack_tsa_RealFFT const &o){ return new PyCallBack_tsa_RealFFT(o); } ) );
		cl.def( pybind11::init( [](tsa::RealFFT const &o){ return new tsa::RealFFT(o); } ) );
		cl.def("__call__", (void (tsa::RealFFT::*)(class tsa::SeqView<double> &, class tsa::SeqView<class std::complex<double> > &)) &tsa::RealFFT::operator(), "Apply the transformation on the data\n\n \n a reference to the buffer containing the input data\n \n\n a reference to the buffer containing the input data\n\n \n a reference to this instance of the class\n\nC++: tsa::RealFFT::operator()(class tsa::SeqView<double> &, class tsa::SeqView<class std::complex<double> > &) --> void", pybind11::arg("in"), pybind11::arg("out"));
		cl.def("MakePlan", (void (tsa::RealFFT::*)()) &tsa::RealFFT::MakePlan, "Make a new plan, with the current parameters.\n\n \n std::runtime_error The new plan cannot be created\n\nC++: tsa::RealFFT::MakePlan() --> void");
		cl.def("assign", (class tsa::RealFFT & (tsa::RealFFT::*)(const class tsa::RealFFT &)) &tsa::RealFFT::operator=, "C++: tsa::RealFFT::operator=(const class tsa::RealFFT &) --> class tsa::RealFFT &", pybind11::return_value_policy::automatic, pybind11::arg(""));
	}
	{ // tsa::RLSCanceler file:RLSCanceler.hpp line:71
		pybind11::class_<tsa::RLSCanceler, std::shared_ptr<tsa::RLSCanceler>, tsa::AlgoBase> cl(M("tsa"), "RLSCanceler", "");
		cl.def( pybind11::init<unsigned int, double, double, unsigned int>(), pybind11::arg("Order"), pybind11::arg("delta"), pybind11::arg("lambda"), pybind11::arg("Channels") );

		cl.def( pybind11::init( [](tsa::RLSCanceler const &o){ return new tsa::RLSCanceler(o); } ) );
		cl.def("assign", (class tsa::RLSCanceler & (tsa::RLSCanceler::*)(const class tsa::RLSCanceler &)) &tsa::RLSCanceler::operator=, "Assignement operator\n\n \n The instance to be assigned from\n\n \n a reference to a new object\n\nC++: tsa::RLSCanceler::operator=(const class tsa::RLSCanceler &) --> class tsa::RLSCanceler &", pybind11::return_value_policy::automatic, pybind11::arg("from"));
		cl.def("__call__", (void (tsa::RLSCanceler::*)(class tsa::SeqView<double> &, class tsa::SeqView<double> &)) &tsa::RLSCanceler::operator(), "C++: tsa::RLSCanceler::operator()(class tsa::SeqView<double> &, class tsa::SeqView<double> &) --> void", pybind11::arg("InputData"), pybind11::arg("CleanedData"));
		cl.def("__call__", (void (tsa::RLSCanceler::*)(class tsa::SeqView<double> &, class tsa::SeqView<double> &, class tsa::SeqView<double> &)) &tsa::RLSCanceler::operator(), "C++: tsa::RLSCanceler::operator()(class tsa::SeqView<double> &, class tsa::SeqView<double> &, class tsa::SeqView<double> &) --> void", pybind11::arg("InputData"), pybind11::arg("CleanedData"), pybind11::arg("ReferenceSignal"));
		cl.def("Getlstart", (double (tsa::RLSCanceler::*)()) &tsa::RLSCanceler::Getlstart, "the last step\n\nC++: tsa::RLSCanceler::Getlstart() --> double");
		cl.def("GetWeights", (double (tsa::RLSCanceler::*)(unsigned int, unsigned int)) &tsa::RLSCanceler::GetWeights, "index of the weights\n \n\n channel to which the weights belong\n \n\n yhe weights of the RLS filter\n\nC++: tsa::RLSCanceler::GetWeights(unsigned int, unsigned int) --> double", pybind11::arg("j"), pybind11::arg("channel"));
	}
	{ // tsa::SelectionOrderCriteria file:SelectionOrderCriteria.hpp line:78
		pybind11::class_<tsa::SelectionOrderCriteria, std::shared_ptr<tsa::SelectionOrderCriteria>> cl(M("tsa"), "SelectionOrderCriteria", "A more detailed description of SelectionOrderCriteria\n\n    Produce order selection criteria");
		cl.def( pybind11::init<unsigned int, unsigned int>(), pybind11::arg("N"), pybind11::arg("Order") );

		cl.def( pybind11::init( [](tsa::SelectionOrderCriteria const &o){ return new tsa::SelectionOrderCriteria(o); } ) );
		cl.def("GetEps", (double (tsa::SelectionOrderCriteria::*)(unsigned int)) &tsa::SelectionOrderCriteria::GetEps, "C++: tsa::SelectionOrderCriteria::GetEps(unsigned int) --> double", pybind11::arg("j"));
		cl.def("GetFpe", (double (tsa::SelectionOrderCriteria::*)(unsigned int)) &tsa::SelectionOrderCriteria::GetFpe, "values for selected selection criteria\n\nC++: tsa::SelectionOrderCriteria::GetFpe(unsigned int) --> double", pybind11::arg("j"));
		cl.def("GetMdl", (double (tsa::SelectionOrderCriteria::*)(unsigned int)) &tsa::SelectionOrderCriteria::GetMdl, "values for selected selection criteria\n\nC++: tsa::SelectionOrderCriteria::GetMdl(unsigned int) --> double", pybind11::arg("j"));
		cl.def("GetAic", (double (tsa::SelectionOrderCriteria::*)(unsigned int)) &tsa::SelectionOrderCriteria::GetAic, "values for selected selection criteria\n\nC++: tsa::SelectionOrderCriteria::GetAic(unsigned int) --> double", pybind11::arg("j"));
		cl.def("GetAicC", (double (tsa::SelectionOrderCriteria::*)(unsigned int)) &tsa::SelectionOrderCriteria::GetAicC, "values for selected selection criteria\n\nC++: tsa::SelectionOrderCriteria::GetAicC(unsigned int) --> double", pybind11::arg("j"));
		cl.def("GetCat", (double (tsa::SelectionOrderCriteria::*)(unsigned int)) &tsa::SelectionOrderCriteria::GetCat, "values for selected selection criteria\n\nC++: tsa::SelectionOrderCriteria::GetCat(unsigned int) --> double", pybind11::arg("j"));
		cl.def("GetHQ", (double (tsa::SelectionOrderCriteria::*)(unsigned int)) &tsa::SelectionOrderCriteria::GetHQ, "values for selected selection criteria\n\nC++: tsa::SelectionOrderCriteria::GetHQ(unsigned int) --> double", pybind11::arg("j"));
		cl.def("GetCic", (double (tsa::SelectionOrderCriteria::*)(unsigned int)) &tsa::SelectionOrderCriteria::GetCic, "values for selected selection criteria\n\nC++: tsa::SelectionOrderCriteria::GetCic(unsigned int) --> double", pybind11::arg("j"));
		cl.def("GetFsic", (double (tsa::SelectionOrderCriteria::*)(unsigned int)) &tsa::SelectionOrderCriteria::GetFsic, "values for selected selection criteria\n\nC++: tsa::SelectionOrderCriteria::GetFsic(unsigned int) --> double", pybind11::arg("j"));
		cl.def("assign", (class tsa::SelectionOrderCriteria & (tsa::SelectionOrderCriteria::*)(const class tsa::SelectionOrderCriteria &)) &tsa::SelectionOrderCriteria::operator=, "C++: tsa::SelectionOrderCriteria::operator=(const class tsa::SelectionOrderCriteria &) --> class tsa::SelectionOrderCriteria &", pybind11::return_value_policy::automatic, pybind11::arg(""));
	}
}


// File: TF2Psd.cpp
#include <BaseWindow.hpp>
#include <SeqView.hpp>
#include <TF2Psd.hpp>
#include <TukeyHannWindow.hpp>
#include <TukeyWindow.hpp>
#include <boost/numeric/ublas/functional.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/storage.hpp>
#include <complex>
#include <iterator>
#include <memory>
#include <sstream> // __str__
#include <string>

#include <functional>
#include <pybind11/pybind11.h>
#include <string>

#ifndef BINDER_PYBIND11_TYPE_CASTER
	#define BINDER_PYBIND11_TYPE_CASTER
	PYBIND11_DECLARE_HOLDER_TYPE(T, std::shared_ptr<T>)
	PYBIND11_DECLARE_HOLDER_TYPE(T, T*)
	PYBIND11_MAKE_OPAQUE(std::shared_ptr<void>)
#endif

// tsa::TukeyWindow file:TukeyWindow.hpp line:76
struct PyCallBack_tsa_TukeyWindow : public tsa::TukeyWindow {
	using tsa::TukeyWindow::TukeyWindow;

	void operator()(class tsa::SeqView<double> & a0) override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const tsa::TukeyWindow *>(this), "__call__");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::override_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return TukeyWindow::operator()(a0);
	}
	void operator()(class tsa::SeqView<double> & a0, class tsa::SeqView<double> & a1) override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const tsa::TukeyWindow *>(this), "__call__");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0, a1);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::override_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return TukeyWindow::operator()(a0, a1);
	}
	void Resize(unsigned int a0) override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const tsa::TukeyWindow *>(this), "Resize");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::override_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return TukeyWindow::Resize(a0);
	}
	void Normalize() override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const tsa::TukeyWindow *>(this), "Normalize");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>();
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::override_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return BaseWindow::Normalize();
	}
	void FillWindow() override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const tsa::TukeyWindow *>(this), "FillWindow");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>();
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::override_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return BaseWindow::FillWindow();
	}
};

// tsa::TukeyHannWindow file:TukeyHannWindow.hpp line:68
struct PyCallBack_tsa_TukeyHannWindow : public tsa::TukeyHannWindow {
	using tsa::TukeyHannWindow::TukeyHannWindow;

	void operator()(class tsa::SeqView<double> & a0) override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const tsa::TukeyHannWindow *>(this), "__call__");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::override_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return TukeyHannWindow::operator()(a0);
	}
	void operator()(class tsa::SeqView<double> & a0, class tsa::SeqView<double> & a1) override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const tsa::TukeyHannWindow *>(this), "__call__");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0, a1);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::override_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return TukeyHannWindow::operator()(a0, a1);
	}
	void Resize(unsigned int a0) override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const tsa::TukeyHannWindow *>(this), "Resize");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::override_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return TukeyHannWindow::Resize(a0);
	}
	void Normalize() override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const tsa::TukeyHannWindow *>(this), "Normalize");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>();
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::override_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return BaseWindow::Normalize();
	}
	void FillWindow() override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const tsa::TukeyHannWindow *>(this), "FillWindow");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>();
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::override_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return BaseWindow::FillWindow();
	}
};

void bind_TF2Psd(std::function< pybind11::module &(std::string const &namespace_) > &M)
{
	{ // tsa::TF2PSD file:TF2Psd.hpp line:71
		pybind11::class_<tsa::TF2PSD, std::shared_ptr<tsa::TF2PSD>, tsa::AlgoBase> cl(M("tsa"), "TF2PSD", "Convert a transfer function to a PSD \n\n     ");
		cl.def( pybind11::init( [](){ return new tsa::TF2PSD(); } ), "doc" );
		cl.def( pybind11::init<bool>(), pybind11::arg("squared") );

		cl.def( pybind11::init( [](tsa::TF2PSD const &o){ return new tsa::TF2PSD(o); } ) );
		cl.def("assign", (class tsa::TF2PSD & (tsa::TF2PSD::*)(const class tsa::TF2PSD &)) &tsa::TF2PSD::operator=, "Assignement operator\n\n \n The instance to be assigned from\n\n \n a reference to a new object\n\nC++: tsa::TF2PSD::operator=(const class tsa::TF2PSD &) --> class tsa::TF2PSD &", pybind11::return_value_policy::automatic, pybind11::arg("from"));
		cl.def("GetSquared", (bool (tsa::TF2PSD::*)()) &tsa::TF2PSD::GetSquared, "C++: tsa::TF2PSD::GetSquared() --> bool");
		cl.def("SetSquared", [](tsa::TF2PSD &o) -> void { return o.SetSquared(); }, "");
		cl.def("SetSquared", (void (tsa::TF2PSD::*)(bool)) &tsa::TF2PSD::SetSquared, "C++: tsa::TF2PSD::SetSquared(bool) --> void", pybind11::arg("squared"));
	}
	{ // tsa::TukeyWindow file:TukeyWindow.hpp line:76
		pybind11::class_<tsa::TukeyWindow, std::shared_ptr<tsa::TukeyWindow>, PyCallBack_tsa_TukeyWindow, tsa::BaseWindow> cl(M("tsa"), "TukeyWindow", "Tukey windowing algorithm\n Harris, F. J. \"On the Use of Windows for Harmonic Analysis with the Discrete Fourier Transform.\" \n Proceedings of the IEEE. Vol. 66 (January 1978). pp. 66-67.");
		cl.def( pybind11::init<int>(), pybind11::arg("size") );

		cl.def( pybind11::init<int, const std::string &>(), pybind11::arg("size"), pybind11::arg("par") );

		cl.def( pybind11::init( [](PyCallBack_tsa_TukeyWindow const &o){ return new PyCallBack_tsa_TukeyWindow(o); } ) );
		cl.def( pybind11::init( [](tsa::TukeyWindow const &o){ return new tsa::TukeyWindow(o); } ) );
		cl.def("__call__", (void (tsa::TukeyWindow::*)(class tsa::SeqView<double> &)) &tsa::TukeyWindow::operator(), "Apply the window to a given time view.\n\n \n the time view \n\nC++: tsa::TukeyWindow::operator()(class tsa::SeqView<double> &) --> void", pybind11::arg("v1"));
		cl.def("__call__", (void (tsa::TukeyWindow::*)(class tsa::SeqView<double> &, class tsa::SeqView<double> &)) &tsa::TukeyWindow::operator(), "Apply a window to an input view and write the results on a \n output view.\n\n \n the input view\n \n\n the output view\n\n         \n\nC++: tsa::TukeyWindow::operator()(class tsa::SeqView<double> &, class tsa::SeqView<double> &) --> void", pybind11::arg("v1"), pybind11::arg("v2"));
		cl.def("Resize", (void (tsa::TukeyWindow::*)(unsigned int)) &tsa::TukeyWindow::Resize, "Resize the window dimension.\n\n \n new size for the window\n\nC++: tsa::TukeyWindow::Resize(unsigned int) --> void", pybind11::arg("size"));
		cl.def("__call__", (double (tsa::TukeyWindow::*)(int)) &tsa::TukeyWindow::operator(), "Get the value of the window at a given index.\n\n \n \n\n the value of the window at the given plage\n\nC++: tsa::TukeyWindow::operator()(int) --> double", pybind11::arg("i"));
		cl.def("assign", (class tsa::TukeyWindow & (tsa::TukeyWindow::*)(const class tsa::TukeyWindow &)) &tsa::TukeyWindow::operator=, "C++: tsa::TukeyWindow::operator=(const class tsa::TukeyWindow &) --> class tsa::TukeyWindow &", pybind11::return_value_policy::automatic, pybind11::arg(""));
	}
	{ // tsa::TukeyHannWindow file:TukeyHannWindow.hpp line:68
		pybind11::class_<tsa::TukeyHannWindow, std::shared_ptr<tsa::TukeyHannWindow>, PyCallBack_tsa_TukeyHannWindow, tsa::BaseWindow> cl(M("tsa"), "TukeyHannWindow", "TukeyHann windowing algorithm\n\n     ");
		cl.def( pybind11::init<int>(), pybind11::arg("size") );

		cl.def( pybind11::init<int, const std::string &>(), pybind11::arg("size"), pybind11::arg("p") );

		cl.def( pybind11::init( [](PyCallBack_tsa_TukeyHannWindow const &o){ return new PyCallBack_tsa_TukeyHannWindow(o); } ) );
		cl.def( pybind11::init( [](tsa::TukeyHannWindow const &o){ return new tsa::TukeyHannWindow(o); } ) );
		cl.def("__call__", (void (tsa::TukeyHannWindow::*)(class tsa::SeqView<double> &)) &tsa::TukeyHannWindow::operator(), "Apply the window to a given time view.\n\n \n the time view \n\nC++: tsa::TukeyHannWindow::operator()(class tsa::SeqView<double> &) --> void", pybind11::arg("v1"));
		cl.def("__call__", (void (tsa::TukeyHannWindow::*)(class tsa::SeqView<double> &, class tsa::SeqView<double> &)) &tsa::TukeyHannWindow::operator(), "Apply a window to an input view and write the results on a \n output view.\n\n \n the input view\n \n\n the output view\n\n         \n\nC++: tsa::TukeyHannWindow::operator()(class tsa::SeqView<double> &, class tsa::SeqView<double> &) --> void", pybind11::arg("v1"), pybind11::arg("v2"));
		cl.def("Resize", (void (tsa::TukeyHannWindow::*)(unsigned int)) &tsa::TukeyHannWindow::Resize, "Resize the window dimension.\n\n \n new size for the window\n\nC++: tsa::TukeyHannWindow::Resize(unsigned int) --> void", pybind11::arg("size"));
		cl.def("assign", (class tsa::TukeyHannWindow & (tsa::TukeyHannWindow::*)(const class tsa::TukeyHannWindow &)) &tsa::TukeyHannWindow::operator=, "C++: tsa::TukeyHannWindow::operator=(const class tsa::TukeyHannWindow &) --> class tsa::TukeyHannWindow &", pybind11::return_value_policy::automatic, pybind11::arg(""));
	}
}


// File: WaveletThreshold.cpp
#include <BaseWindow.hpp>
#include <EventFullFeatured.hpp>
#include <SeqView.hpp>
#include <WDF2Classify.hpp>
#include <WDF2Reconstruct.hpp>
#include <WavReconstruction.hpp>
#include <WaveletThreshold.hpp>
#include <WaveletTransform.hpp>
#include <WelchWindow.hpp>
#include <WindowFactory.hpp>
#include <boost/numeric/ublas/functional.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/storage.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include <iterator>
#include <memory>
#include <sstream> // __str__
#include <string>
#include <vector>

#include <functional>
#include <pybind11/pybind11.h>
#include <string>

#ifndef BINDER_PYBIND11_TYPE_CASTER
	#define BINDER_PYBIND11_TYPE_CASTER
	PYBIND11_DECLARE_HOLDER_TYPE(T, std::shared_ptr<T>)
	PYBIND11_DECLARE_HOLDER_TYPE(T, T*)
	PYBIND11_MAKE_OPAQUE(std::shared_ptr<void>)
#endif

// tsa::WelchWindow file:WelchWindow.hpp line:69
struct PyCallBack_tsa_WelchWindow : public tsa::WelchWindow {
	using tsa::WelchWindow::WelchWindow;

	void operator()(class tsa::SeqView<double> & a0) override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const tsa::WelchWindow *>(this), "__call__");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::override_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return WelchWindow::operator()(a0);
	}
	void operator()(class tsa::SeqView<double> & a0, class tsa::SeqView<double> & a1) override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const tsa::WelchWindow *>(this), "__call__");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0, a1);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::override_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return WelchWindow::operator()(a0, a1);
	}
	void Resize(unsigned int a0) override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const tsa::WelchWindow *>(this), "Resize");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::override_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return WelchWindow::Resize(a0);
	}
	void Normalize() override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const tsa::WelchWindow *>(this), "Normalize");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>();
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::override_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return BaseWindow::Normalize();
	}
	void FillWindow() override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const tsa::WelchWindow *>(this), "FillWindow");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>();
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::override_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return BaseWindow::FillWindow();
	}
};

void bind_WaveletThreshold(std::function< pybind11::module &(std::string const &namespace_) > &M)
{
	{ // tsa::WaveletThreshold file:WaveletThreshold.hpp line:77
		pybind11::class_<tsa::WaveletThreshold, std::shared_ptr<tsa::WaveletThreshold>> cl(M("tsa"), "WaveletThreshold", "Perform threshold on wavelet coefficients");
		cl.def( pybind11::init( [](unsigned int const & a0){ return new tsa::WaveletThreshold(a0); } ), "doc" , pybind11::arg("N"));
		cl.def( pybind11::init( [](unsigned int const & a0, unsigned int const & a1){ return new tsa::WaveletThreshold(a0, a1); } ), "doc" , pybind11::arg("N"), pybind11::arg("ncoeff"));
		cl.def( pybind11::init<unsigned int, unsigned int, double>(), pybind11::arg("N"), pybind11::arg("ncoeff"), pybind11::arg("sigma") );

		cl.def( pybind11::init( [](tsa::WaveletThreshold const &o){ return new tsa::WaveletThreshold(o); } ) );

		pybind11::enum_<tsa::WaveletThreshold::WaveletThresholding>(cl, "WaveletThresholding", pybind11::arithmetic(), "")
			.value("highest", tsa::WaveletThreshold::highest)
			.value("dohonojohnston", tsa::WaveletThreshold::dohonojohnston)
			.value("cuoco", tsa::WaveletThreshold::cuoco)
			.export_values();


		pybind11::enum_<tsa::WaveletThreshold::ThresholdingMode>(cl, "ThresholdingMode", pybind11::arithmetic(), "")
			.value("hard", tsa::WaveletThreshold::hard)
			.value("soft", tsa::WaveletThreshold::soft)
			.export_values();

		cl.def("__call__", [](tsa::WaveletThreshold &o, class tsa::SeqView<double> & a0, enum tsa::WaveletThreshold::WaveletThresholding const & a1) -> void { return o.operator()(a0, a1); }, "", pybind11::arg("WT"), pybind11::arg("t"));
		cl.def("__call__", (void (tsa::WaveletThreshold::*)(class tsa::SeqView<double> &, enum tsa::WaveletThreshold::WaveletThresholding, enum tsa::WaveletThreshold::ThresholdingMode)) &tsa::WaveletThreshold::operator(), "Brief documentation for the execute method.\n\n Start of the long documentation for execute method.\n\n \n A precondition\n \n\n A postcondition\n \n\n An exception\n\n \n parameter\n\n \n a returned value\n\n Declaration of execute operation\n\nC++: tsa::WaveletThreshold::operator()(class tsa::SeqView<double> &, enum tsa::WaveletThreshold::WaveletThresholding, enum tsa::WaveletThreshold::ThresholdingMode) --> void", pybind11::arg("WT"), pybind11::arg("t"), pybind11::arg("m"));
		cl.def("GetSigma", (double (tsa::WaveletThreshold::*)()) &tsa::WaveletThreshold::GetSigma, "C++: tsa::WaveletThreshold::GetSigma() --> double");
		cl.def("GetLevel", (double (tsa::WaveletThreshold::*)()) &tsa::WaveletThreshold::GetLevel, "C++: tsa::WaveletThreshold::GetLevel() --> double");
		cl.def("GetCm", (double (tsa::WaveletThreshold::*)()) &tsa::WaveletThreshold::GetCm, "C++: tsa::WaveletThreshold::GetCm() --> double");
		cl.def("SetSigma", (void (tsa::WaveletThreshold::*)(double)) &tsa::WaveletThreshold::SetSigma, "C++: tsa::WaveletThreshold::SetSigma(double) --> void", pybind11::arg("sigma"));
		cl.def("assign", (class tsa::WaveletThreshold & (tsa::WaveletThreshold::*)(const class tsa::WaveletThreshold &)) &tsa::WaveletThreshold::operator=, "C++: tsa::WaveletThreshold::operator=(const class tsa::WaveletThreshold &) --> class tsa::WaveletThreshold &", pybind11::return_value_policy::automatic, pybind11::arg(""));
	}
	{ // tsa::WaveletTransform file:WaveletTransform.hpp line:75
		pybind11::class_<tsa::WaveletTransform, std::shared_ptr<tsa::WaveletTransform>> cl(M("tsa"), "WaveletTransform", "Compute the wavelet transform");
		cl.def( pybind11::init<unsigned int, enum tsa::WaveletTransform::WaveletType>(), pybind11::arg("N"), pybind11::arg("wt") );

		cl.def( pybind11::init( [](tsa::WaveletTransform const &o){ return new tsa::WaveletTransform(o); } ) );

		pybind11::enum_<tsa::WaveletTransform::WaveletType>(cl, "WaveletType", pybind11::arithmetic(), "")
			.value("Daub4", tsa::WaveletTransform::Daub4)
			.value("Daub6", tsa::WaveletTransform::Daub6)
			.value("Daub8", tsa::WaveletTransform::Daub8)
			.value("Daub10", tsa::WaveletTransform::Daub10)
			.value("Daub12", tsa::WaveletTransform::Daub12)
			.value("Daub14", tsa::WaveletTransform::Daub14)
			.value("Daub16", tsa::WaveletTransform::Daub16)
			.value("Daub18", tsa::WaveletTransform::Daub18)
			.value("Daub20", tsa::WaveletTransform::Daub20)
			.value("DaubC4", tsa::WaveletTransform::DaubC4)
			.value("DaubC6", tsa::WaveletTransform::DaubC6)
			.value("DaubC8", tsa::WaveletTransform::DaubC8)
			.value("DaubC10", tsa::WaveletTransform::DaubC10)
			.value("DaubC12", tsa::WaveletTransform::DaubC12)
			.value("DaubC14", tsa::WaveletTransform::DaubC14)
			.value("DaubC16", tsa::WaveletTransform::DaubC16)
			.value("DaubC18", tsa::WaveletTransform::DaubC18)
			.value("DaubC20", tsa::WaveletTransform::DaubC20)
			.value("Haar", tsa::WaveletTransform::Haar)
			.value("HaarC", tsa::WaveletTransform::HaarC)
			.value("Bspline103", tsa::WaveletTransform::Bspline103)
			.value("Bspline105", tsa::WaveletTransform::Bspline105)
			.value("Bspline202", tsa::WaveletTransform::Bspline202)
			.value("Bspline204", tsa::WaveletTransform::Bspline204)
			.value("Bspline206", tsa::WaveletTransform::Bspline206)
			.value("Bspline208", tsa::WaveletTransform::Bspline208)
			.value("Bspline301", tsa::WaveletTransform::Bspline301)
			.value("Bspline303", tsa::WaveletTransform::Bspline303)
			.value("Bspline305", tsa::WaveletTransform::Bspline305)
			.value("Bspline307", tsa::WaveletTransform::Bspline307)
			.value("Bspline309", tsa::WaveletTransform::Bspline309)
			.value("BsplineC103", tsa::WaveletTransform::BsplineC103)
			.value("BsplineC105", tsa::WaveletTransform::BsplineC105)
			.value("BsplineC202", tsa::WaveletTransform::BsplineC202)
			.value("BsplineC204", tsa::WaveletTransform::BsplineC204)
			.value("BsplineC206", tsa::WaveletTransform::BsplineC206)
			.value("BsplineC208", tsa::WaveletTransform::BsplineC208)
			.value("BsplineC301", tsa::WaveletTransform::BsplineC301)
			.value("BsplineC303", tsa::WaveletTransform::BsplineC303)
			.value("BsplineC305", tsa::WaveletTransform::BsplineC305)
			.value("BsplineC307", tsa::WaveletTransform::BsplineC307)
			.value("BsplineC309", tsa::WaveletTransform::BsplineC309)
			.export_values();

		cl.def("assign", (class tsa::WaveletTransform & (tsa::WaveletTransform::*)(const class tsa::WaveletTransform &)) &tsa::WaveletTransform::operator=, "Assignement operator\n\n \n The instance to be assigned from\n\n \n a reference to a new object\n\nC++: tsa::WaveletTransform::operator=(const class tsa::WaveletTransform &) --> class tsa::WaveletTransform &", pybind11::return_value_policy::automatic, pybind11::arg("from"));
		cl.def("Forward", (void (tsa::WaveletTransform::*)(class tsa::SeqView<double> &)) &tsa::WaveletTransform::Forward, "Brief documentation for the execute method.\n\n Start of the long documentation for execute method.\n\n \n A precondition\n \n\n A postcondition\n \n\n An exception\n\n \n parameter\n\n \n a returned value\n\n Declaration of execute operation\n\nC++: tsa::WaveletTransform::Forward(class tsa::SeqView<double> &) --> void", pybind11::arg("In"));
		cl.def("Inverse", (void (tsa::WaveletTransform::*)(class tsa::SeqView<double> &)) &tsa::WaveletTransform::Inverse, "C++: tsa::WaveletTransform::Inverse(class tsa::SeqView<double> &) --> void", pybind11::arg("In"));
		cl.def("WaveletPrint", (void (tsa::WaveletTransform::*)()) &tsa::WaveletTransform::WaveletPrint, "C++: tsa::WaveletTransform::WaveletPrint() --> void");
	}
	{ // tsa::WavReconstruction file:WavReconstruction.hpp line:78
		pybind11::class_<tsa::WavReconstruction, std::shared_ptr<tsa::WavReconstruction>, tsa::AlgoBase> cl(M("tsa"), "WavReconstruction", "A more detailed description of WavReconstruction\n\n Reconstructed the wavelet transformed signal");
		cl.def( pybind11::init<unsigned int, enum tsa::WaveletTransform::WaveletType, double>(), pybind11::arg("N"), pybind11::arg("F"), pybind11::arg("Th") );

		cl.def( pybind11::init( [](tsa::WavReconstruction const &o){ return new tsa::WavReconstruction(o); } ) );
		cl.def("__call__", (void (tsa::WavReconstruction::*)(class tsa::SeqView<double> &)) &tsa::WavReconstruction::operator(), "C++: tsa::WavReconstruction::operator()(class tsa::SeqView<double> &) --> void", pybind11::arg("InputData"));
		cl.def("assign", (class tsa::WavReconstruction & (tsa::WavReconstruction::*)(const class tsa::WavReconstruction &)) &tsa::WavReconstruction::operator=, "C++: tsa::WavReconstruction::operator=(const class tsa::WavReconstruction &) --> class tsa::WavReconstruction &", pybind11::return_value_policy::automatic, pybind11::arg(""));
	}
	{ // tsa::WDF2Classify file:WDF2Classify.hpp line:85
		pybind11::class_<tsa::WDF2Classify, std::shared_ptr<tsa::WDF2Classify>, tsa::AlgoBase> cl(M("tsa"), "WDF2Classify", "Time domain detection of transients based on wavelet transform");
		cl.def( pybind11::init( [](unsigned int const & a0, unsigned int const & a1, double const & a2, double const & a3, unsigned int const & a4){ return new tsa::WDF2Classify(a0, a1, a2, a3, a4); } ), "doc" , pybind11::arg("window"), pybind11::arg("overlap"), pybind11::arg("thresh"), pybind11::arg("sigma"), pybind11::arg("ncoeff"));
		cl.def( pybind11::init<unsigned int, unsigned int, double, double, unsigned int, enum tsa::WaveletThreshold::WaveletThresholding>(), pybind11::arg("window"), pybind11::arg("overlap"), pybind11::arg("thresh"), pybind11::arg("sigma"), pybind11::arg("ncoeff"), pybind11::arg("WTh") );

		cl.def( pybind11::init( [](tsa::WDF2Classify const &o){ return new tsa::WDF2Classify(o); } ) );
		cl.def("__lshift__", (void (tsa::WDF2Classify::*)(class tsa::SeqView<double> &)) &tsa::WDF2Classify::operator<<, "@{\n\nC++: tsa::WDF2Classify::operator<<(class tsa::SeqView<double> &) --> void", pybind11::arg("Data"));
		cl.def("__call__", (void (tsa::WDF2Classify::*)(class tsa::SeqView<double> &, double)) &tsa::WDF2Classify::operator(), "C++: tsa::WDF2Classify::operator()(class tsa::SeqView<double> &, double) --> void", pybind11::arg("Data"), pybind11::arg("sigma"));
		cl.def("__call__", (int (tsa::WDF2Classify::*)(class tsa::EventFullFeatured &)) &tsa::WDF2Classify::operator(), "C++: tsa::WDF2Classify::operator()(class tsa::EventFullFeatured &) --> int", pybind11::arg("Ev"));
		cl.def("GetEvent", (void (tsa::WDF2Classify::*)(class tsa::EventFullFeatured &)) &tsa::WDF2Classify::GetEvent, "C++: tsa::WDF2Classify::GetEvent(class tsa::EventFullFeatured &) --> void", pybind11::arg("Ev"));
		cl.def("GetDataNeeded", (int (tsa::WDF2Classify::*)()) &tsa::WDF2Classify::GetDataNeeded, "Get the number of data needed in order to be able to \n call GetData successfully. If the returned value is less or \n equal than zero no data are needed.\n\n \n the needed data\n\nC++: tsa::WDF2Classify::GetDataNeeded() --> int");
		cl.def("assign", (class tsa::WDF2Classify & (tsa::WDF2Classify::*)(const class tsa::WDF2Classify &)) &tsa::WDF2Classify::operator=, "C++: tsa::WDF2Classify::operator=(const class tsa::WDF2Classify &) --> class tsa::WDF2Classify &", pybind11::return_value_policy::automatic, pybind11::arg(""));
	}
	{ // tsa::WDF2Reconstruct file:WDF2Reconstruct.hpp line:84
		pybind11::class_<tsa::WDF2Reconstruct, std::shared_ptr<tsa::WDF2Reconstruct>, tsa::AlgoBase> cl(M("tsa"), "WDF2Reconstruct", "Time domain detection of transients based on wavelet transform");
		cl.def( pybind11::init( [](unsigned int const & a0, unsigned int const & a1, double const & a2, double const & a3, unsigned int const & a4){ return new tsa::WDF2Reconstruct(a0, a1, a2, a3, a4); } ), "doc" , pybind11::arg("window"), pybind11::arg("overlap"), pybind11::arg("thresh"), pybind11::arg("sigma"), pybind11::arg("ncoeff"));
		cl.def( pybind11::init<unsigned int, unsigned int, double, double, unsigned int, enum tsa::WaveletThreshold::WaveletThresholding>(), pybind11::arg("window"), pybind11::arg("overlap"), pybind11::arg("thresh"), pybind11::arg("sigma"), pybind11::arg("ncoeff"), pybind11::arg("WTh") );

		cl.def( pybind11::init( [](tsa::WDF2Reconstruct const &o){ return new tsa::WDF2Reconstruct(o); } ) );
		cl.def("__lshift__", (void (tsa::WDF2Reconstruct::*)(class tsa::SeqView<double> &)) &tsa::WDF2Reconstruct::operator<<, "@{\n\nC++: tsa::WDF2Reconstruct::operator<<(class tsa::SeqView<double> &) --> void", pybind11::arg("Data"));
		cl.def("__call__", (void (tsa::WDF2Reconstruct::*)(class tsa::SeqView<double> &, double)) &tsa::WDF2Reconstruct::operator(), "C++: tsa::WDF2Reconstruct::operator()(class tsa::SeqView<double> &, double) --> void", pybind11::arg("Data"), pybind11::arg("sigma"));
		cl.def("__call__", (int (tsa::WDF2Reconstruct::*)(class tsa::EventFullFeatured &)) &tsa::WDF2Reconstruct::operator(), "C++: tsa::WDF2Reconstruct::operator()(class tsa::EventFullFeatured &) --> int", pybind11::arg("Ev"));
		cl.def("GetEvent", (void (tsa::WDF2Reconstruct::*)(class tsa::EventFullFeatured &)) &tsa::WDF2Reconstruct::GetEvent, "C++: tsa::WDF2Reconstruct::GetEvent(class tsa::EventFullFeatured &) --> void", pybind11::arg("Ev"));
		cl.def("GetDataNeeded", (int (tsa::WDF2Reconstruct::*)()) &tsa::WDF2Reconstruct::GetDataNeeded, "Get the number of data needed in order to be able to \n call GetData successfully. If the returned value is less or \n equal than zero no data are needed.\n\n \n the needed data\n\nC++: tsa::WDF2Reconstruct::GetDataNeeded() --> int");
		cl.def("assign", (class tsa::WDF2Reconstruct & (tsa::WDF2Reconstruct::*)(const class tsa::WDF2Reconstruct &)) &tsa::WDF2Reconstruct::operator=, "C++: tsa::WDF2Reconstruct::operator=(const class tsa::WDF2Reconstruct &) --> class tsa::WDF2Reconstruct &", pybind11::return_value_policy::automatic, pybind11::arg(""));
	}
	{ // tsa::WelchWindow file:WelchWindow.hpp line:69
		pybind11::class_<tsa::WelchWindow, std::shared_ptr<tsa::WelchWindow>, PyCallBack_tsa_WelchWindow, tsa::BaseWindow> cl(M("tsa"), "WelchWindow", "Welch windowing algorithm\n\n ");
		cl.def( pybind11::init<int>(), pybind11::arg("size") );

		cl.def( pybind11::init<int, const std::string &>(), pybind11::arg("size"), pybind11::arg("p") );

		cl.def( pybind11::init( [](PyCallBack_tsa_WelchWindow const &o){ return new PyCallBack_tsa_WelchWindow(o); } ) );
		cl.def( pybind11::init( [](tsa::WelchWindow const &o){ return new tsa::WelchWindow(o); } ) );
		cl.def("__call__", (void (tsa::WelchWindow::*)(class tsa::SeqView<double> &)) &tsa::WelchWindow::operator(), "Apply the window to a given time view.\n\n \n the time view \n\nC++: tsa::WelchWindow::operator()(class tsa::SeqView<double> &) --> void", pybind11::arg("v1"));
		cl.def("__call__", (void (tsa::WelchWindow::*)(class tsa::SeqView<double> &, class tsa::SeqView<double> &)) &tsa::WelchWindow::operator(), "Apply a window to an input view and write the results on a \n output view.\n\n \n the input view\n \n\n the output view\n\n         \n\nC++: tsa::WelchWindow::operator()(class tsa::SeqView<double> &, class tsa::SeqView<double> &) --> void", pybind11::arg("v1"), pybind11::arg("v2"));
		cl.def("Resize", (void (tsa::WelchWindow::*)(unsigned int)) &tsa::WelchWindow::Resize, "Resize the window dimension.\n\n \n new size for the window\n\nC++: tsa::WelchWindow::Resize(unsigned int) --> void", pybind11::arg("size"));
		cl.def("assign", (class tsa::WelchWindow & (tsa::WelchWindow::*)(const class tsa::WelchWindow &)) &tsa::WelchWindow::operator=, "C++: tsa::WelchWindow::operator=(const class tsa::WelchWindow &) --> class tsa::WelchWindow &", pybind11::return_value_policy::automatic, pybind11::arg(""));
	}
	// tsa::GetWindowList() file:WindowFactory.hpp line:69
	M("tsa").def("GetWindowList", (class std::vector<std::string > (*)()) &tsa::GetWindowList, "C++: tsa::GetWindowList() --> class std::vector<std::string >");

	// tsa::WindowFactory(const std::string &, unsigned int) file:WindowFactory.hpp line:71
	M("tsa").def("WindowFactory", (class tsa::BaseWindow * (*)(const std::string &, unsigned int)) &tsa::WindowFactory, "C++: tsa::WindowFactory(const std::string &, unsigned int) --> class tsa::BaseWindow *", pybind11::return_value_policy::automatic, pybind11::arg("name"), pybind11::arg("size"));

	// tsa::WindowFactory(const std::string &, const std::string &, unsigned int) file:WindowFactory.hpp line:74
	M("tsa").def("WindowFactory", (class tsa::BaseWindow * (*)(const std::string &, const std::string &, unsigned int)) &tsa::WindowFactory, "C++: tsa::WindowFactory(const std::string &, const std::string &, unsigned int) --> class tsa::BaseWindow *", pybind11::return_value_policy::automatic, pybind11::arg("name"), pybind11::arg("parameters"), pybind11::arg("size"));

}


// File: Util.cpp
#include <SeqView.hpp>
#include <Util.hpp>
#include <boost/numeric/ublas/functional.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/storage.hpp>
#include <memory>
#include <sstream> // __str__
#include <string>

#include <functional>
#include <pybind11/pybind11.h>
#include <string>

#ifndef BINDER_PYBIND11_TYPE_CASTER
	#define BINDER_PYBIND11_TYPE_CASTER
	PYBIND11_DECLARE_HOLDER_TYPE(T, std::shared_ptr<T>)
	PYBIND11_DECLARE_HOLDER_TYPE(T, T*)
	PYBIND11_MAKE_OPAQUE(std::shared_ptr<void>)
#endif

void bind_Util(std::function< pybind11::module &(std::string const &namespace_) > &M)
{
	{ // tsa::Util file:Util.hpp line:64
		pybind11::class_<tsa::Util, std::shared_ptr<tsa::Util>, tsa::AlgoBase> cl(M("tsa"), "Util", "");
		cl.def( pybind11::init( [](){ return new tsa::Util(); } ) );
		cl.def_static("Sum", (void (*)(class tsa::SeqView<double> &, double, class tsa::SeqView<double> &)) &tsa::Util::Sum, "C++: tsa::Util::Sum(class tsa::SeqView<double> &, double, class tsa::SeqView<double> &) --> void", pybind11::arg("res"), pybind11::arg("scale"), pybind11::arg("ts"));
	}
}


// File: FrameIStream.cpp
#include <FrameIStream.hpp>
#include <FrameL.h>
#include <SeqView.hpp>
#include <boost/numeric/ublas/functional.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/storage.hpp>
#include <iterator>
#include <memory>
#include <sstream> // __str__
#include <string>
#include <vector>

#include <functional>
#include <pybind11/pybind11.h>
#include <string>

#ifndef BINDER_PYBIND11_TYPE_CASTER
	#define BINDER_PYBIND11_TYPE_CASTER
	PYBIND11_DECLARE_HOLDER_TYPE(T, std::shared_ptr<T>)
	PYBIND11_DECLARE_HOLDER_TYPE(T, T*)
	PYBIND11_MAKE_OPAQUE(std::shared_ptr<void>)
#endif

// tsa::ChannelDescriptor file:FrameIStream.hpp line:101
struct PyCallBack_tsa_ChannelDescriptor : public tsa::ChannelDescriptor {
	using tsa::ChannelDescriptor::ChannelDescriptor;

	void AddData() override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const tsa::ChannelDescriptor *>(this), "AddData");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>();
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::override_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return ChannelDescriptor::AddData();
	}
	double GetLength() override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const tsa::ChannelDescriptor *>(this), "GetLength");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>();
			if (pybind11::detail::cast_is_temporary_value_reference<double>::value) {
				static pybind11::detail::override_caster_t<double> caster;
				return pybind11::detail::cast_ref<double>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<double>(std::move(o));
		}
		return ChannelDescriptor::GetLength();
	}
	double GetRate() override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const tsa::ChannelDescriptor *>(this), "GetRate");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>();
			if (pybind11::detail::cast_is_temporary_value_reference<double>::value) {
				static pybind11::detail::override_caster_t<double> caster;
				return pybind11::detail::cast_ref<double>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<double>(std::move(o));
		}
		return ChannelDescriptor::GetRate();
	}
	void WriteView(class tsa::SeqView<double> & a0) override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const tsa::ChannelDescriptor *>(this), "WriteView");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::override_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return ChannelDescriptor::WriteView(a0);
	}
	void FillView(class tsa::SeqView<double> & a0, double a1, double a2) override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const tsa::ChannelDescriptor *>(this), "FillView");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0, a1, a2);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::override_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return ChannelDescriptor::FillView(a0, a1, a2);
	}
	void WriteView(class tsa::SeqView<double> & a0, class tsa::SeqView<double> & a1) override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const tsa::ChannelDescriptor *>(this), "WriteView");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0, a1);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::override_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return ChannelDescriptor::WriteView(a0, a1);
	}
};

// tsa::ADC_Channel file:FrameIStream.hpp line:230
struct PyCallBack_tsa_ADC_Channel : public tsa::ADC_Channel {
	using tsa::ADC_Channel::ADC_Channel;

	void AddData() override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const tsa::ADC_Channel *>(this), "AddData");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>();
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::override_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return ADC_Channel::AddData();
	}
	double GetLength() override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const tsa::ADC_Channel *>(this), "GetLength");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>();
			if (pybind11::detail::cast_is_temporary_value_reference<double>::value) {
				static pybind11::detail::override_caster_t<double> caster;
				return pybind11::detail::cast_ref<double>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<double>(std::move(o));
		}
		return ADC_Channel::GetLength();
	}
	double GetRate() override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const tsa::ADC_Channel *>(this), "GetRate");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>();
			if (pybind11::detail::cast_is_temporary_value_reference<double>::value) {
				static pybind11::detail::override_caster_t<double> caster;
				return pybind11::detail::cast_ref<double>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<double>(std::move(o));
		}
		return ChannelDescriptor::GetRate();
	}
	void WriteView(class tsa::SeqView<double> & a0) override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const tsa::ADC_Channel *>(this), "WriteView");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::override_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return ChannelDescriptor::WriteView(a0);
	}
	void FillView(class tsa::SeqView<double> & a0, double a1, double a2) override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const tsa::ADC_Channel *>(this), "FillView");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0, a1, a2);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::override_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return ChannelDescriptor::FillView(a0, a1, a2);
	}
	void WriteView(class tsa::SeqView<double> & a0, class tsa::SeqView<double> & a1) override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const tsa::ADC_Channel *>(this), "WriteView");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0, a1);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::override_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return ChannelDescriptor::WriteView(a0, a1);
	}
};

// tsa::PROC_Channel file:FrameIStream.hpp line:285
struct PyCallBack_tsa_PROC_Channel : public tsa::PROC_Channel {
	using tsa::PROC_Channel::PROC_Channel;

	void AddData() override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const tsa::PROC_Channel *>(this), "AddData");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>();
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::override_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return PROC_Channel::AddData();
	}
	double GetLength() override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const tsa::PROC_Channel *>(this), "GetLength");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>();
			if (pybind11::detail::cast_is_temporary_value_reference<double>::value) {
				static pybind11::detail::override_caster_t<double> caster;
				return pybind11::detail::cast_ref<double>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<double>(std::move(o));
		}
		return PROC_Channel::GetLength();
	}
	void FillView(class tsa::SeqView<double> & a0, double a1, double a2) override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const tsa::PROC_Channel *>(this), "FillView");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0, a1, a2);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::override_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return PROC_Channel::FillView(a0, a1, a2);
	}
	double GetRate() override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const tsa::PROC_Channel *>(this), "GetRate");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>();
			if (pybind11::detail::cast_is_temporary_value_reference<double>::value) {
				static pybind11::detail::override_caster_t<double> caster;
				return pybind11::detail::cast_ref<double>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<double>(std::move(o));
		}
		return ChannelDescriptor::GetRate();
	}
	void WriteView(class tsa::SeqView<double> & a0) override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const tsa::PROC_Channel *>(this), "WriteView");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::override_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return ChannelDescriptor::WriteView(a0);
	}
	void WriteView(class tsa::SeqView<double> & a0, class tsa::SeqView<double> & a1) override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const tsa::PROC_Channel *>(this), "WriteView");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0, a1);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::override_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return ChannelDescriptor::WriteView(a0, a1);
	}
};

// tsa::SIM_Channel file:FrameIStream.hpp line:344
struct PyCallBack_tsa_SIM_Channel : public tsa::SIM_Channel {
	using tsa::SIM_Channel::SIM_Channel;

	void AddData() override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const tsa::SIM_Channel *>(this), "AddData");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>();
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::override_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return SIM_Channel::AddData();
	}
	double GetLength() override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const tsa::SIM_Channel *>(this), "GetLength");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>();
			if (pybind11::detail::cast_is_temporary_value_reference<double>::value) {
				static pybind11::detail::override_caster_t<double> caster;
				return pybind11::detail::cast_ref<double>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<double>(std::move(o));
		}
		return SIM_Channel::GetLength();
	}
	double GetRate() override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const tsa::SIM_Channel *>(this), "GetRate");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>();
			if (pybind11::detail::cast_is_temporary_value_reference<double>::value) {
				static pybind11::detail::override_caster_t<double> caster;
				return pybind11::detail::cast_ref<double>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<double>(std::move(o));
		}
		return ChannelDescriptor::GetRate();
	}
	void WriteView(class tsa::SeqView<double> & a0) override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const tsa::SIM_Channel *>(this), "WriteView");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::override_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return ChannelDescriptor::WriteView(a0);
	}
	void FillView(class tsa::SeqView<double> & a0, double a1, double a2) override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const tsa::SIM_Channel *>(this), "FillView");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0, a1, a2);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::override_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return ChannelDescriptor::FillView(a0, a1, a2);
	}
	void WriteView(class tsa::SeqView<double> & a0, class tsa::SeqView<double> & a1) override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const tsa::SIM_Channel *>(this), "WriteView");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0, a1);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::override_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return ChannelDescriptor::WriteView(a0, a1);
	}
};

// tsa::SER_Channel file:FrameIStream.hpp line:399
struct PyCallBack_tsa_SER_Channel : public tsa::SER_Channel {
	using tsa::SER_Channel::SER_Channel;

	void AddData() override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const tsa::SER_Channel *>(this), "AddData");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>();
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::override_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return SER_Channel::AddData();
	}
	double GetLength() override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const tsa::SER_Channel *>(this), "GetLength");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>();
			if (pybind11::detail::cast_is_temporary_value_reference<double>::value) {
				static pybind11::detail::override_caster_t<double> caster;
				return pybind11::detail::cast_ref<double>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<double>(std::move(o));
		}
		return SER_Channel::GetLength();
	}
	double GetRate() override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const tsa::SER_Channel *>(this), "GetRate");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>();
			if (pybind11::detail::cast_is_temporary_value_reference<double>::value) {
				static pybind11::detail::override_caster_t<double> caster;
				return pybind11::detail::cast_ref<double>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<double>(std::move(o));
		}
		return ChannelDescriptor::GetRate();
	}
	void WriteView(class tsa::SeqView<double> & a0) override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const tsa::SER_Channel *>(this), "WriteView");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::override_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return ChannelDescriptor::WriteView(a0);
	}
	void FillView(class tsa::SeqView<double> & a0, double a1, double a2) override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const tsa::SER_Channel *>(this), "FillView");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0, a1, a2);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::override_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return ChannelDescriptor::FillView(a0, a1, a2);
	}
	void WriteView(class tsa::SeqView<double> & a0, class tsa::SeqView<double> & a1) override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const tsa::SER_Channel *>(this), "WriteView");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0, a1);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::override_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return ChannelDescriptor::WriteView(a0, a1);
	}
};

// tsa::FRAMEH_Channel file:FrameIStream.hpp line:456
struct PyCallBack_tsa_FRAMEH_Channel : public tsa::FRAMEH_Channel {
	using tsa::FRAMEH_Channel::FRAMEH_Channel;

	void AddData() override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const tsa::FRAMEH_Channel *>(this), "AddData");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>();
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::override_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return FRAMEH_Channel::AddData();
	}
	double GetLength() override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const tsa::FRAMEH_Channel *>(this), "GetLength");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>();
			if (pybind11::detail::cast_is_temporary_value_reference<double>::value) {
				static pybind11::detail::override_caster_t<double> caster;
				return pybind11::detail::cast_ref<double>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<double>(std::move(o));
		}
		return FRAMEH_Channel::GetLength();
	}
	double GetRate() override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const tsa::FRAMEH_Channel *>(this), "GetRate");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>();
			if (pybind11::detail::cast_is_temporary_value_reference<double>::value) {
				static pybind11::detail::override_caster_t<double> caster;
				return pybind11::detail::cast_ref<double>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<double>(std::move(o));
		}
		return ChannelDescriptor::GetRate();
	}
	void WriteView(class tsa::SeqView<double> & a0) override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const tsa::FRAMEH_Channel *>(this), "WriteView");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::override_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return ChannelDescriptor::WriteView(a0);
	}
	void FillView(class tsa::SeqView<double> & a0, double a1, double a2) override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const tsa::FRAMEH_Channel *>(this), "FillView");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0, a1, a2);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::override_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return ChannelDescriptor::FillView(a0, a1, a2);
	}
	void WriteView(class tsa::SeqView<double> & a0, class tsa::SeqView<double> & a1) override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const tsa::FRAMEH_Channel *>(this), "WriteView");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0, a1);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::override_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return ChannelDescriptor::WriteView(a0, a1);
	}
};

void bind_FrameIStream(std::function< pybind11::module &(std::string const &namespace_) > &M)
{
	{ // tsa::DataException file:FrameIStream.hpp line:71
		pybind11::class_<tsa::DataException, std::shared_ptr<tsa::DataException>> cl(M("tsa"), "DataException", "A small structure which contains informations about\n a data loss period.\n\n     ");
		cl.def( pybind11::init<double, double, enum tsa::DataException::exception_type>(), pybind11::arg("ts"), pybind11::arg("te"), pybind11::arg("e") );


		pybind11::enum_<tsa::DataException::exception_type>(cl, "exception_type", pybind11::arithmetic(), "Type of problem.\n\n         ")
			.value("data_loss", tsa::DataException::data_loss)
			.export_values();

		cl.def_readwrite("Exception", &tsa::DataException::Exception);
		cl.def_readwrite("StartTime", &tsa::DataException::StartTime);
		cl.def_readwrite("EndTime", &tsa::DataException::EndTime);
	}
	{ // tsa::ChannelDescriptor file:FrameIStream.hpp line:101
		pybind11::class_<tsa::ChannelDescriptor, std::shared_ptr<tsa::ChannelDescriptor>, PyCallBack_tsa_ChannelDescriptor, tsa::AlgoBase> cl(M("tsa"), "ChannelDescriptor", "A base class for the descriptor of a data channel.\n\n     ");
		cl.def( pybind11::init<unsigned int>(), pybind11::arg("id") );

		cl.def( pybind11::init( [](PyCallBack_tsa_ChannelDescriptor const &o){ return new PyCallBack_tsa_ChannelDescriptor(o); } ) );
		cl.def( pybind11::init( [](tsa::ChannelDescriptor const &o){ return new tsa::ChannelDescriptor(o); } ) );
		cl.def("AddData", (void (tsa::ChannelDescriptor::*)()) &tsa::ChannelDescriptor::AddData, "This function must be called when there are not enough data \n to fill the output view. In this base class does nothing.\n\n         \n\nC++: tsa::ChannelDescriptor::AddData() --> void");
		cl.def("GetLength", (double (tsa::ChannelDescriptor::*)()) &tsa::ChannelDescriptor::GetLength, "Get the maximul time length of data that can be currently filled\n without calling AddData.\n\n \n the time length of the data available in seconds\n\nC++: tsa::ChannelDescriptor::GetLength() --> double");
		cl.def("GetRate", (double (tsa::ChannelDescriptor::*)()) &tsa::ChannelDescriptor::GetRate, "Get the channel time rate\n\n \n \n\n the channel time rate\n\nC++: tsa::ChannelDescriptor::GetRate() --> double");
		cl.def("WriteView", (void (tsa::ChannelDescriptor::*)(class tsa::SeqView<double> &)) &tsa::ChannelDescriptor::WriteView, "A function to write the available data on an output view. Be careful\n that if there are not enough data available we get a data loss exception.\n\n \n output view where the available data are written\n\nC++: tsa::ChannelDescriptor::WriteView(class tsa::SeqView<double> &) --> void", pybind11::arg("v"));
		cl.def("FillView", (void (tsa::ChannelDescriptor::*)(class tsa::SeqView<double> &, double, double)) &tsa::ChannelDescriptor::FillView, "C++: tsa::ChannelDescriptor::FillView(class tsa::SeqView<double> &, double, double) --> void", pybind11::arg("v"), pybind11::arg("tstart"), pybind11::arg("tend"));
		cl.def("WriteView", (void (tsa::ChannelDescriptor::*)(class tsa::SeqView<double> &, class tsa::SeqView<double> &)) &tsa::ChannelDescriptor::WriteView, "A function to write the available data on an output view. Be careful\n that if there are not enough data available we get a data loss exception.\n At the same time a second view is filled with ones which correspond to \n avaliable data, or zeros which correspond to unavailable data.\n\n \n output view where the available data are written\n \n\n output view where the available data flags are written\n\nC++: tsa::ChannelDescriptor::WriteView(class tsa::SeqView<double> &, class tsa::SeqView<double> &) --> void", pybind11::arg("v"), pybind11::arg("validation"));
		cl.def("assign", (class tsa::ChannelDescriptor & (tsa::ChannelDescriptor::*)(const class tsa::ChannelDescriptor &)) &tsa::ChannelDescriptor::operator=, "C++: tsa::ChannelDescriptor::operator=(const class tsa::ChannelDescriptor &) --> class tsa::ChannelDescriptor &", pybind11::return_value_policy::automatic, pybind11::arg(""));
	}
	{ // tsa::ADC_Channel file:FrameIStream.hpp line:230
		pybind11::class_<tsa::ADC_Channel, std::shared_ptr<tsa::ADC_Channel>, PyCallBack_tsa_ADC_Channel, tsa::ChannelDescriptor> cl(M("tsa"), "ADC_Channel", "A descriptor for an ADC channel\n\n     ");
		cl.def( pybind11::init<class tsa::FrameIStream *, struct FrAdcData *, unsigned int>(), pybind11::arg("FIS"), pybind11::arg("adc"), pybind11::arg("id") );

		cl.def( pybind11::init( [](PyCallBack_tsa_ADC_Channel const &o){ return new PyCallBack_tsa_ADC_Channel(o); } ) );
		cl.def( pybind11::init( [](tsa::ADC_Channel const &o){ return new tsa::ADC_Channel(o); } ) );
		cl.def("AddData", (void (tsa::ADC_Channel::*)()) &tsa::ADC_Channel::AddData, "This function must be called when there are not enough data \n to fill the output view. It reads a chunk of data from the \n current frame\n\n         \n\nC++: tsa::ADC_Channel::AddData() --> void");
		cl.def("GetLength", (double (tsa::ADC_Channel::*)()) &tsa::ADC_Channel::GetLength, "Get the maximul time length of data that can be currently filled\n without calling AddData.\n\n \n the time length of the data available in seconds\n\nC++: tsa::ADC_Channel::GetLength() --> double");
		cl.def_static("Create", (class tsa::ADC_Channel * (*)(class tsa::FrameIStream *, char *, unsigned int)) &tsa::ADC_Channel::Create, "Create, if possible, an instance of the class\n\n \n pointer to the FrameIStream class instance\n \n\n name of the channel\n \n\n index of the channel\n\n \n pointer to the created class instance or null\n\nC++: tsa::ADC_Channel::Create(class tsa::FrameIStream *, char *, unsigned int) --> class tsa::ADC_Channel *", pybind11::return_value_policy::automatic, pybind11::arg("FIS"), pybind11::arg("name"), pybind11::arg("id"));
		cl.def("assign", (class tsa::ADC_Channel & (tsa::ADC_Channel::*)(const class tsa::ADC_Channel &)) &tsa::ADC_Channel::operator=, "C++: tsa::ADC_Channel::operator=(const class tsa::ADC_Channel &) --> class tsa::ADC_Channel &", pybind11::return_value_policy::automatic, pybind11::arg(""));
	}
	{ // tsa::PROC_Channel file:FrameIStream.hpp line:285
		pybind11::class_<tsa::PROC_Channel, std::shared_ptr<tsa::PROC_Channel>, PyCallBack_tsa_PROC_Channel, tsa::ChannelDescriptor> cl(M("tsa"), "PROC_Channel", "A descriptor for a proc channel\n\n     ");
		cl.def( pybind11::init<class tsa::FrameIStream *, struct FrProcData *, unsigned int>(), pybind11::arg("FIS"), pybind11::arg("proc"), pybind11::arg("id") );

		cl.def( pybind11::init( [](PyCallBack_tsa_PROC_Channel const &o){ return new PyCallBack_tsa_PROC_Channel(o); } ) );
		cl.def( pybind11::init( [](tsa::PROC_Channel const &o){ return new tsa::PROC_Channel(o); } ) );
		cl.def("AddData", (void (tsa::PROC_Channel::*)()) &tsa::PROC_Channel::AddData, "This function must be called when there are not enough data \n to fill the output view. It reads a chunk of data from the next\n FrProcData structure.\n\n         \n\nC++: tsa::PROC_Channel::AddData() --> void");
		cl.def("GetLength", (double (tsa::PROC_Channel::*)()) &tsa::PROC_Channel::GetLength, "Get the maximul time length of data that can be currently filled\n without calling AddData.\n\n \n the time length of the data available in seconds\n\nC++: tsa::PROC_Channel::GetLength() --> double");
		cl.def_static("Create", (class tsa::PROC_Channel * (*)(class tsa::FrameIStream *, char *, unsigned int)) &tsa::PROC_Channel::Create, "Create, if possible, an instance of the class\n\n \n pointer to the FrameIStream class instance\n \n\n name of the channel\n \n\n index of the channel\n\n \n pointer to the created class instance or null\n\nC++: tsa::PROC_Channel::Create(class tsa::FrameIStream *, char *, unsigned int) --> class tsa::PROC_Channel *", pybind11::return_value_policy::automatic, pybind11::arg("FIS"), pybind11::arg("name"), pybind11::arg("id"));
		cl.def("FillView", (void (tsa::PROC_Channel::*)(class tsa::SeqView<double> &, double, double)) &tsa::PROC_Channel::FillView, "C++: tsa::PROC_Channel::FillView(class tsa::SeqView<double> &, double, double) --> void", pybind11::arg("v"), pybind11::arg("tstart"), pybind11::arg("tend"));
		cl.def("assign", (class tsa::PROC_Channel & (tsa::PROC_Channel::*)(const class tsa::PROC_Channel &)) &tsa::PROC_Channel::operator=, "C++: tsa::PROC_Channel::operator=(const class tsa::PROC_Channel &) --> class tsa::PROC_Channel &", pybind11::return_value_policy::automatic, pybind11::arg(""));
	}
	{ // tsa::SIM_Channel file:FrameIStream.hpp line:344
		pybind11::class_<tsa::SIM_Channel, std::shared_ptr<tsa::SIM_Channel>, PyCallBack_tsa_SIM_Channel, tsa::ChannelDescriptor> cl(M("tsa"), "SIM_Channel", "A descriptor for a SIM channel\n\n     ");
		cl.def( pybind11::init<class tsa::FrameIStream *, struct FrSimData *, unsigned int>(), pybind11::arg("FIS"), pybind11::arg("sim"), pybind11::arg("id") );

		cl.def( pybind11::init( [](PyCallBack_tsa_SIM_Channel const &o){ return new PyCallBack_tsa_SIM_Channel(o); } ) );
		cl.def( pybind11::init( [](tsa::SIM_Channel const &o){ return new tsa::SIM_Channel(o); } ) );
		cl.def("AddData", (void (tsa::SIM_Channel::*)()) &tsa::SIM_Channel::AddData, "This function must be called when there are not enough data \n to fill the output view. It reads a chunk of data from the next\n FrSimData structure.\n\n         \n\nC++: tsa::SIM_Channel::AddData() --> void");
		cl.def("GetLength", (double (tsa::SIM_Channel::*)()) &tsa::SIM_Channel::GetLength, "Get the maximul time length of data that can be currently filled\n without calling AddData.\n\n \n the time length of the data available in seconds\n\nC++: tsa::SIM_Channel::GetLength() --> double");
		cl.def_static("Create", (class tsa::SIM_Channel * (*)(class tsa::FrameIStream *, char *, unsigned int)) &tsa::SIM_Channel::Create, "Create, if possible, an instance of the class\n\n \n pointer to the FrameIStream class instance\n \n\n name of the channel\n \n\n index of the channel\n\n \n pointer to the created class instance or null\n\nC++: tsa::SIM_Channel::Create(class tsa::FrameIStream *, char *, unsigned int) --> class tsa::SIM_Channel *", pybind11::return_value_policy::automatic, pybind11::arg("FIS"), pybind11::arg("name"), pybind11::arg("id"));
		cl.def("assign", (class tsa::SIM_Channel & (tsa::SIM_Channel::*)(const class tsa::SIM_Channel &)) &tsa::SIM_Channel::operator=, "C++: tsa::SIM_Channel::operator=(const class tsa::SIM_Channel &) --> class tsa::SIM_Channel &", pybind11::return_value_policy::automatic, pybind11::arg(""));
	}
	{ // tsa::SER_Channel file:FrameIStream.hpp line:399
		pybind11::class_<tsa::SER_Channel, std::shared_ptr<tsa::SER_Channel>, PyCallBack_tsa_SER_Channel, tsa::ChannelDescriptor> cl(M("tsa"), "SER_Channel", "A descriptor for a SER channel\n\n     ");
		cl.def( pybind11::init<class tsa::FrameIStream *, char *, char *, unsigned int>(), pybind11::arg("FIS"), pybind11::arg("smsName"), pybind11::arg("smsParam"), pybind11::arg("id") );

		cl.def( pybind11::init( [](PyCallBack_tsa_SER_Channel const &o){ return new PyCallBack_tsa_SER_Channel(o); } ) );
		cl.def( pybind11::init( [](tsa::SER_Channel const &o){ return new tsa::SER_Channel(o); } ) );
		cl.def("AddData", (void (tsa::SER_Channel::*)()) &tsa::SER_Channel::AddData, "This function must be called when there are not enough data \n to fill the output view. It reads a chunk of data from the next\n serial data structure.\n\n         \n\nC++: tsa::SER_Channel::AddData() --> void");
		cl.def("GetLength", (double (tsa::SER_Channel::*)()) &tsa::SER_Channel::GetLength, "Get the maximul time length of data that can be currently filled\n without calling AddData.\n\n \n the time length of the data available in seconds\n\nC++: tsa::SER_Channel::GetLength() --> double");
		cl.def_static("Create", (class tsa::SER_Channel * (*)(class tsa::FrameIStream *, char *, unsigned int)) &tsa::SER_Channel::Create, "Create, if possible, an instance of the class\n\n \n pointer to the FrameIStream class instance\n \n\n name of the channel\n \n\n index of the channel\n\n \n pointer to the created class instance or null\n\nC++: tsa::SER_Channel::Create(class tsa::FrameIStream *, char *, unsigned int) --> class tsa::SER_Channel *", pybind11::return_value_policy::automatic, pybind11::arg("FIS"), pybind11::arg("name"), pybind11::arg("id"));
		cl.def("assign", (class tsa::SER_Channel & (tsa::SER_Channel::*)(const class tsa::SER_Channel &)) &tsa::SER_Channel::operator=, "C++: tsa::SER_Channel::operator=(const class tsa::SER_Channel &) --> class tsa::SER_Channel &", pybind11::return_value_policy::automatic, pybind11::arg(""));
	}
	{ // tsa::FRAMEH_Channel file:FrameIStream.hpp line:456
		pybind11::class_<tsa::FRAMEH_Channel, std::shared_ptr<tsa::FRAMEH_Channel>, PyCallBack_tsa_FRAMEH_Channel, tsa::ChannelDescriptor> cl(M("tsa"), "FRAMEH_Channel", "Descriptor for a FrameH field channel.\n\n     ");
		cl.def( pybind11::init<class tsa::FrameIStream *, enum tsa::FRAMEH_Channel::field_type, unsigned int>(), pybind11::arg("FIS"), pybind11::arg("ft"), pybind11::arg("id") );

		cl.def( pybind11::init( [](PyCallBack_tsa_FRAMEH_Channel const &o){ return new PyCallBack_tsa_FRAMEH_Channel(o); } ) );
		cl.def( pybind11::init( [](tsa::FRAMEH_Channel const &o){ return new tsa::FRAMEH_Channel(o); } ) );

		pybind11::enum_<tsa::FRAMEH_Channel::field_type>(cl, "field_type", pybind11::arithmetic(), "Field type in the frame to dump on channel\n\n         ")
			.value("field_run", tsa::FRAMEH_Channel::field_run)
			.value("field_frame", tsa::FRAMEH_Channel::field_frame)
			.value("field_dataQuality", tsa::FRAMEH_Channel::field_dataQuality)
			.value("field_GTimeS", tsa::FRAMEH_Channel::field_GTimeS)
			.value("field_GTimeN", tsa::FRAMEH_Channel::field_GTimeN)
			.value("field_ULeapS", tsa::FRAMEH_Channel::field_ULeapS)
			.value("field_dt", tsa::FRAMEH_Channel::field_dt)
			.value("field_time", tsa::FRAMEH_Channel::field_time)
			.export_values();

		cl.def("AddData", (void (tsa::FRAMEH_Channel::*)()) &tsa::FRAMEH_Channel::AddData, "This function must be called when there are not enough data \n to fill the output view. It reads a chunk of data from the \n current frame.\n\n         \n\nC++: tsa::FRAMEH_Channel::AddData() --> void");
		cl.def("GetLength", (double (tsa::FRAMEH_Channel::*)()) &tsa::FRAMEH_Channel::GetLength, "Get the maximul time length of data that can be currently filled\n without calling AddData.\n\n \n the time length of the data available in seconds\n\nC++: tsa::FRAMEH_Channel::GetLength() --> double");
		cl.def_static("Create", (class tsa::FRAMEH_Channel * (*)(class tsa::FrameIStream *, char *, unsigned int)) &tsa::FRAMEH_Channel::Create, "Create, if possible, an instance of the class\n\n \n pointer to the FrameIStream class instance\n \n\n name of the channel\n \n\n index of the channel\n\n \n pointer to the created class instance or null\n\nC++: tsa::FRAMEH_Channel::Create(class tsa::FrameIStream *, char *, unsigned int) --> class tsa::FRAMEH_Channel *", pybind11::return_value_policy::automatic, pybind11::arg("FIS"), pybind11::arg("field_name"), pybind11::arg("id"));
		cl.def("assign", (class tsa::FRAMEH_Channel & (tsa::FRAMEH_Channel::*)(const class tsa::FRAMEH_Channel &)) &tsa::FRAMEH_Channel::operator=, "C++: tsa::FRAMEH_Channel::operator=(const class tsa::FRAMEH_Channel &) --> class tsa::FRAMEH_Channel &", pybind11::return_value_policy::automatic, pybind11::arg(""));
	}
	{ // tsa::FrameIStream file:FrameIStream.hpp line:536
		pybind11::class_<tsa::FrameIStream, std::shared_ptr<tsa::FrameIStream>, tsa::AlgoBase> cl(M("tsa"), "FrameIStream", "A source of data taken from a Frame file\n\n This class can be used to read data from a frame file. \n A set of channels can be specified, which are returned together.\n\n \n\n Ser data:\n\n Channel:Parameter:Frequency:Default");
		cl.def( pybind11::init<const std::string &, const double &>(), pybind11::arg("fileName"), pybind11::arg("StartTime") );

		cl.def( pybind11::init<const std::string &, const double &, const double &, const class std::vector<std::string > &>(), pybind11::arg("fileName"), pybind11::arg("StartTime"), pybind11::arg("TimeLength"), pybind11::arg("channelNames") );

		cl.def( pybind11::init( [](tsa::FrameIStream const &o){ return new tsa::FrameIStream(o); } ) );
		cl.def("Init", (void (tsa::FrameIStream::*)()) &tsa::FrameIStream::Init, "C++: tsa::FrameIStream::Init() --> void");
		cl.def("__rshift__", (class tsa::FrameIStream & (tsa::FrameIStream::*)(class tsa::SeqView<double> &)) &tsa::FrameIStream::operator>>, "Read data from the frame file. \n\n \n A list a time view to fill with data.  It contains a single channel.\n\n \n a reference to the instance of the class\n\nC++: tsa::FrameIStream::operator>>(class tsa::SeqView<double> &) --> class tsa::FrameIStream &", pybind11::return_value_policy::automatic, pybind11::arg("rSeqView"));
		cl.def("FillView", (void (tsa::FrameIStream::*)(class tsa::SeqView<double> &, double, double)) &tsa::FrameIStream::FillView, "C++: tsa::FrameIStream::FillView(class tsa::SeqView<double> &, double, double) --> void", pybind11::arg("rSeqView"), pybind11::arg("tstart"), pybind11::arg("tend"));
		cl.def("GetInfo", [](tsa::FrameIStream &o) -> std::string { return o.GetInfo(); }, "");
		cl.def("GetInfo", (std::string (tsa::FrameIStream::*)(int)) &tsa::FrameIStream::GetInfo, "C++: tsa::FrameIStream::GetInfo(int) --> std::string", pybind11::arg("gtime"));
		cl.def("GetFileName", (const std::string & (tsa::FrameIStream::*)() const) &tsa::FrameIStream::GetFileName, "Get the file name of the frame file used.\n\n \n the file name of the frame file\n\nC++: tsa::FrameIStream::GetFileName() const --> const std::string &", pybind11::return_value_policy::automatic);
		cl.def("GetChannelNames", (const class std::vector<std::string > & (tsa::FrameIStream::*)() const) &tsa::FrameIStream::GetChannelNames, "Get the list of the channel's names.\n\n \n a list of channel's names\n\nC++: tsa::FrameIStream::GetChannelNames() const --> const class std::vector<std::string > &", pybind11::return_value_policy::automatic);
		cl.def("GetStartTime", (double (tsa::FrameIStream::*)() const) &tsa::FrameIStream::GetStartTime, "Get the actual start time, which is the start time\n of the next data chunk that will be read.\n\n \n the actual start time\n\nC++: tsa::FrameIStream::GetStartTime() const --> double");
		cl.def("GetEndTime", (double (tsa::FrameIStream::*)() const) &tsa::FrameIStream::GetEndTime, "Get the actual end time, which is the end time\n of the next data chunk that will be read.\n\n \n the actual end time\n\nC++: tsa::FrameIStream::GetEndTime() const --> double");
		cl.def("GetSampling", (double (tsa::FrameIStream::*)(unsigned int) const) &tsa::FrameIStream::GetSampling, "Get the sampling time of a channel\n\n \n the channel's name\n\n \n the channel's sampling time\n\nC++: tsa::FrameIStream::GetSampling(unsigned int) const --> double", pybind11::arg("cn"));
		cl.def("GetTimeLength", (double (tsa::FrameIStream::*)()) &tsa::FrameIStream::GetTimeLength, "Get the time duration of the next data chunk that will be \n read.\n\n \n the actual time duration.\n\nC++: tsa::FrameIStream::GetTimeLength() --> double");
		cl.def("GetFrame", (struct FrameH * (tsa::FrameIStream::*)()) &tsa::FrameIStream::GetFrame, "Get a pointer to the current FrameH structure.\n\n \n \n\n a pointer to the current FrameH\n\nC++: tsa::FrameIStream::GetFrame() --> struct FrameH *", pybind11::return_value_policy::automatic);
		cl.def("GetFrameFile", (struct FrFile * (tsa::FrameIStream::*)()) &tsa::FrameIStream::GetFrameFile, "C++: tsa::FrameIStream::GetFrameFile() --> struct FrFile *", pybind11::return_value_policy::automatic);
		cl.def("GetDataLossFlag", (bool (tsa::FrameIStream::*)()) &tsa::FrameIStream::GetDataLossFlag, "Get the value of the data loss flag. It is\n true if a data loss event is occurred.\n\n \n the data loss flag value\n\nC++: tsa::FrameIStream::GetDataLossFlag() --> bool");
		cl.def("SetChannels", (void (tsa::FrameIStream::*)(const class std::vector<std::string > &)) &tsa::FrameIStream::SetChannels, "Set the channels which should be opened\n\n \n vector of names for the channels\n\nC++: tsa::FrameIStream::SetChannels(const class std::vector<std::string > &) --> void", pybind11::arg("channelNames"));
		cl.def("SetTimeLength", (void (tsa::FrameIStream::*)(double)) &tsa::FrameIStream::SetTimeLength, "Set the length of the data buffer that will be returned from now on\n \n\n the new length\n\nC++: tsa::FrameIStream::SetTimeLength(double) --> void", pybind11::arg("length"));
		cl.def("ResetValidationView", (void (tsa::FrameIStream::*)()) &tsa::FrameIStream::ResetValidationView, "Set to zero the validation view. No validation data are\n written.\n\nC++: tsa::FrameIStream::ResetValidationView() --> void");
		cl.def("SetDataLossFlag", (void (tsa::FrameIStream::*)(bool)) &tsa::FrameIStream::SetDataLossFlag, "Set the value of the data loss flag.\n\n \n new value of the data loss flag\n\nC++: tsa::FrameIStream::SetDataLossFlag(bool) --> void", pybind11::arg("status"));
		cl.def("AddException", (void (tsa::FrameIStream::*)(const std::string &, double, double, unsigned int)) &tsa::FrameIStream::AddException, "Ad an exception to the set of data losses.\n\n \n exception textual message\n \n\n start time for data loss\n \n\n end time for data loss (excluded)\n \n\n channel where the data loss occurred\n\nC++: tsa::FrameIStream::AddException(const std::string &, double, double, unsigned int) --> void", pybind11::arg("msg"), pybind11::arg("miss_start"), pybind11::arg("miss_end"), pybind11::arg("channel"));
		cl.def("assign", (class tsa::FrameIStream & (tsa::FrameIStream::*)(const class tsa::FrameIStream &)) &tsa::FrameIStream::operator=, "C++: tsa::FrameIStream::operator=(const class tsa::FrameIStream &) --> class tsa::FrameIStream &", pybind11::return_value_policy::automatic, pybind11::arg(""));
	}
}


// File: FrameIChannel.cpp
#include <FrameIChannel.hpp>
#include <SeqView.hpp>
#include <boost/numeric/ublas/functional.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/storage.hpp>
#include <iterator>
#include <memory>
#include <sstream> // __str__
#include <string>

#include <functional>
#include <pybind11/pybind11.h>
#include <string>

#ifndef BINDER_PYBIND11_TYPE_CASTER
	#define BINDER_PYBIND11_TYPE_CASTER
	PYBIND11_DECLARE_HOLDER_TYPE(T, std::shared_ptr<T>)
	PYBIND11_DECLARE_HOLDER_TYPE(T, T*)
	PYBIND11_MAKE_OPAQUE(std::shared_ptr<void>)
#endif

void bind_FrameIChannel(std::function< pybind11::module &(std::string const &namespace_) > &M)
{
	{ // tsa::FrameIChannel file:FrameIChannel.hpp line:82
		pybind11::class_<tsa::FrameIChannel, std::shared_ptr<tsa::FrameIChannel>, tsa::AlgoBase> cl(M("tsa"), "FrameIChannel", "A source of data taken from a Frame file\n\n This class can be used to read data from a frame file, in a single channel. ");
		cl.def( pybind11::init( [](const std::string & a0, const std::string & a1){ return new tsa::FrameIChannel(a0, a1); } ), "doc" , pybind11::arg("fileName"), pybind11::arg("channelName"));
		cl.def( pybind11::init( [](const std::string & a0, const std::string & a1, double const & a2){ return new tsa::FrameIChannel(a0, a1, a2); } ), "doc" , pybind11::arg("fileName"), pybind11::arg("channelName"), pybind11::arg("dLength"));
		cl.def( pybind11::init<const std::string &, const std::string &, double, double>(), pybind11::arg("fileName"), pybind11::arg("channelName"), pybind11::arg("dLength"), pybind11::arg("tStart") );

		cl.def( pybind11::init( [](tsa::FrameIChannel const &o){ return new tsa::FrameIChannel(o); } ) );
		cl.def("NextSlice", (double (tsa::FrameIChannel::*)()) &tsa::FrameIChannel::NextSlice, "C++: tsa::FrameIChannel::NextSlice() --> double");
		cl.def("GetData", (bool (tsa::FrameIChannel::*)(class tsa::SeqView<double> &, double, double)) &tsa::FrameIChannel::GetData, "Get a specified slice of data. After this call, start time will be\n set to tStart+dLength and data length to dLength\n\n \n the view to fill with data\n \n\n start time of the data returned \n \n\n length of data returned by \n\nC++: tsa::FrameIChannel::GetData(class tsa::SeqView<double> &, double, double) --> bool", pybind11::arg("rSeqView"), pybind11::arg("tStart"), pybind11::arg("dLength"));
		cl.def("GetData", (bool (tsa::FrameIChannel::*)(class tsa::SeqView<double> &)) &tsa::FrameIChannel::GetData, "Get a slice of data the current data length, starting \n from the current start time.\n\n \n the view to fill with data\n\nC++: tsa::FrameIChannel::GetData(class tsa::SeqView<double> &) --> bool", pybind11::arg("rSeqView"));
		cl.def_static("GetChannelList", [](const std::string & a0) -> std::string { return tsa::FrameIChannel::GetChannelList(a0); }, "", pybind11::arg("fileName"));
		cl.def_static("GetChannelList", (std::string (*)(const std::string &, int)) &tsa::FrameIChannel::GetChannelList, "C++: tsa::FrameIChannel::GetChannelList(const std::string &, int) --> std::string", pybind11::arg("fileName"), pybind11::arg("gtime"));
		cl.def("SetStartTime", (void (tsa::FrameIChannel::*)(double)) &tsa::FrameIChannel::SetStartTime, "C++: tsa::FrameIChannel::SetStartTime(double) --> void", pybind11::arg("tStart"));
		cl.def("SetDataLength", (void (tsa::FrameIChannel::*)(double)) &tsa::FrameIChannel::SetDataLength, "C++: tsa::FrameIChannel::SetDataLength(double) --> void", pybind11::arg("dLength"));
		cl.def("SetAutoIncrement", (void (tsa::FrameIChannel::*)(bool)) &tsa::FrameIChannel::SetAutoIncrement, "C++: tsa::FrameIChannel::SetAutoIncrement(bool) --> void", pybind11::arg("status"));
		cl.def("assign", (class tsa::FrameIChannel & (tsa::FrameIChannel::*)(const class tsa::FrameIChannel &)) &tsa::FrameIChannel::operator=, "C++: tsa::FrameIChannel::operator=(const class tsa::FrameIChannel &) --> class tsa::FrameIChannel &", pybind11::return_value_policy::automatic, pybind11::arg(""));
	}
}


#include <map>
#include <algorithm>
#include <functional>
#include <memory>
#include <stdexcept>
#include <string>

#include <pybind11/pybind11.h>

typedef std::function< pybind11::module & (std::string const &) > ModuleGetter;

void bind_std_exception(std::function< pybind11::module &(std::string const &namespace_) > &M);
void bind_std_stl_vector(std::function< pybind11::module &(std::string const &namespace_) > &M);
void bind_std_stl_map(std::function< pybind11::module &(std::string const &namespace_) > &M);
void bind_std_stdexcept(std::function< pybind11::module &(std::string const &namespace_) > &M);
void bind_eternity_persist(std::function< pybind11::module &(std::string const &namespace_) > &M);
void bind_eternity_persist_xml(std::function< pybind11::module &(std::string const &namespace_) > &M);
void bind_tsaTraits(std::function< pybind11::module &(std::string const &namespace_) > &M);
void bind_tsaUtilityFunctions(std::function< pybind11::module &(std::string const &namespace_) > &M);
void bind_LatticeView(std::function< pybind11::module &(std::string const &namespace_) > &M);
void bind_FrameL(std::function< pybind11::module &(std::string const &namespace_) > &M);
void bind_SeqView(std::function< pybind11::module &(std::string const &namespace_) > &M);
void bind_AlgoExceptions(std::function< pybind11::module &(std::string const &namespace_) > &M);
void bind_Parcor2AR(std::function< pybind11::module &(std::string const &namespace_) > &M);
void bind_BaseFFT(std::function< pybind11::module &(std::string const &namespace_) > &M);
void bind_BLInterpolation(std::function< pybind11::module &(std::string const &namespace_) > &M);
void bind_DoubleWhitening(std::function< pybind11::module &(std::string const &namespace_) > &M);
void bind_LSLLearning(std::function< pybind11::module &(std::string const &namespace_) > &M);
void bind_TF2Psd(std::function< pybind11::module &(std::string const &namespace_) > &M);
void bind_WaveletThreshold(std::function< pybind11::module &(std::string const &namespace_) > &M);
void bind_Util(std::function< pybind11::module &(std::string const &namespace_) > &M);
void bind_FrameIStream(std::function< pybind11::module &(std::string const &namespace_) > &M);
void bind_FrameIChannel(std::function< pybind11::module &(std::string const &namespace_) > &M);


PYBIND11_MODULE(pytsa, root_module) {
	root_module.doc() = "pytsa module";

	std::map <std::string, pybind11::module> modules;
	ModuleGetter M = [&](std::string const &namespace_) -> pybind11::module & {
		auto it = modules.find(namespace_);
		if( it == modules.end() ) throw std::runtime_error("Attempt to access pybind11::module for namespace " + namespace_ + " before it was created!!!");
		return it->second;
	};

	modules[""] = root_module;

	static std::vector<std::string> const reserved_python_words {"nonlocal", "global", };

	auto mangle_namespace_name(
		[](std::string const &ns) -> std::string {
			if ( std::find(reserved_python_words.begin(), reserved_python_words.end(), ns) == reserved_python_words.end() ) return ns;
			else return ns+'_';
		}
	);

	std::vector< std::pair<std::string, std::string> > sub_modules {
		{"", "eternity"},
		{"", "std"},
		{"", "tsa"},
	};
	for(auto &p : sub_modules ) modules[p.first.size() ? p.first+"::"+p.second : p.second] = modules[p.first].def_submodule( mangle_namespace_name(p.second).c_str(), ("Bindings for " + p.first + "::" + p.second + " namespace").c_str() );

	//pybind11::class_<std::shared_ptr<void>>(M(""), "_encapsulated_data_");

	bind_std_exception(M);
	bind_std_stl_vector(M);
	bind_std_stl_map(M);
	bind_std_stdexcept(M);
	bind_eternity_persist(M);
	bind_eternity_persist_xml(M);
	bind_tsaTraits(M);
	bind_tsaUtilityFunctions(M);
	bind_LatticeView(M);
	bind_FrameL(M);
	bind_SeqView(M);
	bind_AlgoExceptions(M);
	bind_Parcor2AR(M);
	bind_BaseFFT(M);
	bind_BLInterpolation(M);
	bind_DoubleWhitening(M);
	bind_LSLLearning(M);
	bind_TF2Psd(M);
	bind_WaveletThreshold(M);
	bind_Util(M);
	bind_FrameIStream(M);
	bind_FrameIChannel(M);

}

// Source list file: ./python-wrapper//pytsa.sources
// pytsa.cpp
// std/exception.cpp
// std/stl_vector.cpp
// std/stl_map.cpp
// std/stdexcept.cpp
// eternity/persist.cpp
// eternity/persist_xml.cpp
// tsaTraits.cpp
// tsaUtilityFunctions.cpp
// LatticeView.cpp
// FrameL.cpp
// SeqView.cpp
// AlgoExceptions.cpp
// Parcor2AR.cpp
// BaseFFT.cpp
// BLInterpolation.cpp
// DoubleWhitening.cpp
// LSLLearning.cpp
// TF2Psd.cpp
// WaveletThreshold.cpp
// Util.cpp
// FrameIStream.cpp
// FrameIChannel.cpp

// Modules list file: ./python-wrapper//pytsa.modules
// eternity std tsa 
