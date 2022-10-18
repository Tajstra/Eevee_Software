#pragma once

#include "hal_mock_common.h"

GPIO_TypeDef g_gpio_port_a_instance{};
GPIO_TypeDef g_gpio_port_b_instance{};
GPIO_TypeDef g_gpio_port_c_instance{};
GPIO_TypeDef g_gpio_port_d_instance{};
GPIO_TypeDef g_gpio_port_e_instance{};
GPIO_TypeDef g_gpio_port_f_instance{};
GPIO_TypeDef g_gpio_port_g_instance{};
GPIO_TypeDef g_gpio_port_h_instance{};

// Defines to mock pointers to GPIO
#define GPIOA &g_gpio_port_a_instance
#define GPIOB &g_gpio_port_b_instance
#define GPIOC &g_gpio_port_c_instance
#define GPIOD &g_gpio_port_d_instance
#define GPIOE &g_gpio_port_e_instance
#define GPIOF &g_gpio_port_f_instance
#define GPIOG &g_gpio_port_g_instance
#define GPIOH &g_gpio_port_h_instance


// Public functions:
void systemInit()
{
	// std::cout << "Inititalizing HAL" << std::endl;
}