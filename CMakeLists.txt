cmake_minimum_required(VERSION 3.13)
project(eevee_software)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/release)

cmake_path(SET free_rtos_source "${CMAKE_SOURCE_DIR}/sources/eevee/FreeRTOSv202112.00/FreeRTOS/Source")

add_library(free_rtos
    STATIC
    ${free_rtos_source}/croutine.c 
    ${free_rtos_source}/event_groups.c 
    ${free_rtos_source}/list.c 
    ${free_rtos_source}/queue.c 
    ${free_rtos_source}/stream_buffer.c 
    ${free_rtos_source}/tasks.c 
    ${free_rtos_source}/timers.c 
    ${free_rtos_source}/portable/MSVC-MingW/port.c
    ${free_rtos_source}/portable/MemMang/heap_5.c)

cmake_path(SET demo_windows_source "${CMAKE_SOURCE_DIR}/sources/eevee/FreeRTOSv202112.00/FreeRTOS/Demo/WIN32-MingW")

add_executable(eevee_software
    ${demo_windows_source}/main.c
    ${demo_windows_source}/main_blinky.c
    ${demo_windows_source}/Run-time-stats-utils.c)

list(APPEND
    free_rtos_flags
    "-fpermissive")

target_compile_options(free_rtos
    PRIVATE
    ${free_rtos_flags})

target_include_directories(free_rtos
    PRIVATE
    "${free_rtos_source}/include"
    "${free_rtos_source}/portable/MSVC-MingW"
    "${demo_windows_source}")

list(APPEND
    demo_flags
    "-fpermissive")

target_compile_options(eevee_software
    PRIVATE
    ${demo_flags})

target_include_directories(eevee_software
    PRIVATE
    "${free_rtos_source}/include"
    "${free_rtos_source}/portable/MSVC-MingW"
    "${demo_windows_source}")

target_link_libraries(eevee_software free_rtos -lwinmm)