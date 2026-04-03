#include "Game.h"

int main(int argc, char** argv) {
    (void)argc;
    (void)argv;

    Game& game = Game::GetInstance("Zenilda Pedrosa Vieira - 212002907", 1200, 900);

    game.Run();

    return 0;
}
