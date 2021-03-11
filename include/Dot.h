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
        float mPosX, mPosY;
        float mVelX, mVelY;
        Texture* mTexture;
        std::vector<Texture*> mParticleTextures;
        Circle mCollider;
        void shiftColliders();
        Particle* particles[TOTAL_PARTICLES];
        void renderParticles(SDL_Renderer* renderer, SDL_Rect& camera);

    public:
        static const int DOT_WIDTH = 20;
        static const int DOT_HEIGHT = 20;
        static const int DOT_VEL = 640;
        Dot(std::vector<Texture*> particleTextures, float posX = 0, float posY = 0, float velX = 0, float velY = 0);
        ~Dot();
        void setTexture(Texture* texture);
        void handleEvent(SDL_Event& e);
        void move(float deltaTime, int levelHeight, int levelWidth, Tile *tiles[]);
        void render(SDL_Renderer* renderer, SDL_Rect& camera);
        void setCamera(SDL_Rect& camera, int levelHeight, int levelWidth);
        Circle& getCollider();
        int getPosX();
        int getPosY();
};