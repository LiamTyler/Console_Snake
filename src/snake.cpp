#include "include/snake.h"
#include <iostream>

Snake::Snake() : Snake('O', 'o', 1, 10, 1, 0) {}

Snake::Snake(char head_symbol, char body_symbol, int x, int y, int vx, int vy) :
    Moveable(x, y, vx, vy) {

    score_ = 0;
    h_symbol_ = head_symbol;
    b_symbol_ = body_symbol;
    grow_ = 0;  // Snake isn't growing until it eats some fruit
    size_ = 1;  // Snake starts with only a head
    segments_.push_back(vec2(x, y));  // Only has one segment (head)
}

// Updates the velocities according to the user input (if any)
void Snake::ProcessInput(int key_code) {
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
        // If another key (or no key was pressed)
        default:
            break;
    }
}

void Snake::Erase(WindowManager* win) {
    for (int i = 0; i < size_; i++) {
        win->PrintChar(' ', segments_[i].x, segments_[i].y);
    }
}

void Snake::Draw(WindowManager* win) {
    win->PrintChar(h_symbol_, segments_[0].x, segments_[0].y);
    for (int i = 1; i < size_; i++) {
        win->PrintChar(b_symbol_, segments_[i].x, segments_[i].y);
    }
}

void Snake::EatFruit(Fruit* fruit, WindowManager* win) {
    Grow(4);
    score_ += fruit->Destroy(win);
}

void Snake::AddSegment() {
    segments_.push_back(segments_[size_ - 1]);
    grow_--;
    size_++;
}

void Snake::UpdatePosition(WindowManager* win) {
    // Erase the old snake off the screen before we draw its new position
    Erase(win);

    // Update the snake body position.
    // Each Segment(i+1) = Segment(i), besides the head
    for (int i = size_ - 2; i >= 0; i--) {
        segments_[i + 1] = segments_[i];
    }
    // Update the snake head position
    segments_[0].x += vx_;
    segments_[0].y += vy_;
    x_ = segments_[0].x;
    y_ = segments_[0].y;

    // Draw the snake with its new position
    Draw(win);
}

// Returns true if the snake is within the window borders
bool Snake::InBounds(WindowManager* win) {
    return (win->LBorder() < x_ && x_ < win->RBorder() - 1 &&
          win->TBorder() < y_ && y_ < win->BBorder() - 1);
}

// Returns true if the snake heads collided
// Note: Have to account for snake heads going "through" each other
bool Snake::HitHead(Snake* s) {
    if (!s)
        return false;

    int sx = s->X();
    int sy = s->Y();
    if (x_ == sx && y_ == sy)
        return true;

    int oldx = x_ - vx_;
    int oldy = y_ - vy_;
    if (oldx == sx && oldy == sy &&
        (vx_ == -s->VX() && vy_ == -s->VY()))
        return true;

    return false;
}

// Returns true if a given point is within the snake's body
bool Snake::BodyContains(int x, int y) {
    for (int i = 1; i < segments_.size(); i++) {
        if (segments_[i].x == x && segments_[i].y == y)
            return true;
    }
    return false;
}

void Snake::Update(WindowManager* win, int key_code) {
    // Add a single segment if we are currently growing
    if (grow_) {
        AddSegment();
    }
    // Update velocities if a key was pressed
    ProcessInput(key_code);

    // Update our position and draw the new snake
    UpdatePosition(win);
}
