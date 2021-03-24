#include <stdint.h>
#include <SDL2/SDL.h>
#include <iostream>

#include "Limiter.h"

using namespace RQEngine;

const int DEFAULT_FRAME_RATE = 60;
const uint32_t FRAME_SAMPLE_RATE = 3 * DEFAULT_FRAME_RATE;


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
    if (frameCount >= FRAME_SAMPLE_RATE){
        currentFPSEstimate = frameCount * 1000 / (startFrameTime - lastFrameSample);
        std::cout << "FPS: " << currentFPSEstimate << std::endl;
        frameCount = 0;
        lastFrameSample = startFrameTime;
    }

    frameCount++;
    previousFrameTime = startFrameTime;
}

void Limiter::limit() {
    update();

    uint32_t frameTime = SDL_GetTicks() - startFrameTime;
    if (frameTime < targetFrameTime) {
        SDL_Delay(targetFrameTime - frameTime);
    }
}
