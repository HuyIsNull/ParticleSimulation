#pragma once

#include <SDL3/SDL_rect.h>

#include "math/vector.hpp"


namespace hin {
    
    float Rand( );

    bool PointCollidedRect( const Vector2f &point, const SDL_FRect &rect );

}

