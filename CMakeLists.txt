cmake_minimum_required(VERSION 3.13)
project(eevee_software CXX C ASM)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/release/${TARGET})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Og -g -gdwarf-2 -fno-exceptions")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Og -gdwarf-2 -g")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")

add_executable(eevee_software "sources/app/main.cpp")
add_subdirectory(sources/eevee)

add_library(free_rtos STATIC "")
include(cmake/freertos.cmake)

if("${TARGET}" STREQUAL "SIM")
  add_subdirectory(sources/sim)
  message(STATUS "Subdirectory sources/sim added")
elseif("${TARGET}" STREQUAL "MCAL")
  add_subdirectory(sources/mcal)
  message(STATUS "Subdirectory sources/mcal added")
elseif("${TARGET}" STREQUAL "")
  message(SEND_ERROR "Please specify the target using '-DTARGET=target'")
else()
  message(SEND_ERROR "Target '${TARGET}' does not exist")
endif()

target_include_directories(
  eevee_software PRIVATE "${free_rtos_source}/include")

target_link_libraries(eevee_software free_rtos)
