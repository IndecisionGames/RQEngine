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
        0.583f,  0.771f,  0.014f,
        0.609f,  0.115f,  0.436f,
        0.327f,  0.483f,  0.844f,
        0.822f,  0.569f,  0.201f,
        0.435f,  0.602f,  0.223f,
        0.310f,  0.747f,  0.185f,
        0.597f,  0.770f,  0.761f,
        0.559f,  0.436f,  0.730f,
        0.359f,  0.583f,  0.152f,
        0.483f,  0.596f,  0.789f,
        0.559f,  0.861f,  0.639f,
        0.195f,  0.548f,  0.859f,
        0.014f,  0.184f,  0.576f,
        0.771f,  0.328f,  0.970f,
        0.406f,  0.615f,  0.116f,
        0.676f,  0.977f,  0.133f,
        0.971f,  0.572f,  0.833f,
        0.140f,  0.616f,  0.489f,
        0.997f,  0.513f,  0.064f,
        0.945f,  0.719f,  0.592f,
        0.543f,  0.021f,  0.978f,
        0.279f,  0.317f,  0.505f,
        0.167f,  0.620f,  0.077f,
        0.347f,  0.857f,  0.137f,
        0.055f,  0.953f,  0.042f,
        0.714f,  0.505f,  0.345f,
        0.783f,  0.290f,  0.734f,
        0.722f,  0.645f,  0.174f,
        0.302f,  0.455f,  0.848f,
        0.225f,  0.587f,  0.040f,
        0.517f,  0.713f,  0.338f,
        0.053f,  0.959f,  0.120f,
        0.393f,  0.621f,  0.362f,
        0.673f,  0.211f,  0.457f,
        0.820f,  0.883f,  0.371f,
        0.982f,  0.099f,  0.879f
    };

    glGenBuffers(1, &gIBO);
    glBindBuffer(GL_ARRAY_BUFFER, gIBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colourData), colourData, GL_STATIC_DRAW);
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

        timer.start();
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

        float time = (float)timer.getTicks() / 100;

        // Model matrix
        glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(time), glm::vec3(0.0f, 1.0f, 0.0f));
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

