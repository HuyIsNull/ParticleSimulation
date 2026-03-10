#pragma once

#include <cstddef>
#include <vector>

#include "core/particle.hpp"
#include "core/particle_group.hpp"
#include "core/particle_properties.hpp"
#include "ds/simple_grid.hpp"


class Simulation {

public:

    Simulation( ) = default;
    virtual ~Simulation( ) = default;

    void Update( float delta );

    void AddParticles( std::size_t count, const ParticleProperties &properties );

    void Load( const char *filepath );

    void SetSize( float width, float height );

    float GetGravity( ) const;

    void Clear( );


private:

    float __width{ 0 }, __height{ 0 };
    float __gravity{ 1.f };

    hin::SimpleGrid<Particle> __grid{ };

    std::vector<ParticleProperties> __properties{ };
    
};
