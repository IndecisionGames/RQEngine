#pragma once

#include "Limiter.h"
#include "KeyBinds.h"
#include "InputManager.h"
#include "Window.h"

namespace RQEngine
{

    class Game {

        public:
            Game();
            ~Game();

            void run();
            void exit();

            virtual void onInit() = 0;
            virtual void onExit() = 0;

            virtual void fixedUpdate(float deltaTime) = 0;
            virtual void update(float deltaTime) = 0;

            virtual void draw() = 0;

            InputManager* inputManager;
            KeyBinds* keyBinds;

            Window* window;

        private:

            void init();

            Limiter fpsLimiter;

    };

} // namespace RQEngine
