#pragma once

#include <type_traits>
#include <vector>

#include <SDL3/SDL_log.h>
#include <SDL3/SDL_stdinc.h>

#include "math/vector.hpp"


namespace hin {

    template<typename T>
        requires std::is_convertible_v<std::remove_pointer_t<T>, hin::Vector2f>
    class Grid {

    public:

        Grid( ) = default;

        ~Grid( ) {
            if( this->__cells != nullptr ) {
                delete[ ] this->__cells;
            }
        }


        bool Add( const T &element ) {
            if( this->GetIndex( element ) >= this->__size ) {
                return false;
            }
            this->__cells[ this->GetIndex( element ) ].push_back( element );
            return true;
        }


        bool Remove( const T &element ) {
            auto &vec = this->__cells[ this->GetIndex( element ) ];
            for( auto it = vec.begin( ); it != vec.end( ); ++it ) {
                if( *it == element ) {
                    vec.erase( it );
                    return true;
                }
            }

            return false;
        }


        void SetSize( float width, float height, float minimum ) {
            this->__column = static_cast<Uint16>( width / minimum );
            this->__row = static_cast<Uint16>( height / minimum );
            this->__cellWidth = width / this->__column;
            this->__cellHeight = height / this->__row;
            this->__size = this->__column * this->__row;

            if( this->__cells != nullptr ) {
                delete[ ] this->__cells;
                this->__cells = nullptr;
            }
            this->__cells = new std::vector<T>[ this->__column * this->__row ];
        }


        std::size_t GetIndex( const T &element ) {
            const hin::Vector2f &vec = static_cast<hin::Vector2f>( __UniformType( element ) );
            return static_cast<std::size_t>( vec.GetY( ) / this->__cellHeight ) * this->__column + static_cast<std::size_t>( vec.GetX( ) / this->__cellWidth );
        }


        std::vector<T> &GetCell( std::size_t index ) {
            return this->__cells[ index ];
        }

        Uint16 GetColumn( ) const {
            return this->__column;
        }

        Uint16 GetRow( ) const {
            return this->__row;
        }

        Uint32 GetSize( ) const {
            return this->__size;
        }


    private:

        constexpr const std::remove_pointer_t<T> &__UniformType( const T &element ) {
            if constexpr ( std::is_pointer_v<T> ) {
                return *( element ); 
            } else {
                return element;
            }
        }


        std::vector<T> *__cells{ nullptr };
        Uint16 __column{ },
               __row{ };

        Uint32 __size{ };

        float __cellWidth{ },
              __cellHeight{ };

    };

}
