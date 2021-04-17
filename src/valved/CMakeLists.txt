file(GLOB VALVED_SOURCES "*.h" "*.cpp")

add_executable(valved ${VALVED_SOURCES})

target_include_directories(
    valved 
    PRIVATE 
    ${VALVE_INCLUDE})