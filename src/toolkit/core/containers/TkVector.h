#pragma once

#include <toolkit/core/TkSTD.h>

#include <vector>

template <typename T, class Allocator = TkSTLAllocator<T>>
class cTkVector : public std::vector<T, Allocator>
{};