#include "abminimaxalgo.hpp"
#include <iostream>

namespace algo {

ABMiniMaxAlgo::ABMiniMaxAlgo(int depth) : depth_{depth}, evaluator_{eval::Evaluator()} {
    done_.store(false);
    active_jobs_.store(0);
    for (unsigned int i = 0; i < THREAD_LIMIT; i++) {
        threads_.push_back(std::thread(&ABMiniMaxAlgo::WorkerThread, this));
    }
}

ABMiniMaxAlgo::~ABMiniMaxAlgo() {
    done_.store(true);
    for (unsigned int i = 0; i < threads_.size(); i++) {
        threads_[i].join();
    }
}

[[nodiscard]] libchess::Move ABMiniMaxAlgo::GetNextMove(libchess::Position* pos, const libchess::Side& color_to_play) {
    return ABMiniMaxRootNode(pos, color_to_play);
}

[[nodiscard]] libchess::Move ABMiniMaxAlgo::ABMiniMaxRootNode(libchess::Position* pos,
                                                              const libchess::Side& color_to_play) {
    // Setup the helper and storage variables
    libchess::Move best_move;
    int best_eval = BASE_VALUE;
    int alpha = BASE_VALUE;
    int beta = -1 * BASE_VALUE;
    int queued_jobs = 0;

    // Generate Moves
    auto legal_moves = GetMoveList(*pos);
    // Setup maximizing boolean
    bool is_maximizing = true;

    // Queue the Jobs
    for (const auto& move : legal_moves) {
        pos->makemove(move);
        ABMiniMaxArgs job_args = {move, *pos, color_to_play, depth_, !is_maximizing, alpha, beta};
        pos->undomove();
        // std::cout << job_args.pos << std::endl;
        // std::cout << *pos << std::endl;
        job_queue_.push(job_args);
        queued_jobs++;
    }
    // Check the results
    while (queued_jobs > 0) {
        ResultsPair res = results_queue_.pop();
        // std::cout << "Move: " << res.first << "Eval: " << res.second << std::endl;

        if (res.second > best_eval) {
            best_eval = res.second;
            best_move = res.first;
        }
        queued_jobs--;
    }
    return best_move;
}

void ABMiniMaxAlgo::WorkerThread() {
    while (!done_) {
        // Switch this to a try pop so we can interrupt the thread
        if (!job_queue_.isempty()) {
            ABMiniMaxArgs args = job_queue_.pop();
            active_jobs_++;
            int result =
                ABMiniMaxSubNode(&(args.pos), args.side, args.depth, args.is_maximizing, args.alpha, args.beta);
            results_queue_.push(algo::ResultsPair(args.move, result));
            active_jobs_--;
        } else {
            std::this_thread::yield();
        }
    }
}

[[nodiscard]] int ABMiniMaxAlgo::ABMiniMaxSubNode(libchess::Position* pos,
                                                  const libchess::Side& color_to_play,
                                                  int depth,
                                                  bool is_maximizing,
                                                  int alpha,
                                                  int beta) {
    // End recursion

    if (evaluator_.IsCheckmate(*pos) || depth == 0) {
        if (color_to_play == libchess::White) {
            return evaluator_.FullEvaluator(*pos);
        } else {
            return evaluator_.FullEvaluator(*pos) * -1;
        }
    }

    // Setup best eval
    int best_eval;
    if (is_maximizing) {
        best_eval = BASE_VALUE;
    } else {
        best_eval = -1 * BASE_VALUE;
    }

    auto legal_moves = GetMoveList(*pos);
    int count = 0;
    for (const auto& move : legal_moves) {
        pos->makemove(move);
        if (is_maximizing) {
            int eval = ABMiniMaxSubNode(pos, color_to_play, depth - 1, !is_maximizing, alpha, beta);
            if (eval > best_eval) {
                best_eval = eval;
            }
            pos->undomove();
            alpha = std::max(alpha, best_eval);
            if (beta <= alpha) {
                return best_eval;
            }
        } else {
            int eval = ABMiniMaxSubNode(pos, color_to_play, depth - 1, !is_maximizing, alpha, beta);
            if (eval < best_eval) {
                best_eval = eval;
            }
            pos->undomove();
            beta = std::min(beta, best_eval);
            if (beta <= alpha) {
                return best_eval;
            }
        }
        count++;
    }
    return best_eval;
}

}  // namespace algo