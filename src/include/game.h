#ifndef SRC_INCLUDE_GAME_H_
#define SRC_INCLUDE_GAME_H_

#include "include/window_manager.h"
#include "include/snake.h"
#include "include/fruit.h"
#include "include/snake_fruit.h"
#include <chrono>

enum {
    PLAIN,
    MOVING,
    TOTAL_FRUITS
};

class Game {
    public:
        Game();
        ~Game();
        void Init();
        void UpdateHeader();
        void Play();
        void HandleCollisions();
        void SpawnFruit();
        std::string GetGameTime();

    private:
        WindowManager* win_;
        Snake* snake_;
        Fruit* fruit_;
        SnakeFruit* snake_fruit_;
        bool gameover_;
        int score_;

        std::chrono::steady_clock::time_point start_time_;
};

#endif  // SRC_INCLUDE_GAME_H_
