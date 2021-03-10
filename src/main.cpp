#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <sstream>

#include "Texture.h"
#include "Timer.h"
#include "Dot.h"
#include "Window.h"

const int LEVEL_WIDTH = 1920;
const int LEVEL_HEIGHT = 1080;

const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;
const int SCREEN_FPS = 60;
const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;

bool vsync = false;

Window gWindow;
SDL_Renderer* gRenderer = NULL;

Timer timer;

TTF_Font *gFont = NULL;

Texture gDotTexture;
Texture gTimeTexture;
Texture gRedTexture;
Texture gGreenTexture;
Texture gBlueTexture;
Texture gShimmerTexture;
std::vector<Texture*> particleTextures;

void init() {
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);
    TTF_Init();

    gWindow.init(SCREEN_WIDTH, SCREEN_HEIGHT);
    gRenderer = gWindow.createRenderer(vsync);
}

void loadTextures() {
    gFont = TTF_OpenFont("res/font/OstrichSans-Heavy.otf", 48);
    gDotTexture.loadFromFile(gRenderer, "res/dot.bmp", {255, 255, 255});
    gRedTexture.loadFromFile(gRenderer, "res/red.bmp");
    gGreenTexture.loadFromFile(gRenderer, "res/green.bmp");
    gBlueTexture.loadFromFile(gRenderer, "res/blue.bmp");
    gShimmerTexture.loadFromFile(gRenderer, "res/shimmer.bmp");

    gRedTexture.setAlpha(192);
    gGreenTexture.setAlpha(192);
    gBlueTexture.setAlpha(192);
    gShimmerTexture.setAlpha(192);

    particleTextures.push_back(&gRedTexture);
    particleTextures.push_back(&gGreenTexture);
    particleTextures.push_back(&gBlueTexture);
    particleTextures.push_back(&gShimmerTexture);
}

void close() {
    gTimeTexture.free();
    gDotTexture.free();
    gRedTexture.free();
    gGreenTexture.free();
    gBlueTexture.free();

    TTF_CloseFont(gFont);
    gFont = NULL;

    gWindow.free();
    gRenderer = NULL;

    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

int main( int argc, char* args[] ) {
    init();
    loadTextures();

    bool quit = false;
    SDL_Event e;

    Dot dot(particleTextures, 500, 500);
    dot.setTexture(&gDotTexture);

    SDL_Rect wall = {700, 400, 400, 600};

    SDL_Rect camera = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};

    SDL_Color textColor = {0, 255, 0};

    Timer fpsTimer;
    Timer capTimer;
    Uint32 lastFrameTime = 0;

    std::stringstream timeText;

    int countedFrames = 0;
    int lastRecordedFrames = 0;
    int FPS = 60;
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
            gWindow.handleEvent(e);
            dot.handleEvent(e);
        }

        dot.move(LEVEL_HEIGHT, LEVEL_WIDTH, wall);

        camera.x = dot.getPosX() - SCREEN_WIDTH / 2;
        camera.y = dot.getPosY() - SCREEN_HEIGHT / 2;

        if (camera.x < 0) camera.x = 0;
        if (camera.y < 0) camera.y = 0;
        if (camera.x > LEVEL_WIDTH - camera.w) camera.x = LEVEL_WIDTH - camera.w;
        if (camera.y > LEVEL_HEIGHT - camera.h) camera.y = LEVEL_HEIGHT - camera.h;

        if (fpsTimer.getTicks() - lastFrameTime >= 1000) {
            FPS = (countedFrames - lastRecordedFrames);
            
            lastRecordedFrames = countedFrames;
            lastFrameTime = fpsTimer.getTicks();
        }

        timeText.str("");
        timeText << FPS;

        gTimeTexture.loadFromRenderedText(gRenderer, gFont, timeText.str().c_str(), textColor);


        if(!gWindow.isMinimised()) {
            SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
            SDL_RenderClear(gRenderer);

            SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);

            SDL_Rect temp = {wall.x - camera.x, wall.y - camera.y, wall.w, wall.h};
            SDL_RenderDrawRect(gRenderer, &temp);

            dot.render(gRenderer, camera.x, camera.y);

            gTimeTexture.render(gRenderer, SCREEN_WIDTH - gTimeTexture.getWidth() * 3 / 2 + 10, 30 - gTimeTexture.getHeight() / 2);

            SDL_RenderPresent(gRenderer);
        }
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