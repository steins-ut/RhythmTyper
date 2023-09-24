set(PROJECT_NAME RhythmTyperTests)
set(TEST_TARGET_NAME "test_rhythm_typer")
project(${PROJECT_NAME} VERSION ${PROJECT_VERSION})

if(WIN32)
	message("Project is built on Windows, will copy library and runtime builds to project build location.")
	set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
endif()

add_executable(${TEST_TARGET_NAME} "event_tests.cpp")
target_link_libraries(${TEST_TARGET_NAME} PRIVATE Catch2::Catch2WithMain ${GAME_LIBRARY_NAME})
target_include_directories(${TEST_TARGET_NAME} PRIVATE ${Catch2_SOURCE_DIR}/src
													${SDL2_SOURCE_DIR}/include
													${SDL2_MIXER_SOURCE_DIR}/include
													${SDL2_IMAGE_SOURCE_DIR}
													${SDL2_TTF_SOURCE_DIR}
													"../src")

include(CTest)
include(Catch)
catch_discover_tests(${TEST_TARGET_NAME})