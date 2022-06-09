
#include <chrono>
#include <iostream>
#include <string>
#include <libchess/position.hpp>
#include <libchess/side.hpp>
#include <libchess/piece.hpp>
#include <libchess/movegen.hpp>
#include <spdlog/spdlog.h>


#include "evaluator/evaluator.hpp"
#include "algo/minimaxalgo.hpp"
#include "algo/abminimaxalgo.hpp"

#include "spdlog/spdlog.h"

int main(int argc, char const *argv[])
{
    spdlog::info("Starting chess ai!");
    // std::string fen = "2Q5/1p1r2kp/p4pq1/6p1/2P5/1PB5/P4PPK/4r3 w - - 0 42";
    // std::string fen = "r7/ppQ5/k7/3q1N2/3B4/N7/P3rnPP/1KR5 b - - 0 27";
    // std::string fen = "r4r1k/3q3p/2p2pnQ/ppb1pN2/3pP3/P2P2PP/BP3P2/3R2K1 w - - 1 24";
    // std::string fen = "5k2/7R/2p2KP1/p1p2p2/5P2/1P4q1/P2p4/8 w - - 0 45";
    // std::string fen = "2q3k1/8/8/5N2/6P1/7K/8/8 w - - 0 1";
    // std::string fen = "2q3k1/8/8/5N2/6P1/7K/8/8 b - - 0 1";
    // std::string fen = "r3k3/7p/6p1/5p2/5r2/2NP4/PPP2PPP/R5K1 w - - 0 1"; // 3 mover
    // std::string fen = "r3k3/7p/6p1/3N1p2/7r/3P4/PPP2PPP/R5K1 w - - 2 2"; //kngiht fork w/ tolns of pawns
    // std::string fen = "r3k3/7p/6p1/3N1p2/7r/8/P5PP/R5K1 w - - 2 2"; //kngiht fork w/o tons of pawns
    // std::string fen = "r7/2Nk3p/6p1/5p2/7r/8/P5PP/R5K1 w - - 4 3";
    // std::string fen = "2q3k1/8/8/5N2/6P1/7K/8/8 w - - 0 1";
    // std::string fen = "6k1/5r1p/p2N4/nppP2q1/2P5/1P2N3/PQ5P/7K w - - 0 1";
    std::string fen = "8/4kprb/6p1/6Pp/4B2P/P7/8/1K2R3 b - - 0 1";
    auto pos = libchess::Position(fen);

    std::cout << pos << std::endl;
    std::cout << pos.get_fen() << std::endl;
    std::cout << std::endl;

    // for(const auto& move : pos.legal_moves()){
    //     std::cout << "Move is: " << move << std::endl;
    // }    

    auto evaluator = eval::Evaluator();
    std::cout << "Position value is : " << evaluator.FullEvaluator(pos) << std::endl;

    // auto start = std::chrono::high_resolution_clock::now();
    // auto minimax = algo::MiniMaxAlgo(3);
    // auto next_move = minimax.GetNextMove(&pos, libchess::White);
    // auto stop = std::chrono::high_resolution_clock::now();
    // auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    // std::cout << "minimax move to play is: " << next_move << " Time taken: " << duration.count() << std::endl;

    // auto start = std::chrono::high_resolution_clock::now();
    // algo::ABMiniMaxAlgo abminimax(5);
    // auto next_move = abminimax.GetNextMove(&pos, libchess::White);
    // auto stop = std::chrono::high_resolution_clock::now();
    // auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    // std::cout << "abpminimax move to play is: " << next_move << " Time taken: " << duration.count() << std::endl;

    // pos.makemove("f5e7");
    // pos.makemove("g8f7");

    // start = std::chrono::high_resolution_clock::now();
    // next_move = abminimax.GetNextMove(&pos, libchess::White);
    // stop = std::chrono::high_resolution_clock::now();
    // duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    // std::cout << "abpminimax move to play is: " << next_move << " Time taken: " << duration.count() << std::endl;



    return 0;
}
