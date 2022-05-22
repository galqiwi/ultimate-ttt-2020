#include <iostream>
#include <optional>

#include "Strategy.h"

std::optional<std::pair<int, int>> GetEnemyMove() {
    int x, y;
    std::cin >> x >> y;
    if (x == -1 && y == -1) {
        return std::nullopt;
    }
    return std::make_pair(x, y);
}

void RunMatch() {
    Strategy s;

    bool firstMove = true;

    while (true) {
        auto enemyMove = GetEnemyMove();
        if (!enemyMove && !firstMove) {
            return;
        }
        firstMove = false;

        auto [x, y] = s.GetNextMove(enemyMove);
        std::cout << x << " " << y << std::endl;
    }
}

int main() {
    while (true) {
        RunMatch();
    }
}