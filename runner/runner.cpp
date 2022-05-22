#include "game_state.h"
#include <iostream>

std::pair<int, int> AskNextMove(PlayerId player) {
    int x, y;
    std::cin >> x >> y;
    return {x, y};
}

void RunGame() {
    GameState game;
    PlayerId player = Players::First;

    while(!game.GameFinished()) {
        auto [x, y] = AskNextMove(player);

        if (game.CanMakeMove(player, x, y)) {
            game.MakeMove(player, x, y);
            std::cout << Players::Unknown << std::endl;
        } else {
            std::cout << AnotherPlayer(player) << std::endl;
            return;
        }

        player = AnotherPlayer(player);
    }
    auto winner = game.GetWinner();
    if (winner == Players::Unknown) {
        winner = Players::Draw;
    }
    std::cout << winner << std::endl;
}

int main() {
    while (true) {
        RunGame();
    }
}
