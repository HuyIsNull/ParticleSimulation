#pragma once

#include <vector>

#include <SDL3/SDL_render.h>
#include <SDL3/SDL_events.h>


namespace hin {

    class UI;
   

    class UIManager {

    public:

        UIManager( ) = default;
        virtual ~UIManager( ) = default;

        void Update( );
        void HandleEvent( SDL_Event &event );
        void Render( SDL_Renderer *renderer );

        void AddUI( UI *ui );
        void RemoveUI( UI *ui );

    
    private:

        std::vector<UI*> __uis{ };

    };

}

