#include "include/snake.h"

Snake::Snake() : Snake('O', 1, 1, 1, 0) {}

Snake::Snake(char symbol, int x, int y, int vx, int vy) :
    symbol_(symbol), x_(x), y_(y), vx_(vx), vy_(vy) {

}

void Snake::Update() {
    x_ += vx_;
    y_ += vy_;
}
