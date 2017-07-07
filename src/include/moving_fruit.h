#ifndef SRC_INCLUDE_MOVING_FRUIT_H_
#define SRC_INCLUDE_MOVING_FRUIT_H_

#include "include/fruit.h"

class MovingFruit : public Fruit {
    public:
        MovingFruit();
        MovingFruit(char sym, int val, unsigned color, int x, int y);
        void Init(WindowManager* win);
        void Update(WindowManager* win);

    private:
        int frame_;
};

#endif  // SRC_INCLUDE_MOVING_FRUIT_H_

