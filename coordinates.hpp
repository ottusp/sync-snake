#pragma once

class Coordinates {
  public:
    Coordinates(int y, int x) {
      this->y = y;
      this->x = x;
    }

    int operator==(Coordinates other) {
      return x == other.x && y == other.y;
    }

    int getY() {
      return y;
    }

    int getX() {
      return x;
    }

  protected:
    int x, y;
};