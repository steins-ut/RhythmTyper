set(PROJECT_NAME "RhythmTyperGame")
set(GAME_EXECUTABLE_NAME "game")
set(GAME_LIBRARY_NAME "engine" CACHE STRING "")
project(${PROJECT_NAME})

find_package(Catch2 CONFIG REQUIRED)
find_package(SDL2 CONFIG REQUIRED)
find_package(SDL2_image CONFIG REQUIRED)
find_package(SDL2_mixer CONFIG REQUIRED)
find_package(SDL2_ttf CONFIG REQUIRED)

add_executable(${GAME_EXECUTABLE_NAME} main.cpp)
add_library(${GAME_LIBRARY_NAME} STATIC)

add_subdirectory("core")
add_subdirectory("event")
add_subdirectory("ui")
add_subdirectory("graphic")
add_subdirectory("scene")
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
	add_subdirectory("debug")
	target_include_directories(${GAME_EXECUTABLE_NAME} PRIVATE "debug")
	target_include_directories(${GAME_LIBRARY_NAME} PRIVATE "debug")
endif()

target_include_directories(${GAME_LIBRARY_NAME} PRIVATE ${SDL2_INCLUDE_DIR}
													${SDL2MIXER_INCLUDE_DIR}
													${SDL2IMAGE_INCLUDE_DIR}
													${SDL2TTF_INCLUDE_DIR}
													"./")

target_include_directories(${GAME_EXECUTABLE_NAME} PRIVATE ${SDL2_INCLUDE_DIR}
													${SDL2MIXER_INCLUDE_DIR}
													${SDL2IMAGE_INCLUDE_DIR}
													${SDL2TTF_INCLUDE_DIR}
													"./")

target_link_libraries(${GAME_LIBRARY_NAME} PRIVATE $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
												$<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
												$<IF:$<TARGET_EXISTS:SDL2_image::SDL2_image>,SDL2_image::SDL2_image,SDL2_image::SDL2_image-static>
												$<IF:$<TARGET_EXISTS:SDL2_mixer::SDL2_mixer>,SDL2_mixer::SDL2_mixer,SDL2_mixer::SDL2_mixer-static>
												$<IF:$<TARGET_EXISTS:SDL2_ttf::SDL2_ttf>,SDL2_ttf::SDL2_ttf,SDL2_ttf::SDL2_ttf-static>)
target_link_libraries(${GAME_EXECUTABLE_NAME} PRIVATE ${GAME_LIBRARY_NAME})

set_target_properties(${GAME_LIBRARY_NAME} ${GAME_EXECUTABLE_NAME} 
						PROPERTIES CMAKE_CXX_EXTENSIONS OFF
						CXX_STANDARD 11
						CMAKE_INTERPROCEDURAL_OPTIMIZATION ON)