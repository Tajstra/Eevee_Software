#include <gtest/gtest.h>
#include "eevee/library/integrator.h"

TEST(IntegratorTest, Test)
{
    Time::s const            sample_time = 1e-3f;
    eevee::Integrator<float> integrator {sample_time};

    integrator(1.0f);

    EXPECT_FLOAT_EQ(integrator.getValue(), 1.0f * sample_time);

    auto const prev_value = integrator.getValue();
    integrator(198572.5f);

    EXPECT_FLOAT_EQ(integrator.getValue(), 198572.5f * sample_time + prev_value);

    integrator.reset();
    EXPECT_FLOAT_EQ(integrator.getValue(), 0.0f);
}