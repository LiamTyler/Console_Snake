#include "include/snake_fruit.h"
#include <algorithm>
#include <cmath>
#include <ncurses.h>

SnakeFruit::SnakeFruit() :
    target_(nullptr), dead_(false),
    Fruit('f', 0, COLOR_RED, 0, 0),
    Snake('E', 'e', 0, 0, 0, 0) {}

void SnakeFruit::Init(WindowManager* win) {
    do {
        x_ = rand() % win->ScreenWidth();
        y_ = std::max(rand() % win->ScreenHeight(), 1+ win->TBorder());
    } while (win->GetChar(x_, y_) != ' ');
    segments_[0].x = x_;
    segments_[0].y = y_;
}

// I don't know anything about pathfinding, so this is probably super bad code
void SnakeFruit::GotoTarget(WindowManager* win) {
    if (!target_)
        return;

    // position we are trying to reach
    int x = target_->X();
    int y = target_->Y();
    if (x_ == x && y_ == y)
        return;

    // direction we need to go to reach that
    int dx = x - x_;
    if (dx)
        dx = dx / std::abs(dx);
    int dy = y - y_;
    if (dy)
        dy = dy / std::abs(dy);
    /*
    win->PrintString("dx:    ", 60, 22);
    win->PrintString("dy:    ", 67, 22);
    win->PrintString("dx: " + std::to_string(dx), 60, 22);
    win->PrintString("dy: " + std::to_string(dy), 67, 22);
    win->PrintString("vx:    ", 74, 22);
    win->PrintString("vy:    ", 81, 22);
    win->PrintString("vx: " + std::to_string(vx_), 74, 22);
    win->PrintString("vy: " + std::to_string(vy_), 81, 22);
    */

    // Calculate valid directions to move
    // i.e., not off the map, and not into itself
    bool lvalid = (x_ > 1);
    if (lvalid) {
        int ch = win->GetChar(x_ - 1, y_);
        lvalid &= (ch != h_symbol_ && ch != b_symbol_);
    }
    bool rvalid = (x_ < win->RBorder() - 1);
    if (rvalid) {
        int ch = win->GetChar(x_ + 1, y_);
        rvalid &= (ch != h_symbol_ && ch != b_symbol_);
    }
    bool uvalid = (y_ > win->TBorder() + 1);
    if (uvalid) {
        int ch = win->GetChar(x_, y_ - 1);
        uvalid &= (ch != h_symbol_ && ch != b_symbol_);
    }
    bool dvalid = (y_ < win->BBorder() - 2);
    if (dvalid) {
        int ch = win->GetChar(x_, y_ + 1);
        dvalid &= (ch != h_symbol_ && ch != b_symbol_);
    }

    if (x_ != x) {
        if (vx_ == dx) {
            bool cont = true;
            if (dx < 0) {
                cont = lvalid;
            } else {
                cont = rvalid;
            }
            if (!cont) {
                if (uvalid) {
                    vy_ = -1;
                    vx_ = 0;
                 } else if (dvalid) {
                    vy_ = 1;
                    vx_ = 0;
                 } else if (rvalid)
                    vx_ = 1;
                else if (lvalid)
                    vx_ = -1;
                else
                    dead_ = true;
            }
        } else if (vx_ == -dx) {
            if (uvalid) {
                vx_ = 0;
                vy_ = -1;
            } else if (dvalid) {
                vx_ = 0;
                vy_ = 1;
            } else {
                if (vx_ < 0)
                    dead_ = lvalid;
                else
                    dead_ = rvalid;
            }
        } else if (vx_ == 0) {
            if (dx < 0) {
                if (lvalid) {
                    vx_ = -1;
                    vy_ = 0;
                }
            } else {
                if (rvalid) {
                    vx_ = 1;
                    vy_ = 0;
                }
            }
            if (vx_ == 0) {
                vy_ = 0;
                if (uvalid)
                    vy_ = -1;
                else if (dvalid)
                    vy_ = 1;
                else if (rvalid)
                    vx_ = 1;
                else if (lvalid)
                    vx_ = -1;
                else
                    dead_ = true;
            }
        }
    }
    else {
        if (vy_ == dy) {
            bool cont = true;
            if (dy < 0) {
                cont = uvalid;
            } else {
                cont = dvalid;
            }
            if (!cont) {
                if (rvalid) {
                    vx_ = 1;
                    vy_ = 0;
                } else if (lvalid) {
                    vx_ = -1;
                    vy_ = 0;
                } else if (dvalid)
                    vy_ = 1;
                else if (uvalid)
                    vy_ = -1;
                else
                    dead_ = true;
            }
        } else if (vy_ == -dy) {
            if (rvalid) {
                vx_ = 1;
                vy_ = 0;
            } else if (lvalid) {
                vx_ = -1;
                vy_ = 0;
            } else {
                if (vy_ < 0)
                    dead_ = uvalid;
                else
                    dead_ = dvalid;
            }
        } else if (vy_ == 0) {
            if (dy < 0) {
                if (uvalid) {
                    vy_ = -1;
                    vx_ = 0;
                }
            } else {
                if (dvalid) {
                    vy_ = 1;
                    vx_ = 0;
                }
            }
            if (vy_ == 0) {
                vx_ = 0;
                if (uvalid)
                    vy_ = -1;
                else if (dvalid)
                    vy_ = 1;
                else if (rvalid)
                    vx_ = 1;
                else if (lvalid)
                    vx_ = -1;
                else
                    dead_ = true;
            }
        }
    }
}

void SnakeFruit::Update(WindowManager* win) {
    // Add a single segment if we are currently growing
    if (grow_) {
        AddSegment();
    }

    // Update velocities if a key was pressed
    GotoTarget(win);
    if (dead_)
        return;

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
    Snake::Draw(win);
}
