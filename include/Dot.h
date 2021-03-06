#pragma once

#include <SDL2/SDL.h>
#include <stdio.h>

#include "Texture.h"

class Dot {
    private:
        int mPosX, mPosY;
        int mVelX, mVelY;
        Texture* mTexture;

    public:
        static const int DOT_WIDTH = 20;
        static const int DOT_HEIGHT = 20;
        static const int DOT_VEL = 10;
        Dot();
        void setTexture(Texture* texture);
        void handleEvent(SDL_Event& e);
        void move(int screenHeight, int screenWidth);
        void render(SDL_Renderer* renderer);
};