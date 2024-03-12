#pragma once

#ifdef D_MSVC
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#ifndef NOMINMAX
#define NOMINMAX
#endif

#include <Windows.h>
#include <direct.h>
#endif // D_MSVC

// STL includes

#include <stdio.h>

#include <deque>
#include <fstream>
#include <functional>
#include <memory>
#include <span>
#include <string>
#include <vector>

#include <chrono>