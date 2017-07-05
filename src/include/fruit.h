#ifndef SRC_INCLUDE_FRUIT_H_
#define SRC_INCLUDE_FRUIT_H_

#include "include/moveable.h"
#include "include/window.h"

class Fruit : public Moveable {
 public:
  Fruit(char symbol, int value);
  Fruit(char symbol, int value, int x, int y, int vx, int vy);
  void Init(WindowManager* win);
  void Destroy(WindowManager* win);
  void Update(WindowManager* win);
  void Draw(WindowManager* win);
  char GetSymbol() { return symbol_; }
  int GetValue() { return value_; }

 private:
  char symbol_;
  int value_;

};

#endif  // SRC_INCLUDE_FRUIT_H_

