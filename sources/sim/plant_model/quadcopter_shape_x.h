#define EIGEN_RUNTIME_NO_MALLOC 1

#include <cmath>
#include <Eigen/Dense>
#include "eevee/library/integrator.h"
#pragma once
namespace sim
{

static std::size_t constexpr P = 0u;
static std::size_t constexpr Q = 1u;
static std::size_t constexpr R = 2u;

static std::size_t constexpr PHI   = 0u;
static std::size_t constexpr THETA = 1u;
static std::size_t constexpr PSI   = 2u;

static std::size_t constexpr X = 0u;
static std::size_t constexpr Y = 1u;
static std::size_t constexpr Z = 2u;

class QuadcopterShapeX
{
public:
    struct Parameters
    {
        float kv_coeff;
        float kt_coeff;
        float kh_coeff;
        float inertia_x;
        float inertia_y;
        float inertia_z;
        float inertia_p;
        float arm_length;
        float drag_coeff_x;
        float drag_coeff_y;
        float drag_coeff_z;
        float total_mass_inverted;
        float gravity_acceleration;
    };

    QuadcopterShapeX(Time::s const sample_time);

    void
    update(Eigen::Vector4f const & input_signals);

    void
    setParameters(Parameters const & parameters);

    void
    reset();

    Eigen::Vector3f const &
    getAngularRates() const
    {
        return _angular_rates.getValue();
    }

    Eigen::Vector3f const &
    getAngularPosition() const
    {
        return _angular_positions.getValue();
    }

    Eigen::Vector3f const &
    getVelocity() const
    {
        return _velocity.getValue();
    }

    Eigen::Vector3f const &
    getDisplacement() const
    {
        return _displacement.getValue();
    }

private:
    void
    updateAngularRates(
        Eigen::Vector4f const & thrust_p,
        Eigen::Vector4f const & torque_p,
        Eigen::Vector4f const & propeller_omegas);

    void
    updateAngularPosition();

    void
    updateDisplacement(float const total_thrust);

    using IntegratorVector3 = eevee::Integrator<Eigen::Vector3f>;

    IntegratorVector3 _angular_rates;
    IntegratorVector3 _angular_positions;

    IntegratorVector3 _velocity;
    IntegratorVector3 _displacement;

    Parameters _parameters {};
};

}   // namespace sim