#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>

class Timer {
    private:
        Uint32 mStartTicks; // Clock time when timer started
        Uint32 mPausedTicks; // Clock time when timer was paused
        bool mPaused;
        bool mStarted;
    
    public:
        Timer();

        void start();
        void stop();
        void pause();
        void unpause();

        Uint32 getTicks();

        bool isPaused();
        bool isStarted();
};