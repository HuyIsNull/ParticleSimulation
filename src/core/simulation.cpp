#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <fstream>

#include <SDL3/SDL_timer.h>
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_stdinc.h>

#include <nlohmann/json.hpp>
#include <type_traits>

#include "core/simulation.hpp"
#include "core/particle.hpp"
#include "core/particle_properties.hpp"
#include "core/program.hpp"
#include "math/vector.hpp"
#include "utilities/utils.hpp"


static constexpr float AFFECT_RANGE = 75.f;


inline static void SurroundIndices( std::uint32_t returnArray[ 9 ], std::uint32_t columns, std::uint32_t rows, std::uint32_t index ) {
    std::int32_t x = index % columns,
                 y = index / columns;

    std::int32_t up = y - 1 > -1 ? y - 1 : rows - 1,
                 down = y + 1 < static_cast<std::int32_t>( rows ) ? y + 1 : 0,
                 left = x - 1 > -1 ? x - 1 : columns - 1,
                 right = x + 1 < static_cast<std::int32_t>( columns ) ? x + 1 : 0;

    returnArray[ 0 ] = up * columns + left;
    returnArray[ 1 ] = up * columns + x;
    returnArray[ 2 ] = up * columns + right;
    returnArray[ 3 ] = y * columns + left;
    returnArray[ 4 ] = y * columns + right;
    returnArray[ 5 ] = down * columns + left;
    returnArray[ 6 ] = down * columns + x;
    returnArray[ 7 ] = down * columns + right;
    returnArray[ 8 ] = index;
}


void Simulation::Update( float delta ) {
    SDL_Renderer *renderer = Program::GetInstance( ).GetRenderer( );

    this->__grid.Update( );

    const auto &cells = this->__grid.GetCells( );
    for( std::size_t i = 0; i < cells.size( ); ++i ) {
        auto &cell = cells[ i ];

        std::uint32_t indices[ 9 ];
        SurroundIndices( indices, this->__grid.GetColumn( ), this->__grid.GetRow( ), i );

        std::remove_reference_t<decltype( cells[ 0 ] )> *groups[ 8 ];
        Uint8 count = 0;
        for( Uint8 j = 0; j < 8; ++j ) {
            if( indices[ j ] < i )
                continue;
            groups[ count++ ] = &cells[ indices[ j ] ];
        }

        std::size_t index = cell.first,
                    size = cell.second;

        while( size-- ) {
            Particle &particle = this->__grid.GetDatas( )[ index++ ]; 
            auto &properties = this->__properties[ particle.type ];

            {
                std::size_t jndex = index,
                            jsize = cell.second - ( jndex - cell.first );
                
                while( jsize-- ) {
                    Particle &otherParticle = this->__grid.GetDatas( )[ jndex++ ];

                    float dstX = otherParticle.position.GetX( ) - particle.position.GetX( ),
                          dstY = otherParticle.position.GetY( ) - particle.position.GetY( );
                    dstX -= ( this->__width * SDL_roundf( dstX / this->__width ) );
                    dstY -= ( this->__height * SDL_roundf( dstY / this->__height ) );
                    float dst = SDL_sqrtf( dstX * dstX + dstY * dstY );

                    if( dst <= 0.f || dst > AFFECT_RANGE )
                        continue;

                    float interaction = properties.interactions[ otherParticle.type ],
                          otherInteraction = this->__properties[ otherParticle.type ].interactions[ particle.type ];

                    float force = this->GetGravity( ) / ( dst * dst );
                    float forceX = force * dstX,
                          forceY = force * dstY;

                    particle.velocity.GetX( ) += ( forceX * interaction );
                    particle.velocity.GetY( ) += ( forceY * interaction );

                    otherParticle.velocity.GetX( ) -= ( forceX * otherInteraction );
                    otherParticle.velocity.GetY( ) -= ( forceY * otherInteraction );
                }
            }

            for( Uint8 j = 0; j < count; ++j ) {
                auto &otherCell = *groups[ j ];

                std::size_t jndex = otherCell.first,
                            jsize = otherCell.second;
                
                while( jsize-- ) {
                    Particle &otherParticle = this->__grid.GetDatas( )[ jndex++ ];

                    float dstX = otherParticle.position.GetX( ) - particle.position.GetX( ),
                          dstY = otherParticle.position.GetY( ) - particle.position.GetY( );
                    dstX -= ( this->__width * SDL_roundf( dstX / this->__width ) );
                    dstY -= ( this->__height * SDL_roundf( dstY / this->__height ) );
                    float dst = SDL_sqrtf( dstX * dstX + dstY * dstY );

                    if( dst <= 0.f || dst > AFFECT_RANGE )
                        continue;

                    float interaction = properties.interactions[ otherParticle.type ],
                          otherInteraction = this->__properties[ otherParticle.type ].interactions[ particle.type ];

                    float force = this->GetGravity( ) / ( dst * dst );
                    float forceX = force * dstX,
                          forceY = force * dstY;

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


void Simulation::Load( const char *filepath ) {
    this->Clear( );

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

    std::size_t totalCount = 0;
    for( auto &particleType : particleTypes ) {
        totalCount += particleType[ "count" ].get<std::size_t>( );
    }

    this->__grid.SetSize( this->__width, this->__height, AFFECT_RANGE );
    this->__grid.ReserveElementCount( totalCount );

    for( auto &particleType : particleTypes ) {
        auto &color = particleType[ "color" ];
        this->AddParticles( particleType[ "count" ], {
            .type = particleType[ "type" ],
            .color = SDL_FColor{ color[ 0 ], color[ 1 ], color[ 2 ], color[ 3 ] },
            .affectRange = particleType[ "affectRange" ],
            .interactions = particleType[ "interactions" ]
        } );
    }

    this->__properties.shrink_to_fit( );
}


void Simulation::AddParticles( std::size_t count, const ParticleProperties &properties ) {
    auto &newProps = this->__properties.emplace_back( properties );
    newProps.count = count;

    for( std::size_t i = 0; i < count; i++ ) {
        this->__grid.Add( Particle {
            .type = newProps.type,
            .position = hin::Vector2f{ hin::Rand( ) * this->__width, hin::Rand( ) * this->__height }, 
            .velocity = hin::Vector2f{ 0, 0 },
        } );
    }
}


void Simulation::Clear( ) {
    this->__grid.Clear( );
    this->__properties.clear( );
}


void Simulation::SetSize( float width, float height ) {
    this->__width = width;
    this->__height = height;
}


float Simulation::GetGravity( ) const {
    return this->__gravity;
}
