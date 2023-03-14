add_executable(${PROJECT_NAME} main.cpp)

add_subdirectory("core")
add_subdirectory("event")

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
add_subdirectory("debug")
target_include_directories(${PROJECT_NAME} PRIVATE "debug")
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE SDL2 SDL2main SDL2_image SDL2_mixer SDL2_ttf)
target_include_directories(${PROJECT_NAME} PRIVATE ${SDL2_SOURCE_DIR}/include
													${SDL2_MIXER_SOURCE_DIR}/include
													${SDL2_IMAGE_SOURCE_DIR}
													${SDL2_TTF_SOURCE_DIR}
													"core"
													"event")