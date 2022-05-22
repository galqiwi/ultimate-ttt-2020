#pragma once

#include <array>
#include <cassert>
#include <cstdint>
#include <vector>
#include <ostream>
#include <unordered_map>

using PlayerId = int;

namespace Players {

constexpr PlayerId Unknown = 0;
constexpr PlayerId First = 1;
constexpr PlayerId Second = 2;
constexpr PlayerId Draw = 3;

}

PlayerId AnotherPlayer(PlayerId player);

char GetPlayerChar(PlayerId player);

constexpr int FIELD_SIDE = 9;
constexpr int META_FIELD_SIDE = 3;

class GameState {
public:
    GameState();

    void MakeMove(PlayerId player, int x, int y);
    bool CanMakeMove(PlayerId player, int x, int y) const;

    PlayerId GetCellState(int x, int y) const;
    PlayerId GetMetaCellState(int xMeta, int yMeta) const;

    PlayerId GetWinner() const;
    bool GameFinished() const;

    std::optional<std::pair<int, int>> GetNextMeta() const;
private:
    inline static int GetCellId(int x, int y);
    inline static int GetMetaCellId(int xMeta, int yMeta);

    void UpdateMetaCell(int xMeta, int yMeta);

    std::array<PlayerId, FIELD_SIDE * FIELD_SIDE> Field_;
    std::array<PlayerId, META_FIELD_SIDE * META_FIELD_SIDE> MetaField_;
    PlayerId LastPlayer_ = Players::Unknown;
    int NextMetaX_ = -1;
    int NextMetaY_ = -1;
};

std::ostream& operator<<(std::ostream& out, const GameState& game);
