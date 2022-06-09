#include <gtest/gtest.h>
#include <array>
#include <string>
#include <utility>
#include <memory>

#include <libchess/position.hpp>
#include <libchess/move.hpp>
#include "../src/algo/abminimaxalgo.hpp"

static constexpr int TEST_DEPTH = 5;

class ABPMiniMaxTest : public ::testing::Test{
    protected:
        void SetUp() override{
            abminimax_ = std::make_unique<algo::ABMiniMaxAlgo>(TEST_DEPTH);
        }
    algo::ABMiniMaxAlgoPtr abminimax_;
};

TEST(ABPMiniMax, Construction){
    EXPECT_NO_THROW(algo::ABMiniMaxAlgo(5));
}

using fen = std::string;
// correct move, opponent move  
using solution_moves = std::pair<std::string, std::string>; 
using solution = std::vector<solution_moves>;
using PuzzlePair = std::pair<fen, solution>;

TEST_F(ABPMiniMaxTest, SimpleFork){
    // TODO (Dan) find a way to load these from a file? JSON or something
    std::array<PuzzlePair, 2> test_cases = {
        std::make_pair("2q3k1/8/8/5N2/6P1/7K/8/8 w - - 0 1", solution({{"f5e7", "g8f7"}, {"e7c8", "end"}})),
        std::make_pair("6k1/5r1p/p2N4/nppP2q1/2P5/1P2N3/PQ5P/7K w - - 0 1", solution({{"b2h8", "g8h8"},  {"d6f7", "h8g7"}, {"f7g5","end"}}))
    };

    for(auto& test_case : test_cases){
        libchess::Position test_pos(test_case.first);
        for(auto& move : test_case.second){
            auto guess = abminimax_->GetNextMove(&test_pos, test_pos.turn());
            EXPECT_EQ(static_cast<std::string>(guess), move.first);
            if(move.second == "end"){
                break;
            }
            test_pos.makemove(move.first);
            test_pos.makemove(move.second);
        }
    }

}