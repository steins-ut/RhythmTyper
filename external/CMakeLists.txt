message("Setting up external dependencies...")

include(FetchContent)
set(FETCHCONTENT_QUIET OFF)

set(SDL_TEST OFF CACHE BOOL "" FORCE)
set(SDL_TESTS OFF CACHE BOOL "" FORCE)
set(SDL_INSTALL_TESTS OFF CACHE BOOL "" FORCE)

set(SDL2IMAGE_SAMPLES OFF CACHE BOOL "" FORCE)
set(SDL2IMAGE_INSTALL OFF CACHE BOOL "CMake fails unless set to OFF." FORCE)

set(SDL2MIXER_SAMPLES OFF CACHE BOOL "" FORCE)
set(SDL2MIXER_INSTALL OFF CACHE BOOL "CMake fails unless set to OFF." FORCE)
set(SDL2MIXER_VENDORED ON CACHE BOOL "Some computers don't compile some libraries from source without this for some reason." FORCE)

set(SDL2TTF_SAMPLES OFF CACHE BOOL "" FORCE)
set(SDL2TTF_INSTALL OFF CACHE BOOL "CMake fails unless set to OFF." FORCE)

FetchContent_Declare(
	SDL2
	GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
	GIT_TAG adf31f6ec0be0f9ba562889398f71172c7941023
	SOURCE_DIR ${CMAKE_SOURCE_DIR}/external/SDL2
)

FetchContent_Declare(
	SDL2_image
	GIT_REPOSITORY https://github.com/libsdl-org/SDL_image.git
	GIT_TAG d3c6d5963dbe438bcae0e2b6f3d7cfea23d02829
	SOURCE_DIR ${CMAKE_SOURCE_DIR}/external/SDL2_image
)

FetchContent_Declare(
	SDL2_mixer
	GIT_REPOSITORY https://github.com/libsdl-org/SDL_mixer.git
	GIT_TAG 6103316427a8479e5027e41ab9948bebfc1c3c19
	SOURCE_DIR ${CMAKE_SOURCE_DIR}/external/SDL2_mixer
)

FetchContent_Declare(
	SDL2_ttf
	GIT_REPOSITORY https://github.com/libsdl-org/SDL_ttf.git
	GIT_TAG 89d1692fd8fe91a679bb943d377bfbd709b52c23
	SOURCE_DIR ${CMAKE_SOURCE_DIR}/external/SDL2_ttf
)

message("Setting up SDL and auxiliary libraries...")
FetchContent_MakeAvailable(SDL2 SDL2_image SDL2_mixer SDL2_ttf)
message("External dependencies are set up.")