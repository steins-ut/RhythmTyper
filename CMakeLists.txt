# CMakeList.txt : CMake project for RhythmTyper, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.13)
cmake_policy(SET CMP0076 NEW)

message("Setting up project build...")

set(PROJECT_NAME "RhythmTyper")
set(PROJECT_VERSION_MAJOR 0)
set(PROJECT_VERSION_MINOR 1)
set(PROJECT_VERSION_PATCH 0)
set(PROJECT_VERSION ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH})

message("Project ${PROJECT_NAME}: Version ${PROJECT_VERSION}")
project (${PROJECT_NAME} VERSION ${PROJECT_VERSION})

if(MINGW)
	message("Project is built with MinGW, compile option -fstack-protector-strong will be added.")
	add_compile_options(-fstack-protector-strong)
	link_libraries(-fstack-protector-strong)
endif()

if(WIN32)
	message("Project is built on Windows, will copy library and runtime builds to project build location.")
	set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
endif()

add_subdirectory("external")
add_subdirectory("src")

set_property(TARGET ${PROJECT_NAME} PROPERTY CMAKE_CXX_EXTENSIONS OFF)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)
set_property(TARGET ${PROJECT_NAME} PROPERTY CMAKE_INTERPROCEDURAL_OPTIMIZATION ON)
# TODO: Add tests and install targets if needed.
