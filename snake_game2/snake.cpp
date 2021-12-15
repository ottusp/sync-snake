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

// definindo os dois jogadores
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

	p1.bEatsFruit = false;
	p2.bEatsFruit = false;

	p1.score = 0;
	p2.score = 0; 
	del = 110000;

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
void snakeGame::DrawSnake() {
	
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
		int tmpx = (rand() % maxwidth) + 1;
		int tmpy = (rand() % maxheight) + 1;

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
bool snakeGame::FatalCollision() {
	// Player1: se a cobrinha colidiu nos limites da tela
	if (p1.snake[0].x == 0 || p1.snake[0].x == maxwidth-1 || p1.snake[0].y == 0 || p1.snake[0].y == maxheight-2) {
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


// verifica se alguma cobrinha comeu a fruta
pair<bool,bool> snakeGame::GetsFruit() {
	pair<bool, bool> eatsFruit;

	// player1
	if (p1.snake[0].x == fruit.x && p1.snake[0].y == fruit.y) {
		PositionFruit(); 
		p1.score += 10; 
		PrintScore();

		p1.bEatsFruit = true;
	}

	else {
		p1.bEatsFruit = false;
	}


	// player2
	if (p2.snake[0].x == fruit.x && p2.snake[0].y == fruit.y) {
		PositionFruit(); 
		p2.score +=10; 
		PrintScore();

		p2.bEatsFruit = true;
	}

	else {
		p2.bEatsFruit = false;
	}

	eatsFruit = std::make_pair(p1.bEatsFruit, p2.bEatsFruit);
	
	return eatsFruit;
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
	}

	// Player1: se a cobrinha nao comer a fruta, permanece com o mesmo tamanho
	if (!p1.bEatsFruit)
	{
		move(p1.snake[p1.snake.size()-1].y, p1.snake[p1.snake.size()-1].x); // fim da cauda
		printw(" "); // adicionando char vazio
		refresh();
		p1.snake.pop_back(); // remove o ultimo elemento do vetor
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


	// Player2: se a cobrinha nao comer a fruta, permanece com o mesmo tamanho
	if (!p2.bEatsFruit)
	{
		move(p2.snake[p2.snake.size()-1].y, p2.snake[p2.snake.size()-1].x); // fim da cauda
		printw(" "); // adicionando char vazio
		refresh();
		p2.snake.pop_back(); // remove o ultimo elemento do vetor
	}


	// PLAYER2
	// conforme a cobrinha se movimenta, adicionamos um char extra no inicio do vetor 
	// inicializando coordenadas de acordo com a direcao
	if (toupper(p2.direction) == 'A' ) { 
        p2.snake.insert(p2.snake.begin(), CharPosition(p2.snake[0].x-1, p2.snake[0].y)); 
    } 
	else if (toupper(p2.direction) == 'D') { 
        p2.snake.insert(p2.snake.begin(), CharPosition(p2.snake[0].x+1, p2.snake[0].y)); 
    }
	else if (toupper(p2.direction) == 'W') { 
        p2.snake.insert(p2.snake.begin(), CharPosition(p2.snake[0].x, p2.snake[0].y-1)); 
    }
	else if (toupper(p2.direction) == 'S') { 
        p2.snake.insert(p2.snake.begin(), CharPosition(p2.snake[0].x, p2.snake[0].y+1)); 
    }

	// movimenta a cobrinha para nova coordenada
	move(p2.snake[0].y, p2.snake[0].x);

    // incrementa o corpo da cobrinha
	addch(p2.snakeBody); 

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

        if (p1.direction == 'q' || p2.direction == 'q') {
        	break;
        }

        usleep(del); // delay
    }
}