#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <string>

class Texture {
    private:
        SDL_Texture* mTexture;
        int mWidth;
        int mHeight;

    public:
        Texture();
        ~Texture();
        bool loadFromFile(SDL_Renderer* renderer, std::string path, SDL_Color keyColor = {0, 255, 255});
        bool loadFromRenderedText(SDL_Renderer* renderer, TTF_Font* font, std::string textureText, SDL_Color textColor);
        void free();
        void render(SDL_Renderer* renderer, int x, int y, SDL_Rect* clip = NULL);
        int getWidth();
        int getHeight();
};