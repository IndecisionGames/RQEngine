#include "Dot.h"

double distanceSquared(int x1, int y1, int x2, int y2) {
    int dX = x2 - x1;
    int dY = y2 - y1;
    return dX * dX + dY * dY;
}

bool checkCollision(Circle& a, Circle& b) {
    int totalRadiusSquared = (a.r + b.r) * (a.r + b.r);

    if (distanceSquared(a.x, a.y, b.x, b.y) < totalRadiusSquared) return true;
    return false;
}

bool checkCollision(Circle& a, SDL_Rect& b) {
    int cX, cY;

    if (a.x < b.x) {
        cX = b.x;
    } else if (a.x > b.x + b.w) {
        cX = b.x + b.w;
    } else {
        cX = a.x;
    }

    if (a.y < b.y) {
        cY = b.y;
    } else if (a.y > b.y + b.h) {
        cY = b.y + b.h;
    } else {
        cY = a.y;
    }

    if (distanceSquared(a.x, a.y, cX, cY) < a.r * a.r) return true;
    return false;
}

Dot::Dot(std::vector<Texture*> particleTextures, int posX, int posY, int velX, int velY) {
    mPosX = posX;
    mPosY = posY;
    mVelX = velX;
    mVelY = velY;
    mTexture = NULL;

    mParticleTextures = particleTextures;

    mCollider.r = DOT_WIDTH / 2;
    shiftColliders();

    for (int i = 0; i < TOTAL_PARTICLES; ++i) {
        particles[i] = new Particle(mPosX, mPosY, mParticleTextures);
    }
}

Dot::~Dot() {
    for (int i = 0; i < TOTAL_PARTICLES; ++i) {
        delete particles[i];
    }
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

void Dot::move(int levelHeight, int leveWidth, SDL_Rect& square) {
    mPosX += mVelX;
    shiftColliders();
    if ((mPosX < 0) || (mPosX + DOT_WIDTH > leveWidth) || checkCollision(mCollider, square)) {
        mPosX -= mVelX;
        shiftColliders();
    }
    mPosY += mVelY;
    shiftColliders();
    if ((mPosY < 0) || (mPosY + DOT_HEIGHT > levelHeight) || checkCollision(mCollider, square)) { 
        mPosY -= mVelY;
        shiftColliders();
    }
}

void Dot::render(SDL_Renderer* renderer, int camX, int camY) {
    mTexture->render(renderer, mPosX - camX, mPosY - camY);
    renderParticles(renderer);
}

void Dot::renderParticles(SDL_Renderer* renderer) {
    for (int i = 0; i < TOTAL_PARTICLES; ++i) {
        if (particles[i]->isDead()) {
            delete particles[i];
            particles[i] = new Particle(mPosX, mPosY, mParticleTextures);
        }
    }

    for (int i = 0; i < TOTAL_PARTICLES; ++i) {
        particles[i]->render(renderer);
    }
}

void Dot::shiftColliders() {
    mCollider.x = mPosX + DOT_WIDTH / 2;
    mCollider.y = mPosY + DOT_HEIGHT / 2; 
}

Circle& Dot::getCollider() {
    return mCollider;
}

int Dot::getPosX() {
    return mPosX;
}

int Dot::getPosY() {
    return mPosY;
}