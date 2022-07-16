#ifndef ALGO_H
#define ALGO_H

#include <libchess/move.hpp>
#include <libchess/position.hpp>
#include <libchess/side.hpp>
#include <memory>

enum class AlgoType
{
    MiniMax = 0,
    ABMiniMax = 1
};

namespace algo {

class ChessAiAlgo {
   public:
    [[nodiscard]] virtual libchess::Move GetNextMove(libchess::Position* pos, const libchess::Side& color_to_play) = 0;

   protected:
    [[nodiscard]] std::vector<libchess::Move> GetMoveList(const libchess::Position& pos) {
        return pos.legal_moves();
    }
};

using ChessAiAlgoPtr = std::unique_ptr<ChessAiAlgo>;

}  // namespace algo

#endif  // ALGO_H
