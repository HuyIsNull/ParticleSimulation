#pragma once

#include <algorithm>
#include <array>
#include <cstddef>
#include <tuple>

#include "utilities/weird_ass_shit.hpp"


template<typename ...Args>
requires are_unique<Args...>::value
class MultiVector {

public:

    MultiVector( ) {
        this->__size = 0;
        this->__capacity = 1;
        this->__data = std::make_tuple( new Args[ this->__capacity ]... );
    }


    void Reserve( std::size_t size ) {
        this->__capacity += size;
        std::apply( [ this ]( Args *...args ) {
            ( [ this ]<typename T>( T *&arg ) {
                T *temp = arg;
                arg = new T[ this->__capacity ];
                std::copy( temp, temp + this->__size, arg );
                delete[ ] temp;
            } ( args ), ... );
        }, this->__data );
    }


    consteval std::size_t GetTypeCount( ) {
        return std::tuple_size<decltype( this->__data )>::value;
    }


private:

    std::tuple<Args*...> __data{ };
    std::size_t __size{ },
                __capacity{ };

};

