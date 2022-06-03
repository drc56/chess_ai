project(ChessAi)

#Configure C++ & CMake
cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_STANDARD 17)

# Set build location
set(EXECUTABLE_OUTPUT_PATH build/ CACHE PATH "Build directory" FORCE)

#Set libchess include directories
include_directories(${CMAKE_SOURCE_DIR}/lib/libchess/src)

# TODO make subdirectory cmake files when ready
# Create Evaulator Library
add_library(evaluator 
            src/evaluator/evaluator.hpp 
            src/evaluator/evaluator.cpp )

# Create Evaulator Library
add_library(algo 
            src/algo/algo.hpp 
            src/algo/minimaxalgo.hpp
            src/algo/minimaxalgo.cpp
            src/algo/abminimaxalgo.hpp
            src/algo/abminimaxalgo.cpp  )

target_link_libraries(algo
                     evaluator)                   

# Test executable application
add_executable(chessai src/main.cpp)

# Link to library
# TODO (dcuomo) add a check to build the static library if it doesn't exist
target_link_libraries(chessai 
                    evaluator
                    algo
                    ${CMAKE_SOURCE_DIR}/lib/libchess/build/static/libchess.a)

