if(NOT TARGET matrixpath_compiler_flags)
        find_package(matrixpath_compiler_flags REQUIRED)
endif()

add_executable(matrixpath main.cpp matrix.cpp node.cpp path.cpp)
target_link_libraries(matrixpath 
        PUBLIC matrixpath_compiler_flags)
target_include_directories(matrixpath 
        PUBLIC ${PROJECT_SOURCE_DIR}/src)

install(TARGETS matrixpath 
        RUNTIME DESTINATION ${CMAKE_SOURCE_DIR}/build/matrixpath)
