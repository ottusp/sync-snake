program = snake

all:
	g++ main.cpp -lncurses -o ${program}

run:
	@make -s all
	./${program}
	@make -s clear

clear:
	rm -f ${program}