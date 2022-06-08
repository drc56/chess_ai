project(ChessAi)

#Configure C++ & CMake
cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_STANDARD 20)

# Set build location
set(PROJECT_BINARY_DIR build/)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")

#Set libchess include directories
include_directories(${CMAKE_SOURCE_DIR}/lib/libchess/src)

# Add spdlog
if(NOT TARGET spdlog)
    # Stand-alone build
    find_package(spdlog REQUIRED)
endif()

# I don't really care if I use GTEST from github
include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.11.0
)
FetchContent_MakeAvailable(googletest)
add_library(GTest::GTest INTERFACE IMPORTED)
target_link_libraries(GTest::GTest INTERFACE gtest_main)

# TODO make subdirectory cmake files when ready

add_library(common
            INTERFACE)
target_include_directories(common INTERFACE src/common/)


# Create Evaulator Library
add_library(evaluator 
            src/evaluator/evaluator.hpp 
            src/evaluator/evaluator.cpp )

target_link_libraries(evaluator PRIVATE spdlog::spdlog)

# Create Evaulator Library
add_library(algo 
            src/algo/algo.hpp 
            src/algo/minimaxalgo.hpp
            src/algo/minimaxalgo.cpp
            src/algo/abminimaxalgo.hpp
            src/algo/abminimaxalgo.cpp  )

target_link_libraries(algo
                     evaluator
                     spdlog::spdlog
                     common)                   

# Test executable application
add_executable(chessai src/main.cpp)

# Link to library
# TODO (dcuomo) add a check to build the static library if it doesn't exist
target_link_libraries(chessai 
                    evaluator
                    algo
                    ${CMAKE_SOURCE_DIR}/lib/libchess/build/static/libchess.a
                    spdlog::spdlog)

add_executable(
    hello_test
    test/hello_test.cpp
)
target_link_libraries(hello_test GTest::GTest pthread)
