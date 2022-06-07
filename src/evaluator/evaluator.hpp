#ifndef EVALUATOR_H
#define EVALUATOR_H

#include <libchess/position.hpp>

namespace eval{

/**
 * @brief EvalResult
 * Structu to contain what is returned from the evaluator.
 */

constexpr int PAWN_WEIGHT = 100;
constexpr int KNIGHT_WEIGHT = 300;
constexpr int BISHOP_WEIGHT = 300;
constexpr int ROOK_WEIGHT = 500;
constexpr int QUEEN_WEIGHT = 900;

class Evaluator
{

public:
    Evaluator(/* args */);
    ~Evaluator();
    [[nodiscard]] bool IsCheckmate(const libchess::Position& eval_position);
    [[nodiscard]] int MaterialEvaluator(const libchess::Position& eval_position);
    [[nodiscard]] int FullEvaluator(const libchess::Position& eval_position);
    // BasicPieceEval()
private:
    /* data */
};
}

#endif