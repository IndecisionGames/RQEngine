#include <sstream>

#include "Window.h"

using namespace RQEngine;

Window::Window() {
    mWindow = NULL;
    mMouseFocus = false;
    mKeyboardFocus = false;
    mFullScreen = false;
    mMinimised = false;
    mWidth = 0;
    mHeight = 0;
}

Window::~Window() {
    free();
}

bool Window::init(int width, int height) {
    mWindow = SDL_CreateWindow("RQ Engine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    if (mWindow != NULL) {
        mMouseFocus = true;
        mKeyboardFocus = true;
        mWidth = width;
        mHeight = height;
        mContext = SDL_GL_CreateContext(mWindow);
    }
    return mWindow != NULL;
}

void Window::handleEvent(SDL_Event& e) {
    if (e.type == SDL_WINDOWEVENT) {
        bool updateCaption = false;
        switch(e.window.event) {
            case SDL_WINDOWEVENT_ENTER:
                mMouseFocus = true;
                updateCaption = true;
                break;

            case SDL_WINDOWEVENT_LEAVE:
                mMouseFocus = false;
                updateCaption = true;
                break;

            case SDL_WINDOWEVENT_FOCUS_GAINED:
                mKeyboardFocus = true;
                updateCaption = true;
                break;

            case SDL_WINDOWEVENT_FOCUS_LOST:
                mKeyboardFocus = false;
                updateCaption = true;

            case SDL_WINDOWEVENT_MINIMIZED:
                mMinimised = true;
                break;

            case SDL_WINDOWEVENT_MAXIMIZED:
                mMinimised = false;
                break;

            case SDL_WINDOWEVENT_RESTORED:
                mMinimised = false;
                break;
        }

        if (updateCaption) {
            std::stringstream caption;
            caption << "SDL Tutorial - MouseFocus:" << (mMouseFocus ? "On" : "Off") << " KeyboardFocus:" << (mKeyboardFocus ? "On" : "Off");
            SDL_SetWindowTitle(mWindow, caption.str().c_str());
        }
    } else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_F11) {
        if (mFullScreen) {
            SDL_SetWindowFullscreen(mWindow, 0);
            mFullScreen = false;
        } else {
            SDL_SetWindowFullscreen(mWindow, 1);
            mFullScreen = true;
            mMinimised = false;
        }
    }
}

void Window::free() {
    SDL_DestroyWindow(mWindow);
    mWindow = NULL;
}
