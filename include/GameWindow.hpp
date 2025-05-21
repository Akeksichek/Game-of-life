#pragma once

#include <string>
#include <unordered_map>
#include <memory>

#include <SDL2/SDL.h>

#ifndef PROJECT_NAME
#define PROJECT_NAME "unknown"
#endif //PROJECT_NAME

class GameWindow
{
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Event event;    
    bool running;

    struct {
        int mouseX = 0;
        int mouseY = 0;
        bool mouseClicked = false;
    } inputState;
    
private:
    void handleEvents();

public:
    GameWindow();
    ~GameWindow();

    SDL_Window* get_window() { return window; }
    SDL_Renderer* get_renderer() { return renderer; }

    template <typename F>
    void play(F&& callback) {
        while (running) {
            handleEvents();
            
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderClear(renderer);
            
            callback(renderer, inputState);
            
            inputState.mouseClicked = false;
            SDL_RenderPresent(renderer);
        }
    }
};