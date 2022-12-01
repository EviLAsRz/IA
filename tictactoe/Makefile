CC = gcc 
CFLAGS = -g 
files = main.o minimaxAlum.o tictactoe.o

all: $(files)
	$(CC) $(CFLAGS) $(files) -o main -lm

main.o: minimaxAlum.o tictactoe.o
	gcc -c main.c

minimaxAlum.o: minimaxAlum.c minimaxAlum.h
	gcc -c minimaxAlum.c

tictactoe.o: tictactoe.c tictactoe.h
	gcc -c tictactoe.c

clean: 
	del $(files) *.exe
	
debug: 
	gdb ./main
