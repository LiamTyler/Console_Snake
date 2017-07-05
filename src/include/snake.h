#ifndef SRC_INCLUDE_SNAKE_H_
#define SRC_INCLUDE_SNAKE_H_

#include "include/window.h"
#include "include/moveable.h"

class Snake : public Moveable {
    public:
        Snake();
        Snake(char symbol, int x, int y, int vx, int vy);
        bool Update(WindowManager* win);
        void Draw(WindowManager* win);
        bool ProcessInput(int key_code);
        char GetSymbol() { return symbol_; }

    private:
        char symbol_;
};

#endif  // SRC_INCLUDE_SNAKE_H_
