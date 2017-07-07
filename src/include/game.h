#ifndef SRC_INCLUDE_GAME_H_
#define SRC_INCLUDE_GAME_H_

#include "include/window_manager.h"
#include "include/snake.h"
#include "include/fruit.h"
#include <chrono>

class Game {
    public:
        Game();
        ~Game();
        void Init();
        void UpdateHeader();
        void Play();
        void HandleCollisions();
        std::string GetGameTime();

    private:
        WindowManager* win_;
        Snake* snake_;
        Fruit* fruit_;
        bool gameover_;
        int score_;

        std::chrono::steady_clock::time_point start_time_;
};

#endif  // SRC_INCLUDE_GAME_H_
