#include "SDL.h"

SDL_Surface *screen;
SDL_Event event;

int main(int argc, char* argv[]) {
	SDL_Init(SDL_INIT_VIDEO);
	screen = SDL_SetVideoMode(640, 480, 16, SDL_HWSURFACE);
	SDL_WM_SetCaption("Simple Window", "Simple Window");

	bool done = false;
	while(!done) {
		while(SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				done = true;
			}
		}

		SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 0, 0, 0));
		SDL_Flip(screen);
	}

	SDL_Quit();
	return 0;
}

