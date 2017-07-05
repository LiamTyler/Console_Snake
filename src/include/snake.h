#ifndef SRC_INCLUDE_SNAKE_H_
#define SRC_INCLUDE_SNAKE_H_

#include "include/window.h"
#include "include/moveable.h"
#include <vector>

typedef struct vec2 {
    vec2() {
        x = 0;
        y = 0;
    }
    vec2(int xx, int yy) {
        x = xx;
        y = yy;
    }
    int x;
    int y;
} vec2;

class Snake : public Moveable {
    public:
        Snake();
        Snake(char symbol, int x, int y, int vx, int vy);
        bool Update(WindowManager* win);
        void Draw(WindowManager* win);
        void Erase(WindowManager* win);
        void AddSegment();
        bool ProcessInput(int key_code);
        char GetSymbol() { return symbol_; }
        void Grow(int g) { grow_ += g; }

        int X() { return segments_[0].x; }
        int Y() { return segments_[0].y; }

    private:
        char symbol_;
        int grow_;
        int size_;
        std::vector<vec2> segments_;
};

#endif  // SRC_INCLUDE_SNAKE_H_
