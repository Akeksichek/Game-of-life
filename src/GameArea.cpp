#include <include/GameArea.hpp>

GameArea::GameArea(int width, int height, int speed)
    :width_(width),
    height_(height),
    pause_(true),
    started_(std::chrono::steady_clock::now()),
    time_(speed)
{
    cols_ = width_ / cell_size_;
    rows_ = height_ / cell_size_;
    cells_.resize(rows_ * cols_, false);

    area_rect_.w = cols_ * cell_size_;
    area_rect_.h = rows_ * cell_size_;
}

void GameArea::Render(SDL_Renderer* renderer, int screenHeight, int screenWidth) {
    area_rect_.x = (screenWidth - area_rect_.w) / 2;
    area_rect_.y = (screenHeight - area_rect_.h) / 2;
    
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    
    SDL_SetRenderDrawColor(renderer, 150, 150, 150, 255);
    for (int x = 0; x <= cols_; x++) {
        SDL_RenderDrawLine(renderer, 
            area_rect_.x + x * cell_size_, area_rect_.y,
            area_rect_.x + x * cell_size_, area_rect_.y + area_rect_.h);
    }
    for (int y = 0; y <= rows_; y++) {
        SDL_RenderDrawLine(renderer,
            area_rect_.x, area_rect_.y + y * cell_size_,
            area_rect_.x + area_rect_.w, area_rect_.y + y * cell_size_);
    }
    
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    for (int y = 0; y < rows_; y++) {
        for (int x = 0; x < cols_; x++) {
            if (cells_[y * cols_ + x]) {
                SDL_Rect cell = {
                    area_rect_.x + x * cell_size_ + 1,
                    area_rect_.y + y * cell_size_ + 1,
                    cell_size_ - 2,
                    cell_size_ - 2
                };
                SDL_RenderFillRect(renderer, &cell);
            }
        }
    }
}

void GameArea::ToggleCell(int mouse_x, int mouse_y) {
    int grid_x = (mouse_x - area_rect_.x) / cell_size_;
    int grid_y = (mouse_y - area_rect_.y) / cell_size_;

    if (grid_x >= 0 && grid_x < cols_ && grid_y >= 0 && grid_y < rows_) {
        cells_[grid_y * cols_ + grid_x] = !cells_[grid_y * cols_ + grid_x];
    }
}

void GameArea::HandleRequest(const GameEvent& event) {
    if(event == GameEvent::ClearMap) clear_map();
    if(event == GameEvent::Pause) pause_ = true;
    if(event == GameEvent::Start) pause_ = false;
}

void GameArea::clear_map()
{
    for(auto cell : cells_) {
        cell = false;
    }
}

int GameArea::neighbor_cell_counting(int x, int y)
{
    int count = 0;

    for (int dy = -1; dy <= 1; ++dy) {
        for (int dx = -1; dx <= 1; ++dx) {
            if (dx == 0 && dy == 0) continue;

            int nx = x + dx;
            int ny = y + dy;

            if (nx < 0) nx = cols_ - 1;
            if (nx >= cols_) nx = 0;
            if (ny < 0) ny = rows_ - 1;
            if (ny >= rows_) ny = 0;

            if (cells_[ny * cols_ + nx]) {
                count++;
            }
        }
    }

    return count;
}

void GameArea::Update()
{
    if(pause_) return;

    std::chrono::steady_clock::time_point interval = std::chrono::steady_clock::now();

    if(interval - started_ >= std::chrono::milliseconds(1000 / time_))
    {

            std::vector<bool> newCells(rows_ * cols_, false);
            
            for (int y = 0; y < rows_; ++y) {
                for (int x = 0; x < cols_; ++x) {
                    int neighbors = neighbor_cell_counting(x, y);
                    bool isAlive = cells_[y * cols_ + x];
                    
                    if (isAlive) {
                        newCells[y * cols_ + x] = (neighbors == 2 || neighbors == 3);
                    } else {
                        newCells[y * cols_ + x] = (neighbors == 3);
                    }
                }
            }
            
            cells_ = std::move(newCells);
            started_ = std::chrono::steady_clock::now();
    }
}