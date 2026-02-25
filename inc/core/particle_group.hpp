#pragma once

#include "core/particle.hpp"
#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_stdinc.h>
#include <cstddef>
#include <initializer_list>
#include <vector>


class Simulation;

class ParticleGroup {

public:

    ParticleGroup( ) = default;
    virtual ~ParticleGroup( ) = default;

    void UpdateParticle( Simulation &sim, std::size_t ind, ParticleGroup &group, std::size_t beginInd );

    void Reset( Uint16 type, SDL_FColor color, float affectRange, std::size_t n, std::size_t width, std::size_t height, std::initializer_list<float> interactions );
    void Reserve( std::size_t n );

    Uint16 GetType( ) const;
    SDL_FColor &GetColor( );
    float GetAffectRange( ) const;
    std::vector<float> &GetInteractions( );
    std::vector<Particle> &GetParticles( );


private:

    Uint16 __type{ };
    SDL_FColor __color{ };
    float __affectRange{ };
    std::vector<float> __interactions{ };
    std::vector<Particle> __particles{ };

};
