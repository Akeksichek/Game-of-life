#include <include/GameMenu.hpp>

GameMenu::GameMenu() : pause_(true), speed_(5), font_(nullptr) {
    if (TTF_Init() == -1) {
        SDL_Log("TTF_Init failed: %s", TTF_GetError());
        return;
    }
    
    font_ = TTF_OpenFont("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf", 24);
    
    if (!font_) {
        SDL_Log("Failed to load font: %s", TTF_GetError());
    } else {
        SDL_Log("Font loaded successfully!");
    }
}

GameMenu::~GameMenu() {
    if (font_) TTF_CloseFont(font_);
}

void GameMenu::Render(SDL_Renderer* renderer, int screenWidth, int screenHeight) {
    if (!font_) {
        throw "Menu render error: " + std::string(TTF_GetError());
    }
    
    SDL_Color white = {255, 255, 255, 255};
    SDL_Color gray = {150, 150, 150, 255};
    
    // Фон меню
    SDL_Rect menuRect = {0, 0, screenWidth, 50};
    SDL_SetRenderDrawColor(renderer, 40, 40, 40, 255);
    SDL_RenderFillRect(renderer, &menuRect);
    
    if (pause_) {
        auto start_btn = add_btn(renderer, "Start", white, {20, 10, 80, 30});
        auto clear_btn = add_btn(renderer, "Clear", white, {120, 10, 80, 30});

    } else {
        auto start_btn = add_btn(renderer, "Pause", white, {20, 10, 80, 30});
        auto clear_btn = add_btn(renderer, "Clear", gray, {120, 10, 80, 30});
    }
}

void GameMenu::HandleClick(int mouseX, int mouseY) {
    if (mouseY < 50) {
        if (pause_) {
            if (mouseX >= 20 && mouseX <= 100) {
                pause_ = false;
                event_ = GameEvent::Start;
            }
            if (mouseX >= 120 && mouseX <= 200) {
                event_ = GameEvent::ClearMap;
            }
        } else {
            if (mouseX >= 20 && mouseX <= 100) {
                pause_ = true;
                event_ = GameEvent::Pause;
            }
        }
    } else {
        event_ = GameEvent::None;
    }
}

GameMenu::Button GameMenu::add_btn(SDL_Renderer* renderer, const char* text, SDL_Color color, SDL_Rect rect) {
    SDL_Surface* surf = TTF_RenderText_Solid(font_, text, color);
    SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, surf);
    SDL_RenderCopy(renderer, tex, nullptr, &rect);

    return Button{
        std::unique_ptr<SDL_Surface, decltype(&SDL_FreeSurface)>(surf, SDL_FreeSurface),
        std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)>(tex, SDL_DestroyTexture)
    };
}