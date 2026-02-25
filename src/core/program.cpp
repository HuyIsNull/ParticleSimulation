#include <SDL3/SDL_log.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_timer.h>
#include <SDL3/SDL_assert.h>

#include "core/program.hpp"


Program Program::__instance{ };


Program &Program::GetInstance( ) {
    return Program::__instance;
}


void Program::Init( ) {
    Program &instance = Program::GetInstance( );

    std::size_t width, height;
    width = 800, height = 600;
    SDL_assert( SDL_CreateWindowAndRenderer( "Particle Simulation", width, height, SDL_WINDOW_RESIZABLE, &instance.__window, &instance.__renderer ) && "Initialization failed!" );

    SDL_SetRenderDrawColorFloat( instance.__renderer, 0.f, 0.f, 0.f, 1.f );

    instance.__isRunning = true;
    instance.__simulation.SetSize( width, height );
    instance.__simulation.Reset( );
}


void Program::Update( ) {
    SDL_SetRenderDrawColorFloat( this->__renderer, 0.f, 0.f, 0.f, 1.f );
    SDL_RenderClear( this->__renderer );

    this->__clock.CheckPoint( );
    this->__simulation.Update( 1.f );
    SDL_Log( "%f", this->__clock.GetFPS( ) );

    SDL_RenderPresent( this->__renderer );

    SDL_Delay( 20 );
}


void Program::HandleEvent( const SDL_Event &event ) {
    switch( event.type ) {

        case SDL_EVENT_QUIT:
            this->__isRunning = false;
            break;
    
    }
}


bool Program::IsRunning( ) const {
    return this->__isRunning;
}


SDL_Renderer *Program::GetRenderer( ) const {
    return this->__renderer;
}

