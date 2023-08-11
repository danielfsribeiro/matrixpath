cmake_minimum_required(VERSION 3.0.0)

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
configure_file(${PROJECT_SOURCE_DIR}/src/config.h.in ${PROJECT_SOURCE_DIR}/src/config.h)

add_executable(matrixpath src/main.cpp src/matrix.cpp src/node.cpp src/path.cpp)

target_link_libraries(matrixpath 
        PUBLIC matrixpath_compiler_flags)

target_include_directories(matrixpath 
        PUBLIC ${PROJECT_SOURCE_DIR}/src)
                           
