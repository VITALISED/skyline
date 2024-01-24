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

find_package(Vulkan REQUIRED)

add_library(SkylineSubmoduleDependencies INTERFACE)

set(SPDLOG_USE_STD_FORMAT)
add_submodule(
    SkylineSubmoduleDependencies ./submodules/spdlog
    ./submodules/spdlog/include
)

add_submodule(
    SkylineSubmoduleDependencies ./submodules/glfw ./submodules/glfw/include
)

set(SKYLINE_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

add_subdirectory(src/toolkit)
add_subdirectory(src/engine)
add_subdirectory(src/game)
