#include <SDL2/SDL.h>
#include <iostream>

#include "include/GameWindow.hpp"
#include "include/GameArea.hpp"
#include "include/GameMenu.hpp"

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "Ошибка инициализации SDL: " << SDL_GetError() << std::endl;
        return 1;
    }

    try {
        
        GameWindow gameWin;

        int height = 300, width = 500, speed = 5;
        if(argv[1] && argv[2] && argv[3]) {
            width = std::stoi(argv[1]);
            height = std::stoi(argv[2]);
            speed = std::stoi(argv[3]);
        }

        GameArea gameArea(width, height, speed);
        GameMenu gameMenu;

        int screenHeight, screenWidth;
        
        gameWin.play([&](SDL_Renderer* renderer, const auto& inputState) {
            SDL_GetWindowSize(gameWin.get_window(), &screenWidth, &screenHeight);

            
            if(inputState.mouseClicked) {
                gameArea.ToggleCell(inputState.mouseX, inputState.mouseY);
                gameMenu.HandleClick(inputState.mouseX, inputState.mouseY);
            }

            if(gameMenu.request_event() != GameEvent::None)
                gameArea.HandleRequest(gameMenu.request_event());

            gameArea.Update();

            gameMenu.Render(renderer, screenWidth, screenHeight);
            gameArea.Render(renderer, screenHeight, screenWidth);
        });
        
    } catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
        SDL_Quit();
        return 1;
    }

    SDL_Quit();
    return 0;
}