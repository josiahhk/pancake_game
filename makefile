CC = g++-8.2.0
CFLAGS = -std=c++11 -lfltk -lfltk_images -lX11 -ljpeg -static-libstdc++

all:  Game
	
Game:  Game.o Simple_window.o Graph.o Window.o GUI.o AI.o GameStats.o
	$(CC) $(CFLAGS) -o Game Game.o Simple_window.o Graph.o Window.o GUI.o AI.o GameStats.o

Game.o:  Game.cpp Simple_window.h Graph.h Window.h GUI.h AI.h GameStats.h
	$(CC) $(CFLAGS) -c Game.cpp

Simple_window.o:  Simple_window.cpp Simple_window.h 
	$(CC) $(CFLAGS) -c Simple_window.cpp

Graph.o:  Graph.cpp Graph.h 
	$(CC) $(CFLAGS) -c Graph.cpp

Window.o:  Window.cpp Window.h 
	$(CC) $(CFLAGS) -c Window.cpp

GUI.o:  GUI.cpp GUI.h 
	$(CC) $(CFLAGS) -c GUI.cpp
	
AI.o: AI.cpp AI.h
	$(CC) $(CFLAGS) -c AI.cpp
	
GameStats.o: GameStats.cpp GameStats.h
	$(CC) $(CFLAGS) -c GameStats.cpp

# To start over from scratch, type 'make clean'.  This
# removes the executable file, as well as old .o object
# files and *~ backup files:
#
#clean: 
#	$(RM) count *.o *~