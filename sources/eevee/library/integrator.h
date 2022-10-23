//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                  (C) Copyright 2022 Konrad Tajstra. All rights reserved.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                     ____  ____  _  _  ____  ____      ____   __  ____  ____  _  _   __   ____  ____
//                    (  __)(  __)/ )( \(  __)(  __)    / ___) /  \(  __)(_  _)/ )( \ / _\ (  _ \(  __)
//                     ) _)  ) _) \ \/ / ) _)  ) _)     \___ \(  O )) _)   )(  \ /\ //    \ )   / ) _)
//                    (____)(____) \__/ (____)(____)    (____/ \__/(__)   (__) (_/\_)\_/\_/(__\_)(____)
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Description: Integrator
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "eevee_types.h"

namespace eevee
{
    template <typename Tin, typename Tout = Tin>
    class Integrator
    {
    public:
        Integrator(Time::s const sample_time) : _sample_time(sample_time)
        {
        }

        Tout const &
        operator()(Tin const &input)
        {
            _state += input * _sample_time;
            return _state;
        }

        void
        reset()
        {
            _state = Tout();
        }

        Tout const &
        getValue() const
        {
            return _state;
        }

    private:
        Time::s const _sample_time;
        Tout _state{};
    };
} // namespace eevee