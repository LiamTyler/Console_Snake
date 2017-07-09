#include "include/game.h"
#include <string>
#include <algorithm>

using namespace std;

Game::Game() {
    win_ = nullptr;
    snake_ = nullptr;
    // TODO(partA): initialze your Fruit pointer
    // TODO(partD): initialze your SnakeFruit pointer
}

Game::~Game() {
    if (win_)
        delete win_;
    if (snake_)
        delete snake_;
    // TODO(partA): delete your Fruit pointer
    // TODO(partD): delete your SnakeFruit pointer
}

void Game::Init() {
    srand(time(NULL));

    // Create window, snake, and fruit. Draw fruit and snake
    win_ = new WindowManager();

    snake_ = new Snake();
    snake_->Draw(win_);

    // TODO(partD): Create your SnakeFruit, set its target,
    //              initialize it, and draw it

    // Spawn fruit after snakes are initialized
    SpawnFruit();

    // Initial state: playing (not gameovered), score = 0, and start the timer
    gameover_ = false;
    start_time_ = chrono::steady_clock::now();
}

// TODO: See game.h for the enumeration of fruits
void Game::SpawnFruit() {
    // TODO(partA): If there is a fruit existing, delete it

    // TODO(partB): Randomly select which fruit to spawn
    int r = PLAIN;
    switch(r) {
        case PLAIN:
            // TODO(partA): Update the pointer to a new Fruit object
            break;
        // TODO(partB): Add in your moving fruit as an option
        default:
            // TODO(partA): Safe programming, uncomment this
            // fruit_ = nullptr;
            break;
    }

    // TODO(partA): Initialize your newly created fruit

    // TODO(partD): Set the SnakeFruit to target the new fruit
    //              if a snake fruit exists
}

// Return a string of the time in seconds since the game started (max at 9999)
string Game::GetGameTime() {
    chrono::steady_clock::time_point now = chrono::steady_clock::now();
    return to_string(min(9999, (int)chrono::duration_cast<chrono::seconds>
                (now - start_time_).count()));
}

void Game::UpdateHeader() {
    win_->PrintString("Player Score: " + to_string(snake_->Score()), 1, 1);
    // TODO(partD): Uncomment this
    /*
    if (snake_fruit_)
        win_->PrintString("SnakeFruit Score: " + to_string(snake_fruit_->Score()), 20, 1);
    else
        win_->PrintString("                      ", 20, 1);
    */
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
                // TODO(partA): Call the fruit's update function
                // TODO(partD): If there is a snake fruit, call its
                //              update function
                snake_->Update(win_, key_code);
                HandleCollisions();
                win_->EndFrame();
        }
    }
}

void Game::HandleCollisions() {
    // TODO(partD): Uncomment this
    /*
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
    */

    int sx = snake_->X();
    int sy = snake_->Y();
    // TODO(partA): Check to see if the fruit and snake collide. If so,
    //              call the snake's eat fruit method, spawn a new fruit,
    //              and redraw the snake
    //
    
    // TODO(partD): Uncomment this
    /*
    if (snake_->HitHead(snake_fruit_)) {
        snake_->EatFruit(snake_fruit_, win_);
        delete snake_fruit_;
        snake_fruit_ = nullptr;
    }
    */

    // TODO(partD): Add in the following check: "If the snake fruit is alive,
    //              and its body contains the snake's head, gameover"
    if (!snake_->InBounds(win_) ||
        snake_->BodyContains(sx, sy)) {
        gameover_ = true;
    }
}
