target_sources(free_rtos PRIVATE "port_files/port.c")

target_include_directories(free_rtos PRIVATE "port_files")

target_include_directories(${EXECUTABLE_NAME} PRIVATE "port_files" "${CMAKE_CURRENT_SOURCE_DIR}")

add_subdirectory(cubemx)

target_link_options(${EXECUTABLE_NAME} PRIVATE --specs=nosys.specs)

set_target_properties(
    ${EXECUTABLE_NAME} 
    PROPERTIES 
        OUTPUT_NAME "${EXECUTABLE_NAME}"
        SUFFIX ".elf"
)