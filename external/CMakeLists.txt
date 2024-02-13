message("Setting up external dependencies...")

find_package(Catch2 CONFIG REQUIRED)
find_package(SDL2 CONFIG REQUIRED)
find_package(SDL2_image CONFIG REQUIRED)
find_package(SDL2_mixer CONFIG REQUIRED)
find_package(SDL2_ttf CONFIG REQUIRED)

find_path(CATCH2_INCLUDE_DIR NAMES catch.hpp PATH_SUFFIXES catch2)
find_path(SDL2_INCLUDE_DIR NAMES SDL.h PATH_SUFFIXES SDL2)
find_path(SDL2IMAGE_INCLUDE_DIR NAMES SDL_image.h PATH_SUFFIXES SDL2)
find_path(SDL2MIXER_INCLUDE_DIR NAMES SDL_mixer.h PATH_SUFFIXES SDL2)
find_path(SDL2TTF_INCLUDE_DIR NAMES SDL_ttf.h PATH_SUFFIXES SDL2)

list(APPEND CMAKE_MODULE_PATH ${CATCH2_DIR})

set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH}" PARENT_SCOPE)

message("External dependencies are set up.")
