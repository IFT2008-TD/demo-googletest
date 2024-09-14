cmake_minimum_required(VERSION 3.22)
project(monprojet)

set(CMAKE_CXX_STANDARD 14)

include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.12.x
)

FetchContent_MakeAvailable(googletest)

add_executable(monprojet main.cpp Tugabudoire.cpp)

enable_testing()

add_subdirectory(tests)

