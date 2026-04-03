#pragma once

#include <string>
#include <SDL.h>

class State;

class Game {

public:
    ~Game();

    void Run();
    SDL_Renderer* GetRenderer() const;
    State& GetState() const;
    static Game& GetInstance(const std::string& title = "Jogo", int width = 1200, int height = 900);

private:
    Game(const std::string& title, int width, int height);

    static Game* instance;

    SDL_Window* window;
    SDL_Renderer* renderer;
    State* state;
};