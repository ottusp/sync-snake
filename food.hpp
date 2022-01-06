///#pragma once
#include <ncurses.h>
#include "drawable.hpp"


class Food : public Drawable {
 
  public:
      Food(int y, int x): Drawable(y, x, 'Y') {
    }
};