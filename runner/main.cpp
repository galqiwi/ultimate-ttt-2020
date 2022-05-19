#include "game_state.h"
#include <iostream>

std::pair<int, int> AskNextMove(PlayerId player) {
    int x, y;
    std::cin >> x >> y;
    return {x, y};
}

int main() {
    GameState game;
    PlayerId player = Players::First;

    while(!game.GameFinished()) {
        auto [x, y] = AskNextMove(player);

        if (game.CanMakeMove(player, x, y)) {
            game.MakeMove(player, x, y);
            std::cout << "OK" << std::endl;
        } else {
            std::cout << (int)AnotherPlayer(player) << std::endl;
            return 0;
        }

        player = AnotherPlayer(player);
    }
    std::cout << (int)game.GetWinner() << std::endl;
    return 0;
}
