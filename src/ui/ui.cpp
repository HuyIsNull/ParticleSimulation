#include <SDL3/SDL_events.h>
#include <SDL3/SDL_mouse.h>
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>

#include "ui/ui.hpp"
#include "utilities/utils.hpp"


namespace hin {

    UI::UI( SDL_Texture *texture, const SDL_FRect &dstRect ) 
        : __texture{ texture }, __dstRect{ dstRect } {
    }


    void UI::HandleEvent( SDL_Event &event ) {

        switch( event.type ) {
            
            case SDL_EVENT_MOUSE_MOTION:
                this->__isHovered = PointCollidedRect( SDL_FPoint{ event.motion.x, event.motion.y }, this->__dstRect );
            break;


            case SDL_EVENT_MOUSE_BUTTON_UP:
                if( event.button.button == SDL_BUTTON_LEFT &&
                        PointCollidedRect( SDL_FPoint{ event.button.x, event.button.y }, this->__dstRect ) &&
                        event.button.clicks == 1 ) {

                    this->__isClicked = true;
                }
            break;
        }
    }


    void UI::Render( SDL_Renderer *renderer ) {
        SDL_RenderTexture( renderer, this->__texture, nullptr, &this->__dstRect );
    }


    bool UI::IsHoverred( ) const {
        return this->__isHovered;
    }

    bool UI::IsClicked( ) const {
        return this->__isClicked;
    }

}

