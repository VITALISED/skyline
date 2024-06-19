#pragma once

#include <toolkit/core/TkTypes.h>
#include <toolkit/core/string/TkString.h>

#include <concepts>
#include <type_traits>

template <typename T>
concept TkFundamental = std::is_fundamental_v<T> or std::same_as<std::remove_cv_t<T>, cTkString>;

template <typename T>
constexpr inline bool TkIsIntegralV = std::is_integral_v<T>;

template <typename T, typename U>
constexpr inline bool TkIsSameV = std::is_same_v<T, U>;