cmake_minimum_required(VERSION 3.0)

project(extern)

set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR}/install)

set(SPDLOG_INSTALL ON CACHE BOOL "Install spdlog")
set(EVENT__DISABLE_MBEDTLS ON CACHE BOOL "Disable mbedTLS")

configure_file(${CMAKE_SOURCE_DIR}/cryptopp-cmake/CMakeLists.txt ${CMAKE_SOURCE_DIR}/cryptopp/CMakeLists.txt COPYONLY)
configure_file(${CMAKE_SOURCE_DIR}/cryptopp-cmake/cryptopp-config.cmake ${CMAKE_SOURCE_DIR}/cryptopp/cryptopp-config.cmake COPYONLY)

add_subdirectory(libevent)
add_subdirectory(flatbuffers)
add_subdirectory(cryptopp)
add_subdirectory(spdlog)
add_subdirectory(rapidyaml)