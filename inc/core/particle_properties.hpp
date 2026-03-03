#pragma once

#include <cstddef>
#include <vector>

#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_stdinc.h>


struct ParticleProperties {

    Uint8 type{ };
    std::size_t count{ };
    SDL_FColor color{ };
    float affectRange{ };
    std::vector<float> interactions{ };

};
