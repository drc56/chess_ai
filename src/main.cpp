
#include <spdlog/spdlog.h>
#include <iostream>
#include <libchess/side.hpp>
#include "algo/algo.hpp"
#include "gamemanager/gamemanager.hpp"

int main(int argc, char const *argv[]) {
    spdlog::info("Starting Game!");
    auto game_man = game::GameManager(AlgoType::ABMiniMax, 5, libchess::White);
    game_man.RunGame();
    return 0;
}
