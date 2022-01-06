#pragma once

#include <iterator>
#include <ncurses.h>
#include <stdlib.h>
#include <string>
#include <time.h>

#include "board.hpp"
#include "direction.hpp"
#include "drawable.hpp"
#include "empty.hpp"
#include "food.hpp"
#include "helpers.hpp"
#include "player.hpp"
#include "snake.hpp"

using namespace std;

class SnakeGame {

  public:

    // iniciando o jogo
    SnakeGame(int height, int width) {
      board = Board(height, width);
      board.initialize();
      game_over = false;

      food = new Food(height/2, width*2/3);
      board.add(*food);
      player = new Player(height/2, width/2);
      board.addAt(height/2,  width/2, 'A');

      // para gerar aleatoriamente a fruta
      srand(time(NULL));
    }

    ~SnakeGame() {
      delete food;
      delete player;
    }

    void processInput() {
      if(kbhit()) {
        chtype input = board.getInput();

        if(isArrow(input)) {
          Direction dir = getDirectionFromArrow(input);

          player->snake->changeDirection(dir);
        }
      }
    }

    void updateState() {
      int y, x;
      board.getEmptyCoordinates(y, x);

      if(food != NULL && doesPlayerEatFruit(*player)) {
        board.add(Empty(food->getY(), food->getX()));
      
        food = new Food(y, x);
        board.add(*food);
        player->snake->grow();
        player->increasePoints();
      }

      board.add(Empty(player->snake->tail().getY(), player->snake->tail().getX()));
      player->snake->move();
      addSnakeToBoard();

      if (hasCollision(player->snake->head())) {
        game_over = true;
      }

      printScore(*player);
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
    Player *player;

    bool isArrow(chtype ch) {
      return ch == '\033';
    }

    Direction getDirectionFromArrow(chtype ch) {
      board.getInput();

      switch(board.getInput()) {
        case 'A':
          return UP;

        case 'B':
          return DOWN;

        case 'C':
          return RIGHT;

        case 'D':
          return LEFT;

        default:
          return DOWN;
      }
    }
    
    void addSnakeToBoard() {
      for(auto piece = player->snake->prev_pieces.begin(); piece != player->snake->prev_pieces.end(); piece++) {
        board.add(*piece);
      }
    }

    bool hasCollision(Drawable piece) {
      return piece.getX() == board.getWidth() - 1 || piece.getY() == board.getHeight() - 1
        || piece.getX() == 0 || piece.getY() == 0;
    }

    bool doesPlayerEatFruit(Player p) {
      return p.snake->head().getX() == food->getX()
          && p.snake->head().getY() == food->getY();
    }

    void printScore(Player p) {
      string text = p.getName() + "'s score: " + to_string(p.getPoints());
      board.addText(0, 1, text.c_str());
    }
};