#pragma once

#include <type_traits>
#include <cstdint>


namespace hin {

    template<typename T>
        requires std::is_arithmetic_v<T>
    constexpr T InvSqrtQuake( T n ) {
        union {
            float f;
            uint32_t i;
        } conv;

        float x2;
        const float threehalfs = 1.5F;

        x2 = n * 0.5F;
        conv.f  = n;
        conv.i  = 0x5f3759df - ( conv.i >> 1 );
        conv.f  = conv.f * ( threehalfs - ( x2 * conv.f * conv.f ) );
        return conv.f;
    }

}
