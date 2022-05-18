#pragma once

#include <array>
#include <cassert>
#include <cstdint>
#include <vector>

using PlayerId = int8_t;

namespace Players {

constexpr PlayerId Me = 1;
constexpr PlayerId Opponent = -1;
constexpr PlayerId Unknown = 0;

}

PlayerId AnotherPlayer(PlayerId player);

constexpr int FIELD_SIDE = 9;
constexpr int META_FIELD_SIDE = 3;

class GameState {
public:
    GameState();

    void MakeMove(PlayerId player, int x, int y);
    bool CanMakeMove(PlayerId player, int x, int y) const;

    PlayerId GetCell(int x, int y) const;
    PlayerId GetMetaCell(int xMeta, int yMeta) const;

    PlayerId GetWinner() const;
    bool GameFinished() const;
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
