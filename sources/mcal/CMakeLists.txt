target_sources(free_rtos PRIVATE "port_files/port.c")

target_include_directories(free_rtos PRIVATE "port_files")

target_sources(eevee_software PUBLIC "../sim/main.c" "main_blinky.c")

target_include_directories(eevee_software PRIVATE "port_files")

# Set linker script:
# set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -T ${CMAKE_SOURCE_DIR}/sources/mcal/cubemx/STM32F411VETx_FLASH.ld")
# set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -T ${CMAKE_SOURCE_DIR}/sources/mcal/cubemx/STM32F411VETx_FLASH.ld")
# set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lc")
# set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lm")
# set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lnosys")

add_subdirectory(cubemx)

target_link_options(eevee_software PRIVATE --specs=nosys.specs)

set_target_properties(
    eevee_software 
    PROPERTIES 
        OUTPUT_NAME "eevee_software"
        SUFFIX ".elf"
)