#include "include/fruit.h"
#include <algorithm>
#include <ncurses.h>

Fruit::Fruit() : Fruit('F', 10, COLOR_RED, 0, 0) {}

Fruit::Fruit(char symbol, int value, unsigned c, int x, int y) :
             symbol_(symbol), value_(value), color_(c),
             Moveable(x, y, 0, 0) {}

void Fruit::Init(WindowManager* win) {
    do {
        x_ = rand() % win->ScreenWidth();
        y_ = std::max(rand() % win->ScreenHeight(), 1+ win->TBorder());
    } while (win->GetChar(x_, y_) != ' ');

    Draw(win);
}

void Fruit::Destroy(WindowManager* win, Snake* snake) {
    snake->Score(snake->Score() + GetValue());
    snake->Grow(7);
}

void Fruit::Draw(WindowManager* win) {
    WINDOW* w = win->GetWindow();
    win->StartColor(color_);
    win->PrintChar(symbol_, x_, y_);
    win->StopColor(color_);
}

void Fruit::Update(WindowManager* win) {
    win->PrintChar(' ', x_, y_);
    Moveable::UpdatePosition();
    Draw(win);
}
