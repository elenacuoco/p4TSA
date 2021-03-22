// File: eternity/persist.cpp
#include <eternity/persist.hpp>
#include <functional>
#include <initializer_list>
#include <iterator>
#include <memory>
#include <sstream> // __str__
#include <string>

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#ifndef BINDER_PYBIND11_TYPE_CASTER
	#define BINDER_PYBIND11_TYPE_CASTER
	PYBIND11_DECLARE_HOLDER_TYPE(T, std::shared_ptr<T>);
	PYBIND11_DECLARE_HOLDER_TYPE(T, T*);
#endif

void bind_eternity_persist(std::function< pybind11::module &(std::string const &namespace_) > &M)
{
	{ // eternity::archive file:eternity/persist.hpp line:47
		pybind11::class_<eternity::archive, std::shared_ptr<eternity::archive>> cl(M("eternity"), "archive", "This class supply common services for all\n        kind of persistence archives. The major one\n        is the ability to stored doubled pointers only\n        one time and so avoid circularity, broken links\n        and lost spaces on hard disks.");
		pybind11::handle cl_type = cl;

		cl.def(pybind11::init<>());

		cl.def(pybind11::init<const class eternity::archive &>(), pybind11::arg(""));

		pybind11::enum_<eternity::archive::opening_mode>(cl, "opening_mode", "")
			.value("load", eternity::archive::opening_mode::load)
			.value("store", eternity::archive::opening_mode::store)
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
#include <eternity/algorithms.hpp>
#include <eternity/persist.hpp>
#include <eternity/persist_xml.hpp>
#include <functional>
#include <initializer_list>
#include <iterator>
#include <map>
#include <memory>
#include <sstream> // __str__
#include <string>
#include <utility>

#include <pybind11/pybind11.h>

#ifndef BINDER_PYBIND11_TYPE_CASTER
	#define BINDER_PYBIND11_TYPE_CASTER
	PYBIND11_DECLARE_HOLDER_TYPE(T, std::shared_ptr<T>);
	PYBIND11_DECLARE_HOLDER_TYPE(T, T*);
#endif

void bind_eternity_persist_xml(std::function< pybind11::module &(std::string const &namespace_) > &M)
{
	{ // eternity::xml_archive file:eternity/persist_xml.hpp line:39
		pybind11::class_<eternity::xml_archive, std::shared_ptr<eternity::xml_archive>, eternity::archive> cl(M("eternity"), "xml_archive", "xml_archive is the specialization of class archive able\n        to manage XML persistence.");
		pybind11::handle cl_type = cl;

		cl.def(pybind11::init<>());

		cl.def("close", (void (eternity::xml_archive::*)()) &eternity::xml_archive::close, "End the persistence operation, release the file\n      handle and clear all allocated buffers.\n\nC++: eternity::xml_archive::close() --> void");
		cl.def("done", (void (eternity::xml_archive::*)()) &eternity::xml_archive::done, "End the persistence operation, release the file\n      handle and clear all allocated buffers.\n          Deprecated: use close instead\n\nC++: eternity::xml_archive::done() --> void");
		cl.def("formatting", (void (eternity::xml_archive::*)()) &eternity::xml_archive::formatting, "Indent XML output for nested class persistence\n\nC++: eternity::xml_archive::formatting() --> void");
		cl.def("leave_current_branch", (void (eternity::xml_archive::*)()) &eternity::xml_archive::leave_current_branch, "Leaves current node and returns to its parent\n\nC++: eternity::xml_archive::leave_current_branch() --> void");
	}
}


// File: tsaUtilityFunctions.cpp
#include <ARMAView.hpp>
#include <BaseView.hpp>
#include <eternity/persist.hpp>
#include <eternity/persist_xml.hpp>
#include <functional>
#include <initializer_list>
#include <iterator>
#include <map>
#include <memory>
#include <sstream> // __str__
#include <string>
#include <tsaLog.hpp>
#include <tsaSerialize.hpp>
#include <tsaUtilityFunctions.hpp>
#include <utility>

#include <pybind11/pybind11.h>

#ifndef BINDER_PYBIND11_TYPE_CASTER
	#define BINDER_PYBIND11_TYPE_CASTER
	PYBIND11_DECLARE_HOLDER_TYPE(T, std::shared_ptr<T>);
	PYBIND11_DECLARE_HOLDER_TYPE(T, T*);
#endif

void bind_tsaUtilityFunctions(std::function< pybind11::module &(std::string const &namespace_) > &M)
{
	{ // tsa::ParseParameterString file:tsaUtilityFunctions.hpp line:74
		pybind11::class_<tsa::ParseParameterString, std::shared_ptr<tsa::ParseParameterString>> cl(M("tsa"), "ParseParameterString", "");
		pybind11::handle cl_type = cl;

		cl.def(pybind11::init<const class std::basic_string<char> &>(), pybind11::arg("parlist"));

		cl.def(pybind11::init<const class tsa::ParseParameterString &>(), pybind11::arg(""));

		cl.def("GetFloat", (double (tsa::ParseParameterString::*)(int)) &tsa::ParseParameterString::GetFloat, "C++: tsa::ParseParameterString::GetFloat(int) --> double", pybind11::arg("n"));
		cl.def("GetInt", (int (tsa::ParseParameterString::*)(int)) &tsa::ParseParameterString::GetInt, "C++: tsa::ParseParameterString::GetInt(int) --> int", pybind11::arg("n"));
	}
	{ // tsa::MathUtils file:tsaUtilityFunctions.hpp line:140
		pybind11::class_<tsa::MathUtils, std::shared_ptr<tsa::MathUtils>> cl(M("tsa"), "MathUtils", "");
		pybind11::handle cl_type = cl;

		cl.def(pybind11::init<>());
		cl.def_static("isqrt", (unsigned int (*)(unsigned long)) &tsa::MathUtils::isqrt, "Evaluate the integer square root of a number.\n\n \n input number\n\n \n integer square root of val\n\nC++: tsa::MathUtils::isqrt(unsigned long) --> unsigned int", pybind11::arg("val"));
		cl.def_static("gcd", (int (*)(int, int)) &tsa::MathUtils::gcd, "Find the great common divisor between two numbers u and v\n\n \n first number\n \n\n second number\n\n \n the great common divisor between u and v\n\nC++: tsa::MathUtils::gcd(int, int) --> int", pybind11::arg("u"), pybind11::arg("v"));
		cl.def_static("max", (int (*)(int, int)) &tsa::MathUtils::max, "C++: tsa::MathUtils::max(int, int) --> int", pybind11::arg("u"), pybind11::arg("v"));
		cl.def_static("min", (int (*)(int, int)) &tsa::MathUtils::min, "C++: tsa::MathUtils::min(int, int) --> int", pybind11::arg("u"), pybind11::arg("v"));
	}
	{ // tsa::UpperTriangular file:tsaUtilityFunctions.hpp line:193
		pybind11::class_<tsa::UpperTriangular, std::shared_ptr<tsa::UpperTriangular>> cl(M("tsa"), "UpperTriangular", "");
		pybind11::handle cl_type = cl;

		cl.def(pybind11::init<>());
		cl.def_static("Map", (unsigned int (*)(unsigned int, unsigned int, unsigned int)) &tsa::UpperTriangular::Map, "C++: tsa::UpperTriangular::Map(unsigned int, unsigned int, unsigned int) --> unsigned int", pybind11::arg("i"), pybind11::arg("j"), pybind11::arg("dim"));
		cl.def_static("Size", (unsigned int (*)(unsigned int)) &tsa::UpperTriangular::Size, "C++: tsa::UpperTriangular::Size(unsigned int) --> unsigned int", pybind11::arg("dim"));
		cl.def_static("Dimension", (unsigned int (*)(unsigned int)) &tsa::UpperTriangular::Dimension, "C++: tsa::UpperTriangular::Dimension(unsigned int) --> unsigned int", pybind11::arg("sz"));
	}
	{ // tsa::LowerTriangular file:tsaUtilityFunctions.hpp line:211
		pybind11::class_<tsa::LowerTriangular, std::shared_ptr<tsa::LowerTriangular>> cl(M("tsa"), "LowerTriangular", "");
		pybind11::handle cl_type = cl;

		cl.def(pybind11::init<>());
		cl.def_static("Map", (unsigned int (*)(unsigned int, unsigned int, unsigned int)) &tsa::LowerTriangular::Map, "C++: tsa::LowerTriangular::Map(unsigned int, unsigned int, unsigned int) --> unsigned int", pybind11::arg("i"), pybind11::arg("j"), pybind11::arg(""));
		cl.def_static("Size", (unsigned int (*)(unsigned int)) &tsa::LowerTriangular::Size, "C++: tsa::LowerTriangular::Size(unsigned int) --> unsigned int", pybind11::arg("dim"));
		cl.def_static("Dimension", (unsigned int (*)(unsigned int)) &tsa::LowerTriangular::Dimension, "C++: tsa::LowerTriangular::Dimension(unsigned int) --> unsigned int", pybind11::arg("sz"));
	}
	{ // tsa::StrictUpperTriangular file:tsaUtilityFunctions.hpp line:229
		pybind11::class_<tsa::StrictUpperTriangular, std::shared_ptr<tsa::StrictUpperTriangular>> cl(M("tsa"), "StrictUpperTriangular", "");
		pybind11::handle cl_type = cl;

		cl.def(pybind11::init<>());
		cl.def_static("Map", (unsigned int (*)(unsigned int, unsigned int, unsigned int)) &tsa::StrictUpperTriangular::Map, "C++: tsa::StrictUpperTriangular::Map(unsigned int, unsigned int, unsigned int) --> unsigned int", pybind11::arg("i"), pybind11::arg("j"), pybind11::arg("dim"));
		cl.def_static("Size", (unsigned int (*)(unsigned int)) &tsa::StrictUpperTriangular::Size, "C++: tsa::StrictUpperTriangular::Size(unsigned int) --> unsigned int", pybind11::arg("dim"));
		cl.def_static("Dimension", (unsigned int (*)(unsigned int)) &tsa::StrictUpperTriangular::Dimension, "C++: tsa::StrictUpperTriangular::Dimension(unsigned int) --> unsigned int", pybind11::arg("sz"));
	}
	{ // tsa::StrictLowerTriangular file:tsaUtilityFunctions.hpp line:246
		pybind11::class_<tsa::StrictLowerTriangular, std::shared_ptr<tsa::StrictLowerTriangular>> cl(M("tsa"), "StrictLowerTriangular", "");
		pybind11::handle cl_type = cl;

		cl.def(pybind11::init<>());
		cl.def_static("Map", (unsigned int (*)(unsigned int, unsigned int, unsigned int)) &tsa::StrictLowerTriangular::Map, "C++: tsa::StrictLowerTriangular::Map(unsigned int, unsigned int, unsigned int) --> unsigned int", pybind11::arg("i"), pybind11::arg("j"), pybind11::arg(""));
		cl.def_static("Size", (unsigned int (*)(unsigned int)) &tsa::StrictLowerTriangular::Size, "C++: tsa::StrictLowerTriangular::Size(unsigned int) --> unsigned int", pybind11::arg("dim"));
		cl.def_static("Dimension", (unsigned int (*)(unsigned int)) &tsa::StrictLowerTriangular::Dimension, "C++: tsa::StrictLowerTriangular::Dimension(unsigned int) --> unsigned int", pybind11::arg("sz"));
	}
	{ // tsa::Square file:tsaUtilityFunctions.hpp line:262
		pybind11::class_<tsa::Square, std::shared_ptr<tsa::Square>> cl(M("tsa"), "Square", "");
		pybind11::handle cl_type = cl;

		cl.def(pybind11::init<>());
		cl.def_static("Map", (unsigned int (*)(unsigned int, unsigned int, unsigned int)) &tsa::Square::Map, "C++: tsa::Square::Map(unsigned int, unsigned int, unsigned int) --> unsigned int", pybind11::arg("i"), pybind11::arg("j"), pybind11::arg("lda"));
		cl.def_static("Size", (unsigned int (*)(unsigned int)) &tsa::Square::Size, "C++: tsa::Square::Size(unsigned int) --> unsigned int", pybind11::arg("dim"));
		cl.def_static("Dimension", (unsigned int (*)(unsigned int)) &tsa::Square::Dimension, "C++: tsa::Square::Dimension(unsigned int) --> unsigned int", pybind11::arg("sz"));
	}
	{ // tsa::GetRe file:tsaUtilityFunctions.hpp line:279
		pybind11::class_<tsa::GetRe, std::shared_ptr<tsa::GetRe>> cl(M("tsa"), "GetRe", "");
		pybind11::handle cl_type = cl;

		cl.def(pybind11::init<>());
	}
	{ // tsa::GetIm file:tsaUtilityFunctions.hpp line:288
		pybind11::class_<tsa::GetIm, std::shared_ptr<tsa::GetIm>> cl(M("tsa"), "GetIm", "");
		pybind11::handle cl_type = cl;

		cl.def(pybind11::init<>());
	}
	{ // tsa::GetAbs file:tsaUtilityFunctions.hpp line:298
		pybind11::class_<tsa::GetAbs, std::shared_ptr<tsa::GetAbs>> cl(M("tsa"), "GetAbs", "");
		pybind11::handle cl_type = cl;

		cl.def(pybind11::init<>());
	}
	{ // tsa::GetAbs2 file:tsaUtilityFunctions.hpp line:308
		pybind11::class_<tsa::GetAbs2, std::shared_ptr<tsa::GetAbs2>> cl(M("tsa"), "GetAbs2", "");
		pybind11::handle cl_type = cl;

		cl.def(pybind11::init<>());
	}
	{ // tsa::GetPhase file:tsaUtilityFunctions.hpp line:318
		pybind11::class_<tsa::GetPhase, std::shared_ptr<tsa::GetPhase>> cl(M("tsa"), "GetPhase", "");
		pybind11::handle cl_type = cl;

		cl.def(pybind11::init<>());
	}
	// tsa::Tag(char *, int, const char *, const char *) file:tsaSerialize.hpp line:47
	M("tsa").def("Tag", (char * (*)(char *, int, const char *, const char *)) &tsa::Tag, "C++: tsa::Tag(char *, int, const char *, const char *) --> char *", pybind11::return_value_policy::automatic, pybind11::arg("buffer"), pybind11::arg("n"), pybind11::arg("base"), pybind11::arg("rec"));

	// tsa::Tag(char *, int, const char *, const char *, unsigned int) file:tsaSerialize.hpp line:48
	M("tsa").def("Tag", (char * (*)(char *, int, const char *, const char *, unsigned int)) &tsa::Tag, "C++: tsa::Tag(char *, int, const char *, const char *, unsigned int) --> char *", pybind11::return_value_policy::automatic, pybind11::arg("buffer"), pybind11::arg("n"), pybind11::arg("base"), pybind11::arg("rec"), pybind11::arg("i"));

	// tsa::Tag(char *, int, const char *, const char *, unsigned int, unsigned int) file:tsaSerialize.hpp line:49
	M("tsa").def("Tag", (char * (*)(char *, int, const char *, const char *, unsigned int, unsigned int)) &tsa::Tag, "C++: tsa::Tag(char *, int, const char *, const char *, unsigned int, unsigned int) --> char *", pybind11::return_value_policy::automatic, pybind11::arg("buffer"), pybind11::arg("n"), pybind11::arg("base"), pybind11::arg("rec"), pybind11::arg("i"), pybind11::arg("j"));

	{ // tsa::BaseView file:BaseView.hpp line:73
		pybind11::class_<tsa::BaseView, std::shared_ptr<tsa::BaseView>> cl(M("tsa"), "BaseView", "");
		pybind11::handle cl_type = cl;

		cl.def("__init__", [](tsa::BaseView *self_) { new (self_) tsa::BaseView(); }, "doc");
		cl.def(pybind11::init<const class std::basic_string<char> &>(), pybind11::arg("aName"));

		cl.def(pybind11::init<const class tsa::BaseView &>(), pybind11::arg("from"));

		cl.def("assign", (class tsa::BaseView & (tsa::BaseView::*)(const class tsa::BaseView &)) &tsa::BaseView::operator=, "Assignement operator\n\n \n The instance to be assigned from\n\n \n a reference to a new object\n\nC++: tsa::BaseView::operator=(const class tsa::BaseView &) --> class tsa::BaseView &", pybind11::return_value_policy::automatic, pybind11::arg("from"));
	}
	{ // tsa::ARMAView file:ARMAView.hpp line:83
		pybind11::class_<tsa::ARMAView, std::shared_ptr<tsa::ARMAView>, tsa::BaseView> cl(M("tsa"), "ARMAView", "ARMA view: container for (vectorial) ARMA processes\n\n A view for ARMA parametrization. It defines a general (V)ARMA process, which\n can be written as\n \n\n\n\n where A,B are square matrix of dimension d equal to the dimension of the input\n and output vectors x,y.\n If the order of the part MA q is equal to zero the process is an AR process.\n If the order of the AR part p is equal to zero the process is an MA process.\n Note that the matrix \n\n is assumed to be the identity.");
		pybind11::handle cl_type = cl;

		cl.def("__init__", [](tsa::ARMAView *self_, unsigned int  const &a0, unsigned int  const &a1) { new (self_) tsa::ARMAView(a0, a1); }, "doc");
		cl.def(pybind11::init<unsigned int, unsigned int, int>(), pybind11::arg("maxP"), pybind11::arg("maxQ"), pybind11::arg("channels"));

		cl.def(pybind11::init<const class tsa::ARMAView &>(), pybind11::arg("from"));

		cl.def("Load", [](tsa::ARMAView &o, const char * a0) -> void { return o.Load(a0); }, "", pybind11::arg("filename"));
		cl.def("Load", (void (tsa::ARMAView::*)(const char *, const char *)) &tsa::ARMAView::Load, "C++: tsa::ARMAView::Load(const char *, const char *) --> void", pybind11::arg("filename"), pybind11::arg("fmt"));
		cl.def("Save", [](tsa::ARMAView &o, const char * a0) -> void { return o.Save(a0); }, "", pybind11::arg("filename"));
		cl.def("Save", (void (tsa::ARMAView::*)(const char *, const char *)) &tsa::ARMAView::Save, "C++: tsa::ARMAView::Save(const char *, const char *) --> void", pybind11::arg("filename"), pybind11::arg("fmt"));
		cl.def("xml_serialize", (void (tsa::ARMAView::*)(class eternity::xml_archive &, const char *)) &tsa::ARMAView::xml_serialize, "C++: tsa::ARMAView::xml_serialize(class eternity::xml_archive &, const char *) --> void", pybind11::arg("xml"), pybind11::arg("prefix"));
		cl.def("GetAR", [](tsa::ARMAView const &o, int  const &a0) -> const double & { return o.GetAR(a0); }, "", pybind11::return_value_policy::automatic, pybind11::arg("i"));
		cl.def("GetAR", (const double & (tsa::ARMAView::*)(int, unsigned int) const) &tsa::ARMAView::GetAR, "This method gives the value of the AR[i] coefficient for one of the channels.\n It is assumed that the VARMA process is diagonal, which means that there is\n and independent ARMA process for each channel.\n\n \n the index of the AR coefficient\n \n\n the channel\n\n \n the value of the AR[i] coefficient\n\nC++: tsa::ARMAView::GetAR(int, unsigned int) const --> const double &", pybind11::return_value_policy::automatic, pybind11::arg("i"), pybind11::arg("channel"));
		cl.def("GetMA", [](tsa::ARMAView const &o, int  const &a0) -> const double & { return o.GetMA(a0); }, "", pybind11::return_value_policy::automatic, pybind11::arg("i"));
		cl.def("GetMA", (const double & (tsa::ARMAView::*)(int, unsigned int) const) &tsa::ARMAView::GetMA, "This method gives the value of the MA[i] coefficient for one of the channels.\n It is assumed that the VARMA process is diagonal, which means that there is\n and independent ARMA process for each channel.\n\n \n the index of the MA coefficient\n \n\n the channel\n\n \n the value of the MA[i] coefficient\n\nC++: tsa::ARMAView::GetMA(int, unsigned int) const --> const double &", pybind11::return_value_policy::automatic, pybind11::arg("i"), pybind11::arg("channel"));
		cl.def("GetVAR", (const double & (tsa::ARMAView::*)(int, unsigned int, unsigned int) const) &tsa::ARMAView::GetVAR, "This method gives the value of the \n coefficient for the VARMA process\n\n \n the index of the VAR coefficient\n \n\n the first channel (index j)\n \n\n the se channel (index k)\n\n \n the value of the coefficient \n\nC++: tsa::ARMAView::GetVAR(int, unsigned int, unsigned int) const --> const double &", pybind11::return_value_policy::automatic, pybind11::arg("i"), pybind11::arg("channel1"), pybind11::arg("channel2"));
		cl.def("GetVMA", (const double & (tsa::ARMAView::*)(int, unsigned int, unsigned int) const) &tsa::ARMAView::GetVMA, "This method gives the value of the \n coefficient for the VARMA process\n\n \n the index of the VMA coefficient\n \n\n the first channel (index j)\n \n\n the se channel (index k)\n\n \n the value of the coefficient \n\nC++: tsa::ARMAView::GetVMA(int, unsigned int, unsigned int) const --> const double &", pybind11::return_value_policy::automatic, pybind11::arg("i"), pybind11::arg("channel1"), pybind11::arg("channel2"));
		cl.def("GetArOrder", (unsigned int (tsa::ARMAView::*)() const) &tsa::ARMAView::GetArOrder, "Get the order of the AR part of the process.\n\n \n the order of the AR part of the process\n\nC++: tsa::ARMAView::GetArOrder() const --> unsigned int");
		cl.def("GetMaOrder", (unsigned int (tsa::ARMAView::*)() const) &tsa::ARMAView::GetMaOrder, "Get the order of the MA part of the process.\n\n \n the order of the MA part of the process\n\nC++: tsa::ARMAView::GetMaOrder() const --> unsigned int");
		cl.def("GetChannels", (unsigned int (tsa::ARMAView::*)() const) &tsa::ARMAView::GetChannels, "Get the dimension of the VARMA process.\n\n \n the dimension of the VARMA process\n\nC++: tsa::ARMAView::GetChannels() const --> unsigned int");
		cl.def("SetAR", [](tsa::ARMAView &o, int  const &a0, double  const &a1) -> void { return o.SetAR(a0, a1); }, "", pybind11::arg("i"), pybind11::arg("v"));
		cl.def("SetAR", (void (tsa::ARMAView::*)(int, double, unsigned int)) &tsa::ARMAView::SetAR, "This method sets the value of the AR[i] coefficient for one of the channels.\n It is assumed that the VARMA process is diagonal, which means that there is\n and independent ARMA process for each channel.\n\n \n the index of the AR part\n \n\n the new value of AR[i]\n \n\n the channel\n\nC++: tsa::ARMAView::SetAR(int, double, unsigned int) --> void", pybind11::arg("i"), pybind11::arg("v"), pybind11::arg("channel"));
		cl.def("SetMA", [](tsa::ARMAView &o, int  const &a0, double  const &a1) -> void { return o.SetMA(a0, a1); }, "", pybind11::arg("i"), pybind11::arg("v"));
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

#include <pybind11/pybind11.h>

#ifndef BINDER_PYBIND11_TYPE_CASTER
	#define BINDER_PYBIND11_TYPE_CASTER
	PYBIND11_DECLARE_HOLDER_TYPE(T, std::shared_ptr<T>);
	PYBIND11_DECLARE_HOLDER_TYPE(T, T*);
#endif

void bind_LatticeView(std::function< pybind11::module &(std::string const &namespace_) > &M)
{
	{ // tsa::LatticeView file:LatticeView.hpp line:75
		pybind11::class_<tsa::LatticeView, std::shared_ptr<tsa::LatticeView>, tsa::BaseView> cl(M("tsa"), "LatticeView", "Define the object needed to implement the Lattice filter");
		pybind11::handle cl_type = cl;

		cl.def("__init__", [](tsa::LatticeView *self_) { new (self_) tsa::LatticeView(); }, "doc");
		cl.def(pybind11::init<unsigned int>(), pybind11::arg("ArOrder"));

		cl.def(pybind11::init<const class tsa::LatticeView &>(), pybind11::arg(""));

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
#include <stdio.h>
#include <sstream> // __str__

#include <pybind11/pybind11.h>

#ifndef BINDER_PYBIND11_TYPE_CASTER
	#define BINDER_PYBIND11_TYPE_CASTER
	PYBIND11_DECLARE_HOLDER_TYPE(T, std::shared_ptr<T>);
	PYBIND11_DECLARE_HOLDER_TYPE(T, T*);
#endif

void bind_FrameL(std::function< pybind11::module &(std::string const &namespace_) > &M)
{
	{ // FrameH file:FrameL.h line:161
		pybind11::class_<FrameH, std::shared_ptr<FrameH>> cl(M(""), "FrameH", "");
		pybind11::handle cl_type = cl;

		cl.def(pybind11::init<>());
		cl.def_readwrite("run", &FrameH::run);
		cl.def_readwrite("frame", &FrameH::frame);
		cl.def_readwrite("dataQuality", &FrameH::dataQuality);
		cl.def_readwrite("GTimeS", &FrameH::GTimeS);
		cl.def_readwrite("GTimeN", &FrameH::GTimeN);
		cl.def_readwrite("ULeapS", &FrameH::ULeapS);
		cl.def_readwrite("dt", &FrameH::dt);
	}
	{ // FrAdcData file:FrameL.h line:293
		pybind11::class_<FrAdcData, std::shared_ptr<FrAdcData>> cl(M(""), "FrAdcData", "");
		pybind11::handle cl_type = cl;

		cl.def(pybind11::init<>());
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
	{ // FrFile file:FrameL.h line:510
		pybind11::class_<FrFile, std::shared_ptr<FrFile>> cl(M(""), "FrFile", "");
		pybind11::handle cl_type = cl;

		cl.def(pybind11::init<>());
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
	{ // FrProcData file:FrameL.h line:749
		pybind11::class_<FrProcData, std::shared_ptr<FrProcData>> cl(M(""), "FrProcData", "");
		pybind11::handle cl_type = cl;

		cl.def(pybind11::init<>());
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
	{ // FrSimData file:FrameL.h line:908
		pybind11::class_<FrSimData, std::shared_ptr<FrSimData>> cl(M(""), "FrSimData", "");
		pybind11::handle cl_type = cl;

		cl.def(pybind11::init<>());
		cl.def_readwrite("sampleRate", &FrSimData::sampleRate);
		cl.def_readwrite("timeOffset", &FrSimData::timeOffset);
		cl.def_readwrite("fShift", &FrSimData::fShift);
		cl.def_readwrite("phase", &FrSimData::phase);
	}
	{ // FrVect file: line:41
		pybind11::class_<FrVect, std::shared_ptr<FrVect>> cl(M(""), "FrVect", "");
		pybind11::handle cl_type = cl;

		cl.def(pybind11::init<>());
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
#include <AlgoBase.hpp>
#include <AlgoExceptions.hpp>
#include <SeqView.hpp>
#include <ViewUtil.hpp>
#include <boost/numeric/ublas/functional.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/storage.hpp>
#include <complex>
#include <initializer_list>
#include <iterator>
#include <memory>
#include <sstream> // __str__
#include <string>

#include <pybind11/pybind11.h>

#ifndef BINDER_PYBIND11_TYPE_CASTER
	#define BINDER_PYBIND11_TYPE_CASTER
	PYBIND11_DECLARE_HOLDER_TYPE(T, std::shared_ptr<T>);
	PYBIND11_DECLARE_HOLDER_TYPE(T, T*);
#endif

// tsa::bad_matrix_size file:AlgoExceptions.hpp line:72
struct PyCallBack_bad_matrix_size : public tsa::bad_matrix_size {
	using tsa::bad_matrix_size::bad_matrix_size;

};

// tsa::bad_vector_size file:AlgoExceptions.hpp line:98
struct PyCallBack_bad_vector_size : public tsa::bad_vector_size {
	using tsa::bad_vector_size::bad_vector_size;

};

// tsa::no_data_available file:AlgoExceptions.hpp line:122
struct PyCallBack_no_data_available : public tsa::no_data_available {
	using tsa::no_data_available::no_data_available;

};

// tsa::bad_value file:AlgoExceptions.hpp line:145
struct PyCallBack_bad_value : public tsa::bad_value {
	using tsa::bad_value::bad_value;

};

// tsa::missing_data file:AlgoExceptions.hpp line:168
struct PyCallBack_missing_data : public tsa::missing_data {
	using tsa::missing_data::missing_data;

};

// tsa::quality_change file:AlgoExceptions.hpp line:207
struct PyCallBack_quality_change : public tsa::quality_change {
	using tsa::quality_change::quality_change;

};

void bind_SeqView(std::function< pybind11::module &(std::string const &namespace_) > &M)
{
	{ // tsa::SeqView file:SeqView.hpp line:25
		pybind11::class_<tsa::SeqView<double>, std::shared_ptr<tsa::SeqView<double>>, tsa::BaseView> cl(M("tsa"), "SeqView_double_t", "");
		pybind11::handle cl_type = cl;

		cl.def(pybind11::init<>());

		cl.def("__init__", [](tsa::SeqView<double> *self_, double  const &a0, double  const &a1, unsigned int  const &a2) { new (self_) tsa::SeqView<double>(a0, a1, a2); }, "doc");
		cl.def("__init__", [](tsa::SeqView<double> *self_, double  const &a0, double  const &a1, unsigned int  const &a2, const class std::basic_string<char> & a3) { new (self_) tsa::SeqView<double>(a0, a1, a2, a3); }, "doc");
		cl.def(pybind11::init<double, double, unsigned int, const class std::basic_string<char> &, unsigned int>(), pybind11::arg("aStart"), pybind11::arg("aSampling"), pybind11::arg("ChannelSize"), pybind11::arg("aName"), pybind11::arg("ColumnDim"));

		cl.def(pybind11::init<const class tsa::SeqView<double> &>(), pybind11::arg("from"));

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
		cl.def("GetY", (double (tsa::SeqView<double>::*)(unsigned int, unsigned int)) &tsa::SeqView<double>::GetY, "C++: tsa::SeqView<double>::GetY(unsigned int, unsigned int) --> double", pybind11::arg("channel"), pybind11::arg("f"));
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
	}
	{ // tsa::bad_matrix_size file:AlgoExceptions.hpp line:72
		pybind11::class_<tsa::bad_matrix_size, std::shared_ptr<tsa::bad_matrix_size>, PyCallBack_bad_matrix_size> cl(M("tsa"), "bad_matrix_size", "This exception should be used when a matrix argument of an algorithm\n   has an incorrect size. It contains information about the correct expected size.");
		pybind11::handle cl_type = cl;

		cl.def(pybind11::init<const class std::basic_string<char> &>(), pybind11::arg("msg"));

		cl.def(pybind11::init<PyCallBack_bad_matrix_size const &>());
		cl.def("assign", (class tsa::bad_matrix_size & (tsa::bad_matrix_size::*)(const class tsa::bad_matrix_size &)) &tsa::bad_matrix_size::operator=, "C++: tsa::bad_matrix_size::operator=(const class tsa::bad_matrix_size &) --> class tsa::bad_matrix_size &", pybind11::return_value_policy::automatic, pybind11::arg(""));
	}
	{ // tsa::bad_vector_size file:AlgoExceptions.hpp line:98
		pybind11::class_<tsa::bad_vector_size, std::shared_ptr<tsa::bad_vector_size>, PyCallBack_bad_vector_size> cl(M("tsa"), "bad_vector_size", "This exception should be used when a vector argument of an algorithm\n   has an incorrect size. It contains information about the correct expected size.");
		pybind11::handle cl_type = cl;

		cl.def(pybind11::init<const class std::basic_string<char> &>(), pybind11::arg("msg"));

		cl.def(pybind11::init<PyCallBack_bad_vector_size const &>());
		cl.def("assign", (class tsa::bad_vector_size & (tsa::bad_vector_size::*)(const class tsa::bad_vector_size &)) &tsa::bad_vector_size::operator=, "C++: tsa::bad_vector_size::operator=(const class tsa::bad_vector_size &) --> class tsa::bad_vector_size &", pybind11::return_value_policy::automatic, pybind11::arg(""));
	}
	{ // tsa::no_data_available file:AlgoExceptions.hpp line:122
		pybind11::class_<tsa::no_data_available, std::shared_ptr<tsa::no_data_available>, PyCallBack_no_data_available> cl(M("tsa"), "no_data_available", "This exception should be used when some processed data cannot be returned");
		pybind11::handle cl_type = cl;

		cl.def(pybind11::init<const class std::basic_string<char> &>(), pybind11::arg("msg"));

		cl.def(pybind11::init<PyCallBack_no_data_available const &>());
		cl.def("assign", (class tsa::no_data_available & (tsa::no_data_available::*)(const class tsa::no_data_available &)) &tsa::no_data_available::operator=, "C++: tsa::no_data_available::operator=(const class tsa::no_data_available &) --> class tsa::no_data_available &", pybind11::return_value_policy::automatic, pybind11::arg(""));
	}
	{ // tsa::bad_value file:AlgoExceptions.hpp line:145
		pybind11::class_<tsa::bad_value, std::shared_ptr<tsa::bad_value>, PyCallBack_bad_value> cl(M("tsa"), "bad_value", "This exception should be used when some processed data cannot be returned");
		pybind11::handle cl_type = cl;

		cl.def(pybind11::init<>());

		cl.def(pybind11::init<PyCallBack_bad_value const &>());
		cl.def("assign", (class tsa::bad_value & (tsa::bad_value::*)(const class tsa::bad_value &)) &tsa::bad_value::operator=, "C++: tsa::bad_value::operator=(const class tsa::bad_value &) --> class tsa::bad_value &", pybind11::return_value_policy::automatic, pybind11::arg(""));
	}
	{ // tsa::missing_data file:AlgoExceptions.hpp line:168
		pybind11::class_<tsa::missing_data, std::shared_ptr<tsa::missing_data>, PyCallBack_missing_data> cl(M("tsa"), "missing_data", "This exception should be used when some frames are missing");
		pybind11::handle cl_type = cl;

		cl.def(pybind11::init<const class std::basic_string<char> &, double, double, unsigned int>(), pybind11::arg("msg"), pybind11::arg("miss_start"), pybind11::arg("miss_end"), pybind11::arg("channel"));

		cl.def(pybind11::init<PyCallBack_missing_data const &>());
		cl.def("Start", (double (tsa::missing_data::*)()) &tsa::missing_data::Start, "C++: tsa::missing_data::Start() --> double");
		cl.def("End", (double (tsa::missing_data::*)()) &tsa::missing_data::End, "C++: tsa::missing_data::End() --> double");
		cl.def("Channel", (double (tsa::missing_data::*)()) &tsa::missing_data::Channel, "C++: tsa::missing_data::Channel() --> double");
		cl.def("assign", (class tsa::missing_data & (tsa::missing_data::*)(const class tsa::missing_data &)) &tsa::missing_data::operator=, "C++: tsa::missing_data::operator=(const class tsa::missing_data &) --> class tsa::missing_data &", pybind11::return_value_policy::automatic, pybind11::arg(""));
	}
	{ // tsa::quality_change file:AlgoExceptions.hpp line:207
		pybind11::class_<tsa::quality_change, std::shared_ptr<tsa::quality_change>, PyCallBack_quality_change> cl(M("tsa"), "quality_change", "This exception should be used when data quality change");
		pybind11::handle cl_type = cl;

		cl.def(pybind11::init<const class std::basic_string<char> &, double, unsigned int, unsigned int>(), pybind11::arg("msg"), pybind11::arg("change_time"), pybind11::arg("old_flag"), pybind11::arg("new_flag"));

		cl.def(pybind11::init<PyCallBack_quality_change const &>());
		cl.def("EventTime", (double (tsa::quality_change::*)()) &tsa::quality_change::EventTime, "C++: tsa::quality_change::EventTime() --> double");
		cl.def("OldFlag", (unsigned int (tsa::quality_change::*)()) &tsa::quality_change::OldFlag, "C++: tsa::quality_change::OldFlag() --> unsigned int");
		cl.def("NewFlag", (unsigned int (tsa::quality_change::*)()) &tsa::quality_change::NewFlag, "C++: tsa::quality_change::NewFlag() --> unsigned int");
		cl.def("assign", (class tsa::quality_change & (tsa::quality_change::*)(const class tsa::quality_change &)) &tsa::quality_change::operator=, "C++: tsa::quality_change::operator=(const class tsa::quality_change &) --> class tsa::quality_change &", pybind11::return_value_policy::automatic, pybind11::arg(""));
	}
	{ // tsa::AlgoBase file:AlgoBase.hpp line:64
		pybind11::class_<tsa::AlgoBase, std::shared_ptr<tsa::AlgoBase>> cl(M("tsa"), "AlgoBase", "AlgoBase is the abstract base class for all algorithm.\n\n AlgoBase is the abstract base class for all the algorithm classes.\n It contain the definition of the common methods. An algorithm is a class\n with one or more execute() methods, with a variable number of parameters.");
		pybind11::handle cl_type = cl;

		cl.def(pybind11::init<>());

		cl.def(pybind11::init<const class tsa::AlgoBase &>(), pybind11::arg(""));

		cl.def("assign", (class tsa::AlgoBase & (tsa::AlgoBase::*)(const class tsa::AlgoBase &)) &tsa::AlgoBase::operator=, "C++: tsa::AlgoBase::operator=(const class tsa::AlgoBase &) --> class tsa::AlgoBase &", pybind11::return_value_policy::automatic, pybind11::arg(""));
	}
	{ // tsa::ViewUtil file:ViewUtil.hpp line:73
		pybind11::class_<tsa::ViewUtil, std::shared_ptr<tsa::ViewUtil>, tsa::AlgoBase> cl(M("tsa"), "ViewUtil", "This is a short description of the class ViewUtil\n\n A more detailed description of ViewUtil start here");
		pybind11::handle cl_type = cl;

		cl.def(pybind11::init<>());

		cl.def_static("Join", (void (*)(class tsa::SeqView<double> &, class tsa::SeqView<double> &, class tsa::SeqView<double> &)) &tsa::ViewUtil::Join, "C++: tsa::ViewUtil::Join(class tsa::SeqView<double> &, class tsa::SeqView<double> &, class tsa::SeqView<double> &) --> void", pybind11::arg("s1"), pybind11::arg("s2"), pybind11::arg("joined"));
		cl.def_static("Append", (void (*)(class tsa::SeqView<double> &, class tsa::SeqView<double> &)) &tsa::ViewUtil::Append, "C++: tsa::ViewUtil::Append(class tsa::SeqView<double> &, class tsa::SeqView<double> &) --> void", pybind11::arg("s1"), pybind11::arg("s2"));
		cl.def_static("Print", (void (*)(class tsa::SeqView<double> &, char *)) &tsa::ViewUtil::Print, "C++: tsa::ViewUtil::Print(class tsa::SeqView<double> &, char *) --> void", pybind11::arg("s1"), pybind11::arg("filename"));
		cl.def_static("Print", (void (*)(class tsa::SeqView<double> &)) &tsa::ViewUtil::Print, "C++: tsa::ViewUtil::Print(class tsa::SeqView<double> &) --> void", pybind11::arg("s1"));
		cl.def_static("Range", (void (*)(class tsa::SeqView<double> &, int, int)) &tsa::ViewUtil::Range, "C++: tsa::ViewUtil::Range(class tsa::SeqView<double> &, int, int) --> void", pybind11::arg("s1"), pybind11::arg("l"), pybind11::arg("m"));
		cl.def_static("Range", (void (*)(class tsa::SeqView<double> &, class tsa::SeqView<double> &, int, int)) &tsa::ViewUtil::Range, "C++: tsa::ViewUtil::Range(class tsa::SeqView<double> &, class tsa::SeqView<double> &, int, int) --> void", pybind11::arg("s1"), pybind11::arg("s2"), pybind11::arg("l"), pybind11::arg("m"));
		cl.def_static("LeftShift", (void (*)(class tsa::SeqView<double> &, class tsa::SeqView<double> &)) &tsa::ViewUtil::LeftShift, "C++: tsa::ViewUtil::LeftShift(class tsa::SeqView<double> &, class tsa::SeqView<double> &) --> void", pybind11::arg("seq"), pybind11::arg("ins"));
		cl.def_static("PadLeft", [](class tsa::SeqView<double> & a0, class tsa::SeqView<double> & a1, unsigned int  const &a2) -> void { return tsa::ViewUtil::PadLeft(a0, a1, a2); }, "", pybind11::arg("src"), pybind11::arg("dst"), pybind11::arg("size"));
		cl.def_static("PadLeft", (void (*)(class tsa::SeqView<double> &, class tsa::SeqView<double> &, unsigned int, double)) &tsa::ViewUtil::PadLeft, "C++: tsa::ViewUtil::PadLeft(class tsa::SeqView<double> &, class tsa::SeqView<double> &, unsigned int, double) --> void", pybind11::arg("src"), pybind11::arg("dst"), pybind11::arg("size"), pybind11::arg("value"));
		cl.def_static("PadRight", [](class tsa::SeqView<double> & a0, class tsa::SeqView<double> & a1, unsigned int  const &a2) -> void { return tsa::ViewUtil::PadRight(a0, a1, a2); }, "", pybind11::arg("src"), pybind11::arg("dst"), pybind11::arg("size"));
		cl.def_static("PadRight", (void (*)(class tsa::SeqView<double> &, class tsa::SeqView<double> &, unsigned int, double)) &tsa::ViewUtil::PadRight, "C++: tsa::ViewUtil::PadRight(class tsa::SeqView<double> &, class tsa::SeqView<double> &, unsigned int, double) --> void", pybind11::arg("src"), pybind11::arg("dst"), pybind11::arg("size"), pybind11::arg("value"));
		cl.def_static("Dot", (double (*)(class tsa::SeqView<double> &, unsigned int, class tsa::SeqView<double> &, unsigned int)) &tsa::ViewUtil::Dot, "C++: tsa::ViewUtil::Dot(class tsa::SeqView<double> &, unsigned int, class tsa::SeqView<double> &, unsigned int) --> double", pybind11::arg("s1"), pybind11::arg("ch1"), pybind11::arg("s2"), pybind11::arg("ch2"));
		cl.def_static("SumChannels", (void (*)(class tsa::SeqView<double> &, class tsa::SeqView<double> &)) &tsa::ViewUtil::SumChannels, "C++: tsa::ViewUtil::SumChannels(class tsa::SeqView<double> &, class tsa::SeqView<double> &) --> void", pybind11::arg("s1"), pybind11::arg("sum"));
		cl.def_static("SumChannels", (void (*)(class tsa::SeqView<double> &, class tsa::SeqView<double> &, double, double)) &tsa::ViewUtil::SumChannels, "C++: tsa::ViewUtil::SumChannels(class tsa::SeqView<double> &, class tsa::SeqView<double> &, double, double) --> void", pybind11::arg("s1"), pybind11::arg("sum"), pybind11::arg("wfirst"), pybind11::arg("wothers"));
		cl.def_static("Fill", (void (*)(class tsa::SeqView<double> &, double)) &tsa::ViewUtil::Fill, "C++: tsa::ViewUtil::Fill(class tsa::SeqView<double> &, double) --> void", pybind11::arg("ts"), pybind11::arg("value"));
		cl.def_static("FillSeq", (void (*)(class tsa::SeqView<double> &, unsigned int, unsigned int, double)) &tsa::ViewUtil::FillSeq, "C++: tsa::ViewUtil::FillSeq(class tsa::SeqView<double> &, unsigned int, unsigned int, double) --> void", pybind11::arg("ts"), pybind11::arg("i"), pybind11::arg("j"), pybind11::arg("value"));
		cl.def_static("PeekRange", (bool (*)(class tsa::SeqView<double> &, class tsa::SeqView<double> &, double, double)) &tsa::ViewUtil::PeekRange, "Extract from the src view the data included in a given time range, tstart<=t<=tend,\n and put it in the dst view. \n\n \n the source view\n \n\n the destination view\n \n\n start time of the range\n \n\n end time for the range\n\n \n true if the range is fully inside src, false otherwise\n\nC++: tsa::ViewUtil::PeekRange(class tsa::SeqView<double> &, class tsa::SeqView<double> &, double, double) --> bool", pybind11::arg("src"), pybind11::arg("dst"), pybind11::arg("tstart"), pybind11::arg("tend"));
		cl.def_static("Sum", (void (*)(class tsa::SeqView<double> &, double, class tsa::SeqView<double> &)) &tsa::ViewUtil::Sum, "C++: tsa::ViewUtil::Sum(class tsa::SeqView<double> &, double, class tsa::SeqView<double> &) --> void", pybind11::arg("res"), pybind11::arg("scale"), pybind11::arg("ts"));
		cl.def_static("Inverse", (void (*)(class tsa::SeqView<double> &, class tsa::SeqView<double> &)) &tsa::ViewUtil::Inverse, "C++: tsa::ViewUtil::Inverse(class tsa::SeqView<double> &, class tsa::SeqView<double> &) --> void", pybind11::arg("ts1"), pybind11::arg("res"));
		cl.def_static("AffineTransformation", (void (*)(class tsa::SeqView<double> &, double, double, class tsa::SeqView<double> &)) &tsa::ViewUtil::AffineTransformation, "C++: tsa::ViewUtil::AffineTransformation(class tsa::SeqView<double> &, double, double, class tsa::SeqView<double> &) --> void", pybind11::arg("ts1"), pybind11::arg("a"), pybind11::arg("b"), pybind11::arg("res"));
		cl.def_static("Ratio", (void (*)(class tsa::SeqView<double> &, class tsa::SeqView<double> &, class tsa::SeqView<double> &)) &tsa::ViewUtil::Ratio, "C++: tsa::ViewUtil::Ratio(class tsa::SeqView<double> &, class tsa::SeqView<double> &, class tsa::SeqView<double> &) --> void", pybind11::arg("ts1"), pybind11::arg("ts2"), pybind11::arg("res"));
		cl.def_static("Prod", (void (*)(class tsa::SeqView<double> &, class tsa::SeqView<double> &, class tsa::SeqView<double> &)) &tsa::ViewUtil::Prod, "C++: tsa::ViewUtil::Prod(class tsa::SeqView<double> &, class tsa::SeqView<double> &, class tsa::SeqView<double> &) --> void", pybind11::arg("ts1"), pybind11::arg("ts2"), pybind11::arg("res"));
		cl.def_static("Integrate", (double (*)(class tsa::SeqView<double> &, double, double)) &tsa::ViewUtil::Integrate, "C++: tsa::ViewUtil::Integrate(class tsa::SeqView<double> &, double, double) --> double", pybind11::arg("data"), pybind11::arg("f1"), pybind11::arg("f2"));
		cl.def_static("Multiply", (void (*)(class tsa::SeqView<double> &, class tsa::SeqView<double> &, class tsa::SeqView<double> &)) &tsa::ViewUtil::Multiply, "C++: tsa::ViewUtil::Multiply(class tsa::SeqView<double> &, class tsa::SeqView<double> &, class tsa::SeqView<double> &) --> void", pybind11::arg("in1"), pybind11::arg("in2"), pybind11::arg("res"));
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
#include <initializer_list>
#include <iterator>
#include <map>
#include <memory>
#include <sstream> // __str__
#include <string>
#include <utility>
#include <vector>

#include <pybind11/pybind11.h>

#ifndef BINDER_PYBIND11_TYPE_CASTER
	#define BINDER_PYBIND11_TYPE_CASTER
	PYBIND11_DECLARE_HOLDER_TYPE(T, std::shared_ptr<T>);
	PYBIND11_DECLARE_HOLDER_TYPE(T, T*);
#endif

// tsa::BaseWindow file:BaseWindow.hpp line:74
struct PyCallBack_BaseWindow : public tsa::BaseWindow {
	using tsa::BaseWindow::BaseWindow;

	void operator()(class tsa::SeqView<double> & a0) override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const tsa::BaseWindow *>(this), "__call__");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::overload_caster_t<void> caster;
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
				static pybind11::detail::overload_caster_t<void> caster;
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
				static pybind11::detail::overload_caster_t<void> caster;
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
				static pybind11::detail::overload_caster_t<void> caster;
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
				static pybind11::detail::overload_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return BaseWindow::FillWindow();
	}
};

// tsa::BartlettWindow file:BartlettWindow.hpp line:68
struct PyCallBack_BartlettWindow : public tsa::BartlettWindow {
	using tsa::BartlettWindow::BartlettWindow;

	void operator()(class tsa::SeqView<double> & a0) override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const tsa::BartlettWindow *>(this), "__call__");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::overload_caster_t<void> caster;
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
				static pybind11::detail::overload_caster_t<void> caster;
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
				static pybind11::detail::overload_caster_t<void> caster;
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
				static pybind11::detail::overload_caster_t<void> caster;
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
				static pybind11::detail::overload_caster_t<void> caster;
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
		pybind11::handle cl_type = cl;

		cl.def(pybind11::init<>());

		cl.def("assign", (class tsa::Parcor2AR & (tsa::Parcor2AR::*)(const class tsa::Parcor2AR &)) &tsa::Parcor2AR::operator=, "C++: tsa::Parcor2AR::operator=(const class tsa::Parcor2AR &) --> class tsa::Parcor2AR &", pybind11::return_value_policy::automatic, pybind11::arg(""));
	}
	{ // tsa::ArBurgEstimator file:ArBurgEstimator.hpp line:77
		pybind11::class_<tsa::ArBurgEstimator, std::shared_ptr<tsa::ArBurgEstimator>, tsa::AlgoBase> cl(M("tsa"), "ArBurgEstimator", "Estimate the Parcor and AR parameters on a sequence of data\n\n     ");
		pybind11::handle cl_type = cl;

		cl.def(pybind11::init<unsigned int>(), pybind11::arg("ArOrder"));

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
		pybind11::handle cl_type = cl;

		cl.def(pybind11::init<unsigned int>(), pybind11::arg("ArOrder"));

		cl.def("GetArOrder", (unsigned int (tsa::ArDurbinEstimator::*)()) &tsa::ArDurbinEstimator::GetArOrder, "C++: tsa::ArDurbinEstimator::GetArOrder() --> unsigned int");
		cl.def("SetArOrder", (void (tsa::ArDurbinEstimator::*)(unsigned int)) &tsa::ArDurbinEstimator::SetArOrder, "C++: tsa::ArDurbinEstimator::SetArOrder(unsigned int) --> void", pybind11::arg("P"));
		cl.def("assign", (class tsa::ArDurbinEstimator & (tsa::ArDurbinEstimator::*)(const class tsa::ArDurbinEstimator &)) &tsa::ArDurbinEstimator::operator=, "C++: tsa::ArDurbinEstimator::operator=(const class tsa::ArDurbinEstimator &) --> class tsa::ArDurbinEstimator &", pybind11::return_value_policy::automatic, pybind11::arg(""));
	}
	{ // tsa::Arma2Psd file:Arma2Psd.hpp line:72
		pybind11::class_<tsa::Arma2Psd, std::shared_ptr<tsa::Arma2Psd>, tsa::AlgoBase> cl(M("tsa"), "Arma2Psd", "Estimate the PSD for a ARMA model");
		pybind11::handle cl_type = cl;

		cl.def(pybind11::init<>());

		cl.def(pybind11::init<const class tsa::Arma2Psd &>(), pybind11::arg("from"));

		cl.def("assign", (class tsa::Arma2Psd & (tsa::Arma2Psd::*)(const class tsa::Arma2Psd &)) &tsa::Arma2Psd::operator=, "Assignement operator\n\n \n The instance to be assigned from\n\n \n a reference to a new object\n\nC++: tsa::Arma2Psd::operator=(const class tsa::Arma2Psd &) --> class tsa::Arma2Psd &", pybind11::return_value_policy::automatic, pybind11::arg("from"));
		cl.def("__call__", (void (tsa::Arma2Psd::*)(class tsa::ARMAView &, class tsa::SeqView<double> &)) &tsa::Arma2Psd::operator(), "The P or the Q order must be greater than 0\n\n \n the Arma View\n\n \n Psd the Power Spectral density\n\nC++: tsa::Arma2Psd::operator()(class tsa::ARMAView &, class tsa::SeqView<double> &) --> void", pybind11::arg("arma"), pybind11::arg("Psd"));
	}
	{ // tsa::Arma2TF file:Arma2TF.hpp line:75
		pybind11::class_<tsa::Arma2TF, std::shared_ptr<tsa::Arma2TF>, tsa::AlgoBase> cl(M("tsa"), "Arma2TF", "Estimate the Transfer function using the ARMA parametrization\n\n     ");
		pybind11::handle cl_type = cl;

		cl.def(pybind11::init<>());

		cl.def(pybind11::init<const class tsa::Arma2TF &>(), pybind11::arg("from"));

		cl.def("assign", (class tsa::Arma2TF & (tsa::Arma2TF::*)(const class tsa::Arma2TF &)) &tsa::Arma2TF::operator=, "Assignement operator\n\n \n The instance to be assigned from\n\n \n a reference to a new object\n\nC++: tsa::Arma2TF::operator=(const class tsa::Arma2TF &) --> class tsa::Arma2TF &", pybind11::return_value_policy::automatic, pybind11::arg("from"));
	}
	{ // tsa::AR2 file:AR2.hpp line:70
		pybind11::class_<tsa::AR2, std::shared_ptr<tsa::AR2>, tsa::AlgoBase> cl(M("tsa"), "AR2", "");
		pybind11::handle cl_type = cl;

		cl.def(pybind11::init<const double, const double, const double>(), pybind11::arg("f"), pybind11::arg("gamma"), pybind11::arg("h"));

		cl.def("__call__", (void (tsa::AR2::*)(class tsa::SeqView<double> &, class tsa::SeqView<double> &)) &tsa::AR2::operator(), "C++: tsa::AR2::operator()(class tsa::SeqView<double> &, class tsa::SeqView<double> &) --> void", pybind11::arg("in"), pybind11::arg("out"));
		cl.def("assign", (class tsa::AR2 & (tsa::AR2::*)(const class tsa::AR2 &)) &tsa::AR2::operator=, "C++: tsa::AR2::operator=(const class tsa::AR2 &) --> class tsa::AR2 &", pybind11::return_value_policy::automatic, pybind11::arg(""));
	}
	{ // tsa::AR2Parcor file:AR2Parcor.hpp line:71
		pybind11::class_<tsa::AR2Parcor, std::shared_ptr<tsa::AR2Parcor>, tsa::AlgoBase> cl(M("tsa"), "AR2Parcor", "Estimate the AR parameters by the Parcor");
		pybind11::handle cl_type = cl;

		cl.def(pybind11::init<>());

		cl.def("assign", (class tsa::AR2Parcor & (tsa::AR2Parcor::*)(const class tsa::AR2Parcor &)) &tsa::AR2Parcor::operator=, "C++: tsa::AR2Parcor::operator=(const class tsa::AR2Parcor &) --> class tsa::AR2Parcor &", pybind11::return_value_policy::automatic, pybind11::arg(""));
	}
	{ // tsa::ARMAFilter file:ARMAFilter.hpp line:78
		pybind11::class_<tsa::ARMAFilter, std::shared_ptr<tsa::ARMAFilter>, tsa::AlgoBase> cl(M("tsa"), "ARMAFilter", "Implement the   ARMA filtering\n\n This class implement a general ARMA filter. Given an input sequence x(n)\n and an output sequence y(n) an ARMA filter is defined by the relation\n (look at the signs definitions..)\n\n a(0) y(n) =  a(1) y(n-1) + ... + a(N) y(n-N) + b(0) x(n) + b(1) x(n-1) + .... + b(M) x(n-M)\n\n ");
		pybind11::handle cl_type = cl;

		cl.def(pybind11::init<const class std::vector<double, class std::allocator<double> > &, const class std::vector<double, class std::allocator<double> > &, double>(), pybind11::arg("mAR"), pybind11::arg("mMA"), pybind11::arg("gain"));

		cl.def("__call__", (void (tsa::ARMAFilter::*)(class tsa::SeqView<double> &, class tsa::SeqView<double> &)) &tsa::ARMAFilter::operator(), "C++: tsa::ARMAFilter::operator()(class tsa::SeqView<double> &, class tsa::SeqView<double> &) --> void", pybind11::arg("in"), pybind11::arg("out"));
		cl.def("assign", (class tsa::ARMAFilter & (tsa::ARMAFilter::*)(const class tsa::ARMAFilter &)) &tsa::ARMAFilter::operator=, "C++: tsa::ARMAFilter::operator=(const class tsa::ARMAFilter &) --> class tsa::ARMAFilter &", pybind11::return_value_policy::automatic, pybind11::arg(""));
	}
	{ // tsa::MYWE file:MYWE.hpp line:74
		pybind11::class_<tsa::MYWE, std::shared_ptr<tsa::MYWE>> cl(M("tsa"), "MYWE", "A more detailed description of MYWE");
		pybind11::handle cl_type = cl;

		cl.def(pybind11::init<unsigned int, unsigned int>(), pybind11::arg("mIP"), pybind11::arg("mIQ"));

		cl.def("assign", (class tsa::MYWE & (tsa::MYWE::*)(const class tsa::MYWE &)) &tsa::MYWE::operator=, "Assignement operator\n\n \n The instance to be assigned from\n\n \n a reference to a new object\n\nC++: tsa::MYWE::operator=(const class tsa::MYWE &) --> class tsa::MYWE &", pybind11::return_value_policy::automatic, pybind11::arg("from"));
	}
	{ // tsa::ARMAfit file:ARMAfit.hpp line:75
		pybind11::class_<tsa::ARMAfit, std::shared_ptr<tsa::ARMAfit>> cl(M("tsa"), "ARMAfit", "implement the ARMA fit to a PSD");
		pybind11::handle cl_type = cl;

		cl.def(pybind11::init<unsigned int, unsigned int>(), pybind11::arg("P"), pybind11::arg("Q"));

		cl.def("assign", (class tsa::ARMAfit & (tsa::ARMAfit::*)(const class tsa::ARMAfit &)) &tsa::ARMAfit::operator=, "Assignement operator\n\n \n The instance to be assigned from\n\n \n a reference to a new object\n\nC++: tsa::ARMAfit::operator=(const class tsa::ARMAfit &) --> class tsa::ARMAfit &", pybind11::return_value_policy::automatic, pybind11::arg("from"));
	}
	{ // tsa::BaseWindow file:BaseWindow.hpp line:74
		pybind11::class_<tsa::BaseWindow, std::shared_ptr<tsa::BaseWindow>, PyCallBack_BaseWindow, tsa::AlgoBase> cl(M("tsa"), "BaseWindow", "Base class for various windowing algorithms\n\n ");
		pybind11::handle cl_type = cl;

		cl.def(pybind11::init<unsigned int>(), pybind11::arg("size"));

		cl.def(pybind11::init<PyCallBack_BaseWindow const &>());
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
		pybind11::class_<tsa::BartlettWindow, std::shared_ptr<tsa::BartlettWindow>, PyCallBack_BartlettWindow, tsa::BaseWindow> cl(M("tsa"), "BartlettWindow", "Bartlett windowing algorithm");
		pybind11::handle cl_type = cl;

		cl.def(pybind11::init<int>(), pybind11::arg("size"));

		cl.def(pybind11::init<int, const class std::basic_string<char> &>(), pybind11::arg("size"), pybind11::arg(""));

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
#include <initializer_list>
#include <iterator>
#include <memory>
#include <sstream> // __str__
#include <string>

#include <pybind11/pybind11.h>

#ifndef BINDER_PYBIND11_TYPE_CASTER
	#define BINDER_PYBIND11_TYPE_CASTER
	PYBIND11_DECLARE_HOLDER_TYPE(T, std::shared_ptr<T>);
	PYBIND11_DECLARE_HOLDER_TYPE(T, T*);
#endif

// tsa::BaseFFT file:BaseFFT.hpp line:88
struct PyCallBack_BaseFFT : public tsa::BaseFFT {
	using tsa::BaseFFT::BaseFFT;

	void MakePlan() override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const tsa::BaseFFT *>(this), "MakePlan");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>();
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::overload_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		pybind11::pybind11_fail("Tried to call pure virtual function \"BaseFFT::MakePlan\"");
	}
};

// tsa::BisquareWindow file:BisquareWindow.hpp line:69
struct PyCallBack_BisquareWindow : public tsa::BisquareWindow {
	using tsa::BisquareWindow::BisquareWindow;

	void operator()(class tsa::SeqView<double> & a0) override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const tsa::BisquareWindow *>(this), "__call__");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::overload_caster_t<void> caster;
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
				static pybind11::detail::overload_caster_t<void> caster;
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
				static pybind11::detail::overload_caster_t<void> caster;
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
				static pybind11::detail::overload_caster_t<void> caster;
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
				static pybind11::detail::overload_caster_t<void> caster;
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
	pybind11::enum_<tsa::FFTPlanningMode>(M("tsa"), "FFTPlanningMode", "Planning modes. They describe the way in which the planning\n is done. See the fftw documentation.")
		.value("ESTIMATE", tsa::FFTPlanningMode::ESTIMATE)
		.value("MEASURE", tsa::FFTPlanningMode::MEASURE)
		.value("PATIENT", tsa::FFTPlanningMode::PATIENT)
		.value("EXHAUSTIVE", tsa::FFTPlanningMode::EXHAUSTIVE)
		.export_values();

;

	// tsa::FFTsize(int) file:BaseFFT.hpp line:78
	M("tsa").def("FFTsize", (int (*)(int)) &tsa::FFTsize, "C++: tsa::FFTsize(int) --> int", pybind11::arg("n"));

	{ // tsa::BaseFFT file:BaseFFT.hpp line:88
		pybind11::class_<tsa::BaseFFT, std::shared_ptr<tsa::BaseFFT>, PyCallBack_BaseFFT, tsa::AlgoBase> cl(M("tsa"), "BaseFFT", "Base class for various FFT\n\n ");
		pybind11::handle cl_type = cl;

		cl.def(pybind11::init<int, enum tsa::FFTPlanningMode, bool>(), pybind11::arg("size"), pybind11::arg("mode"), pybind11::arg("PreserveInput"));

		cl.def(pybind11::init<PyCallBack_BaseFFT const &>());
		cl.def_static("ForgetWisdom", (void (*)()) &tsa::BaseFFT::ForgetWisdom, "Forget wisdom\n\nC++: tsa::BaseFFT::ForgetWisdom() --> void");
		cl.def("MakePlan", (void (tsa::BaseFFT::*)()) &tsa::BaseFFT::MakePlan, "Make a new plan, with the current parameters.\n\nC++: tsa::BaseFFT::MakePlan() --> void");
		cl.def("SetPlanningMode", (void (tsa::BaseFFT::*)(enum tsa::FFTPlanningMode)) &tsa::BaseFFT::SetPlanningMode, "Set the way in which the plan is constructed. No new plan is generated.\n\n \n the requested planning mode.\n\nC++: tsa::BaseFFT::SetPlanningMode(enum tsa::FFTPlanningMode) --> void", pybind11::arg("mode"));
		cl.def("SetPreserveInput", [](tsa::BaseFFT &o) -> void { return o.SetPreserveInput(); }, "");
		cl.def("SetPreserveInput", (void (tsa::BaseFFT::*)(bool)) &tsa::BaseFFT::SetPreserveInput, "Request that the input buffer is preserved during the transformation.\n No new plan is generated.\n\n \n true (default) if input buffer must be preserved, false otherwise\n\nC++: tsa::BaseFFT::SetPreserveInput(bool) --> void", pybind11::arg("flag"));
		cl.def("assign", (class tsa::BaseFFT & (tsa::BaseFFT::*)(const class tsa::BaseFFT &)) &tsa::BaseFFT::operator=, "C++: tsa::BaseFFT::operator=(const class tsa::BaseFFT &) --> class tsa::BaseFFT &", pybind11::return_value_policy::automatic, pybind11::arg(""));
	}
	{ // tsa::BisquareWindow file:BisquareWindow.hpp line:69
		pybind11::class_<tsa::BisquareWindow, std::shared_ptr<tsa::BisquareWindow>, PyCallBack_BisquareWindow, tsa::BaseWindow> cl(M("tsa"), "BisquareWindow", "Bisquare windowing algorithm\n\n ");
		pybind11::handle cl_type = cl;

		cl.def(pybind11::init<int>(), pybind11::arg("size"));

		cl.def(pybind11::init<int, const class std::basic_string<char> &>(), pybind11::arg("size"), pybind11::arg(""));

		cl.def("__call__", (void (tsa::BisquareWindow::*)(class tsa::SeqView<double> &)) &tsa::BisquareWindow::operator(), "Apply the window to a given time view.\n\n \n the time view \n\nC++: tsa::BisquareWindow::operator()(class tsa::SeqView<double> &) --> void", pybind11::arg("v1"));
		cl.def("__call__", (void (tsa::BisquareWindow::*)(class tsa::SeqView<double> &, class tsa::SeqView<double> &)) &tsa::BisquareWindow::operator(), "Apply a window to an input view and write the results on a \n output view.\n\n \n the input view\n \n\n the output view\n\n         \n\nC++: tsa::BisquareWindow::operator()(class tsa::SeqView<double> &, class tsa::SeqView<double> &) --> void", pybind11::arg("v1"), pybind11::arg("v2"));
		cl.def("Resize", (void (tsa::BisquareWindow::*)(unsigned int)) &tsa::BisquareWindow::Resize, "Resize the window dimension.\n\n \n new size for the window\n\nC++: tsa::BisquareWindow::Resize(unsigned int) --> void", pybind11::arg("size"));
		cl.def("assign", (class tsa::BisquareWindow & (tsa::BisquareWindow::*)(const class tsa::BisquareWindow &)) &tsa::BisquareWindow::operator=, "C++: tsa::BisquareWindow::operator=(const class tsa::BisquareWindow &) --> class tsa::BisquareWindow &", pybind11::return_value_policy::automatic, pybind11::arg(""));
	}
	{ // tsa::ButterworthFilter file:ButterworthFilter.hpp line:74
		pybind11::class_<tsa::ButterworthFilter, std::shared_ptr<tsa::ButterworthFilter>, tsa::AlgoBase> cl(M("tsa"), "ButterworthFilter", "A generator of random normal numbers.\n\n     ");
		pybind11::handle cl_type = cl;

		cl.def(pybind11::init<double, int>(), pybind11::arg("freq"), pybind11::arg("order"));

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
#include <IDCT.hpp>
#include <DST.hpp>
#include <DoubleWhitening.hpp>
#include <FifoBuffer.hpp>
#include <LatticeView.hpp>
#include <SeqView.hpp>
#include <boost/numeric/ublas/functional.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/storage.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include <eternity/persist.hpp>
#include <eternity/persist_xml.hpp>
#include <functional>
#include <initializer_list>
#include <iterator>
#include <map>
#include <memory>
#include <sstream> // __str__
#include <string>
#include <utility>

#include <pybind11/pybind11.h>

#ifndef BINDER_PYBIND11_TYPE_CASTER
	#define BINDER_PYBIND11_TYPE_CASTER
	PYBIND11_DECLARE_HOLDER_TYPE(T, std::shared_ptr<T>);
	PYBIND11_DECLARE_HOLDER_TYPE(T, T*);
#endif

// tsa::Cs2HammingWindow file:Cs2HammingWindow.hpp line:73
struct PyCallBack_Cs2HammingWindow : public tsa::Cs2HammingWindow {
	using tsa::Cs2HammingWindow::Cs2HammingWindow;

	void operator()(class tsa::SeqView<double> & a0) override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const tsa::Cs2HammingWindow *>(this), "__call__");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::overload_caster_t<void> caster;
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
				static pybind11::detail::overload_caster_t<void> caster;
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
				static pybind11::detail::overload_caster_t<void> caster;
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
				static pybind11::detail::overload_caster_t<void> caster;
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
				static pybind11::detail::overload_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return BaseWindow::FillWindow();
	}
};

// tsa::Cs2HannWindow file:Cs2HannWindow.hpp line:73
struct PyCallBack_Cs2HannWindow : public tsa::Cs2HannWindow {
	using tsa::Cs2HannWindow::Cs2HannWindow;

	void operator()(class tsa::SeqView<double> & a0) override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const tsa::Cs2HannWindow *>(this), "__call__");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::overload_caster_t<void> caster;
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
				static pybind11::detail::overload_caster_t<void> caster;
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
				static pybind11::detail::overload_caster_t<void> caster;
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
				static pybind11::detail::overload_caster_t<void> caster;
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
				static pybind11::detail::overload_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return BaseWindow::FillWindow();
	}
};

// tsa::DCT file:DCT.hpp line:73
struct PyCallBack_DCT : public tsa::DCT {
	using tsa::DCT::DCT;

	void MakePlan() throw() override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const tsa::DCT *>(this), "MakePlan");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>();
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::overload_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return DCT::MakePlan();
	}
};

// tsa::IDCT file:IDCT.hpp line:73
struct PyCallBack_IDCT : public tsa::IDCT {
    using tsa::IDCT::IDCT;

    void MakePlan() throw() override {
        pybind11::gil_scoped_acquire gil;
        pybind11::function overload = pybind11::get_overload(static_cast<const tsa::IDCT *>(this), "MakePlan");
        if (overload) {
            auto o = overload.operator()<pybind11::return_value_policy::reference>();
            if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
                static pybind11::detail::overload_caster_t<void> caster;
                return pybind11::detail::cast_ref<void>(std::move(o), caster);
            }
            else return pybind11::detail::cast_safe<void>(std::move(o));
        }
        return IDCT::MakePlan();
    }
};

// tsa::DST file:DST.hpp line:73
struct PyCallBack_DST : public tsa::DST {
	using tsa::DST::DST;

	void MakePlan() throw() override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const tsa::DST *>(this), "MakePlan");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>();
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::overload_caster_t<void> caster;
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
		pybind11::handle cl_type = cl;

		cl.def("__init__", [](tsa::BLInterpolation *self_, unsigned int  const &a0, unsigned int  const &a1, unsigned int  const &a2, unsigned int  const &a3, unsigned int  const &a4) { new (self_) tsa::BLInterpolation(a0, a1, a2, a3, a4); }, "doc");
		cl.def("__init__", [](tsa::BLInterpolation *self_, unsigned int  const &a0, unsigned int  const &a1, unsigned int  const &a2, unsigned int  const &a3, unsigned int  const &a4, double  const &a5) { new (self_) tsa::BLInterpolation(a0, a1, a2, a3, a4, a5); }, "doc");
		cl.def(pybind11::init<unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, double, enum tsa::BLInterpolation::NormalizationType>(), pybind11::arg("channels"), pybind11::arg("outdata"), pybind11::arg("irate"), pybind11::arg("orate"), pybind11::arg("order"), pybind11::arg("alpha"), pybind11::arg("nt"));

		cl.def(pybind11::init<const class tsa::BLInterpolation &>(), pybind11::arg("from"));

		pybind11::enum_<tsa::BLInterpolation::NormalizationType>(cl, "NormalizationType", "")
			.value("NONormalization", tsa::BLInterpolation::NormalizationType::NONormalization)
			.value("DCNormalization", tsa::BLInterpolation::NormalizationType::DCNormalization)
			.export_values();

		cl.def("assign", (class tsa::BLInterpolation & (tsa::BLInterpolation::*)(const class tsa::BLInterpolation &)) &tsa::BLInterpolation::operator=, "Assignement operator\n\n \n The instance to be assigned from\n\n \n a reference to a new object\n\nC++: tsa::BLInterpolation::operator=(const class tsa::BLInterpolation &) --> class tsa::BLInterpolation &", pybind11::return_value_policy::automatic, pybind11::arg("from"));
		cl.def("Input", (class tsa::BLInterpolation & (tsa::BLInterpolation::*)(class tsa::SeqView<double> &)) &tsa::BLInterpolation::Input, "C++: tsa::BLInterpolation::Input(class tsa::SeqView<double> &) --> class tsa::BLInterpolation &", pybind11::return_value_policy::automatic, pybind11::arg("indata"));
		cl.def("Output", (class tsa::BLInterpolation & (tsa::BLInterpolation::*)(class tsa::SeqView<double> &)) &tsa::BLInterpolation::Output, "C++: tsa::BLInterpolation::Output(class tsa::SeqView<double> &) --> class tsa::BLInterpolation &", pybind11::return_value_policy::automatic, pybind11::arg("outdata"));
		cl.def("GetDataAvailable", (long (tsa::BLInterpolation::*)()) &tsa::BLInterpolation::GetDataAvailable, "C++: tsa::BLInterpolation::GetDataAvailable() --> long");
		cl.def("GetStartTime", (double (tsa::BLInterpolation::*)()) &tsa::BLInterpolation::GetStartTime, "Start time of the next sequence of resampled data.\n\n \n \n\n the start time of the next sequence of resampled data\n\nC++: tsa::BLInterpolation::GetStartTime() --> double");
	}
	{ // tsa::Cs2HammingWindow file:Cs2HammingWindow.hpp line:73
		pybind11::class_<tsa::Cs2HammingWindow, std::shared_ptr<tsa::Cs2HammingWindow>, PyCallBack_Cs2HammingWindow, tsa::BaseWindow> cl(M("tsa"), "Cs2HammingWindow", "Cs2Hamming windowing algorithm");
		pybind11::handle cl_type = cl;

		cl.def(pybind11::init<int>(), pybind11::arg("size"));

		cl.def(pybind11::init<int, const class std::basic_string<char> &>(), pybind11::arg("size"), pybind11::arg(""));

		cl.def(pybind11::init<PyCallBack_Cs2HammingWindow const &>());
		cl.def("__call__", (void (tsa::Cs2HammingWindow::*)(class tsa::SeqView<double> &)) &tsa::Cs2HammingWindow::operator(), "Apply the window to a given time view.\n\n \n the time view \n\nC++: tsa::Cs2HammingWindow::operator()(class tsa::SeqView<double> &) --> void", pybind11::arg("v1"));
		cl.def("__call__", (void (tsa::Cs2HammingWindow::*)(class tsa::SeqView<double> &, class tsa::SeqView<double> &)) &tsa::Cs2HammingWindow::operator(), "Apply a window to an input view and write the results on a \n output view.\n\n \n the input view\n \n\n the output view\n\n         \n\nC++: tsa::Cs2HammingWindow::operator()(class tsa::SeqView<double> &, class tsa::SeqView<double> &) --> void", pybind11::arg("v1"), pybind11::arg("v2"));
		cl.def("Resize", (void (tsa::Cs2HammingWindow::*)(unsigned int)) &tsa::Cs2HammingWindow::Resize, "Resize the window dimension.\n\n \n new size for the window\n\nC++: tsa::Cs2HammingWindow::Resize(unsigned int) --> void", pybind11::arg("size"));
		cl.def("__call__", (double (tsa::Cs2HammingWindow::*)(int)) &tsa::Cs2HammingWindow::operator(), "Get the value of the window at a given index.\n\n \n \n\n the value of the window at the given plage\n\nC++: tsa::Cs2HammingWindow::operator()(int) --> double", pybind11::arg("i"));
		cl.def("assign", (class tsa::Cs2HammingWindow & (tsa::Cs2HammingWindow::*)(const class tsa::Cs2HammingWindow &)) &tsa::Cs2HammingWindow::operator=, "C++: tsa::Cs2HammingWindow::operator=(const class tsa::Cs2HammingWindow &) --> class tsa::Cs2HammingWindow &", pybind11::return_value_policy::automatic, pybind11::arg(""));
	}
	{ // tsa::Cs2HannWindow file:Cs2HannWindow.hpp line:73
		pybind11::class_<tsa::Cs2HannWindow, std::shared_ptr<tsa::Cs2HannWindow>, PyCallBack_Cs2HannWindow, tsa::BaseWindow> cl(M("tsa"), "Cs2HannWindow", "Cs2Hann windowing algorithm");
		pybind11::handle cl_type = cl;

		cl.def(pybind11::init<int>(), pybind11::arg("size"));

		cl.def(pybind11::init<int, const class std::basic_string<char> &>(), pybind11::arg("size"), pybind11::arg(""));

		cl.def("__call__", (void (tsa::Cs2HannWindow::*)(class tsa::SeqView<double> &)) &tsa::Cs2HannWindow::operator(), "Apply the window to a given time view.\n\n \n the time view \n\nC++: tsa::Cs2HannWindow::operator()(class tsa::SeqView<double> &) --> void", pybind11::arg("v1"));
		cl.def("__call__", (void (tsa::Cs2HannWindow::*)(class tsa::SeqView<double> &, class tsa::SeqView<double> &)) &tsa::Cs2HannWindow::operator(), "Apply a window to an input view and write the results on a \n output view.\n\n \n the input view\n \n\n the output view\n\n         \n\nC++: tsa::Cs2HannWindow::operator()(class tsa::SeqView<double> &, class tsa::SeqView<double> &) --> void", pybind11::arg("v1"), pybind11::arg("v2"));
		cl.def("Resize", (void (tsa::Cs2HannWindow::*)(unsigned int)) &tsa::Cs2HannWindow::Resize, "Resize the window dimension.\n\n \n new size for the window\n\nC++: tsa::Cs2HannWindow::Resize(unsigned int) --> void", pybind11::arg("size"));
		cl.def("assign", (class tsa::Cs2HannWindow & (tsa::Cs2HannWindow::*)(const class tsa::Cs2HannWindow &)) &tsa::Cs2HannWindow::operator=, "C++: tsa::Cs2HannWindow::operator=(const class tsa::Cs2HannWindow &) --> class tsa::Cs2HannWindow &", pybind11::return_value_policy::automatic, pybind11::arg(""));
	}
	{ // tsa::DCT file:DCT.hpp line:73
		pybind11::class_<tsa::DCT, std::shared_ptr<tsa::DCT>, PyCallBack_DCT, tsa::BaseFFT> cl(M("tsa"), "DCT", "Multichannel Discrete Cosine Transform.");
		pybind11::handle cl_type = cl;

		cl.def("__init__", [cl_type](pybind11::handle self_) { if (self_.get_type() == cl_type) new (self_.cast<tsa::DCT *>()) tsa::DCT(); else new (self_.cast<PyCallBack_DCT *>()) PyCallBack_DCT(); }, "doc");
		cl.def("__init__", [cl_type](pybind11::handle self_, int  const &a0) { if (self_.get_type() == cl_type) new (self_.cast<tsa::DCT *>()) tsa::DCT(a0); else new (self_.cast<PyCallBack_DCT *>()) PyCallBack_DCT(a0); }, "doc");
		cl.def("__init__", [cl_type](pybind11::handle self_, int  const &a0, enum tsa::FFTPlanningMode  const &a1) { if (self_.get_type() == cl_type) new (self_.cast<tsa::DCT *>()) tsa::DCT(a0, a1); else new (self_.cast<PyCallBack_DCT *>()) PyCallBack_DCT(a0, a1); }, "doc");
		cl.def(pybind11::init<int, enum tsa::FFTPlanningMode, bool>(), pybind11::arg("size"), pybind11::arg("mode"), pybind11::arg("PreserveInput"));

		cl.def(pybind11::init<PyCallBack_DCT const &>());
		cl.def("__call__", (void (tsa::DCT::*)(class tsa::SeqView<double> &, class tsa::SeqView<double> &)) &tsa::DCT::operator(), "Apply the transformation on the data\n\n \n a reference to the buffer containing the input data\n \n\n a reference to the buffer containing the input data\n\n \n a reference to this instance of the class\n\nC++: tsa::DCT::operator()(class tsa::SeqView<double> &, class tsa::SeqView<double> &) --> void", pybind11::arg("in"), pybind11::arg("out"));
		cl.def("MakePlan", (void (tsa::DCT::*)()) &tsa::DCT::MakePlan, "Make a new plan, with the current parameters.\n\n \n std::runtime_error The new plan cannot be created\n\nC++: tsa::DCT::MakePlan() --> void");
		cl.def("assign", (class tsa::DCT & (tsa::DCT::*)(const class tsa::DCT &)) &tsa::DCT::operator=, "C++: tsa::DCT::operator=(const class tsa::DCT &) --> class tsa::DCT &", pybind11::return_value_policy::automatic, pybind11::arg(""));
	}
{ // tsa::IDCT file:IDCT.hpp line:73
pybind11::class_<tsa::IDCT, std::shared_ptr<tsa::IDCT>, PyCallBack_IDCT, tsa::BaseFFT> cl(M("tsa"), "IDCT", "Multichannel Discrete Cosine Transform.");
pybind11::handle cl_type = cl;

cl.def("__init__", [cl_type](pybind11::handle self_) { if (self_.get_type() == cl_type) new (self_.cast<tsa::IDCT *>()) tsa::IDCT(); else new (self_.cast<PyCallBack_IDCT *>()) PyCallBack_IDCT(); }, "doc");
cl.def("__init__", [cl_type](pybind11::handle self_, int  const &a0) { if (self_.get_type() == cl_type) new (self_.cast<tsa::IDCT *>()) tsa::IDCT(a0); else new (self_.cast<PyCallBack_IDCT *>()) PyCallBack_IDCT(a0); }, "doc");
cl.def("__init__", [cl_type](pybind11::handle self_, int  const &a0, enum tsa::FFTPlanningMode  const &a1) { if (self_.get_type() == cl_type) new (self_.cast<tsa::IDCT *>()) tsa::IDCT(a0, a1); else new (self_.cast<PyCallBack_IDCT *>()) PyCallBack_IDCT(a0, a1); }, "doc");
cl.def(pybind11::init<int, enum tsa::FFTPlanningMode, bool>(), pybind11::arg("size"), pybind11::arg("mode"), pybind11::arg("PreserveInput"));

cl.def(pybind11::init<PyCallBack_IDCT const &>());
cl.def("__call__", (void (tsa::IDCT::*)(class tsa::SeqView<double> &, class tsa::SeqView<double> &)) &tsa::IDCT::operator(), "Apply the transformation on the data\n\n \n a reference to the buffer containing the input data\n \n\n a reference to the buffer containing the input data\n\n \n a reference to this instance of the class\n\nC++: tsa::IDCT::operator()(class tsa::SeqView<double> &, class tsa::SeqView<double> &) --> void", pybind11::arg("in"), pybind11::arg("out"));
cl.def("MakePlan", (void (tsa::IDCT::*)()) &tsa::IDCT::MakePlan, "Make a new plan, with the current parameters.\n\n \n std::runtime_error The new plan cannot be created\n\nC++: tsa::IDCT::MakePlan() --> void");
cl.def("assign", (class tsa::IDCT & (tsa::IDCT::*)(const class tsa::IDCT &)) &tsa::IDCT::operator=, "C++: tsa::IDCT::operator=(const class tsa::IDCT &) --> class tsa::IDCT &", pybind11::return_value_policy::automatic, pybind11::arg(""));
}
	{ // tsa::DST file:DST.hpp line:73
		pybind11::class_<tsa::DST, std::shared_ptr<tsa::DST>, PyCallBack_DST, tsa::BaseFFT> cl(M("tsa"), "DST", "Multichannel Discrete Sine Transform.");
		pybind11::handle cl_type = cl;

		cl.def("__init__", [cl_type](pybind11::handle self_) { if (self_.get_type() == cl_type) new (self_.cast<tsa::DST *>()) tsa::DST(); else new (self_.cast<PyCallBack_DST *>()) PyCallBack_DST(); }, "doc");
		cl.def("__init__", [cl_type](pybind11::handle self_, int  const &a0) { if (self_.get_type() == cl_type) new (self_.cast<tsa::DST *>()) tsa::DST(a0); else new (self_.cast<PyCallBack_DST *>()) PyCallBack_DST(a0); }, "doc");
		cl.def("__init__", [cl_type](pybind11::handle self_, int  const &a0, enum tsa::FFTPlanningMode  const &a1) { if (self_.get_type() == cl_type) new (self_.cast<tsa::DST *>()) tsa::DST(a0, a1); else new (self_.cast<PyCallBack_DST *>()) PyCallBack_DST(a0, a1); }, "doc");
		cl.def(pybind11::init<int, enum tsa::FFTPlanningMode, bool>(), pybind11::arg("size"), pybind11::arg("mode"), pybind11::arg("PreserveInput"));

		cl.def(pybind11::init<PyCallBack_DST const &>());
		cl.def("__call__", (void (tsa::DST::*)(class tsa::SeqView<double> &, class tsa::SeqView<double> &)) &tsa::DST::operator(), "Apply the transformation on the data\n\n \n a reference to the buffer containing the input data\n \n\n a reference to the buffer containing the input data\n\n \n a reference to this instance of the class\n\nC++: tsa::DST::operator()(class tsa::SeqView<double> &, class tsa::SeqView<double> &) --> void", pybind11::arg("in"), pybind11::arg("out"));
		cl.def("MakePlan", (void (tsa::DST::*)()) &tsa::DST::MakePlan, "Make a new plan, with the current parameters.\n\n \n std::runtime_error The new plan cannot be created\n\nC++: tsa::DST::MakePlan() --> void");
		cl.def("assign", (class tsa::DST & (tsa::DST::*)(const class tsa::DST &)) &tsa::DST::operator=, "C++: tsa::DST::operator=(const class tsa::DST &) --> class tsa::DST &", pybind11::return_value_policy::automatic, pybind11::arg(""));
	}
	{ // tsa::FifoBuffer file:FifoBuffer.hpp line:76
		pybind11::class_<tsa::FifoBuffer, std::shared_ptr<tsa::FifoBuffer>> cl(M("tsa"), "FifoBuffer", "Band limited interpolation.\n\n ");
		pybind11::handle cl_type = cl;

		cl.def(pybind11::init<unsigned int>(), pybind11::arg("channels"));

		cl.def(pybind11::init<const class tsa::FifoBuffer &>(), pybind11::arg("from"));

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
	{ // tsa::DoubleWhitening file:DoubleWhitening.hpp line:81
		pybind11::class_<tsa::DoubleWhitening, std::shared_ptr<tsa::DoubleWhitening>, tsa::AlgoBase> cl(M("tsa"), "DoubleWhitening", "A more detailed description of DoubleWhitening\n\n     \n Implement the double whitening filter in time domain\n\n     ");
		pybind11::handle cl_type = cl;

		cl.def(pybind11::init<class tsa::LatticeView &, unsigned int, unsigned int>(), pybind11::arg("LV"), pybind11::arg("OutputSize"), pybind11::arg("ExtraSize"));

		cl.def(pybind11::init<class boost::numeric::ublas::vector<double, class boost::numeric::ublas::unbounded_array<double, class std::allocator<double> > > &, class boost::numeric::ublas::vector<double, class boost::numeric::ublas::unbounded_array<double, class std::allocator<double> > > &, class boost::numeric::ublas::matrix<double, struct boost::numeric::ublas::basic_row_major<unsigned long, long>, class boost::numeric::ublas::unbounded_array<double, class std::allocator<double> > > &, class boost::numeric::ublas::matrix<double, struct boost::numeric::ublas::basic_row_major<unsigned long, long>, class boost::numeric::ublas::unbounded_array<double, class std::allocator<double> > > &, unsigned int, unsigned int>(), pybind11::arg("ParcorF"), pybind11::arg("ParcorB"), pybind11::arg("ErrF"), pybind11::arg("ErrB"), pybind11::arg("OutputSize"), pybind11::arg("ExtraSize"));

		cl.def("init", (void (tsa::DoubleWhitening::*)(class tsa::LatticeView &)) &tsa::DoubleWhitening::init, "C++: tsa::DoubleWhitening::init(class tsa::LatticeView &) --> void", pybind11::arg("LV"));
		cl.def("Load", [](tsa::DoubleWhitening &o, const char * a0) -> void { return o.Load(a0); }, "", pybind11::arg("filename"));
		cl.def("Load", (void (tsa::DoubleWhitening::*)(const char *, const char *)) &tsa::DoubleWhitening::Load, "C++: tsa::DoubleWhitening::Load(const char *, const char *) --> void", pybind11::arg("filename"), pybind11::arg("fmt"));
		cl.def("Save", [](tsa::DoubleWhitening &o, const char * a0) -> void { return o.Save(a0); }, "", pybind11::arg("filename"));
		cl.def("Save", (void (tsa::DoubleWhitening::*)(const char *, const char *)) &tsa::DoubleWhitening::Save, "C++: tsa::DoubleWhitening::Save(const char *, const char *) --> void", pybind11::arg("filename"), pybind11::arg("fmt"));
		cl.def("xml_serialize", (void (tsa::DoubleWhitening::*)(class eternity::xml_archive &, const char *)) &tsa::DoubleWhitening::xml_serialize, "C++: tsa::DoubleWhitening::xml_serialize(class eternity::xml_archive &, const char *) --> void", pybind11::arg("xml"), pybind11::arg("p"));
		cl.def("assign", (class tsa::DoubleWhitening & (tsa::DoubleWhitening::*)(const class tsa::DoubleWhitening &)) &tsa::DoubleWhitening::operator=, "C++: tsa::DoubleWhitening::operator=(const class tsa::DoubleWhitening &) --> class tsa::DoubleWhitening &", pybind11::return_value_policy::automatic, pybind11::arg(""));
        cl.def("Input", (class tsa::DoubleWhitening & (tsa::DoubleWhitening::*)(class tsa::SeqView<double> &)) &tsa::DoubleWhitening::Input, "C++: tsa::DoubleWhitening::Input(class tsa::SeqView<double> &) --> class tsa::DoubleWhitening &", pybind11::return_value_policy::automatic, pybind11::arg("indata"));
        cl.def("Output", (class tsa::DoubleWhitening & (tsa::DoubleWhitening::*)(class tsa::SeqView<double> &)) &tsa::DoubleWhitening::Output, "C++: tsa::DoubleWhitening::Output(class tsa::SeqView<double> &) --> class tsa::DoubleWhitening &", pybind11::return_value_policy::automatic, pybind11::arg("outdata"));


}
}


// File: EventDescription.cpp
#include <BaseFFT.hpp>
#include <BaseWindow.hpp>
#include <ClusterizedEventFullFeatured.hpp>
#include <EventDescription.hpp>
#include <EventFullFeatured.hpp>
#include <InverseRealFFT.hpp>
#include <KaiserWindow.hpp>
#include <LSLLearning.hpp>
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
#include <initializer_list>
#include <iterator>
#include <map>
#include <memory>
#include <sstream> // __str__
#include <string>
#include <utility>

#include <pybind11/pybind11.h>

#ifndef BINDER_PYBIND11_TYPE_CASTER
	#define BINDER_PYBIND11_TYPE_CASTER
	PYBIND11_DECLARE_HOLDER_TYPE(T, std::shared_ptr<T>);
	PYBIND11_DECLARE_HOLDER_TYPE(T, T*);
#endif

// tsa::InverseRealFFT file:InverseRealFFT.hpp line:66
struct PyCallBack_InverseRealFFT : public tsa::InverseRealFFT {
	using tsa::InverseRealFFT::InverseRealFFT;

	void MakePlan() throw() override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const tsa::InverseRealFFT *>(this), "MakePlan");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>();
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::overload_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return InverseRealFFT::MakePlan();
	}
};

// tsa::KaiserWindow file:KaiserWindow.hpp line:77
struct PyCallBack_KaiserWindow : public tsa::KaiserWindow {
	using tsa::KaiserWindow::KaiserWindow;

	void operator()(class tsa::SeqView<double> & a0) override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const tsa::KaiserWindow *>(this), "__call__");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::overload_caster_t<void> caster;
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
				static pybind11::detail::overload_caster_t<void> caster;
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
				static pybind11::detail::overload_caster_t<void> caster;
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
				static pybind11::detail::overload_caster_t<void> caster;
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
				static pybind11::detail::overload_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return BaseWindow::FillWindow();
	}
};

void bind_EventDescription(std::function< pybind11::module &(std::string const &namespace_) > &M)
{
	{ // tsa::EventFull file:EventDescription.hpp line:81
		pybind11::class_<tsa::EventFull, std::shared_ptr<tsa::EventFull>> cl(M("tsa"), "EventFull", "");
		pybind11::handle cl_type = cl;

		cl.def(pybind11::init<>());

		cl.def(pybind11::init<const class tsa::EventFull &>(), pybind11::arg(""));

		cl.def_readwrite("mTime", &tsa::EventFull::mTime);
		cl.def_readwrite("mSNR", &tsa::EventFull::mSNR);
		cl.def_readwrite("mCmax", &tsa::EventFull::mCmax);
		cl.def_readwrite("mlevel", &tsa::EventFull::mlevel);
		cl.def_readwrite("mWave", &tsa::EventFull::mWave);
		cl.def("assign", (class tsa::EventFull & (tsa::EventFull::*)(const class tsa::EventFull &)) &tsa::EventFull::operator=, "C++: tsa::EventFull::operator=(const class tsa::EventFull &) --> class tsa::EventFull &", pybind11::return_value_policy::automatic, pybind11::arg("from"));
	}
	{ // tsa::Event file:EventDescription.hpp line:116
		pybind11::class_<tsa::Event, std::shared_ptr<tsa::Event>> cl(M("tsa"), "Event", "");
		pybind11::handle cl_type = cl;

		cl.def(pybind11::init<>());

		cl.def(pybind11::init<const class tsa::Event &>(), pybind11::arg(""));

		cl.def_readwrite("mTime", &tsa::Event::mTime);
		cl.def_readwrite("mSNR", &tsa::Event::mSNR);
		cl.def_readwrite("mWave", &tsa::Event::mWave);
		cl.def("assign", (class tsa::Event & (tsa::Event::*)(const class tsa::Event &)) &tsa::Event::operator=, "C++: tsa::Event::operator=(const class tsa::Event &) --> class tsa::Event &", pybind11::return_value_policy::automatic, pybind11::arg("from"));
	}
	{ // tsa::ClusterizedEvent file:EventDescription.hpp line:151
		pybind11::class_<tsa::ClusterizedEvent, std::shared_ptr<tsa::ClusterizedEvent>> cl(M("tsa"), "ClusterizedEvent", "");
		pybind11::handle cl_type = cl;

		cl.def(pybind11::init<>());

		cl.def(pybind11::init<const class tsa::ClusterizedEvent &>(), pybind11::arg(""));

		cl.def_readwrite("mTime", &tsa::ClusterizedEvent::mTime);
		cl.def_readwrite("mLenght", &tsa::ClusterizedEvent::mLenght);
		cl.def_readwrite("mSNR", &tsa::ClusterizedEvent::mSNR);
		cl.def_readwrite("mWave", &tsa::ClusterizedEvent::mWave);
		cl.def("assign", (class tsa::ClusterizedEvent & (tsa::ClusterizedEvent::*)(const class tsa::ClusterizedEvent &)) &tsa::ClusterizedEvent::operator=, "C++: tsa::ClusterizedEvent::operator=(const class tsa::ClusterizedEvent &) --> class tsa::ClusterizedEvent &", pybind11::return_value_policy::automatic, pybind11::arg("from"));
	}
	{ // tsa::ClusterizedEventFull file:EventDescription.hpp line:179
		pybind11::class_<tsa::ClusterizedEventFull, std::shared_ptr<tsa::ClusterizedEventFull>> cl(M("tsa"), "ClusterizedEventFull", "");
		pybind11::handle cl_type = cl;

		cl.def(pybind11::init<>());

		cl.def(pybind11::init<const class tsa::ClusterizedEventFull &>(), pybind11::arg(""));

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
		pybind11::handle cl_type = cl;

		cl.def(pybind11::init<unsigned int>(), pybind11::arg("NumCoeff"));

		cl.def(pybind11::init<const class tsa::EventFullFeatured &>(), pybind11::arg(""));

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
		pybind11::handle cl_type = cl;

		cl.def(pybind11::init<unsigned int>(), pybind11::arg("NumCoeff"));

		cl.def(pybind11::init<const class tsa::ClusterizedEventFullFeatured &>(), pybind11::arg(""));

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
		pybind11::class_<tsa::InverseRealFFT, std::shared_ptr<tsa::InverseRealFFT>, PyCallBack_InverseRealFFT, tsa::BaseFFT> cl(M("tsa"), "InverseRealFFT", "Multichannel inverse real to complex FFT.\n\n This is the implementation of the FFT of a real multichannel buffer");
		pybind11::handle cl_type = cl;

		cl.def("__init__", [cl_type](pybind11::handle self_) { if (self_.get_type() == cl_type) new (self_.cast<tsa::InverseRealFFT *>()) tsa::InverseRealFFT(); else new (self_.cast<PyCallBack_InverseRealFFT *>()) PyCallBack_InverseRealFFT(); }, "doc");
		cl.def("__init__", [cl_type](pybind11::handle self_, int  const &a0) { if (self_.get_type() == cl_type) new (self_.cast<tsa::InverseRealFFT *>()) tsa::InverseRealFFT(a0); else new (self_.cast<PyCallBack_InverseRealFFT *>()) PyCallBack_InverseRealFFT(a0); }, "doc");
		cl.def("__init__", [cl_type](pybind11::handle self_, int  const &a0, enum tsa::FFTPlanningMode  const &a1) { if (self_.get_type() == cl_type) new (self_.cast<tsa::InverseRealFFT *>()) tsa::InverseRealFFT(a0, a1); else new (self_.cast<PyCallBack_InverseRealFFT *>()) PyCallBack_InverseRealFFT(a0, a1); }, "doc");
		cl.def(pybind11::init<int, enum tsa::FFTPlanningMode, bool>(), pybind11::arg("size"), pybind11::arg("mode"), pybind11::arg("PreserveInput"));

		cl.def(pybind11::init<PyCallBack_InverseRealFFT const &>());
		cl.def("MakePlan", (void (tsa::InverseRealFFT::*)()) &tsa::InverseRealFFT::MakePlan, "Make a new plan, with the current parameters.\n\n \n std::runtime_error The new plan cannot be created\n\nC++: tsa::InverseRealFFT::MakePlan() --> void");
		cl.def("assign", (class tsa::InverseRealFFT & (tsa::InverseRealFFT::*)(const class tsa::InverseRealFFT &)) &tsa::InverseRealFFT::operator=, "C++: tsa::InverseRealFFT::operator=(const class tsa::InverseRealFFT &) --> class tsa::InverseRealFFT &", pybind11::return_value_policy::automatic, pybind11::arg(""));
	}
	{ // tsa::KaiserWindow file:KaiserWindow.hpp line:77
		pybind11::class_<tsa::KaiserWindow, std::shared_ptr<tsa::KaiserWindow>, PyCallBack_KaiserWindow, tsa::BaseWindow> cl(M("tsa"), "KaiserWindow", "Kaiser windowing algorithm\n Harris, F. J. \"On the Use of Windows for Harmonic Analysis with the Discrete Fourier Transform.\" \n Proceedings of the IEEE. Vol. 66 (January 1978). pp. 66-67.");
		pybind11::handle cl_type = cl;

		cl.def(pybind11::init<int>(), pybind11::arg("size"));

		cl.def(pybind11::init<int, const class std::basic_string<char> &>(), pybind11::arg("size"), pybind11::arg("par"));

		cl.def("__call__", (void (tsa::KaiserWindow::*)(class tsa::SeqView<double> &)) &tsa::KaiserWindow::operator(), "Apply the window to a given time view.\n\n \n the time view \n\nC++: tsa::KaiserWindow::operator()(class tsa::SeqView<double> &) --> void", pybind11::arg("v1"));
		cl.def("__call__", (void (tsa::KaiserWindow::*)(class tsa::SeqView<double> &, class tsa::SeqView<double> &)) &tsa::KaiserWindow::operator(), "Apply a window to an input view and write the results on a \n output view.\n\n \n the input view\n \n\n the output view\n\n         \n\nC++: tsa::KaiserWindow::operator()(class tsa::SeqView<double> &, class tsa::SeqView<double> &) --> void", pybind11::arg("v1"), pybind11::arg("v2"));
		cl.def("Resize", (void (tsa::KaiserWindow::*)(unsigned int)) &tsa::KaiserWindow::Resize, "Resize the window dimension.\n\n \n new size for the window\n\nC++: tsa::KaiserWindow::Resize(unsigned int) --> void", pybind11::arg("size"));
		cl.def("__call__", (double (tsa::KaiserWindow::*)(int)) &tsa::KaiserWindow::operator(), "Get the value of the window at a given index.\n\n \n \n\n the value of the window at the given plage\n\nC++: tsa::KaiserWindow::operator()(int) --> double", pybind11::arg("i"));
		cl.def("assign", (class tsa::KaiserWindow & (tsa::KaiserWindow::*)(const class tsa::KaiserWindow &)) &tsa::KaiserWindow::operator=, "C++: tsa::KaiserWindow::operator=(const class tsa::KaiserWindow &) --> class tsa::KaiserWindow &", pybind11::return_value_policy::automatic, pybind11::arg(""));
	}
	{ // tsa::LatticeFilter file:LatticeFilter.hpp line:77
		pybind11::class_<tsa::LatticeFilter, std::shared_ptr<tsa::LatticeFilter>, tsa::AlgoBase> cl(M("tsa"), "LatticeFilter", "Implement the lattice filter\n\n     ");
		pybind11::handle cl_type = cl;

		cl.def(pybind11::init<class tsa::LatticeView &>(), pybind11::arg("LV"));

		cl.def(pybind11::init<class boost::numeric::ublas::vector<double, class boost::numeric::ublas::unbounded_array<double, class std::allocator<double> > > &, class boost::numeric::ublas::vector<double, class boost::numeric::ublas::unbounded_array<double, class std::allocator<double> > > &, class boost::numeric::ublas::matrix<double, struct boost::numeric::ublas::basic_row_major<unsigned long, long>, class boost::numeric::ublas::unbounded_array<double, class std::allocator<double> > > &, class boost::numeric::ublas::matrix<double, struct boost::numeric::ublas::basic_row_major<unsigned long, long>, class boost::numeric::ublas::unbounded_array<double, class std::allocator<double> > > &>(), pybind11::arg("ParcorF"), pybind11::arg("ParcorB"), pybind11::arg("ErrF"), pybind11::arg("ErrB"));

		cl.def("Load", [](tsa::LatticeFilter &o, const char * a0) -> void { return o.Load(a0); }, "", pybind11::arg("filename"));
		cl.def("Load", (void (tsa::LatticeFilter::*)(const char *, const char *)) &tsa::LatticeFilter::Load, "C++: tsa::LatticeFilter::Load(const char *, const char *) --> void", pybind11::arg("filename"), pybind11::arg("fmt"));
		cl.def("Save", [](tsa::LatticeFilter &o, const char * a0) -> void { return o.Save(a0); }, "", pybind11::arg("filename"));
		cl.def("Save", (void (tsa::LatticeFilter::*)(const char *, const char *)) &tsa::LatticeFilter::Save, "C++: tsa::LatticeFilter::Save(const char *, const char *) --> void", pybind11::arg("filename"), pybind11::arg("fmt"));
		cl.def("xml_serialize", (void (tsa::LatticeFilter::*)(class eternity::xml_archive &, const char *)) &tsa::LatticeFilter::xml_serialize, "C++: tsa::LatticeFilter::xml_serialize(class eternity::xml_archive &, const char *) --> void", pybind11::arg("xml"), pybind11::arg("p"));
		cl.def("__call__", (void (tsa::LatticeFilter::*)(class tsa::SeqView<double> &, class tsa::SeqView<double> &)) &tsa::LatticeFilter::operator(), "Declaration of execute operation\n\n \n Matrix containing Time Series\n \n\n Matrix containing the WhitenedData\n\nC++: tsa::LatticeFilter::operator()(class tsa::SeqView<double> &, class tsa::SeqView<double> &) --> void", pybind11::arg("InputData"), pybind11::arg("WhitenedData"));
		cl.def("init", (void (tsa::LatticeFilter::*)(class tsa::LatticeView &)) &tsa::LatticeFilter::init, "Initialization function\n \n\n lattice view\n\nC++: tsa::LatticeFilter::init(class tsa::LatticeView &) --> void", pybind11::arg("LV"));
		cl.def("assign", (class tsa::LatticeFilter & (tsa::LatticeFilter::*)(const class tsa::LatticeFilter &)) &tsa::LatticeFilter::operator=, "C++: tsa::LatticeFilter::operator=(const class tsa::LatticeFilter &) --> class tsa::LatticeFilter &", pybind11::return_value_policy::automatic, pybind11::arg(""));
	}
	{ // tsa::LSLLearning file:LSLLearning.hpp line:74
		pybind11::class_<tsa::LSLLearning, std::shared_ptr<tsa::LSLLearning>, tsa::AlgoBase> cl(M("tsa"), "LSLLearning", "algorithm for the learning phase of the Adaptive Least Squares Lattice");
		pybind11::handle cl_type = cl;

		cl.def("__init__", [](tsa::LSLLearning *self_, unsigned int  const &a0, double  const &a1) { new (self_) tsa::LSLLearning(a0, a1); }, "doc");
		cl.def(pybind11::init<unsigned int, double, double>(), pybind11::arg("Order"), pybind11::arg("sigma"), pybind11::arg("lambda"));

		cl.def(pybind11::init<const class tsa::LSLLearning &>(), pybind11::arg("from"));

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
}


// File: LeastSquaresLattice.cpp
#include <BaseFFT.hpp>
#include <BaseWindow.hpp>
#include <LSLLearning.hpp>
#include <LSLfilter.hpp>
#include <LatticeView.hpp>
#include <LeastSquaresLattice.hpp>
#include <NotchWidrow.hpp>
#include <RLSCanceler.hpp>
#include <RealFFT.hpp>
#include <SelectionOrderCriteria.hpp>
#include <SeqView.hpp>
#include <TF2Psd.hpp>
#include <TukeyWindow.hpp>
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
#include <initializer_list>
#include <iterator>
#include <map>
#include <memory>
#include <sstream> // __str__
#include <string>
#include <utility>

#include <pybind11/pybind11.h>

#ifndef BINDER_PYBIND11_TYPE_CASTER
	#define BINDER_PYBIND11_TYPE_CASTER
	PYBIND11_DECLARE_HOLDER_TYPE(T, std::shared_ptr<T>);
	PYBIND11_DECLARE_HOLDER_TYPE(T, T*);
#endif

// tsa::RealFFT file:RealFFT.hpp line:74
struct PyCallBack_RealFFT : public tsa::RealFFT {
	using tsa::RealFFT::RealFFT;

	void MakePlan() throw() override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const tsa::RealFFT *>(this), "MakePlan");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>();
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::overload_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return RealFFT::MakePlan();
	}
};

// tsa::TukeyWindow file:TukeyWindow.hpp line:76
struct PyCallBack_TukeyWindow : public tsa::TukeyWindow {
	using tsa::TukeyWindow::TukeyWindow;

	void operator()(class tsa::SeqView<double> & a0) override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const tsa::TukeyWindow *>(this), "__call__");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::overload_caster_t<void> caster;
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
				static pybind11::detail::overload_caster_t<void> caster;
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
				static pybind11::detail::overload_caster_t<void> caster;
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
				static pybind11::detail::overload_caster_t<void> caster;
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
				static pybind11::detail::overload_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return BaseWindow::FillWindow();
	}
};

void bind_LeastSquaresLattice(std::function< pybind11::module &(std::string const &namespace_) > &M)
{
	{ // tsa::LeastSquaresLattice file:LeastSquaresLattice.hpp line:79
		pybind11::class_<tsa::LeastSquaresLattice, std::shared_ptr<tsa::LeastSquaresLattice>, tsa::AlgoBase> cl(M("tsa"), "LeastSquaresLattice", "Estimate the parameters for the Least Squares Lattice filter and implement the adaptive whitening. \n\n     ");
		pybind11::handle cl_type = cl;

		cl.def(pybind11::init<class boost::numeric::ublas::matrix_row<class boost::numeric::ublas::matrix<double, struct boost::numeric::ublas::basic_row_major<unsigned long, long>, class boost::numeric::ublas::unbounded_array<double, class std::allocator<double> > > > &, class boost::numeric::ublas::matrix_row<class boost::numeric::ublas::matrix<double, struct boost::numeric::ublas::basic_row_major<unsigned long, long>, class boost::numeric::ublas::unbounded_array<double, class std::allocator<double> > > > &, unsigned int, double, unsigned int>(), pybind11::arg("LearnData"), pybind11::arg("WhitenData"), pybind11::arg("P"), pybind11::arg("lambda"), pybind11::arg("D"));

		cl.def("assign", (class tsa::LeastSquaresLattice & (tsa::LeastSquaresLattice::*)(const class tsa::LeastSquaresLattice &)) &tsa::LeastSquaresLattice::operator=, "Assignement operator\n\n \n The instance to be assigned from\n\n \n a reference to a new object\n\nC++: tsa::LeastSquaresLattice::operator=(const class tsa::LeastSquaresLattice &) --> class tsa::LeastSquaresLattice &", pybind11::return_value_policy::automatic, pybind11::arg("from"));
	}
	{ // tsa::LSLfilter file:LSLfilter.hpp line:76
		pybind11::class_<tsa::LSLfilter, std::shared_ptr<tsa::LSLfilter>, tsa::AlgoBase> cl(M("tsa"), "LSLfilter", "Algorithm for the filter phase of the Adaptive Least Squares Lattice");
		pybind11::handle cl_type = cl;

		cl.def("__init__", [](tsa::LSLfilter *self_, class tsa::LSLLearning & a0) { new (self_) tsa::LSLfilter(a0); }, "doc");
		cl.def("__init__", [](tsa::LSLfilter *self_, class tsa::LSLLearning & a0, double  const &a1) { new (self_) tsa::LSLfilter(a0, a1); }, "doc");
		cl.def("__init__", [](tsa::LSLfilter *self_, class tsa::LSLLearning & a0, double  const &a1, unsigned int  const &a2) { new (self_) tsa::LSLfilter(a0, a1, a2); }, "doc");
		cl.def(pybind11::init<class tsa::LSLLearning &, double, unsigned int, bool>(), pybind11::arg("LSL"), pybind11::arg("lambda"), pybind11::arg("size"), pybind11::arg("Norm"));

		cl.def("Load", [](tsa::LSLfilter &o, const char * a0) -> void { return o.Load(a0); }, "", pybind11::arg("filename"));
		cl.def("Load", (void (tsa::LSLfilter::*)(const char *, const char *)) &tsa::LSLfilter::Load, "C++: tsa::LSLfilter::Load(const char *, const char *) --> void", pybind11::arg("filename"), pybind11::arg("fmt"));
		cl.def("Save", [](tsa::LSLfilter &o, const char * a0) -> void { return o.Save(a0); }, "", pybind11::arg("filename"));
		cl.def("Save", (void (tsa::LSLfilter::*)(const char *, const char *)) &tsa::LSLfilter::Save, "C++: tsa::LSLfilter::Save(const char *, const char *) --> void", pybind11::arg("filename"), pybind11::arg("fmt"));
		cl.def("xml_serialize", (void (tsa::LSLfilter::*)(class eternity::xml_archive &, const char *)) &tsa::LSLfilter::xml_serialize, "C++: tsa::LSLfilter::xml_serialize(class eternity::xml_archive &, const char *) --> void", pybind11::arg("xml"), pybind11::arg("p"));
		cl.def("__call__", (void (tsa::LSLfilter::*)(class tsa::SeqView<double> &, class tsa::SeqView<double> &)) &tsa::LSLfilter::operator(), "for online process\n\nC++: tsa::LSLfilter::operator()(class tsa::SeqView<double> &, class tsa::SeqView<double> &) --> void", pybind11::arg("Data"), pybind11::arg("outdata"));
		cl.def("GetDataNeeded", (int (tsa::LSLfilter::*)()) &tsa::LSLfilter::GetDataNeeded, "Get the number of data needed in order to be able to \n call GetData successfully. If the returned value is less or \n equal than zero no data are needed.\n\n \n the needed data\n\nC++: tsa::LSLfilter::GetDataNeeded() --> int");
		cl.def("GetOrder", (unsigned int (tsa::LSLfilter::*)()) &tsa::LSLfilter::GetOrder, "C++: tsa::LSLfilter::GetOrder() --> unsigned int");
		cl.def("GetParcorForward", (double (tsa::LSLfilter::*)(unsigned int)) &tsa::LSLfilter::GetParcorForward, "C++: tsa::LSLfilter::GetParcorForward(unsigned int) --> double", pybind11::arg("j"));
		cl.def("GetParcorBackward", (double (tsa::LSLfilter::*)(unsigned int)) &tsa::LSLfilter::GetParcorBackward, "C++: tsa::LSLfilter::GetParcorBackward(unsigned int) --> double", pybind11::arg("j"));
		cl.def("GetEpf", (double (tsa::LSLfilter::*)(unsigned int)) &tsa::LSLfilter::GetEpf, "C++: tsa::LSLfilter::GetEpf(unsigned int) --> double", pybind11::arg("j"));
		cl.def("GetErrorForward", (double (tsa::LSLfilter::*)(unsigned int)) &tsa::LSLfilter::GetErrorForward, "C++: tsa::LSLfilter::GetErrorForward(unsigned int) --> double", pybind11::arg("j"));
		cl.def("GetErrorBackward", (double (tsa::LSLfilter::*)(unsigned int)) &tsa::LSLfilter::GetErrorBackward, "C++: tsa::LSLfilter::GetErrorBackward(unsigned int) --> double", pybind11::arg("j"));
		cl.def("GetSigma", (double (tsa::LSLfilter::*)(unsigned int)) &tsa::LSLfilter::GetSigma, "C++: tsa::LSLfilter::GetSigma(unsigned int) --> double", pybind11::arg("j"));
	}
	{ // tsa::NotchWidrow file:NotchWidrow.hpp line:71
		pybind11::class_<tsa::NotchWidrow, std::shared_ptr<tsa::NotchWidrow>, tsa::AlgoBase> cl(M("tsa"), "NotchWidrow", "Implement the lines removal using adaptive notch filters, with the Least Mean Squared method, Widrow's like.");
		pybind11::handle cl_type = cl;

		cl.def("__init__", [](tsa::NotchWidrow *self_, unsigned int  const &a0, class boost::numeric::ublas::matrix<double, struct boost::numeric::ublas::basic_row_major<unsigned long, long>, class boost::numeric::ublas::unbounded_array<double, class std::allocator<double> > > & a1) { new (self_) tsa::NotchWidrow(a0, a1); }, "doc");
		cl.def(pybind11::init<unsigned int, class boost::numeric::ublas::matrix<double, struct boost::numeric::ublas::basic_row_major<unsigned long, long>, class boost::numeric::ublas::unbounded_array<double, class std::allocator<double> > > &, double>(), pybind11::arg("channels"), pybind11::arg("FrequencyList"), pybind11::arg("C"));

		cl.def(pybind11::init<const class tsa::NotchWidrow &>(), pybind11::arg("from"));

		cl.def("__call__", (void (tsa::NotchWidrow::*)(class tsa::SeqView<double> &, class tsa::SeqView<double> &)) &tsa::NotchWidrow::operator(), "C++: tsa::NotchWidrow::operator()(class tsa::SeqView<double> &, class tsa::SeqView<double> &) --> void", pybind11::arg("InputData"), pybind11::arg("CleanedData"));
		cl.def("__call__", (void (tsa::NotchWidrow::*)(class tsa::SeqView<double> &, class tsa::SeqView<double> &, class tsa::SeqView<double> &)) &tsa::NotchWidrow::operator(), "C++: tsa::NotchWidrow::operator()(class tsa::SeqView<double> &, class tsa::SeqView<double> &, class tsa::SeqView<double> &) --> void", pybind11::arg("InputData"), pybind11::arg("CleanedData"), pybind11::arg("ReferenceSignal"));
		cl.def("assign", (class tsa::NotchWidrow & (tsa::NotchWidrow::*)(const class tsa::NotchWidrow &)) &tsa::NotchWidrow::operator=, "Assignement operator\n\n \n The instance to be assigned from\n\n \n a reference to a new object\n\nC++: tsa::NotchWidrow::operator=(const class tsa::NotchWidrow &) --> class tsa::NotchWidrow &", pybind11::return_value_policy::automatic, pybind11::arg("from"));
		cl.def("Getlstart", (double (tsa::NotchWidrow::*)()) &tsa::NotchWidrow::Getlstart, "C++: tsa::NotchWidrow::Getlstart() --> double");
	}
	{ // tsa::RealFFT file:RealFFT.hpp line:74
		pybind11::class_<tsa::RealFFT, std::shared_ptr<tsa::RealFFT>, PyCallBack_RealFFT, tsa::BaseFFT> cl(M("tsa"), "RealFFT", "Multichannel real to complex FFT.\n\n This is the implementation of the FFT of a real multichannel buffer");
		pybind11::handle cl_type = cl;

		cl.def("__init__", [cl_type](pybind11::handle self_) { if (self_.get_type() == cl_type) new (self_.cast<tsa::RealFFT *>()) tsa::RealFFT(); else new (self_.cast<PyCallBack_RealFFT *>()) PyCallBack_RealFFT(); }, "doc");
		cl.def("__init__", [cl_type](pybind11::handle self_, int  const &a0) { if (self_.get_type() == cl_type) new (self_.cast<tsa::RealFFT *>()) tsa::RealFFT(a0); else new (self_.cast<PyCallBack_RealFFT *>()) PyCallBack_RealFFT(a0); }, "doc");
		cl.def("__init__", [cl_type](pybind11::handle self_, int  const &a0, enum tsa::FFTPlanningMode  const &a1) { if (self_.get_type() == cl_type) new (self_.cast<tsa::RealFFT *>()) tsa::RealFFT(a0, a1); else new (self_.cast<PyCallBack_RealFFT *>()) PyCallBack_RealFFT(a0, a1); }, "doc");
		cl.def(pybind11::init<int, enum tsa::FFTPlanningMode, bool>(), pybind11::arg("size"), pybind11::arg("mode"), pybind11::arg("PreserveInput"));

		cl.def(pybind11::init<PyCallBack_RealFFT const &>());
		cl.def("MakePlan", (void (tsa::RealFFT::*)()) &tsa::RealFFT::MakePlan, "Make a new plan, with the current parameters.\n\n \n std::runtime_error The new plan cannot be created\n\nC++: tsa::RealFFT::MakePlan() --> void");
		cl.def("assign", (class tsa::RealFFT & (tsa::RealFFT::*)(const class tsa::RealFFT &)) &tsa::RealFFT::operator=, "C++: tsa::RealFFT::operator=(const class tsa::RealFFT &) --> class tsa::RealFFT &", pybind11::return_value_policy::automatic, pybind11::arg(""));
	}
	{ // tsa::RLSCanceler file:RLSCanceler.hpp line:71
		pybind11::class_<tsa::RLSCanceler, std::shared_ptr<tsa::RLSCanceler>, tsa::AlgoBase> cl(M("tsa"), "RLSCanceler", "");
		pybind11::handle cl_type = cl;

		cl.def(pybind11::init<unsigned int, double, double, unsigned int>(), pybind11::arg("Order"), pybind11::arg("delta"), pybind11::arg("lambda"), pybind11::arg("Channels"));

		cl.def(pybind11::init<const class tsa::RLSCanceler &>(), pybind11::arg("from"));

		cl.def("assign", (class tsa::RLSCanceler & (tsa::RLSCanceler::*)(const class tsa::RLSCanceler &)) &tsa::RLSCanceler::operator=, "Assignement operator\n\n \n The instance to be assigned from\n\n \n a reference to a new object\n\nC++: tsa::RLSCanceler::operator=(const class tsa::RLSCanceler &) --> class tsa::RLSCanceler &", pybind11::return_value_policy::automatic, pybind11::arg("from"));
		cl.def("__call__", (void (tsa::RLSCanceler::*)(class tsa::SeqView<double> &, class tsa::SeqView<double> &)) &tsa::RLSCanceler::operator(), "C++: tsa::RLSCanceler::operator()(class tsa::SeqView<double> &, class tsa::SeqView<double> &) --> void", pybind11::arg("InputData"), pybind11::arg("CleanedData"));
		cl.def("__call__", (void (tsa::RLSCanceler::*)(class tsa::SeqView<double> &, class tsa::SeqView<double> &, class tsa::SeqView<double> &)) &tsa::RLSCanceler::operator(), "C++: tsa::RLSCanceler::operator()(class tsa::SeqView<double> &, class tsa::SeqView<double> &, class tsa::SeqView<double> &) --> void", pybind11::arg("InputData"), pybind11::arg("CleanedData"), pybind11::arg("ReferenceSignal"));
		cl.def("Getlstart", (double (tsa::RLSCanceler::*)()) &tsa::RLSCanceler::Getlstart, "the last step\n\nC++: tsa::RLSCanceler::Getlstart() --> double");
		cl.def("GetWeights", (double (tsa::RLSCanceler::*)(unsigned int, unsigned int)) &tsa::RLSCanceler::GetWeights, "index of the weights\n \n\n channel to which the weights belong\n \n\n yhe weights of the RLS filter\n\nC++: tsa::RLSCanceler::GetWeights(unsigned int, unsigned int) --> double", pybind11::arg("j"), pybind11::arg("channel"));
	}
	{ // tsa::SelectionOrderCriteria file:SelectionOrderCriteria.hpp line:78
		pybind11::class_<tsa::SelectionOrderCriteria, std::shared_ptr<tsa::SelectionOrderCriteria>> cl(M("tsa"), "SelectionOrderCriteria", "A more detailed description of SelectionOrderCriteria\n\n    Produce order selection criteria");
		pybind11::handle cl_type = cl;

		cl.def(pybind11::init<unsigned int, unsigned int>(), pybind11::arg("N"), pybind11::arg("Order"));

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
	{ // tsa::TF2PSD file:TF2Psd.hpp line:71
		pybind11::class_<tsa::TF2PSD, std::shared_ptr<tsa::TF2PSD>, tsa::AlgoBase> cl(M("tsa"), "TF2PSD", "Convert a transfer function to a PSD \n\n     ");
		pybind11::handle cl_type = cl;

		cl.def("__init__", [](tsa::TF2PSD *self_) { new (self_) tsa::TF2PSD(); }, "doc");
		cl.def(pybind11::init<bool>(), pybind11::arg("squared"));

		cl.def(pybind11::init<const class tsa::TF2PSD &>(), pybind11::arg("from"));

		cl.def("assign", (class tsa::TF2PSD & (tsa::TF2PSD::*)(const class tsa::TF2PSD &)) &tsa::TF2PSD::operator=, "Assignement operator\n\n \n The instance to be assigned from\n\n \n a reference to a new object\n\nC++: tsa::TF2PSD::operator=(const class tsa::TF2PSD &) --> class tsa::TF2PSD &", pybind11::return_value_policy::automatic, pybind11::arg("from"));
		cl.def("GetSquared", (bool (tsa::TF2PSD::*)()) &tsa::TF2PSD::GetSquared, "C++: tsa::TF2PSD::GetSquared() --> bool");
		cl.def("SetSquared", [](tsa::TF2PSD &o) -> void { return o.SetSquared(); }, "");
		cl.def("SetSquared", (void (tsa::TF2PSD::*)(bool)) &tsa::TF2PSD::SetSquared, "C++: tsa::TF2PSD::SetSquared(bool) --> void", pybind11::arg("squared"));
	}
	{ // tsa::TukeyWindow file:TukeyWindow.hpp line:76
		pybind11::class_<tsa::TukeyWindow, std::shared_ptr<tsa::TukeyWindow>, PyCallBack_TukeyWindow, tsa::BaseWindow> cl(M("tsa"), "TukeyWindow", "Tukey windowing algorithm\n Harris, F. J. \"On the Use of Windows for Harmonic Analysis with the Discrete Fourier Transform.\" \n Proceedings of the IEEE. Vol. 66 (January 1978). pp. 66-67.");
		pybind11::handle cl_type = cl;

		cl.def(pybind11::init<int>(), pybind11::arg("size"));

		cl.def(pybind11::init<int, const class std::basic_string<char> &>(), pybind11::arg("size"), pybind11::arg("par"));

		cl.def("__call__", (void (tsa::TukeyWindow::*)(class tsa::SeqView<double> &)) &tsa::TukeyWindow::operator(), "Apply the window to a given time view.\n\n \n the time view \n\nC++: tsa::TukeyWindow::operator()(class tsa::SeqView<double> &) --> void", pybind11::arg("v1"));
		cl.def("__call__", (void (tsa::TukeyWindow::*)(class tsa::SeqView<double> &, class tsa::SeqView<double> &)) &tsa::TukeyWindow::operator(), "Apply a window to an input view and write the results on a \n output view.\n\n \n the input view\n \n\n the output view\n\n         \n\nC++: tsa::TukeyWindow::operator()(class tsa::SeqView<double> &, class tsa::SeqView<double> &) --> void", pybind11::arg("v1"), pybind11::arg("v2"));
		cl.def("Resize", (void (tsa::TukeyWindow::*)(unsigned int)) &tsa::TukeyWindow::Resize, "Resize the window dimension.\n\n \n new size for the window\n\nC++: tsa::TukeyWindow::Resize(unsigned int) --> void", pybind11::arg("size"));
		cl.def("__call__", (double (tsa::TukeyWindow::*)(int)) &tsa::TukeyWindow::operator(), "Get the value of the window at a given index.\n\n \n \n\n the value of the window at the given plage\n\nC++: tsa::TukeyWindow::operator()(int) --> double", pybind11::arg("i"));
		cl.def("assign", (class tsa::TukeyWindow & (tsa::TukeyWindow::*)(const class tsa::TukeyWindow &)) &tsa::TukeyWindow::operator=, "C++: tsa::TukeyWindow::operator=(const class tsa::TukeyWindow &) --> class tsa::TukeyWindow &", pybind11::return_value_policy::automatic, pybind11::arg(""));
	}
}


// File: TukeyHannWindow.cpp
#include <BaseWindow.hpp>
#include <SeqView.hpp>
#include <TukeyHannWindow.hpp>
#include <boost/numeric/ublas/functional.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/storage.hpp>
#include <initializer_list>
#include <iterator>
#include <memory>
#include <sstream> // __str__
#include <string>

#include <pybind11/pybind11.h>

#ifndef BINDER_PYBIND11_TYPE_CASTER
	#define BINDER_PYBIND11_TYPE_CASTER
	PYBIND11_DECLARE_HOLDER_TYPE(T, std::shared_ptr<T>);
	PYBIND11_DECLARE_HOLDER_TYPE(T, T*);
#endif

// tsa::TukeyHannWindow file:TukeyHannWindow.hpp line:68
struct PyCallBack_TukeyHannWindow : public tsa::TukeyHannWindow {
	using tsa::TukeyHannWindow::TukeyHannWindow;

	void operator()(class tsa::SeqView<double> & a0) override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const tsa::TukeyHannWindow *>(this), "__call__");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::overload_caster_t<void> caster;
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
				static pybind11::detail::overload_caster_t<void> caster;
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
				static pybind11::detail::overload_caster_t<void> caster;
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
				static pybind11::detail::overload_caster_t<void> caster;
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
				static pybind11::detail::overload_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return BaseWindow::FillWindow();
	}
};

void bind_TukeyHannWindow(std::function< pybind11::module &(std::string const &namespace_) > &M)
{
	{ // tsa::TukeyHannWindow file:TukeyHannWindow.hpp line:68
		pybind11::class_<tsa::TukeyHannWindow, std::shared_ptr<tsa::TukeyHannWindow>, PyCallBack_TukeyHannWindow, tsa::BaseWindow> cl(M("tsa"), "TukeyHannWindow", "TukeyHann windowing algorithm\n\n     ");
		pybind11::handle cl_type = cl;

		cl.def(pybind11::init<int>(), pybind11::arg("size"));

		cl.def(pybind11::init<int, const class std::basic_string<char> &>(), pybind11::arg("size"), pybind11::arg("p"));

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
#include <Util.hpp>
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
#include <initializer_list>
#include <iterator>
#include <memory>
#include <sstream> // __str__
#include <string>
#include <vector>

#include <pybind11/pybind11.h>

#ifndef BINDER_PYBIND11_TYPE_CASTER
	#define BINDER_PYBIND11_TYPE_CASTER
	PYBIND11_DECLARE_HOLDER_TYPE(T, std::shared_ptr<T>);
	PYBIND11_DECLARE_HOLDER_TYPE(T, T*);
#endif

// tsa::WelchWindow file:WelchWindow.hpp line:69
struct PyCallBack_WelchWindow : public tsa::WelchWindow {
	using tsa::WelchWindow::WelchWindow;

	void operator()(class tsa::SeqView<double> & a0) override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const tsa::WelchWindow *>(this), "__call__");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::overload_caster_t<void> caster;
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
				static pybind11::detail::overload_caster_t<void> caster;
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
				static pybind11::detail::overload_caster_t<void> caster;
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
				static pybind11::detail::overload_caster_t<void> caster;
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
				static pybind11::detail::overload_caster_t<void> caster;
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
		pybind11::handle cl_type = cl;

		cl.def("__init__", [](tsa::WaveletThreshold *self_, unsigned int  const &a0) { new (self_) tsa::WaveletThreshold(a0); }, "doc");
		cl.def("__init__", [](tsa::WaveletThreshold *self_, unsigned int  const &a0, unsigned int  const &a1) { new (self_) tsa::WaveletThreshold(a0, a1); }, "doc");
		cl.def(pybind11::init<unsigned int, unsigned int, double>(), pybind11::arg("N"), pybind11::arg("ncoeff"), pybind11::arg("sigma"));

		cl.def(pybind11::init<const class tsa::WaveletThreshold &>(), pybind11::arg(""));

		pybind11::enum_<tsa::WaveletThreshold::WaveletThresholding>(cl, "WaveletThresholding", "")
			.value("highest", tsa::WaveletThreshold::WaveletThresholding::highest)
			.value("dohonojohnston", tsa::WaveletThreshold::WaveletThresholding::dohonojohnston)
			.value("cuoco", tsa::WaveletThreshold::WaveletThresholding::cuoco)
			.export_values();

		pybind11::enum_<tsa::WaveletThreshold::ThresholdingMode>(cl, "ThresholdingMode", "")
			.value("hard", tsa::WaveletThreshold::ThresholdingMode::hard)
			.value("soft", tsa::WaveletThreshold::ThresholdingMode::soft)
			.export_values();

		cl.def("__call__", [](tsa::WaveletThreshold &o, class tsa::SeqView<double> & a0, enum tsa::WaveletThreshold::WaveletThresholding  const &a1) -> void { return o.operator()(a0, a1); }, "", pybind11::arg("WT"), pybind11::arg("t"));
		cl.def("__call__", (void (tsa::WaveletThreshold::*)(class tsa::SeqView<double> &, enum tsa::WaveletThreshold::WaveletThresholding, enum tsa::WaveletThreshold::ThresholdingMode)) &tsa::WaveletThreshold::operator(), "Brief documentation for the execute method.\n\n Start of the long documentation for execute method.\n\n \n A precondition\n \n\n A postcondition\n \n\n An exception\n\n \n parameter\n\n \n a returned value\n\n Declaration of execute operation\n\nC++: tsa::WaveletThreshold::operator()(class tsa::SeqView<double> &, enum tsa::WaveletThreshold::WaveletThresholding, enum tsa::WaveletThreshold::ThresholdingMode) --> void", pybind11::arg("WT"), pybind11::arg("t"), pybind11::arg("m"));
		cl.def("GetSigma", (double (tsa::WaveletThreshold::*)()) &tsa::WaveletThreshold::GetSigma, "C++: tsa::WaveletThreshold::GetSigma() --> double");
		cl.def("GetLevel", (double (tsa::WaveletThreshold::*)()) &tsa::WaveletThreshold::GetLevel, "C++: tsa::WaveletThreshold::GetLevel() --> double");
		cl.def("GetCm", (double (tsa::WaveletThreshold::*)()) &tsa::WaveletThreshold::GetCm, "C++: tsa::WaveletThreshold::GetCm() --> double");
		cl.def("SetSigma", (void (tsa::WaveletThreshold::*)(double)) &tsa::WaveletThreshold::SetSigma, "C++: tsa::WaveletThreshold::SetSigma(double) --> void", pybind11::arg("sigma"));
		cl.def("assign", (class tsa::WaveletThreshold & (tsa::WaveletThreshold::*)(const class tsa::WaveletThreshold &)) &tsa::WaveletThreshold::operator=, "C++: tsa::WaveletThreshold::operator=(const class tsa::WaveletThreshold &) --> class tsa::WaveletThreshold &", pybind11::return_value_policy::automatic, pybind11::arg(""));
	}
	{ // tsa::WaveletTransform file:WaveletTransform.hpp line:75
		pybind11::class_<tsa::WaveletTransform, std::shared_ptr<tsa::WaveletTransform>> cl(M("tsa"), "WaveletTransform", "Compute the wavelet transform");
		pybind11::handle cl_type = cl;

		cl.def(pybind11::init<unsigned int, enum tsa::WaveletTransform::WaveletType>(), pybind11::arg("N"), pybind11::arg("wt"));

		cl.def(pybind11::init<const class tsa::WaveletTransform &>(), pybind11::arg("from"));

		pybind11::enum_<tsa::WaveletTransform::WaveletType>(cl, "WaveletType", "")
			.value("Daub4", tsa::WaveletTransform::WaveletType::Daub4)
			.value("Daub6", tsa::WaveletTransform::WaveletType::Daub6)
			.value("Daub8", tsa::WaveletTransform::WaveletType::Daub8)
			.value("Daub10", tsa::WaveletTransform::WaveletType::Daub10)
			.value("Daub12", tsa::WaveletTransform::WaveletType::Daub12)
			.value("Daub14", tsa::WaveletTransform::WaveletType::Daub14)
			.value("Daub16", tsa::WaveletTransform::WaveletType::Daub16)
			.value("Daub18", tsa::WaveletTransform::WaveletType::Daub18)
			.value("Daub20", tsa::WaveletTransform::WaveletType::Daub20)
			.value("DaubC4", tsa::WaveletTransform::WaveletType::DaubC4)
			.value("DaubC6", tsa::WaveletTransform::WaveletType::DaubC6)
			.value("DaubC8", tsa::WaveletTransform::WaveletType::DaubC8)
			.value("DaubC10", tsa::WaveletTransform::WaveletType::DaubC10)
			.value("DaubC12", tsa::WaveletTransform::WaveletType::DaubC12)
			.value("DaubC14", tsa::WaveletTransform::WaveletType::DaubC14)
			.value("DaubC16", tsa::WaveletTransform::WaveletType::DaubC16)
			.value("DaubC18", tsa::WaveletTransform::WaveletType::DaubC18)
			.value("DaubC20", tsa::WaveletTransform::WaveletType::DaubC20)
			.value("Haar", tsa::WaveletTransform::WaveletType::Haar)
			.value("HaarC", tsa::WaveletTransform::WaveletType::HaarC)
			.value("Bspline103", tsa::WaveletTransform::WaveletType::Bspline103)
			.value("Bspline105", tsa::WaveletTransform::WaveletType::Bspline105)
			.value("Bspline202", tsa::WaveletTransform::WaveletType::Bspline202)
			.value("Bspline204", tsa::WaveletTransform::WaveletType::Bspline204)
			.value("Bspline206", tsa::WaveletTransform::WaveletType::Bspline206)
			.value("Bspline208", tsa::WaveletTransform::WaveletType::Bspline208)
			.value("Bspline301", tsa::WaveletTransform::WaveletType::Bspline301)
			.value("Bspline303", tsa::WaveletTransform::WaveletType::Bspline303)
			.value("Bspline305", tsa::WaveletTransform::WaveletType::Bspline305)
			.value("Bspline307", tsa::WaveletTransform::WaveletType::Bspline307)
			.value("Bspline309", tsa::WaveletTransform::WaveletType::Bspline309)
			.value("BsplineC103", tsa::WaveletTransform::WaveletType::BsplineC103)
			.value("BsplineC105", tsa::WaveletTransform::WaveletType::BsplineC105)
			.value("BsplineC202", tsa::WaveletTransform::WaveletType::BsplineC202)
			.value("BsplineC204", tsa::WaveletTransform::WaveletType::BsplineC204)
			.value("BsplineC206", tsa::WaveletTransform::WaveletType::BsplineC206)
			.value("BsplineC208", tsa::WaveletTransform::WaveletType::BsplineC208)
			.value("BsplineC301", tsa::WaveletTransform::WaveletType::BsplineC301)
			.value("BsplineC303", tsa::WaveletTransform::WaveletType::BsplineC303)
			.value("BsplineC305", tsa::WaveletTransform::WaveletType::BsplineC305)
			.value("BsplineC307", tsa::WaveletTransform::WaveletType::BsplineC307)
			.value("BsplineC309", tsa::WaveletTransform::WaveletType::BsplineC309)
			.export_values();

		cl.def("assign", (class tsa::WaveletTransform & (tsa::WaveletTransform::*)(const class tsa::WaveletTransform &)) &tsa::WaveletTransform::operator=, "Assignement operator\n\n \n The instance to be assigned from\n\n \n a reference to a new object\n\nC++: tsa::WaveletTransform::operator=(const class tsa::WaveletTransform &) --> class tsa::WaveletTransform &", pybind11::return_value_policy::automatic, pybind11::arg("from"));
		cl.def("Forward", (void (tsa::WaveletTransform::*)(class tsa::SeqView<double> &)) &tsa::WaveletTransform::Forward, "Brief documentation for the execute method.\n\n Start of the long documentation for execute method.\n\n \n A precondition\n \n\n A postcondition\n \n\n An exception\n\n \n parameter\n\n \n a returned value\n\n Declaration of execute operation\n\nC++: tsa::WaveletTransform::Forward(class tsa::SeqView<double> &) --> void", pybind11::arg("In"));
		cl.def("Inverse", (void (tsa::WaveletTransform::*)(class tsa::SeqView<double> &)) &tsa::WaveletTransform::Inverse, "C++: tsa::WaveletTransform::Inverse(class tsa::SeqView<double> &) --> void", pybind11::arg("In"));
		cl.def("WaveletPrint", (void (tsa::WaveletTransform::*)()) &tsa::WaveletTransform::WaveletPrint, "C++: tsa::WaveletTransform::WaveletPrint() --> void");
	}
	{ // tsa::WavReconstruction file:WavReconstruction.hpp line:78
		pybind11::class_<tsa::WavReconstruction, std::shared_ptr<tsa::WavReconstruction>, tsa::AlgoBase> cl(M("tsa"), "WavReconstruction", "A more detailed description of WavReconstruction\n\n Reconstructed the wavelet transformed signal");
		pybind11::handle cl_type = cl;

		cl.def(pybind11::init<unsigned int, enum tsa::WaveletTransform::WaveletType, double>(), pybind11::arg("N"), pybind11::arg("F"), pybind11::arg("Th"));

		cl.def("__call__", (void (tsa::WavReconstruction::*)(class tsa::SeqView<double> &)) &tsa::WavReconstruction::operator(), "C++: tsa::WavReconstruction::operator()(class tsa::SeqView<double> &) --> void", pybind11::arg("InputData"));
	}
	{ // tsa::WDF2Classify file:WDF2Classify.hpp line:85
		pybind11::class_<tsa::WDF2Classify, std::shared_ptr<tsa::WDF2Classify>, tsa::AlgoBase> cl(M("tsa"), "WDF2Classify", "Time domain detection of transients based on wavelet transform");
		pybind11::handle cl_type = cl;

		cl.def("__init__", [](tsa::WDF2Classify *self_, unsigned int  const &a0, unsigned int  const &a1, double  const &a2, double  const &a3, unsigned int  const &a4) { new (self_) tsa::WDF2Classify(a0, a1, a2, a3, a4); }, "doc");
		cl.def(pybind11::init<unsigned int, unsigned int, double, double, unsigned int, enum tsa::WaveletThreshold::WaveletThresholding>(), pybind11::arg("window"), pybind11::arg("overlap"), pybind11::arg("thresh"), pybind11::arg("sigma"), pybind11::arg("ncoeff"), pybind11::arg("WTh"));

		cl.def(pybind11::init<const class tsa::WDF2Classify &>(), pybind11::arg(""));

		cl.def("__call__", (void (tsa::WDF2Classify::*)(class tsa::SeqView<double> &, double)) &tsa::WDF2Classify::operator(), "C++: tsa::WDF2Classify::operator()(class tsa::SeqView<double> &, double) --> void", pybind11::arg("Data"), pybind11::arg("sigma"));
		cl.def("__call__", (int (tsa::WDF2Classify::*)(class tsa::EventFullFeatured &)) &tsa::WDF2Classify::operator(), "C++: tsa::WDF2Classify::operator()(class tsa::EventFullFeatured &) --> void", pybind11::arg("Ev"));
		cl.def("GetEvent", (void (tsa::WDF2Classify::*)(class tsa::EventFullFeatured &)) &tsa::WDF2Classify::GetEvent, "C++: tsa::WDF2Classify::GetEvent(class tsa::EventFullFeatured &) --> void", pybind11::arg("Ev"));
		cl.def("GetDataNeeded", (int (tsa::WDF2Classify::*)()) &tsa::WDF2Classify::GetDataNeeded, "Get the number of data needed in order to be able to \n call GetData successfully. If the returned value is less or \n equal than zero no data are needed.\n\n \n the needed data\n\nC++: tsa::WDF2Classify::GetDataNeeded() --> int");
		cl.def("assign", (class tsa::WDF2Classify & (tsa::WDF2Classify::*)(const class tsa::WDF2Classify &)) &tsa::WDF2Classify::operator=, "C++: tsa::WDF2Classify::operator=(const class tsa::WDF2Classify &) --> class tsa::WDF2Classify &", pybind11::return_value_policy::automatic, pybind11::arg(""));
	}
	{ // tsa::WDF2Reconstruct file:WDF2Reconstruct.hpp line:85
					pybind11::class_<tsa::WDF2Reconstruct, std::shared_ptr<tsa::WDF2Reconstruct>, tsa::AlgoBase> cl(M("tsa"), "WDF2Reconstruct", "Time domain detection of transients based on wavelet transform");
					pybind11::handle cl_type = cl;

					cl.def("__init__", [](tsa::WDF2Reconstruct *self_, unsigned int  const &a0, unsigned int  const &a1, double  const &a2, double  const &a3, unsigned int  const &a4) { new (self_) tsa::WDF2Reconstruct(a0, a1, a2, a3, a4); }, "doc");
					cl.def(pybind11::init<unsigned int, unsigned int, double, double, unsigned int, enum tsa::WaveletThreshold::WaveletThresholding>(), pybind11::arg("window"), pybind11::arg("overlap"), pybind11::arg("thresh"), pybind11::arg("sigma"), pybind11::arg("ncoeff"), pybind11::arg("WTh"));

					cl.def(pybind11::init<const class tsa::WDF2Reconstruct &>(), pybind11::arg(""));

					cl.def("__call__", (void (tsa::WDF2Reconstruct::*)(class tsa::SeqView<double> &, double)) &tsa::WDF2Reconstruct::operator(), "C++: tsa::WDF2Reconstruct::operator()(class tsa::SeqView<double> &, double) --> void", pybind11::arg("Data"), pybind11::arg("sigma"));
					cl.def("__call__", (int (tsa::WDF2Reconstruct::*)(class tsa::EventFullFeatured &)) &tsa::WDF2Reconstruct::operator(), "C++: tsa::WDF2Reconstruct::operator()(class tsa::EventFullFeatured &) --> void", pybind11::arg("Ev"));
					cl.def("GetEvent", (void (tsa::WDF2Reconstruct::*)(class tsa::EventFullFeatured &)) &tsa::WDF2Reconstruct::GetEvent, "C++: tsa::WDF2Reconstruct::GetEvent(class tsa::EventFullFeatured &) --> void", pybind11::arg("Ev"));
					cl.def("GetDataNeeded", (int (tsa::WDF2Reconstruct::*)()) &tsa::WDF2Reconstruct::GetDataNeeded, "Get the number of data needed in order to be able to \n call GetData successfully. If the returned value is less or \n equal than zero no data are needed.\n\n \n the needed data\n\nC++: tsa::WDF2Classify::GetDataNeeded() --> int");
					cl.def("assign", (class tsa::WDF2Reconstruct & (tsa::WDF2Reconstruct::*)(const class tsa::WDF2Reconstruct &)) &tsa::WDF2Reconstruct::operator=, "C++: tsa::WDF2Reconstruct::operator=(const class tsa::WDF2Reconstruct &) --> class tsa::WDF2Reconstruct &", pybind11::return_value_policy::automatic, pybind11::arg(""));
	}
	{ // tsa::WelchWindow file:WelchWindow.hpp line:69
		pybind11::class_<tsa::WelchWindow, std::shared_ptr<tsa::WelchWindow>, PyCallBack_WelchWindow, tsa::BaseWindow> cl(M("tsa"), "WelchWindow", "Welch windowing algorithm\n\n ");
		pybind11::handle cl_type = cl;

		cl.def(pybind11::init<int>(), pybind11::arg("size"));

		cl.def(pybind11::init<int, const class std::basic_string<char> &>(), pybind11::arg("size"), pybind11::arg("p"));

		cl.def("__call__", (void (tsa::WelchWindow::*)(class tsa::SeqView<double> &)) &tsa::WelchWindow::operator(), "Apply the window to a given time view.\n\n \n the time view \n\nC++: tsa::WelchWindow::operator()(class tsa::SeqView<double> &) --> void", pybind11::arg("v1"));
		cl.def("__call__", (void (tsa::WelchWindow::*)(class tsa::SeqView<double> &, class tsa::SeqView<double> &)) &tsa::WelchWindow::operator(), "Apply a window to an input view and write the results on a \n output view.\n\n \n the input view\n \n\n the output view\n\n         \n\nC++: tsa::WelchWindow::operator()(class tsa::SeqView<double> &, class tsa::SeqView<double> &) --> void", pybind11::arg("v1"), pybind11::arg("v2"));
		cl.def("Resize", (void (tsa::WelchWindow::*)(unsigned int)) &tsa::WelchWindow::Resize, "Resize the window dimension.\n\n \n new size for the window\n\nC++: tsa::WelchWindow::Resize(unsigned int) --> void", pybind11::arg("size"));
		cl.def("assign", (class tsa::WelchWindow & (tsa::WelchWindow::*)(const class tsa::WelchWindow &)) &tsa::WelchWindow::operator=, "C++: tsa::WelchWindow::operator=(const class tsa::WelchWindow &) --> class tsa::WelchWindow &", pybind11::return_value_policy::automatic, pybind11::arg(""));
	}
	{ // tsa::Util file:Util.hpp line:64
		pybind11::class_<tsa::Util, std::shared_ptr<tsa::Util>, tsa::AlgoBase> cl(M("tsa"), "Util", "");
		pybind11::handle cl_type = cl;

		cl.def(pybind11::init<>());
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
#include <initializer_list>
#include <iterator>
#include <memory>
#include <sstream> // __str__
#include <string>
#include <vector>

#include <pybind11/pybind11.h>

#ifndef BINDER_PYBIND11_TYPE_CASTER
	#define BINDER_PYBIND11_TYPE_CASTER
	PYBIND11_DECLARE_HOLDER_TYPE(T, std::shared_ptr<T>);
	PYBIND11_DECLARE_HOLDER_TYPE(T, T*);
#endif

// tsa::ChannelDescriptor file:FrameIStream.hpp line:101
struct PyCallBack_ChannelDescriptor : public tsa::ChannelDescriptor {
	using tsa::ChannelDescriptor::ChannelDescriptor;

	void AddData() override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const tsa::ChannelDescriptor *>(this), "AddData");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>();
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::overload_caster_t<void> caster;
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
				static pybind11::detail::overload_caster_t<double> caster;
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
				static pybind11::detail::overload_caster_t<double> caster;
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
				static pybind11::detail::overload_caster_t<void> caster;
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
				static pybind11::detail::overload_caster_t<void> caster;
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
				static pybind11::detail::overload_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return ChannelDescriptor::WriteView(a0, a1);
	}
};

// tsa::ADC_Channel file:FrameIStream.hpp line:230
struct PyCallBack_ADC_Channel : public tsa::ADC_Channel {
	using tsa::ADC_Channel::ADC_Channel;

	void AddData() override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const tsa::ADC_Channel *>(this), "AddData");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>();
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::overload_caster_t<void> caster;
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
				static pybind11::detail::overload_caster_t<double> caster;
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
				static pybind11::detail::overload_caster_t<double> caster;
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
				static pybind11::detail::overload_caster_t<void> caster;
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
				static pybind11::detail::overload_caster_t<void> caster;
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
				static pybind11::detail::overload_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return ChannelDescriptor::WriteView(a0, a1);
	}
};

// tsa::PROC_Channel file:FrameIStream.hpp line:285
struct PyCallBack_PROC_Channel : public tsa::PROC_Channel {
	using tsa::PROC_Channel::PROC_Channel;

	void AddData() override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const tsa::PROC_Channel *>(this), "AddData");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>();
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::overload_caster_t<void> caster;
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
				static pybind11::detail::overload_caster_t<double> caster;
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
				static pybind11::detail::overload_caster_t<void> caster;
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
				static pybind11::detail::overload_caster_t<double> caster;
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
				static pybind11::detail::overload_caster_t<void> caster;
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
				static pybind11::detail::overload_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return ChannelDescriptor::WriteView(a0, a1);
	}
};

// tsa::SIM_Channel file:FrameIStream.hpp line:344
struct PyCallBack_SIM_Channel : public tsa::SIM_Channel {
	using tsa::SIM_Channel::SIM_Channel;

	void AddData() override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const tsa::SIM_Channel *>(this), "AddData");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>();
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::overload_caster_t<void> caster;
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
				static pybind11::detail::overload_caster_t<double> caster;
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
				static pybind11::detail::overload_caster_t<double> caster;
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
				static pybind11::detail::overload_caster_t<void> caster;
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
				static pybind11::detail::overload_caster_t<void> caster;
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
				static pybind11::detail::overload_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return ChannelDescriptor::WriteView(a0, a1);
	}
};

// tsa::SER_Channel file:FrameIStream.hpp line:399
struct PyCallBack_SER_Channel : public tsa::SER_Channel {
	using tsa::SER_Channel::SER_Channel;

	void AddData() override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const tsa::SER_Channel *>(this), "AddData");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>();
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::overload_caster_t<void> caster;
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
				static pybind11::detail::overload_caster_t<double> caster;
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
				static pybind11::detail::overload_caster_t<double> caster;
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
				static pybind11::detail::overload_caster_t<void> caster;
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
				static pybind11::detail::overload_caster_t<void> caster;
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
				static pybind11::detail::overload_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return ChannelDescriptor::WriteView(a0, a1);
	}
};

// tsa::FRAMEH_Channel file:FrameIStream.hpp line:456
struct PyCallBack_FRAMEH_Channel : public tsa::FRAMEH_Channel {
	using tsa::FRAMEH_Channel::FRAMEH_Channel;

	void AddData() override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const tsa::FRAMEH_Channel *>(this), "AddData");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>();
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::overload_caster_t<void> caster;
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
				static pybind11::detail::overload_caster_t<double> caster;
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
				static pybind11::detail::overload_caster_t<double> caster;
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
				static pybind11::detail::overload_caster_t<void> caster;
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
				static pybind11::detail::overload_caster_t<void> caster;
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
				static pybind11::detail::overload_caster_t<void> caster;
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
		pybind11::handle cl_type = cl;

		cl.def(pybind11::init<double, double, enum tsa::DataException::exception_type>(), pybind11::arg("ts"), pybind11::arg("te"), pybind11::arg("e"));

		pybind11::enum_<tsa::DataException::exception_type>(cl, "exception_type", "Type of problem.\n\n         ")
			.value("data_loss", tsa::DataException::exception_type::data_loss)
			.export_values();

		cl.def_readwrite("Exception", &tsa::DataException::Exception);
		cl.def_readwrite("StartTime", &tsa::DataException::StartTime);
		cl.def_readwrite("EndTime", &tsa::DataException::EndTime);
	}
	{ // tsa::ChannelDescriptor file:FrameIStream.hpp line:101
		pybind11::class_<tsa::ChannelDescriptor, std::shared_ptr<tsa::ChannelDescriptor>, PyCallBack_ChannelDescriptor, tsa::AlgoBase> cl(M("tsa"), "ChannelDescriptor", "A base class for the descriptor of a data channel.\n\n     ");
		pybind11::handle cl_type = cl;

		cl.def(pybind11::init<unsigned int>(), pybind11::arg("id"));

		cl.def("AddData", (void (tsa::ChannelDescriptor::*)()) &tsa::ChannelDescriptor::AddData, "This function must be called when there are not enough data \n to fill the output view. In this base class does nothing.\n\n         \n\nC++: tsa::ChannelDescriptor::AddData() --> void");
		cl.def("GetLength", (double (tsa::ChannelDescriptor::*)()) &tsa::ChannelDescriptor::GetLength, "Get the maximul time length of data that can be currently filled\n without calling AddData.\n\n \n the time length of the data available in seconds\n\nC++: tsa::ChannelDescriptor::GetLength() --> double");
		cl.def("GetRate", (double (tsa::ChannelDescriptor::*)()) &tsa::ChannelDescriptor::GetRate, "Get the channel time rate\n\n \n \n\n the channel time rate\n\nC++: tsa::ChannelDescriptor::GetRate() --> double");
		cl.def("WriteView", (void (tsa::ChannelDescriptor::*)(class tsa::SeqView<double> &)) &tsa::ChannelDescriptor::WriteView, "A function to write the available data on an output view. Be careful\n that if there are not enough data available we get a data loss exception.\n\n \n output view where the available data are written\n\nC++: tsa::ChannelDescriptor::WriteView(class tsa::SeqView<double> &) --> void", pybind11::arg("v"));
		cl.def("FillView", (void (tsa::ChannelDescriptor::*)(class tsa::SeqView<double> &, double, double)) &tsa::ChannelDescriptor::FillView, "C++: tsa::ChannelDescriptor::FillView(class tsa::SeqView<double> &, double, double) --> void", pybind11::arg("v"), pybind11::arg("tstart"), pybind11::arg("tend"));
		cl.def("WriteView", (void (tsa::ChannelDescriptor::*)(class tsa::SeqView<double> &, class tsa::SeqView<double> &)) &tsa::ChannelDescriptor::WriteView, "A function to write the available data on an output view. Be careful\n that if there are not enough data available we get a data loss exception.\n At the same time a second view is filled with ones which correspond to \n avaliable data, or zeros which correspond to unavailable data.\n\n \n output view where the available data are written\n \n\n output view where the available data flags are written\n\nC++: tsa::ChannelDescriptor::WriteView(class tsa::SeqView<double> &, class tsa::SeqView<double> &) --> void", pybind11::arg("v"), pybind11::arg("validation"));
		cl.def("assign", (class tsa::ChannelDescriptor & (tsa::ChannelDescriptor::*)(const class tsa::ChannelDescriptor &)) &tsa::ChannelDescriptor::operator=, "C++: tsa::ChannelDescriptor::operator=(const class tsa::ChannelDescriptor &) --> class tsa::ChannelDescriptor &", pybind11::return_value_policy::automatic, pybind11::arg(""));
	}
	{ // tsa::ADC_Channel file:FrameIStream.hpp line:230
		pybind11::class_<tsa::ADC_Channel, std::shared_ptr<tsa::ADC_Channel>, PyCallBack_ADC_Channel, tsa::ChannelDescriptor> cl(M("tsa"), "ADC_Channel", "A descriptor for an ADC channel\n\n     ");
		pybind11::handle cl_type = cl;

		cl.def(pybind11::init<class tsa::FrameIStream *, struct FrAdcData *, unsigned int>(), pybind11::arg("FIS"), pybind11::arg("adc"), pybind11::arg("id"));

		cl.def("AddData", (void (tsa::ADC_Channel::*)()) &tsa::ADC_Channel::AddData, "This function must be called when there are not enough data \n to fill the output view. It reads a chunk of data from the \n current frame\n\n         \n\nC++: tsa::ADC_Channel::AddData() --> void");
		cl.def("GetLength", (double (tsa::ADC_Channel::*)()) &tsa::ADC_Channel::GetLength, "Get the maximul time length of data that can be currently filled\n without calling AddData.\n\n \n the time length of the data available in seconds\n\nC++: tsa::ADC_Channel::GetLength() --> double");
		cl.def_static("Create", (class tsa::ADC_Channel * (*)(class tsa::FrameIStream *, char *, unsigned int)) &tsa::ADC_Channel::Create, "Create, if possible, an instance of the class\n\n \n pointer to the FrameIStream class instance\n \n\n name of the channel\n \n\n index of the channel\n\n \n pointer to the created class instance or null\n\nC++: tsa::ADC_Channel::Create(class tsa::FrameIStream *, char *, unsigned int) --> class tsa::ADC_Channel *", pybind11::return_value_policy::automatic, pybind11::arg("FIS"), pybind11::arg("name"), pybind11::arg("id"));
		cl.def("assign", (class tsa::ADC_Channel & (tsa::ADC_Channel::*)(const class tsa::ADC_Channel &)) &tsa::ADC_Channel::operator=, "C++: tsa::ADC_Channel::operator=(const class tsa::ADC_Channel &) --> class tsa::ADC_Channel &", pybind11::return_value_policy::automatic, pybind11::arg(""));
	}
	{ // tsa::PROC_Channel file:FrameIStream.hpp line:285
		pybind11::class_<tsa::PROC_Channel, std::shared_ptr<tsa::PROC_Channel>, PyCallBack_PROC_Channel, tsa::ChannelDescriptor> cl(M("tsa"), "PROC_Channel", "A descriptor for a proc channel\n\n     ");
		pybind11::handle cl_type = cl;

		cl.def(pybind11::init<class tsa::FrameIStream *, struct FrProcData *, unsigned int>(), pybind11::arg("FIS"), pybind11::arg("proc"), pybind11::arg("id"));

		cl.def("AddData", (void (tsa::PROC_Channel::*)()) &tsa::PROC_Channel::AddData, "This function must be called when there are not enough data \n to fill the output view. It reads a chunk of data from the next\n FrProcData structure.\n\n         \n\nC++: tsa::PROC_Channel::AddData() --> void");
		cl.def("GetLength", (double (tsa::PROC_Channel::*)()) &tsa::PROC_Channel::GetLength, "Get the maximul time length of data that can be currently filled\n without calling AddData.\n\n \n the time length of the data available in seconds\n\nC++: tsa::PROC_Channel::GetLength() --> double");
		cl.def_static("Create", (class tsa::PROC_Channel * (*)(class tsa::FrameIStream *, char *, unsigned int)) &tsa::PROC_Channel::Create, "Create, if possible, an instance of the class\n\n \n pointer to the FrameIStream class instance\n \n\n name of the channel\n \n\n index of the channel\n\n \n pointer to the created class instance or null\n\nC++: tsa::PROC_Channel::Create(class tsa::FrameIStream *, char *, unsigned int) --> class tsa::PROC_Channel *", pybind11::return_value_policy::automatic, pybind11::arg("FIS"), pybind11::arg("name"), pybind11::arg("id"));
		cl.def("FillView", (void (tsa::PROC_Channel::*)(class tsa::SeqView<double> &, double, double)) &tsa::PROC_Channel::FillView, "C++: tsa::PROC_Channel::FillView(class tsa::SeqView<double> &, double, double) --> void", pybind11::arg("v"), pybind11::arg("tstart"), pybind11::arg("tend"));
		cl.def("assign", (class tsa::PROC_Channel & (tsa::PROC_Channel::*)(const class tsa::PROC_Channel &)) &tsa::PROC_Channel::operator=, "C++: tsa::PROC_Channel::operator=(const class tsa::PROC_Channel &) --> class tsa::PROC_Channel &", pybind11::return_value_policy::automatic, pybind11::arg(""));
	}
	{ // tsa::SIM_Channel file:FrameIStream.hpp line:344
		pybind11::class_<tsa::SIM_Channel, std::shared_ptr<tsa::SIM_Channel>, PyCallBack_SIM_Channel, tsa::ChannelDescriptor> cl(M("tsa"), "SIM_Channel", "A descriptor for a SIM channel\n\n     ");
		pybind11::handle cl_type = cl;

		cl.def(pybind11::init<class tsa::FrameIStream *, struct FrSimData *, unsigned int>(), pybind11::arg("FIS"), pybind11::arg("sim"), pybind11::arg("id"));

		cl.def("AddData", (void (tsa::SIM_Channel::*)()) &tsa::SIM_Channel::AddData, "This function must be called when there are not enough data \n to fill the output view. It reads a chunk of data from the next\n FrSimData structure.\n\n         \n\nC++: tsa::SIM_Channel::AddData() --> void");
		cl.def("GetLength", (double (tsa::SIM_Channel::*)()) &tsa::SIM_Channel::GetLength, "Get the maximul time length of data that can be currently filled\n without calling AddData.\n\n \n the time length of the data available in seconds\n\nC++: tsa::SIM_Channel::GetLength() --> double");
		cl.def_static("Create", (class tsa::SIM_Channel * (*)(class tsa::FrameIStream *, char *, unsigned int)) &tsa::SIM_Channel::Create, "Create, if possible, an instance of the class\n\n \n pointer to the FrameIStream class instance\n \n\n name of the channel\n \n\n index of the channel\n\n \n pointer to the created class instance or null\n\nC++: tsa::SIM_Channel::Create(class tsa::FrameIStream *, char *, unsigned int) --> class tsa::SIM_Channel *", pybind11::return_value_policy::automatic, pybind11::arg("FIS"), pybind11::arg("name"), pybind11::arg("id"));
		cl.def("assign", (class tsa::SIM_Channel & (tsa::SIM_Channel::*)(const class tsa::SIM_Channel &)) &tsa::SIM_Channel::operator=, "C++: tsa::SIM_Channel::operator=(const class tsa::SIM_Channel &) --> class tsa::SIM_Channel &", pybind11::return_value_policy::automatic, pybind11::arg(""));
	}
	{ // tsa::SER_Channel file:FrameIStream.hpp line:399
		pybind11::class_<tsa::SER_Channel, std::shared_ptr<tsa::SER_Channel>, PyCallBack_SER_Channel, tsa::ChannelDescriptor> cl(M("tsa"), "SER_Channel", "A descriptor for a SER channel\n\n     ");
		pybind11::handle cl_type = cl;

		cl.def(pybind11::init<class tsa::FrameIStream *, char *, char *, unsigned int>(), pybind11::arg("FIS"), pybind11::arg("smsName"), pybind11::arg("smsParam"), pybind11::arg("id"));

		cl.def("AddData", (void (tsa::SER_Channel::*)()) &tsa::SER_Channel::AddData, "This function must be called when there are not enough data \n to fill the output view. It reads a chunk of data from the next\n serial data structure.\n\n         \n\nC++: tsa::SER_Channel::AddData() --> void");
		cl.def("GetLength", (double (tsa::SER_Channel::*)()) &tsa::SER_Channel::GetLength, "Get the maximul time length of data that can be currently filled\n without calling AddData.\n\n \n the time length of the data available in seconds\n\nC++: tsa::SER_Channel::GetLength() --> double");
		cl.def_static("Create", (class tsa::SER_Channel * (*)(class tsa::FrameIStream *, char *, unsigned int)) &tsa::SER_Channel::Create, "Create, if possible, an instance of the class\n\n \n pointer to the FrameIStream class instance\n \n\n name of the channel\n \n\n index of the channel\n\n \n pointer to the created class instance or null\n\nC++: tsa::SER_Channel::Create(class tsa::FrameIStream *, char *, unsigned int) --> class tsa::SER_Channel *", pybind11::return_value_policy::automatic, pybind11::arg("FIS"), pybind11::arg("name"), pybind11::arg("id"));
		cl.def("assign", (class tsa::SER_Channel & (tsa::SER_Channel::*)(const class tsa::SER_Channel &)) &tsa::SER_Channel::operator=, "C++: tsa::SER_Channel::operator=(const class tsa::SER_Channel &) --> class tsa::SER_Channel &", pybind11::return_value_policy::automatic, pybind11::arg(""));
	}
	{ // tsa::FRAMEH_Channel file:FrameIStream.hpp line:456
		pybind11::class_<tsa::FRAMEH_Channel, std::shared_ptr<tsa::FRAMEH_Channel>, PyCallBack_FRAMEH_Channel, tsa::ChannelDescriptor> cl(M("tsa"), "FRAMEH_Channel", "Descriptor for a FrameH field channel.\n\n     ");
		pybind11::handle cl_type = cl;

		cl.def(pybind11::init<class tsa::FrameIStream *, enum tsa::FRAMEH_Channel::field_type, unsigned int>(), pybind11::arg("FIS"), pybind11::arg("ft"), pybind11::arg("id"));

		pybind11::enum_<tsa::FRAMEH_Channel::field_type>(cl, "field_type", "Field type in the frame to dump on channel\n\n         ")
			.value("field_run", tsa::FRAMEH_Channel::field_type::field_run)
			.value("field_frame", tsa::FRAMEH_Channel::field_type::field_frame)
			.value("field_dataQuality", tsa::FRAMEH_Channel::field_type::field_dataQuality)
			.value("field_GTimeS", tsa::FRAMEH_Channel::field_type::field_GTimeS)
			.value("field_GTimeN", tsa::FRAMEH_Channel::field_type::field_GTimeN)
			.value("field_ULeapS", tsa::FRAMEH_Channel::field_type::field_ULeapS)
			.value("field_dt", tsa::FRAMEH_Channel::field_type::field_dt)
			.value("field_time", tsa::FRAMEH_Channel::field_type::field_time)
			.export_values();

		cl.def("AddData", (void (tsa::FRAMEH_Channel::*)()) &tsa::FRAMEH_Channel::AddData, "This function must be called when there are not enough data \n to fill the output view. It reads a chunk of data from the \n current frame.\n\n         \n\nC++: tsa::FRAMEH_Channel::AddData() --> void");
		cl.def("GetLength", (double (tsa::FRAMEH_Channel::*)()) &tsa::FRAMEH_Channel::GetLength, "Get the maximul time length of data that can be currently filled\n without calling AddData.\n\n \n the time length of the data available in seconds\n\nC++: tsa::FRAMEH_Channel::GetLength() --> double");
		cl.def_static("Create", (class tsa::FRAMEH_Channel * (*)(class tsa::FrameIStream *, char *, unsigned int)) &tsa::FRAMEH_Channel::Create, "Create, if possible, an instance of the class\n\n \n pointer to the FrameIStream class instance\n \n\n name of the channel\n \n\n index of the channel\n\n \n pointer to the created class instance or null\n\nC++: tsa::FRAMEH_Channel::Create(class tsa::FrameIStream *, char *, unsigned int) --> class tsa::FRAMEH_Channel *", pybind11::return_value_policy::automatic, pybind11::arg("FIS"), pybind11::arg("field_name"), pybind11::arg("id"));
		cl.def("assign", (class tsa::FRAMEH_Channel & (tsa::FRAMEH_Channel::*)(const class tsa::FRAMEH_Channel &)) &tsa::FRAMEH_Channel::operator=, "C++: tsa::FRAMEH_Channel::operator=(const class tsa::FRAMEH_Channel &) --> class tsa::FRAMEH_Channel &", pybind11::return_value_policy::automatic, pybind11::arg(""));
	}
	{ // tsa::FrameIStream file:FrameIStream.hpp line:536
		pybind11::class_<tsa::FrameIStream, std::shared_ptr<tsa::FrameIStream>, tsa::AlgoBase> cl(M("tsa"), "FrameIStream", "A source of data taken from a Frame file\n\n This class can be used to read data from a frame file. \n A set of channels can be specified, which are returned together.\n\n \n\n Ser data:\n\n Channel:Parameter:Frequency:Default");
		pybind11::handle cl_type = cl;

		cl.def(pybind11::init<const class std::basic_string<char> &, const double &>(), pybind11::arg("fileName"), pybind11::arg("StartTime"));

		cl.def(pybind11::init<const class std::basic_string<char> &, const double &, const double &, const class std::vector<class std::basic_string<char>, class std::allocator<class std::basic_string<char> > > &>(), pybind11::arg("fileName"), pybind11::arg("StartTime"), pybind11::arg("TimeLength"), pybind11::arg("channelNames"));

		cl.def(pybind11::init<const class tsa::FrameIStream &>(), pybind11::arg(""));

		cl.def("Init", (void (tsa::FrameIStream::*)()) &tsa::FrameIStream::Init, "C++: tsa::FrameIStream::Init() --> void");
		cl.def("FillView", (void (tsa::FrameIStream::*)(class tsa::SeqView<double> &, double, double)) &tsa::FrameIStream::FillView, "C++: tsa::FrameIStream::FillView(class tsa::SeqView<double> &, double, double) --> void", pybind11::arg("rSeqView"), pybind11::arg("tstart"), pybind11::arg("tend"));
		cl.def("GetStartTime", (double (tsa::FrameIStream::*)() const) &tsa::FrameIStream::GetStartTime, "Get the actual start time, which is the start time\n of the next data chunk that will be read.\n\n \n the actual start time\n\nC++: tsa::FrameIStream::GetStartTime() const --> double");
		cl.def("GetEndTime", (double (tsa::FrameIStream::*)() const) &tsa::FrameIStream::GetEndTime, "Get the actual end time, which is the end time\n of the next data chunk that will be read.\n\n \n the actual end time\n\nC++: tsa::FrameIStream::GetEndTime() const --> double");
		cl.def("GetSampling", (double (tsa::FrameIStream::*)(unsigned int) const) &tsa::FrameIStream::GetSampling, "Get the sampling time of a channel\n\n \n the channel's name\n\n \n the channel's sampling time\n\nC++: tsa::FrameIStream::GetSampling(unsigned int) const --> double", pybind11::arg("cn"));
		cl.def("GetTimeLength", (double (tsa::FrameIStream::*)()) &tsa::FrameIStream::GetTimeLength, "Get the time duration of the next data chunk that will be \n read.\n\n \n the actual time duration.\n\nC++: tsa::FrameIStream::GetTimeLength() --> double");
		cl.def("GetFrame", (struct FrameH * (tsa::FrameIStream::*)()) &tsa::FrameIStream::GetFrame, "Get a pointer to the current FrameH structure.\n\n \n \n\n a pointer to the current FrameH\n\nC++: tsa::FrameIStream::GetFrame() --> struct FrameH *", pybind11::return_value_policy::automatic);
		cl.def("GetFrameFile", (struct FrFile * (tsa::FrameIStream::*)()) &tsa::FrameIStream::GetFrameFile, "C++: tsa::FrameIStream::GetFrameFile() --> struct FrFile *", pybind11::return_value_policy::automatic);
		cl.def("GetDataLossFlag", (bool (tsa::FrameIStream::*)()) &tsa::FrameIStream::GetDataLossFlag, "Get the value of the data loss flag. It is\n true if a data loss event is occurred.\n\n \n the data loss flag value\n\nC++: tsa::FrameIStream::GetDataLossFlag() --> bool");
		cl.def("SetTimeLength", (void (tsa::FrameIStream::*)(double)) &tsa::FrameIStream::SetTimeLength, "Set the length of the data buffer that will be returned from now on\n \n\n the new length\n\nC++: tsa::FrameIStream::SetTimeLength(double) --> void", pybind11::arg("length"));
		cl.def("ResetValidationView", (void (tsa::FrameIStream::*)()) &tsa::FrameIStream::ResetValidationView, "Set to zero the validation view. No validation data are\n written.\n\nC++: tsa::FrameIStream::ResetValidationView() --> void");
		cl.def("SetDataLossFlag", (void (tsa::FrameIStream::*)(bool)) &tsa::FrameIStream::SetDataLossFlag, "Set the value of the data loss flag.\n\n \n new value of the data loss flag\n\nC++: tsa::FrameIStream::SetDataLossFlag(bool) --> void", pybind11::arg("status"));
		cl.def("assign", (class tsa::FrameIStream & (tsa::FrameIStream::*)(const class tsa::FrameIStream &)) &tsa::FrameIStream::operator=, "C++: tsa::FrameIStream::operator=(const class tsa::FrameIStream &) --> class tsa::FrameIStream &", pybind11::return_value_policy::automatic, pybind11::arg(""));
	}
}


// File: FrameIChannel.cpp
#include <FrameIChannel.hpp>
#include <SeqView.hpp>
#include <boost/numeric/ublas/functional.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/storage.hpp>
#include <initializer_list>
#include <iterator>
#include <memory>
#include <sstream> // __str__
#include <string>

#include <pybind11/pybind11.h>

#ifndef BINDER_PYBIND11_TYPE_CASTER
	#define BINDER_PYBIND11_TYPE_CASTER
	PYBIND11_DECLARE_HOLDER_TYPE(T, std::shared_ptr<T>);
	PYBIND11_DECLARE_HOLDER_TYPE(T, T*);
#endif

void bind_FrameIChannel(std::function< pybind11::module &(std::string const &namespace_) > &M)
{
	{ // tsa::FrameIChannel file:FrameIChannel.hpp line:82
		pybind11::class_<tsa::FrameIChannel, std::shared_ptr<tsa::FrameIChannel>, tsa::AlgoBase> cl(M("tsa"), "FrameIChannel", "A source of data taken from a Frame file\n\n This class can be used to read data from a frame file, in a single channel. ");
		pybind11::handle cl_type = cl;

		cl.def("__init__", [](tsa::FrameIChannel *self_, const class std::basic_string<char> & a0, const class std::basic_string<char> & a1) { new (self_) tsa::FrameIChannel(a0, a1); }, "doc");
		cl.def("__init__", [](tsa::FrameIChannel *self_, const class std::basic_string<char> & a0, const class std::basic_string<char> & a1, double  const &a2) { new (self_) tsa::FrameIChannel(a0, a1, a2); }, "doc");
		cl.def(pybind11::init<const class std::basic_string<char> &, const class std::basic_string<char> &, double, double>(), pybind11::arg("fileName"), pybind11::arg("channelName"), pybind11::arg("dLength"), pybind11::arg("tStart"));
		cl.def(pybind11::init<const class tsa::FrameIChannel &>(), pybind11::arg(""));

		cl.def("NextSlice", (double (tsa::FrameIChannel::*)()) &tsa::FrameIChannel::NextSlice, "C++: tsa::FrameIChannel::NextSlice() --> double");
		cl.def("GetData", (bool (tsa::FrameIChannel::*)(class tsa::SeqView<double> &, double, double)) &tsa::FrameIChannel::GetData, "Get a specified slice of data. After this call, start time will be\n set to tStart+dLength and data length to dLength\n\n \n the view to fill with data\n \n\n start time of the data returned \n \n\n length of data returned by \n\nC++: tsa::FrameIChannel::GetData(class tsa::SeqView<double> &, double, double) --> bool", pybind11::arg("rSeqView"), pybind11::arg("tStart"), pybind11::arg("dLength"));
		cl.def("GetData", (bool (tsa::FrameIChannel::*)(class tsa::SeqView<double> &)) &tsa::FrameIChannel::GetData, "Get a slice of data the current data length, starting \n from the current start time.\n\n \n the view to fill with data\n\nC++: tsa::FrameIChannel::GetData(class tsa::SeqView<double> &) --> bool", pybind11::arg("rSeqView"));
		cl.def("SetStartTime", (void (tsa::FrameIChannel::*)(double)) &tsa::FrameIChannel::SetStartTime, "C++: tsa::FrameIChannel::SetStartTime(double) --> void", pybind11::arg("tStart"));
		cl.def("SetDataLength", (void (tsa::FrameIChannel::*)(double)) &tsa::FrameIChannel::SetDataLength, "C++: tsa::FrameIChannel::SetDataLength(double) --> void", pybind11::arg("dLength"));
		cl.def("SetAutoIncrement", (void (tsa::FrameIChannel::*)(bool)) &tsa::FrameIChannel::SetAutoIncrement, "C++: tsa::FrameIChannel::SetAutoIncrement(bool) --> void", pybind11::arg("status"));
		cl.def("assign", (class tsa::FrameIChannel & (tsa::FrameIChannel::*)(const class tsa::FrameIChannel &)) &tsa::FrameIChannel::operator=, "C++: tsa::FrameIChannel::operator=(const class tsa::FrameIChannel &) --> class tsa::FrameIChannel &", pybind11::return_value_policy::automatic, pybind11::arg(""));
	}
}


#include <map>
#include <memory>
#include <stdexcept>
#include <functional>

#include <pybind11/pybind11.h>

typedef std::function< pybind11::module & (std::string const &) > ModuleGetter;

void bind_eternity_persist(std::function< pybind11::module &(std::string const &namespace_) > &M);
void bind_eternity_persist_xml(std::function< pybind11::module &(std::string const &namespace_) > &M);
void bind_tsaUtilityFunctions(std::function< pybind11::module &(std::string const &namespace_) > &M);
void bind_LatticeView(std::function< pybind11::module &(std::string const &namespace_) > &M);
void bind_FrameL(std::function< pybind11::module &(std::string const &namespace_) > &M);
void bind_SeqView(std::function< pybind11::module &(std::string const &namespace_) > &M);
void bind_Parcor2AR(std::function< pybind11::module &(std::string const &namespace_) > &M);
void bind_BaseFFT(std::function< pybind11::module &(std::string const &namespace_) > &M);
void bind_BLInterpolation(std::function< pybind11::module &(std::string const &namespace_) > &M);
void bind_EventDescription(std::function< pybind11::module &(std::string const &namespace_) > &M);
void bind_LeastSquaresLattice(std::function< pybind11::module &(std::string const &namespace_) > &M);
void bind_TukeyHannWindow(std::function< pybind11::module &(std::string const &namespace_) > &M);
void bind_WaveletThreshold(std::function< pybind11::module &(std::string const &namespace_) > &M);
void bind_FrameIStream(std::function< pybind11::module &(std::string const &namespace_) > &M);
void bind_FrameIChannel(std::function< pybind11::module &(std::string const &namespace_) > &M);


PYBIND11_PLUGIN(pytsa) {
	std::map <std::string, std::shared_ptr<pybind11::module> > modules;
	ModuleGetter M = [&](std::string const &namespace_) -> pybind11::module & {
		auto it = modules.find(namespace_);
		if( it == modules.end() ) throw std::runtime_error("Attempt to access pybind11::module for namespace " + namespace_ + " before it was created!!!");
		return * it->second;
	};

	modules[""] = std::make_shared<pybind11::module>("pytsa", "pytsa module");

	std::vector< std::pair<std::string, std::string> > sub_modules {
		{"", "eternity"},
		{"", "tsa"},
	};
	for(auto &p : sub_modules ) modules[p.first.size() ? p.first+"::"+p.second : p.second] = std::make_shared<pybind11::module>( modules[p.first]->def_submodule(p.second.c_str(), ("Bindings for " + p.first + "::" + p.second + " namespace").c_str() ) );

	bind_eternity_persist(M);
	bind_eternity_persist_xml(M);
	bind_tsaUtilityFunctions(M);
	bind_LatticeView(M);
	bind_FrameL(M);
	bind_SeqView(M);
	bind_Parcor2AR(M);
	bind_BaseFFT(M);
	bind_BLInterpolation(M);
	bind_EventDescription(M);
	bind_LeastSquaresLattice(M);
	bind_TukeyHannWindow(M);
	bind_WaveletThreshold(M);
	bind_FrameIStream(M);
	bind_FrameIChannel(M);

	return modules[""]->ptr();
}

// Source list file: ./python-wrapper/pytsa.sources
// pytsa.cpp
// eternity/persist.cpp
// eternity/persist_xml.cpp
// tsaUtilityFunctions.cpp
// LatticeView.cpp
// FrameL.cpp
// SeqView.cpp
// Parcor2AR.cpp
// BaseFFT.cpp
// BLInterpolation.cpp
// EventDescription.cpp
// LeastSquaresLattice.cpp
// TukeyHannWindow.cpp
// WaveletThreshold.cpp
// FrameIStream.cpp
// FrameIChannel.cpp

// Modules list file: ./python-wrapper/pytsa.modules
// eternity tsa
