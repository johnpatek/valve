cmake_minimum_required(VERSION 3.0)

project(valve)

set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR}/install)

set(EXTERN_ROOT ${CMAKE_SOURCE_DIR}/extern/build/install)
set(EXTERN_INCLUDE ${EXTERN_ROOT}/include)
set(EXTERN_LIB ${EXTERN_ROOT}/lib)





add_subdirectory(src)