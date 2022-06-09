#ifndef MINIMAX_ALGO_H
#define MINIMAX_ALGO_H

#include <libchess/move.hpp>
#include <libchess/position.hpp>
#include "../evaluator/evaluator.hpp"
#include "algo.hpp"

namespace algo {

class MiniMaxAlgo : public ChessAiAlgo {
   public:
    MiniMaxAlgo(int depth);
    [[nodiscard]] libchess::Move GetNextMove(libchess::Position* pos, const libchess::Side& color_to_play) override;

   private:
    // Function
    [[nodiscard]] libchess::Move MiniMaxRootNode(libchess::Position* pos, const libchess::Side& color_to_play);
    [[nodiscard]] int MiniMaxSubNode(libchess::Position* pos,
                                     const libchess::Side& color_to_play,
                                     int depth,
                                     bool is_maximizing);
    // Member Variables
    int depth_;
    eval::Evaluator evaluator_;
};

}  // namespace algo

#endif
