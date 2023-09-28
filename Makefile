CC=gcc
CPPFLAGS= -DDEBUG 
CFLAGS= -std=c99 
LDFLAGS= `pkg-config --libs gtk+-3.0`
EXEC=hex
all: $(EXEC)

CFLAGS += `pkg-config --cflags gtk+-3.0`
LDFLAGS += `pkg-config --libs gtk+-3.0`

hex: Board.o Jeu.o IA.o Score.o interface.o network.o main.o 
	$(CC) -o $@ $^ $(LDFLAGS)
%.o: %.c
	$(CC) -c $(CPPFLAGS) $(CFLAGS) -o $@ $<


# Dependance 

Board.o: Board.c Board.h Constant.h 
Score.o: Score.c Score.h Constant.h
Jeu.o: Jeu.c Jeu.h
IA.o: IA.c IA.h Jeu.h Constant.h
network.o : network.c network.h
interface.o : interface.c interface.h IA.h Jeu.h network.h
main.o: main.c Jeu.h IA.h network.h

.PHONY: clean cleanall

clean:
	rm -f *.o
cleanall: 
	clean rm -f $(EXEC)