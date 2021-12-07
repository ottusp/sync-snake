#include "helpers.hpp"
#include "board.hpp"

class Food {
  private: 
    position food;

  public:
    position getDirection(Board board);
};