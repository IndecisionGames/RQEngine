#include <SDL2/SDL.h>
#include <gl/glew.h>
#include <SDL2/SDL_opengl.h>
#include <gl/glu.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <glm/vec2.hpp>

#include "RQEngine.h"

enum KeyCodes {

    PLAYER_UP = 10,
    PLAYER_DOWN,
    PLAYER_LEFT,
    PLAYER_RIGHT,

    DEBUG = 100,
};

class TestGame: public RQEngine::Game {

    void onInit() {

        RQEngine::keyBind keys[5] = {
            RQEngine::keyBind(PLAYER_UP, SDLK_w),
            RQEngine::keyBind(PLAYER_DOWN, SDLK_s),
            RQEngine::keyBind(PLAYER_LEFT, SDLK_a),
            RQEngine::keyBind(PLAYER_RIGHT, SDLK_d),
            RQEngine::keyBind(DEBUG, SDLK_p)
        };

        keyBinds->loadKeyBinds(keys, 5);

    };
    void onExit() {};

    void fixedUpdate(float deltaTime) {};
    void update(float deltaTime) {

        unsigned int keyHeldTime = inputManager->isKeyHeld(keyBinds->getKey(DEBUG));
        if (keyHeldTime > 0) {
            std::cout << "Key Held: " << keyHeldTime << std::endl;
        } else if (inputManager->isKeyPressed(keyBinds->getKey(DEBUG))) {
            std::cout << "Key Pressed" << std::endl;
        }
    };

    void draw() {};

};


int main(int argc, char* args[]) {

    glm::vec2 vector2 = glm::vec2(1.0f, 1.0f);

    TestGame game = TestGame();

    game.run();
    return 0;
}

