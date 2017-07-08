#ifndef SRC_INCLUDE_SNAKE_FRUIT_H_
#define SRC_INCLUDE_SNAKE_FRUIT_H_

#include "include/snake.h"
#include "include/fruit.h"

class SnakeFruit : public Snake, public Fruit {
    public:
        SnakeFruit();
        virtual void Init(WindowManager* win);
        virtual void Update(WindowManager* win);
        virtual int Destroy(WindowManager* win);
        virtual void EatFruit(Fruit* fruit, WindowManager* win);
        virtual void GotoTarget(WindowManager* win);
        virtual void SetTarget(Fruit* f) { target_ = f; }
        bool Dead() { return dead_; }

    protected:
        Fruit* target_;
        bool dead_;
};

#endif  // SRC_INCLUDE_SNAKE_FRUIT_H_

