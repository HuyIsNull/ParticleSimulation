#pragma once

#include <cstddef>
#include <vector>

#include "core/particle.hpp"
#include "core/particle_group.hpp"
#include "core/particle_properties.hpp"


class Simulation {

public:

    Simulation( ) = default;
    virtual ~Simulation( ) = default;

    void Update( float delta );

    void AddParticles( std::size_t count, const ParticleProperties &properties );

    void Reset( );

    void Load( const char *filepath );

    void SetSize( float width, float height );

    float GetGravity( ) const;


private:

    float __width{ 0 }, __height{ 0 };
    float __gravity{ 1.f };

    // hin::Grid<Particle> __grid{ };
    std::vector<Particle> __particles{ };

    std::vector<ParticleProperties> __properties{ };
    
};
