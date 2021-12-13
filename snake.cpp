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

Player p1;
Player p2;

snakeGame::snakeGame() {
	
    // inicializando variaveis
	p1.snakeBody = 'o'; 
	p2.snakeBody = 'u';
	edgechar = (char)219;

	fruitchar = '@'; 

	fruit.x = 0; 
	fruit.y = 0; 

	p1.score = 0;
	p2.score = 0; 
	del = 110000;
	
	p1.bEatsFruit = 0;
	p2.bEatsFruit = 0;

	p1.direction = 'l';
	p2.direction = 'l';

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

// inicializar jogo
void snakeGame::InitGameWindow() { 

	initscr(); // incializa a tela
	nodelay(stdscr,TRUE);

	keypad(stdscr, true); // inicializa o teclado para movimentar as cobrinhas
    
	noecho();
	curs_set(0);

	getmaxyx(stdscr, maxheight, maxwidth); // dimensoes da tela

	return; 
}

// desenha as bordas da tela
void snakeGame::DrawWindow() {

    // superior
	for (int i = 0; i < maxwidth; i++){ 
		move(0, i);
		addch(edgechar);
	}

    // inferior
	for (int i = 0; i < maxwidth; i++) {
		move(maxheight-2, i);
		addch(edgechar);
	}

    // esquerda
	for (int i = 0; i < maxheight-1; i++) {
		move(i, 0);
		addch(edgechar);
	}  

    // direita
	for (int i = 0; i < maxheight-1; i++) {
		move(i, maxwidth-1);
		addch(edgechar);
	}

	return;
}

// desenha a cobrinha
void snakeGame::DrawSnake()
{
	
	// desenhando a cobrinha do player1
	for (int i = 0; i < 5; i++) {
		p1.snake.push_back(CharPosition(30+i, 10));
	}

	for (int i = 0; i < p1.snake.size(); i++) {
		move(p1.snake[i].y, p1.snake[i].x);
		addch(p1.snakeBody);
	}


	// desenhando a cobrinha do player2
	for (int i = 0; i < 5; i++) {
		p2.snake.push_back(CharPosition(50-i, -10));
	}

	for (int i = 0; i < p2.snake.size(); i++) {
		move(p2.snake[i].y, p2.snake[i].x);
		addch(p2.snakeBody);
	}

	// cobra 2
	for (int i = 0; i < 5; i++) {
		snake2.push_back(CharPosition(50+i, 10));
	}

	for (int i = 0; i < snake2.size(); i++) {
		move(snake2[i].y, snake2[i].x);
		addch(snakeBody2);
	}


	return;
}


// mostra pontuacao
void snakeGame::PrintScore() {
	move(maxheight-1, 0);
	printw("Score Player 1: %d", p1.score);

	move(maxheight-1, maxwidth-22);
	printw("Score Player 2: %d", p2.score);
	return;
}


// posiciona a frutinha na tela
void snakeGame::PositionFruit() {
	while(1) {
		int tmpx = rand()%maxwidth+1;
		int tmpy = rand()%maxheight+1;

		// verifica se a posicao da fruta nao e a mesma da cobra do player1 
		for (int i = 0; i < p1.snake.size(); i++) {
			if (p1.snake[i].x == tmpx && p1.snake[i].y == tmpy) {
				continue;
			}
		}

		// verifica se a posicao da fruta nao e a mesma da cobra do player2
		for (int i = 0; i < p2.snake.size(); i++) {
			if (p2.snake[i].x == tmpx && p2.snake[i].y == tmpy) {
				continue;
			}

			if(snake2[i].x == tmpx && snake2[i].y == tmpy) {
				continue;
			}
		}

		// verifica se a posicao da fruta nao e a mesma da borda
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
	// Player1: se a cobrinha colidiu nos limites da tela
	if (p1.snake[0].x == 0 || p1.snake[0].x == maxwidth-1 || p1.snake[0].y == 0 || p1.snake[0].y == maxheight-2) {
		return true;
	}

	if (snake2[0].x == 0 || snake2[0].x == maxwidth-1 || snake2[0].y == 0 || snake2[0].y == maxheight-2) {
		return true;
	}

	// se a cobrinha colidiu nela mesma
	for (int i = 2; i < p1.snake.size(); i++) {
		if (p1.snake[0].x == p1.snake[i].x && p1.snake[0].y == p1.snake[i].y) {
			return true;
		}
	}


	// Player2: se a cobrinha colidiu nos limites da tela
	if (p2.snake[0].x == 0 || p2.snake[0].x == maxwidth-1 || p2.snake[0].y == 0 || p2.snake[0].y == maxheight-2) {
		return true;
	}

	// se a cobrinha colidiu nela mesma
	for (int i = 2; i < p2.snake.size(); i++) {
		if (p2.snake[0].x == p2.snake[i].x && p2.snake[0].y == p2.snake[i].y) {
			return true;
		}
	}


	return false;
}

// ESSA LOGICA NÃO TA CERTA, PRECISA CORRIGIR
// verifica se a cobrinha comeu a fruta
bool snakeGame::GetsFruit() {

	// player1
	if (p1.snake[0].x == fruit.x && p1.snake[0].y == fruit.y) {
		PositionFruit(); 
		p1.score +=10; 
		PrintScore();

		return p1.bEatsFruit = true;
	}

	else 
	{
		return p1.bEatsFruit = false;
	}


	// player2
	if (p2.snake[0].x == fruit.x && p2.snake[0].y == fruit.y) {
		PositionFruit(); 
		p2.score +=10; 
		PrintScore();

		return p2.bEatsFruit = true;
	}

	return p2.bEatsFruit;
}

// verifica se a cobrinha 2 comeu a fruta
bool snakeGame::GetsFruit2() {
	if (snake2[0].x == fruit.x && snake2[0].y == fruit.y) {
		PositionFruit(); 
		score2 +=10; 
		PrintScore();

		return bEatsFruit2 = true;
	}
	else 
	{
		return bEatsFruit2 = false;
	}
	return bEatsFruit2;
}

// movimentos da cobrinha
void snakeGame::MoveSnake() {
	int KeyPressed1 = getch();
	int KeyPressed2 = getch();

    // Player1: verifica a tecla pressionada
	switch(KeyPressed1)
	{
		case KEY_LEFT:
			if (p1.direction != 'r') 
			{ p1.direction = 'l'; }  
			break;
		case KEY_RIGHT:
			if (p1.direction != 'l')
			{ p1.direction = 'r'; }
			break;
		case KEY_UP:
			if (p1.direction != 'd')
			{ p1.direction = 'u'; }
			break;
		case KEY_DOWN:
			if (p1.direction != 'u')
			{ p1.direction = 'd'; }
			break;
		case KEY_BACKSPACE:
			p1.direction = 'q'; // "QUIT" para sair do jogo
			break;
		default: break;
	}


	// Player2: verifica a tecla pressionada
	switch(KeyPressed2)
	{
		case 'A':
		case 'a':
			if (p2.direction != 'r') 
			{ p2.direction = 'l'; }  
			break;
		case 'D':
		case 'd':
			if (p2.direction != 'l')
			{ p2.direction = 'r'; }
			break;
		case 'W':
		case 'w':
			if (p2.direction != 'd')
			{ p2.direction = 'u'; }
			break;
		case 'S':
		case 's':
			if (p2.direction != 'u')
			{ p2.direction = 'd'; }
			break;
		case KEY_BACKSPACE:
			p2.direction = 'q'; // "QUIT" para sair do jogo
			break;
	}



	// Player1: se a cobrinha nao comer a fruta, permanece com o mesmo tamanho
	if (!p1.bEatsFruit)
	{
		move(p1.snake[p1.snake.size()-1].y, p1.snake[p1.snake.size()-1].x); // fim da cauda
		printw(" "); // adicionando char vazio
		refresh();
		p1.snake.pop_back(); // remove o ultimo elemento do vetor
	}

	// Player2: se a cobrinha nao comer a fruta, permanece com o mesmo tamanho
	if (!p2.bEatsFruit)
	{
		move(p2.snake[p2.snake.size()-1].y, p2.snake[p2.snake.size()-1].x); // fim da cauda
		printw(" "); // adicionando char vazio
		refresh();
		p2.snake.pop_back(); // remove o ultimo elemento do vetor
	}

	// PLAYER1
	// conforme a cobrinha se movimenta, adicionamos um char extra no inicio do vetor 
	// inicializando coordenadas de acordo com a direcao
	if (p1.direction == 'l') { 
        p1.snake.insert(p1.snake.begin(), CharPosition(p1.snake[0].x-1, p1.snake[0].y)); 
    } 
	else if (p1.direction == 'r') { 
        p1.snake.insert(p1.snake.begin(), CharPosition(p1.snake[0].x+1, p1.snake[0].y)); 
    }
	else if (p1.direction == 'u') { 
        p1.snake.insert(p1.snake.begin(), CharPosition(p1.snake[0].x, p1.snake[0].y-1)); 
    }
	else if (p1.direction == 'd') { 
        p1.snake.insert(p1.snake.begin(), CharPosition(p1.snake[0].x, p1.snake[0].y+1)); 
    }

	// movimenta a cobrinha para nova coordenada
	move(p1.snake[0].y, p1.snake[0].x);

    // incrementa o corpo da cobrinha
	addch(p1.snakeBody); 


	// PLAYER2
	// conforme a cobrinha se movimenta, adicionamos um char extra no inicio do vetor 
	// inicializando coordenadas de acordo com a direcao
	if (p2.direction == 'A') { 
        p2.snake.insert(p2.snake.begin(), CharPosition(p2.snake[0].x-1, p2.snake[0].y)); 
    } 
	else if (p2.direction == 'D') { 
        p2.snake.insert(p2.snake.begin(), CharPosition(p2.snake[0].x+1, p2.snake[0].y)); 
    }
	else if (p2.direction == 'W') { 
        p2.snake.insert(p2.snake.begin(), CharPosition(p2.snake[0].x, p2.snake[0].y-1)); 
    }
	else if (p2.direction == 'S') { 
        p2.snake.insert(p2.snake.begin(), CharPosition(p2.snake[0].x, p2.snake[0].y+1)); 
    }

	// movimenta a cobrinha para nova coordenada
	move(p2.snake[0].y, p2.snake[0].x);

    // incrementa o corpo da cobrinha
	addch(p2.snakeBody); 

	refresh();
	return;
}

// movimentos da cobrinha 2
void snakeGame::MoveSnake2() {
	int KeyPressed = getchar();

    // verifica a tecla pressionada
	switch(KeyPressed)
	{
		case 'A':
			if (direction2 != 'r') 
			{ direction2 = 'l'; }  
			break;
		case 'D':
			if (direction2 != 'l')
			{ direction2 = 'r'; }
			break;
		case 'W':
			if (direction2 != 'd')
			{ direction2 = 'u'; }
			break;
		case 'S':
			if (direction2 != 'u')
			{ direction2 = 'd'; }
			break;
		case KEY_BACKSPACE:
			direction2 = 'q'; // "QUIT" para sair do jogo
			break;
	}

	// se a cobrinha nao comer a fruta, permanece com o mesmo tamanho
	if (!bEatsFruit2)
	{
		move(snake2[snake2.size()-1].y, snake2[snake2.size()-1].x); // fim da cauda
		printw(" "); // adicionando char vazio
		refresh();
		snake2.pop_back(); // remove o ultimo elemento do vetor
	}

	// conforme a cobrinha se movimenta, adicionamos um char extra no inicio do vetor 
	// inicializando coordenadas de acordo com a direcao
	if (direction2 == 'l') { 
        snake2.insert(snake2.begin(), CharPosition(snake2[0].x-1, snake2[0].y)); 
    } 
	else if (direction2 == 'r') { 
        snake2.insert(snake2.begin(), CharPosition(snake2[0].x+1, snake2[0].y)); 
    }
	else if (direction2 == 'u') { 
        snake2.insert(snake2.begin(), CharPosition(snake2[0].x, snake2[0].y-1)); 
    }
	else if (direction2 == 'd') { 
        snake2.insert(snake2.begin(), CharPosition(snake2[0].x, snake2[0].y+1)); 
    }

	// movimenta a cobrinha para nova coordenada
	move(snake2[0].y, snake2[0].x);

    // aumenta o corpo da cobrinha
	addch(snakeBody2); 

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

		std::thread firstFruit(&snakeGame::GetsFruit, this);
		std::thread secondFruit(&snakeGame::GetsFruit2, this);

		firstFruit.join();
		secondFruit.join();

		std::thread first(&snakeGame::MoveSnake, this);
		std::thread second(&snakeGame::MoveSnake2, this);

		first.join();
		second.join();

        if (direction == 'q') {        
        	break;
        }

		if (direction2 == 'q') {
        	break;
        }

        usleep(del); // delay
	}

}