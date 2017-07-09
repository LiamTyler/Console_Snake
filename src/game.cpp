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
    snake_fruit_ = nullptr;
}

Game::~Game() {
    if (win_)
        delete win_;
    if (snake_)
        delete snake_;
    if (fruit_)
        delete fruit_;
    if (snake_fruit_)
        delete snake_fruit_;
}

void Game::Init() {
    srand(time(NULL));

    // Create window, snake, and fruit. Draw fruit and snake
    win_ = new WindowManager();

    snake_ = new Snake();
    snake_->Draw(win_);

    snake_fruit_ = new SnakeFruit();
    snake_fruit_->SetTarget(fruit_);
    snake_fruit_->Init(win_);
    snake_fruit_->Snake::Draw(win_);

    // Spawn fruit after snakes are initialized
    SpawnFruit();

    // Initial state: playing (not gameovered), score = 0, and start the timer
    gameover_ = false;
    start_time_ = chrono::steady_clock::now();
}

void Game::SpawnFruit() {
    if (fruit_)
        delete fruit_;
    int f = rand() % TOTAL_FRUITS;
    // f = 0;
    switch(f) {
        case PLAIN:
            fruit_ = new Fruit();
            break;
        case MOVING:
            fruit_ = new MovingFruit();
            break;
        default:
            fruit_ = nullptr;
    }
    fruit_->Init(win_);
    if (snake_fruit_)
        snake_fruit_->SetTarget(fruit_);
}

// Return a string of the time in seconds since the game started (max at 9999)
string Game::GetGameTime() {
    chrono::steady_clock::time_point now = chrono::steady_clock::now();
    return to_string(min(9999, (int)chrono::duration_cast<chrono::seconds>
                (now - start_time_).count()));
}

void Game::UpdateHeader() {
    win_->PrintString("Player Score: " + to_string(snake_->Score()), 1, 1);
    if (snake_fruit_)
        win_->PrintString("SnakeFruit Score: " + to_string(snake_fruit_->Score()), 20, 1);
    else
        win_->PrintString("                      ", 20, 1);
    win_->PrintString("Time: " + GetGameTime(), win_->ScreenWidth() - 11, 1);
    win_->PrintString("FPS: " + to_string((int) win_->FPS()), win_->ScreenWidth() - 21, 1);
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
            default:
                UpdateHeader();
                fruit_->Update(win_);
                if (snake_fruit_)
                    snake_fruit_->Update(win_);
                snake_->Update(win_, key_code);
                HandleCollisions();
                win_->EndFrame();
        }
    }
}

void Game::HandleCollisions() {
    if (snake_fruit_) {
        if (snake_fruit_->Dead()) {
            snake_->EatFruit(snake_fruit_, win_);
            delete snake_fruit_;
            snake_fruit_ = nullptr;
        } else {
            if (fruit_->X() == snake_fruit_->X() && fruit_->Y() == snake_fruit_->Y()) {
                snake_fruit_->EatFruit(fruit_, win_);
                SpawnFruit();
            }
        }
    }

    int sx = snake_->X();
    int sy = snake_->Y();
    if (fruit_->X() == sx && fruit_->Y() == sy) {
        snake_->EatFruit(fruit_, win_);
        SpawnFruit();
        snake_->Draw(win_);
    }
    if (snake_->HitHead(snake_fruit_)) {
        snake_->EatFruit(snake_fruit_, win_);
        delete snake_fruit_;
        snake_fruit_ = nullptr;
    }

    if (!snake_->InBounds(win_) ||
        snake_->BodyContains(sx, sy) ||
        (snake_fruit_ && snake_fruit_->BodyContains(sx, sy))) {
        gameover_ = true;
    }
}
