cmake_minimum_required(VERSION 3.8)

project(Demo)

if(WIN32)
    file(GLOB_RECURSE SOURCES "src/Windows/*.cpp")
    file(GLOB_RECURSE HEADERS "include/Windows/*.h")
    source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES} ${HEADERS})
elseif(UNIX)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}"build/Android")
    file(GLOB_RECURSE SOURCES "src/Android/*.cpp")
    file(GLOB_RECURSE HEADERS "include/Android/*.h")
endif()

include_directories(include)

link_directories(${CMAKE_SOURCE_DIR}/build/Windows/Debug)

add_executable(Demo ${SOURCES} ${HEADERS})

set_property(TARGET Demo PROPERTY VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/asset)

target_link_libraries(Demo PRIVATE Engine10.lib)