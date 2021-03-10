#pragma once

#include <SDL2/SDL.h>
#include <stdio.h>
#include <vector>

#include "Texture.h"
#include "Circle.h"
#include "Particle.h"
#include "Tile.h"

class Dot {
    private:
        int mPosX, mPosY;
        int mVelX, mVelY;
        Texture* mTexture;
        std::vector<Texture*> mParticleTextures;
        Circle mCollider;
        void shiftColliders();
        Particle* particles[TOTAL_PARTICLES];
        void renderParticles(SDL_Renderer* renderer, SDL_Rect& camera);

    public:
        static const int DOT_WIDTH = 20;
        static const int DOT_HEIGHT = 20;
        static const int DOT_VEL = 10;
        Dot(std::vector<Texture*> particleTextures, int posX = 0, int posY = 0, int velX = 0, int velY = 0);
        ~Dot();
        void setTexture(Texture* texture);
        void handleEvent(SDL_Event& e);
        void move(int levelHeight, int levelWidth, Tile *tiles[]);
        void render(SDL_Renderer* renderer, SDL_Rect& camera);
        void setCamera(SDL_Rect& camera, int levelHeight, int levelWidth);
        Circle& getCollider();
        int getPosX();
        int getPosY();
};