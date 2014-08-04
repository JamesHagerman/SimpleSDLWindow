MACHINE= $(shell uname -s)

ifeq ($(MACHINE),Darwin)
    OPENGL_INC= -FOpenGL
    OPENGL_LIB= -framework OpenGL
    SDL_INC= `sdl-config --cflags`
    SDL_LIB= `sdl-config --libs`
else
    OPENGL_INC= -I/usr/X11R6/include
    OPENGL_LIB= -I/usr/lib64 -lGL -lGLU
    SDL_INC= `sdl-config --cflags`
    SDL_LIB= `sdl-config --libs`
endif

CXX = g++
CFLAGS = -Wall -g
LDFLAGS = $(SDL_LIB) $(OPENGL_LIB)
IFLAGS = $(SDL_INC) $(OPENGL_INC)

OUTPUT = sdl_window
OBJS = main.o

all: ${OUTPUT}

${OUTPUT}: $(OBJS)
	$(CXX) $(OBJS) $(LDFLAGS) -o ${OUTPUT}

%.o: %.cpp
	$(CXX) -c $(CFLAGS) $(IFLAGS) -o $@ $<


clean:
	rm -rf *o ${OUTPUT}