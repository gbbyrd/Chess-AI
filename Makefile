all:
	g++ -Iinclude -Iinclude/sdl2 -Iinclude/headers -Llib -o Main src/*.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -g