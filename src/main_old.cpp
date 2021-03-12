// #include <SDL2/SDL.h>
// #include <SDL2/SDL_image.h>
// #include <SDL2/SDL_ttf.h>
// #include <stdio.h>
// #include <string>
// #include <sstream>
// #include <fstream>

// #include "Texture.h"
// #include "Timer.h"
// #include "Dot.h"
// #include "Window.h"

// const int LEVEL_WIDTH = 1280;
// const int LEVEL_HEIGHT = 960;

// const int SCREEN_WIDTH = 640;
// const int SCREEN_HEIGHT = 480;
// const int SCREEN_FPS = 60;
// const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;

// bool vsync = false;

// Window gWindow;
// SDL_Renderer* gRenderer = NULL;

// Timer timer;

// TTF_Font *gFont = NULL;

// SDL_Rect gTileClips[TOTAL_TILE_SPRITES];
// Texture gDotTexture;
// Texture gTimeTexture;
// Texture gRedTexture;
// Texture gGreenTexture;
// Texture gBlueTexture;
// Texture gShimmerTexture;
// Texture gTileTexture;
// std::vector<Texture*> particleTextures;

// void init() {
//     SDL_Init(SDL_INIT_VIDEO);
//     IMG_Init(IMG_INIT_PNG);
//     TTF_Init();

//     gWindow.init(SCREEN_WIDTH, SCREEN_HEIGHT);
//     gRenderer = gWindow.createRenderer(vsync);
// }

// bool setTiles(Tile* tiles[]) {
//     bool tilesLoaded = true;

//     int x = 0, y = 0;

//     std::ifstream map("res/level.map");

//     if(map.fail()) {
//         tilesLoaded = false;
//     } else {
//         for (int i = 0; i < TOTAL_TILES; ++i) {
//             int tileType = -1;
//             map >> tileType;

//             if(map.fail()) {
//                 //Stop loading map
//                 printf( "Error loading map: Unexpected end of file!\n" );
//                 tilesLoaded = false;
//                 break;
//             }

//             //If the number is a valid tile number
//             if ((tileType >= 0) && (tileType < TOTAL_TILE_SPRITES)) {
//                 tiles[i] = new Tile(x, y, tileType, &gTileTexture);
//             }
//             //If we don't recognize the tile type
//             else {
//                 //Stop loading map
//                 printf( "Error loading map: Invalid tile type at %d!\n", i );
//                 tilesLoaded = false;
//                 break;
//             }

//             x += TILE_WIDTH;

//             if (x >= LEVEL_WIDTH) {
//                 x = 0;
//                 y += TILE_HEIGHT;
//             }
//         }
//         if( tilesLoaded ) {
//             gTileClips[ TILE_RED ].x = 0;
//             gTileClips[ TILE_RED ].y = 0;
//             gTileClips[ TILE_RED ].w = TILE_WIDTH;
//             gTileClips[ TILE_RED ].h = TILE_HEIGHT;

//             gTileClips[ TILE_GREEN ].x = 0;
//             gTileClips[ TILE_GREEN ].y = 80;
//             gTileClips[ TILE_GREEN ].w = TILE_WIDTH;
//             gTileClips[ TILE_GREEN ].h = TILE_HEIGHT;

//             gTileClips[ TILE_BLUE ].x = 0;
//             gTileClips[ TILE_BLUE ].y = 160;
//             gTileClips[ TILE_BLUE ].w = TILE_WIDTH;
//             gTileClips[ TILE_BLUE ].h = TILE_HEIGHT;

//             gTileClips[ TILE_TOPLEFT ].x = 80;
//             gTileClips[ TILE_TOPLEFT ].y = 0;
//             gTileClips[ TILE_TOPLEFT ].w = TILE_WIDTH;
//             gTileClips[ TILE_TOPLEFT ].h = TILE_HEIGHT;

//             gTileClips[ TILE_LEFT ].x = 80;
//             gTileClips[ TILE_LEFT ].y = 80;
//             gTileClips[ TILE_LEFT ].w = TILE_WIDTH;
//             gTileClips[ TILE_LEFT ].h = TILE_HEIGHT;

//             gTileClips[ TILE_BOTTOMLEFT ].x = 80;
//             gTileClips[ TILE_BOTTOMLEFT ].y = 160;
//             gTileClips[ TILE_BOTTOMLEFT ].w = TILE_WIDTH;
//             gTileClips[ TILE_BOTTOMLEFT ].h = TILE_HEIGHT;

//             gTileClips[ TILE_TOP ].x = 160;
//             gTileClips[ TILE_TOP ].y = 0;
//             gTileClips[ TILE_TOP ].w = TILE_WIDTH;
//             gTileClips[ TILE_TOP ].h = TILE_HEIGHT;

//             gTileClips[ TILE_CENTER ].x = 160;
//             gTileClips[ TILE_CENTER ].y = 80;
//             gTileClips[ TILE_CENTER ].w = TILE_WIDTH;
//             gTileClips[ TILE_CENTER ].h = TILE_HEIGHT;

//             gTileClips[ TILE_BOTTOM ].x = 160;
//             gTileClips[ TILE_BOTTOM ].y = 160;
//             gTileClips[ TILE_BOTTOM ].w = TILE_WIDTH;
//             gTileClips[ TILE_BOTTOM ].h = TILE_HEIGHT;

//             gTileClips[ TILE_TOPRIGHT ].x = 240;
//             gTileClips[ TILE_TOPRIGHT ].y = 0;
//             gTileClips[ TILE_TOPRIGHT ].w = TILE_WIDTH;
//             gTileClips[ TILE_TOPRIGHT ].h = TILE_HEIGHT;

//             gTileClips[ TILE_RIGHT ].x = 240;
//             gTileClips[ TILE_RIGHT ].y = 80;
//             gTileClips[ TILE_RIGHT ].w = TILE_WIDTH;
//             gTileClips[ TILE_RIGHT ].h = TILE_HEIGHT;

//             gTileClips[ TILE_BOTTOMRIGHT ].x = 240;
//             gTileClips[ TILE_BOTTOMRIGHT ].y = 160;
//             gTileClips[ TILE_BOTTOMRIGHT ].w = TILE_WIDTH;
//             gTileClips[ TILE_BOTTOMRIGHT ].h = TILE_HEIGHT;
//         }
//     }

//     map.close();
//     return tilesLoaded;
// }

// void loadTextures(Tile* tiles[]) {
//     gFont = TTF_OpenFont("res/font/OstrichSans-Heavy.otf", 48);
//     gDotTexture.loadFromFile(gRenderer, "res/dot.bmp", {255, 255, 255});
//     gRedTexture.loadFromFile(gRenderer, "res/red.bmp");
//     gGreenTexture.loadFromFile(gRenderer, "res/green.bmp");
//     gBlueTexture.loadFromFile(gRenderer, "res/blue.bmp");
//     gShimmerTexture.loadFromFile(gRenderer, "res/shimmer.bmp");
//     gTileTexture.loadFromFile(gRenderer, "res/tiles.png");

//     gRedTexture.setAlpha(192);
//     gGreenTexture.setAlpha(192);
//     gBlueTexture.setAlpha(192);
//     gShimmerTexture.setAlpha(192);

//     particleTextures.push_back(&gRedTexture);
//     particleTextures.push_back(&gGreenTexture);
//     particleTextures.push_back(&gBlueTexture);
//     particleTextures.push_back(&gShimmerTexture);

//     setTiles(tiles);
// }

// void close(Tile* tiles[]) {
//     for (int i = 0; i < TOTAL_TILES; ++i) {
//         delete tiles[i];
//     }

//     gTimeTexture.free();
//     gDotTexture.free();
//     gRedTexture.free();
//     gGreenTexture.free();
//     gBlueTexture.free();
//     gTileTexture.free();

//     TTF_CloseFont(gFont);
//     gFont = NULL;

//     gWindow.free();
//     gRenderer = NULL;

//     TTF_Quit();
//     IMG_Quit();
//     SDL_Quit();
// }

// int notmain( int argc, char* args[] ) {
//     init();

//     Tile* tileSet[TOTAL_TILES];
//     loadTextures(tileSet);

//     bool quit = false;
//     SDL_Event e;

//     Dot dot(particleTextures, 50, 50);
//     dot.setTexture(&gDotTexture);

//     SDL_Rect camera = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};

//     SDL_Color textColor = {0, 255, 0};

//     Timer deltaTimer;
//     Timer fpsTimer;
//     Timer capTimer;
//     Uint32 lastFrameTime = 0;

//     std::stringstream timeText;

//     int countedFrames = 0;
//     int lastRecordedFrames = 0;
//     int FPS = 60;
//     fpsTimer.start();

//     // Game loop
//     while (!quit) {
//         capTimer.start();

//         // Handle events
//         while (SDL_PollEvent(&e) != 0) {

//             if (e.type == SDL_QUIT || (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)) quit = true;

//             gWindow.handleEvent(e);
//             dot.handleEvent(e);
//         }

//         float deltaTime = deltaTimer.getTicks() / 1000.f;

//         dot.move(deltaTime, LEVEL_HEIGHT, LEVEL_WIDTH, tileSet);
//         dot.setCamera(camera, LEVEL_HEIGHT, LEVEL_WIDTH);

//         if (fpsTimer.getTicks() - lastFrameTime >= 1000) {
//             FPS = (countedFrames - lastRecordedFrames);
            
//             lastRecordedFrames = countedFrames;
//             lastFrameTime = fpsTimer.getTicks();
//         }

//         timeText.str("");
//         timeText << FPS;

//         gTimeTexture.loadFromRenderedText(gRenderer, gFont, timeText.str().c_str(), textColor);

//         deltaTimer.start();
//         if(!gWindow.isMinimised()) {
//             SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
//             SDL_RenderClear(gRenderer);

//             SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);

//             for (int i = 0; i < TOTAL_TILES; ++i) {
//                 tileSet[i]->render(gRenderer, camera, gTileClips);
//             }

//             dot.render(gRenderer, camera);

//             gTimeTexture.render(gRenderer, SCREEN_WIDTH - gTimeTexture.getWidth() * 3 / 2 + 10, 30 - gTimeTexture.getHeight() / 2);

//             SDL_RenderPresent(gRenderer);
//         }
//         ++countedFrames;

//         if (!vsync) {
//             int frameTicks = capTimer.getTicks();
//             if (frameTicks < SCREEN_TICKS_PER_FRAME) {
//                 SDL_Delay(SCREEN_TICKS_PER_FRAME - frameTicks);
//             }
//         }
//     }

//     close(tileSet);

//     return 0;
// }