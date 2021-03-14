#pragma once

#include <unordered_map>
#include <SDL2/SDL.h>

namespace RQEngine
{

    class InputManager {

        public:

            static InputManager* getInstance();

            // Used in Game Class only
            static void handleEvent(SDL_Event& e);
            static void update(unsigned int deltaTime);

            static bool isKeyPressed(unsigned int keyID);
            static bool isKeyPressedInitial(unsigned int keyID);
            static unsigned int isKeyHeld(unsigned int keyID);

            // TODO Add Mouse

        private:

            InputManager();

            static InputManager* instance;

            static std::unordered_map<unsigned int, bool> keyMap;
            static std::unordered_map<unsigned int, unsigned int> keyHeldMap;

            static void pressKey(unsigned int keyID);
            static void releaseKey(unsigned int keyID);
    };

} // namespace RQEngine
