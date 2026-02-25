#pragma once

#include <SDL3/SDL_render.h>

#include "ui/ui.hpp"


namespace hin {

    class Button : public UI {

    public:

        Button( SDL_Texture *texture, const SDL_FRect &dstRect );

        void Update( ) override;

    };

}
