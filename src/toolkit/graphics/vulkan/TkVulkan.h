#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <VkBootstrap.h>
#include <toolkit/graphics/vulkan/constructors/TkVkConstructorIncludes.inl>
#include <toolkit/graphics/vulkan/vk_mem_alloc.h>

#ifdef D_DEBUG
#define _VK_GUARD(x) TK_ASSERT((x == VK_SUCCESS), "Vulkan error.");
#else
#define _VK_GUARD(x) x
#endif