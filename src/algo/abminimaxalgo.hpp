#ifndef AB_MINIMAX_ALGO_H
#define AB_MINIMAX_ALGO_H

#include "algo.hpp"
#include "../evaluator/evaluator.hpp"
#include <libchess/move.hpp>
#include <libchess/position.hpp>

namespace algo {

constexpr double BASE_VALUE = -9999.9;

class ABMiniMaxAlgo : public ChessAiAlgo {
    public:
        ABMiniMaxAlgo(int depth);
        [[nodiscard]] libchess::Move GetNextMove(libchess::Position* pos, const libchess::Side& color_to_play) override;
    private:
        // Function
        [[nodiscard]] libchess::Move ABMiniMaxRootNode(libchess::Position* pos, const libchess::Side& color_to_play);
        [[nodiscard]] double ABMiniMaxSubNode(libchess::Position* pos, const libchess::Side& color_to_play, int depth, bool is_maximizing, double alpha, double beta); 
        // Member Variables
        int depth_;
        eval::Evaluator evaluator_;
};

} // namespace algo


#endif
