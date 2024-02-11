set(EGENGINE_HEADERS
    EgMain.h renderer/EgRenderer.h renderer/EgDeletionQueue.h
    renderer/EgDescriptor.h renderer/EgPipeline.h renderer/EgShader.h
)

set(EGENGINE_SOURCES
    EgMain.cpp renderer/EgRenderer.cpp renderer/EgDescriptor.cpp
    renderer/EgShader.cpp renderer/EgPipeline.cpp
)

add_library(EgEngine ${EGENGINE_HEADERS} ${EGENGINE_SOURCES})

target_precompile_headers(EgEngine PUBLIC EgPch.h)

target_include_directories(EgEngine PRIVATE ${SKYLINE_SRC_DIR})

target_link_libraries(EgEngine PUBLIC TkToolkit)
