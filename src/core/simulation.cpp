#include <cstddef>
#include <cstdlib>
#include <fstream>

#include <SDL3/SDL_timer.h>
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_stdinc.h>

#include <nlohmann/json.hpp>

#include "core/simulation.hpp"
#include "core/particle.hpp"
#include "core/particle_properties.hpp"
#include "core/program.hpp"
#include "ds/grid.hpp"
#include "math/vector.hpp"
#include "utilities/utils.hpp"


static constexpr float AFFECT_RANGE = 75.f;


void Simulation::Update( float delta ) {
    SDL_Renderer *renderer = Program::GetInstance( ).GetRenderer( );

    hin::Grid<Particle*> grid{ };
    grid.SetSize( this->__width, this->__height, AFFECT_RANGE );
    for( auto &particle : this->__particles ) {
        grid.Add( &particle );
    }

    for( Uint32 i = 0; i < grid.GetSize( ); ++i ) {
        std::vector<Particle*> &particles = grid.GetCell( i );

        Uint8 count = 0;
        Uint32 beginIndex = ( i + grid.GetSize( ) - 1 ) % grid.GetSize( );
        Uint16 x = beginIndex % grid.GetColumn( );
        beginIndex -= x;

        std::vector<Particle*> *groups[ 9 ];
        for( Uint8 j = 0; j < 3; ++j ) {
            for( Uint8 k = 0; k < 3; ++k ) {
                Uint32 index = beginIndex + ( ( x + k ) % grid.GetColumn( ) );
                if( index < i )
                    continue;
                groups[ count++ ] = &grid.GetCell( index );
            }
            beginIndex = ( beginIndex + grid.GetColumn( ) ) % grid.GetSize( );
        }

        std::size_t particleCount = particles.size( );
        while( particleCount-- ) {
            Particle &particle = *particles[ particleCount ];
            auto &properties = this->__properties[ particle.type ];

            particles.erase( particles.end( ) - 1 );

            for( Uint8 k = 0; k < count; ++k ) {
                auto &otherParticles = *groups[ k ];                
                for( auto otherParticleP : otherParticles ) {
                    Particle &otherParticle = *otherParticleP;

                    float dstX = otherParticle.position.GetX( ) - particle.position.GetX( ),
                          dstY = otherParticle.position.GetY( ) - particle.position.GetY( );
                    dstX -= ( this->__width * SDL_roundf( dstX / this->__width ) );
                    dstY -= ( this->__height * SDL_roundf( dstY / this->__height ) );
                    float dst = SDL_sqrtf( dstX * dstX + dstY * dstY );

                    if( dst <= 2.5f || dst > AFFECT_RANGE )
                        continue;

                    float interaction = properties.interactions[ otherParticle.type ],
                          otherInteraction = this->__properties[ otherParticle.type ].interactions[ particle.type ];

                    float force = this->GetGravity( ) / ( dst * dst );
                    float forceX = force * ( dstX / dst ),
                          forceY = force * ( dstY / dst );

                    particle.velocity.GetX( ) += ( forceX * interaction );
                    particle.velocity.GetY( ) += ( forceY * interaction );

                    otherParticle.velocity.GetX( ) -= ( forceX * otherInteraction );
                    otherParticle.velocity.GetY( ) -= ( forceY * otherInteraction );
                }
            }

            float x = SDL_fmodf( particle.position.GetX( ) + ( particle.velocity.GetX( ) * delta ), this->__width ),
                  y = SDL_fmodf( particle.position.GetY( ) + ( particle.velocity.GetY( ) * delta ), this->__height );

            particle.position.GetX( ) = x >= 0 ? x : ( x += this->__width ) != this->__width ? x : 0;
            particle.position.GetY( ) = y >= 0 ? y : ( y += this->__height ) != this->__height ? y : 0;

            SDL_SetRenderDrawColorFloat( renderer, properties.color.r, properties.color.g, properties.color.b, properties.color.a );
            SDL_RenderPoint( renderer, particle.position.GetX( ), particle.position.GetY( ) );
        }
    }
}


void Simulation::Reset( ) {
    this->__properties.clear( );
    // this->__grid.SetSize( this->__width, this->__height, AFFECT_RANGE );

    this->AddParticles( 10000, { .type = 0, .color = { 1.f, 0, 0, 1.f }, .affectRange = 75.f, .interactions = { -0.1f, 0.9f } } );

    SDL_Log( "Simulation reset!" );
}


void Simulation::Load( const char *filepath ) {
    this->__particles.clear( );
    this->__properties.clear( );

    std::ifstream file( filepath );
    nlohmann::json data;
    if( !file.good( ) ) {
        SDL_Log( "Failed to open file: %s", filepath );
        data = {
            {
                "particle_types",
                {
                    {
                        { "type", 0 },
                        { "count", 1000 },
                        { "color", { 1.f, 0, 0, 1.f } },
                        { "affectRange", 75.f },
                        { "interactions", { -0.1f, 0.9f, 0.f } }
                    },
                    {
                        { "type", 1 },
                        { "count", 1000 },
                        { "color", { 0.f, 1.f, 0.f, 1.f } },
                        { "affectRange", 75.f },
                        { "interactions", { 0.1f, 0.9f, 0.f } }
                    },
                    {
                        { "type", 2 },
                        { "count", 1000 },
                        { "color", { 0.f, 0.f, 1.f, 1.f } },
                        { "affectRange", 75.f },
                        { "interactions", { 0.f, 0.f, 0.f } }
                    }
                }
            }
        };
        std::ofstream ofile( filepath );
        ofile << data.dump( 4 );
        ofile.close( );
    } else {
        data = nlohmann::json::parse( file );
    }

    nlohmann::json &particleTypes = data[ "particle_types" ];
    for( auto &particleType : particleTypes ) {
        auto &color = particleType[ "color" ];
        this->AddParticles( particleType[ "count" ], {
            .type = particleType[ "type" ],
            .color = SDL_FColor{ color[ 0 ], color[ 1 ], color[ 2 ], color[ 3 ] },
            .affectRange = particleType[ "affectRange" ],
            .interactions = particleType[ "interactions" ]
        } );
    }

    this->__particles.shrink_to_fit( );
    this->__properties.shrink_to_fit( );
}


void Simulation::AddParticles( std::size_t count, const ParticleProperties &properties ) {
    auto &newProps = this->__properties.emplace_back( properties );
    newProps.count = count;

    for( std::size_t i = 0; i < count; i++ ) {
        // this->__grid.Add( Particle{ 
        this->__particles.emplace_back( Particle {
            .type = newProps.type,
            .position = hin::Vector2f{ hin::Rand( ) * this->__width, hin::Rand( ) * this->__height }, 
            .velocity = hin::Vector2f{ 0, 0 },
        } );
    }
}


void Simulation::SetSize( float width, float height ) {
    this->__width = width;
    this->__height = height;
}


float Simulation::GetGravity( ) const {
    return this->__gravity;
}

