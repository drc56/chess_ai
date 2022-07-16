
#include "gamemanager.hpp"
#include "../algo/abminimaxalgo.hpp"
#include "../algo/minimaxalgo.hpp"

namespace game {

GameManager::GameManager(const AlgoType& ai_type, const int ai_depth, const libchess::Side ai_side_to_play)
    : ai_side_(ai_side_to_play), side_to_play_(libchess::White) {
    // TODO make this a loader somewhere contained in algo..
    switch (ai_type) {
        case AlgoType::MiniMax:
            ai_.reset(new algo::MiniMaxAlgo(ai_depth));
            break;
        case AlgoType::ABMiniMax:
            ai_.reset(new algo::ABMiniMaxAlgo(ai_depth));
            break;
    }

    // Set the game to start position
    cur_position_.set_fen("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
}

std::string GameManager::GetAiMove() {
    libchess::Move next_move = ai_->GetNextMove(&cur_position_, ai_side_);
    return std::string(next_move);
}

std::string GameManager::GetUserMove() {
    std::string move;
    std::cin >> move;
    return move;
}

bool GameManager::CheckMoveIsValid(const std::string& move) {
    try {
        cur_position_.parse_move(move);
    } catch (std::invalid_argument&) {
        return false;
    }
    return true;
}

void GameManager::PrintEndDetails() {
    if (cur_position_.is_stalemate()) {
        std::cout << "Game is a stalemate" << std::endl;
    } else if (cur_position_.is_draw()) {
        std::cout << "Game is a draw" << std::endl;
    } else if (cur_position_.is_checkmate()) {
        if (!cur_position_.turn() == libchess::White) {
            std::cout << "Checkmate: White wins! " << std::endl;
        } else {
            std::cout << "Checkmate: Black wins! " << std::endl;
        }
    } else {
        std::cout << "Huh?" << std::endl;
    }
}

void GameManager::RunGame() {
    while (!cur_position_.is_checkmate() && !cur_position_.is_draw() && !cur_position_.is_stalemate()) {
        bool move_made = false;
        if (side_to_play_ == ai_side_) {
            while (!move_made) {
                std::string move = GetAiMove();
                if (CheckMoveIsValid(move)) {
                    cur_position_.makemove(move);
                    std::cout << "Ai made move " << move << std::endl;
                    move_made = true;
                }
            }
        } else {
            while (!move_made) {
                std::cout << "Make a move in algebraic notation ex: d2d4 " << std::endl;
                std::string move = GetUserMove();
                if (CheckMoveIsValid(move)) {
                    cur_position_.makemove(move);
                    move_made = true;
                } else {
                    std::cout << "Invalid move, please make a valid move" << std::endl;
                }
            }
        }
        side_to_play_ = !side_to_play_;
        std::cout << "Current position: " << std::endl;
        PrintBoard();
    }
    std::cout << "Game Over!" << std::endl;
    PrintEndDetails();
}

}  // namespace game
