#include "simulated_integration_test.h"

// Includes to control FreeRTOS for testing purposes:
#include "FreeRTOS.h"
#include "task.h"

ApplicationSoftware app_software{};

int main()
{
	testing::InitGoogleTest();

	// SimulatedIntegrationTest integration_test (application_software);

	// Create a test task with low prority that can only read from application software:
	xTaskCreate(&SimulatedIntegrationTest::integrationTestTask,
				"Test task",
				configMINIMAL_STACK_SIZE,
				NULL,
				tskIDLE_PRIORITY,
				NULL);

	app_software.initialize();

	return 0;
}
