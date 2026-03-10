#pragma once

#include <SDL3/SDL_log.h>
#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <type_traits>
#include <utility>
#include <vector>

#include "math/vector.hpp"


namespace hin {

    template<typename T>
        requires std::is_convertible_v<std::remove_pointer_t<T>, hin::Vector2f>
    class SimpleGrid {

    public:

        SimpleGrid( ) = default;

        ~SimpleGrid( ) = default; 


        void Update( ) {
            std::sort( this->__datas.begin( ), this->__datas.end( ), [ this ]( const T &a, const T &b ) {
                return this->GetIndex( a ) < this->GetIndex( b );
            } );

            this->__cells.assign( this->__cells.size( ), { 0, 0 } );

            std::size_t preIndex = this->GetIndex( this->__datas[ 0 ] );
            for( std::size_t i = 0; i < this->__datas.size( ); ++i ) {
                std::size_t index = this->GetIndex( this->__datas[ i ] );
                if( index != preIndex ) {
                    preIndex = index;
                    this->__cells[ preIndex ].first = i;
                }
                ++this->__cells[ preIndex ].second;
            }
        }


        void Add( const T &element ) {
            this->__datas.push_back( element );
        }


        bool Remove( const T &element ) {
            return true;
        }


        void SetSize( float width, float height, float minimum ) {
            this->__column = static_cast<std::uint16_t>( width / minimum );
            std::uint16_t row = static_cast<std::uint16_t>( height / minimum );
            this->__cellWidth = width / this->__column;
            this->__cellHeight = height / row;
            this->__cells.resize( this->__column * row );
        }
        

        void ReserveElementCount( std::size_t count ) {
            this->__datas.reserve( count );
        }


        void Clear( ) {
            this->__datas.clear( );
        }


        std::size_t GetIndex( const T &element ) {
            const hin::Vector2f &vec = static_cast<hin::Vector2f>( __UniformType( element ) );
            return static_cast<std::size_t>( vec.GetY( ) / this->__cellHeight ) * this->__column + static_cast<std::size_t>( vec.GetX( ) / this->__cellWidth );
        }


        auto &GetDatas( ) {
            return this->__datas;
        }


        const auto &GetCells( ) const {
            return this->__cells;
        }


        std::uint16_t GetColumn( ) const {
            return this->__column;
        }

        std::uint16_t GetRow( ) const {
            return this->GetSize( ) / this->__column;
        }

        std::size_t GetSize( ) const {
            return this->__cells.size( );
        }


    private:

        std::vector<T> __datas{ };
        // index, count
        std::vector<std::pair<std::uint16_t, std::uint16_t>> __cells{ };
        std::uint16_t __column{ };
        float __cellWidth{ }, 
              __cellHeight{ };


        constexpr const std::remove_pointer_t<T> &__UniformType( const T &element ) {
            if constexpr ( std::is_pointer_v<T> ) {
                return *( element ); 
            } else {
                return element;
            }
        }

    };

}

