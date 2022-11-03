RM = del
CC = gcc
CFLAGS = -g
EXE = test.exe
OBJS = main.o 3puzle.o busqueda.o listaia.o

test: $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

main.o: main.c 3puzle.h listaia.h busqueda.h
	$(CC) $(CFLAGS) -c $< 
busqueda.o: busqueda.c busqueda.h listaia.h 3puzle.h
	$(CC) $(CFLAGS) -c $<

3puzle.o: 3puzle.c 3puzle.h
	$(CC) $(CFLAGS) -c $<

listaia.o: listaia.c listaia.h
	$(CC) $(CFLAGS) -c $<

clean:
	$(RM) $(EXE) $(OBJS)
