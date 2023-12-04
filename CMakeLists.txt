cmake_minimum_required(VERSION 3.8)

project(Engine10)

if(WIN32)
    file(GLOB_RECURSE SOURCES "src/Windows/*.cpp")
    file(GLOB_RECURSE HEADERS "include/Windows/*.h")
    source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES} ${HEADERS})
    add_custom_target(Engine10
		  COMMAND lib.exe /OUT:$<TARGET_FILE_DIR:a>/Engine10.lib $<TARGET_FILE:a> 
                  ${CMAKE_CURRENT_SOURCE_DIR}"/lib/Windows/OpenGL32.lib"
		  ${CMAKE_CURRENT_SOURCE_DIR}"/lib/Windows/glfw3.lib"
		  ${CMAKE_CURRENT_SOURCE_DIR}"/lib/Windows/glew32s.lib"
                  WORKING_DIRECTORY .)
    include_directories(include/Windows)
    add_definitions(-DGLEW_STATIC)
elseif(UNIX)
   
endif()

add_library(a ${SOURCES} ${HEADERS})

target_compile_features(a PRIVATE cxx_std_17)

add_subdirectory(demo)