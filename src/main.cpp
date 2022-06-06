
#include <chrono>
#include <iostream>
#include <string>
#include <libchess/position.hpp>
#include <libchess/side.hpp>
#include <libchess/piece.hpp>
#include <spdlog/spdlog.h>


#include "evaluator/evaluator.hpp"
#include "algo/minimaxalgo.hpp"
#include "algo/abminimaxalgo.hpp"

#include "spdlog/spdlog.h"

int main(int argc, char const *argv[])
{
    spdlog::info("Starting chess ai!");
    // std::string fen = "2Q5/1p1r2kp/p4pq1/6p1/2P5/1PB5/P4PPK/4r3 w - - 0 42";
    std::string fen = "r7/ppQ5/k7/3q1N2/3B4/N7/P3rnPP/1KR5 b - - 0 27";
    // std::string fen = "r4r1k/3q3p/2p2pnQ/ppb1pN2/3pP3/P2P2PP/BP3P2/3R2K1 w - - 1 24";

    auto pos = libchess::Position(fen);

    std::cout << pos << std::endl;
    std::cout << pos.get_fen() << std::endl;
    std::cout << std::endl;

    // for(const auto& move : pos.legal_moves()){
    //     std::cout << "Move is: " << move << std::endl;
    // }    

    // auto evaluator = eval::Evaluator();
    // std::cout << "Position value is : " << evaluator.FullEvaluator(pos) << std::endl;

    // auto start = std::chrono::high_resolution_clock::now();
    // auto minimax = algo::MiniMaxAlgo(5);
    // auto next_move = minimax.GetNextMove(&pos, libchess::Black);
    // auto stop = std::chrono::high_resolution_clock::now();
    // auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

    // std::cout << "minimax move to play is: " << next_move << " Time taken: " << duration.count() << std::endl;


    auto start = std::chrono::high_resolution_clock::now();
    auto abminimax = algo::ABMiniMaxAlgo(5);
    auto next_move = abminimax.GetNextMove(&pos, libchess::Black);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

    std::cout << "abpminimax move to play is: " << next_move << " Time taken: " << duration.count() << std::endl;
    return 0;
}
