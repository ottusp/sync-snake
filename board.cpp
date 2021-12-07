#include "board.hpp"

#include <iostream>

using namespace std;

void Board::printBoard() {
  for(int i = 0; i < HEIGHT; i++) {
    for(int j = 0; j < WIDTH; j++) {
      if(i == 0 || j == 0 || i == HEIGHT - 1 || j == WIDTH - 1)
        printf("#");
      else
        printf(" ");
    }
  cout << endl;
  }
}