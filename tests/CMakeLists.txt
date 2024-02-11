set(PROJECT_NAME "RhythmTyperTests")
set(TEST_TARGET_NAME "test_rhythm_typer")
project(${PROJECT_NAME} VERSION ${PROJECT_VERSION})

find_package(Catch2 CONFIG REQUIRED)

if(WIN32)
	message("Project is built on Windows, will copy library and runtime builds to project build location.")
	set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
endif()

add_executable(${TEST_TARGET_NAME} "event_tests.cpp" "space_tests.cpp")
target_link_libraries(${TEST_TARGET_NAME} PRIVATE Catch2::Catch2WithMain ${GAME_LIBRARY_NAME})
target_include_directories(${TEST_TARGET_NAME} PRIVATE ${CATCH2_INCLUDE_DIR}
													${SDL2_INCLUDE_DIR}
													${SDL2MIXER_INCLUDE_DIR}
													${SDL2IMAGE_INCLUDE_DIR}
													${SDL2TTF_INCLUDE_DIR}
													"../src")

include(CTest)
include(Catch)
catch_discover_tests(${TEST_TARGET_NAME})