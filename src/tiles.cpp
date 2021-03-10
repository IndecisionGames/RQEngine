#include "Tile.h"

Tile::Tile(int x, int y, int tileType, Texture* texture) {
    mBox.x = x;
    mBox.y = y;
    mBox.w = TILE_WIDTH;
    mBox.h = TILE_HEIGHT;
    mType = tileType;
    mTexture = texture;
}

bool Tile::checkCollision(SDL_Rect other) {
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    leftA = mBox.x;
    rightA = mBox.x + mBox.w;
    topA = mBox.y;
    bottomA = mBox.y + mBox.h;

    leftB = other.x;
    rightB = other.x + other.w;
    topB = other.y;
    bottomB = other.y + other.h;

    if(bottomA <= topB) return false;
    if(topA >= bottomB) return false;
    if(rightA <= leftB) return false;
    if(leftA >= rightB) return false;

    return true;
}

void Tile::render(SDL_Renderer* renderer, SDL_Rect& camera, SDL_Rect tileClips[]) {
    if(checkCollision(camera)) {
        mTexture->render(renderer, mBox.x - camera.x, mBox.y - camera.y, &tileClips[mType]);
    }
}

int Tile::getType() {
    return mType;
}

SDL_Rect Tile::getBox() {
    return mBox;
}