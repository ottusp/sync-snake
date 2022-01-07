#include <chrono>
#include <future>
#include <iostream>
#include <mutex>
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

mutex gameMutex;

void play(SnakeGame game) {
  const int delay = 3;

  while(!game.isOver()) {
    gameMutex.lock();
    game.play();
    gameMutex.unlock();
    usleep(delay * 1000);
  }
}

void redraw(SnakeGame game, future<void> futureObj) {
  const int delay = 18;

  while(futureObj.wait_for(chrono::milliseconds(1)) == future_status::timeout) {
    gameMutex.lock();
    game.redraw();
    gameMutex.unlock();
    usleep(delay * 1000);
  }
}

int main() {

  initscr();
  refresh();

  noecho();
  curs_set(0);

  SnakeGame game(BOARD_ROWS, BOARD_COLS);

  thread playThread(play, game);

  promise<void> exitSignal;
  future<void> futureObj = exitSignal.get_future();
  thread redrawThread(redraw, game, std::move(futureObj));

  playThread.join();

  exitSignal.set_value();
  redrawThread.join();

  getch();
  endwin();

  return 0;
}