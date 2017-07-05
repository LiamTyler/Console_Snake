#ifndef SRC_INCLUDE_MOVEABLE_H_
#define SRC_INCLUDE_MOVEABLE_H_

#include <iostream>

class Moveable {
    public:
        Moveable() : Moveable(0,0,0,0) {}
        Moveable(int x, int y, int vx, int vy) :
            x_(x), y_(y), vx_(vx), vy_(vy) {}

        int VX() { return vx_; }
        int VY() { return vy_; }
        int X() { return x_; }
        int Y() { return y_; }

    protected:
        int x_;
        int y_;
        int vx_;
        int vy_;

        void X(int x) { x_ = x; }
        void Y(int y) { y_ = y; }
        void VX(int vx) { vx_ = vx; }
        void VY(int vy) { vy_ = vy; }

};

#endif  // SRC_INCLUDE_MOVEABLE_H_

