#include <iostream>
#include <ncurses.h>
#include <thread>
#include <unistd.h>

#include "board.hpp"
#include "snakeGame.hpp"
#include "drawable.hpp"

using namespace std;

#define BOARD_DIM 25
#define BOARD_ROWS BOARD_DIM
#define BOARD_COLS BOARD_DIM * 2.5

void play(SnakeGame game) {
  game.play();
}

void redraw(SnakeGame game) {
  game.redraw();
}

int main() {

  initscr();
  refresh();

  noecho();
  curs_set(0);

  SnakeGame game(BOARD_ROWS, BOARD_COLS);

  thread playThread(play, game);
  thread redrawThread(redraw, game);

  playThread.join();
  redrawThread.join();

  getch();
  endwin();

  return 0;
}