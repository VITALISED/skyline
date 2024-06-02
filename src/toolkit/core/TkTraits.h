#pragma once

#include <toolkit/core/TkString.h>
#include <toolkit/core/TkTypes.h>

template <typename T>
concept TkFundamental = std::is_fundamental_v<T> or std::same_as<std::remove_cv_t<T>, cTkString>;