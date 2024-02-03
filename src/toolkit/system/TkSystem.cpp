#include <toolkit/system/TkSystem.h>

void cTkSystem::Construct()
{
    glfwInit();
    this->mpFilesystem = new cTkFilesystem();

    this->muiHeight = 720;
    this->muiWidth  = 1280;
    this->ConstructVideo();
}

void cTkSystem::Destruct()
{
    this->mpFilesystem->Destruct();
    delete this->mpFilesystem;

    glfwDestroyWindow(this->mpGLFWWindow);
    glfwTerminate();
}

void cTkSystem::ConstructVideo()
{
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    this->mpGLFWWindow = glfwCreateWindow(this->muiWidth, this->muiHeight, "GcGame", nullptr, nullptr);
}

void cTkSystem::PollForEvents()
{
    if (!glfwWindowShouldClose(this->mpGLFWWindow)) { glfwPollEvents(); }
}