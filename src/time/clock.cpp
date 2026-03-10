#include <SDL3/SDL_stdinc.h>
#include <SDL3/SDL_timer.h>

#include "time/clock.hpp"


namespace hin {

    Clock::Clock( ) : __lastTicks( SDL_GetTicks( ) ) {
    }


    void Clock::CheckPoint( ) {
        this->__lastTicks = SDL_GetTicks( );
        ++this->__count;
    }


    void Clock::Update( ) {
        Uint32 tickSpan = SDL_GetTicks( ) - this->__lastTicks;
        // Uint32 ticks = 0;
        // if( tickSpan < ticks ) {
        //     SDL_Delay( ticks - tickSpan );
        // }
        this->__fps = 1000.f / static_cast<double>( tickSpan );
        this->__averageFPS = this->__averageFPS + ( this->__fps - this->__averageFPS ) /  static_cast<double>( this->__count );
        this->__deltaTime = static_cast<double>( tickSpan ) / 1000.0f;
    }


    void Clock::Reset( ) {
        this->__averageFPS = 0;
        this->__count = 0;
    }


    double Clock::GetFPS( ) const {
        return this->__fps;
    }


    double Clock::GetAverageFPS( ) const {
        return this->__averageFPS;
    }

    double Clock::GetDeltaTime( ) const {
        return this->__deltaTime;
    }


}
