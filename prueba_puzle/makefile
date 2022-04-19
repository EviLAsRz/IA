RM = del			#variable limpiar
CC = gcc			#compilador
CFLAGS = -g   #flags del compilador: WALL-> advertencias del compilador -G: genera información del debugger
EXE = main.exe      #ejecutable/s
OBJS = main.o puzle.o	#objetos

main: $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

main.o: main.c puzle.h
	$(CC) $(CFLAGS) -c $< 

clean:
	$(RM) $(EXE) $(OBJS)