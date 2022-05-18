#include <gtest/gtest.h>
#include "game_state.h"

TEST(GameState, SetCell) {
    GameState game{};
    ASSERT_EQ(game.GetCell(0, 0), Players::Unknown);
    ASSERT_TRUE(game.CanMakeMove(Players::Me, 0, 0));
    game.MakeMove(Players::Me, 0, 0);
    ASSERT_EQ(game.GetCell(0, 0), Players::Me);
    ASSERT_FALSE(game.CanMakeMove(Players::Me, 0, 0));
}

TEST(GameState, MetaCellVertical) {
    GameState game{};

    game.MakeMove(Players::Me, 0, 0);
    game.MakeMove(Players::Opponent, 1, 0);
    game.MakeMove(Players::Me, 3, 0);
    game.MakeMove(Players::Opponent, 1, 1);
    game.MakeMove(Players::Me, 3, 3);
    ASSERT_EQ(game.GetMetaCell(0, 0), Players::Unknown);
    game.MakeMove(Players::Opponent, 1, 2);
    ASSERT_EQ(game.GetMetaCell(0, 0), Players::Opponent);
}

TEST(GameState, MetaCellHorizontal) {
    GameState game{};

    game.MakeMove(Players::Me, 0, 0);
    game.MakeMove(Players::Opponent, 0, 1);
    game.MakeMove(Players::Me, 0, 3);
    game.MakeMove(Players::Opponent, 1, 1);
    game.MakeMove(Players::Me, 3, 3);
    ASSERT_EQ(game.GetMetaCell(0, 0), Players::Unknown);
    game.MakeMove(Players::Opponent, 2, 1);
    ASSERT_EQ(game.GetMetaCell(0, 0), Players::Opponent);
}

TEST(GameState, MetaCellDiagonal) {
    GameState game{};

    game.MakeMove(Players::Me, 1, 1);
    game.MakeMove(Players::Opponent, 3, 3);
    game.MakeMove(Players::Me, 2, 2);
    game.MakeMove(Players::Opponent, 6, 6);
    ASSERT_EQ(game.GetMetaCell(0, 0), Players::Unknown);
    game.MakeMove(Players::Me, 0, 0);
    ASSERT_EQ(game.GetMetaCell(0, 0), Players::Me);
}

TEST(GameState, MetaCellRule) {
    GameState game{};

    ASSERT_FALSE(game.GameFinished());

    game.MakeMove(Players::Me, 1, 0);
    game.MakeMove(Players::Opponent, 3, 0);
    game.MakeMove(Players::Me, 1, 1);
    game.MakeMove(Players::Opponent, 3, 3);
    game.MakeMove(Players::Me, 1, 2);
    game.MakeMove(Players::Opponent, 3, 7);
    game.MakeMove(Players::Me, 1, 3);
    game.MakeMove(Players::Opponent, 3, 1);
    game.MakeMove(Players::Me, 1, 4);

    ASSERT_FALSE(game.GameFinished());

    game.MakeMove(Players::Opponent, 3, 4);
    game.MakeMove(Players::Me, 1, 5);
    game.MakeMove(Players::Opponent, 3, 8);
    game.MakeMove(Players::Me, 1, 6);
    game.MakeMove(Players::Opponent, 3, 2);
    game.MakeMove(Players::Me, 1, 7);
    game.MakeMove(Players::Opponent, 3, 5);

    ASSERT_FALSE(game.GameFinished());
    game.MakeMove(Players::Me, 1, 8);
    ASSERT_TRUE(game.GameFinished());
    ASSERT_EQ(game.GetWinner(), Players::Me);
}
