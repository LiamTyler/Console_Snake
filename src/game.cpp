#include "include/game.h"
#include <string>
#include <algorithm>
#include "include/moving_fruit.h"
#include "include/snake_fruit.h"

using namespace std;

Game::Game() {
    win_ = nullptr;
    snake_ = nullptr;
    fruit_ = nullptr;
    sf_ = nullptr;
}

Game::~Game() {
    if (win_)
        delete win_;
    if (snake_)
        delete snake_;
    if (fruit_)
        delete fruit_;
    if (sf_)
        delete sf_;
}

void Game::Init() {
    srand(time(NULL));

    // Create window, snake, and fruit. Draw fruit and snake
    win_ = new WindowManager();
    snake_ = new Snake();
    fruit_ = new Fruit();
    fruit_->Init(win_);
    // fruit_ = new MovingFruit();
    sf_ = new SnakeFruit();
    sf_->SetTarget(fruit_);
    sf_->Init(win_);
    sf_->Snake::Draw(win_);
    snake_->Draw(win_);

    // Initial state: playing (not gameovered), score = 0, and start the timer
    gameover_ = false;
    start_time_ = chrono::steady_clock::now();
}

// Return a string of the time in seconds since the game started (max at 9999)
string Game::GetGameTime() {
    chrono::steady_clock::time_point now = chrono::steady_clock::now();
    return to_string(min(9999, (int)chrono::duration_cast<chrono::seconds>
                (now - start_time_).count()));
}

void Game::UpdateHeader() {
    win_->PrintString("Player Score: " + to_string(snake_->Score()), 1, 1);
    win_->PrintString("SnakeFruit Score: " + to_string(sf_->Score()), 20, 1);
    win_->PrintString("Time: " + GetGameTime(), win_->ScreenWidth() - 11, 1);
}

void Game::Play() {
    while(!gameover_) {
        win_->StartFrame();
        int key_code = win_->GetInput();
        switch( key_code ) {
            case 'q':
                gameover_ = true;
                break;
            case 'p':
                win_->Pause();
                break;
            case 'l':
                win_->FlipSpeed();
                break;
            default:
                UpdateHeader();
                fruit_->Update(win_);
                sf_->Update(win_);
                if (sf_->Dead())
                    win_->Pause();
                // gameover_ = snake_->Update(win_, key_code);
                HandleCollisions();
                win_->EndFrame();
        }
    }
}

void Game::HandleCollisions() {
    if (fruit_->X() == snake_->X() && fruit_->Y() == snake_->Y()) {
        fruit_->Destroy(win_, snake_);
        delete fruit_;
        fruit_ = new Fruit();
        // fruit_ = new MovingFruit();
        sf_->SetTarget(fruit_);
        snake_->Draw(win_);
        fruit_->Init(win_);
    }
    if (fruit_->X() == sf_->X() && fruit_->Y() == sf_->Y()) {
        fruit_->Destroy(win_, sf_);
        delete fruit_;
        fruit_ = new Fruit();
        // fruit_ = new MovingFruit();
        sf_->SetTarget(fruit_);
        // snake_->Draw(win_);
        fruit_->Init(win_);
    }
    /*
    if (snake_->X() == sf_->X() && snake_->Y() == sf_->Y()) {
        sf_->Destroy(win_, snake_);
        delete sf_;
    }
    */
}
