#include <iostream>
#include <vector>
#include <ncurses.h>
#include <cstdlib>
#include <ctime>
#include <thread>
#ifndef SNAKE_GAME_H
#define SNAKE_GAME_H

/*enum Direction {
  up,
  down,
  left, 
  right,
  A,
  W,
  S,
  D
};*/

struct CharPosition {
	int x, y;
	CharPosition(int col, int row);
	CharPosition();
};

struct Player {
	std::vector<CharPosition> snake;
	char snakeBody;
	char direction;
	int score;
	bool bEatsFruit;
};

class snakeGame {
private:
	int del, maxwidth, maxheight; //score
	char direction, snakeBody, edgechar, fruitchar;
	//bool bEatsFruit;
	CharPosition fruit;
	//std::vector<CharPosition> snake;

	void InitGameWindow();
	void DrawWindow();  
	void DrawSnake();
	void PrintScore();
	void PositionFruit();
	bool FatalCollision();
	
	void MoveSnake();
	void MoveSnake2();

	bool GetsFruit();
	bool GetsFruit2();

public:
	snakeGame();
	~snakeGame(); // limpa e desaloca memoria
	void PlayGame(); 
};

#endif