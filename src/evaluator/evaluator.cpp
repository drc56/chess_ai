#include "evaluator.hpp"
#include <iostream>
#include <libchess/side.hpp>
#include <libchess/piece.hpp>

namespace eval{

Evaluator::Evaluator(/* args */)
{
}

Evaluator::~Evaluator()
{
}

[[nodiscard]] bool Evaluator::IsCheckmate(const libchess::Position& eval_position){
    return eval_position.in_check() && eval_position.legal_moves().empty();
}

[[nodiscard]] int Evaluator::MaterialEvaluator(const libchess::Position& eval_position)
{
    // Evaluate White Pieces
    int white_material = eval_position.pieces(libchess::White, libchess::Pawn).count() * PAWN_WEIGHT +
        eval_position.pieces(libchess::White, libchess::Knight).count() * KNIGHT_WEIGHT +
        eval_position.pieces(libchess::White, libchess::Bishop).count() * BISHOP_WEIGHT +
        eval_position.pieces(libchess::White, libchess::Rook).count() * ROOK_WEIGHT +
        eval_position.pieces(libchess::White, libchess::Queen).count() * QUEEN_WEIGHT;

    // Evaluate White Pieces
    int black_material = -1 * (eval_position.pieces(libchess::Black, libchess::Pawn).count() * PAWN_WEIGHT +
        eval_position.pieces(libchess::Black, libchess::Knight).count() * KNIGHT_WEIGHT +
        eval_position.pieces(libchess::Black, libchess::Bishop).count() * BISHOP_WEIGHT +
        eval_position.pieces(libchess::Black, libchess::Rook).count() * ROOK_WEIGHT +
        eval_position.pieces(libchess::Black, libchess::Queen).count() * QUEEN_WEIGHT);

    return white_material + black_material;
}

[[nodiscard]] int Evaluator::FullEvaluator(const libchess::Position& eval_position)
{
    int pos_eval = 0;

    if(IsCheckmate(eval_position))
    {
        // If it's white turn that means black made the checkmate.
        if(eval_position.turn() == libchess::White)
            return -10000;
        else
            return 10000;
    }

    // TODO Add more evaluation steps
    pos_eval += MaterialEvaluator(eval_position);
    return pos_eval;
}

} // namespace eval