all:
	g++ main.cpp board.hpp snakeGame.hpp -lncurses -o main

run:
	@make -s all
	./main
	@make -s clear

clear:
	rm -f main