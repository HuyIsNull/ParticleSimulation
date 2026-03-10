#pragma once

#include <SDL3/SDL_stdinc.h>


namespace hin {

    class Clock {
    
    public:

        Clock( );

        void Update( );
        void CheckPoint( );
        void Reset( );

        double GetFPS( ) const;

        double GetAverageFPS( ) const;
        double GetDeltaTime( ) const;


    private:
    
        Uint32 __lastTicks{ 0 };
        Uint64 __count{ 0 };
        double __fps{ 0 },
               __averageFPS{ 0 },
               __deltaTime{ 0 };

    };

}
