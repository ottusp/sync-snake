///#pragma once
#include <ncurses.h>
#include "drawable.hpp"


class Food : public Drawable {
 
  public:
      Food(int y, int x) {
        this->y = y; 
        this->x = x;
        this->icon = 'Y';
    }
};