#include "snake.h"

int maxHeight, maxWidth;
void PlayGame();
int InitScreen();
int FinalScreen();
void ClearCentre();
int UserInput();

int main () {
    // verifica se o usuario que jogar
	if (InitScreen() == 'S')
	do {
		{
			snakeGame NewSnake;
			NewSnake.PlayGame();
		}
	}
	while (FinalScreen() == 'S'); // enquanto o usuario quiser continuar jogando

	return 0;
}

// limpa a tela e centraliza o cursor
void ClearCentre(float x, float y) {
	clear();
	initscr(); 
	noecho();
	getmaxyx(stdscr, maxHeight, maxWidth);
	move((maxHeight/y), (maxWidth/x));
}

// recebe a tecla digitada pelo usuario
int UserInput() {
	int UserInput = getch();
	refresh();
	endwin();
	clear();

	return UserInput;	
}

// tela de inicio
int InitScreen()  {
	ClearCentre(3, 2.5);
    printw("JOGO DA COBRINHA!\n");

	printw("                 Está pronto para começar a jogar?? (S/N)   ");

	return UserInput();
}

// tela final e pergunta se o usuario quer jogar novamente
int FinalScreen() {
	ClearCentre(3, 2.5);
	printw("QUER JOGAR NOVAMENTE? (S/N)");
	return UserInput();
}