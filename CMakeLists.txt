cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_CXX_EXTENSIONS OFF)

# set the project name and version
project(matrixpath 
        VERSION 1.0.0.0
        LANGUAGES C CXX
        DESCRIPTION "Build a matrix from a tree of nodes and navigate it")
      
# specify the C++ standard
add_library(matrixpath_compiler_flags INTERFACE)
target_compile_features(matrixpath_compiler_flags 
        INTERFACE cxx_std_17 
                  c_std_99)

# configure a header file to pass some of the CMake settings
# to the source code
set(Python3_ROOT_DIR "${CONDA_ROOT}/envs/py39")
find_package(Python 3.9 EXACT COMPONENTS Interpreter Development REQUIRED)
configure_file(${PROJECT_SOURCE_DIR}/src/config.h.in ${PROJECT_SOURCE_DIR}/src/config.h)

# Subproject executable
add_subdirectory(src ${PROJECT_SOURCE_DIR}/build/bin)
# Subproject library static and shared
add_subdirectory(src/lib ${PROJECT_SOURCE_DIR}/build/lib)
# Subproject python bindings
add_subdirectory(src/python ${PROJECT_SOURCE_DIR}/build/python)