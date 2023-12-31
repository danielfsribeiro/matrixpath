#include "../config.h"
#include PYBIND11
#include PYBIND11_STL

#include "../include/matrixpath.h"

#include <string>

namespace py = pybind11;

PYBIND11_MODULE(matrixpath_py, m) 
{
    //matrixpath_py --> module name that will be seen by 
    m.doc() = "matrixpath Python binding"; // optional module docstring

    m.def("matrixpath", &matrixpath, "Build a matrix from a tree of nodes and navigate it",
    py::arg("nodes"), 
    py::arg("out_tree_matrix") = false, 
    py::arg("out_score_matrix") = false,
    py::arg("out_score_table") = false, 
    py::arg("out_path") = std::string());
}
