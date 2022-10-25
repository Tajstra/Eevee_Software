#include "application_software.h"
#include "hal_init.h"

ApplicationSoftware::ApplicationSoftware()
{}

void
ApplicationSoftware::initialize()
{
    systemInit();
    eevee_software.start(&update_1000ms, &update_100ms);
}

void
ApplicationSoftware::update_1000ms()
{
    HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_12);
}

void
ApplicationSoftware::update_100ms()
{
    HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_13);
}
