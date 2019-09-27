#include <boost/python.hpp>
#include <boost/python/make_constructor.hpp>

#include "src/logic_manager.h"
#include <boost/foreach.hpp>
#ifndef foreach
    #define foreach BOOST_FOREACH
#endif

using namespace boost::python;

template<typename T>
struct list_to_list
{
    static PyObject* convert(const std::list<T>& src)
    {
        boost::python::list result;
        foreach (const T& val, src)
        {
            result.append(val);
        }

        return incref(result.ptr());
    }
};

BOOST_PYTHON_MODULE(logic)
{
    to_python_converter<std::list<string>, list_to_list<string>>();
 
    Py_Initialize();
    class_<logic>("logic", init<std::string>())
        .def_readonly("proposition", &logic::proposition)
        .def_readonly("variables", &logic::variables)
        .def_readonly("truthTable", &logic::truthTable)
        .def_readonly("simplifiedTable", &logic::simplifiedTable)
        .def_readonly("dnf", &logic::dnf)
        .def_readonly("nandify", &logic::nandify)
        .def_readonly("cnf", &logic::cnf);

    // class_<logic>("logic", init<string>())
    //     .def("getProposition", &logic::getProposition)
    //     .def("getVariables", &logic::getVariables)
    //     .def("getTruthTable", &logic::getTruthTable)
    //     .def("getSimplifiedTable", &logic::getSimplifiedTable)
    //     .def("getDNF", &logic::getDNF)
    //     .def("getNandify", &logic::getNandify)
    //     .def("getCNF", &logic::getCNF);
}