#pragma once

#include "coordinates.hpp"

class Drawable {
  public: 
    Drawable(): Drawable(0, 0, ' ') {
    }

    Drawable(int y, int x, chtype ch): Drawable(Coordinates(y, x), ch) {
    }

    Drawable(Coordinates coordinates, chtype ch) {
      coord = new Coordinates(coordinates.getY(), coordinates.getX());
      this->icon = ch;
    }

    int getX() {
      return coord->getX();
    }

    int getY() {
      return coord->getY();
    }

    Coordinates getCoordinates() {
      return *coord;
    }

    int getIcon() {
      return icon;
    }

  protected:
    Coordinates * coord;
    chtype icon;
};