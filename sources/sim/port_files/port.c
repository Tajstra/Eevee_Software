/*
 * FreeRTOS Kernel V10.4.6
 * Copyright (C) 2021 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
 *
 * SPDX-License-Identifier: MIT
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * https://www.FreeRTOS.org
 * https://github.com/FreeRTOS
 *
 */

/* Standard includes. */
#include <stdio.h>
#include <assert.h>

/* Scheduler includes. */
#include "FreeRTOS.h"
#include "task.h"

#define portMAX_INTERRUPTS ((uint32_t)sizeof(uint32_t) * 8UL) /* The number of bits in an uint32_t. */
#define portNO_CRITICAL_NESTING ((uint32_t)0)

/* The priorities at which the various components of the simulation execute. */
#define portDELETE_SELF_THREAD_PRIORITY THREAD_PRIORITY_TIME_CRITICAL /* Must be highest. */
#define portSIMULATED_INTERRUPTS_THREAD_PRIORITY THREAD_PRIORITY_TIME_CRITICAL
#define portSIMULATED_TIMER_THREAD_PRIORITY THREAD_PRIORITY_HIGHEST
#define portTASK_THREAD_PRIORITY THREAD_PRIORITY_ABOVE_NORMAL

/*
 * Process all the simulated interrupts - each represented by a bit in
 * ulPendingInterrupts variable.
 */
void
prvProcessSimulatedInterrupts(void);

/*
 * Interrupt handlers used by the kernel itself.  These are executed from the
 * simulated interrupt handler thread.
 */
static uint32_t
prvProcessYieldInterrupt(void);
static uint32_t
prvProcessTickInterrupt(void);

/*
 * Exiting a critical section will cause the calling task to block on yield
 * event to wait for an interrupt to process if an interrupt was pended while
 * inside the critical section.  This variable protects against a recursive
 * attempt to obtain pvInterruptEventMutex if a critical section is used inside
 * an interrupt handler itself.
 */
volatile BaseType_t xInsideInterrupt = pdFALSE;

/*-----------------------------------------------------------*/

/* The WIN32 simulator runs each task in a thread.  The context switching is
managed by the threads, so the task stack does not have to be managed directly,
although the task stack is still used to hold an xThreadState structure this is
the only thing it will ever hold.  The structure indirectly maps the task handle
to a thread handle. */
typedef struct
{
    /* Handle of the thread that executes the task. */
    void * pvThread;

    /* Event used to make sure the thread does not execute past a yield point
	between the call to SuspendThread() to suspend the thread and the
	asynchronous SuspendThread() operation actually being performed. */
    void * pvYieldEvent;
} ThreadState_t;

/* Simulated interrupts waiting to be processed.  This is a bit mask where each
bit represents one interrupt, so a maximum of 32 interrupts can be simulated. */
static volatile uint32_t ulPendingInterrupts = 0UL;

/* An event used to inform the simulated interrupt processing thread (a high
priority thread that simulated interrupt processing) that an interrupt is
pending. */
static void * pvInterruptEvent = NULL;

/* Mutex used to protect all the simulated interrupt variables that are accessed
by multiple threads. */
static void * pvInterruptEventMutex = NULL;

/* The critical nesting count for the currently executing task.  This is
initialised to a non-zero value so interrupts do not become enabled during
the initialisation phase.  As each task has its own critical nesting value
ulCriticalNesting will get set to zero when the first task runs.  This
initialisation is probably not critical in this simulated environment as the
simulated interrupt handlers do not get created until the FreeRTOS scheduler is
started anyway. */
static volatile uint32_t ulCriticalNesting = 9999UL;

/* Handlers for all the simulated software interrupts.  The first two positions
are used for the Yield and Tick interrupts so are handled slightly differently,
all the other interrupts can be user defined. */
static uint32_t (*ulIsrHandler[portMAX_INTERRUPTS])(void) = {0};

/* Pointer to the TCB of the currently executing task. */
extern void * volatile pxCurrentTCB;

/* Used to ensure nothing is processed during the startup sequence. */
static BaseType_t xPortRunning = pdFALSE;

/*-----------------------------------------------------------*/

StackType_t *
pxPortInitialiseStack(StackType_t * pxTopOfStack, TaskFunction_t pxCode, void * pvParameters)
{
    ThreadState_t * pxThreadState = NULL;
    int8_t *        pcTopOfStack  = (int8_t *)pxTopOfStack;
    size_t          xStackSize = 1024; /* Set the size to a small number which will get rounded up to the minimum possible. */

    /* In this simulated case a stack is not initialised, but instead a thread
	is created that will execute the task being created.  The thread handles
	the context switching itself.  The ThreadState_t object is placed onto
	the stack that was created for the task - so the stack buffer is still
	used, just not in the conventional way.  It will not be used for anything
	other than holding this structure. */
    pxThreadState = (ThreadState_t *)(pcTopOfStack - sizeof(ThreadState_t));

    configASSERT(pxThreadState->pvThread); /* See comment where TerminateThread() is called. */

    return (StackType_t *)pxThreadState;
}

BaseType_t
xPortStartScheduler(void)
{
    /* Handle all simulated interrupts - including yield requests and
		simulated ticks. */
    prvProcessSimulatedInterrupts();

    /* Would not expect to return from prvProcessSimulatedInterrupts(), so should
	not get here. */
    return 0;
}
/*-----------------------------------------------------------*/

static uint32_t
prvProcessTickInterrupt(void)
{
    uint32_t ulSwitchRequired;

    /* Process the tick itself. */
    configASSERT(xPortRunning);
    ulSwitchRequired = (uint32_t)xTaskIncrementTick();

    return ulSwitchRequired;
}
/*-----------------------------------------------------------*/

void
prvProcessSimulatedInterrupts(void)
{
    uint32_t        ulSwitchRequired, i;
    ThreadState_t * pxThreadState;
    void *          pvObjectList[2];

    /* Going to block on the mutex that ensured exclusive access to the simulated
	interrupt objects, and the event that signals that a simulated interrupt
	should be processed. */
    pvObjectList[0] = pvInterruptEventMutex;
    pvObjectList[1] = pvInterruptEvent;

    /* Create a pending tick to ensure the first task is started as soon as
	this thread pends. */

    xPortRunning = pdTRUE;

    xInsideInterrupt = pdFALSE;

    /* Cannot be in a critical section to get here.  Tasks that exit a
		critical section will block on a yield mutex to wait for an interrupt to
		process if an interrupt was set pending while the task was inside the
		critical section.  xInsideInterrupt prevents interrupts that contain
		critical sections from doing the same. */
    xInsideInterrupt = pdTRUE;

    /* Used to indicate whether the simulated interrupt processing has
		necessitated a context switch to another task/thread. */
    ulSwitchRequired = prvProcessTickInterrupt();

    if (ulSwitchRequired != pdFALSE)
    {
        void * pvOldCurrentTCB;

        pvOldCurrentTCB = pxCurrentTCB;

        /* Select the next task to run. */
        vTaskSwitchContext();
        listGET_OWNER_OF_NEXT_ENTRY( pxCurrentTCB, &( pxReadyTasksLists[ uxTopPriority ] ) );   \
    }
}
/*-----------------------------------------------------------*/

void
vPortDeleteThread(void * pvTaskToDelete)
{
    ThreadState_t * pxThreadState;
    uint32_t        ulErrorCode;

    /* Remove compiler warnings if configASSERT() is not defined. */
    (void)ulErrorCode;

    /* Find the handle of the thread being deleted. */
    pxThreadState = (ThreadState_t *)(*(size_t *)pvTaskToDelete);

    /* Check that the thread is still valid, it might have been closed by
	vPortCloseRunningThread() - which will be the case if the task associated
	with the thread originally deleted itself rather than being deleted by a
	different task. */
    if (pxThreadState->pvThread != NULL)
    {
        configASSERT(ulErrorCode);
        configASSERT(ulErrorCode);
    }
}
/*-----------------------------------------------------------*/

void
vPortCloseRunningThread(void * pvTaskToDelete, volatile BaseType_t * pxPendYield)
{
    ThreadState_t * pxThreadState;
    void *          pvThread;
    uint32_t        ulErrorCode;

    /* Remove compiler warnings if configASSERT() is not defined. */
    (void)ulErrorCode;

    /* Find the handle of the thread being deleted. */
    pxThreadState = (ThreadState_t *)(*(size_t *)pvTaskToDelete);
    pvThread      = pxThreadState->pvThread;

    /* This function will not return, therefore a yield is set as pending to
	ensure a context switch occurs away from this thread on the next tick. */
    *pxPendYield = pdTRUE;

    /* Mark the thread associated with this task as invalid so
	vPortDeleteThread() does not try to terminate it. */
    pxThreadState->pvThread = NULL;
}
/*-----------------------------------------------------------*/

void
vPortEndScheduler(void)
{
    exit(0);
}
/*-----------------------------------------------------------*/

void
vPortGenerateSimulatedInterrupt(uint32_t ulInterruptNumber)
{
    ThreadState_t * pxThreadState = (ThreadState_t *)*((size_t *)pxCurrentTCB);

    configASSERT(xPortRunning);

    if ((ulInterruptNumber < portMAX_INTERRUPTS) && (pvInterruptEventMutex != NULL))
    {
        ulPendingInterrupts |= (1 << ulInterruptNumber);
    }
}
/*-----------------------------------------------------------*/

void
vPortEnterCritical(void)
{
    ulCriticalNesting++;
}
/*-----------------------------------------------------------*/

void
vPortExitCritical(void)
{
    int32_t lMutexNeedsReleasing;

    /* The interrupt event mutex should already be held by this thread as it was
	obtained on entry to the critical section. */
    lMutexNeedsReleasing = pdTRUE;

    if (ulCriticalNesting > portNO_CRITICAL_NESTING)
    {
        ulCriticalNesting--;

        /* Don't need to wait for any pending interrupts to execute if the
		critical section was exited from inside an interrupt. */
        if ((ulCriticalNesting == portNO_CRITICAL_NESTING) && (xInsideInterrupt == pdFALSE))
        {
            /* Were any interrupts set to pending while interrupts were
			(simulated) disabled? */
            if (ulPendingInterrupts != 0UL)
            {
                ThreadState_t * pxThreadState = (ThreadState_t *)*((size_t *)pxCurrentTCB);

                configASSERT(xPortRunning);

                /* Mutex will be released now so the (simulated) interrupt can
				execute, so does not require releasing on function exit. */
                lMutexNeedsReleasing = pdFALSE;
            }
        }
    }

    if (pvInterruptEventMutex != NULL)
    {
        if (lMutexNeedsReleasing == pdTRUE)
        {
            configASSERT(xPortRunning);
        }
    }
}

void
assert_failed(uint8_t * file, uint32_t line)
{
    assert(0u && "File: " && file && "Line:" && line);
}

/*-----------------------------------------------------------*/
