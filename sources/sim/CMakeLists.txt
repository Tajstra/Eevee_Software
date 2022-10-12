target_sources(free_rtos PRIVATE "port_files/port.c")

target_include_directories(free_rtos PRIVATE "port_files")

target_sources(
  eevee_software
  PRIVATE "main.c"
          "main_blinky.c")


target_include_directories(eevee_software
    PRIVATE
    "port_files")

target_link_libraries(free_rtos -lwinmm)
