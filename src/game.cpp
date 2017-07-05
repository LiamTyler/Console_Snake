#include "include/game.h"
#include <string>
#include <algorithm>

using namespace std;

Game::Game() {
    win_ = nullptr;
    snake_ = nullptr;
    fruit_ = nullptr;
}

Game::~Game() {
    if (win_)
        delete win_;
    if (snake_)
        delete snake_;
    if (fruit_)
        delete fruit_;
}

void Game::Init() {
    srand(time(NULL));

    win_ = new WindowManager();
    snake_ = new Snake();
    fruit_ = new Fruit('F', 10);
    fruit_->Init(win_);
    snake_->Draw(win_);

    gameover_ = false;
    score_ = 0;
    start_time_ = chrono::steady_clock::now();

    WINDOW* w = win_->GetWindow();
    mvwhline(w, 2, 1, ACS_S9, 78);
}

string Game::GetGameTime() {
    chrono::steady_clock::time_point now = chrono::steady_clock::now();
    return to_string(min(9999, (int)chrono::duration_cast<chrono::seconds>(now - start_time_).count()));
}

void Game::UpdateHeader() {
    win_->PrintString("Score: " + to_string(score_), 1, 1);
    win_->PrintString("Time: " + GetGameTime(), 69, 1);
}

void Game::Play() {
    while(!gameover_) {
        win_->StartFrame();
        UpdateHeader();
        fruit_->Update(win_);
        gameover_ = snake_->Update(win_);
        HandleCollisions();
        win_->EndFrame();
    }
}

void Game::HandleCollisions() {
    if (fruit_->X() == snake_->X() && fruit_->Y() == snake_->Y()) {
        snake_->Grow(1);
        score_ += fruit_->GetValue();
        delete fruit_;
        fruit_ = new Fruit('F', 10);
        snake_->Draw(win_);
        fruit_->Init(win_);
    }
}
