#include <SDL2/SDL.h>
#include <stdio.h>
#include <glm/vec2.hpp>
#include <string>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "RQEngine.h"

enum KeyCodes {

    PLAYER_UP = 10,
    PLAYER_DOWN,
    PLAYER_LEFT,
    PLAYER_RIGHT,

    FIRE = 50,
    AIM,

    DEBUG = 100,
};


bool gRenderQuad = true;

GLuint gVBO = 0;
GLuint gMatrixID = 0;

RQEngine::Shader* shader;

//Initializes rendering program and clear color
void initGL() {
    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    // Compline Shaders
    shader = new RQEngine::Shader("src/shaders/SimpleVertexShader.glsl", "src/shaders/SimpleFragmentShader.glsl");
    gMatrixID = glGetUniformLocation(*(shader->getID()), "MVP");

    glClearColor(0.f, 0.f, 0.06f, 1.f);

    GLfloat vertexData[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.5f,  0.5f, 0.0f,
        -0.5f,  0.5f, 0.0f
    };

    // Create VBO
    // TODO:: Should likely be configurable in main Game class
    glGenBuffers(1, &gVBO);
    glBindBuffer(GL_ARRAY_BUFFER, gVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
}

class TestGame: public RQEngine::Game {

    void render();

    void onInit() {

        RQEngine::keyBind keys[7] = {
            RQEngine::keyBind(PLAYER_UP, SDLK_w),
            RQEngine::keyBind(PLAYER_DOWN, SDLK_s),
            RQEngine::keyBind(PLAYER_LEFT, SDLK_a),
            RQEngine::keyBind(PLAYER_RIGHT, SDLK_d),
            RQEngine::keyBind(DEBUG, SDLK_p),
            RQEngine::keyBind(FIRE, SDL_BUTTON_LEFT),
            RQEngine::keyBind(AIM, SDL_BUTTON_RIGHT)
        };
        keyBinds->loadKeyBinds(keys);

        initGL();

    };

    void onExit() {
        shader->free();
    };

    void fixedUpdate(float deltaTime) {};

    void update(float deltaTime) {

        unsigned int keyHeldTime = inputManager->isKeyHeld(keyBinds->getKey(DEBUG));
        if (keyHeldTime > 0) {
            std::cout << "Key Held: " << keyHeldTime << std::endl;
        } else if (inputManager->isKeyPressed(keyBinds->getKey(DEBUG))) {
            std::cout << "Key Pressed" << std::endl;
        }

        if (inputManager->isKeyPressedInitial(keyBinds->getKey(AIM))) {
            glm::uvec2 mousePos = inputManager->getMousePosition();
            glm::ivec2 mouseMotion = inputManager->getMouseMotion();

            printf("Position: (%u, %u)\n", mousePos.x, mousePos.y);
            printf("Motion: (%i,%i)\n", mouseMotion.x, mouseMotion.y);
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


int main(int argc, char* args[]) {

    TestGame game = TestGame();
    game.run();

    return 0;
}

