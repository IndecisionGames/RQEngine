#pragma once

#include <unordered_map>

namespace RQEngine
{
    
    class InputManager {


    public:

        static InputManager* getInstance();

        // Used in Game Class only
        static void pressKey(unsigned int keyID, unsigned int deltaTime);
        static void releaseKey(unsigned int keyID);

        static bool isKeyPressed(unsigned int keyID);
        static unsigned int isKeyHeld(unsigned int keyID);

        // TODO Add Mouse

    private:
    
        InputManager();

        static InputManager* instance;

        static std::unordered_map<unsigned int, bool> keyMap;
        static std::unordered_map<unsigned int, unsigned int> keyHeldMap;
    };

} // namespace RQEngine
