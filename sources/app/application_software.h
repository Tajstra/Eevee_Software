#pragma once
#include "eevee_software.h"

class ApplicationSoftware
{
public:
	ApplicationSoftware();

	void initialize();

	void print()
	{
		// std::cout << "Application software print" << std::endl;
	}

	float
	getSimTime() const
	{
		return eevee_software.getSimTime();
	}

private:
	static void update_1000ms();
	static void update_100ms();

	EeveeSoftware eevee_software{};
};