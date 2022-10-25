#include "quadcopter_shape_x.h"

namespace sim
{
QuadcopterShapeX::QuadcopterShapeX(Time::s const sample_time) :
    _angular_rates(sample_time), _angular_displacement(sample_time)
{}

void
QuadcopterShapeX::update(Eigen::Vector4f const & input_signals)
{
    updateAngularRates(input_signals);
}

void
QuadcopterShapeX::setParameters(Parameters const & parameters)
{
    _parameters = parameters;
}

void
QuadcopterShapeX::updateAngularRates(Eigen::Vector4f const & input_signals)
{
    Eigen::Vector4f const propeller_omegas = input_signals * _parameters.kv_coeff * M_PI / 30.0f;

    Eigen::Vector4f propeller_omegas_squared {};

    std::transform(
        propeller_omegas.begin(), propeller_omegas.end(), propeller_omegas_squared.begin(), [](float x) { return x * x; });

    // Calculate propellers thrusts and torques
    Eigen::Vector4f const thrust_p = propeller_omegas_squared * _parameters.kt_coeff;
    Eigen::Vector4f const torque_p = propeller_omegas_squared * _parameters.kh_coeff;

    // Angular acceleration calculation:
    float const torque_x = (-thrust_p[0u] + thrust_p[1u] + thrust_p[2u] - thrust_p[3u]) * _parameters.arm_length;
    float const torque_y = (thrust_p[0u] + thrust_p[1u] - thrust_p[2u] - thrust_p[3u]) * _parameters.arm_length;
    float const torque_z = (torque_p[0u] - torque_p[1u] + torque_p[2u] - torque_p[3u]);

    float const omega_g = -propeller_omegas[0u] + propeller_omegas[1u] - propeller_omegas[2u] + propeller_omegas[3u];

    float const torque_gyro_x = omega_g * _angular_rates.getValue()[Q] * _parameters.inertia_p;
    float const torque_gyro_y = omega_g * _angular_rates.getValue()[P] * _parameters.inertia_p;

    float const torque_inertia_x =
        _angular_rates.getValue()[Q] * _angular_rates.getValue()[R] * (_parameters.inertia_y - _parameters.inertia_z);
    float const torque_inertia_y =
        _angular_rates.getValue()[P] * _angular_rates.getValue()[R] * (_parameters.inertia_z - _parameters.inertia_x);
    float const torque_inertia_z =
        _angular_rates.getValue()[P] * _angular_rates.getValue()[Q] * (_parameters.inertia_x - _parameters.inertia_y);

    float const epsilon_x = (torque_inertia_x + torque_x - torque_gyro_x) / _parameters.inertia_x;
    float const epsilon_y = (torque_inertia_y + torque_y + torque_gyro_y) / _parameters.inertia_y;
    float const epsilon_z = (torque_inertia_z + torque_z) / _parameters.inertia_z;

    Eigen::Vector3f const epsilon = {epsilon_x, epsilon_y, epsilon_z};
    _angular_rates(epsilon);
}
}   // namespace sim