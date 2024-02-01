#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <VkBootstrap.h>
#include <toolkit/graphics/vulkan/constructors/TkVkConstructorIncludes.inl>

#ifdef D_DEBUG
#define _VK_GUARD(x) \
    if (x != VK_SUCCESS) { TK_ERROR("Vulkan Error: " #x " failed"); }
#else
#define _VK_GUARD(x) x
#endif