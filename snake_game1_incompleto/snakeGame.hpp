//#pragma once
#include <ncurses.h>
#include <time.h>
#include <stdlib.h>
#include "food.hpp"
#include "board.hpp"
#include "empty.hpp"
#include "drawable.hpp"
#include "snake.hpp"

class SnakeGame {

  public:

    // iniciando o jogo
    SnakeGame(int height, int width) {
      board = Board(height, width);
      board.initialize();
      game_over = false; 

      // para gerar aleatoriamente a fruta
      srand(time(NULL));
    }

    ~SnakeGame() {
      delete food;
    }

    void processInput() {
      chtype input = board.getInput();
    }

    void updateState() {
      int y, x;
      board.getEmptyCoordinates(y, x);

      // criando a comidinha
      // se já temos uma comidinha e a cobra chegou nela 
      if(food != NULL && ((snake.head() ))) {
        //então sobrescrevemos com espaço 
        board.add(Empty(food->getY(), food->getX()));
      
        // e geramos uma nova comidinha em um lugar aleatorio
        food = new Food(y, x);
        board.add(*food);
      }
      //board.add(Drawable(3, 3, '#'));
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
    Food *food;
    Snake *snake;
};