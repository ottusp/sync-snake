#pragma once
#include "drawable.hpp"
#include "direction.hpp"

#include <ncurses.h>
#include <deque>


class SnakePiece : public Drawable {
  
  public:
    SnakePiece(): SnakePiece(0, 0) {
    }

    SnakePiece(int y, int x): Drawable(y, x, 'o') {
    }

    SnakePiece(Coordinates coord): SnakePiece(coord.getY(), coord.getX()) {
    }
};


class Snake {
  
  public:
    std::deque<SnakePiece> prev_pieces;
    Direction cur_direction;

    Snake() {
      cur_direction = DOWN;
      willGrow = false;
    }

    Snake(int y, int x) {
      cur_direction = DOWN;
      willGrow = false;

      yHead = y;
      xHead = x;
      SnakePiece piece(y, x);
      addPiece(piece);
    }

    void grow() {
      willGrow = true;
    }

    void addPiece(SnakePiece piece) {
      prev_pieces.push_front(piece);
    }

    void removePiece() {
      prev_pieces.pop_back();
    }

    SnakePiece head() {
      return prev_pieces.front();
    }

    SnakePiece tail() {
      return prev_pieces.back();
    }

    SnakePiece begin() {
      return head();
    }

    void move() {
      float verticalShift = 0, horizontalShift = 0;

      switch(cur_direction) {
        case UP:
          verticalShift = -1 * vSpeed;
          break;

        case DOWN:
          verticalShift = 1 * vSpeed;
          break;

        case LEFT:
          horizontalShift = -1 * hSpeed;
          break;

        case RIGHT:
          horizontalShift = 1 * hSpeed;
          break;
      }

      xHead += horizontalShift;
      yHead += verticalShift;
      Coordinates actualCell = getDiscreteHeadCell();

      SnakePiece piece(actualCell);
      addPiece(piece);

      if(!willGrow) {
        removePiece();
      }

      willGrow = false;
    }

    void changeDirection(Direction dir) {
      cur_direction = dir;
    }

    string headCoord() {
      return to_string(xHead) + " " + to_string(yHead);
    }

    string headDiscreteCoord() {
      Coordinates actualCell = getDiscreteHeadCell();
      return to_string(actualCell.getX()) + " " + to_string(actualCell.getY());
    }

  private:
    bool willGrow;

    float vSpeed = 0.025f;
    float hSpeed = 0.05f;

    float xHead;
    float yHead;

    Coordinates getDiscreteHeadCell() {
      return Coordinates(static_cast<int>(yHead), static_cast<int>(xHead));
    }
};