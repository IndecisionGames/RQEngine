#include <SDL2/SDL.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "Game.h"
#include "Shader.h"

const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;

const uint32_t MAX_PHYSICS_TIMESTEP = 10; // ms

bool gRenderQuad = true;

GLuint gVBO = 0;
GLuint gMatrixID = 0;

using namespace RQEngine;

Shader* shader;

//Initializes rendering program and clear color
void initGL() {
    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    // Compline Shaders
    shader = new Shader("src/shaders/SimpleVertexShader.glsl", "src/shaders/SimpleFragmentShader.glsl");
    gMatrixID = glGetUniformLocation(*(shader->getID()), "MVP");
    
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
        // Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
        glm::mat4 Projection = glm::perspective(glm::radians(45.0f), (float) SCREEN_WIDTH / (float) SCREEN_HEIGHT, 0.1f, 100.0f);

        // Or, for an ortho camera :
        // glm::mat4 Projection = glm::ortho(-10.0f,10.0f,-10.0f,10.0f,0.0f,100.0f); // In world coordinates

        // Camera matrix
        glm::mat4 View = glm::lookAt(
            glm::vec3(4,3,3), // Camera is at (4,3,3), in World Space
            glm::vec3(0,0,0), // and looks at the origin
            glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
        );
            
        // Model matrix
        glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(3.0f, 3.0f, 1.0f));
        glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));

        glm::mat4 Model = translationMatrix * rotationMatrix * scaleMatrix;
        //glm::mat4 Model = glm::mat4(1.0f);

        // Our ModelViewProjection : multiplication of our 3 matrices
        glm::mat4 mvp = Projection * View * Model; // Remember, matrix multiplication is the other way around

        shader->use();

        // Send our transformation to the currently bound shader, in the "MVP" uniform
        // This is done in the main loop since each model will have a different MVP matrix (At least for the M part)
        glUniformMatrix4fv(gMatrixID, 1, GL_FALSE, &mvp[0][0]);

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
