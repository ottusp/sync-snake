#include "snake.h"
#include <unistd.h>

using namespace std;

CharPosition::CharPosition(int col, int row) {
	x = col;
	y = row;
}

CharPosition::CharPosition() {
	x = 0;
	y = 0;
}

snakeGame::snakeGame() {
	
    // inicializando variaveis
	snakeBody = 'o'; 
	edgechar = (char)219;
	fruitchar = '@'; 
	fruit.x = 0; 
	fruit.y = 0; 
	score = 0; 
	del = 110000;
	bool bEatsFruit = 0;
	direction = 'l';

	srand(time(NULL));
	
	InitGameWindow();
	PositionFruit();
	DrawWindow();
	DrawSnake();
	PrintScore();

	refresh();	
}

snakeGame::~snakeGame() {
	nodelay(stdscr, false);
	getch();
	endwin();
}

// inicializando a tela do jogo
void snakeGame::InitGameWindow() { 

	initscr(); // incializa a tela
	nodelay(stdscr,TRUE);
	keypad(stdscr, true); // inicializa o teclado para usar as teclas de direcao para movimentar a cobrinha
    
	noecho();
	curs_set(0);

	getmaxyx(stdscr, maxheight, maxwidth); // dimensoes da tela

	return; 
}

// desenha as "paredes" da tela do jogo
void snakeGame::DrawWindow() {

    // teto
	for (int i = 0; i < maxwidth; i++){ 
		move(0, i);
		addch(edgechar);
	}

    // chao
	for (int i = 0; i < maxwidth; i++) {
		move(maxheight-2, i);
		addch(edgechar);
	}

    // parede esquerda
	for (int i = 0; i < maxheight-1; i++) {
		move(i, 0);
		addch(edgechar);
	}  

    // parede direita
	for (int i = 0; i < maxheight-1; i++) {
		move(i, maxwidth-1);
		addch(edgechar);
	}

	return;
}

// desenha a cobrinha
void snakeGame::DrawSnake()
{
	for (int i = 0; i < 5; i++) {
		snake.push_back(CharPosition(30+i, 10));
	}

	for (int i = 0; i < snake.size(); i++) {
		move(snake[i].y, snake[i].x);
		addch(snakeBody);
	}

	return;
}

// mostra pontuacao
void snakeGame::PrintScore() {
	move(maxheight-1, 0);
	printw("Score: %d", score);
	return;
}

// posiciona a frutinha na tela
void snakeGame::PositionFruit() {
	while(1) {
		int tmpx = rand()%maxwidth+1;
		int tmpy = rand()%maxheight+1;

		// verifica se a posicao da fruta nao e a mesma da cobra
		for (int i = 0; i < snake.size(); i++) {
			if (snake[i].x == tmpx && snake[i].y == tmpy) {
				continue;
			}
		}

		// verifica se a posicao da fruta nao e a mesma dos limites da tela
		if (tmpx >= maxwidth-2 || tmpy >= maxheight-3) {
			continue;
		}

		fruit.x = tmpx;
		fruit.y = tmpy;

		break;
	}

	move(fruit.y, fruit.x); 
	addch(fruitchar);
	refresh();
}

// verifica se o jogo acabou
bool snakeGame::FatalCollision()
{
	// se a cobrinha colidiu nos limites da tela
	if (snake[0].x == 0 || snake[0].x == maxwidth-1 || snake[0].y == 0 || snake[0].y == maxheight-2) {
		return true;
	}

	// se a cobrinha colidiu nela mesma
	for (int i = 2; i < snake.size(); i++) {
		if (snake[0].x == snake[i].x && snake[0].y == snake[i].y) {
			return true;
		}
	}

	return false;
}

// verifica se a cobrinha comeu a fruta
bool snakeGame::GetsFruit() {
	if (snake[0].x == fruit.x && snake[0].y == fruit.y) {
		PositionFruit(); 
		score +=10; 
		PrintScore();

		return bEatsFruit = true;
	}
	else 
	{
		return bEatsFruit = false;
	}
	return bEatsFruit;
}

// movimentos da cobrinha
void snakeGame::MoveSnake() {
	int KeyPressed = getch();

    // verifica a tecla pressionada
	switch(KeyPressed)
	{
		case KEY_LEFT:
			if (direction != 'r') 
			{ direction = 'l'; }  
			break;
		case KEY_RIGHT:
			if (direction != 'l')
			{ direction = 'r'; }
			break;
		case KEY_UP:
			if (direction != 'd')
			{ direction = 'u'; }
			break;
		case KEY_DOWN:
			if (direction != 'u')
			{ direction = 'd'; }
			break;
		case KEY_BACKSPACE:
			direction = 'q'; // "QUIT" para sair do jogo
			break;
	}

	// se a cobrinha nao comer a fruta, permanece com o mesmo tamanho
	if (!bEatsFruit)
	{
		move(snake[snake.size()-1].y, snake[snake.size()-1].x); // fim da cauda
		printw(" "); // adicionando char vazio
		refresh();
		snake.pop_back(); // remove o ultimo elemento do vetor
	}

	// conforme a cobrinha se movimenta, adicionamos um char extra no inicio do vetor 
	// inicializando coordenadas de acordo com a direcao
	if (direction == 'l') { 
        snake.insert(snake.begin(), CharPosition(snake[0].x-1, snake[0].y)); 
    } 
	else if (direction == 'r') { 
        snake.insert(snake.begin(), CharPosition(snake[0].x+1, snake[0].y)); 
    }
	else if (direction == 'u') { 
        snake.insert(snake.begin(), CharPosition(snake[0].x, snake[0].y-1)); 
    }
	else if (direction == 'd') { 
        snake.insert(snake.begin(), CharPosition(snake[0].x, snake[0].y+1)); 
    }

	// movimenta a cobrinha para nova coordenada
	move(snake[0].y, snake[0].x);

    // incrementa o corpo da cobrinha
	addch(snakeBody); 

	refresh();
	return;
}

// controla o jogo
void snakeGame::PlayGame() {
    while(1) {
        if (FatalCollision()) {
            move((maxheight-2)/2,(maxwidth-5)/2);
            printw("GAME OVER!!");
            break;
        }

        GetsFruit();
        MoveSnake();

        if (direction == 'q') {
        	break;
        }

        usleep(del); // delay
    }
}