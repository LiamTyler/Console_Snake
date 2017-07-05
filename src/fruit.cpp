#include "include/fruit.h"

Fruit::Fruit(char symbol, int value, int x, int y, int vx, int vy) :
             symbol_(symbol), value_(value), Moveable(x, y, vx, vy) {}

void Fruit::Destroy(WindowManager& win) {
    win.PrintChar(' ', x_, y_);
}

void Fruit::Draw(WindowManager& win) {
    win.PrintChar(symbol_, x_, y_);
}

void Fruit::Update(WindowManager& win) {
    win.PrintChar(' ', x_, y_);
    Moveable::UpdatePosition();
    Draw(win);
}
