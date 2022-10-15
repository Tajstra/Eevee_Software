target_sources(free_rtos PRIVATE "port_files/port.c")

target_include_directories(free_rtos PRIVATE "port_files")

target_sources(${EXECUTABLE_NAME} PRIVATE "hal_mock/stm32f4xx_hal_gpio.cpp")

target_include_directories(
  ${EXECUTABLE_NAME}
  PRIVATE "port_files"
          # Includes for HAL mock:
          "hal_mock")

target_link_libraries(free_rtos -lwinmm)
