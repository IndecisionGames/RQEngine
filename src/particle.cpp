#include "Particle.h"

Particle::Particle(int x, int y, std::vector<Texture*> particleTextures) {
    mPosX = x - 5 + (rand() % 25);
    mPosY = y - 5 + (rand() % 25);

    mFrame = rand() % 5;

    int index = rand() % 3;
    mTexture = particleTextures[index];
    mShimmerTexture = particleTextures[3];
}

void Particle::render(SDL_Renderer* renderer, int camX, int camY) {
    mTexture->render(renderer, mPosX - camX, mPosY - camY);

    if(mFrame % 5 == 0) {
        mShimmerTexture->render(renderer, mPosX - camX, mPosY - camY);
    }

    mFrame++;
}

bool Particle::isDead() {
    return mFrame > 10;
}