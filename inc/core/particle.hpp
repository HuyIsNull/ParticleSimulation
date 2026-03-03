#pragma once

#include <SDL3/SDL_stdinc.h>

#include "math/vector.hpp"


struct Particle {

    Uint8 type{ };
    hin::Vector2f position{ };
    hin::Vector2f velocity{ };


    constexpr operator hin::Vector2f( ) const {
        return this->position;
    }


    bool operator==( const Particle &particle ) const = default;

};

