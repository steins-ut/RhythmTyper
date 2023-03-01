# CMakeList.txt : CMake project for RhythmTyper, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

message("Setting up project build...")

set(PROJECT_NAME "RhythmTyper")
set(PROJECT_VERSION_MAJOR 0)
set(PROJECT_VERSION_MINOR 1)
set(PROJECT_VERSION_PATCH 0)
set(PROJECT_VERSION ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH})
add_compile_options(-fstack-protector-strong)
link_libraries(-fstack-protector-strong)

message("Project ${PROJECT_NAME}: Version ${PROJECT_VERSION}")
project (${PROJECT_NAME} VERSION ${PROJECT_VERSION})

if(WIN32)
	message("Project is built on Windows, will copy library and runtime builds to project build location.")
	set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
endif()

add_subdirectory("external")
add_subdirectory("src")
# TODO: Add tests and install targets if needed.
