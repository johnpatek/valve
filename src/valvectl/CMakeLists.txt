file(GLOB VALVECTL_SOURCES "*.h" "*.cpp")

add_executable(valvectl ${VALVECTL_SOURCES})

target_include_directories(
    valvectl 
    PRIVATE 
    ${VALVECTL_INCLUDE})