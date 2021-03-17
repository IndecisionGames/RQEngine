#include <SDL2/SDL.h>
#include <stdio.h>
#include <glm/vec2.hpp>
#include <string>
#include <iostream>

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

class TestGame: public RQEngine::Game {

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

        if (inputManager->isKeyPressed(keyBinds->getKey(AIM))) {
            glm::uvec2 mousePos = inputManager->getMousePosition();
            glm::ivec2 mouseMotion = inputManager->getMouseMotion();
            glm::ivec2 mouseWheel = inputManager->getMouseWheelMotion();

            printf("Position: (%u, %u)\n", mousePos.x, mousePos.y);
            printf("Motion: (%i,%i)\n", mouseMotion.x, mouseMotion.y);
            printf("Wheel Motion: (%i,%i)\n", mouseWheel.x, mouseWheel.y);
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

