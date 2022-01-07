///#pragma once 
#include <ncurses.h>
#include "drawable.hpp"

class Empty : public Drawable {
  
  public:
    Empty(int y, int x): Drawable(y, x, ' ') {
    }
};