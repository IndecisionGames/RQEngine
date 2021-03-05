#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>

#include "Texture.h"

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;

Texture gWallTexture;
Texture gSpriteSheetTexture;
SDL_Rect gSpriteClips[4];

void init() {
	SDL_Init(SDL_INIT_VIDEO);
	IMG_Init(IMG_INIT_PNG);

	gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
}

void loadTextures() {
	gWallTexture.loadFromFile(gRenderer, "res/wall128x128.png");
	gSpriteSheetTexture.loadFromFile(gRenderer, "res/sprites_sheet.png");
	
	//Set top left sprite
    gSpriteClips[ 0 ].x =   0;
    gSpriteClips[ 0 ].y =   0;
    gSpriteClips[ 0 ].w = 100;
    gSpriteClips[ 0 ].h = 100;

    //Set top right sprite
    gSpriteClips[ 1 ].x = 100;
    gSpriteClips[ 1 ].y =   0;
    gSpriteClips[ 1 ].w = 100;
    gSpriteClips[ 1 ].h = 100;
        
    //Set bottom left sprite
    gSpriteClips[ 2 ].x =   0;
    gSpriteClips[ 2 ].y = 100;
    gSpriteClips[ 2 ].w = 100;
    gSpriteClips[ 2 ].h = 100;

    //Set bottom right sprite
    gSpriteClips[ 3 ].x = 100;
    gSpriteClips[ 3 ].y = 100;
    gSpriteClips[ 3 ].w = 100;
    gSpriteClips[ 3 ].h = 100;
}

void close() {
	gWallTexture.free();

	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gRenderer = NULL;
	gWindow = NULL;

	IMG_Quit();
	SDL_Quit();
}


int main( int argc, char* args[] ) {
	init();
	loadTextures();
	
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

		SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
		SDL_RenderClear(gRenderer);

		for(int i = 0; i < SCREEN_WIDTH; i += gWallTexture.getWidth()) {
			for(int j = 0; j < SCREEN_HEIGHT; j += gWallTexture.getHeight()) {
				gWallTexture.render(gRenderer, i, j);
			}
		}

		 //Render top left sprite
        gSpriteSheetTexture.render(gRenderer, 0, 0, &gSpriteClips[ 0 ] );

         //Render top right sprite
        gSpriteSheetTexture.render(gRenderer, SCREEN_WIDTH - gSpriteClips[ 1 ].w, 0, &gSpriteClips[ 1 ] );

        //Render bottom left sprite
        gSpriteSheetTexture.render(gRenderer, 0, SCREEN_HEIGHT - gSpriteClips[ 2 ].h, &gSpriteClips[ 2 ] );

        //Render bottom right sprite
        gSpriteSheetTexture.render(gRenderer, SCREEN_WIDTH - gSpriteClips[ 3 ].w, SCREEN_HEIGHT - gSpriteClips[ 3 ].h, &gSpriteClips[ 3 ] );
		

		// Draw some geometry
		SDL_Rect fillRect = {SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2};
		SDL_SetRenderDrawColor(gRenderer, 255, 0, 0, 255);
		SDL_RenderFillRect(gRenderer, &fillRect);

		SDL_Rect outlineRect = {SCREEN_WIDTH / 6, SCREEN_HEIGHT / 6, SCREEN_WIDTH * 2 / 3, SCREEN_HEIGHT * 2 / 3};
		SDL_SetRenderDrawColor(gRenderer, 0, 255, 0, 255);
		SDL_RenderDrawRect(gRenderer, &outlineRect);

		SDL_SetRenderDrawColor(gRenderer, 0, 0, 255, 255);
		SDL_RenderDrawLine(gRenderer, 0, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT / 2);

		SDL_SetRenderDrawColor(gRenderer, 255, 255, 0, 255);
		for (int i = 0; i < SCREEN_HEIGHT; i += 4) {
			SDL_RenderDrawPoint(gRenderer, SCREEN_WIDTH / 2, i);
		}

		SDL_RenderPresent(gRenderer);
	}

	close();

	return 0;
}