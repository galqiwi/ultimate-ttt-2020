#include <iostream>
#include <optional>

#include "Strategy.h"

std::optional<std::pair<int, int>> GetEnemyMove() {
    int x, y;
    std::cin >> x >> y;
    if (x == -1) {
        return std::nullopt;
    }
    return std::make_pair(x, y);
}

int main() {
    Strategy s;

    bool firstMove = true;

    while (true) {
        auto enemyMove = GetEnemyMove();
        auto [x, y] = s.GetNextMove(enemyMove);
        std::cout << x << " " << y << std::endl;
        if (!enemyMove && !firstMove) {
            return 0;
        }
        firstMove = false;
    }
}