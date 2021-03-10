#pragma once

#include <SDL2/SDL.h>
#include <stdio.h>
#include <sstream>

class Window {
    private:
        SDL_Window* mWindow;
        SDL_Renderer* mRenderer;

        int mWidth;
        int mHeight;
        bool mMouseFocus;
        bool mKeyboardFocus;
        bool mFullScreen;
        bool mMinimised;
    
    public:
        Window();
        bool init(int width, int height);
        SDL_Renderer* createRenderer(bool vsync);
        void handleEvent(SDL_Event& e);
        void free();
        int getWidth();
        int getHeight();
        bool hadMouseFocus();
        bool hadKeyboardFocus();
        bool isMinimised();
};