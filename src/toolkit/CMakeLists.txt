set(TKTOOLKIT_SOURCES
    core/TkAssert.cpp graphics/vulkan/TkVulkan.cpp
    graphics/api/TkGraphicsAPI.cpp system/timer/TkClock.cpp system/TkSystem.cpp
)

set(TKTOOLKIT_HEADERS
    core/TkAssert.h
    core/TkCore.h
    core/TkMacros.h
    core/TkSingleton.h
    core/TkSTD.h
    core/TkString.h
    engine/TkEngineSettings.h
    graphics/vulkan/TkVulkan.h
    graphics/api/TkGraphicsAPI.h
    maths/numeric/TkIntrinsics.h
    maths/numeric/TkVector2.h
    maths/numeric/TkVector3.h
    maths/numeric/TkVector4.h
    maths/numeric/TkMatrix34.h
    system/timer/TkClock.h
    system/TkSystem.h
)

add_library(TkToolkit ${TKTOOLKIT_SOURCES} ${TKTOOLKIT_HEADERS})

target_include_directories(TkToolkit PRIVATE ${SKYLINE_SRC_DIR})

target_precompile_headers(TkToolkit PUBLIC TkPch.h)

target_link_libraries(
    TkToolkit PUBLIC Vulkan::Vulkan SkylineSubmoduleDependencies spdlog glfw
                     vk-bootstrap
)

if(MSVC)
    target_compile_definitions(TkToolkit PUBLIC D_MSVC=1)
else(MINGW)
    target_compile_definitions(TkToolkit PUBLIC D_MINGW=1)
endif()
