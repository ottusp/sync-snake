#pragma once
#include <ncurses.h> 
#include "drawable.hpp"

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

    void addAt(int y, int x, chtype ch) {
      mvwaddch(board_win, y, x, ch);
    }

    chtype getInput() {
      return wgetch(board_win);
    }

    void clear() {
      wrefresh(board_win);
      addBorder();
    }

    void refresh() {
      wrefresh(board_win);
    }

  private:
    WINDOW *board_win;

    void construct(int height, int width) {
      int xMax, yMax;
      getmaxyx(stdscr, yMax, xMax); // pegando o tamanho máximo da tela

      board_win = newwin(height, width, (yMax/2) - (height/2), (xMax/2) - (width/2)); // definindo o tamanho do board (um quadrado centralizado)
    }
};