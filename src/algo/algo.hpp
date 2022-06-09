#ifndef ALGO_H
#define ALGO_H

#include <libchess/move.hpp>
#include <libchess/position.hpp>
#include <libchess/side.hpp>

namespace algo {

class ChessAiAlgo {
   public:
    [[nodiscard]] virtual libchess::Move GetNextMove(libchess::Position* pos, const libchess::Side& color_to_play) = 0;

   protected:
    [[nodiscard]] std::vector<libchess::Move> GetMoveList(const libchess::Position& pos) {
        return pos.legal_moves();
    }
};

}  // namespace algo

#endif  // ALGO_H
