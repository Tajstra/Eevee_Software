
#include "hal_mock_common.h"
#include "stm32f4xx_hal.h"

#define GPIO_NUMBER 16U

/**
 * @brief Function is mocking behaviour of stm32f4xx_hal_gpio.c HAL_GPIO_Init() function to some extend
 *
 * @param GPIOx
 * @param GPIO_Init
 */
void HAL_GPIO_Init(GPIO_TypeDef *GPIOx, GPIO_InitTypeDef *GPIO_Init)
{
  (void)GPIOx;
  (void)GPIO_Init;
}

/**
 * @brief Function is mocking behaviour of stm32f4xx_hal_gpio.c HAL_GPIO_DeInit() function to some extend
 *
 * @param GPIOx
 * @param GPIO_Pin
 */
void HAL_GPIO_DeInit(GPIO_TypeDef *GPIOx, uint32_t GPIO_Pin)
{
  (void)GPIOx;
  (void)GPIO_Pin;
}

/**
 * @brief Function is mocking behaviour of stm32f4xx_hal_gpio.c HAL_GPIO_ReadPin() function to some extend
 *
 * @param GPIOx
 * @param GPIO_Pin
 * @return GPIO_PinState
 */
GPIO_PinState HAL_GPIO_ReadPin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
  GPIO_PinState bitstatus;

  /* Check the parameters */
  assert_param(IS_GPIO_PIN(GPIO_Pin));

  if ((GPIOx->IDR & GPIO_Pin) != (uint32_t)GPIO_PIN_RESET)
  {
    bitstatus = GPIO_PIN_SET;
  }
  else
  {
    bitstatus = GPIO_PIN_RESET;
  }
  return bitstatus;
}

/**
 * @brief  Sets or clears the selected data port bit.
 *
 * @note   This function uses GPIOx_BSRR register to allow atomic read/modify
 *         accesses. In this way, there is no risk of an IRQ occurring between
 *         the read and the modify access.
 *
 * @param  GPIOx where x can be (A..K) to select the GPIO peripheral for STM32F429X device or
 *                      x can be (A..I) to select the GPIO peripheral for STM32F40XX and STM32F427X devices.
 * @param  GPIO_Pin specifies the port bit to be written.
 *          This parameter can be one of GPIO_PIN_x where x can be (0..15).
 * @param  PinState specifies the value to be written to the selected bit.
 *          This parameter can be one of the GPIO_PinState enum values:
 *            @arg GPIO_PIN_RESET: to clear the port pin
 *            @arg GPIO_PIN_SET: to set the port pin
 * @retval None
 */
void HAL_GPIO_WritePin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, GPIO_PinState PinState)
{
}

/**
 * @brief  Toggles the specified GPIO pins.
 * @param  GPIOx Where x can be (A..K) to select the GPIO peripheral for STM32F429X device or
 *                      x can be (A..I) to select the GPIO peripheral for STM32F40XX and STM32F427X devices.
 * @param  GPIO_Pin Specifies the pins to be toggled.
 * @retval None
 */
void HAL_GPIO_TogglePin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
  uint32_t odr;

  /* Check the parameters */
  assert_param(IS_GPIO_PIN(GPIO_Pin));

  /* get current Output Data Register value */
  odr = GPIOx->ODR;

  /* Set selected pins that were at low level, and reset ones that were high */
  GPIOx->BSRR = ((odr & GPIO_Pin) << GPIO_NUMBER) | (~odr & GPIO_Pin);

  // Simulate that CPU writes to ODR from BSRR:
  GPIOx->ODR = GPIOx->BSRR;
}

/**
 * @brief  Locks GPIO Pins configuration registers.
 * @note   The locked registers are GPIOx_MODER, GPIOx_OTYPER, GPIOx_OSPEEDR,
 *         GPIOx_PUPDR, GPIOx_AFRL and GPIOx_AFRH.
 * @note   The configuration of the locked GPIO pins can no longer be modified
 *         until the next reset.
 * @param  GPIOx where x can be (A..F) to select the GPIO peripheral for STM32F4 family
 * @param  GPIO_Pin specifies the port bit to be locked.
 *         This parameter can be any combination of GPIO_PIN_x where x can be (0..15).
 * @retval None
 */
HAL_StatusTypeDef HAL_GPIO_LockPin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
}

/**
 * @brief  This function handles EXTI interrupt request.
 * @param  GPIO_Pin Specifies the pins connected EXTI line
 * @retval None
 */
void HAL_GPIO_EXTI_IRQHandler(uint16_t GPIO_Pin)
{
}

/**
 * @brief  EXTI line detection callbacks.
 * @param  GPIO_Pin Specifies the pins connected EXTI line
 * @retval None
 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
}
