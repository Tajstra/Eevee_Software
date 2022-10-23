#define EIGEN_RUNTIME_NO_MALLOC 1

#include <cmath>
#include <Eigen/Dense>
#include "eevee/library/integrator.h"
#pragma once
namespace sim
{

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
        };

        QuadcopterShapeX(Time::s const sample_time);

        void
        update(Eigen::Vector4f const &input_signals);

        void
        setParameters(Parameters const &parameters);

    private:
        void
        updateAngularRates(Eigen::Vector4f const &input_signals);

        static std::size_t constexpr P = 0u;
        static std::size_t constexpr Q = 1u;
        static std::size_t constexpr R = 2u;

        using IntegratorVector3 = eevee::Integrator<Eigen::Matrix<float, 3, 1>>;

        IntegratorVector3 _angular_rates;
        IntegratorVector3 _angular_displacement;

        Eigen::Vector3f _displacement{};
        Eigen::Vector3f _velocity{};

        Parameters _parameters{};
    };

} // namespace sim