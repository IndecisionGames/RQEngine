#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <sstream>

#include "Texture.h"
#include "Timer.h"

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;
const int SCREEN_FPS = 60;
const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;

bool vsync = false;

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;

Timer timer;

TTF_Font *gFont = NULL;

Texture gTimeTexture;
Texture gWallTexture;
Texture gSpriteSheetTexture;
SDL_Rect gSpriteClips[4];

void init() {
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);
    TTF_Init();

    gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if (vsync) {
        gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    } else {
        gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
    }
    
}

void loadTextures() {
    gFont = TTF_OpenFont("res/font/OstrichSans-Heavy.otf", 48);

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
    gSpriteSheetTexture.free();
    gTimeTexture.free();

    TTF_CloseFont(gFont);
    gFont = NULL;

    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gRenderer = NULL;
    gWindow = NULL;

    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}


int main( int argc, char* args[] ) {
    init();
    loadTextures();
    
    bool quit = false;
    SDL_Event e;

    SDL_Color textColor = {0, 0, 0};

    Timer fpsTimer;
    Timer capTimer;

    std::stringstream timeText;

    int countedFrames = 0;
    fpsTimer.start();

    // Game loop
    while (!quit) {
        capTimer.start();

        // Handle events
        while (SDL_PollEvent(&e) != 0) {

            if (e.type == SDL_QUIT || (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)) quit = true;

            if (e.type == SDL_MOUSEBUTTONDOWN) {
                switch(e.button.button) {
                    case 1:
                        printf("Left Mouse\n");
                        break;
                    case 3:
                        if(!timer.isStarted()) {
                            printf("Starting timer\n");
                            timer.start();
                        } else {
                            Uint32 time = timer.getTicks();
                            printf("Time: %ums\n", time);
                            timer.stop();
                        }
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

        // Calculate and cap fps
        float avgFPS = countedFrames / (fpsTimer.getTicks() / 1000.f);
        if (avgFPS > 2000000) avgFPS = 0;

        timeText.str("");
        timeText << "FPS " << avgFPS;
        gTimeTexture.loadFromRenderedText(gRenderer, gFont, timeText.str().c_str(), textColor);

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

        gTimeTexture.render(gRenderer, (SCREEN_WIDTH - gTimeTexture.getWidth()) / 2, (SCREEN_HEIGHT - gTimeTexture.getHeight()) / 2);

        SDL_RenderPresent(gRenderer);
        ++countedFrames;

        if (!vsync) {
            int frameTicks = capTimer.getTicks();
            if (frameTicks < SCREEN_TICKS_PER_FRAME) {
                SDL_Delay(SCREEN_TICKS_PER_FRAME - frameTicks);
            }
        }
    }

    close();

    return 0;
}