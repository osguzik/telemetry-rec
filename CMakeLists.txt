cmake_minimum_required(VERSION 3.14...3.28)
project(telemetry-rec LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(telemetry-rec src/TelemetryBlackBox.cpp)
target_include_directories(telemetry-rec PUBLIC include)
target_compile_options(telemetry-rec PRIVATE -Wall -Wextra -Wpedantic)
