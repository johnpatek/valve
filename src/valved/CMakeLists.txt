file(GLOB VALVED_SOURCES "*.h" "*.cpp")

add_executable(valved ${VALVED_SOURCES})

target_include_directories(
    valved 
    PRIVATE 
    ${VALVE_INCLUDE}
    ${EXTERN_INCLUDE})

target_link_libraries(
    valved 
    valve
    ${LIBRPIGPIO})