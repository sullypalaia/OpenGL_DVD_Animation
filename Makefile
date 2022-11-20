CC = g++
CFlags = -std=c++17 -fdiagnostics-color=always -Wall -g -I dependencies/include -L dependencies/library -Wno-deprecated
CFrameworks = -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo -framework CoreFoundation
PROG = app

default: src/*.cpp src/*.hpp dependencies/library/libglfw.3.3.dylib src/glad.c main_src/main.cpp
	mkdir exe
	$(CC) $(CFrameworks) $(CFlags) dependencies/library/libglfw.3.3.dylib src/glad.c src/*.cpp main_src/main.cpp -o exe/$(PROG)

clean:
	rm -rf exe

run:
	./exe/app