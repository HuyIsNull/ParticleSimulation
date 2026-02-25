#include "core/simulation.hpp"
#include "core/program.hpp"
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_stdinc.h>
#include <cmath>
#include <cstdlib>


void Simulation::Update( float delta ) {
    Program &program = Program::GetInstance( );
    SDL_Renderer *renderer = program.GetRenderer( );

    for( std::size_t i = 0; i < this->__groups.size( ); i++ ) {
        ParticleGroup &group = this->__groups[ i ];
        {
            SDL_FColor &color = group.GetColor( );
            SDL_SetRenderDrawColorFloat( renderer, color.r, color.g, color.b, color.a );
        }

        for( std::size_t j = 0; j < group.GetParticles( ).size( ); j++ ) {
            Particle &particle = group.GetParticles( )[ j ];

            for( std::size_t k = i; k < this->__groups.size( ); k++ ) {
                ParticleGroup &otherGroup = this->__groups[ k ];

                float interaction = group.GetInteractions( )[ k ],
                      otherInteraction = otherGroup.GetInteractions( )[ i ];

                for( std::size_t l = ( i + 1 ) * ( i == k ); l < otherGroup.GetParticles( ).size( ); l++ ) {
                    Particle &otherParticle = otherGroup.GetParticles( )[ l ];
                    float distX = otherParticle.position.x - particle.position.x,
                          distY = otherParticle.position.y - particle.position.y;

                    distX -= ( this->__width * SDL_roundf( distX / static_cast<float>( this->__width ) ) );
                    distY -= ( this->__height * SDL_roundf( distY / static_cast<float>( this->__height ) ) );

                    // {
                    //     float absDistX = std::abs( distX ),
                    //           absDistY = std::abs( distY );
                    // 
                    //     if( absDistX < halfWidth ) {
                    //     } else if( absDistX > halfWidth ) {
                    //         distX = ( this->__width - absDistX ) * ( -distX / absDistX );
                    //     } else {
                    //         distX = 0;
                    //     }
                    // 
                    //     if( absDistY < halfHeight ) {
                    //     } else if( absDistY > halfHeight ) {
                    //         distY = ( this->__height - absDistY ) * ( -distY / absDistY );
                    //     } else {
                    //         distY = 0;
                    //     }
                    // 
                    // }
                    
                    float dist = SDL_sqrtf( distX * distX + distY * distY );
                    
                    if( dist <= 5.f || dist > 75.f )
                        continue;

                    float force = this->GetGravity( ) / ( dist * dist );
                    float forceX = force * ( distX / dist ),
                          forceY = force * ( distY / dist );

                    // if( dist < group.GetAffectRange( ) ) {
                        particle.velocity.x += ( forceX * interaction );
                        particle.velocity.y += ( forceY * interaction );
                    // }
                    // if( dist < otherGroup.GetAffectRange( ) ) {
                        otherParticle.velocity.x -= ( forceX * otherInteraction );
                        otherParticle.velocity.y -= ( forceY * otherInteraction );
                    // }
                }
            }

            float x = SDL_fmodf( particle.position.x + ( particle.velocity.x * delta ), this->__width ),
                  y = SDL_fmodf( particle.position.y + ( particle.velocity.y * delta ), this->__height );

            particle.position.x = x < 0 ? x + this->__width : x;
            particle.position.y = y < 0 ? y + this->__height : y;

            // particle.velocity.x = 0;
            // particle.velocity.y = 0;

            // SDL_FRect rect = { particle.position.x, particle.position.y, 10.f, 10.f };
            // SDL_RenderFillRect( renderer, &rect );
            SDL_RenderPoint( renderer, particle.position.x, particle.position.y );
        }
    }
}


void Simulation::Reset( ) {
    auto &group0 = this->__groups.emplace_back( );
    group0.Reset( 0, { 1.f, 0, 0, 1.f }, 75.f, 5000, this->__width, this->__height, { -0.25f, 0.5f } );

    // auto &group1 = this->__groups.emplace_back( );
    // group1.Reset( 1, { 0.f, 1.f, 0, 1.f }, 75.f, 100, this->__width, this->__height, { 0.25f, 0.25f } );
}


void Simulation::SetSize( std::size_t width, std::size_t height ) {
    this->__width = width;
    this->__height = height;
}


float Simulation::GetGravity( ) const {
    return this->__gravity;
}

