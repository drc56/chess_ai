#include <gtest/gtest.h>
#include <array>
#include <string>
#include <utility>

#include <libchess/position.hpp>
#include <libchess/move.hpp>
#include "../src/algo/abminimaxalgo.hpp"

static constexpr int TEST_DEPTH = 5;

class ABPMiniMaxTest : public ::testing::Test{
    protected:
        void SetUp() override{
            abminimax_ = new algo::ABMiniMaxAlgo(TEST_DEPTH);
        }
        void TearDown() override{
            delete abminimax_;
        }
    algo::ABMiniMaxAlgo* abminimax_;
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
    std::array<PuzzlePair, 1> test_cases = {
        std::make_pair("2q3k1/8/8/5N2/6P1/7K/8/8 w - - 0 1", solution({{"f5e7", "g8f7"}, {"e7c8", "end"}}))
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