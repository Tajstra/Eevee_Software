#include <iostream>
#include "sim/plant_model/quadcopter_shape_x.h"
#include "utils/unit_test_base.h"

namespace test
{

class QuadcopterShapeX_Test : public UnitTestBase
{
public:

    void
    SetUp() override
    {
        logger_disp << "Time"
                    << "Displacement X"
                    << "Displacement Y"
                    << "Displacement Z";
        logger_vel << "Time"
                   << "Velocity X"
                   << "Velocity Y"
                   << "Velocity Z";
        logger_rate << "Time"
                    << "P"
                    << "Q"
                    << "R";
        logger_angle << "Time"
                     << "Phi"
                     << "Theta"
                     << "Psi";
    }

    void
    TearDown() override
    {}

protected:
    sim::QuadcopterShapeX::Parameters
    getDefaultParams() const
    {
        sim::QuadcopterShapeX::Parameters params {};
        params.kv_coeff             = 1400.0f;
        params.kt_coeff             = 2.98e-6f;
        params.kh_coeff             = 1.14e-7f;
        params.inertia_x            = 4.856e-3f;
        params.inertia_y            = 4.856e-3f;
        params.inertia_z            = 8.801e-3f;
        params.inertia_p            = 3.357e-5f;
        params.arm_length           = 0.225f;
        params.drag_coeff_x         = 0.25f;
        params.drag_coeff_y         = 0.25f;
        params.drag_coeff_z         = 0.25f;
        params.total_mass_inverted  = 1.0f / 0.468f;
        params.gravity_acceleration = 9.81f;

        return params;
    }

    void
    update(Time::s const time)
    {
        for (unsigned i = 0; i < static_cast<unsigned>(time / sampling_time); ++i)
        {
            quadcopter.update(input_signals);
            logger_disp << simulation_time << quadcopter.getDisplacement()[sim::X] << quadcopter.getDisplacement()[sim::Y]
                        << quadcopter.getDisplacement()[sim::Z];
            logger_vel << simulation_time << quadcopter.getVelocity()[sim::X] << quadcopter.getVelocity()[sim::Y]
                       << quadcopter.getVelocity()[sim::Z];
            logger_rate << simulation_time << quadcopter.getAngularRates()[sim::P] << quadcopter.getAngularRates()[sim::Q]
                        << quadcopter.getAngularRates()[sim::R];
            logger_angle << simulation_time << quadcopter.getAngularPosition()[sim::PHI]
                         << quadcopter.getAngularPosition()[sim::THETA] << quadcopter.getAngularPosition()[sim::PSI];

            simulation_time += sampling_time;
        }
    }

    Time::s const                           sampling_time = 1e-3f;
    Time::s                                 simulation_time {};
    sim::QuadcopterShapeX                   quadcopter {sampling_time};
    sim::QuadcopterShapeX::Parameters const default_parameters = {};
    Eigen::Vector4f                         input_signals {};
    LoggerCsv                               logger_disp {"quadcopter_displacement"};
    LoggerCsv                               logger_vel {"quadcopter_velocity"};
    LoggerCsv                               logger_rate {"quadcopter_angular_rate"};
    LoggerCsv                               logger_angle {"quadcopter_angle"};
};

TEST_F(QuadcopterShapeX_Test, SmokeTest)
{
    quadcopter.setParameters(getDefaultParams());

    // V1, V2, V3, V4 equal so no angle change expected
    input_signals = {4.25f, 4.25f, 4.25f, 4.25f};
    update(1.0f);
    EXPECT_NEAR(quadcopter.getAngularPosition()[sim::PHI], 0.0f, 1e-5f);
    EXPECT_NEAR(quadcopter.getAngularPosition()[sim::THETA], 0.0f, 1e-5f);
    EXPECT_NEAR(quadcopter.getAngularPosition()[sim::PSI], 0.0f, 1e-5f);

    EXPECT_NEAR(quadcopter.getDisplacement()[sim::X], 0.0f, 1e-5f);
    EXPECT_NEAR(quadcopter.getDisplacement()[sim::Y], 0.0f, 1e-5f);
    // Expect some change in Z due to gravity:
    EXPECT_NEAR(quadcopter.getDisplacement()[sim::Z], 0.0f, 5e-2f);

    quadcopter.reset();

    // V1 and V4 lower than V2 and V3, expect change only in phi angle (thus displacement changed in y)
    input_signals = {4.20f, 4.25f, 4.25f, 4.20f};
    update(1.0f);
    // Phi angle deduced heuristically:
    EXPECT_NEAR(quadcopter.getAngularPosition()[sim::PHI], 1.26f, 1e-2f);
    EXPECT_NEAR(quadcopter.getAngularPosition()[sim::THETA], 0.0f, 1e-5f);
    EXPECT_NEAR(quadcopter.getAngularPosition()[sim::PSI], 0.0f, 1e-5f);

    EXPECT_NEAR(quadcopter.getDisplacement()[sim::X], 0.0f, 1e-5f);
    // Y displacement deduced heuristically:
    EXPECT_NEAR(quadcopter.getDisplacement()[sim::Y], -0.87f, 1e-2f);
    // Expect some change in Z due to gravity:
    EXPECT_NEAR(quadcopter.getDisplacement()[sim::Z], -0.2f, 0.05f);

    quadcopter.reset();

    // V1 and V2 lower than V3 and V4, expect change only in theta angle (thus displacement changed in x)
    input_signals = {4.20f, 4.20f, 4.25f, 4.25f};
    update(1.0f);
    EXPECT_NEAR(quadcopter.getAngularPosition()[sim::PHI], 0.0f, 1e-5f);
    // Theta angle deduced heuristically:
    EXPECT_NEAR(quadcopter.getAngularPosition()[sim::THETA], -1.26f, 1e-2f);
    EXPECT_NEAR(quadcopter.getAngularPosition()[sim::PSI], 0.0f, 1e-5f);

    // Y displacement deduced heuristically:
    EXPECT_NEAR(quadcopter.getDisplacement()[sim::X], -0.87f, 1e-2f);
    EXPECT_NEAR(quadcopter.getDisplacement()[sim::Y], 0.0f, 1e-5f);
    // Expect some change in Z due to gravity:
    EXPECT_NEAR(quadcopter.getDisplacement()[sim::Z], -0.2f, 0.05f);

    quadcopter.reset();

    // V1 and V3 lower than V2 and V4, expect change only in psi angle (no displacement changed)
    input_signals = {4.00f, 4.25f, 4.00f, 4.25f};
    update(1.0f);
    EXPECT_NEAR(quadcopter.getAngularPosition()[sim::PHI], 0.0f, 1e-5f);
    EXPECT_NEAR(quadcopter.getAngularPosition()[sim::THETA], 0.0f, 1e-5f);
    // Psi angle deduced heuristically:
    EXPECT_NEAR(quadcopter.getAngularPosition()[sim::PSI], -0.58f, 1e-2f);

    // No displacement changed:
    EXPECT_NEAR(quadcopter.getDisplacement()[sim::X], 0.0f, 1e-5f);
    EXPECT_NEAR(quadcopter.getDisplacement()[sim::Y], 0.0f, 1e-5f);
    // Expect some change in Z due to gravity:
    EXPECT_NEAR(quadcopter.getDisplacement()[sim::Z], -0.2f, 0.05f);

    quadcopter.reset();
}

}   // namespace test