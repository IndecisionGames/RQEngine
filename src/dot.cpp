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

bool checkCollision(Circle& a, SDL_Rect b) {
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

bool touchesWall(Circle& collider, Tile* tiles[]) {
    for(int i = 0; i < TOTAL_TILES; ++i) {
        if ((tiles[i]->getType() >= TILE_CENTER) && (tiles[i]->getType() <= TILE_TOPLEFT)) {
            if (checkCollision(collider, tiles[i]->getBox())) return true;
        }
    }
    return false;
}

Dot::Dot(std::vector<Texture*> particleTextures, float posX, float posY, float velX, float velY) {
    mPosX = posX;
    mPosY = posY;
    mVelX = velX;
    mVelY = velY;
    mTexture = NULL;

    mParticleTextures = particleTextures;

    mCollider.r = DOT_WIDTH / 2;
    shiftColliders();

    for (int i = 0; i < TOTAL_PARTICLES; ++i) {
        particles[i] = new Particle((int)mPosX, (int)mPosY, mParticleTextures);
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

void Dot::move(float deltaTime, int levelHeight, int leveWidth, Tile *tiles[]) {
    mPosX += mVelX * deltaTime;
    shiftColliders();
    if ((mPosX < 0) || (mPosX + DOT_WIDTH > leveWidth) || touchesWall(mCollider, tiles)) {
        mPosX -= mVelX * deltaTime;
        shiftColliders();
    }
    mPosY += mVelY * deltaTime;
    shiftColliders();
    if ((mPosY < 0) || (mPosY + DOT_HEIGHT > levelHeight) || touchesWall(mCollider, tiles)) { 
        mPosY -= mVelY * deltaTime;
        shiftColliders();
    }
}

void Dot::render(SDL_Renderer* renderer, SDL_Rect& camera) {
    mTexture->render(renderer, (int)mPosX - camera.x, (int)mPosY - camera.y);
    renderParticles(renderer, camera);
}

void Dot::renderParticles(SDL_Renderer* renderer, SDL_Rect& camera) {
    for (int i = 0; i < TOTAL_PARTICLES; ++i) {
        if (particles[i]->isDead()) {
            delete particles[i];
            particles[i] = new Particle((int)mPosX, (int)mPosY, mParticleTextures);
        }
    }

    for (int i = 0; i < TOTAL_PARTICLES; ++i) {
        particles[i]->render(renderer, camera.x, camera.y);
    }
}

void Dot::shiftColliders() {
    mCollider.x = mPosX + DOT_WIDTH / 2;
    mCollider.y = mPosY + DOT_HEIGHT / 2; 
}

void Dot::setCamera(SDL_Rect& camera, int levelHeight, int levelWidth) {
    camera.x = ((int)mPosX + DOT_WIDTH / 2) - camera.w / 2;
    camera.y = ((int)mPosY + DOT_HEIGHT / 2) - camera.h / 2;

    if( camera.x < 0 ) camera.x = 0;
    if( camera.y < 0 ) camera.y = 0;
    if( camera.x > levelWidth - camera.w ) camera.x = levelWidth - camera.w;
    if( camera.y > levelHeight - camera.h ) camera.y = levelHeight - camera.h;
}

Circle& Dot::getCollider() {
    return mCollider;
}

int Dot::getPosX() {
    return (int)mPosX;
}

int Dot::getPosY() {
    return (int)mPosY;
}