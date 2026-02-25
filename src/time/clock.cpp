#include <SDL3/SDL_stdinc.h>
#include <SDL3/SDL_timer.h>

#include "time/clock.hpp"


namespace hin {

    Clock::Clock( ) {
        this->Update( );
    }


    void Clock::Update( ) {
        this->__lastTicks = SDL_GetTicks( );
    }


    void Clock::CheckPoint( ) {
        this->__lastTicks = SDL_GetTicks( );
    }


    double Clock::GetDeltaTime( Uint32 fps ) {
        Uint32 ticks = 1000 / fps;
        Uint32 tickSpan = SDL_GetTicks( ) - this->__lastTicks;
        if( tickSpan < ticks ) {
            SDL_Delay( ticks - tickSpan );
        } else {
            ticks = tickSpan;
        }

        return static_cast<double>( ticks ) / 1000.0f;
    }


    float Clock::GetFPS( ) {
        Uint32 ticks = SDL_GetTicks( ) - this->__lastTicks;
        return 1000.f / static_cast<float>( ticks ); 
    }

}
