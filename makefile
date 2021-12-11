all:
	g++ main.cpp -lncurses -o main

run:
	@make -s all
	./main
	@make -s clear

clear:
	rm -f main