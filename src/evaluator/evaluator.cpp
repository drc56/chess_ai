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

[[nodiscard]] bool Evaluator::IsCheckmate(const libchess::Position& eval_position){
    return eval_position.in_check() && eval_position.legal_moves().empty();
}

[[nodiscard]] double Evaluator::MaterialEvaluator(const libchess::Position& eval_position)
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

[[nodiscard]] double Evaluator::FullEvaluator(const libchess::Position& eval_position)
{
    double pos_eval = 0.0;

    if(IsCheckmate(eval_position))
    {
        // If it's white turn that means black made the checkmate.
        if(eval_position.turn() == libchess::White)
            return -1000.0;
        else
            return 1000.0;
    }

    // TODO Add more evaluation steps
    pos_eval += MaterialEvaluator(eval_position);

    return pos_eval;
}

} // namespace eval