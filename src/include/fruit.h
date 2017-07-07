#ifndef SRC_INCLUDE_FRUIT_H_
#define SRC_INCLUDE_FRUIT_H_

#include "include/moveable.h"
#include "include/window_manager.h"
#include "include/snake.h"

class Fruit : virtual public Moveable {
    public:
        Fruit();
        Fruit(char symbol, int value, unsigned color, int x, int y);
        virtual void Init(WindowManager* win);
        virtual void Destroy(WindowManager* win, Snake* snake);
        virtual void Draw(WindowManager* win);
        virtual void Update(WindowManager* win);
        char GetSymbol() { return symbol_; }
        int GetValue() { return value_; }
        unsigned GetColor() { return color_; }

    protected:
        unsigned color_;
        char symbol_;
        int value_;

};

#endif  // SRC_INCLUDE_FRUIT_H_

