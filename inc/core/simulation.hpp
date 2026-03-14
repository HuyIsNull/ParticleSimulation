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

    void SetAffectRange( float min, float max );

    void SetSize( float width, float height );

    float GetGravity( ) const;
    void SetGravity( float gravity );

    float GetDamping( ) const;
    void SetDamping( float viscosity );

    void Clear( );


private:

    float __width{ 0 }, __height{ 0 };
    float __gravity{ 1.f }, __viscosity{ 1.f };
    float __minAffectRange{ 0 }, __maxAffectRange{ 0 };

    hin::SimpleGrid<Particle> __grid{ };

    std::vector<ParticleProperties> __properties{ };
    
};
