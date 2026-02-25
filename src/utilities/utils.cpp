#include <cstdlib>

#include "utilities/utils.hpp"


namespace hin {

    float Rand( ) {
        return static_cast<float>( std::rand( ) ) / static_cast< float >( RAND_MAX );
    }


    bool PointCollidedRect( const SDL_FPoint &point, const SDL_FRect &rect ) {
        return point.x >= rect.x && point.x <= rect.x + rect.w &&
               point.y >= rect.y && point.y <= rect.y + rect.h;
    }

}


