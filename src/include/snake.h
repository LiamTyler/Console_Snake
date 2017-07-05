#ifndef SNAKE_H_
#define SNAKE_H_

class Snake {
    public:
        Snake();
        Snake(char symbol, int x, int y, int vx, int vy);
        void Update();
        void VX(int vx) { vx_ = vx; }
        void VY(int vy) { vy_ = vy; }
        int VX() { return vx_; }
        int VY() { return vy_; }
        int X() { return x_; }
        int Y() { return y_; }
        char GetSymbol() { return symbol_; }

    private:
        int x_;
        int y_;
        int vx_;
        int vy_;
        char symbol_;
};

#endif  // SNAKE_H_
