#include <iostream>
#include <string>
#include <libchess/position.hpp>
#include <libchess/side.hpp>
#include <libchess/piece.hpp>
#include "evaluator/evaluator.hpp"
#include "algo/minimaxalgo.hpp"

int main(int argc, char const *argv[])
{
    std::string fen = "2Q5/1p1r2kp/p4pq1/6p1/2P5/1PB5/P4PPK/4r3 w - - 0 42";
    // std::string fen = "8/p7/q1p3p1/3p4/2kPpP2/1Q2P1P1/P2B2K1/3r4 b - - 5 34";
    // std::string fen = "8/p7/q1p3p1/3p4/1QkPpP2/4P1P1/P2B2K1/3r4 b - - 5 34";

    auto pos = libchess::Position(fen);

    std::cout << pos << std::endl;
    std::cout << std::endl;

    for(const auto& move : pos.legal_moves()){
        std::cout << "Move is: " << move << std::endl;
    }    

    auto evaluator = eval::Evaluator();
    std::cout << "Position value is : " << evaluator.FullEvaluator(pos) << std::endl;

    auto minimax = algo::MiniMaxAlgo(3);
    auto next_move = minimax.GetNextMove(&pos, libchess::White);

    std::cout << "The move to play is: " << next_move << std::endl;

    return 0;
}
