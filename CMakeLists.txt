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

set(VALVE_CONF_DIR "/etc/valve")
set(SYSTEMD_UNIT_DIR "/usr/lib/systemd/system/")

install(FILES config.toml DESTINATION ${VALVE_CONF_DIR})

install(FILES valve-daemon.service DESTINATION ${SYSTEMD_UNIT_DIR})

set(PACKAGE "DEB")
set(PLATFORM "UBUNTU")
set(GENERATOR "DEBIAN")

set(CPACK_PACKAGE_NAME "valve-controller")

set(CPACK_GENERATOR ${PACKAGE})


set(CPACK_PACKAGING_INSTALL_PREFIX /usr)

set(CPACK_PACKAGE_CONTACT "John R. Patek <johnpatek2@gmail.com>")
set(CPACK_PACKAGE_DESCRIPTION "Valve Controller")
set(CPACK_PACKAGE_VERSION_MAJOR ${VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${VERSION_PATCH})
set(CPACK_PACKAGE_VENDOR "John Patek")
set(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}")
set(CPACK_SOURCE_IGNORE_FILES "build")
include (CPack)