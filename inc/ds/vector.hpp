#pragma once

#include "ds/base_vector.hpp"


template<typename T>
class Vector : public BaseVector {

public:

    Vector( ) {
        this->__data = new T[ 1 ];
    }


private:

    T *__data{ nullptr };

};
