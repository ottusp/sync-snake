#include <ncurses.h>
#include <unistd.h>

#include "board.hpp"
#include "snakeGame.hpp"
#include "drawable.hpp"

using namespace std;

#define BOARD_DIM 25
#define BOARD_ROWS BOARD_DIM
#define BOARD_COLS BOARD_DIM * 2.5

#define DELAY 100// milissegundos

int main() {

  initscr();
  refresh();

  noecho();
  curs_set(0);

  SnakeGame game(BOARD_ROWS, BOARD_COLS);
  
  while(!game.isOver()) {
    game.processInput();

    game.updateState();

    game.redraw();

    usleep(DELAY * 1000);
  }

  getch();
  endwin();

  return 0;
}