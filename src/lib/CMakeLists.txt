if(NOT TARGET matrixpath_compiler_flags)
        find_package(matrixpath_compiler_flags REQUIRED)
endif()

# list of source files
set(libsrc matrixpath.cpp ../matrix.cpp ../node.cpp ../path.cpp)
add_library(objlib OBJECT ${libsrc})
# shared libraries need PIC
set_property(TARGET objlib PROPERTY POSITION_INDEPENDENT_CODE 1)

add_library(matrixpath_lib_static STATIC $<TARGET_OBJECTS:objlib>)
target_link_libraries(matrixpath_lib_static 
        PUBLIC matrixpath_compiler_flags)
target_include_directories(matrixpath_lib_static 
        PUBLIC ${PROJECT_SOURCE_DIR}/src
               ${PROJECT_SOURCE_DIR}/include)
install(TARGETS matrixpath_lib_static
               ARCHIVE DESTINATION ${CMAKE_SOURCE_DIR}/build/lib)


add_library(matrixpath_lib_shared SHARED $<TARGET_OBJECTS:objlib>)
target_link_libraries(matrixpath_lib_shared 
        PUBLIC matrixpath_compiler_flags)
target_include_directories(matrixpath_lib_shared 
        PUBLIC ${PROJECT_SOURCE_DIR}/src
               ${PROJECT_SOURCE_DIR}/include)
install(TARGETS matrixpath_lib_shared
               LIBRARY DESTINATION ${CMAKE_SOURCE_DIR}/build/lib)

install(FILES ../../include/matrixpath.h DESTINATION ${CMAKE_SOURCE_DIR}/build/include)