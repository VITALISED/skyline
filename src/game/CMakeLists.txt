set(GCGAME_BUNDLE)

if(MSVC OR MINGW)
    set(GCGAME_BUNDLE WIN32)
elseif(APPLE)
    set(GCGAME_BUNDLE MACOSX_BUNDLE)
endif()

set(GCGAME_SOURCES GcMain.cpp application/GcApplication.cpp)

set(GCGAME_HEADERS GcMain.h application/GcApplication.h)

add_executable(GcGame ${GCGAME_BUNDLE} ${GCGAME_SOURCES} ${GCGAME_HEADERS})

target_include_directories(GcGame PRIVATE ${SKYLINE_SRC_DIR})

target_link_libraries(GcGame PRIVATE EgEngine TkToolkit)

target_precompile_headers(GcGame PRIVATE GcPch.h)
