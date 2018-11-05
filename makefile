CC=g++

sdlA: sdlA.cpp
	$(CC) -o sdlA sdlA.cpp `sdl2-config --cflags --libs`