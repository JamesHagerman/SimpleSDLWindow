#include "SDL.h"

#include <iostream>

SDL_Surface *screen;
SDL_Event event;

using namespace std;

int main(int argc, char* argv[]) {
	SDL_Init(SDL_INIT_VIDEO);
	screen = SDL_SetVideoMode(0, 0, 0, 0);
	SDL_WM_SetCaption("Simple Window", "Simple Window");

	if (!screen) {
		cout << "Could not initialize SDL: " << SDL_GetError() << endl;
		return 0;
	}

	bool done = false;
	while (!done) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				done = true;
			}

			switch (event.type) {
				case SDL_KEYDOWN:
					cout << "Keydown!" << endl;
					cout << "Quitting the app!" << endl;
					done = true;
				case SDL_KEYUP:
					cout << "Keyup!" << endl;
				// case SDL_QUIT:
				// 	done = true;
				default:
					break;
			}

		}
		if (screen != NULL) {
			SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 255, 0, 0));
			SDL_Flip(screen);
		} 
	}

	SDL_Quit();
	return 0;
}