set(PROJECT_NAME "RhythmTyperGame")
set(GAME_EXECUTABLE_NAME "game")
set(GAME_LIBRARY_NAME "engine" CACHE STRING "")
project(${PROJECT_NAME})

add_executable(${GAME_EXECUTABLE_NAME} main.cpp)
add_library(${GAME_LIBRARY_NAME} STATIC)

add_subdirectory("core")
add_subdirectory("event")
add_subdirectory("ui")
add_subdirectory("graphic")
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
	add_subdirectory("debug")
	target_include_directories(${GAME_EXECUTABLE_NAME} PRIVATE "debug")
	target_include_directories(${GAME_LIBRARY_NAME} PRIVATE "debug")
endif()

target_include_directories(${GAME_LIBRARY_NAME} PRIVATE ${SDL2_SOURCE_DIR}/include
													${SDL2_MIXER_SOURCE_DIR}/include
													${SDL2_IMAGE_SOURCE_DIR}
													${SDL2_TTF_SOURCE_DIR}
													"./")

target_include_directories(${GAME_EXECUTABLE_NAME} PRIVATE ${SDL2_SOURCE_DIR}/include
													${SDL2_MIXER_SOURCE_DIR}/include
													${SDL2_IMAGE_SOURCE_DIR}
													${SDL2_TTF_SOURCE_DIR}
													"./")

target_link_libraries(${GAME_LIBRARY_NAME} PRIVATE SDL2 SDL2main SDL2_image SDL2_mixer SDL2_ttf)
target_link_libraries(${GAME_EXECUTABLE_NAME} PRIVATE ${GAME_LIBRARY_NAME})

set_target_properties(${GAME_LIBRARY_NAME} ${GAME_EXECUTABLE_NAME} 
						PROPERTIES CMAKE_CXX_EXTENSIONS OFF
						CXX_STANDARD 11
						CMAKE_INTERPROCEDURAL_OPTIMIZATION ON)