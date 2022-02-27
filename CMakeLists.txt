# Set build location
set(EXECUTABLE_OUTPUT_PATH build/ CACHE PATH "Build directory" FORCE)
# Test executable application
add_executable(chessai src/main.cpp)

# Need to build with CPP 17 for lib chess
set_target_properties(chessai PROPERTIES
            CXX_STANDARD 17
            )

# Set the include directories for the libchess header files
target_include_directories(
    chessai
    PRIVATE
    ${CMAKE_SOURCE_DIR}/lib/libchess/src
)

# Link to library
# TODO (dcuomo) add a check to build the static library if it doesn't exist
target_link_libraries(chessai ${CMAKE_SOURCE_DIR}/lib/libchess/build/static/libchess.a)

