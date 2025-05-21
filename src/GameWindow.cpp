#include <include/GameWindow.hpp>

GameWindow::GameWindow()
    : running(true)
{
    window = SDL_CreateWindow(
        PROJECT_NAME,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        800, 600,
        SDL_WINDOW_RESIZABLE
    );
    if (!window) {
        SDL_Quit();
        throw "Ошибка создания окна: " + std::string(SDL_GetError());
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) {
        SDL_DestroyWindow(window);
        SDL_Quit();
        throw "Ошибка создания рендерера: " + std::string(SDL_GetError());
    }
}

GameWindow::~GameWindow() {
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void GameWindow::handleEvents() {
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            running = false;
        }
        if (event.type == SDL_MOUSEBUTTONDOWN) {
            inputState.mouseX = event.button.x;
            inputState.mouseY = event.button.y;
            inputState.mouseClicked = true;
        }
    }
}

