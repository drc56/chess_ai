#ifndef EVALUATOR_H
#define EVALUATOR_H

#include <libchess/bitboard.hpp>
#include <libchess/position.hpp>
#include <libchess/side.hpp>
#include <libchess/square.hpp>

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
constexpr int MOBILITY_WEIGHT = 10;

class Evaluator
{

public:
    Evaluator(/* args */);
    ~Evaluator();
    [[nodiscard]] bool IsCheckmate(const libchess::Position& eval_position);

    template<libchess::Piece piece>
    [[nodiscard]] int CountControlSquares(const libchess::Position& eval_position, const libchess::Side& color, libchess::Bitboard(*func)(libchess::Square, const libchess::Bitboard&));
    
    template<libchess::Piece piece>
    [[nodiscard]] int CountControlSquares(const libchess::Position& eval_position, const libchess::Side& color, libchess::Bitboard(*func)(libchess::Square));
    
    [[nodiscard]] int MobilityEvaluator(const libchess::Position& eval_position);
    [[nodiscard]] int MaterialEvaluator(const libchess::Position& eval_position);
    [[nodiscard]] int FullEvaluator(const libchess::Position& eval_position);
    // BasicPieceEval()
private:
    /* data */
};
}

#endif