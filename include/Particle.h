#pragma once

#include <vector>

#include "Texture.h"

const int TOTAL_PARTICLES = 20;

class Particle {
    private:
        int mPosX, mPosY;
        int mFrame;
        Texture* mTexture;
        Texture* mShimmerTexture;

    public:
        Particle(int x, int y, std::vector<Texture*> particleTextures);
        void render(SDL_Renderer* renderer, int camX, int camY);
        bool isDead();
};