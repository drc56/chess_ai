#include "minimaxalgo.hpp"
#include <iostream>

namespace algo{

MiniMaxAlgo::MiniMaxAlgo(int depth) : depth_{depth}, evaluator_{eval::Evaluator()}
{

}

[[nodiscard]] libchess::Move MiniMaxAlgo::GetNextMove(libchess::Position* pos, const libchess::Side& color_to_play) 
{
    return MiniMaxRootNode(pos, color_to_play);
}

[[nodiscard]] libchess::Move MiniMaxAlgo::MiniMaxRootNode(libchess::Position* pos, const libchess::Side& color_to_play)
{
    // Variables to store current best move and evaluation
    libchess::Move best_move;
    int best_eval = -99999;

    // Get the legal moves in this position
    // This by default is ordered captures than all other moves
    // TODO look into reordering with checks first
    auto legal_moves = GetMoveList(*pos);

    // We always start with maximizing
    bool is_maximizing = true;

    for(const auto& move : legal_moves){
        // make the move
        pos->makemove(move);
        
        int current_eval = MiniMaxSubNode(pos, color_to_play, depth_, !is_maximizing);
        // if(color_to_play == libchess::Black){
        //     current_eval = current_eval * -1;
        // }
        std::cout << "Move: " << move << "eval: " << current_eval << std::endl;

        if(current_eval > best_eval){
            best_eval = current_eval;
            best_move = move;
            std::cout << "BEST Move: " << move << "eval: " << best_eval << std::endl;
        }
        // undo the move at the end
        pos->undomove();
    }
    return best_move;
}

[[nodiscard]] int MiniMaxAlgo::MiniMaxSubNode(libchess::Position* pos, const libchess::Side& color_to_play, int depth, bool is_maximizing)
{

    // Check if the depth is over
    if(depth == 0 || evaluator_.IsCheckmate(*pos)){
        if(color_to_play == libchess::White){
            return evaluator_.FullEvaluator(*pos);
        }
        else{
            return evaluator_.FullEvaluator(*pos) * -1;
        }

    }

    // Set the best eval based on color and if maximizing or minimizing
    int best_eval = 0;
    if(is_maximizing){
        best_eval = -99999;
    }
    else{
        best_eval = 99999;
    }

    auto legal_moves = GetMoveList(*pos);
    for(const auto& move : legal_moves){
        pos->makemove(move);

        if(is_maximizing){
            auto cur_eval = MiniMaxSubNode(pos, color_to_play, depth-1, !is_maximizing);
            // if(color_to_play == libchess::Black){
            //     cur_eval = cur_eval * -1;
            // }
            best_eval = std::max(best_eval, cur_eval);
        }
        else{
            auto cur_eval = MiniMaxSubNode(pos, color_to_play, depth-1, !is_maximizing);
            // if(color_to_play == libchess::Black){
            //     cur_eval = cur_eval * -1;
            // }
            best_eval = std::min(best_eval, cur_eval);

        }
        pos->undomove();
    }

    return best_eval;
} 


} // namespace algo