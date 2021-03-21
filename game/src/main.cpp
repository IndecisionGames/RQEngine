#include <SDL2/SDL.h>
#include <stdio.h>
#include <glm/vec2.hpp>
#include <string>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "Main.h"

enum KeyCodes {

    PLAYER_FORWARD = 100,
    PLAYER_BACK,
    PLAYER_LEFT,
    PLAYER_RIGHT,
    PLAYER_UP,
    PLAYER_DOWN,
    PLAYER_SPRINT,
    FIRE,
    AIM,
    RESET,
};


float MOUSE_SENSTIVITY = 0.8f; 
float MOVE_SPEED = 0.005f; 

bool gRenderQuad = true;

GLuint vao1 = 0;
GLuint vao2 = 0;

// Loaded Object
GLuint gObjVB = 0;

// Cube
GLuint gIBO = 0; // Index buffer
GLuint gVBO = 0; // Vertex buffer
GLuint gNBO = 0; // Normal buffer

GLuint gModelID = 0;
GLuint gViewID = 0;
GLuint gProjectionID = 0;

RQEngine::Shader* shader;

Timer timer = Timer();

void initShaders() {
    // Compline Shaders
    shader = new RQEngine::Shader("game/src/shaders/SimpleVertexShader.glsl", "game/src/shaders/SimpleFragmentShader.glsl");
    gModelID = glGetUniformLocation(*(shader->getID()), "Model");
    gViewID = glGetUniformLocation(*(shader->getID()), "View");
    gProjectionID = glGetUniformLocation(*(shader->getID()), "Projection");
}

void initVertexBuffer(GLuint* object) {
    glGenBuffers(1, object);
    glBindBuffer(GL_ARRAY_BUFFER, *object);
}

//Initializes rendering program and clear color
void initGL() {
    
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    initShaders();
    
    // Object 1
    glGenVertexArrays(1, &vao1);
    glBindVertexArray(vao1);

    initVertexBuffer(&gVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

    initVertexBuffer(&gIBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colourData), colourData, GL_STATIC_DRAW);


    // Object 2
    // TODO


    // Read .obj
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec2> uvs; // Not used atm
    std::vector<glm::vec3> normals; // Not used atm
    // loadObj("res/mesh/icosphere.obj", vertices, uvs, normals); // BUG - crashes at runtime

    // glGenBuffers(1, &gObjVB);
    // glBindBuffer(GL_ARRAY_BUFFER, gObjVB);
    // glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);
}


class TestGame: public RQEngine::Game {

    void render();

    void onInit() {

        keyBinds->load(PLAYER_FORWARD, SDLK_w);
        keyBinds->load(PLAYER_BACK, SDLK_s);
        keyBinds->load(PLAYER_LEFT, SDLK_a);
        keyBinds->load(PLAYER_RIGHT, SDLK_d);
        keyBinds->load(PLAYER_UP, SDLK_SPACE);
        keyBinds->load(PLAYER_DOWN, SDLK_LCTRL);
        keyBinds->load(PLAYER_SPRINT, SDLK_LSHIFT);
        keyBinds->load(RESET, SDLK_r);
        keyBinds->load(FIRE, SDL_BUTTON_LEFT);
        keyBinds->load(AIM, SDL_BUTTON_RIGHT);

        timer.start();
        initGL();
        SDL_SetRelativeMouseMode(SDL_FALSE);
    };

    void onExit() {
        shader->free();
    };

    void fixedUpdate(float deltaTime) {};

    void update(float deltaTime) {

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
        if(inputManager->isKeyPressed(keyBinds->getKey(PLAYER_SPRINT))){
            movement *= 2;
        }
        if(inputManager->isKeyPressedInitial(keyBinds->getKey(AIM))){
            if(SDL_GetRelativeMouseMode() == SDL_TRUE) {
                SDL_SetRelativeMouseMode(SDL_FALSE);
            } else {
                SDL_SetRelativeMouseMode(SDL_TRUE);
            }
        }

        if(SDL_GetRelativeMouseMode() == SDL_TRUE) {
            glm::ivec2 mouseMotion = inputManager->getMouseMotion();
            camera3D->rotate(MOUSE_SENSTIVITY * glm::vec2(mouseMotion.x, -mouseMotion.y));
        }


        camera3D->translateRelative((MOVE_SPEED * deltaTime) * movement);

        if (inputManager->isKeyPressedInitial(SDLK_1)) {
            gRenderQuad = !gRenderQuad;
        }

        if (inputManager->isKeyPressedInitial(SDLK_2)) {
            if(timer.isPaused()){
                timer.unpause();
            } else {
                timer.pause();
            }
        }

    };

    void draw() {
        render();
    };

};


void TestGame::render() {
    glClearColor(0.f, 0.f, 0.06f, 1.f);
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

        glBindBuffer(GL_ARRAY_BUFFER, gVBO);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

        glBindBuffer(GL_ARRAY_BUFFER, gIBO);
        glEnableVertexAttribArray(1);
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

