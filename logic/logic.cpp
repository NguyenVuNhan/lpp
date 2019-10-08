#include <boost/python.hpp>
#include <boost/python/make_constructor.hpp>

#include "src/proposition/tree.h"
#include "src/proposition/predicate.h"
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
    class_<Tree>("Tree", init<std::string>())
        .def("exportProof", &Tree::exportProof, args("title", "filenname"))
        .def("exportGraph", &Tree::exportGraph, args("title", "filenname"))
        .def("isTautology", &Tree::isTautology)
        .def("getListVariable", &Tree::getListVariable)
        .def("getProposition", &Tree::getProposition);
    class_<Predicate>("Predicate", init<std::string>())
        .def("exportProof", &Tree::exportProof, args("title", "filenname"))
        .def("exportGraph", &Tree::exportGraph, args("title", "filenname"))
        .def("isTautology", &Tree::isTautology)
        .def("getListVariable", &Tree::getListVariable)
        .def("getProposition", &Tree::getProposition);
}