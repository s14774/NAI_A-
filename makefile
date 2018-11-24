CC=g++

sdlA findTheWay: sdlA.cpp findTheWay.cpp
	$(CC) -o sdlA sdlA.cpp `sdl2-config --cflags --libs`
	$(CC) -o findTheWay findTheWay.cpp `sdl2-config --cflags --libs`