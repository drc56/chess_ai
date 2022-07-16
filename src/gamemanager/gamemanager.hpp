
#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include <iostream>
#include <libchess/movegen.hpp>
#include <libchess/piece.hpp>
#include <libchess/position.hpp>
#include <libchess/side.hpp>
#include <string>
#include "../algo/algo.hpp"

namespace game {

class GameManager {
   public:
    GameManager(const AlgoType& ai_type,
                const int ai_depth,
                const libchess::Side ai_side_to_play);  // Function the will run the game and take user input
    void RunGame();

   private:
    std::string GetAiMove();
    std::string GetUserMove();
    bool CheckMoveIsValid(const std::string& move);
    bool MakeMove(const std::string& move);
    void PrintBoard() {
        std::cout << cur_position_ << std::endl;
    }
    void PrintEndDetails();

    // Game Related Variables
    libchess::Position cur_position_;
    algo::ChessAiAlgoPtr ai_;
    libchess::Side ai_side_;
    libchess::Side side_to_play_;
};

}  // namespace game

#endif  // GAME_MANAGER_H