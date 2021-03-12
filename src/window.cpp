#include "Window.h"

Window::Window() {
    mWindow = NULL;
    mRenderer = NULL;
    mMouseFocus = false;
    mKeyboardFocus = false;
    mFullScreen = false;
    mMinimised = false;
    mWidth = 0;
    mHeight = 0;
}

bool Window::init(int width, int height) {
    mWindow = SDL_CreateWindow("RQ Engine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    if (mWindow != NULL) {
        mMouseFocus = true;
        mKeyboardFocus = true;
        mWidth = width;
        mHeight = height;
    }
    return mWindow != NULL;
}

SDL_Renderer* Window::createRenderer(bool vsync) {
    if (vsync) {
        mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    } else {
        mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED);
    }
    return mRenderer;
}

void Window::handleEvent(SDL_Event& e) {
    if (e.type == SDL_WINDOWEVENT) {
        bool updateCaption = false;
        switch(e.window.event) {
            case SDL_WINDOWEVENT_SIZE_CHANGED:
                mWidth = e.window.data1;
                mHeight = e.window.data2;
                SDL_RenderPresent(mRenderer);
                break;

            case SDL_WINDOWEVENT_EXPOSED:
                SDL_RenderPresent(mRenderer);
                break;

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
    SDL_DestroyRenderer(mRenderer);
    SDL_DestroyWindow(mWindow);
    mRenderer = NULL;
    mWindow = NULL;
    
}

int Window::getWidth() {
    return mWidth;
}

int Window::getHeight() {
    return mHeight;
}

bool Window::hadMouseFocus() {
    return mMouseFocus;
}

bool Window::hadKeyboardFocus() {
    return mKeyboardFocus;
}

bool Window::isMinimised() {
    return mMinimised;
}