#include <SDL2/SDL.h>
#include <gl/glew.h>
#include <gl/glu.h>
#include <SDL2/SDL_opengl.h>
#include <stdio.h>
#include <string>
#include <iostream>

#include "Game.h"
#include "Shader.h"

using namespace RQEngine;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

const uint32_t MAX_PHYSICS_TIMESTEP = 10; // ms

bool gRenderQuad = true;

GLint gVertexPos2DLocation = -1;
GLuint gVBO = 0;
GLuint gIBO = 0;

Shader* shader;

//Initializes rendering program and clear color
void initGL() {
    // Compline Shaders

    const GLchar* vertexShaderSource = {
        "#version 140\nin vec2 LVertexPos2D; void main() { gl_Position = vec4( LVertexPos2D.x, LVertexPos2D.y, 0, 1 ); }"
    };

    const GLchar* fragmentShaderSource = {
        "#version 140\nout vec4 LFragment; void main() { LFragment = vec4( 1.0, 1.0, 1.0, 1.0 ); }"
    };

    shader = new Shader(vertexShaderSource, fragmentShaderSource);

    gVertexPos2DLocation = glGetAttribLocation(shader->ID, "LVertexPos2D");
    glClearColor(0.f, 0.f, 0.f, 1.f);

    GLfloat vertexData[] = {
        -0.5f, -0.5f,
            0.5f, -0.5f,
            0.5f,  0.5f,
        -0.5f,  0.5f
    };

    GLuint indexData[] = {0, 1, 2, 3};

    // Create VBO
    glGenBuffers(1, &gVBO);
    glBindBuffer(GL_ARRAY_BUFFER, gVBO);
    glBufferData(GL_ARRAY_BUFFER, 2 * 4 * sizeof(GLfloat), vertexData, GL_STATIC_DRAW);

    // Create IBO
    glGenBuffers(1, &gIBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gIBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 4 * sizeof(GLuint), indexData, GL_STATIC_DRAW);
}

//Input handler
void handleKeys(unsigned char key, int x, int y) {
    if (key == 'q') gRenderQuad = !gRenderQuad;
}

// TODO: Move into test game draw
//Renders quad to the screen
void render() {
    glClear(GL_COLOR_BUFFER_BIT);

    if(gRenderQuad) {
        shader->use();

        glEnableVertexAttribArray(gVertexPos2DLocation);

        glBindBuffer(GL_ARRAY_BUFFER, gVBO);
        glVertexAttribPointer(gVertexPos2DLocation, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), NULL);
  
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gIBO);
        glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, NULL);

        glDisableVertexAttribArray(gVertexPos2DLocation);
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

    // Vsync
    SDL_GL_SetSwapInterval(1);
    initGL();

    // Custom Init
    onInit();
}

void Game::run() {
    // Setup
    init();

    SDL_Event e;
    SDL_StartTextInput();

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
                    inputManager->pressKey(e.key.keysym.sym);
                    break;
                case SDL_KEYUP:
                    inputManager->releaseKey(e.key.keysym.sym);
                    break;
                case SDL_TEXTINPUT:
                    int x = 0, y = 0;
                    SDL_GetMouseState(&x, &y);
                    handleKeys(e.text.text[0], x, y);
            }
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

    SDL_StopTextInput();
    glDeleteProgram(shader->ID);
    delete window;
    SDL_Quit();
}



