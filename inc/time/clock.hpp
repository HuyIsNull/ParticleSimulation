#pragma once

#include <SDL3/SDL_stdinc.h>


namespace hin {

    class Clock {
    
    public:

        Clock( );

        void Update( );

        void CheckPoint( );
        
        double GetDeltaTime( Uint32 fps );

        float GetFPS( );


    private:
    
        Uint32 __lastTicks{ };

    };

}
