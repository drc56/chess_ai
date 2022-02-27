#include <iostream>
#include <string>
#include <libchess/position.hpp>

int main(int argc, char const *argv[])
{
    std::string fen = "startpos";

    auto pos = libchess::Position(fen);

    std::cout << pos << std::endl;
    std::cout << std::endl;
    return 0;
}
