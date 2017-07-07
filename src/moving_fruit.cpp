#include "include/moving_fruit.h"
#include <ncurses.h>
#include <algorithm>

using std::max;
using std::min;

MovingFruit::MovingFruit() : MovingFruit('M', 20, COLOR_YELLOW, 0, 0) {}

MovingFruit::MovingFruit(char sym, int val, unsigned color, int x, int y) :
    frame_(0), Fruit(sym, val, color, x, y) {}

void MovingFruit::Init(WindowManager* win) {
    Fruit::Init(win);
    vx_ = rand() % 3 - 1;
    if (!vx_)
        vy_ = rand() % 3 - 1;
    else
        vy_ = 0;
}

void MovingFruit::Update(WindowManager* win) {
    int sw = win->ScreenWidth();
    int sh = win->ScreenHeight();
    int newx = max(1, min(sw - 2, x_ + vx_));
    int newy = max(3, min(sh - 2, y_ + vy_));

    // Only move if we aren't about to hit anything
    int ch = win->GetChar(newx, newy);
    if (ch == ' ') {
        win->PrintChar(' ', x_, y_);
        x_ = newx;
        y_ = newy;
        Draw(win);
    }


    frame_ = (frame_ + 1) % 5;
    if (!frame_) {
        vx_ = rand() % 3 - 1;
        if (!vx_)
            vy_ = rand() % 3 - 1;
        else
            vy_ = 0;
    }
}
