cmake_minimum_required(VERSION 3.14...3.28)
project(telemetry-rec LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(telemetry-rec src/TelemetryBlackBox.cpp)
target_include_directories(telemetry-rec PUBLIC include)
target_compile_options(telemetry-rec PRIVATE -Wall -Wextra -Wpedantic)

include(FetchContent)
fetchcontent_declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.18.0.zip
)
set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)
fetchcontent_makeavailable(googletest)

enable_testing()

add_executable(tests tests/RingBufferTest.cpp tests/TelemetryBlackBoxTest.cpp)
target_compile_options(tests PRIVATE -Wall -Wextra -Wpedantic)
target_link_libraries(tests PRIVATE telemetry-rec GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(tests)
