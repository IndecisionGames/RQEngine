#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <stdio.h>
#include <string>
#include <iostream>

#include "Game.h"
#include "Camera3D.h"

const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;

const uint32_t MAX_PHYSICS_TIMESTEP = 10; // ms


using namespace RQEngine;

Game::Game() {}

Game::~Game() {}

//Starts up SDL, creates window, and initializes OpenGL
void Game::init() {
    inputManager = InputManager::getInstance();
    keyBinds = KeyBinds::getInstance();

    SDL_Init(SDL_INIT_VIDEO);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    window = new Window();
    window->init(SCREEN_WIDTH, SCREEN_HEIGHT);

    camera3D = new Camera3D();
    camera3D->init(SCREEN_WIDTH, SCREEN_HEIGHT);

    glewExperimental = GL_TRUE;
    GLenum glewError = glewInit();
    if (glewError != GLEW_OK) printf("Error initialising GLEW! %s\n", glewGetErrorString(glewError));

    // VSync
    SDL_GL_SetSwapInterval(1);
    // fpsLimiter.setFPSTarget(144);

    // Custom Init
    onInit();
}

void Game::run() {
    // Setup
    init();

    SDL_Event e;
    uint32_t deltaTime;

    // Running
    bool quit = false;
    while (!quit) {
        deltaTime = fpsLimiter.startFrame();

        // Process Events
        while (SDL_PollEvent(&e) != 0) {
            switch (e.type) {
                case SDL_QUIT:
                    quit = true;
                    break;
                case SDL_KEYDOWN:
                    if (e.key.keysym.sym == SDLK_ESCAPE) quit = true;
                    break;
            }
            inputManager->handleEvent(e);
            window->handleEvent(e);
        }

        // Custom Game Physics Update
        uint32_t timeStepRemaining = deltaTime;
        while (timeStepRemaining > 0) {
            if (timeStepRemaining < MAX_PHYSICS_TIMESTEP){
                fixedUpdate(timeStepRemaining);
                break;
            }
            timeStepRemaining -= MAX_PHYSICS_TIMESTEP;
        }

        // Custom Update and Draw
        update(deltaTime);
        draw();

        // End of Frame Processing
        SDL_GL_SwapWindow(window->getWindow());

        inputManager->update(deltaTime);
        fpsLimiter.limit();
    }

    exit();
}


void Game::exit() {
     // Custom Exit
    onExit();

    window->free();
    SDL_Quit();
}
