target_sources(free_rtos PRIVATE "port_files/port.c")

target_include_directories(free_rtos PRIVATE "port_files")

target_sources(${EXECUTABLE_NAME}
               PRIVATE "hal_mock/stm32f4xx_hal_gpio_mock.cpp")

target_include_directories(
  ${EXECUTABLE_NAME}
  PRIVATE "port_files"
          # Includes for HAL mock:
          "hal_mock"
          "../mcal/cubemx/Drivers/STM32F4xx_HAL_Driver/Inc"
          "../mcal/cubemx/Core/Inc"
          "../mcal/cubemx/Drivers/CMSIS/Device/ST/STM32F4xx/Include")
