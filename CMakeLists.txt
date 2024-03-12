cmake_minimum_required(VERSION 3.15)

project(
    skyline
    LANGUAGES CXX
    VERSION 0.0.1
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

include(AddSubmodule)
include(Shaders.cmake)

find_package(Vulkan REQUIRED)

add_library(SkylineSubmoduleDependencies INTERFACE)

set(SPDLOG_USE_STD_FORMAT ON)
add_submodule(
    SkylineSubmoduleDependencies ./submodules/spdlog
    ./submodules/spdlog/include
)

add_submodule(
    SkylineSubmoduleDependencies ./submodules/glfw ./submodules/glfw/include
)

add_submodule(
    SkylineSubmoduleDependencies ./submodules/vk-bootstrap
    ./submodules/vk-bootstrap/src
)

add_submodule(
    SkylineSubmoduleDependencies ./submodules/squirrel
    ./submodules/squirrel/include
)

add_submodule(
    SkylineSubmoduleDependencies ./submodules/freetype
    ./submodules/freetype/include
)
set(FREETYPE_LIBRARY "${CMAKE_CURRENT_SOURCE_DIR}/lib/freetype.lib")

add_submodule(SkylineSubmoduleDependencies ./submodules/zlib ./submodules/zlib)

add_submodule(
    SkylineSubmoduleDependencies ./submodules/RmlUi ./submodules/RmlUi/Include
)

add_submodule(
    SkylineSubmoduleDependencies ./submodules/StringZilla
    ./submodules/StringZilla/include
)

set(SKYLINE_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

add_subdirectory(src/toolkit)
add_subdirectory(src/engine)
add_subdirectory(src/game)
