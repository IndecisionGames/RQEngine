#include "Dot.h"

Dot::Dot(int posX, int posY, int velX, int velY) {
    mPosX = posX;
    mPosY = posY;
    mVelX = velX;
    mVelY = velY;
    mTexture = NULL;
}

void Dot::setTexture(Texture* texture) {
    mTexture = texture;
}

void Dot::handleEvent(SDL_Event& e) {
    if(e.type == SDL_KEYDOWN && e.key.repeat == 0) {
        switch(e.key.keysym.sym) {
            case SDLK_w: mVelY -= DOT_VEL; break;
            case SDLK_s: mVelY += DOT_VEL; break;
            case SDLK_a: mVelX -= DOT_VEL; break;
            case SDLK_d: mVelX += DOT_VEL; break;
        }
    } else if(e.type == SDL_KEYUP && e.key.repeat == 0) {
        switch(e.key.keysym.sym) {
            case SDLK_w: mVelY += DOT_VEL; break;
            case SDLK_s: mVelY -= DOT_VEL; break;
            case SDLK_a: mVelX += DOT_VEL; break;
            case SDLK_d: mVelX -= DOT_VEL; break;
        }
    }
}

void Dot::move(int screenHeight, int screenWidth) {
    mPosX += mVelX;
    if ((mPosX < 0) || (mPosX + DOT_WIDTH > screenWidth)) mPosX -= mVelX;
    mPosY += mVelY;
    if ((mPosY < 0) || (mPosY + DOT_HEIGHT > screenHeight)) mPosY -= mVelY;
}

void Dot::autoMove(int screenHeight, int screenWidth) {
    mPosX += mVelX;
    if ((mPosX < 0) || (mPosX + DOT_WIDTH > screenWidth)) {
        mPosX -= mVelX;
        mVelX = -mVelX;
    }
    mPosY += mVelY;
    if ((mPosY < 0) || (mPosY + DOT_HEIGHT > screenHeight)) { 
        mPosY -= mVelY;
        mVelY = -mVelY;
    }
}

void Dot::render(SDL_Renderer* renderer) {
    mTexture->render(renderer, mPosX, mPosY);
}