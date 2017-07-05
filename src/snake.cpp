#include "include/snake.h"

Snake::Snake() : Snake('O', 1, 1, 1, 0) {}

Snake::Snake(char symbol, int x, int y, int vx, int vy) :
    Moveable(x, y, vx, vy) {

    symbol_ = symbol;
}

bool Snake::ProcessInput(int key_code) {
    bool quit = false;
    switch( key_code ) {
        case 'w':
        case KEY_UP:
            vx_ = 0;
            vy_ = -1;
            break;
        case 's':
        case KEY_DOWN:
            vx_ = 0;
            vy_ = 1;
            break;
        case 'a':
        case KEY_LEFT:
            vx_ = -1;
            vy_ = 0;
            break;
        case 'd':
        case KEY_RIGHT:
            vx_ = 1;
            vy_ = 0;
            break;
        case 'q':
            quit = true;
        default:
            break;
    }
    return quit;
}

void Snake::Draw(WindowManager& win) {
    win.PrintChar(symbol_, x_, y_);
}

bool Snake::Update(WindowManager& win) {
    // Erase old position
    win.PrintChar(' ', x_, y_);

    // Update velocities if a key was pressed
    bool gameover = ProcessInput(win.GetInput());

    // Update position
    Moveable::UpdatePosition();

    // Draw new position
    Draw(win);

    return gameover;
}
