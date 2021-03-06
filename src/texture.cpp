#include "Texture.h"

Texture::Texture() {
    mTexture = NULL;
    mWidth = 0;
    mHeight = 0;
}

Texture::~Texture() {
    free();
}

bool Texture::loadFromFile(SDL_Renderer* renderer, std::string path) {
    free();
    SDL_Texture* newTexture = NULL;
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());

    //Color key image (remove cyan background)
    SDL_SetColorKey(loadedSurface, 1, SDL_MapRGB(loadedSurface->format, 0, 255, 255));
    newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);

    mWidth = loadedSurface->w;
    mHeight = loadedSurface->h;
    SDL_FreeSurface(loadedSurface);

    mTexture = newTexture;
    return mTexture != NULL;
}

bool Texture::loadFromRenderedText(SDL_Renderer* renderer, TTF_Font* font, std::string textureText, SDL_Color textColor) {
    free();
    SDL_Texture* newTexture = NULL;
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, textureText.c_str(), textColor);

    newTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

    mWidth = textSurface->w;
    mHeight = textSurface->h;
    SDL_FreeSurface(textSurface);

    mTexture = newTexture;
    return mTexture != NULL;
}

void Texture::free() {
    if(mTexture != NULL) {
        SDL_DestroyTexture(mTexture);
        mTexture = NULL;
        mWidth = 0;
        mHeight = 0;
    }
}

void Texture::render(SDL_Renderer* renderer, int x, int y, SDL_Rect* clip) {
    SDL_Rect renderQuad = {x, y, mWidth, mHeight};
    if (clip != NULL) {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }
    SDL_RenderCopy(renderer, mTexture, clip, &renderQuad);
}

int Texture::getWidth() {
    return mWidth;
}

int Texture::getHeight() {
    return mHeight;
}