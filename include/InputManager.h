#pragma once

#include <unordered_map>
#include <SDL2/SDL.h>
#include <glm/vec2.hpp>

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
            static bool isKeyReleasedInitial(unsigned int keyID);
            static unsigned int isKeyHeld(unsigned int keyID);

            static glm::uvec2 getMousePosition();
            static glm::ivec2 getMouseMotion();
            static glm::ivec2 getMouseWheelMotion();

        private:

            InputManager();

            static InputManager* instance;

            static std::unordered_map<unsigned int, bool> keyMap;
            static std::unordered_map<unsigned int, unsigned int> keyHeldMap;

            static glm::uvec2 mousePosition;
            static glm::ivec2 mouseMotion;
            static glm::ivec2 mouseWheelMotion;
    };

} // namespace RQEngine
