#include "quadcopter_shape_x.h"

namespace sim
{
QuadcopterShapeX::QuadcopterShapeX(Time::s const sample_time) :
    _angular_rates(sample_time), _angular_positions(sample_time), _velocity(sample_time), _displacement(sample_time)
{}

void
QuadcopterShapeX::update(Eigen::Vector4f const & input_signals)
{
    Eigen::Vector4f const propeller_omegas = input_signals * _parameters.kv_coeff * M_PI / 30.0f;

    Eigen::Vector4f propeller_omegas_squared {};

    std::transform(
        propeller_omegas.begin(), propeller_omegas.end(), propeller_omegas_squared.begin(), [](float x) { return x * x; });

    // Calculate propellers thrusts and torques
    Eigen::Vector4f const thrust_p = propeller_omegas_squared * _parameters.kt_coeff;
    Eigen::Vector4f const torque_p = propeller_omegas_squared * _parameters.kh_coeff;

    updateAngularRates(thrust_p, torque_p, propeller_omegas);
    updateAngularPosition();
    float const total_thrust = thrust_p.sum();
    updateDisplacement(total_thrust);
}

void
QuadcopterShapeX::setParameters(Parameters const & parameters)
{
    _parameters = parameters;
}

void
QuadcopterShapeX::reset()
{
    _angular_rates.reset();
    _angular_positions.reset();
    _velocity.reset();
    _displacement.reset();
}

void
QuadcopterShapeX::updateAngularRates(
    Eigen::Vector4f const & thrust_p,
    Eigen::Vector4f const & torque_p,
    Eigen::Vector4f const & propeller_omegas)
{

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

    Eigen::Vector3f const & epsilon = {epsilon_x, epsilon_y, epsilon_z};
    _angular_rates(epsilon);
}

void
QuadcopterShapeX::updateAngularPosition()
{
    float const phi_temp   = _angular_positions.getValue()[PHI];
    float const theta_temp = _angular_positions.getValue()[THETA];

    // Phi prim calculation:
    float const phi_prim_component_p = _angular_rates.getValue()[P];
    float const phi_prim_component_q = _angular_rates.getValue()[Q] * std::sin(phi_temp) * std::tan(theta_temp);
    float const phi_prim_component_r = _angular_rates.getValue()[R] * std::cos(phi_temp) * std::tan(theta_temp);

    float const phi_prim = phi_prim_component_p + phi_prim_component_q + phi_prim_component_r;

    // Theta prim calculation:
    float const theta_prim_component_q = _angular_rates.getValue()[Q] * std::cos(phi_temp);
    float const theta_prim_component_r = _angular_rates.getValue()[R] * std::sin(phi_temp);

    float const theta_prim = theta_prim_component_q - theta_prim_component_r;

    // Psi prim calculation:
    float const psi_prim_component_q = _angular_rates.getValue()[Q] * std::sin(phi_temp) / std::cos(theta_temp);
    float const psi_prim_component_r = _angular_rates.getValue()[R] * std::cos(phi_temp) / std::cos(theta_temp);

    float const psi_prim = psi_prim_component_q + psi_prim_component_r;

    Eigen::Vector3f const & angular_rates_transformed = {phi_prim, theta_prim, psi_prim};
    _angular_positions(angular_rates_transformed);
}

void
QuadcopterShapeX::updateDisplacement(float const total_thrust)
{
    float const phi_temp   = _angular_positions.getValue()[PHI];
    float const theta_temp = _angular_positions.getValue()[THETA];
    float const psi_temp   = _angular_positions.getValue()[PSI];

    float const thrust_x_coeff_1 = std::cos(phi_temp) * std::sin(theta_temp) * std::cos(psi_temp);
    float const thrust_x_coeff_2 = std::sin(phi_temp) * std::sin(psi_temp);
    float const thrust_x         = (thrust_x_coeff_1 + thrust_x_coeff_2) * total_thrust;
    float const drag_x           = _velocity.getValue()[X] * _parameters.drag_coeff_x;
    float const acceleration_x   = (thrust_x - drag_x) * _parameters.total_mass_inverted;

    float const thrust_y_coeff_1 = std::cos(phi_temp) * std::sin(theta_temp) * std::sin(psi_temp);
    float const thrust_y_coeff_2 = std::sin(phi_temp) * std::cos(psi_temp);
    float const thrust_y         = (thrust_y_coeff_1 - thrust_y_coeff_2) * total_thrust;
    float const drag_y           = _velocity.getValue()[Y] * _parameters.drag_coeff_y;
    float const acceleration_y   = (thrust_y - drag_y) * _parameters.total_mass_inverted;

    float const thrust_z_coeff = std::cos(phi_temp) * std::cos(theta_temp);
    float const thrust_z       = thrust_z_coeff * total_thrust;
    float const drag_z         = _velocity.getValue()[Z] * _parameters.drag_coeff_z;
    float const acceleration_z = (thrust_z - drag_z) * _parameters.total_mass_inverted - _parameters.gravity_acceleration;

    Eigen::Vector3f const & acceleration = {acceleration_x, acceleration_y, acceleration_z};
    _velocity(acceleration);
    _displacement(_velocity.getValue());
}

}   // namespace sim