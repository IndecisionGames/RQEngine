#include "Timer.h"

Timer::Timer() {
    mStartTicks = 0;
    mPausedTicks = 0;
    mPaused = false;
    mStarted = false;
}

void Timer::start() {
    mStarted = true;
    mPaused = false;

    mStartTicks = SDL_GetTicks();
    mPausedTicks = 0;
}

void Timer::stop() {
    mStarted = false;
    mPaused = false;
    mStartTicks = 0;
    mPausedTicks = 0;
}

void Timer::pause() {
    if(mStarted && !mPaused) {
        mPaused = true;
        mPausedTicks = SDL_GetTicks() - mStartTicks;
        mStartTicks = 0;
    }
}

void Timer::unpause() {
    if(mStarted && mPaused) {
        mPaused = false;
        mStartTicks = SDL_GetTicks() - mPausedTicks;
    }
}

Uint32 Timer::getTicks() {
    if(mStarted) {
        if(mPaused) {
            return mPausedTicks;
        } else {
            return (SDL_GetTicks() - mStartTicks);
        }
    }
    return 0;
}

bool Timer::isPaused() {
    return mPaused && mStarted;
}

bool Timer::isStarted() {
    return mStarted;
}