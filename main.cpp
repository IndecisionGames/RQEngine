#include <SDL2/SDL.h>
#include <stdio.h>
#include <glm/vec2.hpp>
#include <string>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "RQEngine.h"

enum KeyCodes {

    PLAYER_FORWARD = 10,
    PLAYER_BACK,
    PLAYER_LEFT,
    PLAYER_RIGHT,
    PLAYER_UP,
    PLAYER_DOWN,

    FIRE = 50,
    AIM,

    RESET = 100,
};


bool gRenderQuad = true;
glm::vec3 CameraPosition = glm::vec3(0,0,-6);
glm::vec2 CameraRotation = glm::vec2(0,0);

GLuint gIBO = 0;
GLuint gVBO = 0;

GLuint gModelID = 0;
GLuint gViewID = 0;
GLuint gProjectionID = 0;

RQEngine::Shader* shader;

Timer timer = Timer();

//Initializes rendering program and clear color
void initGL() {
    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    // Compline Shaders
    shader = new RQEngine::Shader("src/shaders/SimpleVertexShader.glsl", "src/shaders/SimpleFragmentShader.glsl");
    gModelID = glGetUniformLocation(*(shader->getID()), "Model");
    gViewID = glGetUniformLocation(*(shader->getID()), "View");
    gProjectionID = glGetUniformLocation(*(shader->getID()), "Projection");

    glClearColor(0.f, 0.f, 0.06f, 1.f);

    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    GLfloat vertexData[] = {
        -1.0f,-1.0f,-1.0f, // triangle 1 : begin
        -1.0f,-1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f, // triangle 1 : end
        1.0f, 1.0f,-1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f,-1.0f,
        1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f,-1.0f,
        1.0f,-1.0f,-1.0f,
        1.0f, 1.0f,-1.0f,
        1.0f,-1.0f,-1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f,-1.0f,
        1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f,-1.0f, 1.0f,
        1.0f,-1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f,-1.0f,-1.0f,
        1.0f, 1.0f,-1.0f,
        1.0f,-1.0f,-1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f,-1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f,-1.0f,
        -1.0f, 1.0f,-1.0f,
        1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f,
        1.0f,-1.0f, 1.0f
    };

    // Create VBO
    // TODO:: Should likely be configurable in main Game class
    glGenBuffers(1, &gVBO);
    glBindBuffer(GL_ARRAY_BUFFER, gVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

        // One color for each vertex. They were generated randomly.
    GLfloat colourData[] = {
        1.0f,  0.0f,  0.0f,
        1.0f,  0.0f,  0.0f,
        1.0f,  0.0f,  0.0f,

        0.0f,  1.0f,  0.0f,
        0.0f,  1.0f,  0.0f,
        0.0f,  1.0f,  0.0f,

        0.0f,  0.0f,  1.0f,
        0.0f,  0.0f,  1.0f,
        0.0f,  0.0f,  1.0f,

        0.0f,  1.0f,  0.0f,
        0.0f,  1.0f,  0.0f,
        0.0f,  1.0f,  0.0f,

        1.0f,  0.0f,  0.0f,
        1.0f,  0.0f,  0.0f,
        1.0f,  0.0f,  0.0f,

        0.0f,  0.0f,  1.0f,
        0.0f,  0.0f,  1.0f,
        0.0f,  0.0f,  1.0f,

        1.0f,  0.0f,  1.0f,
        1.0f,  0.0f,  1.0f,
        1.0f,  0.0f,  1.0f,

        0.0f,  1.0f,  1.0f,
        0.0f,  1.0f,  1.0f,
        0.0f,  1.0f,  1.0f,

        0.0f,  1.0f,  1.0f,
        0.0f,  1.0f,  1.0f,
        0.0f,  1.0f,  1.0f,

        1.0f,  1.0f,  0.0f,
        1.0f,  1.0f,  0.0f,
        1.0f,  1.0f,  0.0f,

        1.0f,  1.0f,  0.0f,
        1.0f,  1.0f,  0.0f,
        1.0f,  1.0f,  0.0f,

        1.0f,  0.0f,  1.0f,
        1.0f,  0.0f,  1.0f,
        1.0f,  0.0f,  1.0f,
    };

    glGenBuffers(1, &gIBO);
    glBindBuffer(GL_ARRAY_BUFFER, gIBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colourData), colourData, GL_STATIC_DRAW);
}

class TestGame: public RQEngine::Game {

    void render();

    void onInit() {

        RQEngine::keyBind keys[9] = {
            RQEngine::keyBind(PLAYER_FORWARD, SDLK_w),
            RQEngine::keyBind(PLAYER_BACK, SDLK_s),
            RQEngine::keyBind(PLAYER_LEFT, SDLK_a),
            RQEngine::keyBind(PLAYER_RIGHT, SDLK_d),
            RQEngine::keyBind(PLAYER_UP, SDLK_LSHIFT),
            RQEngine::keyBind(PLAYER_DOWN, SDLK_LCTRL),
            RQEngine::keyBind(RESET, SDLK_r),
            RQEngine::keyBind(FIRE, SDL_BUTTON_LEFT),
            RQEngine::keyBind(AIM, SDL_BUTTON_RIGHT)
        };
        keyBinds->loadKeyBinds(keys);

        timer.start();
        initGL();
    };

    void onExit() {
        shader->free();
    };

    void fixedUpdate(float deltaTime) {};

    void update(float deltaTime) {

        if (inputManager->isKeyPressed(keyBinds->getKey(AIM))) {
            glm::ivec2 mouseMotion = inputManager->getMouseMotion();

            CameraRotation += (glm::vec2)mouseMotion * glm::vec2(0.1f, 0.1f);
        }
        if(inputManager->isKeyPressed(keyBinds->getKey(RESET))){
            CameraRotation = glm::vec2(0.1f, 0.1f);
        }

        // Note: Movement is still relative to world, not camera direction
        float moveVal = 0.005f * deltaTime;
        if(inputManager->isKeyPressed(keyBinds->getKey(PLAYER_FORWARD))){
            CameraPosition.z += moveVal;
        }
        if(inputManager->isKeyPressed(keyBinds->getKey(PLAYER_BACK))){
            CameraPosition.z -= moveVal;
        }
        if(inputManager->isKeyPressed(keyBinds->getKey(PLAYER_LEFT))){
            CameraPosition.x += moveVal;
        }
        if(inputManager->isKeyPressed(keyBinds->getKey(PLAYER_RIGHT))){
            CameraPosition.x -= moveVal;
        }
        if(inputManager->isKeyPressed(keyBinds->getKey(PLAYER_UP))){
            CameraPosition.y -= moveVal;
        }
        if(inputManager->isKeyPressed(keyBinds->getKey(PLAYER_DOWN))){
            CameraPosition.y += moveVal;
        }
        if(inputManager->isKeyPressed(keyBinds->getKey(PLAYER_DOWN))){
            CameraPosition.y += moveVal;
        }


        if (inputManager->isKeyPressedInitial(SDLK_q)) {
            gRenderQuad = !gRenderQuad;
        }

    };

    void draw() {
        render();
    };

};


//Renders quad to the screen
void TestGame::render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if(gRenderQuad) {
        // Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
        glm::mat4 Projection = glm::perspective(glm::radians(45.0f), (float) window->getWidth() / (float) window->getHeight(), 0.1f, 100.0f);

        // Or, for an ortho camera :
        // glm::mat4 Projection = glm::ortho(-10.0f,10.0f,-10.0f,10.0f,0.0f,100.0f); // In world coordinates

        // Camera matrix
        glm::mat4 camScaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        glm::mat4 camRotationMatrixX = glm::rotate(glm::mat4(1.0f), glm::radians(CameraRotation.x), glm::vec3(0.0f, 1.0f, 0.0f));
        glm::mat4 camTranslationMatrix = glm::translate(glm::mat4(1.0f), CameraPosition);

        glm::mat4 View = camScaleMatrix * camRotationMatrixX * camTranslationMatrix;

        // Model matrix
        float time = (float)timer.getTicks() / 10;

        glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(time), glm::vec3(0.20f, 0.80f, 0.30f));
        glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));

        glm::mat4 Model = translationMatrix * rotationMatrix * scaleMatrix;
        //glm::mat4 Model = glm::mat4(1.0f);

        shader->use();

        glUniformMatrix4fv(gModelID, 1, GL_FALSE, &Model[0][0]);
        glUniformMatrix4fv(gViewID, 1, GL_FALSE, &View[0][0]);
        glUniformMatrix4fv(gProjectionID, 1, GL_FALSE, &Projection[0][0]);

        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, gVBO);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, gIBO);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);

        glDrawArrays(GL_TRIANGLES, 0, 12*3);

        glDisableVertexAttribArray(0);
        glUseProgram(0);
    }
}


int main(int argc, char* args[]) {

    TestGame game = TestGame();
    game.run();

    return 0;
}

