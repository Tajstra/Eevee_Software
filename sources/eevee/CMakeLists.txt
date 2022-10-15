target_sources(${EXECUTABLE_NAME} PRIVATE "eevee_software.cpp" "freertos_hooks.c")

target_include_directories(${EXECUTABLE_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")