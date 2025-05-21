#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <memory>
#include <map>
#include <string>

#include "GameEvents.hpp"

class GameMenu
{
private:
    int speed_;
    bool pause_;
    TTF_Font* font_;
    GameEvent event_;

    struct Button {
        std::unique_ptr<SDL_Surface, decltype(&SDL_FreeSurface)> surf;
        std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)> tex;
    };
    Button add_btn(SDL_Renderer* renderer, const char* text, SDL_Color color, SDL_Rect rect);
public:
    GameMenu();
    ~GameMenu();

    void Render(SDL_Renderer* renderer, int screenHeight, int screenWidth);

    void HandleClick(int mouseX, int mouseY);

    GameEvent request_event() {
        return event_;
    }

};