cmake_minimum_required(VERSION 3.20)

project(
    VPlanner
    VERSION 0.1.0
    LANGUAGES CXX
)

include(FetchContent)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.17.0
)

FetchContent_MakeAvailable(googletest)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(
    VPlanner
    src/main.cpp
)

add_executable(
    VPlannerTests
    tests/TimeRangeTests.cpp
    src/domain/TimeRange.cpp
)

target_link_libraries(
    VPlannerTests
    PRIVATE
    GTest::gtest_main
)