#pragma once

#include <gtest/gtest.h>
#include "application_software.h"

extern ApplicationSoftware app_software;

class SimulatedIntegrationTest : public ::testing::Test
{
public:
    SimulatedIntegrationTest()
    {}

protected:
    virtual void
    SetUp() override
    {}

    static void
    SetUpTestSuite()
    {
        // application_software.initialize();
    }

    static void
    TearDownTestSuite()
    {
        // vTaskEndScheduler();
    }

    void
    executeSystick();

    static ApplicationSoftware &
    appSoftware()
    {
        return app_software;
    }
};
