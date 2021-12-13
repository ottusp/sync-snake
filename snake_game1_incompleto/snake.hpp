#pragma once
#include <ncurses.h>
#include "drawable.hpp"
#include <queue>

enum Direction {
  UP,
  DOWN,
  LEFT,
  RIGHT,
  W,
  A,
  S,
  D
};

class SnakePiece : public Drawable {
  
  public:
    SnakePiece() {
      this->x = this->y = 0;
      this->icon = '#';
    }

    SnakePiece(int y, int x) {
      this->x = x;
      this->y = y;
      this->icon = '#';
    }
};


class Snake {
  
  public:
    std::queue<SnakePiece> prev_pieces;
    Direction cur_direction;

    Snake() {
      //cur_direction = DOWN;
    }

    void addPiece(SnakePiece piece) {
      prev_pieces.push(piece);
    }

    void removePiece() {
      prev_pieces.pop();
    }

    SnakePiece head() {
      return prev_pieces.front();
    }

    SnakePiece tail() {
      return prev_pieces.back();
    }
};