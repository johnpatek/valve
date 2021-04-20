file(GLOB VALVECTL_SOURCES "*.h" "*.cpp")

add_executable(valvectl ${VALVECTL_SOURCES})

target_include_directories(
    valvectl 
    PRIVATE 
    ${VALVE_INCLUDE})

target_link_libraries(valvectl valve)