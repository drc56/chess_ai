#include "evaluator.hpp"

#include <libchess/side.hpp>
#include <libchess/piece.hpp>

namespace eval{

Evaluator::Evaluator(/* args */)
{
}

Evaluator::~Evaluator()
{
}

double Evaluator::MaterialEvaluator(const libchess::Position& eval_position)
{
    // Evaluate White Pieces
    double white_material = eval_position.pieces(libchess::White, libchess::Pawn).count() * PAWN_WEIGHT +
        eval_position.pieces(libchess::White, libchess::Knight).count() * KNIGHT_WEIGHT +
        eval_position.pieces(libchess::White, libchess::Bishop).count() * BISHOP_WEIGHT +
        eval_position.pieces(libchess::White, libchess::Rook).count() * ROOK_WEIGHT +
        eval_position.pieces(libchess::White, libchess::Queen).count() * QUEEN_WEIGHT;

    // Evaluate White Pieces
    double black_material = -1.0 * (eval_position.pieces(libchess::Black, libchess::Pawn).count() * PAWN_WEIGHT +
        eval_position.pieces(libchess::Black, libchess::Knight).count() * KNIGHT_WEIGHT +
        eval_position.pieces(libchess::Black, libchess::Bishop).count() * BISHOP_WEIGHT +
        eval_position.pieces(libchess::Black, libchess::Rook).count() * ROOK_WEIGHT +
        eval_position.pieces(libchess::Black, libchess::Queen).count() * QUEEN_WEIGHT);

    return white_material + black_material;
}

double Evaluator::FullEvaluator(const libchess::Position& eval_position)
{
    // TODO Add more evaluation steps
    return MaterialEvaluator(eval_position);
}

} // namespace eval