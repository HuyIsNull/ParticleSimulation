#pragma once

#include <concepts>
#include <type_traits>



template<typename...>
struct are_unique : std::true_type {};

template<typename T, typename... Rest>
struct are_unique<T, Rest...>
    : std::bool_constant<
        (!std::is_same_v<T, Rest> && ...) &&
        are_unique<Rest...>::value
      > {};

