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
    SnakeGame(int height, int width) {
      board = Board(height, width);
      board.initialize();
      game_over = false;

      food = new Food(height/2, width*2/3);
      board.pushBuffer(*food);
      player = new Player(height/2, width/2);

      srand(time(NULL));
    }

    SnakeGame(const SnakeGame& other) {
      board = other.board;

      food = new Food(board.getHeight()/2, board.getWidth()*2/3);

      player = new Player(board.getHeight()/2, board.getWidth()/2);
    }

    SnakeGame& operator=(const SnakeGame& other) {
      if(this != &other) {
        delete food;
        delete player;

        board = other.board;
        food = other.food;
        player = other.player;
      }
      return *this;
    }

    ~SnakeGame() {
      delete food;
      delete player;
    }

    void play() {
      const int delay = 40;

      while(!isOver()) {
        processInput();
        updateState();

        usleep(delay * 1000);
      }
    }

    void redraw() {
      const int delay = 36;

      while(!isOver()) {
        board.refresh();
        board.processAllBuffer();

        usleep(delay * 1000);
      }
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
        board.pushBuffer(Empty(food->getY(), food->getX()));
      
        food = new Food(y, x);
        board.pushBuffer(*food);
        player->snake->grow();
        player->increasePoints();
      }

      board.pushBuffer(Empty(player->snake->tail().getY(), player->snake->tail().getX()));
      player->snake->move();
      addSnakeToBoard();

      if (hasCollision(player->snake->head())) {
        game_over = true;
      }

      printScore(*player);
    }

    bool isOver() {
      return game_over;
    }
  
  private:
    int height;
    int width;

    bool game_over;

    Board board;
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
        board.pushBuffer(*piece);
      }
    }

    bool hasCollision(Drawable piece) {
      return piece.getX() >= board.getWidth() - 1 || piece.getY() >= board.getHeight() - 1
        || piece.getX() <= 0 || piece.getY() <= 0;
    }

    bool doesPlayerEatFruit(Player p) {
      return p.snake->head().getX() == food->getX()
          && p.snake->head().getY() == food->getY();
    }

    void printScore(Player p) {
      string text = p.getName() + "'s score: " + to_string(p.getPoints());
      board.addText(0, 1, text.c_str());
      board.addText(board.getHeight()-1, 1, p.snake->headCoord().c_str());
      board.addText(board.getHeight()-1, board.getWidth()/3 + 2, p.snake->headDiscreteCoord().c_str());
      board.addText(board.getHeight()-1, board.getWidth()*2/3, (to_string(p.snake->prev_pieces.size()).c_str()));
    }
};