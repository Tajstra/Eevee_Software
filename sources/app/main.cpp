#include "hal_init.h"
#include "eevee_software.h"

class Main
{
public:
	Main(){};

	void initialize()
	{
		HAL_initialize();
		eevee_software.start(&taskHook_1000ms, &taskHook_100ms);
	}

private:
	static void taskHook_1000ms()
	{
		HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_12);
	}

	static void taskHook_100ms()
	{
		HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_13);
	}

	EeveeSoftware eevee_software;
};

int main()
{
	Main main{};
	main.initialize();

	return 0;
}