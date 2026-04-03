#include "Game.h"

int main(int argc, char** argv) {
    (void)argc;
    (void)argv;

    Game& game = Game::GetInstance();

    game.Run();

    return 0;
}
