#include "helpers.hpp"

#include <iostream>
#include <vector>

using namespace std;

class Snake {
  private:
    position head;
    position tail;
    vector<position> body;
    direction pointer;

  public:
    void headUp();
    void headLeft();
    void headDown();
    void headRight();
};