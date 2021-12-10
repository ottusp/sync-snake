#pragma once
#include <ncurses.h>
#include "drawable.hpp"


class Food : public Drawable {
 
  public:
    Apple(int y, int x) {
        this->y = y; 
        this->x = x;
        this->icon = 'Ó';
    }
};