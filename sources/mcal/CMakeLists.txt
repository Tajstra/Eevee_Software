target_sources(free_rtos PRIVATE "port_files/port.c")

target_include_directories(free_rtos PRIVATE "port_files")

target_include_directories(eevee_software PRIVATE "port_files" "${CMAKE_CURRENT_SOURCE_DIR}")

add_subdirectory(cubemx)

target_link_options(eevee_software PRIVATE --specs=nosys.specs)

set_target_properties(
    eevee_software 
    PROPERTIES 
        OUTPUT_NAME "eevee_software"
        SUFFIX ".elf"
)