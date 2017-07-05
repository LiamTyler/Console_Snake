#include "include/snake.h"

Snake::Snake() : Snake('O', 1, 10, 1, 0) {}

Snake::Snake(char symbol, int x, int y, int vx, int vy) :
    Moveable(x, y, vx, vy) {

    symbol_ = symbol;
    grow_ = 0;
    size_ = 1;
    segments_.push_back(vec2(x, y));
}

bool Snake::ProcessInput(int key_code) {
    bool quit = false;
    switch( key_code ) {
        case 'w':
        case KEY_UP:
            if (vy_ != 1) {
                vx_ = 0;
                vy_ = -1;
            }
            break;
        case 's':
        case KEY_DOWN:
            if (vy_ != -1) {
                vx_ = 0;
                vy_ = 1;
            }
            break;
        case 'a':
        case KEY_LEFT:
            if (vx_ != 1) {
                vx_ = -1;
                vy_ = 0;
            }
            break;
        case 'd':
        case KEY_RIGHT:
            if (vx_ != -1) {
                vx_ = 1;
                vy_ = 0;
            }
            break;
        case 'q':
            quit = true;
        default:
            break;
    }
    return quit;
}

void Snake::Erase(WindowManager* win) {
    for (int i = 0; i < size_; i++) {
        win->PrintChar(' ', segments_[i].x, segments_[i].y);
    }
}

void Snake::Draw(WindowManager* win) {
    for (int i = 0; i < size_; i++) {
        win->PrintChar(symbol_, segments_[i].x, segments_[i].y);
    }
}

void Snake::AddSegment() {
    segments_.push_back(segments_[size_ - 1]);
    grow_--;
    size_++;
}

bool Snake::Update(WindowManager* win) {
    // Erase old position
    if (grow_) {
        AddSegment();
    }
    // Update velocities if a key was pressed
    bool gameover = ProcessInput(win->GetInput());

    // Detect collision with self
    if (win->GetChar(segments_[0].x + vx_, segments_[0].y + vy_) == symbol_)
        gameover = true;

    Erase(win);


    // Update position
    for (int i = size_ - 2; i >= 0; i--) {
        segments_[i + 1] = segments_[i];
    }
    segments_[0].x += vx_;
    segments_[0].y += vy_;
    if (win->GetChar(segments_[0].x, segments_[0].y) == symbol_)
        gameover = true;

    // Draw new position
    Draw(win);

    if (!(win->LBorder() < x_ && x_ < win->RBorder() &&
          win->TBorder() < y_ && y_ < win->BBorder()))
        gameover = true;

    return gameover;
}
