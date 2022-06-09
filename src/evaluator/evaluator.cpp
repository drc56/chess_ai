#include "evaluator.hpp"
#include <iostream>
#include <libchess/piece.hpp>
#include <libchess/movegen.hpp>


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

template<libchess::Piece piece>
[[nodiscard]] int Evaluator::CountControlSquares(const libchess::Position& eval_position,const libchess::Side& color, libchess::Bitboard(*func)(libchess::Square, const libchess::Bitboard&))
{
    int total_moves = 0;
    for (const auto& sq : eval_position.pieces(color, piece) ){
        auto same_side_pieces = eval_position.occupancy(!color);
        auto moves = func(sq, eval_position.occupied());
        moves = moves ^ same_side_pieces ^ sq;
        total_moves += moves.count();
    }
    return total_moves * MOBILITY_WEIGHT;
}

template<>
[[nodiscard]] int Evaluator::CountControlSquares<libchess::Piece::Knight>(const libchess::Position& eval_position, const libchess::Side& color, libchess::Bitboard(*func)(libchess::Square))
{

    int total_moves = 0;
    for (const auto& sq : eval_position.pieces(color, libchess::Piece::Knight) ){
        auto same_side_pieces = eval_position.occupancy(!color);
        auto moves = func(sq);
        moves = moves ^ same_side_pieces ^ sq;
        total_moves += moves.count();
    }
    return total_moves * MOBILITY_WEIGHT;
}

[[nodiscard]] int Evaluator::MobilityEvaluator(const libchess::Position& eval_position)
{
    // Psuedo legal move generation to judge mobility
    // My idea here is I care about "controlled squares"
    
    int knight_mobility_score = CountControlSquares<libchess::Knight>(eval_position, libchess::White, &libchess::movegen::knight_moves) 
                                - CountControlSquares<libchess::Knight>(eval_position, libchess::Black, &libchess::movegen::knight_moves);
    int bishop_mobility_score = CountControlSquares<libchess::Bishop>(eval_position, libchess::White, &libchess::movegen::bishop_moves) 
                                - CountControlSquares<libchess::Bishop>(eval_position, libchess::Black, &libchess::movegen::bishop_moves); 
    int rook_mobility_score = CountControlSquares<libchess::Rook>(eval_position, libchess::White, &libchess::movegen::rook_moves) 
                                - CountControlSquares<libchess::Rook>(eval_position, libchess::Black, &libchess::movegen::rook_moves); 
    int queen_mobility_score = CountControlSquares<libchess::Queen>(eval_position, libchess::White, &libchess::movegen::queen_moves) 
                                - CountControlSquares<libchess::Queen>(eval_position, libchess::Black, &libchess::movegen::queen_moves); 
    return knight_mobility_score + bishop_mobility_score + rook_mobility_score;
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
    pos_eval += MobilityEvaluator(eval_position);
    return pos_eval;
}

} // namespace eval