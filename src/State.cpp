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

