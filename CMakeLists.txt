cmake_minimum_required(VERSION 3.22)
project(runner)

set(CMAKE_CXX_STANDARD 20)

add_executable(runner runner/runner.cpp runner/game_state.cpp runner/game_state.h)

add_executable(strategy runner/game_state.cpp runner/game_state.h strategy/strategy_main.cpp strategy/Strategy.cpp strategy/Strategy.h)

enable_testing()

include(FetchContent)

FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG        release-1.11.0
)
FetchContent_MakeAvailable(googletest)
add_library(GTest::GTest INTERFACE IMPORTED)
target_link_libraries(GTest::GTest INTERFACE gtest_main)

add_executable(game_state_ut runner/game_state.cpp runner/game_state.h runner/game_state_ut.cpp)

target_link_libraries(game_state_ut PRIVATE GTest::GTest)

add_test(game_state_ut game_state_ut)