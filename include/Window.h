#pragma once

#include <SDL2/SDL.h>

namespace RQEngine {

    class Window {

        public:
            Window();
            ~Window();
            bool init(int width, int height);
            void handleEvent(SDL_Event& e);
            void free();

            int getWidth(){return mWidth;};
            int getHeight(){return mHeight;};
            bool hadMouseFocus(){return mMouseFocus;};
            bool hadKeyboardFocus(){return mKeyboardFocus;};
            bool isMinimised(){return mMinimised;};
            SDL_GLContext* getContext(){return &mContext;};
            SDL_Window* getWindow(){return mWindow;};

        private:
            SDL_Window* mWindow;
            SDL_GLContext mContext;

            int mWidth;
            int mHeight;
            bool mMouseFocus;
            bool mKeyboardFocus;
            bool mFullScreen;
            bool mMinimised;
    };

} // namespace RQEngine