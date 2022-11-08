#include <gtest/gtest.h>
#include <iostream>
#include "../utils/logger_csv.h"
#include <cmath>

namespace test
{

TEST(LoggerCsvTest, Smoke)
{
    LoggerCsv logger {"example_logger_1"};
    logger << "first_col"
           << "second_col" << 3.14f << 5 << 3.0 << 12 << 10 << 9.23;
}

TEST(LoggerCsvTest, SineTest)
{
    LoggerCsv logger {"example_logger_3"};
    logger << "Time" << "Sine wave";
    float const Ts = 0.001f; // 1ms sampling
    float const freq = 5.0f;

    for(unsigned i = 0u; i < 1000u; ++i)
    {
        float const time = i * Ts;
        logger << time << sin(2 * M_PI * freq * time);
    }
}


}   // namespace test