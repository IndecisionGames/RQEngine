#pragma once

#include <SDL2/SDL.h>

#include "Texture.h"

//Tile constants
const int TILE_WIDTH = 80;
const int TILE_HEIGHT = 80;
const int TOTAL_TILES = 192;
const int TOTAL_TILE_SPRITES = 12;

//The different tile sprites
const int TILE_RED = 0;
const int TILE_GREEN = 1;
const int TILE_BLUE = 2;
const int TILE_CENTER = 3;
const int TILE_TOP = 4;
const int TILE_TOPRIGHT = 5;
const int TILE_RIGHT = 6;
const int TILE_BOTTOMRIGHT = 7;
const int TILE_BOTTOM = 8;
const int TILE_BOTTOMLEFT = 9;
const int TILE_LEFT = 10;
const int TILE_TOPLEFT = 11;

class Tile {
    private:
        SDL_Rect mBox;
        int mType;
        Texture* mTexture;
    
    public:
        Tile(int x, int y, int tileType, Texture* texture);
        void render(SDL_Renderer* renderer, SDL_Rect& camera, SDL_Rect tileClips[]);
        int getType();
        SDL_Rect getBox();
        bool checkCollision(SDL_Rect other);
};
