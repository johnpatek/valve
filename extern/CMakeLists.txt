cmake_minimum_required(VERSION 3.0)

project(extern)

set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR}/install)

set(SPDLOG_INSTALL ON CACHE BOOL "Install spdlog")
set(EVENT__DISABLE_MBEDTLS ON CACHE BOOL "Disable mbedTLS")
set(EVENT__DISABLE_TESTS OFF CACHE BOOL "")
set(EVENT__DISABLE_REGRESS OFF CACHE BOOL "")
set(EVENT__DISABLE_BENCHMARK OFF CACHE BOOL "")
set(EVENT__DISABLE_SAMPLES OFF CACHE BOOL "")
set(FLATBUFFERS_BUILD_TESTS OFF CACHE BOOL "Build flatbuffers tests")
set(JSONCPP_WITH_TESTS OFF CACHE BOOL "")
set(JSONCPP_WITH_POST_BUILD_UNITTEST OFF CACHE BOOL "")
set(JSONCPP_WITH_STRICT_ISO OFF CACHE BOOL "")

#configure_file(${CMAKE_SOURCE_DIR}/cryptopp-cmake/CMakeLists.txt ${CMAKE_SOURCE_DIR}/cryptopp/CMakeLists.txt COPYONLY)
#configure_file(${CMAKE_SOURCE_DIR}/cryptopp-cmake/cryptopp-config.cmake ${CMAKE_SOURCE_DIR}/cryptopp/cryptopp-config.cmake COPYONLY)

add_subdirectory(jsoncpp)
add_subdirectory(libevent)
#add_subdirectory(cryptopp)
add_subdirectory(spdlog)
add_subdirectory(toml11)
add_subdirectory(rpi-gpio)