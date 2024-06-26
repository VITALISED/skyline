set(GCGAME_BUNDLE)

if(MSVC OR MINGW)
    set(GCGAME_BUNDLE WIN32)
elseif(APPLE)
    set(GCGAME_BUNDLE MACOSX_BUNDLE)
endif()

set(GCGAME_SOURCES GcMain.cpp application/GcApplication.cpp
                   frontend/GcFrontendManager.cpp scripts/GcScriptManager.cpp
)

set(GCGAME_HEADERS GcMain.h application/GcApplication.h
                   frontend/GcFrontendManager.h scripts/GcScriptManager.h
)

add_executable(GcGame ${GCGAME_BUNDLE} ${GCGAME_SOURCES} ${GCGAME_HEADERS})

target_include_directories(GcGame PRIVATE ${SKYLINE_SRC_DIR})

target_compile_definitions(
    GcGame PRIVATE -DD_WORKING_DIR="${PROJECT_SOURCE_DIR}/"
)

if(MSVC)
    target_compile_definitions(GcGame PUBLIC D_MSVC=1)
    target_compile_options(GcGame PUBLIC /wd4068 /Zc:__cplusplus /std:c++latest)
else(MINGW)
    target_compile_definitions(GcGame PUBLIC D_MINGW=1)
endif()

target_link_libraries(GcGame PRIVATE EgEngine TkToolkit)

target_precompile_headers(GcGame PRIVATE GcPch.h)

add_dependencies(GcGame Shaders)
