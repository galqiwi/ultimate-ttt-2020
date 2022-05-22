#include "Strategy.h"


std::pair<int, int> Strategy::GetNextMove(std::optional<std::pair<int, int>> enemyMove) {
    if (enemyMove) {
        Game_.MakeMove(Players::First, enemyMove->first, enemyMove->second);
    }
    for (int x = 0; x < 9; ++x) {
        for (int y = 0; y < 9; ++y) {
            if (Game_.CanMakeMove(Players::Second, x, y)) {
                Game_.MakeMove(Players::Second, x, y);
                return {x, y};
            }
        }
    }
    abort();
}