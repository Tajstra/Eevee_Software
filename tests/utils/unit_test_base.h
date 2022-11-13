#include <gtest/gtest.h>
#include <filesystem>
#include "logger_csv.h"

#pragma once

class UnitTestBase : public ::testing::Test
{
public:
    static void
    SetUpTestSuite()
    {
        std::filesystem::remove_all("logs");
    }
};