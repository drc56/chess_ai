#ifndef EVALUATOR_H
#define EVALUATOR_H

#include <libchess/position.hpp>

namespace eval{

/**
 * @brief EvalResult
 * Structu to contain what is returned from the evaluator.
 */

constexpr double PAWN_WEIGHT = 1.0;
constexpr double KNIGHT_WEIGHT = 3.0;
constexpr double BISHOP_WEIGHT = 3.0;
constexpr double ROOK_WEIGHT = 5.0;
constexpr double QUEEN_WEIGHT = 9.0;

class Evaluator
{

public:
    Evaluator(/* args */);
    ~Evaluator();
    [[nodiscard]] bool IsCheckmate(const libchess::Position& eval_position);
    [[nodiscard]] double MaterialEvaluator(const libchess::Position& eval_position);
    [[nodiscard]] double FullEvaluator(const libchess::Position& eval_position);
    // BasicPieceEval()
private:
    /* data */
};
}

#endif