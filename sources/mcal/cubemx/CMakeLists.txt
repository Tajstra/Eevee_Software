target_sources(
  eevee_software
  PRIVATE
  "Core/Src/gpio.c " "Core/Src/usart.c " "Core/Src/stm32f4xx_it.c "
  "Core/Src/stm32f4xx_hal_msp.c "
  "Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_tim.c "
  "Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_tim_ex.c "
  "Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_uart.c "
  "Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc.c "
  "Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc_ex.c "
  "Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash.c "
  "Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash_ex.c "
  "Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash_ramfunc.c "
  "Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_gpio.c "
  "Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma_ex.c "
  "Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma.c "
  "Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr.c "
  "Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr_ex.c "
  "Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_cortex.c "
  "Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal.c "
  "Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_exti.c "
  "Core/Src/system_stm32f4xx.c" "startup_stm32f411xe.s"
)

target_include_directories(
  eevee_software
  PRIVATE "Core/Inc" "Drivers/STM32F4xx_HAL_Driver/Inc"
          "Drivers/STM32F4xx_HAL_Driver/Inc/Legacy"
          "Drivers/CMSIS/Device/ST/STM32F4xx/Include" "Drivers/CMSIS/Include")
