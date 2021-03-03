#include <SDL2/SDL.h>
#include <stdio.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Window* gWindow = NULL;
SDL_Surface* gScreenSurface = NULL;
SDL_Surface* gWall = NULL;

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
			// Get window surface
			gScreenSurface = SDL_GetWindowSurface(gWindow);
		}
	}

	return true;
}

bool loadMedia() {
	// Load wall image
	gWall = SDL_LoadBMP("res/wall128x128.bmp");
	if (gWall == NULL) {
		printf("Unable to load image %s! SDL Error: %s\n", "res/wall128x128.bmp", SDL_GetError());
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
	}
	else {
		SDL_BlitSurface(gWall, NULL, gScreenSurface, NULL);
		SDL_UpdateWindowSurface(gWindow);
		SDL_Delay(2000);
	}

	close();

	return 0;
}