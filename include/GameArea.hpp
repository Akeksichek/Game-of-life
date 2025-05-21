#pragma once
#include <SDL2/SDL.h>

#include <vector>
#include <chrono>

#include "GameEvents.hpp"

class GameArea
{
private:
    int cell_size_ = 20;
    int rows_, cols_;
    SDL_Rect area_rect_;
    std::vector<bool> cells_;
    int width_, height_;
    SDL_Rect drawArea_;

    bool pause_;

    int time_;
    std::chrono::steady_clock::time_point started_;

private:
    void clear_map();

    int neighbor_cell_counting(int x, int y);

public:
    GameArea(int width, int height, int speed);

    void Render(SDL_Renderer* renderer, int screenHeight, int screenWidth);
    void ToggleCell(int mouse_x, int mouse_y);
    void Update();

    void HandleRequest(const GameEvent& event);
};