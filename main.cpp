#include <iostream>
#include <vector>

#include "helpers.hpp"
#include "board.hpp"

using namespace std;
bool gameEnded = false;

int main() {
  Board board;

  while(!gameEnded) {
    board.printBoard();
    usleep(1000000);
  }

  return 0;
}