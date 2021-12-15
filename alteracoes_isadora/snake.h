#include <iostream>
#include <vector>
#include <ncurses.h>
#include <cstdlib>
#include <ctime>
#include <thread>
#ifndef SNAKE_GAME_H
#define SNAKE_GAME_H

struct CharPosition {
	int x, y;
	CharPosition(int col, int row);
	CharPosition();
};

class snakeGame {
private:
	int score, del, maxwidth, maxheight, score2;
	char direction, snakeBody, edgechar, fruitchar, direction2, snakeBody2;
	bool bEatsFruit, bEatsFruit2;
	CharPosition fruit;
	std::vector<CharPosition> snake;
	std::vector<CharPosition> snake2;

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