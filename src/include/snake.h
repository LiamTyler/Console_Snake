#ifndef SRC_INCLUDE_SNAKE_H_
#define SRC_INCLUDE_SNAKE_H_

#include "include/window_manager.h"
#include "include/moveable.h"
#include <vector>

/* Brief: This struct is just for keeping track of the position of
 *        each segment of the snake. All it has are x, y member variables
 *        to keep track of which column / row the snake is on.
 */
typedef struct vec2 {
    vec2() {
        x = 0;
        y = 0;
    }
    vec2(int xx, int yy) {
        x = xx;
        y = yy;
    }
    int x;
    int y;
} vec2;

/* Brief: Snake
 */
class Snake : virtual public Moveable {
    public:
        Snake();
        Snake(char head_symbol, char body_symbol, int x, int y, int vx, int vy);
        virtual bool Update(WindowManager* win, int key_code);
        virtual void Draw(WindowManager* win);
        virtual void Erase(WindowManager* win);
        virtual void AddSegment();
        virtual void ProcessInput(int key_code);
        char GetHeadSymbol() { return h_symbol_; }
        char GetBodySymbol() { return b_symbol_; }
        void Grow(int g) { grow_ += g; }
        int Score() { return score_; }
        void Score(int s) { score_ = s; }

    protected:
        char h_symbol_;
        char b_symbol_;
        int grow_;
        int size_;
        int score_;
        std::vector<vec2> segments_;
};

#endif  // SRC_INCLUDE_SNAKE_H_
