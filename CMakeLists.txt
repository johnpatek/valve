cmake_minimum_required(VERSION 3.0)

project(valve)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR}/install)

set(EXTERN_ROOT ${CMAKE_SOURCE_DIR}/extern/build/install)
set(EXTERN_INCLUDE ${EXTERN_ROOT}/include)
set(EXTERN_LIB ${EXTERN_ROOT}/lib)

if(WIN32)
    set(PTHREAD "")
else()
    set(THREADS_PREFER_PTHREAD_FLAG ON)
    find_package(Threads REQUIRED)    
    set(PTHREAD Threads::Threads)
    find_library(LIBEVENT libevent.a PATHS ${EXTERN_LIB})
    find_library(LIBJSON libjsoncpp.a PATHS ${EXTERN_LIB})
    find_library(LIBRPIGPIO librpigpio.a PATHS ${EXTERN_LIB})
endif(WIN32)

add_subdirectory(src)