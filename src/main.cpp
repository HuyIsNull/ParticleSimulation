#define SDL_MAIN_USE_CALLBACKS 1

#include <SDL3/SDL_error.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_stdinc.h>

#include "core/program.hpp"
#include "math/vector.hpp"


SDL_AppResult SDL_AppInit( void **appstate, int argc, char **argv ) {
    if( !SDL_Init( SDL_INIT_VIDEO ) ) {
        SDL_Log( "Initialize SDL Failed!" );
        return SDL_APP_FAILURE;
    }
    Program::Init( );
    return Program::GetInstance( ).GetState( );
}


SDL_AppResult SDL_AppEvent( void *appstate, SDL_Event *event ) {
    Program::GetInstance( ).HandleEvent( *event );
    return Program::GetInstance( ).IsRunning( ) ? SDL_APP_CONTINUE : SDL_APP_SUCCESS;
}


SDL_AppResult SDL_AppIterate( void *appstate ) {
    Program::GetInstance( ).Update( );
    return SDL_APP_CONTINUE;
}


void SDL_AppQuit( void *appstate, SDL_AppResult result ) {
    SDL_Quit( );
}

