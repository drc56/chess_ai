#include <gtest/gtest.h>
#include <array>
#include <libchess/move.hpp>
#include <libchess/position.hpp>
#include <memory>
#include <string>
#include <utility>
#include "../src/algo/abminimaxalgo.hpp"

static constexpr int TEST_DEPTH = 5;

class ABPMiniMaxTest : public ::testing::Test {
   protected:
    void SetUp() override {
        abminimax_ = std::make_unique<algo::ABMiniMaxAlgo>(TEST_DEPTH);
    }
    algo::ABMiniMaxAlgoPtr abminimax_;
};

TEST(ABPMiniMax, Construction) {
    EXPECT_NO_THROW(algo::ABMiniMaxAlgo(5));
}

using fen = std::string;
// correct move, opponent move
using solution_moves = std::pair<std::string, std::string>;
using solution = std::vector<solution_moves>;
using PuzzlePair = std::pair<fen, solution>;

TEST_F(ABPMiniMaxTest, CheckmatePatterns){
    std::array<PuzzlePair, 4> test_cases = {
        std::make_pair("6k1/3qb1pp/4p3/ppp1P3/8/2PP1Q2/PP4PP/5RK1 w - - 0 1", solution({{"f3f7", "g8h8"}, {"f7f8", "e7f8"}, {"f1f8", "end"}})),
        std::make_pair("R7/4kp2/5N2/4P3/8/8/8/6K1 w - - 0 1", solution({{"a8e8", "end"}})),
        std::make_pair("5r1b/2R1R3/P4r2/2p2Nkp/2b3pN/6P1/4PP2/6K1 w - - 0 1", solution({{"e7g7", "h8g7"}, {"c7g7", "f6g6"}, {"g7g6","end"}})),
        std::make_pair("5r1k/1b2Nppp/8/2R5/4Q3/8/5PPP/6K1 w - - 0 1", solution({{"e4h7", "h8h7"}, {"c5h5", "end"}}))};

    for (auto& test_case : test_cases) {
        libchess::Position test_pos(test_case.first);
        for (auto& move : test_case.second) {
            auto guess = abminimax_->GetNextMove(&test_pos, test_pos.turn());
            EXPECT_EQ(static_cast<std::string>(guess), move.first);
            if (move.second == "end") {
                break;
            }
            test_pos.makemove(move.first);
            test_pos.makemove(move.second);
        }
    }
}

TEST_F(ABPMiniMaxTest, SimpleFork) {
    // TODO (Dan) find a way to load these from a file? JSON or something
    std::array<PuzzlePair, 2> test_cases = {
        std::make_pair("2q3k1/8/8/5N2/6P1/7K/8/8 w - - 0 1", solution({{"f5e7", "g8f7"}, {"e7c8", "end"}})),
        std::make_pair("6k1/5r1p/p2N4/nppP2q1/2P5/1P2N3/PQ5P/7K w - - 0 1",
                       solution({{"b2h8", "g8h8"}, {"d6f7", "h8g7"}, {"f7g5", "end"}}))};

    for (auto& test_case : test_cases) {
        libchess::Position test_pos(test_case.first);
        for (auto& move : test_case.second) {
            auto guess = abminimax_->GetNextMove(&test_pos, test_pos.turn());
            EXPECT_EQ(static_cast<std::string>(guess), move.first);
            if (move.second == "end") {
                break;
            }
            test_pos.makemove(move.first);
            test_pos.makemove(move.second);
        }
    }
}