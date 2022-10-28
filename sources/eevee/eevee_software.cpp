//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                  (C) Copyright 2022 Konrad Tajstra. All rights reserved.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                     ____  ____  _  _  ____  ____      ____   __  ____  ____  _  _   __   ____  ____
//                    (  __)(  __)/ )( \(  __)(  __)    / ___) /  \(  __)(_  _)/ )( \ / _\ (  _ \(  __)
//                     ) _)  ) _) \ \/ / ) _)  ) _)     \___ \(  O )) _)   )(  \ /\ //    \ )   / ) _)
//                    (____)(____) \__/ (____)(____)    (____/ \__/(__)   (__) (_/\_)\_/\_/(__\_)(____)
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Description: Main cpp file of the eevee software
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "eevee_software.h"
#include "FreeRTOS.h"
#include "task.h"

/* Priorities at which the tasks are created. */
#define eeveeTASK_PRIORITY_1000MS (tskIDLE_PRIORITY + 1)
#define eeveeTASK_PRIORITY_100MS (tskIDLE_PRIORITY + 2)

/* The rate at which data is sent to the queue.  The times are converted from
milliseconds to ticks using the pdMS_TO_TICKS() macro. */
#define eeveeTASK_1000MS pdMS_TO_TICKS(1000UL)
#define eeveeTASK_100MS pdMS_TO_TICKS(100UL)

EeveeSoftware::EeveeSoftware()
{}

void
EeveeSoftware::start(TaskHookType task_hook_1000ms, TaskHookType task_hook_100ms)
{
    xTaskCreate(
        task_1000ms,
        "Task 1000ms",
        configMINIMAL_STACK_SIZE,
        reinterpret_cast<void *>(task_hook_1000ms),
        eeveeTASK_PRIORITY_1000MS,
        NULL);

    xTaskCreate(
        task_100ms,
        "Task 100ms",
        configMINIMAL_STACK_SIZE,
        reinterpret_cast<void *>(task_hook_100ms),
        eeveeTASK_PRIORITY_100MS,
        NULL);

    /* Start the tasks and timer running. */
    vTaskStartScheduler();

    // Not expected to get there:
    // while (true)
    // {}
}

void
EeveeSoftware::task_1000ms(void * taskHookRaw)
{
    TickType_t       xNextWakeTime;
    const TickType_t xBlockTime = eeveeTASK_1000MS;

    TaskHookType taskHook = reinterpret_cast<TaskHookType>(taskHookRaw);

    /* Initialise xNextWakeTime - this only needs to be done once. */
    xNextWakeTime = xTaskGetTickCount();

    for (;;)
    {
        taskHook();
        vTaskDelayUntil(&xNextWakeTime, xBlockTime);
    }
}

void
EeveeSoftware::task_100ms(void * taskHookRaw)
{
    TickType_t       xNextWakeTime;
    const TickType_t xBlockTime = eeveeTASK_100MS;

    TaskHookType taskHook = reinterpret_cast<TaskHookType>(taskHookRaw);

    /* Initialise xNextWakeTime - this only needs to be done once. */
    xNextWakeTime = xTaskGetTickCount();

    for (;;)
    {
        taskHook();
        vTaskDelayUntil(&xNextWakeTime, xBlockTime);
    }
}

float
EeveeSoftware::getSimTime() const
{
    return static_cast<float>(xTaskGetTickCount() / configTICK_RATE_HZ);
}
