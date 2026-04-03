#include "Music.h"
#include <iostream>

Music::Music()
    : music(nullptr) {
}

Music::Music(const std::string& file)
    : music(nullptr) {
    Open(file);
}

void Music::Play(int times) {
    if (music == nullptr) {
        std::cerr << "Music::Play chamado sem musica carregada." << std::endl;
        return;
    }

    if (Mix_PlayMusic(music, times) != 0) {
        std::cerr << "Erro ao tocar musica: " << Mix_GetError() << std::endl;
    }
}

void Music::Stop(int msToStop) {
    if (!Mix_PlayingMusic()) {
        return;
    }

    if (msToStop == 0) {
        Mix_HaltMusic();
        return;
    }

    if (Mix_FadeOutMusic(msToStop) == 0) {
        std::cerr << "Nao foi possivel aplicar fade out: " << Mix_GetError() << std::endl;
    }
}

void Music::Open(const std::string& file) {
    if (music != nullptr) {
        Stop(0);
        Mix_FreeMusic(music);
        music = nullptr;
    }

    music = Mix_LoadMUS(file.c_str());

    if (music == nullptr) {
        std::cerr << "Erro ao carregar musica: " << file
                  << " | SDL_mixer: " << Mix_GetError() << std::endl;
    }
}

bool Music::IsOpen() const {
    return music != nullptr;
}

Music::~Music() {
    Stop(0);

    if (music != nullptr) {
        Mix_FreeMusic(music);
        music = nullptr;
    }
}
