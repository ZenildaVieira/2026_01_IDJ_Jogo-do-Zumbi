#include "Game.h"

#include <SDL_image.h>
#include <SDL_mixer.h>

#include <cstdlib>
#include <iostream>

Game* Game::instance = nullptr;

Game& Game::GetInstance(const std::string& title, int width, int height) {
    if (instance == nullptr) {
        instance = new Game(title, width, height);
    }
    return *instance;
}

Game::Game(const std::string& title, int width, int height)
    : window(nullptr), renderer(nullptr), state(nullptr) {
    
    if (instance != nullptr && instance != this) {
        std::cerr << "Erro: tentativa de criar mais de uma instancia de Game." << std::endl;
        std::exit(1);
    }
    instance = this;

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) != 0) {
        std::cerr << "Erro no SDL_Init: " << SDL_GetError() << std::endl;
        std::exit(1);
    }

    const int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG | IMG_INIT_TIF;
    const int imgLoaded = IMG_Init(imgFlags);
    if ((imgLoaded & imgFlags) != imgFlags) {
        std::cerr << "Aviso IMG_Init: " << IMG_GetError() << std::endl;
    }

    const int mixFlags = MIX_INIT_OGG | MIX_INIT_MP3;
    const int mixLoaded = Mix_Init(mixFlags);
    if ((mixLoaded & mixFlags) != mixFlags) {
        std::cerr << "Aviso Mix_Init: " << Mix_GetError() << std::endl;
    }

    if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) != 0) {
        std::cerr << "Erro no Mix_OpenAudio: " << Mix_GetError() << std::endl;
        std::exit(1);
    }

    Mix_AllocateChannels(32);

    window = SDL_CreateWindow(
        title.c_str(),
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        width,
        height,
        0
    );
    if (window == nullptr) {
        std::cerr << "Erro ao criar janela: " << SDL_GetError() << std::endl;
        std::exit(1);
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        std::cerr << "Erro ao criar renderer: " << SDL_GetError() << std::endl;
        std::exit(1);
    }

    state = new State();
}

Game::~Game() {
    if (state != nullptr) {
        delete state;
        state = nullptr;
    }

    Mix_CloseAudio();
    Mix_Quit();
    IMG_Quit();

    if (renderer != nullptr) {
        SDL_DestroyRenderer(renderer);
        renderer = nullptr;
    }

    if (window != nullptr) {
        SDL_DestroyWindow(window);
        window = nullptr;
    }

    SDL_Quit();
    instance = nullptr;
}

State& Game::GetState() const {
    return *state;
}

SDL_Renderer* Game::GetRenderer() const {
    return renderer;
}

void Game::Run() {
    while (!state->QuitRequested()) {
        state->Update(0.0f);

        SDL_RenderClear(renderer);
        state->Render();
        SDL_RenderPresent(renderer);

        SDL_Delay(33);
    }
}
