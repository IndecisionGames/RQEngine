#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

SDL_Window* gWindow = NULL;
SDL_Surface* gScreenSurface = NULL;
SDL_Surface* gWall = NULL;

// This file is a playground for now while I follow https://lazyfoo.net/tutorials/SDL/index.php

bool init() {
	// Initialise SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		return false;
	}
	else {
		// Create Window
		gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL) {
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			return false;
		}
		else {
			// Initialise PNG loading
			int imgFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imgFlags) == imgFlags)) {
				printf("SDL_image could not initialise! SDL_image Error: %s\n", IMG_GetError());
			} else {
				// Get window surface
				gScreenSurface = SDL_GetWindowSurface(gWindow);
			}
		}
	}

	return true;
}

SDL_Surface* loadSurface(std::string path) {
	SDL_Surface* optimisedSurface = NULL;

	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL) {
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	} else {
		optimisedSurface = SDL_ConvertSurface(loadedSurface, gScreenSurface->format, 0);
		if (optimisedSurface == NULL) {
			printf("Unable to optimize image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}

		SDL_FreeSurface(loadedSurface);
	}
	return optimisedSurface;
}

bool loadMedia() {
	// Load wall image
	gWall = loadSurface("res/wall128x128.bmp");
	if (gWall == NULL) {
		return false;
	}
	return true;
}

void close() {
	// Deallocate surface
	SDL_FreeSurface(gWall);
	gWall = NULL;

	// Destroy window
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	// Quit SDL subsystems
	SDL_Quit();
}


int main( int argc, char* args[] )
{
	if (!init()) {
		printf("Failed to initialise!\n");
		close();
		return 1;
	}
	if (!loadMedia()) {
		printf("Failed to load media!\n");
		close();
		return 1;
	}
	
	bool quit = false;

	SDL_Event e;

	// Game loop
	while (!quit) {

		// Handle events
		while (SDL_PollEvent(&e) != 0) {

			if (e.type == SDL_QUIT || (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)) quit = true;

			if (e.type == SDL_MOUSEBUTTONDOWN) {
				switch(e.button.button) {
					case 1:
						printf("Left Mouse\n");
						break;
					case 3:
						printf("Right Mouse\n");
						break;
				}
			}

			if (e.type == SDL_KEYDOWN) {
				switch(e.key.keysym.sym) {
					case SDLK_w:
						printf("W\n");
						break;
					case SDLK_a:
						printf("A\n");
						break;
					case SDLK_s:
						printf("S\n");
						break;
					case SDLK_d:
						printf("D\n");
						break;
				}
			}
		}

		// Stretched Image =====
		SDL_Rect stretchRect;
		stretchRect.x = 0;
		stretchRect.y = 0;
		stretchRect.w = SCREEN_WIDTH;
		stretchRect.h = SCREEN_HEIGHT;
		SDL_BlitScaled( gWall, NULL, gScreenSurface, &stretchRect );
		// =====================

		// SDL_BlitSurface(gWall, NULL, gScreenSurface, NULL);
		SDL_UpdateWindowSurface(gWindow);

	}


	close();

	return 0;
}