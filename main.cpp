#include <ncurses.h> 
#include "board.hpp"
#include "snakeGame.hpp"
#include "drawable.hpp"

using namespace std;

#define BOARD_DIM 25
#define BOARD_ROWS BOARD_DIM
#define BOARD_COLS BOARD_DIM * 2.5

int main() {

  initscr();
  refresh();  

  noecho();

  SnakeGame game(BOARD_ROWS, BOARD_COLS);
  
  while(!game.isOver()) {
     
     game.processInput();

     game.updateState();

     game.redraw();
  }

  getch();
  endwin();

  return 0;
}