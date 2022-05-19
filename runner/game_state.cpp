#include "game_state.h"

PlayerId AnotherPlayer(PlayerId player) {
    if (player == Players::First) {
        return Players::Second;
    }
    if (player == Players::Second) {
        return Players::First;
    }
    abort();
}

void GameState::MakeMove(PlayerId player, int x, int y) {
    assert(CanMakeMove(player, x, y));

    LastPlayer_ = player;
    Field_[GetCellId(x, y)] = player;
    NextMetaX_ = x % 3;
    NextMetaY_ = y % 3;
    UpdateMetaCell(x / 3, y / 3);
}

bool GameState::CanMakeMove(PlayerId player, int x, int y) const {
    assert(player != Players::Unknown);

    if (player == LastPlayer_) {
        return false;
    }

    if (
        LastPlayer_ != Players::Unknown
        && (x / 3 != NextMetaX_ || y / 3 != NextMetaY_)
        && (MetaField_[GetMetaCellId(NextMetaX_, NextMetaY_)] == Players::Unknown)) {
        return false;
    }

    if (x < 0 || x >= FIELD_SIDE) {
        return false;
    }

    if (y < 0 || y >= FIELD_SIDE) {
        return false;
    }

    auto& metaCell = MetaField_[GetMetaCellId(x / 3, y / 3)];
    if (metaCell != Players::Unknown) {
        return false;
    }

    auto& cell = Field_[GetCellId(x, y)];
    if (cell != Players::Unknown) {
        return false;
    }

    return true;
}

int GameState::GetCellId(int x, int y) {
    assert(0 <= x && x < FIELD_SIDE);
    assert(0 <= y && y < FIELD_SIDE);
    return y * FIELD_SIDE + x;
}

int GameState::GetMetaCellId(int xMeta, int yMeta) {
    assert(0 <= xMeta && xMeta < META_FIELD_SIDE);
    assert(0 <= yMeta && yMeta < META_FIELD_SIDE);
    return yMeta * META_FIELD_SIDE + xMeta;
}

inline PlayerId SameValueOrUnknown(PlayerId a, PlayerId b, PlayerId c) {
    if (a == b && b == c) {
        return a;
    }
    return Players::Unknown;
}

void GameState::UpdateMetaCell(int xMeta, int yMeta) {
    assert(0 <= xMeta && xMeta < META_FIELD_SIDE);
    assert(0 <= yMeta && yMeta < META_FIELD_SIDE);

    int x = xMeta * 3;
    int y = yMeta * 3;

    for (int i = 0; i < 3; ++i) {
        auto horizontal = SameValueOrUnknown(
            Field_[GetCellId(x + i, y + 0)],
            Field_[GetCellId(x + i, y + 1)],
            Field_[GetCellId(x + i, y + 2)]);
        if (horizontal != Players::Unknown) {
            MetaField_[GetMetaCellId(xMeta, yMeta)] = horizontal;
            return;
        }

        auto vertical = SameValueOrUnknown(
            Field_[GetCellId(x + 0, y + i)],
            Field_[GetCellId(x + 1, y + i)],
            Field_[GetCellId(x + 2, y + i)]);
        if (vertical != Players::Unknown) {
            MetaField_[GetMetaCellId(xMeta, yMeta)] = vertical;
            return;
        }
    }


    auto firstDiagonal = SameValueOrUnknown(
        Field_[GetCellId(x + 0, y + 0)],
        Field_[GetCellId(x + 1, y + 1)],
        Field_[GetCellId(x + 2, y + 2)]);

    if (firstDiagonal != Players::Unknown) {
        MetaField_[GetMetaCellId(xMeta, yMeta)] = firstDiagonal;
        return;
    }

    auto secondDiagonal = SameValueOrUnknown(
        Field_[GetCellId(x + 2, y + 0)],
        Field_[GetCellId(x + 1, y + 1)],
        Field_[GetCellId(x + 0, y + 2)]);

    if (secondDiagonal != Players::Unknown) {
        MetaField_[GetMetaCellId(xMeta, yMeta)] = secondDiagonal;
    }
}

PlayerId GameState::GetCellState(int x, int y) const {
    return Field_[GetCellId(x, y)];
}

PlayerId GameState::GetMetaCellState(int xMeta, int yMeta) const {
    return MetaField_[GetMetaCellId(xMeta, yMeta)];
}

PlayerId GameState::GetWinner() const {
    for (int i = 0; i < 3; ++i) {
        auto horizontal = SameValueOrUnknown(
            MetaField_[3 * i + 0],
            MetaField_[3 * i + 1],
            MetaField_[3 * i + 2]);
        if (horizontal != Players::Unknown) {
            return horizontal;
        }

        auto vertical = SameValueOrUnknown(
            MetaField_[i + 0],
            MetaField_[i + 3],
            MetaField_[i + 6]);
        if (vertical != Players::Unknown) {
            return vertical;
        }
    }

    auto firstDiagonal = SameValueOrUnknown(
        MetaField_[0],
        MetaField_[4],
        MetaField_[8]);

    if (firstDiagonal != Players::Unknown) {
        return firstDiagonal;
    }

    auto secondDiagonal = SameValueOrUnknown(
        MetaField_[2],
        MetaField_[4],
        MetaField_[6]);

    return secondDiagonal;
}

bool GameState::GameFinished() const {
    if (LastPlayer_ == Players::Unknown) {
        return false;
    }
    if (GetWinner() != Players::Unknown) {
        return true;
    }

    auto player = AnotherPlayer(LastPlayer_);

    for (int x = 0; x < 3; ++x) {
        for (int y = 0; y < 3; ++y) {
            if (CanMakeMove(player, NextMetaX_ * 3 + x, NextMetaY_ * 3 + y)) {
                return false;
            }
        }
    }

    return true;
}

GameState::GameState() {
    Field_.fill(Players::Unknown);
    MetaField_.fill(Players::Unknown);
}

std::ostream& operator<<(std::ostream& out, const GameState& game) {
    for (int y = 0; y < FIELD_SIDE + 1; ++y) {
        if (y % (FIELD_SIDE / META_FIELD_SIDE) == 0) {
            for (int x = 0; x < (FIELD_SIDE + META_FIELD_SIDE) * 2 + 1; ++x) {
                out << "-";
            }
            if (y < FIELD_SIDE) {
                out << std::endl;
            }
        }

        if (y == FIELD_SIDE) {
            continue;
        }

        for (int x = 0; x < FIELD_SIDE + 1; ++x) {
            if (x % (FIELD_SIDE / META_FIELD_SIDE) == 0) {
                out << "| ";
            }
            if (x == FIELD_SIDE) {
                continue;
            }
            out << GetPlayerChar(game.GetCellState(x, y)) << " ";
        }
        out << std::endl;
    }
    return out;
}

char GetPlayerChar(PlayerId player) {
    static std::unordered_map<PlayerId, char> names = {
        {Players::First, 'M'},
        {Players::Second, 'E'},
        {Players::Unknown, 'U'},
    };

    return names[player];
}