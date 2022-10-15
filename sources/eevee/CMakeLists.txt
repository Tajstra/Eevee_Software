target_sources(eevee_software PRIVATE "eevee_software.cpp" "freertos_hooks.c")

target_include_directories(eevee_software PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")