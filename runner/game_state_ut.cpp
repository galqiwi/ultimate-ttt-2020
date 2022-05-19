#include <gtest/gtest.h>
#include "game_state.h"

TEST(GameState, SetCell) {
    GameState game{};
    ASSERT_EQ(game.GetCellState(0, 0), Players::Unknown);
    ASSERT_TRUE(game.CanMakeMove(Players::First, 0, 0));
    game.MakeMove(Players::First, 0, 0);
    ASSERT_EQ(game.GetCellState(0, 0), Players::First);
    ASSERT_FALSE(game.CanMakeMove(Players::First, 0, 0));
}

TEST(GameState, MetaCellVertical) {
    GameState game{};

    game.MakeMove(Players::First, 0, 0);
    game.MakeMove(Players::Second, 1, 0);
    game.MakeMove(Players::First, 3, 0);
    game.MakeMove(Players::Second, 1, 1);
    game.MakeMove(Players::First, 3, 3);
    ASSERT_EQ(game.GetMetaCellState(0, 0), Players::Unknown);
    game.MakeMove(Players::Second, 1, 2);
    ASSERT_EQ(game.GetMetaCellState(0, 0), Players::Second);
}

TEST(GameState, MetaCellHorizontal) {
    GameState game{};

    game.MakeMove(Players::First, 0, 0);
    game.MakeMove(Players::Second, 0, 1);
    game.MakeMove(Players::First, 0, 3);
    game.MakeMove(Players::Second, 1, 1);
    game.MakeMove(Players::First, 3, 3);
    ASSERT_EQ(game.GetMetaCellState(0, 0), Players::Unknown);
    game.MakeMove(Players::Second, 2, 1);
    ASSERT_EQ(game.GetMetaCellState(0, 0), Players::Second);
}

TEST(GameState, MetaCellDiagonal) {
    GameState game{};

    game.MakeMove(Players::First, 1, 1);
    game.MakeMove(Players::Second, 3, 3);
    game.MakeMove(Players::First, 2, 2);
    game.MakeMove(Players::Second, 6, 6);
    ASSERT_EQ(game.GetMetaCellState(0, 0), Players::Unknown);
    game.MakeMove(Players::First, 0, 0);
    ASSERT_EQ(game.GetMetaCellState(0, 0), Players::First);
}

TEST(GameState, MetaCellRule) {
    GameState game{};

    ASSERT_FALSE(game.GameFinished());

    game.MakeMove(Players::First, 1, 0);
    game.MakeMove(Players::Second, 3, 0);
    game.MakeMove(Players::First, 1, 1);
    game.MakeMove(Players::Second, 3, 3);
    game.MakeMove(Players::First, 1, 2);
    game.MakeMove(Players::Second, 3, 7);
    game.MakeMove(Players::First, 1, 3);
    game.MakeMove(Players::Second, 3, 1);
    game.MakeMove(Players::First, 1, 4);

    ASSERT_FALSE(game.GameFinished());

    game.MakeMove(Players::Second, 3, 4);
    game.MakeMove(Players::First, 1, 5);
    game.MakeMove(Players::Second, 3, 8);
    game.MakeMove(Players::First, 1, 6);
    game.MakeMove(Players::Second, 3, 2);
    game.MakeMove(Players::First, 1, 7);
    game.MakeMove(Players::Second, 3, 5);

    ASSERT_FALSE(game.GameFinished());
    game.MakeMove(Players::First, 1, 8);

    ASSERT_TRUE(game.GameFinished());
    ASSERT_EQ(game.GetWinner(), Players::First);
}

TEST(GameState, CanGoToAnyMetaCellIfNextCellCapture) {
    GameState game{};

    game.MakeMove(Players::First, 1, 0);
    game.MakeMove(Players::Second, 3, 0);
    game.MakeMove(Players::First, 1, 1);
    game.MakeMove(Players::Second, 3, 3);
    game.MakeMove(Players::First, 1, 2);
    game.MakeMove(Players::Second, 3, 6);

    ASSERT_FALSE(game.CanMakeMove(Players::First, 0, 0));
    ASSERT_TRUE(game.CanMakeMove(Players::First, 4, 4));
    ASSERT_TRUE(game.CanMakeMove(Players::First, 7, 7));

    std::cout << game << std::endl;
}
