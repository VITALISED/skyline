#include <engine/renderer/EgRenderer.h>

void cEgRenderer::Construct(cTkEngineSettings &lSettings)
{
    cTkSystem &gSystem = cTkSystem::GetInstance();

    vkb::InstanceBuilder lInstanceBuilder;

    auto lBuilderRet = lInstanceBuilder.set_app_name(lSettings.msApplicationName.c_str())
                           .set_app_version(lSettings.muiApplicationVersion)
                           .set_engine_name(lSettings.msEngineName.c_str())
                           .set_engine_version(lSettings.muiEngineVersion)
                           .request_validation_layers()
                           .use_default_debug_messenger()
                           .build();
    vkb::Instance lInstance = lBuilderRet.value();

    this->mVkInstance     = lInstance.instance;
    this->mDebugMessenger = lInstance.debug_messenger;

    glfwCreateWindowSurface(this->mVkInstance, gSystem.mpGLFWWindow, nullptr, &this->mSurfaceKHR);

    vkb::PhysicalDeviceSelector lDeviceSelector(lInstance);
    vkb::PhysicalDevice lPhysicalDevice =
        lDeviceSelector.set_minimum_version(1, 1).set_surface(this->mSurfaceKHR).select().value();
    vkb::DeviceBuilder lDeviceBuilder(lPhysicalDevice);
    vkb::Device lDevice = lDeviceBuilder.build().value();

    this->mPhysicalDevice = lPhysicalDevice.physical_device;
    this->mDevice         = lDevice.device;
}
