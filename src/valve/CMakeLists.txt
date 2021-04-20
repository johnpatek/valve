file(GLOB VALVE_SOURCES "*.h" "*.cpp")

add_library(valve STATIC ${VALVE_SOURCES})

target_include_directories(
    valve
    PRIVATE
    ${VALVE_INCLUDE}
    ${EXTERN_INCLUDE})

target_link_libraries(
    valve
    valveprotocol
    ${LIBEVENT})

