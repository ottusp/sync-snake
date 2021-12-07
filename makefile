all:
	g++ board.cpp main.cpp -o main

run:
	@make -s all
	./main
	@make -s clear

clear:
	rm -f main