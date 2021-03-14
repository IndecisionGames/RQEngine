#include <SDL2/SDL.h>
#include <gl/glew.h>
#include <gl/glu.h>
#include <SDL2/SDL_opengl.h>
#include <stdio.h>
#include <string>
#include <iostream>

#include "RQEngine.h"

using namespace RQEngine;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

const uint32_t MAX_PHYSICS_TIMESTEP = 10; // ms

SDL_Window* gWindow = NULL;
SDL_GLContext gContext;

bool gRenderQuad = true;

GLuint gProgramID = 0;
GLint gVertexPos2DLocation = -1;
GLuint gVBO = 0;
GLuint gIBO = 0;

//Shader loading utility programs
void printProgramLog(GLuint program) {
    //Make sure name is program
    if (glIsProgram(program)) {
        //Program log length
        int infoLogLength = 0;
        int maxLength = infoLogLength;

        //Get info string length
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

        //Allocate string
        char* infoLog = new char[maxLength];

        //Get info log
        glGetProgramInfoLog(program, maxLength, &infoLogLength, infoLog);
        if (infoLogLength > 0) printf("%s\n", infoLog);

        //Deallocate string
        delete[] infoLog;
    }
    else {
        printf("Name %d is not a program\n", program);
    }
}

void printShaderLog(GLuint shader) {
    //Make sure name is shader
    if (glIsShader(shader)) {
        //Shader log length
        int infoLogLength = 0;
        int maxLength = infoLogLength;

        //Get info string length
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

        //Allocate string
        char* infoLog = new char[maxLength];

        //Get info log
        glGetShaderInfoLog(shader, maxLength, &infoLogLength, infoLog);
        if (infoLogLength > 0) printf("%s\n", infoLog);

        //Deallocate string
        delete[] infoLog;
    }
    else {
        printf("Name %d is not a shader\n", shader);
    }
}


//Initializes rendering program and clear color
void initGL() {
    gProgramID = glCreateProgram();
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

    const GLchar* vertexShaderSource[] = {
        "#version 140\nin vec2 LVertexPos2D; void main() { gl_Position = vec4( LVertexPos2D.x, LVertexPos2D.y, 0, 1 ); }"
    };

    glShaderSource(vertexShader, 1, vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    GLint vShaderCompiled = GL_FALSE;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vShaderCompiled);
    if (vShaderCompiled != GL_TRUE) {
        printf("Unable to compile vertex shader %d!\n", vertexShader);
        printShaderLog(vertexShader);
    } else {
        glAttachShader(gProgramID, vertexShader);
        GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

        const GLchar* fragmentShaderSource[] = {
            "#version 140\nout vec4 LFragment; void main() { LFragment = vec4( 1.0, 1.0, 1.0, 1.0 ); }"
        };

        glShaderSource(fragmentShader, 1, fragmentShaderSource, NULL);
        glCompileShader(fragmentShader);

        GLint fShaderCompiled = GL_FALSE;
        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &fShaderCompiled);
        if (fShaderCompiled != GL_TRUE) {
            printf("Unable to compile fragment shader %d!\n", fragmentShader);
            printShaderLog(fragmentShader);
        } else {
            glAttachShader(gProgramID, fragmentShader);
            glLinkProgram(gProgramID);

            //Check for errors
            GLint programSuccess = GL_TRUE;
            glGetProgramiv(gProgramID, GL_LINK_STATUS, &programSuccess);
            if (programSuccess != GL_TRUE) {
                printf("Error linking program %d!\n", gProgramID);
                printProgramLog(gProgramID);
            } else {
                gVertexPos2DLocation = glGetAttribLocation(gProgramID, "LVertexPos2D");

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
        }
    }
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
        glUseProgram(gProgramID);

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

    SDL_Init(SDL_INIT_VIDEO);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN );
    gContext = SDL_GL_CreateContext(gWindow);

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
    init();

    SDL_Event e;
    SDL_StartTextInput();

    bool quit = false;
    while (!quit) {
        deltaTime = fpsLimiter.startFrame();

        while (SDL_PollEvent(&e) != 0) {
            switch (e.type) {
                case SDL_QUIT:
                    quit = true;
                    break;
                case SDL_KEYDOWN:
                    inputManager->pressKey(e.key.keysym.sym, deltaTime);
                    break;
                case SDL_KEYUP:
                    inputManager->releaseKey(e.key.keysym.sym);
                    break;
                case SDL_TEXTINPUT:
                    int x = 0, y = 0;
                    SDL_GetMouseState(&x, &y);
                    handleKeys(e.text.text[0], x, y);
            }
        }

        uint32_t timeStepRemaining = deltaTime;
        while (timeStepRemaining > 0) {
            if (timeStepRemaining < MAX_PHYSICS_TIMESTEP){
                fixedUpdate(timeStepRemaining);
                break;
            }
            timeStepRemaining -= MAX_PHYSICS_TIMESTEP;
        }

        update(deltaTime);
        draw();

        render();
        SDL_GL_SwapWindow(gWindow);

        fpsLimiter.limit();
    }

    exit();
}


void Game::exit() {
     // Custom Exit
    onExit();

    SDL_StopTextInput();
    glDeleteProgram(gProgramID);
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    SDL_Quit();
}



