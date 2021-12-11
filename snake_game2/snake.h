#include <iostream>
#include <vector>
#include <ncurses.h>
#include <cstdlib>
#include <ctime>
#ifndef SNAKE_GAME_H
#define SNAKE_GAME_H

struct CharPosition {
	int x, y;
	CharPosition(int col, int row);
	CharPosition();
};

class snakeGame {
private:
	int score, del, maxwidth, maxheight;
	char direction, snakeBody, edgechar, fruitchar;
	bool bEatsFruit;
	CharPosition fruit;
	std::vector<CharPosition> snake;

	void InitGameWindow();
	void DrawWindow();  
	void DrawSnake();
	void PrintScore();
	void PositionFruit();
	bool FatalCollision();
	void MoveSnake();
	bool GetsFruit();

public:
	snakeGame();
	~snakeGame(); // limpa e desaloca memoria
	void PlayGame(); 
};

#endif