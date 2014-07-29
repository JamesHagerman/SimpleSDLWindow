CXX = g++
CFLAGS=-c -Wall -g `sdl-config --cflags`
LDFLAGS = `sdl-config  --libs`
OUTPUT = sdl_window

all: ${OUTPUT}

${OUTPUT}: main.o
	$(CXX) main.o $(LDFLAGS) -o ${OUTPUT}

main.o: main.cpp
	$(CXX) $(CFLAGS) $(IFLAGS) $(LDFLAGS) main.cpp


clean:
	rm -rf *o ${OUTPUT}