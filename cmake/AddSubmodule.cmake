function(add_submodule TARGET DIR INCLUDE)
    message(STATUS "Adding dependency: ${DIR} (${INCLUDE})")

    file(GLOB_RECURSE HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/${DIR}/*.h")
    if(HEADERS STREQUAL "")
        execute_process(
            COMMAND git submodule update --init --recursive --depth 1 ${DIR}
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        )
    endif()

    if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/${DIR}/CMakeLists.txt")
        add_subdirectory(${DIR} SYSTEM)
        set_source_files_properties(
            DIRECTORY ${DIR} PROPERTIES COMPILE_FLAGS "-w"
        )
        set_source_files_properties(
            DIRECTORY ${DIR} PROPERTIES LINKER_FLAGS "-w"
        )
    endif()
    target_include_directories(
        ${TARGET} INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/${INCLUDE}" SYSTEM
    )
endfunction()
