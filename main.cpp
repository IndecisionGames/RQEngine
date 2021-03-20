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

            camera3D->rotate(-glm::vec2(mouseMotion.x * 0.02f, mouseMotion.y * 0.02f));
            SDL_SetRelativeMouseMode(SDL_TRUE);
        }
        if (inputManager->isKeyReleasedInitial(keyBinds->getKey(AIM))) {
            SDL_SetRelativeMouseMode(SDL_FALSE);
        }

        if(inputManager->isKeyPressed(keyBinds->getKey(RESET))){
            camera3D->reset();
        }

        glm::vec3 movement = glm::vec3(0,0,0);
        if(inputManager->isKeyPressed(keyBinds->getKey(PLAYER_FORWARD))){
            movement.z += 1;
        }
        if(inputManager->isKeyPressed(keyBinds->getKey(PLAYER_BACK))){
            movement.z -= 1;
        }
        if(inputManager->isKeyPressed(keyBinds->getKey(PLAYER_LEFT))){
            movement.x += 1;
        }
        if(inputManager->isKeyPressed(keyBinds->getKey(PLAYER_RIGHT))){
            movement.x -= 1;
        }
        if(inputManager->isKeyPressed(keyBinds->getKey(PLAYER_UP))){
            movement.y -= 1;
        }
        if(inputManager->isKeyPressed(keyBinds->getKey(PLAYER_DOWN))){
            movement.y += 1;
        }

        camera3D->translateRelative((0.005f * deltaTime) * movement);

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
        // Model matrix
        float time = (float)timer.getTicks() / 10;

        glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(time), glm::vec3(0.20f, 0.80f, 0.30f));
        glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 5.0f));

        glm::mat4 Model = translationMatrix * rotationMatrix * scaleMatrix;
        //glm::mat4 Model = glm::mat4(1.0f);

        shader->use();

        glUniformMatrix4fv(gModelID, 1, GL_FALSE, &Model[0][0]);
        glUniformMatrix4fv(gViewID, 1, GL_FALSE, &camera3D->getView()[0][0]);
        glUniformMatrix4fv(gProjectionID, 1, GL_FALSE, &camera3D->getProjection()[0][0]);

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

