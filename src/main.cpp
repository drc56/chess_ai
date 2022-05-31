#include <iostream>
#include <string>
#include <libchess/position.hpp>
#include <libchess/side.hpp>
#include <libchess/piece.hpp>
#include "evaluator/evaluator.hpp"

int main(int argc, char const *argv[])
{
    std::string fen = "1Q6/p7/q1p3p1/3p4/2kPpP2/4P1P1/P2B2K1/3r4 w - - 4 34";

    auto pos = libchess::Position(fen);

    std::cout << pos << std::endl;
    std::cout << std::endl;

    for(const auto& move : pos.legal_moves()){
        std::cout << "Move is: " << move << std::endl;
    }    

    auto evaluator = eval::Evaluator();
    std::cout << "Position value is : " << evaluator.FullEvaluator(pos) << std::endl;

    return 0;
}
