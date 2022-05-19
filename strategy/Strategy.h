#pragma once

#include <optional>
#include <utility>

class Strategy {
public:
    std::pair<int, int> GetNextMove(std::optional<std::pair<int, int>> enemyMove);
};