#include "Sprite.h"
#include "Game.h"

#include <SDL_image.h>
#include <iostream>

Sprite::Sprite()
    : texture(nullptr), width(0), height(0), clipRect{0, 0, 0, 0} {
}

Sprite::Sprite(const std::string& file)
    : texture(nullptr), width(0), height(0), clipRect{0, 0, 0, 0} {
    Open(file);
}

Sprite::~Sprite() {
    if (texture != nullptr) {
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }
}

void Sprite::Open(const std::string& file) {
    if (texture != nullptr) {
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }

    SDL_Renderer* renderer = Game::GetInstance().GetRenderer();
    texture = IMG_LoadTexture(renderer, file.c_str());

    if (texture == nullptr) {
        std::cerr << "Erro ao carregar textura: " << file
                  << " | SDL_image: " << IMG_GetError() << std::endl;
        width = 0;
        height = 0;
        clipRect = {0, 0, 0, 0};
        return;
    }

    if (SDL_QueryTexture(texture, nullptr, nullptr, &width, &height) != 0) {
        std::cerr << "Erro ao consultar textura: " << SDL_GetError() << std::endl;
        width = 0;
        height = 0;
        clipRect = {0, 0, 0, 0};
        return;
    }

    SetClip(0, 0, width, height);
}

void Sprite::SetClip(int x, int y, int w, int h) {
    clipRect.x = x;
    clipRect.y = y;
    clipRect.w = w;
    clipRect.h = h;
}

void Sprite::Render(int x, int y) {
    if (texture == nullptr) {
        return;
    }

    SDL_Rect dstRect;
    dstRect.x = x;
    dstRect.y = y;
    dstRect.w = clipRect.w;
    dstRect.h = clipRect.h;

    if (SDL_RenderCopy(Game::GetInstance().GetRenderer(), texture, &clipRect, &dstRect) != 0) {
        std::cerr << "Erro no SDL_RenderCopy: " << SDL_GetError() << std::endl;
    }
}

int Sprite::GetWidth() const {
    return width;
}

int Sprite::GetHeight() const {
    return height;
}

bool Sprite::IsOpen() const {
    return texture != nullptr;
}