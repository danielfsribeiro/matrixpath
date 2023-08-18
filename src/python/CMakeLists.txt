if(NOT TARGET matrixpath_lib_static)
        find_package(matrixpath_lib_static REQUIRED)
endif()
set(Python3_ROOT_DIR "${CONDA_ROOT}/envs/py39")
find_package(Python 3.9 EXACT COMPONENTS Interpreter Development REQUIRED)
find_package(pybind11 CONFIG REQUIRED)

pybind11_add_module(matrixpath_py matrixpath_py.cpp)
target_link_libraries(matrixpath_py
        PUBLIC pybind11::module
               matrixpath_lib_static)
install(FILES matrixpath.py tests.py DESTINATION ${CMAKE_SOURCE_DIR}/build/python)
