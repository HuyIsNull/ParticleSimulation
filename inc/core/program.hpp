#pragma once

#include <SDL3/SDL_events.h>
#include <SDL3/SDL_video.h>
#include <SDL3/SDL_render.h>

#include "core/simulation.hpp"

#include "time/clock.hpp"
#include "ui/ui_manager.hpp"


class Program {

public:

    static void Init( );
    static Program &GetInstance( );

    virtual ~Program( ) = default;

    void Update( );

    void HandleEvent( const SDL_Event &event );

    bool IsRunning( ) const;

    SDL_Renderer *GetRenderer( ) const;


private:

    Program( ) = default;

    static Program __instance;

    SDL_Window *__window{ nullptr };
    SDL_Renderer *__renderer{ nullptr };

    bool __isRunning{ false };
    hin::Clock __clock{ };

    Simulation __simulation{ };
    hin::UIManager __uiManager{ };

};

