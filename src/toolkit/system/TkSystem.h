#pragma once

#include <toolkit/core/TkCore.h>
#include <toolkit/graphics/vulkan/TkVulkan.h>
#include <toolkit/system/filesystem/TkFilesystem.h>
#include <toolkit/system/timer/TkClock.h>

class cTkSystem : public cTkSingleton<cTkSystem>
{
  public:
    void Construct();
    void Destruct();

    void ConstructVideo();
    void PollForEvents();

    uint32_t muiWidth;
    uint32_t muiHeight;
    GLFWwindow *mpGLFWWindow;
    cTkFilesystem *mpFilesystem;
};