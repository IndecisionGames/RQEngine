#include <SDL2/SDL.h>
#include <gl/glew.h>
#include <SDL2/SDL_opengl.h>
#include <gl/glu.h>
#include <stdio.h>
#include <string>

#include "RQEngine.h"

using namespace RQEngine;

class TestGame: public Game {

    void onInit() {};
    void onExit() {};

    void fixedUpdate(float deltaTime) {};
    void update() {};

    void draw() {};

};

int main(int argc, char* args[]) {

    TestGame game = TestGame();

    game.run();
    return 0;
}

