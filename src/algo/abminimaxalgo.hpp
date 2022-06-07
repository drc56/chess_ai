#ifndef AB_MINIMAX_ALGO_H
#define AB_MINIMAX_ALGO_H

#include "algo.hpp"
#include "../evaluator/evaluator.hpp"
#include "../common/threadsafequeue.hpp"
#include <libchess/move.hpp>
#include <libchess/position.hpp>
#include <queue>
#include <unordered_map>
#include <future>
#include <utility>
#include <thread>
#include <atomic>

namespace algo {

constexpr int BASE_VALUE = -99999;
constexpr int THREAD_LIMIT = 4;

struct ABMiniMaxArgs{
    libchess::Move move;
    libchess::Position pos;
    libchess::Side side;
    int depth;
    bool is_maximizing;
    int alpha;
    int beta;
};

using ResultsPair = std::pair<libchess::Move, int>;

class ABMiniMaxAlgo : public ChessAiAlgo {
    public:
        ABMiniMaxAlgo(int depth);
        ~ABMiniMaxAlgo();
        [[nodiscard]] libchess::Move GetNextMove(libchess::Position* pos, const libchess::Side& color_to_play) override;
    private:
        // Function
        [[nodiscard]] libchess::Move ABMiniMaxRootNode(libchess::Position* pos, const libchess::Side& color_to_play);
        [[nodiscard]] int ABMiniMaxSubNode(libchess::Position* pos, const libchess::Side& color_to_play, int depth, bool is_maximizing, int alpha, int beta); 
        void WorkerThread();
        
        // Member Variables
        int depth_;
        eval::Evaluator evaluator_;
        // std::unordered_map<libchess::Move, std::future<double>> thread_pool_;

        // Thread Pool related variables
        common::ThreadSafeQueue<ResultsPair> results_queue_;
        common::ThreadSafeQueue<ABMiniMaxArgs> job_queue_;
        std::vector<std::thread> threads_;
        std::atomic<bool> done_;
        std::atomic<int> active_jobs_;

};

} // namespace algo


#endif
