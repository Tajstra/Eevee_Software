#pragma once

#include <gtest/gtest.h>
#include "application_software.h"

extern ApplicationSoftware app_software;

class SimulatedIntegrationTest : public ::testing::Test
{
public:
    SimulatedIntegrationTest()
    {
    }

    static void integrationTestTask(void *parameters)
    {
        (void)parameters;
        unsigned result = RUN_ALL_TESTS();
        // Terminate scheduler when tests are over:
        exit(result);
    }

protected:
    virtual void SetUp() override
    {
    }

    static void SetUpTestSuite()
    {
        // application_software.initialize();
    }

    static void TearDownTestSuite()
    {
        // vTaskEndScheduler();
    }

    static ApplicationSoftware &
    appSoftware()
    {
        return app_software;
    }
};
