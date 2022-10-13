RM = del
CC = gcc
CFLAGS = -g
EXE = test.exe
OBJS = mainCustom.o puzle.o

test: $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

mainCustom.o: mainCustom.c puzle.h
	$(CC) $(CFLAGS) -c $< 

puzle.o: puzle.c puzle.h
	$(CC) $(CFLAGS) -c $<

clean:
	$(RM) $(EXE) $(OBJS)
