RM = del
CC = gcc
CFLAGS = -g
EXE = test.exe
OBJS = main.o puzle.o busqueda.o listaia.o

test: $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

main.o: main.c puzle.h listaia.h busqueda.h
	$(CC) $(CFLAGS) -c $< 
busqueda.o: busqueda.c busqueda.h listaia.h puzle.h
	$(CC) $(CFLAGS) -c $<

puzle.o: puzle.c puzle.h
	$(CC) $(CFLAGS) -c $<

listaia.o: listaia.c listaia.h
	$(CC) $(CFLAGS) -c $<

clean:
	$(RM) $(EXE) $(OBJS)
