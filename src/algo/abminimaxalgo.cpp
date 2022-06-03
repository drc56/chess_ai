#include "abminimaxalgo.hpp"
#include <iostream>
namespace algo
{
    
ABMiniMaxAlgo::ABMiniMaxAlgo(int depth) : depth_{depth}, evaluator_{eval::Evaluator()}
{

}

[[nodiscard]] libchess::Move ABMiniMaxAlgo::GetNextMove(libchess::Position* pos, const libchess::Side& color_to_play) 
{
    return ABMiniMaxRootNode(pos, color_to_play);
}

[[nodiscard]] libchess::Move ABMiniMaxAlgo::ABMiniMaxRootNode(libchess::Position* pos, const libchess::Side& color_to_play)
{

    // Setup the helper and storage variables
    libchess::Move best_move;
    double best_eval = (color_to_play == libchess::White) ? BASE_VALUE : -1.0 * BASE_VALUE;
    double alpha, beta = BASE_VALUE;
    if(color_to_play == libchess::White){
        beta = beta * -1.0;
    }
    else{
        alpha = alpha * -1.0;
    }

    // Generate Moves
    auto legal_moves = GetMoveList(*pos);

    // Setup maximizing boolean
    bool is_maximizing = true;

    for(const auto& move : legal_moves){
        pos->makemove(move);
        switch (color_to_play){
            case libchess::White:
            {
                double eval = ABMiniMaxSubNode(pos, color_to_play, depth_, !is_maximizing, alpha, beta);
                if(eval > best_eval){
                    best_eval = eval;
                    best_move = move;
                }
                break;
            }
            case libchess::Black:
            {
                double eval = ABMiniMaxSubNode(pos, color_to_play, depth_, !is_maximizing, alpha, beta);
                if(eval < best_eval){
                    best_eval = eval;
                    best_move = move;
                }
                break;
            }
        }
        pos->undomove();
    }

    return best_move;
}

[[nodiscard]] double ABMiniMaxAlgo::ABMiniMaxSubNode(libchess::Position* pos, const libchess::Side& color_to_play, int depth, bool is_maximizing, double alpha, double beta)
{
    // End recursion
    if(evaluator_.IsCheckmate(*pos) || depth == 0){
        return evaluator_.FullEvaluator(*pos);
    }

    // Setup best eval
    double best_eval;
    switch (color_to_play){
        case libchess::White:
        {
            if(is_maximizing){
                best_eval = BASE_VALUE;
            }
            else{
                best_eval = -1.0 * BASE_VALUE;
            }
            break;
        }
        case libchess::Black:
        {
            if(is_maximizing){
                best_eval = -1.0 * BASE_VALUE;
            }
            else{
                best_eval = BASE_VALUE;
            }
            break;
        }
    }

    auto legal_moves = GetMoveList(*pos);
    int count = 0;
    for(const auto& move : legal_moves){
        pos->makemove(move);
        if(color_to_play == libchess::White){
            if(is_maximizing){
                double eval = ABMiniMaxSubNode(pos, color_to_play, depth-1, !is_maximizing, alpha, beta);
                if(eval > best_eval){
                    best_eval = eval;
                }
                alpha = std::max(alpha, best_eval);
                if(beta <= alpha){
                    pos->undomove();
                    break;
                }
            }
            else{
                double eval = ABMiniMaxSubNode(pos, color_to_play, depth-1, !is_maximizing, alpha, beta);
                if(eval < best_eval){
                    best_eval = eval;
                }
                beta = std::min(beta, best_eval);
                if(beta <= alpha){
                    pos->undomove();
                    break;
                }
            }
        }
        else{
            if(is_maximizing){
                double eval = ABMiniMaxSubNode(pos, color_to_play, depth-1, !is_maximizing, alpha, beta);
                if(eval < best_eval){
                    best_eval = eval;
                }
                alpha = std::min(alpha, best_eval);
                if(beta >= alpha){
                    pos->undomove();
                    break;
                }
            }
            else{
                double eval = ABMiniMaxSubNode(pos, color_to_play, depth-1, !is_maximizing, alpha, beta);
                if(eval > best_eval){
                    best_eval = eval;
                }
                beta = std::max(beta, best_eval);
                if(beta >= alpha){
                    pos->undomove();
                    break;
                }
            }
        }
        pos->undomove();
        count++;
    }
    return best_eval;
} 
     

} //namespace algo