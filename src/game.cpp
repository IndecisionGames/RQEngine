#include <SDL2/SDL.h>
#include <gl/glew.h>
#include <gl/glu.h>
#include <SDL2/SDL_opengl.h>
#include <stdio.h>
#include <string>
#include <iostream>

#include "Game.h"
#include "Shader.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

const uint32_t MAX_PHYSICS_TIMESTEP = 10; // ms

bool gRenderQuad = true;

GLuint gVBO = 0;

using namespace RQEngine;

Shader* shader;

//Initializes rendering program and clear color
void initGL() {
    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    // Compline Shaders
    shader = new Shader("src/shaders/SimpleVertexShader.glsl", "src/shaders/SimpleFragmentShader.glsl");

    glClearColor(0.f, 0.f, 0.06f, 1.f);

    GLfloat vertexData[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.5f,  0.5f, 0.0f,
        -0.5f,  0.5f, 0.0f
    };

    // Create VBO
    glGenBuffers(1, &gVBO);
    glBindBuffer(GL_ARRAY_BUFFER, gVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
}

// TODO: Move into test game draw
//Renders quad to the screen
void render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if(gRenderQuad) {
        shader->use();

        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, gVBO);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

        glDisableVertexAttribArray(0);
        glUseProgram(0);
    }
}

// TODO: Refactor everything above

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

    window = new Window();
    window->init(SCREEN_WIDTH, SCREEN_HEIGHT);

    glewExperimental = GL_TRUE;
    GLenum glewError = glewInit();
    if (glewError != GLEW_OK) printf("Error initialising GLEW! %s\n", glewGetErrorString(glewError));

    // VSync
    SDL_GL_SetSwapInterval(1);
    initGL();

    // Custom Init
    onInit();
}

void Game::run() {
    // Setup
    init();

    SDL_Event e;

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

        if (inputManager->isKeyPressedInitial(SDLK_q)) {
            gRenderQuad = !gRenderQuad;
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
        render();
        SDL_GL_SwapWindow(window->getWindow());

        inputManager->update(deltaTime);
        fpsLimiter.limit();
    }

    exit();
}


void Game::exit() {
     // Custom Exit
    onExit();

    shader->free();
    delete window;
    SDL_Quit();
}
