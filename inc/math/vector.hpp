#pragma once

#include <cmath>
#include <cstddef>
#include <cstring>
#include <initializer_list>


namespace hin {

    template<typename T, std::size_t N>
        requires std::is_arithmetic_v<T>
    struct Vector {

        static constexpr std::size_t size{ N };
        T components[ N ]{ };


        Vector( ) = default;
        Vector( const Vector &other ) = default;
        Vector( Vector &&other ) = default;

        Vector( const std::initializer_list<T> &components ) {
            for( std::size_t i = 0; i < N; ++i ) {
                this->components[ i ] = *( components.begin( ) + i );
            }
        }

        ~Vector( ) = default;


        Vector &Normalize( ) {
            constexpr double len = 1.f / this->GetLength( );
            return this->Scale( len );
        }


        double Dot( const Vector &other ) {
            double sum = 0;
            this->Applier( [ &sum, &other ]( std::size_t index, T component ) {
                sum += component * other.GetComponent( index );
                return component;
            } );
            return sum;
        }


        double GetLength( ) {
            double sum = 0;
            this->Applier( [ &sum ]( std::size_t index, T component ) {
                sum += ( component * component );
                return component;
            } );
            return std::sqrt( sum );
        }


        template<typename Func>
            requires std::is_invocable_r_v<T, Func, std::size_t, T>
        Vector &Applier( Func func ) {
            for( std::size_t i = 0; i < this->size; i++ ) {
                this->components[ i ] = func( i, this->components[ i ] );
            }
            return *this;
        }


        Vector &Add( const Vector &other ) {
            return this->Applier( [ other ]( std::size_t index, T component ) { 
                return component + other.GetComponent( index );
            } );
        }

        Vector &Sub( const Vector &other ) {
            return this->Applier( [ other ]( std::size_t index, T component ) { 
                return component - other.GetComponent( index );
            } );
        }

        Vector &Mul( const Vector &other ) {
            return this->Applier( [ other ]( std::size_t index, T component ) { 
                return component * other.GetComponent( index );
            } );
        }

        Vector &Div( const Vector &other ) {
            return this->Applier( [ other ]( std::size_t index, T component ) { 
                return component / other.GetComponent( index );
            } );
        }


        Vector &Scale( double scalar ) {
            return this->Applier( [ scalar ]( std::size_t index, T component ) { 
                return component * scalar;
            } );
        }


        Vector &Reset( ) {
            std::memset( this->components, 0, sizeof( this->components ) );
        }


        Vector Copy( ) const { return *this; }

        T &GetComponent( std::size_t index ) { return this->components[ index ]; }
        const T &GetComponent( std::size_t index ) const { return this->components[ index ]; }

        T &GetX( ) { return this->components[ 0 ]; }
        const T &GetX( ) const { return this->components[ 0 ]; }

        T &GetY( ) { return this->components[ 1 ]; }
        const T &GetY( ) const { return this->components[ 1 ]; }

        T &GetZ( ) { return this->components[ 2 ]; }
        const T &GetZ( ) const { return this->components[ 2 ]; }

        Vector operator+( const Vector &other ) const { return this->Copy( ).Add( other ); }
        Vector operator-( const Vector &other ) const { return this->Copy( ).Sub( other ); }
        Vector operator*( const Vector &other ) const { return this->Copy( ).Mul( other ); }
        Vector operator/( const Vector &other ) const { return this->Copy( ).Div( other ); }
        Vector operator*( const double &scalar ) const { return this->Copy( ).Scale( scalar ); }
        Vector operator/( const double &scalar ) const { return this->Copy( ).Scale( 1.f / scalar ); }

        Vector &operator+=( const Vector &other ) { return this->Add( other ); }
        Vector &operator-=( const Vector &other ) { return this->Sub( other ); }
        Vector &operator*=( const Vector &other ) { return this->Mul( other ); }
        Vector &operator/=( const Vector &other ) { return this->Div( other ); }
        Vector &operator*=( const double &scalar ) { return this->Scale( scalar ); }
        Vector &operator/=( const double &scalar ) { return this->Scale( 1.f / scalar ); }

        Vector &operator=( const Vector &other ) = default;
        bool operator==( const Vector &other ) const = default;

        T &operator[ ]( std::size_t index ) { return this->components[ index ]; }

    };


    using Vector2f = Vector<float, 2>;

}

