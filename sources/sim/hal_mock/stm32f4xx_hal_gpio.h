#pragma once

/* Includes ------------------------------------------------------------------*/
#include <cstdint>
#include <string>
#include "hal_mock_types.h"

/* Structures required for mocking*/
struct GPIO_TypeDef
{
  GPIO_TypeDef(std::string name) : port_name(name)
  {}

  std::string   port_name;

  // HAL variables:
  std::uint32_t MODER;   // GPIO port mode register,
  std::uint32_t OTYPER;  // GPIO port output type register,
  std::uint32_t OSPEEDR; // GPIO port output speed register,
  std::uint32_t PUPDR;   // GPIO port pull-up/pull-down register,
  std::uint32_t IDR;     // GPIO port input data register,
  std::uint32_t ODR;     // GPIO port output data register,
  std::uint32_t BSRR;    // GPIO port bit set/reset register,
  std::uint32_t LCKR;    // GPIO port configuration lock register,
  std::uint32_t AFR[2];  // GPIO alternate function registers
};

extern GPIO_TypeDef *GPIOA;
extern GPIO_TypeDef *GPIOB;
extern GPIO_TypeDef *GPIOC;
extern GPIO_TypeDef *GPIOD;
extern GPIO_TypeDef *GPIOE;
extern GPIO_TypeDef *GPIOF;
extern GPIO_TypeDef *GPIOG;
extern GPIO_TypeDef *GPIOH;

struct GPIO_Ports
{
  GPIO_TypeDef gpio_a_instance {"GPIO A"};
  GPIO_TypeDef gpio_b_instance {"GPIO B"};
  GPIO_TypeDef gpio_c_instance {"GPIO C"};
  GPIO_TypeDef gpio_d_instance {"GPIO D"};
  GPIO_TypeDef gpio_e_instance {"GPIO E"};
  GPIO_TypeDef gpio_f_instance {"GPIO F"};
  GPIO_TypeDef gpio_g_instance {"GPIO G"};
  GPIO_TypeDef gpio_h_instance {"GPIO H"};
};

// Copy-pasted code from original stm32f4xx_pgio.h file
typedef struct
{
  uint32_t Pin; /*!< Specifies the GPIO pins to be configured.
                     This parameter can be any value of @ref GPIO_pins_define */

  uint32_t Mode; /*!< Specifies the operating mode for the selected pins.
                      This parameter can be a value of @ref GPIO_mode_define */

  uint32_t Pull; /*!< Specifies the Pull-up or Pull-Down activation for the selected pins.
                      This parameter can be a value of @ref GPIO_pull_define */

  uint32_t Speed; /*!< Specifies the speed for the selected pins.
                       This parameter can be a value of @ref GPIO_speed_define */

  uint32_t Alternate; /*!< Peripheral to be connected to the selected pins.
                           This parameter can be a value of @ref GPIO_Alternate_function_selection */
} GPIO_InitTypeDef;

typedef enum
{
  GPIO_PIN_RESET = 0,
  GPIO_PIN_SET
} GPIO_PinState;

#define GPIO_PIN_0 ((uint16_t)0x0001)   /* Pin 0 selected    */
#define GPIO_PIN_1 ((uint16_t)0x0002)   /* Pin 1 selected    */
#define GPIO_PIN_2 ((uint16_t)0x0004)   /* Pin 2 selected    */
#define GPIO_PIN_3 ((uint16_t)0x0008)   /* Pin 3 selected    */
#define GPIO_PIN_4 ((uint16_t)0x0010)   /* Pin 4 selected    */
#define GPIO_PIN_5 ((uint16_t)0x0020)   /* Pin 5 selected    */
#define GPIO_PIN_6 ((uint16_t)0x0040)   /* Pin 6 selected    */
#define GPIO_PIN_7 ((uint16_t)0x0080)   /* Pin 7 selected    */
#define GPIO_PIN_8 ((uint16_t)0x0100)   /* Pin 8 selected    */
#define GPIO_PIN_9 ((uint16_t)0x0200)   /* Pin 9 selected    */
#define GPIO_PIN_10 ((uint16_t)0x0400)  /* Pin 10 selected   */
#define GPIO_PIN_11 ((uint16_t)0x0800)  /* Pin 11 selected   */
#define GPIO_PIN_12 ((uint16_t)0x1000)  /* Pin 12 selected   */
#define GPIO_PIN_13 ((uint16_t)0x2000)  /* Pin 13 selected   */
#define GPIO_PIN_14 ((uint16_t)0x4000)  /* Pin 14 selected   */
#define GPIO_PIN_15 ((uint16_t)0x8000)  /* Pin 15 selected   */
#define GPIO_PIN_All ((uint16_t)0xFFFF) /* All pins selected */

#define GPIO_PIN_MASK 0x0000FFFFU /* PIN mask for assert test */

#define GPIO_MODE_INPUT MODE_INPUT                    /*!< Input Floating Mode                   */
#define GPIO_MODE_OUTPUT_PP (MODE_OUTPUT | OUTPUT_PP) /*!< Output Push Pull Mode                 */
#define GPIO_MODE_OUTPUT_OD (MODE_OUTPUT | OUTPUT_OD) /*!< Output Open Drain Mode                */
#define GPIO_MODE_AF_PP (MODE_AF | OUTPUT_PP)         /*!< Alternate Function Push Pull Mode     */
#define GPIO_MODE_AF_OD (MODE_AF | OUTPUT_OD)         /*!< Alternate Function Open Drain Mode    */

#define GPIO_MODE_ANALOG MODE_ANALOG /*!< Analog Mode  */

#define GPIO_MODE_IT_RISING (MODE_INPUT | EXTI_IT | TRIGGER_RISING)                           /*!< External Interrupt Mode with Rising edge trigger detection          */
#define GPIO_MODE_IT_FALLING (MODE_INPUT | EXTI_IT | TRIGGER_FALLING)                         /*!< External Interrupt Mode with Falling edge trigger detection         */
#define GPIO_MODE_IT_RISING_FALLING (MODE_INPUT | EXTI_IT | TRIGGER_RISING | TRIGGER_FALLING) /*!< External Interrupt Mode with Rising/Falling edge trigger detection  */

#define GPIO_MODE_EVT_RISING (MODE_INPUT | EXTI_EVT | TRIGGER_RISING)                           /*!< External Event Mode with Rising edge trigger detection             */
#define GPIO_MODE_EVT_FALLING (MODE_INPUT | EXTI_EVT | TRIGGER_FALLING)                         /*!< External Event Mode with Falling edge trigger detection            */
#define GPIO_MODE_EVT_RISING_FALLING (MODE_INPUT | EXTI_EVT | TRIGGER_RISING | TRIGGER_FALLING) /*!< External Event Mode with Rising/Falling edge trigger detection     */

#define GPIO_SPEED_FREQ_LOW 0x00000000U       /*!< IO works at 2 MHz, please refer to the product datasheet */
#define GPIO_SPEED_FREQ_MEDIUM 0x00000001U    /*!< range 12,5 MHz to 50 MHz, please refer to the product datasheet */
#define GPIO_SPEED_FREQ_HIGH 0x00000002U      /*!< range 25 MHz to 100 MHz, please refer to the product datasheet  */
#define GPIO_SPEED_FREQ_VERY_HIGH 0x00000003U /*!< range 50 MHz to 200 MHz, please refer to the product datasheet  */

#define GPIO_NOPULL 0x00000000U   /*!< No Pull-up or Pull-down activation  */
#define GPIO_PULLUP 0x00000001U   /*!< Pull-up activation                  */
#define GPIO_PULLDOWN 0x00000002U /*!< Pull-down activation                */

/**
 * @brief  Checks whether the specified EXTI line flag is set or not.
 * @param  __EXTI_LINE__ specifies the EXTI line flag to check.
 *         This parameter can be GPIO_PIN_x where x can be(0..15)
 * @retval The new state of __EXTI_LINE__ (SET or RESET).
 */
#define __HAL_GPIO_EXTI_GET_FLAG(__EXTI_LINE__) (EXTI->PR & (__EXTI_LINE__))

/**
 * @brief  Clears the EXTI's line pending flags.
 * @param  __EXTI_LINE__ specifies the EXTI lines flags to clear.
 *         This parameter can be any combination of GPIO_PIN_x where x can be (0..15)
 * @retval None
 */
#define __HAL_GPIO_EXTI_CLEAR_FLAG(__EXTI_LINE__) (EXTI->PR = (__EXTI_LINE__))

/**
 * @brief  Checks whether the specified EXTI line is asserted or not.
 * @param  __EXTI_LINE__ specifies the EXTI line to check.
 *          This parameter can be GPIO_PIN_x where x can be(0..15)
 * @retval The new state of __EXTI_LINE__ (SET or RESET).
 */
#define __HAL_GPIO_EXTI_GET_IT(__EXTI_LINE__) (EXTI->PR & (__EXTI_LINE__))

/**
 * @brief  Clears the EXTI's line pending bits.
 * @param  __EXTI_LINE__ specifies the EXTI lines to clear.
 *          This parameter can be any combination of GPIO_PIN_x where x can be (0..15)
 * @retval None
 */
#define __HAL_GPIO_EXTI_CLEAR_IT(__EXTI_LINE__) (EXTI->PR = (__EXTI_LINE__))

/**
 * @brief  Generates a Software interrupt on selected EXTI line.
 * @param  __EXTI_LINE__ specifies the EXTI line to check.
 *          This parameter can be GPIO_PIN_x where x can be(0..15)
 * @retval None
 */
#define __HAL_GPIO_EXTI_GENERATE_SWIT(__EXTI_LINE__) (EXTI->SWIER |= (__EXTI_LINE__))

/* Initialization and de-initialization functions *****************************/
void HAL_GPIO_Init(GPIO_TypeDef *GPIOx, GPIO_InitTypeDef *GPIO_Init);
void HAL_GPIO_DeInit(GPIO_TypeDef *GPIOx, uint32_t GPIO_Pin);

/* IO operation functions *****************************************************/
GPIO_PinState HAL_GPIO_ReadPin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
void HAL_GPIO_WritePin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, GPIO_PinState PinState);
void HAL_GPIO_TogglePin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
HAL_StatusTypeDef HAL_GPIO_LockPin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
void HAL_GPIO_EXTI_IRQHandler(uint16_t GPIO_Pin);
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);

/* Private constants ---------------------------------------------------------*/
#define GPIO_MODE_Pos 0U
#define GPIO_MODE (0x3UL << GPIO_MODE_Pos)
#define MODE_INPUT (0x0UL << GPIO_MODE_Pos)
#define MODE_OUTPUT (0x1UL << GPIO_MODE_Pos)
#define MODE_AF (0x2UL << GPIO_MODE_Pos)
#define MODE_ANALOG (0x3UL << GPIO_MODE_Pos)
#define OUTPUT_TYPE_Pos 4U
#define OUTPUT_TYPE (0x1UL << OUTPUT_TYPE_Pos)
#define OUTPUT_PP (0x0UL << OUTPUT_TYPE_Pos)
#define OUTPUT_OD (0x1UL << OUTPUT_TYPE_Pos)
#define EXTI_MODE_Pos 16U
#define EXTI_MODE (0x3UL << EXTI_MODE_Pos)
#define EXTI_IT (0x1UL << EXTI_MODE_Pos)
#define EXTI_EVT (0x2UL << EXTI_MODE_Pos)
#define TRIGGER_MODE_Pos 20U
#define TRIGGER_MODE (0x7UL << TRIGGER_MODE_Pos)
#define TRIGGER_RISING (0x1UL << TRIGGER_MODE_Pos)
#define TRIGGER_FALLING (0x2UL << TRIGGER_MODE_Pos)

/* Private macros ------------------------------------------------------------*/
#define IS_GPIO_PIN_ACTION(ACTION) (((ACTION) == GPIO_PIN_RESET) || ((ACTION) == GPIO_PIN_SET))
#define IS_GPIO_PIN(PIN) (((((uint32_t)PIN) & GPIO_PIN_MASK) != 0x00U) && ((((uint32_t)PIN) & ~GPIO_PIN_MASK) == 0x00U))
#define IS_GPIO_MODE(MODE) (((MODE) == GPIO_MODE_INPUT) ||              \
                            ((MODE) == GPIO_MODE_OUTPUT_PP) ||          \
                            ((MODE) == GPIO_MODE_OUTPUT_OD) ||          \
                            ((MODE) == GPIO_MODE_AF_PP) ||              \
                            ((MODE) == GPIO_MODE_AF_OD) ||              \
                            ((MODE) == GPIO_MODE_IT_RISING) ||          \
                            ((MODE) == GPIO_MODE_IT_FALLING) ||         \
                            ((MODE) == GPIO_MODE_IT_RISING_FALLING) ||  \
                            ((MODE) == GPIO_MODE_EVT_RISING) ||         \
                            ((MODE) == GPIO_MODE_EVT_FALLING) ||        \
                            ((MODE) == GPIO_MODE_EVT_RISING_FALLING) || \
                            ((MODE) == GPIO_MODE_ANALOG))
#define IS_GPIO_SPEED(SPEED) (((SPEED) == GPIO_SPEED_FREQ_LOW) || ((SPEED) == GPIO_SPEED_FREQ_MEDIUM) || \
                              ((SPEED) == GPIO_SPEED_FREQ_HIGH) || ((SPEED) == GPIO_SPEED_FREQ_VERY_HIGH))
#define IS_GPIO_PULL(PULL) (((PULL) == GPIO_NOPULL) || ((PULL) == GPIO_PULLUP) || \
                            ((PULL) == GPIO_PULLDOWN))
