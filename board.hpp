#pragma once

#include <ncurses.h> 
#include <queue>
#include <stdlib.h>
#include <string>

#include "drawable.hpp"

using namespace std;

class Board {
  
  public:
    Board(): Board(0, 0) {
    }

    Board(int height, int width){
      int xMax, yMax;
      getmaxyx(stdscr, yMax, xMax);
      this->height = height;
      this->width = width;

      board_win = newwin(height, width, (yMax/2) - (height/2), (xMax/2) - (width/2));

      renderBuffer = new queue<Drawable>();
    }

    Board(const Board& other) {
      board_win = other.board_win;

      height = other.height;
      width = other.width;

      renderBuffer = other.renderBuffer;
    }

    Board& operator=(const Board& other) {
      if(this != &other) {
        board_win = other.board_win;

        height = other.height;
        width = other.width;

        delete renderBuffer;
        renderBuffer = other.renderBuffer;
      }
      return *this;
    }

    void initialize() {
      clear();
      refresh();
    }

    void addBorder() {
      box(board_win, 0, 0);
    }

    void pushBuffer(Drawable drawable) {
      renderBuffer->push(drawable);
    }

    void pushBuffer(int y, int x, const char * text) {
      for (int i = 0; i < x; i++) {
        Drawable d(Coordinates(y, x+i), text[i]);
        renderBuffer->push(d);
      }
    }

    int processAllBuffer() {
      int size = renderBuffer->size();
      for (int i = 0; i < size; i++) {
        processBuffer();
      }

      return size;
    }

    void processBuffer() {
      if(renderBuffer->size()) {
        auto d = renderBuffer->front();
        add(d);
        renderBuffer->pop();
      }
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

    int getBufferSize() {
      return renderBuffer->size();
    }

  private:
    WINDOW *board_win;
    int height, width;

    queue<Drawable> * renderBuffer;

    void construct(int height, int width) {
      int xMax, yMax;
      getmaxyx(stdscr, yMax, xMax); // pegando o tamanho máximo da tela
      this->height = height;
      this->width = width;

      board_win = newwin(height, width, (yMax/2) - (height/2), (xMax/2) - (width/2)); // definindo o tamanho do board (um quadrado centralizado)
    }
};