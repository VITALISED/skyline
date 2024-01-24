set(TKTOOLKIT_SOURCES graphics/vulkan/TkVulkan.cpp system/timer/TkClock.cpp)

set(TKTOOLKIT_HEADERS
    core/TkAssert.h
    core/TkCore.h
    core/TkMacros.h
    core/TkSTD.h
    graphics/vulkan/TkVulkan.h
    maths/numeric/TkIntrinsics.h
    maths/numeric/TkVector2.h
    maths/numeric/TkVector3.h
    maths/numeric/TkVector4.h
    maths/numeric/TkMatrix34.h
    system/timer/TkClock.h
)

add_library(TkToolkit ${TKTOOLKIT_SOURCES} ${TKTOOLKIT_HEADERS})

target_include_directories(TkToolkit PRIVATE ${SKYLINE_SRC_DIR})

target_precompile_headers(TkToolkit PUBLIC TkPch.h)

target_link_libraries(
    TkToolkit PUBLIC Vulkan::Vulkan SkylineSubmoduleDependencies spdlog
)

if(MSVC)
    target_compile_definitions(TkToolkit PUBLIC D_MSVC=1)
else(MINGW)
    target_compile_definitions(TkToolkit PUBLIC D_MINGW=1)
endif()
