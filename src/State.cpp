#include "State.h"
#include <SDL.h>

State::State()
    : bg(), music(), quitRequested(false) {

}

void State::LoadAssets() {
    bg.Open("recursos/img/Background.png");
    music.Open("recursos/audio/BGM.wav");
}

void State::Update(float dt) {
    (void)dt;

    if (SDL_QuitRequested()) {
        quitRequested = true;
    }

}

void State::Render() {
    bg.Render(0, 0);
}

bool State::QuitRequested() const {
    return quitRequested;
}

void State::Run() {
    while (!state->QuitRequested()) {
        state->Update(0.0f);

        SDL_RenderClear(renderer);
        state->Render();
        SDL_RenderPresent(renderer);

        SDL_Delay(33);
    }
}