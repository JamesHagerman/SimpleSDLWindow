CXX = g++
CFLAGS=-c -Wall -g
IFLAGS = -I/usr/include/SDL -D_GNU_SOURCE=1 -D_REENTRANT
LDFLAGS = -L/usr/lib/x86_64-linux-gnu -lSDL
OUTPUT = sdl_window

all: ${OUTPUT}

${OUTPUT}: main.o
	$(CXX) main.o $(LDFLAGS) -o ${OUTPUT}

main.o: main.cpp
	$(CXX) $(CFLAGS) $(IFLAGS) $(LDFLAGS) main.cpp


clean:
	rm -rf *o ${OUTPUT}