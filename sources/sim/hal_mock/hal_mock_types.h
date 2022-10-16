#pragma once

#include <cassert>

// General:

typedef enum 
{
  HAL_OK       = 0x00U,
  HAL_ERROR    = 0x01U,
  HAL_BUSY     = 0x02U,
  HAL_TIMEOUT  = 0x03U
} HAL_StatusTypeDef;

/* Structures required for mocking*/
struct GPIO_TypeDef
{
  GPIO_TypeDef(std::string name) : port_name(name)
  {}

  std::string   port_name;

  // HAL variables:
  std::uint32_t MODER {};   // GPIO port mode register,
  std::uint32_t OTYPER {};  // GPIO port output type register,
  std::uint32_t OSPEEDR {}; // GPIO port output speed register,
  std::uint32_t PUPDR {};   // GPIO port pull-up/pull-down register,
  std::uint32_t IDR {};     // GPIO port input data register,
  std::uint32_t ODR {};     // GPIO port output data register,
  std::uint32_t BSRR {};    // GPIO port bit set/reset register,
  std::uint32_t LCKR {};    // GPIO port configuration lock register,
  std::uint32_t AFR[2] {};  // GPIO alternate function registers
};

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
