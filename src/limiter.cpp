#include <stdint.h>
#include <SDL2/SDL.h>
#include <iostream>

#include "RQEngine.h"

using namespace RQEngine;

const int DEFAULT_FRAME_RATE = 60;
const uint32_t FRAME_SAMPLE_RATE = 5 * DEFAULT_FRAME_RATE ;


Limiter::Limiter() {
    previousFrameTime = SDL_GetTicks();
    setFPSTarget(DEFAULT_FRAME_RATE);

    frameCount = 0;
    lastFrameSample = previousFrameTime;
    currentFPSEstimate = (float)DEFAULT_FRAME_RATE;

}

void Limiter::setFPSTarget(int target) {
    targetFPS = target;
    targetFrameTime = 1000 / targetFPS;
}

int Limiter::currentFPS() {
    return currentFPSEstimate;
}

uint32_t Limiter::startFrame() {
    startFrameTime = SDL_GetTicks();
    return startFrameTime - previousFrameTime;
}

void Limiter::update() {
    frameCount++;
    if (frameCount >= FRAME_SAMPLE_RATE){
        std::cout << "FPS: " << currentFPSEstimate << std::endl;
        currentFPSEstimate = (startFrameTime - lastFrameSample) / frameCount;
        frameCount = 0;
        lastFrameSample = startFrameTime;
    }

    previousFrameTime = startFrameTime;
}

void Limiter::limit() {
    uint32_t frameTime = SDL_GetTicks() - startFrameTime;

    if (frameTime < targetFrameTime) {
        SDL_Delay(targetFrameTime - frameTime);
    }
    update();
}
