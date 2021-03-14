#include <SDL2/SDL.h>
#include <gl/glew.h>
#include <SDL2/SDL_opengl.h>
#include <gl/glu.h>
#include <stdio.h>
#include <string>
#include <iostream>

#include "RQEngine.h"

using namespace RQEngine;

class TestGame: public Game {

    void onInit() {};
    void onExit() {};

    void fixedUpdate(float deltaTime) {};
    void update(float deltaTime) {

        unsigned int keyHeldTime = inputManager->isKeyHeld(SDLK_p);
        if (keyHeldTime > 0) {
            std::cout << "Key Held: " << keyHeldTime << std::endl;
        } else if (inputManager->isKeyPressed(SDLK_p)) {
            std::cout << "Key Pressed" << std::endl;
        }
    };

    void draw() {};

};

int main(int argc, char* args[]) {

    TestGame game = TestGame();

    game.run();
    return 0;
}

