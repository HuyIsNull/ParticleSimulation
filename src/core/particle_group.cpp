#include <cstdlib>

#include <SDL3/SDL_stdinc.h>
#include <vector>

#include "core/particle_group.hpp"

#include "core/particle.hpp"
#include "core/simulation.hpp"
#include "utilities/utils.hpp"


void ParticleGroup::UpdateParticle( Simulation &sim, std::size_t ind, ParticleGroup &group, std::size_t beginInd ) {
    Particle &particle = this->__particles[ ind ];
    const float &interaction = group.GetInteractions( )[ group.GetType( ) ],
                &otherInteraction = group.GetInteractions( )[ this->GetType( ) ];

    for( auto other = group.GetParticles( ).begin( ) + beginInd; other != group.GetParticles( ).end( ); other++ ) {
        float distX = particle.position.x - other->position.x,
              distY = particle.position.y - other->position.y;
        float dist = SDL_sqrtf( distX * distX + distY * distY );

        if( dist == 0.f )
            continue;

        float force = sim.GetGravity( ) / ( dist * dist );
        float forceX = force * ( distX / dist ),
              forceY = force * ( distY / dist );

        if( dist < this->GetAffectRange( ) ) {
            particle.velocity.x += ( forceX * interaction );
            particle.velocity.y += ( forceY * interaction );
        }
        if( dist < group.GetAffectRange( ) ) { 
            other->velocity.x += ( -forceX * otherInteraction );
            other->velocity.y += ( -forceY * otherInteraction );
        }
    }
}


void ParticleGroup::Reset( Uint16 type, SDL_FColor color, float affectRange, std::size_t n, std::size_t width, std::size_t height, std::initializer_list<float> interactions ) {
    this->__type = type;
    this->__color = color;
    this->__affectRange = affectRange;
    this->__interactions = interactions;
    this->Reserve( n );
    for( std::size_t i = 0; i < n; i++ ) {
        this->__particles.emplace_back( SDL_FPoint{ hin::Rand( ) * width, hin::Rand( ) * height }, SDL_FPoint{ 0, 0 } );
    }
}


void ParticleGroup::Reserve( std::size_t n ) {
    this->__particles.reserve( n );
}


Uint16 ParticleGroup::GetType( ) const {
    return this->__type;
}


SDL_FColor &ParticleGroup::GetColor( ) {
    return this->__color;
}


float ParticleGroup::GetAffectRange( ) const {
    return this->__affectRange;
}


std::vector<float> &ParticleGroup::GetInteractions( ) {
    return this->__interactions;
}


std::vector<Particle> &ParticleGroup::GetParticles( ) {
    return this->__particles;
}

