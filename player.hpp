#pragma once

#include "snake.hpp"

#define POINTS_INCREASE 10

class Player {
  public:
    Snake * snake;

    Player(): Player(1, 1, "Player") {
    }

    Player(int y, int x): Player(y, x, "Player") {
    }

    Player(int y, int x, string name) {
      snake = new Snake(y, x);
      // toupper(name[0]);
      this->name = name;
    }

  int getPoints() {
    return points;
  }

  void increasePoints() {
    points += POINTS_INCREASE;
  }

  string getName() {
    return name;
  }

  private:
    int points;

    string name;
};