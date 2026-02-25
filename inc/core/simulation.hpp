#pragma once

#include <cstddef>
#include <vector>

#include "core/particle_group.hpp"


class Simulation {

public:

    Simulation( ) = default;
    virtual ~Simulation( ) = default;

    void Update( float delta );

    void Reset( );

    void SetSize( std::size_t width, std::size_t height );

    float GetGravity( ) const;


private:

    std::size_t __width{ 0 }, __height{ 0 };
    float __gravity{ 1.f };
    std::vector<ParticleGroup> __groups{ };

};
