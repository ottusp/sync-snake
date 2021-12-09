#pragma once
#include <ncurses.h>
#include "board.hpp"

class SnakeGame {

  public:

    // iniciando o jogo
    SnakeGame(int height, int width) {
      board = Board(height, width);
      board.initialize();
      game_over = false; 
    }

    void processInput() {
      chtype input = board.getInput();

    }

    void updateState() {

    }

    void redraw() {
      board.refresh();
    }

    bool isOver() {
      return game_over;
    }
  
  private:
    Board board;
    bool game_over;
};