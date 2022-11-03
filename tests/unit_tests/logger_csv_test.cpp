#include <gtest/gtest.h>
#include <iostream>
#include "../utils/logger_csv.h"

namespace test
{

TEST(LoggerCsvTest, Smoke)
{
    LoggerCsv logger {"example_logger"};
    logger << "first_col"
           << "second_col" << 3.14f << 5 << 3.0 << 12 << 10 << 9.23;

    std::ofstream result {"logs/log_example_logger.csv"};
}

TEST(LoggerCsvTest, AssertTest)
{
    LoggerCsv logger {"example_logger"};
    logger << "string 1" << 1.0f;
    // EXPECT_DEATH({logger << "string 2";}, "Column name written when inhibited!");
}

}   // namespace test