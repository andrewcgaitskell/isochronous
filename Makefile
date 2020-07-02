all:
	gcc -o program program.c -lusb-1.0
	./program
