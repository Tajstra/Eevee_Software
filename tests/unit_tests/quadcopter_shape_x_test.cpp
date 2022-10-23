#include <gtest/gtest.h>
#include <iostream>
#include "sim/plant_model/quadcopter_shape_x.h"

TEST(QuadcopterShapeX_Test, Test)
{
    sim::QuadcopterShapeX quadcopter {1e-3f};
    quadcopter.update({0,0,0,0});
}