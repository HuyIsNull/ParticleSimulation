#include <SDL3/SDL_init.h>
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_stdinc.h>
#include <SDL3/SDL_timer.h>
#include <SDL3/SDL_assert.h>
#include <SDL3/SDL_video.h>

#include "core/program.hpp"


static const char *FILE_PATH = "config.json";


Program Program::__instance{ };


Program &Program::GetInstance( ) {
    return Program::__instance;
}


void Program::Init( ) {
    Program &instance = Program::GetInstance( );

    std::size_t width, height;
    width = 800, height = 600;
    if( !SDL_CreateWindowAndRenderer( "Particle Simulation", width, height, SDL_WINDOW_FULLSCREEN, &instance.__window, &instance.__renderer ) ) {
        SDL_Log( "Create Window And Renderer Failed: %s", SDL_GetError( ) );
    }

    {
        int numDisplays;
        SDL_DisplayID *displayID = SDL_GetDisplays( &numDisplays );
        SDL_DisplayMode **modes = SDL_GetFullscreenDisplayModes( *displayID, NULL );
        SDL_DisplayMode *mode = modes[ 0 ];

        width = mode->w;
        height = mode->h;

        SDL_free( modes );
        SDL_free( displayID );
    }

    SDL_SetRenderDrawColorFloat( instance.__renderer, 0.f, 0.f, 0.f, 1.f );

    instance.__isRunning = true;
    instance.__simulation.SetSize( static_cast<float>( width ), static_cast<float>( height ) ); 
    instance.__simulation.Load( FILE_PATH );
}


void Program::Update( ) {
    SDL_SetRenderTarget( this->__renderer, nullptr );
    SDL_SetRenderDrawColorFloat( this->__renderer, 0.f, 0.f, 0.f, 1.f );
    SDL_RenderClear( this->__renderer );

    this->__clock.CheckPoint( );
    this->__simulation.Update( 1.f );
    SDL_Log( "fps: %f", this->__clock.GetFPS( ) );

    SDL_RenderPresent( this->__renderer );

    SDL_Delay( 20 );
}


void Program::HandleEvent( const SDL_Event &event ) {
    switch( event.type ) {

        case SDL_EVENT_QUIT:
            this->__isRunning = false;
            break;
    

        case SDL_EVENT_KEY_DOWN:
            if( event.key.key == SDLK_ESCAPE ) {
                this->__simulation.Load( FILE_PATH );
            }
            break;
    }
}


bool Program::IsRunning( ) const {
    return this->__isRunning;
}


SDL_Renderer *Program::GetRenderer( ) const {
    return this->__renderer;
}

SDL_AppResult Program::GetState( ) {
    return this->__state;
}

void Program::SetState( SDL_AppResult state ) {
    this->__state = state;
}

