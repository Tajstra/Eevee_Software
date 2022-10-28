#include "simulated_integration_test.h"
// Includes to control FreeRTOS for testing purposes:
#include "FreeRTOS.h"
#include "task.h"

void
SimulatedIntegrationTest::executeSystick()
{
    extern void prvProcessSimulatedInterrupts(void);
    prvProcessSimulatedInterrupts();
}
