#include <iostream>

#include "SDL.h" // brew install sdl
#include "SDL_gfxPrimitives.h" // brew install sdl_gfx

SDL_Surface *screen;
SDL_Event event;

// Some drawing rects:
SDL_Rect rect;
int shape_size = 100;
int x = 0;
int y = 0;
int color = 0;

using namespace std;

int main(int argc, char* argv[]) {
	SDL_Init(SDL_INIT_VIDEO);
	screen = SDL_SetVideoMode(0, 0, 0, SDL_HWSURFACE);
	SDL_WM_SetCaption("Simple Window", "Simple Window");

	if (!screen) {
		cout << "Could not initialize SDL: " << SDL_GetError() << endl;
		return 0;
	}

	bool done = false;
	rect.w = shape_size;
	rect.h = shape_size;

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

		color +=10;
		if (color>=255) {
			color = 0;
		}

		SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, color, 0, 0));

		SDL_PumpEvents();
		if(SDL_GetMouseState(&x, &y)&SDL_BUTTON(1)) {
			// printf("Mouse Button 1(left) is pressed. X: %i, Y: %i\n", x, y);
			rect.x = x;
			rect.y = y;
			// rect = {0, 0, 100, 100}; // x, y, width, height
			SDL_FillRect(screen, &rect, SDL_MapRGB(screen->format, 255, 255, 255));
		}

		SDL_Flip(screen);

	}

	SDL_Quit();
	return 0;
}

