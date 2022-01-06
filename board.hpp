#pragma once

#include <ncurses.h> 
#include <stdlib.h>
#include <string>

#include "drawable.hpp"

using namespace std;

class Board {
  
  public:

    //default
    Board() {
      construct(0, 0);
    }

    Board(int height, int width) {
      construct(height, width);
    }

    void initialize() {
      clear();
      refresh();
    }

    void addBorder() {
      box(board_win, 0, 0);
    }

    void add(Drawable drawable) {
      addAt(drawable.getY(), drawable.getX(), drawable.getIcon());
    }

    void addText(int y, int x, const char * text) {
      mvwaddstr(board_win, y, x, text);
    }

    void addAt(int y, int x, chtype ch) {
      mvwaddch(board_win, y, x, ch);
    }

    chtype getInput() {
      return wgetch(board_win);
    }

    //metodo para encontrar um lugar para inserir a comidinha
    void getEmptyCoordinates(int &y, int &x) {
      // fica no loop até encontrar um lugar vazio
      while((mvwinch(board_win, y = rand() % height, x = rand() % width)) != ' ');
    }

    void clear() {
      wrefresh(board_win);
      addBorder();
    }

    void refresh() {
      wrefresh(board_win);
    }

    int getHeight() {
      return height;
    }

    int getWidth() {
      return width;
    }

  private:
    WINDOW *board_win;
    int height, width;

    void construct(int height, int width) {
      int xMax, yMax;
      getmaxyx(stdscr, yMax, xMax); // pegando o tamanho máximo da tela
      this->height = height;
      this->width = width;

      board_win = newwin(height, width, (yMax/2) - (height/2), (xMax/2) - (width/2)); // definindo o tamanho do board (um quadrado centralizado)
    }
};