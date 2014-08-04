CXX = g++
CFLAGS=-c -Wall -g `sdl-config --cflags`
LDFLAGS = `sdl-config  --libs` -lGL -lGLU
LDFLAGSMAC = `sdl-config  --libs` -framework OpenGL
OUTPUT = sdl_window

all: ${OUTPUT}

${OUTPUT}: main.o
	$(CXX) main.o $(LDFLAGSMAC) -o ${OUTPUT}

main.o: main.cpp
	$(CXX) $(CFLAGS) $(IFLAGS) $(LDFLAGSMAC) main.cpp


clean:
	rm -rf *o ${OUTPUT}