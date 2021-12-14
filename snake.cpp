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
	snakeBody2 = 'u';

	edgechar = (char)219;
	fruitchar = '@'; 

	fruit.x = 0; 
	fruit.y = 0; 

	score = 0;
	score2 = 0;

	del = 110000;

	bool bEatsFruit = 0;
	bool bEatsFruit2 = 0;

	direction = 'l';
	direction2 = 'r';

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
	// cobra 1
	for (int i = 0; i < 5; i++) {
		snake.push_back(CharPosition(30+i, 10));
	}

	for (int i = 0; i < snake.size(); i++) {
		move(snake[i].y, snake[i].x);
		addch(snakeBody);
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

// pontuacao
void snakeGame::PrintScore() {
	move(maxheight-1, 0);

	printw("Score: %d |", score);
	printw("Score Snake 2: %d", score2);

	return;
}

// posiciona a frutinha na tela
void snakeGame::PositionFruit() {
	while(1) {
		int tmpx = rand()%maxwidth+1;
		int tmpy = rand()%maxheight+1;

		// verifica se a posicao da fruta nao e a mesma das cobras
		for (int i = 0; i < snake.size(); i++) {
			if (snake[i].x == tmpx && snake[i].y == tmpy) {
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
bool snakeGame::FatalCollision() {
	// se a cobrinha colidiu com a borda
	if (snake[0].x == 0 || snake[0].x == maxwidth-1 || snake[0].y == 0 || snake[0].y == maxheight-2) {
		return true;
	}

	if (snake2[0].x == 0 || snake2[0].x == maxwidth-1 || snake2[0].y == 0 || snake2[0].y == maxheight-2) {
		return true;
	}

	// se a cobrinha colidiu nela mesma
	/*for (int i = 2; i < snake.size(); i++) {
		if (snake[0].x == snake[i].x && snake[0].y == snake[i].y) {
			return true;
		}
	}

	for (int i = 2; i < snake2.size(); i++) {
		if (snake2[0].x == snake2[i].x && snake2[0].y == snake2[i].y) {
			return true;
		}
	}*/

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
			break;
		default: break;
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

    // aumenta o corpo da cobrinha
	addch(snakeBody); 

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