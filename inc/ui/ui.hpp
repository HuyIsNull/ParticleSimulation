#pragma once

#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_render.h>


namespace hin {

    class UI {

    public:

        UI( SDL_Texture *texture, const SDL_FRect &dstRect );
        virtual ~UI( ) = default;

        virtual void Update( ) = 0;
        virtual void HandleEvent( SDL_Event &event ) final;
        void Render( SDL_Renderer *renderer );

        bool IsHoverred( ) const;
        bool IsClicked( ) const;


    private:
        
        SDL_Texture *__texture{ nullptr };
        SDL_FRect __dstRect{ };
        bool __isHovered{ false };
        bool __isClicked{ false };

    };

}
