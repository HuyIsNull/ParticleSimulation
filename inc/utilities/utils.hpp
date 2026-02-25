#pragma once

#include <SDL3/SDL_rect.h>


namespace hin {
    
    float Rand( );

    bool PointCollidedRect( const SDL_FPoint &point, const SDL_FRect &rect );

}

