set(TKTOOLKIT_SOURCES
    system/filesystem/TkFile.cpp system/filesystem/TkFileSystem.cpp
    system/filesystem/TkFileHandle.cpp system/timer/TkClock.cpp
    system/TkSystem.cpp
)

set(TKTOOLKIT_HEADERS
    core/TkAssert.h
    core/TkIDMap.h
    core/TkCore.h
    core/TkMacros.h
    core/TkSingleton.h
    core/TkSTD.h
    core/TkTypes.h
    core/containers/TkUnorderedMap.h
    core/containers/TkVector.h
    core/TkString.h
    engine/TkEngineSettings.h
    graphics/vulkan/TkVulkan.h
    graphics/vulkan/vk_mem_alloc.h
    graphics/vulkan/constructors/TkVmaStructures.h
    graphics/vulkan/constructors/TkVulkanImageStructures.h
    graphics/vulkan/constructors/TkVulkanConstructors.h
    graphics/vulkan/constructors/TkVulkanCommandStructures.h
    graphics/vulkan/constructors/TkVulkanPipelineStructures.h
    graphics/vulkan/constructors/TkVulkanRenderPassStructures.h
    graphics/vulkan/constructors/TkVulkanSyncStructures.h
    graphics/vulkan/constructors/TkVkConstructorIncludes.inl
    maths/numeric/TkIntrinsics.h
    maths/numeric/TkVector2.h
    maths/numeric/TkVector3.h
    maths/numeric/TkVector4.h
    maths/numeric/TkMatrix34.h
    maths/hash/TkHash.h
    scripts/squirrel/TkSquirrelVM.h
    system/filesystem/TkFile.h
    system/filesystem/TkFileHandle.h
    system/filesystem/TkFileSystem.h
    system/timer/TkClock.h
    system/TkSystem.h
)

add_library(TkToolkit ${TKTOOLKIT_SOURCES} ${TKTOOLKIT_HEADERS})

target_include_directories(TkToolkit PRIVATE ${SKYLINE_SRC_DIR})

target_precompile_headers(TkToolkit PUBLIC TkPch.h)

target_link_libraries(
    TkToolkit
    PUBLIC SkylineSubmoduleDependencies
           spdlog
           glfw
           vk-bootstrap
           Vulkan::Vulkan
           ${Vulkan_LIBRARIES}
           squirrel
)

if(MSVC)
    target_compile_definitions(TkToolkit PUBLIC D_MSVC=1)
else(MINGW)
    target_compile_definitions(TkToolkit PUBLIC D_MINGW=1)
endif()
