#include "minimaxalgo.hpp"

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
    double best_eval = (color_to_play == libchess::White) ? -9999.9 : 9999.9;

    // Get the legal moves in this position
    // This by default is ordered captures than all other moves
    // TODO look into reordering with checks first
    auto legal_moves = GetMoveList(*pos);

    // We always start with maximizing
    bool is_maximizing = true;

    for(const auto& move : legal_moves){
        // make the move
        pos->makemove(move);
        
        double current_eval = MiniMaxSubNode(pos, color_to_play, depth_, !is_maximizing);

        switch (color_to_play){
            case libchess::White:
            {
                if(current_eval > best_eval){
                    best_eval = current_eval;
                    best_move = move;
                }
                break;
            }
            case libchess::Black:
            {
                if(current_eval < best_eval){
                    best_eval = current_eval;
                    best_move = move;
                }
                break;
            }
        }
        // undo the move at the end
        pos->undomove();
    }
    return best_move;
}

[[nodiscard]] double MiniMaxAlgo::MiniMaxSubNode(libchess::Position* pos, const libchess::Side& color_to_play, int depth, bool is_maximizing)
{
    // Check if the depth is over
    if(depth == 0 || evaluator_.IsCheckmate(*pos)){
        return evaluator_.FullEvaluator(*pos);
    }

    // Set the best eval based on color and if maximizing or minimizing
    double best_eval = 0.0;
    if(is_maximizing){
        if(color_to_play == libchess::White){
            best_eval = -9999.9;
        }
        else{
            best_eval = 9999.9;
        }
    }
    else{
        if(color_to_play == libchess::White){
            best_eval = 9999.9;
        }
        else{
            best_eval = -9999.9;
        }
    }

    auto legal_moves = GetMoveList(*pos);
    for(const auto& move : legal_moves){
        pos->makemove(move);

        if(is_maximizing){
            if(color_to_play == libchess::White){
                best_eval = std::max(best_eval, MiniMaxSubNode(pos, color_to_play, depth-1, !is_maximizing));
            }
            else{
                best_eval = std::min(best_eval, MiniMaxSubNode(pos, color_to_play, depth-1, !is_maximizing));
            }
        }
        else{
            if(color_to_play == libchess::White){
                best_eval = std::min(best_eval, MiniMaxSubNode(pos, color_to_play, depth-1, !is_maximizing));
            }
            else{
                best_eval = std::max(best_eval, MiniMaxSubNode(pos, color_to_play, depth-1, !is_maximizing));
            }
        }
        pos->undomove();
    }

    return best_eval;
} 


} // namespace algo