LIBRARY = -lsfml-graphics -lsfml-window -lsfml-system
CFLAGS = -Wall -g -std=c++11
CC = g++
EXE = pong
SOURCE:= $(wildcard src/*.cc)
INCLUDE:= -Iinclude/

all:$(EXE)

$(EXE):
	$(CC) $(CFLAGS) $(INCLUDE) $(SOURCE) $(LIBRARY) -o $@

clean:
	$(RM) $(EXE)
