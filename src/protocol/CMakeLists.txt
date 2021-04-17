file(GLOB PROTOCOL_SOURCES "*.h" "*.cpp")

add_library(valveprotocol STATIC ${PROTOCOL_SOURCES})

target_include_directories(
    valveprotocol
    PUBLIC
    ${VALVE_INCLUDE})

target_link_libraries(valveprotocol )