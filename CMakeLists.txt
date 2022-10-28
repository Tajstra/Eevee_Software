cmake_minimum_required(VERSION 3.13)
project(eevee_software CXX C ASM)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/release/${TARGET})

include(cmake/common_flags.cmake)

set(EXECUTABLE_NAME "Eevee_sotware_${TARGET}_${BUILD_TYPE}")
add_executable(${EXECUTABLE_NAME} "")

target_include_directories(
  ${EXECUTABLE_NAME}
  PRIVATE ${CMAKE_SOURCE_DIR}/sources ${CMAKE_SOURCE_DIR}/sources/app
          ${CMAKE_SOURCE_DIR}/libraries)

set(APPLICATION_BASED_TARGET
    ${TARGET}
    STREQUAL
    "SIM"
    OR
    ${TARGET}
    STREQUAL
    "MCAL")

if(${APPLICATION_BASED_TARGET})
  # Add main of the project:
  target_sources(${EXECUTABLE_NAME}
                 PRIVATE "sources/app/application_software.cpp")
  # Add common directories and libraries for system targets:
  add_subdirectory(${CMAKE_SOURCE_DIR}/sources/eevee)
  add_library(free_rtos STATIC "")
  include(${CMAKE_SOURCE_DIR}/cmake/freertos.cmake)
  target_link_libraries(${EXECUTABLE_NAME} free_rtos)
endif()

if(${TARGET} STREQUAL "SIM")
  add_subdirectory(tests/integration_tests)
  add_subdirectory(sources/sim)
  message(STATUS "Subdirectory sources/sim added")
elseif(${TARGET} STREQUAL "MCAL")
  add_subdirectory(sources/mcal)
  message(STATUS "Subdirectory sources/mcal added")
elseif(${TARGET} STREQUAL "UNIT_TEST")
  add_subdirectory(libraries/matplotlib-cpp)
  add_subdirectory(tests/unit_tests)
  message(STATUS "Subdirectory tests/unit_tests added")
elseif(${TARGET} STREQUAL "")
  message(SEND_ERROR "Please specify the target using '-DTARGET=target'")
else()
  message(SEND_ERROR "Target '${TARGET}' does not exist")
endif()
