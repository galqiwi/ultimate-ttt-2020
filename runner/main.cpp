#include "game_state.h"
#include <iostream>

int main() {
    GameState game;
    PlayerId player = Players::Me;

    while(!game.GameFinished()) {
        int x, y;
        std::cin >> x >> y;

        if (game.CanMakeMove(player, x, y)) {
            game.MakeMove(player, x, y);
        } else {
            std::cout << "invalid move" << std::endl;
            std::cout << (int)AnotherPlayer(player) << std::endl;
            return 0;
        }

        player = AnotherPlayer(player);
    }
    std::cout << (int)game.GetWinner() << std::endl;
    return 0;
}