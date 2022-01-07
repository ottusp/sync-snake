program = snake

all:
	g++ main.cpp -lncurses -pthread -o ${program}

run:
	@make -s all
	./${program}
	@make -s clear

clear:
	rm -f ${program}

valgrind:
	valgrind ./${program}