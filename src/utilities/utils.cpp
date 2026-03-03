#include <cstdlib>

#include "utilities/utils.hpp"
#include "math/vector.hpp"


namespace hin {

    float Rand( ) {
        return static_cast<float>( std::rand( ) ) / static_cast< float >( RAND_MAX );
    }


    bool PointCollidedRect( const Vector2f &point, const SDL_FRect &rect ) {
        return point.GetX( ) >= rect.x && point.GetX( ) <= rect.x + rect.w &&
               point.GetY( ) >= rect.y && point.GetY( ) <= rect.y + rect.h;
    }

}


